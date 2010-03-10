#!/usr/bin/python

print "blah bleh"

principal = 1000 # anfangssumme
rate = 0.05 # zins
numyears = 5
year = 1

f = open("zinsen", "w")
while year <= numyears:
	principal = principal*(1+rate)
	f.write("%3d  %0.2f\n" % (year, principal))
	year = year + 1
f.close()


