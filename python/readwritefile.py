#!/usr/bin/python

trenner = '*=*=*=*=*=*==*=*=*=*=*=*=*=*'
file = 'bleh.csv'

#txt auslesen
f = open(file)

line = f.readlines()
print 'Inhalt von:' + file

laenge = len(line)

print laenge

while line:
	if line == 0:
		print 'datei ist leer'
	else:
		print line,
		line = f.readlines()

print 'so jetz mal was reinschreiben'

f.close()

writeme = raw_input("write>")

f = open(file, "a")

f.write("%s \n" % (writeme))
f.close()



