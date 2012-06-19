#!/usr/bin/python2
from mutagen.id3 import ID3 as id3
import sys

x = id3(sys.argv[1])

print "filename: %s" % sys.argv[1]
for i,a in x.iteritems():
	print "%s:\t\t%s" %  (i, a)
