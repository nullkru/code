#!/usr/bin/python2
#-*- coding: UTF-8 -*-
import sys, os, re

class krename:
	
	#aktuelles verzeichnis
	curDir = 0 
	
	renamed = 0 #falls nichts veraendert wurde bleit dieser wert auf 0
	#getopt param
	verbose = 0
	trymode = 0
	filesonly = 0

	def __init__(self):
		import getopt
		from optparse import OptionParser
		

		usage = "usage: %prog [options]"
		parser = OptionParser(usage)
		parser.add_option("-v", action="count", dest="verbose",
				help="be verbose")
		parser.add_option("-t", action="count", dest="trymode",
				help="try mode, just print what it will do")
		parser.add_option("-f", action="count", dest="filesonly",
				help="only rename files (no directorys)")
		parser.add_option("-d", metavar="DIR", dest='renamedir',
				help="rename file in given directory")

		(options, args) = parser.parse_args()
		
		#fill the class vars
		krename.verbose = options.verbose
		krename.trymode = options.trymode
		krename.filesonly = options.filesonly
		
		if not options.renamedir:
			krename.curDir = os.getcwd()
		else:
			krename.curDir = os.path.abspath(options.renamedir)
		
	def getDirContent(self):
		self.fileList = []	
		dirContent = os.listdir(krename.curDir)
		for file in dirContent:
			absoluteFileName = "%s/%s" % (krename.curDir, file)
			m = re.match("^\.",file)
			if not krename.filesonly:
				if os.path.exists(absoluteFileName) and not m:
					self.fileList.append(file)
			#only if file only switch is true else 
			else:
				if os.path.isfile(absoluteFileName) and not m:
					self.fileList.append(file)
		
		return self.fileList

	def cleanName(self, value):
		renameChars = {
				'\xc3\xa4': 'ae',
				'\xc3\x84': 'Ae',
				'\xc3\xb6': 'oe',
				'\xc3\x96': 'Oe',
				'\xc3\xbc': 'ue',
				'\xc3\x9c': 'Ue',
				'&': 'and',
				' ': '_',
				',': '_',
				'(': '_',
				')': '_',
				'}': '',
				'{': '',
				'[': '',
				']': '',
				'`': '',
				'\'':''
		}
		#begin replacing special chars
		name = value
		for char, repChar in renameChars.items():
			name = name.replace(char,repChar)
		
		try: name = str(name)
		except:
			print "oh oh... error"
			raise
	
		name = re.sub(r'\s+-\s+', '-', name)
		name = re.sub(r'[^a-zA-Z0-9_\- \.&!,\'?()]', '', name)
		name = name.strip()
		name = name.lower()

		if name != value:		
			if krename.verbose:
				print "rename from: %s -> %s" % (value, name)
			return name
	
	def renameIt(self, name, newname):
		if not os.path.exists(newname):
			try: 
				os.rename(name, newname)
				self.renamed = 1
			except:
				print "rename error"
				raise
		else: print "file exists: %s" % newname

	def main(self):
		if krename.trymode:
			krename.verbose = 1
		
		#go trough all files and clean it if necessary
		for file in self.getDirContent():
			newName = self.cleanName(file)
			if newName and not krename.trymode:
				file = "%s/%s" % (krename.curDir, file)
				newName = "%s/%s" % (krename.curDir, newName)
				self.renameIt(file, newName)

		if not self.renamed and not self.trymode:
			print "nothing todo..."
			
				
#end krename class
if __name__ == "__main__":
	kr = krename()
	try: kr.main()
	except: 
		print "hew exception error..."
		import traceback
		traceback.print_exc()
