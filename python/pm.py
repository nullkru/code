#!/usr/bin/python

orders = [
	'Sleep->sudo pm-suspend',
	'Hibernate->sudo pm-hibernate',
	'Shutdown->shutdown -h 0'
	]

class pm():
	
	commands = []
	menu = ''	
	def __init__(self):
		import sys

		i = 0
		for order in orders:
			point =  order.split('->')
			self.commands = self.commands + [point[1]]
			self.menu += "%d - %s\n" % (i, point[0])
			i+=1
		try: sys.argv[1]
		except: print self.menu
		else: self.action(int(sys.argv[1]))

	def action(self,number):
		import os
		os.system(self.commands[int(number)])

try:
	pm = pm()
	pm.action(raw_input('Execute #'))
except:
	print 'sorry not avaliable'

