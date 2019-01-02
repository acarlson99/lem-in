#!/usr/bin/env python3

# TODO: implement

import sys
import fileinput
import re
import contextlib
with contextlib.redirect_stdout(None):
    import pygame
    from pygame.locals import *

def main():
    lines = [n.rstrip() for n in fileinput.input()]
    for n in lines:
        print(n)

if __name__ == "__main__":
    main()
