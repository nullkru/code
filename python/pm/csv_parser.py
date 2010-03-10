#!/usr/bin/python

def parseCSV(aFile):

	f = open(aFile)
	lines = f.readlines()

	for line in lines:
		splited = line.split(';')
		i = 0
		for val in splited:
			print splited[i]
			i += 1

import sys

parseCSV(sys.argv[1])
