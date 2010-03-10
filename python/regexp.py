#!/usr/bin/python

import re

#text = "2 3 asdf.php?test=yay 6"
text = '4/22'
#m = re.match("\d", text)
m = re.match("(\d*)\/\d*", text)

if m:
	print m.group(1)
else:
	print "nothing found..."
