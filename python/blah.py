#!/usr/bin/python

import os, sys, pwd

blah = "ha ha string"

print blah+"asdfadsf"


sys.stdout.write("bleh out\n")

def something(text):
	print text



something("things goes wrong\n\n")

i = 23

if i != "24":
	print 'sorry "i" ist nicht 24'


print 'blah %s' % i






array = [' blah', 'bleh ', 'blih']

#letztes zeichen eines wertes ausgeben... 

for word in array:
	if word[0] == ' ':
		print 'space is there'
	
	length = len(word)
	char = word[0:length-1]
	print 'last char:'+ char





haha = 'miau'
print haha
haha += 'blah'
print haha

def fucker(s):
	s.replace('a','fuck')
	return s

einevar = "aoiuua"
einevar.fucker()
