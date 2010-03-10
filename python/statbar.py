#!/usr/bin/python

import sys, os, time

if len(sys.argv) < 3:
	print "command args: <file with commands> <update interval>"
else:
	while 1:
		command = '/bin/bash %s' % sys.argv[1]
		os.system(command)
		time.sleep(int(sys.argv[2]))

