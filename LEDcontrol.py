#Controls am 8x8 LED matrix through the serial line

import serial, sys, math
import pygame
import time
import array
import math
import numpy as np
from pygame.locals import *
yellow = (255,255,0)
black = (0,0,0)
blue = (0,0,255)
ser = serial.Serial('/dev/ttyUSB0', 4800, timeout=None, parity='N', bytesize=8, stopbits=1, xonxoff=0, rtscts=0)
print ser.name

c = np.ones((8,8), dtype=bool)
pygame.init()
screen = pygame.display.set_mode((500,500))
myfont = pygame.font.SysFont("monospace", 25)
clock = pygame.time.Clock()
background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((255,255,255))
screen.blit(background, (0,0))
pygame.display.flip()
on = pygame.image.load('on.png')
off = pygame.image.load('off.png')

while True:
    ev = pygame.event.poll()
    if ev.type == pygame.QUIT:
        break
    for a in range(0,8):
        x = 100
        y = 100+30*a
        for b in range(0,8):
            if c[a,b] == 1:
                screen.blit(off, (x+30*b,y))
            else:
                screen.blit(on, (x+30*b,y))
    if ev.type == MOUSEBUTTONDOWN:
        d,f = ev.pos
        for a in range(0,8):
            x = 100 + 30*a
            y = 100 + 30*a
            if d >= x and d <= x+30:
                n = a
            if f >= y and f <= y+30:
                m = a
        if c[m,n] == True:
            c[m,n] = False
        else:
            c[m,n] = True
        u = str(n)
        i = str(m)
        data = u + i
        print u
        print i
        ser.write(u)
        ser.write(i)     
    pygame.display.flip()
