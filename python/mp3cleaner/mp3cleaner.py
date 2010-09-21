#!/usr/bin/python
#-*- coding: UTF-8 -*-
'''
Depencies:
	PIL : python image library
	mutagen : python metadata tag reader/writer
TODO: + output format definieren in config %a_-_%t_-_usw
	+ compilation mode and enhanced mode ( title, trackno ...) 
	+ better class... 
	+ code cleanup

'''
import mutagen,string, sys, os, re, Image

class cleaner(object):
	
	single = 0
	compilation = 0
	album = 1

	def __init__(self):
		from mutagen.easyid3 import EasyID3 as id3 
		self.id3 = id3
		
		import getopt
		from optparse import OptionParser

		usage = "usage: %prog [options]"
		parser = OptionParser(usage)
		parser.add_option("-s", dest="single", help="use settings for a single file")
		parser.add_option("-c", action="count", dest="compilation", help="use settings for Compilations")
		
		(options, args) = parser.parse_args()
		cleaner.single = options.single
		cleaner.compilation = options.compilation 
	
	def getMp3info(self, file):
		self.x  = self.id3(file)
		x = self.x

		try: x['artist'] = x['artist']
		except: self.x['artist'] = 'na'

		try: x['title'] = x['title']
		except: self.x['title'] = 'na'

		try: x['album'] = x['album']
		except: self.x['album'] = 'na'

		try: x['tracknumber'] = x['tracknumber']
		except: self.x['tracknumber'] = 'na'

		try: x['date'] = x['date']
		except: self.x['date'] = 'na'
		
		if self.compilation:
			try: x['performer'] = x['performer']
			except: self.x['performer'] = 'na'
			try: x['discnumber'] = x['discnumber']
			except: self.x['discnumber'] = 'na'

		try: x['genre'] = x['genre']
		except: self.x['genre'] = 'na'

		#search for cover
		self.getCover()
	
	albumArt = 0

	def getCover(self):
		CoversInDir = os.listdir(os.getcwd())
		for cover in CoversInDir:
			m = re.match(".*\.(jpg|jpeg)", cover.lower())
			if m and not self.albumArt:
				self.albumArt = cover
				
	def resizeCover(self, coverfile):
		img = Image.open(coverfile)
		coverout = img.resize((300,300), Image.ANTIALIAS)
		#filename = '%s' % coverfile.lower()
		filename = 'folder.jpg'
		coverout.save(filename)
		return filename

	def addCover(self,file,cover):
		from mutagen.id3 import ID3, APIC, error
		from mutagen.mp3 import MP3

		cover = self.resizeCover(cover)
		audio = MP3(file, ID3=ID3)
		audio.tags.add(
				APIC(
					encoding=3,
					mime='image/jpeg',
					type=3,
					desc=u'Cover',
					data=open(cover).read()
					)
		)
		audio.save()

	def setMp3info(self, artist=0, album=0, date=0, title=0, track=0, genre=0):
		b = self.basedata

		if artist: 
			self.x['artist'] = u'%s' % artist
		
		if title and title != self.x.title:
			self.x['title'] = u'%s' % title
		
		if album:
			self.x['album'] = u'%s' % album
		
		if track and track != self.x['tracknumber']:
			self.x['tracknumber'] = track
		
		if date:
			self.x['date'] = u'%s' % date

		if genre:
			self.x['genre'] = u'%s' % genre


		if self.compilation:
			self.x['compilation'] = u'1'
			self.x['discnumber'] = u'%s' % self.compilationdisc 

		if self.compilationperformer:
			self.x['performer'] = b['performer']
			

		self.x.save()

	def cleanName(self, name):
		#replace chart
		specialchars = {
			'\xc3\x84': 'a', #Ä
			'\xc3\xa4': 'a', #ä
			'\xc3\x9c': 'u', #Ü
			'\xc3\xbc': 'u', #ü
			'\xc3\xb6': 'o', #ö
			'\xc3\x96': 'o', #Ö
			'\xc3\xad' : '', #í
			'\xc3\xa1': 'a', #á
			'\xc3\xa9': 'e', #é
			'\xc3\xa7': 'c', #ç
			'&': 'and',
			'?':'',
			'!':'',
			' ': '_',
			"'":'',
			'`': '',
			'(': '',
			')': '',
			',': ''
			}

		if isinstance(name, unicode):
			name = name.encode('utf-8')
		for val, repl in specialchars.items():
			name = name.replace(val, repl) #.encode('utf-8')
		try:
			name = name.encode('utf-8')
		except:
			print "Bad name:", repr(name), '=', str(name)
			raise
		for val, repl in [(':', ','),
			('&amp;', '&'),
			('&amp', '&'),
			]:
			name = name.replace(val, repl)
		name = re.sub(r'\s+-\s+', '-', name)
		name = re.sub(r'[^a-zA-Z0-9_\- \.&!,\'?()]', '', name)
		name = name.strip()
		return name

	albumArtChoosen = 0
	discnumberOK = 0
	def askParams(self, quiet=1):
		new = {}
		if self.x['title'] == 'na' or not quiet:
			new['title'] = raw_input('Title (%s):' % self.x['title'][0])
		
		if self.x['tracknumber'] == 'na' or not quiet:
			new['track'] = raw_input('Track # (%s):' % self.x['tracknumber'][0])
	
		if not cleaner.compilation:
			new['artist'] = raw_input('Artist (%s):' % self.x['artist'][0])
			if not new['artist']:
				new['artist'] = self.x['artist'][0]

		if not cleaner.compilationperformer and self.compilation:
			new['performer'] =  raw_input('Album Artist (Performer) (%s):' % self.x['performer'][0])
			if not new['performer']:
				new['performer'] = self.x['performer'][0]
		else:
			new['performer'] = cleaner.compilationperformer

		if not cleaner.compilationalbum:
			new['album'] = raw_input('Album (%s):' % self.x['album'][0])
			if not new['album']:
				new['album'] = self.x['album'][0]
		else:
			new['album'] = cleaner.compilationalbum
		
		if not cleaner.compilationdate:
			new['date'] =  raw_input('Year (%s):' % self.x['date'][0])
			if not new['date']:
				new['date'] = self.x['date'][0]
		else:
			new['date'] = cleaner.compilationdate

		if not cleaner.compilationgenre:
			new['genre'] =  raw_input('Genre (%s):' % self.x['genre'][0])
			if not new['genre']:
				new['genre'] = self.x['genre'][0]
		else:
			new['genre'] = cleaner.compilationgenre
		
		if not self.albumArtChoosen:
			new['cover'] = raw_input('Front Cover (%s):' % self.albumArt)
			self.albumArtChoosen = 1 # don't ask again for compilations
		else:
			new['cover'] = self.albumArt

		if cleaner.compilation and not self.discnumberOK:
			new['discnumber'] = raw_input('Compilation Disc no. (eg.1/3) (%s): ' % self.x['discnumber'][0])
			self.discnumberOK = 1
			if not new['discnumber']:
				new['discnumber'] = self.x['discnumber'][0]

		#write the infos to the basedata class var
		self.basedata = new	
		

	def newFilename(self, file=0, test=0):
		x = self.x
		
		#get format for trackno eg. just 1 or 1/23
		track = x['tracknumber'][0]
		m = re.match("^(\d*)\/\d*", track)
		if m:
			track = m.group(1)

		if len('%s' % track) < 2:
			track = '0%s' % track 
		
		if cleaner.compilation:
			newName = ('%s_-_%s_-_%s_-_%s.mp3'  % (x['album'][0], track,  x['artist'][0], x['title'][0])).lower()
		else:
			newName = ('%s_-_%s_-_%s_-_%s.mp3'  % (x['artist'][0], x['album'][0], track, x['title'][0])).lower()
		newName =  self.cleanName(newName)
		if not test:
			os.rename(file, newName)
			print '%s renamed to %s' % (file, newName)
		else:
			print '%s renamed to %s' % (file, newName)
	
	def getFiles(self, dir=0):
		del sys.argv[0]
		self.Files = []
		for i in sys.argv:
			self.Files.append(i)

		return self.Files
		
	def isAlbum(self, firstfile, test=0):
		self.getMp3info(firstfile)
		self.askParams()
		b = self.basedata
		for file in self.Files:
			self.getMp3info(file)
			if not test:
				self.setMp3info(b['artist'], b['album'], b['date'], 0, 0, b['genre'])
				if b['cover']:
					self.addCover(file,b['cover'])
			self.newFilename(file, test)


	#compilation specifig vars
	compilationalbum = 0
	compilationdate = 0
	compilationgenre = 0
	compilationperformer = 0
	compilationdisc = 0

	def isCompilation (self, fileList, test=0):
		fileList.pop(0)
		for file in fileList:
			self.getMp3info(file)
			self.askParams()
			if not cleaner.compilationalbum:
				cleaner.compilationalbum = self.basedata['album']
			if not cleaner.compilationdate:
				cleaner.compilationdate = self.basedata['date']
			if not cleaner.compilationgenre:
				cleaner.compilationgenre = self.basedata['genre']
			if not cleaner.compilationperformer:
				cleaner.compilationperformer = self.basedata['performer']
			if not cleaner.compilationdisc:
				cleaner.compilationdisc = self.basedata['discnumber']
			b = self.basedata
			if not test:
				self.setMp3info(0, b['album'], b['date'], 0, 0, b['genre'])
				if b['cover']:
					self.addCover(file,b['cover'])
			self.newFilename(file, test)

	def isSingle(self, file, test=0):
		self.album = 0
		self.getMp3info(file)
		self.askParams(0)
		b = self.basedata
		self.setMp3info(b['artist'], b['album'], b['date'], b['title'], b['track'], b['genre'])
		self.newFilename(file, test)

	def main(self):
		if cleaner.single:
			self.isSingle(cleaner.single)
		if cleaner.compilation:
			files = self.getFiles()
			self.isCompilation(files)
		#default is album mode
		if not cleaner.compilation:
			files = self.getFiles()
			try: files[0] 
			except:
				print "at least one argument is required"
				return 1
			self.isAlbum(files[0])

#end class

if __name__ == "__main__":
	c = cleaner()
	try: c.main()
	except:
		import traceback
		traceback.print_exc()
		print 'omfg error'
		sys.exit(1)
