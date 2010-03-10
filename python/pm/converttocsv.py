# -*- coding: UTF-8 -*-
import sys, win32com.client, os

def convertXLS2CSV(aFile): 
	'''converts a MS Excel file to csv w/ the same name in the same directory'''

	print "------ beginning to convert XLS to CSV ------"

	try:
		excel = win32com.client.Dispatch('Excel.Application')

		fileDir, fileName = os.path.split(aFile)
		
		nameOnly = os.path.splitext(fileName)
		#newName = nameOnly[0] + ".csv"
		
		workbook = excel.Workbooks.Open(aFile)
		#hardcoded sheetnames
		excelsheets = ['planday_TimeRow', 'planday_grunddaten', \
		'input_SETI', 'input_map', 'input_VAK']
		os.mkdir(fileDir + '\\' + nameOnly[0])
		for actSheet in excelsheets:
			excel.sheets(actSheet).select #sheet auswählen
			csvname = excel.ActiveSheet.name + '.csv'
			outCSV = os.path.join(fileDir + '\\' + nameOnly[0], csvname)
			workbook.SaveAs(outCSV, FileFormat=24) # 24 represents xlCSVMSDOS
			print "...Converted sheet to " + csvname 
		
		workbook.Close(False)
		excel.Quit()
		del excel
		print 'Finished converting: %s' % aFile

	except:
		print ">>>>>>> FAILED to convert " + aFile + " to CSV!"


if len(sys.argv) < 2:
	print 'Datei name angeben'
else:
	filetoconvert = sys.argv[1]
	path = os.getcwd() + '\\'
	convertXLS2CSV(path + filetoconvert)
