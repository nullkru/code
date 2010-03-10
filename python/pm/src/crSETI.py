#!/usr/bin/python
# -*- coding: UTF-8 -*-
import postmail
pm = postmail.postmail()

grunddaten = pm.parseCSV('daten/Test_8a_28_03_2008/planday_grunddaten.csv')
sd = pm.parseCSV('daten/Test_8a_28_03_2008/input_SETI.csv')

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

print setiDaten
