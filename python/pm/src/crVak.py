#!/usr/bin/python
#-*- coding: UTF-8 -*-

import postmail
pm = postmail.postmail()

grunddaten = pm.parseCSV('daten/Test_8a_28_03_2008/planday_grunddaten.csv')
vakdaten = pm.parseCSV('daten/Test_8a_28_03_2008/input_VAK.csv')

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
f = open('vak.xml',"a")
f.write("%s" % (pm.crXML_header()))
f.write('%s' % (Announcements))
f.close()
print "VAK writen..."

