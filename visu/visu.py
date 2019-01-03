#!/usr/bin/env python3

import sys
import fileinput
import random
import re
import contextlib
with contextlib.redirect_stdout(None):
    import pygame
    from pygame.locals import *

FPS = 30

#            R    G    B
GRAY     = (100, 100, 100)
NAVYBLUE = ( 60,  60, 100)
WHITE    = (255, 255, 255)
BLACK    = (  0,   0,   0)
RED      = (255,   0,   0)
GREEN    = (  0, 255,   0)
BLUE     = (  0,   0, 255)
YELLOW   = (255, 255,   0)
PURPLE   = (255,   0, 255)
CYAN     = (  0, 255, 255)
VIOLET   = (110,  60, 135)
DGREEN   = (165, 105, 178)
MUSTARD  = (229, 137, 100)
ORANGE   = (206,  90,  57)
DPURPLE  = ( 41,  50,  65)

GREEN    = ( 79, 255, 151)
DGREEN   = ( 15,  91,  82)
PINK     = (220,  40,  90)
DPINK    = (111,  29,  74)

BGCOLOR = ( 32,  40,  55)
ANTCOLOR = BLACK
ROOMCOLOR = PURPLE
STARTCOLOR = RED
ENDCOLOR = BLUE

ANTS_ERR = 1
ROOM_ERR = 2
CONN_ERR = 4

WINDOWWIDTH = 1000
WINDOWHEIGHT = 1000

ANT_LIST = [
    "/assets/ant_00.png",
    "/assets/durant_comma_kevin.png"
]

class Ant:

    def __init__(self, name, start):
        self.name = name
        self.seed = random.randint(0, 100)
        self.x, self.y = start
        self.image = pygame.image.load(sys.path[0] + ANT_LIST[self.seed % len(ANT_LIST)]).convert()
        self.move_list = None

        # self.image.set_colorkey((255, 255, 255))
        # self.size = self.image.get_size()
        # self.image = pygame.transform.scale(self.image, (int(self.size[0]*0.25), int(self.size[1]*0.25)))
        # TODO: Maybe use these to scale images n stuff idk bro it's up to you :shrug:

class Room:

    def __init__(self, name, coords, start_end=0):
        self.name = name
        self.x, self.y = coords
        self.start_end = start_end  # start = -1; end = 1; other = 0
        self.conns = {}
        self.disp_x = self.x * 3
        self.disp_y = self.y * 3
        self.disp_size = 10
        self.center = (self.disp_x + self.disp_size / 2, self.disp_y + self.disp_size / 2)

    def __str__(self):
        return ("Room %s start_end %d pos (%d, %d)" % (self.name, self.start_end, self.x, self.y))

    def add_conn(new):
        self.conns[new.name] = new

class Game:

    def __init__(self):
        pygame.init()
        pygame.key.set_repeat(105, 5)
        self.clock = pygame.time.Clock()
        self.surf = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT), 0, 32)
        pygame.display.set_caption("lem-in visualizer\n")
        self.fps = FPS
        self.num_ants = None
        self.room_max_x = None
        self.room_max_y = None
        self.room_min_x = None
        self.room_min_y = None
        self.roommap = {}
        self.antmap = {}
        self.start = None
        self.end = None

    def __str__(self):
        try:
            return "Num_ants %d max_x %d max_y %d min_x %d min_y %d" % (self.num_ants, self.room_max_x, self.room_max_y, self.room_min_x, self.room_min_y)
        except TypeError:
            return "Type error"

    def events(self):
        for self.event in pygame.event.get():
            if self.event.type == QUIT:
                self.quit()
            if self.event.type == KEYDOWN:
                if self.event.key == 113 or self.event.key == 27:
                    self.quit()

    def display_ant(self, ant):
        # img_rect = ant.image.get_rect()
        # img_rect.center = (ant.x, ant.y)
        # self.surf.blit(ant.image, img_rect)
        pygame.draw.circle(self.surf, ANTCOLOR, (ant.x, ant.y), 10, 0)

    def add_conn(self, line):
        n = line.split('-')
        try:
            self.roommap[n[0]].conns[n[1]] = self.roommap[n[1]]
            self.roommap[n[1]].conns[n[0]] = self.roommap[n[0]]
        except KeyError:
            print_err(CONN_ERR)

    def add_room(self, line, start_end):
        n = line.split(' ')
        new = Room(n[0], (int(n[1]), int(n[2])), start_end)
        if self.room_max_y == None or self.room_max_y < new.y:
            self.room_max_y = new.y
        if self.room_max_x == None or self.room_max_x < new.x:
            self.room_max_x = new.x
        if self.room_min_y == None or new.y < self.room_min_y:
            self.room_min_y = new.y
        if self.room_min_x == None or new.x < self.room_max_x:
            self.room_min_x = new.x
        self.roommap[new.name] = new

    def draw_rooms(self):
        for rname in self.roommap:
            if self.roommap[rname].start_end == -1:
                room_color = STARTCOLOR
            elif self.roommap[rname].start_end == 1:
                room_color = ENDCOLOR
            else:
                room_color = ROOMCOLOR
            pygame.draw.rect(self.surf, room_color, (self.roommap[rname].disp_x, self.roommap[rname].disp_y, self.roommap[rname].disp_size, self.roommap[rname].disp_size))

    def draw_connections(self):
        for rname in self.roommap:
            room_a = self.roommap[rname]
            for cname in room_a.conns:
                room_b = self.roommap[cname]
                pygame.draw.line(self.surf, BLUE, room_a.center, room_b.center)

    def update_rooms(self): # TODO: update display variables
        pass

    def read_input(self):
        lines = [n.rstrip() for n in fileinput.input()]
        linum = len(lines)
        n = 0
        start_end = 0
        room_p = re.compile("(?:(?:[a-zA-Z0-9_]+ \d+ \d+$)|(?:^#))")
        try:
            self.num_ants = int(lines[n])
            n += 1
        except ValueError:
            print_err(ANTS_ERR)
        while n < linum and room_p.match(lines[n]):
            if lines[n][0] == '#':
                if lines[n] == '##start':
                    start_end = -1
                elif lines[n] == '##end':
                    start_end = 1
                n += 1
                continue
            else:
                self.add_room(lines[n], start_end)
            start_end = 0
            n += 1
        conn_p = re.compile("(?:(?:^[a-zA-Z0-9_]+-[a-zA-Z0-9_]+$)|(?:^#))")
        while n < linum and conn_p.match(lines[n]):
            if lines[n][0] == '#':
                pass
            else:
                self.add_conn(lines[n])
            n += 1
        self.update_rooms()

    def quit(self):
        pygame.quit()
        sys.exit()

    def draw(self):
        self.surf.fill(WHITE)
        self.draw_connections()
        self.draw_rooms()
        pygame.display.update()

    def run(self):
        while 1:
            self.clock.tick(self.fps)
            self.events()
            self.draw()

def print_err(code):
    if code == CONN_ERR:
        print("Connection error")
        pygame.quit()
        sys.exit()

def main():
    g = Game()
    g.read_input()
    print(g)
    g.run()

if __name__ == "__main__":
    main()

    # a
