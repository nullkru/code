#!/usr/bin/python2

import re

#text = "2 3 asdf.php?test=yay 6"
text = ('blahbleh.jpg' 'miau.gif')
#m = re.match("\d", text)
m = re.match(".*\.(jpg|JPG|png|PNG|jpeg|gif)", text)

if m:
	print m.group(0)
else:
	print "nothing found..."
