#!/usr/bin/python
#-*- encoding: UTF-8 -*-

import postmail
pm = postmail.postmail()

grunddaten = pm.parseCSV('daten/Test_8a_28_03_2008/planday_grunddaten.csv')
plandaydaten = pm.parseCSV('daten/Test_8a_28_03_2008/planday_TimeRow.csv')



#<Attributes>

Attributes =	pm.crTag('', 'Name',0,1)
Attributes +=	pm.crTag(grunddaten[1][5], 'Troughput',0,1)
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
WorkingAreaBlock = '' 
for name in WorkingAreaNames:
	WorkingAreaContent =	pm.crTag(name, 'Name', 0, 1)
	WorkingAreaContent +=	pm.crTag('10', 'MaxFpCount', 0, 1)

	WorkingAreaBlock +=	pm.crTag(WorkingAreaContent + FunctionPlaceBlock, 'WorkingArea',0,1,1)

#PlanDay * 7
Date = grunddaten[1][1]
dateVal = Date.split('-')
PlanDayBlock = ''
pdDate='%s-%s-%s' % (dateVal[0],dateVal[1], dateVal[2])

i=1
while i <= 7:
	PlanDayBlockContent = 	pm.crTag(pdDate, 'Date', 0,1)
	PlanDayBlockContent +=	pm.crTag(grunddaten[1][2], 'WorkingDay', 0,1)

	PlanDayBlock += pm.crTag(PlanDayBlockContent + WorkingAreaBlock, 'PlanDay',0,1,1)
	day = (int(dateVal[2])+i)
	if len('%s')-1 % day == 1:
		day = '0%s' % day
	pdDate='%s-%s-%s' % (dateVal[0], dateVal[1], day)
	i+=1


plz = pm.crTag(grunddaten[1][0], 'PLZ', 0,1)
bzBlock = pm.crTag(plz + PlanDayBlock, 'BZ', 0, 1,1) 


apl_plantage = pm.crTag(bzBlock, 'APL_Plantage', 'xmlns="http://www.post.ch/ids/apl" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.post.ch/ids/apl APL_Plantage.xsd"',0,1)

#open map xmlfile and write it
f = open('planday.xml',"a")
f.write("%s" % (pm.crXML_header()))
f.write('%s' % (apl_plantage))
f.close()
print "Planday xml writen..."
