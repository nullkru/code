#!/usr/bin/python

class postmail:
	
	QUANTITY = 0

	#create XML structure
	def crTag(self, val, xmltag, attrib=0, ind=0, hasChild=0):
		
		if not attrib:
			xmlstarttag=xmltag
		else:
			xmlstarttag=xmltag + ' ' + attrib

		indent = '\t' * ind
		
		if ind and hasChild:
			val = val.split('\n')
			newval = ''
			valSize = len(val)-1
			i=0
			for line in val:
				if i != valSize: 
					newval += indent + line + '\n'
				else:
					newval += indent + line
				i+=1

			string = '%s<%s>\n%s</%s>\n' \
				% (indent, xmlstarttag, newval, xmltag)
			return  string
		
		if not ind and hasChild:
			return '<%s>\n%s</%s>\n' % (xmlstarttag, val, xmltag)
		
		elif ind and  not hasChild:
			string = '%s<%s>%s</%s>\n' % (indent, xmlstarttag, val, xmltag)
			return string
		
		else:	
			string = '<%s>%s</%s>\n' % (xmlstarttag, val, xmltag)
			return string  

	#parseCSV
	def parseCSV(self, aFile):
		f = open(aFile)
		lines = f.readlines()
		
		data = [] # leeres array
		for line in lines:
			splited = line.split(';')
			subdata = []
			for val in splited:
				val = val.strip()
				#if len(val) != 0:
				subdata.append(val)
			data.append(subdata)
		return data

	def crXML_header(self):
		return '<?xml version="1.0" encoding="UTF-8"?>\n'

	def crSETIstring(self, invoke, quantity, vap, bctype, plz, progno, date, time=0, weight=0, day=0):
		import string
		if invoke.lower() == 'bb':
			invoke = 2
		elif invoke.lower() == 'sb':
			invoke = 48

		if len(bctype) == 1:
			bctype = '0%s' % bctype

		if not time:
			time = '00'

		self.QUANTITY = self.QUANTITY + int(quantity)+1
		
		label_barcode = '%s%s%s%s' % (vap.upper(), bctype, plz, progno)

		first_container = int('100000000100000000') + self.QUANTITY 

		#mit induction_date
		#return 'cmd invoke %s Add_containers Quantity=%s Induction_point==WE00BB01.WG509 Label_barcode=%s000 First_container_Id=%s Induction_date=%sT08:%s:00 \n\n' % (invoke, quantity, label_barcode, first_container, date, time) 
		return 'cmd invoke %s Add_containers Quantity=%s Induction_point==WE00BB01.WG509 Label_barcode=%s000 First_container_Id=%s\n\n' % (invoke, quantity, label_barcode, first_container)
		

