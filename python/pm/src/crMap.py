#!/usr/bin/python
# -*- coding: UTF-8 -*-

import postmail

csvFile = 'daten/Test_8a_28_03_2008/input_map.csv'

pm = postmail.postmail()

mapcontent = pm.parseCSV(csvFile)

grunddaten = pm.parseCSV('daten/Test_8a_28_03_2008/planday_grunddaten.csv')



#<Amount>
arrAmount = ['AAA', 'BAA', 'EAA', 'FAA']
i = 2
AmountBlock = ''
for amount in arrAmount:
	AmountBlockCont = pm.crTag(amount, 'Vap', 0, 1)
	AmountBlockCont += pm.crTag(mapcontent[1][i], 'Count',0, 1)
	AmountBlock += pm.crTag(AmountBlockCont, 'Amount',0,0,1)
	i+=1

#<Transport>
TransportBlockCont = pm.crTag('Transport', 'ID', 0, 1)
TransportBlockCont +=pm.crTag('TIMESTAMP', 'ArrivalTime', 0, 1)

TransportBlock = pm.crTag(grunddaten[1][0], 'PLZ', 0, 1 )
TransportBlock += pm.crTag(TransportBlockCont + AmountBlock, 'Transport', 0, 1, 1) 
bzBlock = pm.crTag(TransportBlock, 'BZ', 0, 1, 1) 

apl_map = pm.crTag(bzBlock, 'APL_MAP', 'xmlns="http://www.post.ch/ids/apl" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.post.ch/ids/apl APL_MAP.xsd"', 0,1) 


#open map xmlfile and write it
f = open('map.xml',"a")
f.write("%s" % (pm.crXML_header()))
f.write('%s' % (apl_map))
f.close()
print "MAP writen..."

