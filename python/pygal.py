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
					<link href='../style.css' rel='stylesheet' media='screen' />\n \
					<script src='http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js'></script>\n \
					<script src='../galleria/src/galleria.js'></script>\n \
					<script>Galleria.loadTheme('../galleria/src/themes/classic/galleria.classic.js');</script>\n \
				</head>\n \
				<body>\n \
					<h2>[title]</h2> \n \
					<script>$('.images').galleria({height: 650});</script>\n \
					<div class='images'>\n \
						[imglist] \
					</div>\n \
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

	def maxSize(self, image, maxSize, method = 3):
		imAspect = float(image.size[0])/float(image.size[1])
		outAspect = float(maxSize[0])/float(maxSize[1])

		if imAspect >= outAspect:
			return image.resize((maxSize[0], int((float(maxSize[0])/imAspect) + 0.5)), method)
		else:
			return image.resize((int((float(maxSize[1])*imAspect) + 0.5), maxSize[1]), method)

	# process (rotate/resize) images 
	def processImages(self):
		print "Processing images..."
		from PIL import Image
		from PIL.ExifTags import TAGS
		for i in self.picArr:
			print "rotating and resizing %s" % i
			img = Image.open(i)
			exif = img._getexif()
			if exif != None:
				for tag,value in exif.items():
					decoded = TAGS.get(tag,tag)
					if decoded == 'Orientation':
						if value == 3: img = img.rotate(180)
						if value == 6: img = img.rotate(270)
						if value == 8: img = img.rotate(90)
						break
			img = self.maxSize(img,(800,600), Image.ANTIALIAS)
			img.save(i,'JPEG',quality=95)

		print "Done processing images!"


	def createThumbs(self):
		import Image
		print "Creating thumbnails..."
		if not os.path.isdir('tnails'):
			os.mkdir('tnails')
		for i in pygal.picArr:
			print i

	def createHtml(self):
		print "Generating html index"
		linetmpl = "<img src='%s' alt='%s %s'>\n"
		
		self.images = ""
		for i in pygal.picArr:
			 self.images += linetmpl % (i,self.name,i)
		
		title = re.compile('\[title\]')
		self.tmpl = title.sub(self.name,self.tmpl)

		p = re.compile('\[imglist\]')
		self.tmpl = p.sub(self.images, self.tmpl)


	def createGal(self):
		print "Creating Gallery %s" % pygal.name
		self.getPics()
		self.processImages()
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
