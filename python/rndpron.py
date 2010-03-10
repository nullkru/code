#!/usr/bin/python

#path = '/mnt/data/movies/norp/new'
path = '/home/kru/multimedia/movies/.norp'
player = 'mplayer -fs '

import random, os, dircache

list = dircache.listdir(path)

def playthis():
	rndfile = random.choice(list)
	command = player + path +'/'+ rndfile
	os.system(command) 

playthis()
while ( 1 ):
	next = raw_input('next [y/n]:')
	if next.lower() == 'n':
		break
	else:
		playthis()
		next=0

