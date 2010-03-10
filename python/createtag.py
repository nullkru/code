#!/usr/bin/python

class kxml:
	def crTag(self, val, xmltag, indent = 0):
		string = '<'+xmltag+'>'+val+'</'+xmltag+'>\n'
		if indent != 0:
			return  '\t' * indent + string
		else:	
			return string  



k = kxml()
blah = k.crTag('ich bin der wert','tag')
blah = blah + k.crTag('erste stufe', 'zwei', 1)

print blah
