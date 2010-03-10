#!/usr/bin/python
#-*- coding: UTF-8 -*-

import postmail, sys, os, string, time
pm = postmail.postmail()

if len(sys.argv) < 2:
	print "Ordner Name angeben"
else:

	grunddaten = pm.parseCSV(sys.argv[1]+'/planday_grunddaten.csv')
	mapcontent = pm.parseCSV(sys.argv[1]+'/input_map.csv')
	vakdaten = pm.parseCSV(sys.argv[1]+'/input_VAK.csv')
	plandaydaten = pm.parseCSV(sys.argv[1]+'/planday_TimeRow.csv')
	sd = pm.parseCSV(sys.argv[1]+'/input_SETI.csv')
	
	
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
	TransportBlockCont =pm.crTag('TIMESTAMP', 'ArrivalTime', 0, 1)
	TransportBlockCont += pm.crTag('Transport', 'ID', 0, 1)

	TransportBlock = pm.crTag(grunddaten[1][0], 'PLZ', 0, 1 )
	TransportBlock += pm.crTag(TransportBlockCont + AmountBlock, 'Transport', 0, 1, 1) 
	bzBlock = pm.crTag(TransportBlock, 'BZ', 0, 1, 1) 

	apl_map = pm.crTag(bzBlock, 'APL_MAP', 'xmlns="http://www.post.ch/ids/apl" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.post.ch/ids/apl APL_MAP.xsd"', 0,1) 


	#open map xmlfile and write it
	f = open(sys.argv[1]+'/map_'+grunddaten[1][1]+'.xml',"a") 
	f.write("%s" % (pm.crXML_header()))
	f.write('%s' % (apl_map))
	f.close()
	print "MAP writen..."


	###################################------>VAK
	

	#<Announcement>

	AnnouncementContent = 	pm.crTag('AAA', 'VAP', 0,1)
	AnnouncementContent +=	pm.crTag(grunddaten[1][0] + '%s', 'Destination',0,1) % vakdaten[1][0]
	AnnouncementContent +=	pm.crTag(grunddaten[1][1] + 'T06:00:00', 'captureDate', 0,1)
	AnnouncementContent += 	pm.crTag('false', 'missedIZV', 0, 1)
	AnnouncementContent +=	pm.crTag(vakdaten[1][1], 'Counter', 0,1)

	Announcement = pm.crTag(AnnouncementContent, 'Announcement', 0, 1,1)

	PostCode = pm.crTag(grunddaten[1][0], 'Postcode', 0,1)

	Announcements = pm.crTag(PostCode + Announcement, 'Announcements','xsi:schemaLocation="http://www.post.ch/ids/apl PPS_Announcement.xsd" xmlns="http://www.post.ch/ids/apl" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"',0,1)


	#open map xmlfile and write it
	f = open(sys.argv[1]+'/VAK_'+grunddaten[1][1]+'.xml',"a") 
	f.write("%s" % (pm.crXML_header()))
	f.write('%s' % (Announcements))
	f.close()
	print "VAK writen..."

	#################################--------> planday
	





	#<Attributes>

	Attributes =	pm.crTag('', 'Name',0,1)
	Attributes +=	pm.crTag(grunddaten[1][5], 'Throughput',0,1)
	Attributes +=	pm.crTag(grunddaten[1][6], 'ThroughputInwardSorting',0,1)
	Attributes +=	pm.crTag(grunddaten[1][7], 'ThroughputOutwardSorting',0,1)

	AttributesBlock = pm.crTag(Attributes, 'Attributes',0,1,1)

	#<TimeRow>
	i=1
	TimeRow = ''
	while i <= 48:
		TimeRowContent =	pm.crTag(plandaydaten[i][1], 'Intervall', 0, 1)
		TimeRowContent +=	pm.crTag(plandaydaten[i][2], 'FunctionPlaceCount',0,1)
		TimeRowContent +=	pm.crTag(plandaydaten[i][3], 'AvailableFpCount', 0,1)

		TimeRow += pm.crTag(TimeRowContent, 'TimeRow',0,1,1)
		i+=1


	#<FunctionPlaceType>
	FunctionPlaceBlock = pm.crTag(AttributesBlock + TimeRow, 'FunctionPlaceType', 0,1,1)


	#<WorkingArea>

	WorkingAreaNames = ['AB400', 'AB410', 'AB420', 'AB430']
	MAXFpCount = {'AB400':'10', 'AB410':'76', 'AB420':'8', 'AB430':'36'}
	WorkingAreaBlock = '' 
	for name in WorkingAreaNames:
		WorkingAreaContent =	pm.crTag(name, 'Name', 0, 1)
		WorkingAreaContent +=	pm.crTag(MAXFpCount[name], 'MaxFpCount', 0, 1)

		WorkingAreaBlock +=	pm.crTag(WorkingAreaContent + FunctionPlaceBlock, 'WorkingArea',0,1,1)

	#PlanDay * 7
	Date = grunddaten[1][1]
	dateVal = Date.split('-')
	PlanDayBlock = ''
	
	if not dateVal[0]:
		now = time.localtime(time.time())
		dateVal[0] = time.strftime("%Y", now)
		dateVal[1] = time.strftime("%m", now)
		dateVal[2] = time.strftime("%d", now)

	pdDate='%s-%s-%s' % (dateVal[0],dateVal[1], dateVal[2])

	i=1
	while i <= 7:
		PlanDayBlockContent = 	pm.crTag(pdDate, 'Date', 0,1)
		PlanDayBlockContent +=	pm.crTag(grunddaten[1][2].lower(), 'WorkingDay', 0,1)

		PlanDayBlock += pm.crTag(PlanDayBlockContent + WorkingAreaBlock, 'PlanDay',0,1,1)
		day = (int(dateVal[2])+i)
		if len('%s') % day == 1: #len('')-1
			day = '0%s' % day
		pdDate='%s-%s-%s' % (dateVal[0], dateVal[1], day)
		i+=1


	plz = pm.crTag(grunddaten[1][0], 'PLZ', 0,1)
	bzBlock = pm.crTag(plz + PlanDayBlock, 'BZ', 0, 1,1) 


	apl_plantage = pm.crTag(bzBlock, 'APL_Plantage', 'xmlns="http://www.post.ch/ids/apl" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.post.ch/ids/apl APL_Plantage.xsd"',0,1)

	#open map xmlfile and write it
	f = open(sys.argv[1]+'/planday_'+grunddaten[1][1]+'.xml',"a")
	f.write("%s" % (pm.crXML_header()))
	f.write('%s' % (apl_plantage))
	f.close()
	print "Planday xml writen..."



	####################################---------------->SETI



	i=1
	arrSize = len(sd)-1
	setiDaten = ''
	while i <= arrSize:
		invoke = sd[i][0]
		quantity = sd[i][1]
		vap = sd[i][2]
		bctype = sd[i][3]
		plz = sd[i][4]
		progno = sd[i][5]
		date = grunddaten[1][1]
		setiDaten += pm.crSETIstring(invoke, quantity, vap, bctype, plz, progno, date)
		i+=1

	f = open(sys.argv[1]+'/SETIdaten_'+grunddaten[1][1]+'.txt',"a") 
	f.write('%s' % (setiDaten))
	f.close()
	print "SETI writen..."
	print "%s finished" % sys.argv[1]
