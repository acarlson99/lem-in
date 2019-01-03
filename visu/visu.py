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

        # self.image.set_colorkey((255, 255, 255))
        # self.size = self.image.get_size()
        # self.image = pygame.transform.scale(self.image, (int(self.size[0]*0.25), int(self.size[1]*0.25)))
        # TODO: Maybe use these to scale images n stuff idk bro it's up to you :shrug:

class Room:

    def __init__(self, name, coords, start_end=0):
        self.name = name
        self.x, self.y = coords
        self.start_end = start_end
        self.conns = {}
        self.disp_x = self.x * 3
        self.disp_y = self.y * 3
        self.disp_size = 10

    def __str__(self):
        return ("Room %s start_end %d pos (%d, %d)" % (self.name, self.start_end, self.x, self.y))

    def add_conn(new):
        self.conns[new.name] = new

class Game:

    def __init__(self):
        pygame.init()
        self.clock = pygame.time.Clock()
        self.surf = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT), 0, 32)
        self.fps = FPS
        self.num_ants = None
        self.room_max_y = None
        self.room_max_x = None
        self.room_min_y = None
        self.room_min_x = None
        self.roommap = {}
        self.antmap = {}
        self.start = None
        self.end = None

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
        self.roommap[n[0]].conns[n[1]] = self.roommap[n[1]]
        self.roommap[n[1]].conns[n[0]] = self.roommap[n[0]]
        pass

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
            pygame.draw.rect(self.surf, ORANGE, (self.roommap[rname].disp_x, self.roommap[rname].disp_y, self.roommap[rname].disp_size, self.roommap[rname].disp_size))

    def draw_connections(self):
        for rname in self.roommap:
            for cname in self.roommap[rname].conns:
                pygame.draw.line(self.surf, BLUE, (self.roommap[rname].disp_x, self.roommap[rname].disp_y), (self.roommap[cname].disp_x, self.roommap[cname].disp_y))

    def update_rooms(self): # TODO: update display variables
        pass

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

def main():
    lines = [n.rstrip() for n in fileinput.input()]
    linum = len(lines)
    n = 0
    start_end = 0
    room_decl_p = re.compile("(?:(?:[a-zA-Z0-9_]+ \d+ \d+$)|(?:^#))")
    g = Game()
    try:
        g.num_ants = int(lines[n])
        n += 1
    except ValueError:
        print("Parsing error")
        sys.exit()
    while n < linum and room_decl_p.match(lines[n]):
        if lines[n][0] == '#':
            if lines[n] == '##start':
                start_end = -1
            elif lines[n] == '##end':
                start_end = 1
            n += 1
            continue
        else:
            g.add_room(lines[n], start_end)
        start_end = 0
        n += 1
    room_conn_p = re.compile("(?:(?:^[a-zA-Z0-9_]+-[a-zA-Z0-9_]+$)|(?:^#))")
    while n < linum and room_conn_p.match(lines[n]):
        if lines[n][0] == '#':
            pass
        else:
            g.add_conn(lines[n])
        n += 1
    g.update_rooms()
    for j in g.roommap:
        print(g.roommap[j])
        for k in g.roommap[j].conns:
            print('Connedted to ' + str(g.roommap[j].conns[k]))
    g.run()

if __name__ == "__main__":
    main()
