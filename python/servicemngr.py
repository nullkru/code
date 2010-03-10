#!/usr/bin/python

import os, subprocess, dircache

if os.getuid() is not 0:
	print "You must be root to run this"
	exit(1)

try:
	rcdir = '/etc/rc.d/'

	services = dircache.listdir(rcdir)

	def do_action(serviceint):
		actions = ['nothing', 'restart', 'stop', 'start']
		os.system('clear')
		print "You choosed: %s " % services[serviceint]
		print """
	What should i do?
	[0]%s
	[1]%s
	[2]%s
	[3]%s""" % (actions[0], actions[1], actions[2], actions[3])
		actionint = int(raw_input('#->'))
		
		if actionint is not 0:
			command = '%s%s %s' % (rcdir, services[serviceint], actions[actionint])
			os.system(command)

	while [ 1 ]:
		i=0
		for service in services: 
			print "[%s] -> %s" % (i, service) 
			i+=1
		do_action(int(raw_input('Service #: ')))
except:
	exit(1)
