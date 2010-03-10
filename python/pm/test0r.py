#!/usr/bin/python
#-*- coding: UTF-8 -*-
import postmail, sys

pm = postmail.postmail()
'''
print pm.parseCSV(sys.argv[1])


blah = pm.crTag('blah', 'eins',0,1)
blah += pm.crTag('bli', 'zwei',0,1)
	
print pm.crTag(blah, 'zwei','blah="bleh"', 1, 1)


print pm.crTag(pm.crTag('value', 'drei', 'attrib', 1, 0), 'blah', 0,0,1)
'''

pm.crSETIstring('BB',4,'aaa', 1, 13500, 301, '23-23-23')
blah = pm.crSETIstring('BB',4,'aaa', 1, 13500, 301, '23-23-23')


print blah 
print pm.QUANTITY
