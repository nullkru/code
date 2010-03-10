#!/usr/bin/python

import random, dircache, os, sys

path = sys.argv[1]

pictures = dircache.listdir(path)

rndfile =  random.choice(pictures)
command = "feh --bg-scale " + path +'/' +rndfile 
os.system(command)

