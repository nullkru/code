#!/usr/bin/python

import os, sys

EDITOR='vim '

os.system(EDITOR + 'timer.txt')

f = open('timer.txt')
content = f.readlines()
print content
