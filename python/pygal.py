#!/usr/bin/python

import sys, os, re

class pygal(object):

	name = 0
	FILE = 0

	def __init__(self):
		import getopt

		from optparse import OptionParser
		usage = "usage: %prog [options]"
		parser = OptionParser(usage)
		parser.add_option('-n', dest="name", help="set gallery name")
		parser.add_option('-f', dest="filename", help='html output file')
		
		(options, args) = parser.parse_args()
		pygal.name = options.name
		pygal.FILE = options.filename

	
	#html templates
	tmpl = "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>\n \
			<html>\n \
				<head>\n \
					<title>[title]</title>\n \
					<!--<link href='css/snip.style.css' rel='stylesheet' media='screen' />-->\n \
					<script src='http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js'></script>\n \
					<script src='../galleria/src/galleria.js'></script>\n \
					<script>Galleria.loadTheme('../galleria/src/themes/classic/galleria.classic.js');</script>\n \
				</head>\n \
				<body>\n \
					<h2>[title]</h2> \n \
					<div class='images'>\n \
						[imglist] \
					</div>\n \
					<script>$('.images').galleria();</script>\n \
				</body>\n \
			</html>\n"


	# picture array
	picArr = []
	def getPics(self, dir=0):
		self.Pics = []
		for i in sys.argv:
			m = re.match('.*\.(jpg|JPG|jpeg|png|PNG)', i)
			if m:
				self.Pics.append(i)

		pygal.picArr = self.Pics

	def createThumbs(self):
		import Image
		print "Creating thumbnails..."
		if not os.path.isdir('tnails'):
			os.mkdir('tnails')
		for i in pygal.picArr:
			print i

	def createHtml(self):
		print "Generating html index"
		linetmpl = "<img src='%s' alt='%s'>\n"
		
		self.images = ""
		for i in pygal.picArr:
			 self.images += linetmpl % (i,i)
		
		title = re.compile('\[title\]')
		self.tmpl = title.sub(self.name,self.tmpl)

		p = re.compile('\[imglist\]')
		self.tmpl = p.sub(self.images, self.tmpl)


	def createGal(self):
		print "Creating Gallery %s" % pygal.name
		self.getPics()
		#self.createThumbs()
		self.createHtml()
		f = open(self.FILE,"w")
		f.write(self.tmpl)
		f.close()

	def main(self):
		if not pygal.name or not pygal.FILE:
			print "please enter a name and output file"
			return 1
		else:
			self.createGal()


if __name__ == "__main__":
	g = pygal()
	try: g.main()
	except:
		import traceback
		traceback.print_exc()
