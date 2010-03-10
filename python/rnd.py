#!/usr/bin/python

import random, dircache, os

#blah = ['eins', 'zwei', 'drei', 'vier']
#blah = 'eins zwei drei vier'
#f = open('bleh.csv')
#blah = f.readlines()

path = '/home/kru/movies'

blah = dircache.listdir(path)

#rndzahl = random.choice(blah)

def playthis():
	rndfile =  random.choice(blah)
	command = "mplayer -fs " + path +'/' +rndfile 
	os.system(command)

playthis()

more = 0
while( 1 ):
	more = raw_input('more y/n: ')
	if more == "n":
		break
	else:
		playthis()
		more = 0
