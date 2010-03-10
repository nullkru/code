
import re

text = ('blah bleh blhe bliu'
		'asdfasdf'
		'enter your busty nasti hole pric tick [asdfasdr]'
		'http://www.chao.ch/index.php'
		'chao.ch/blah/bleh/miau.php')
matchthis = re.findall('enter your', text)
if not matchthis:
	print "miau not found mf"
else:
	print "ok found"
	print matchthis


m = re.search('\/.*\/(.*)\.php$', text)
print m.group(1)
