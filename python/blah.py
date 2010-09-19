#!/usr/bin/python

blah = [3,4,2,5]
anz = len(blah)-1
n = anz
while n is not 0 :
	print "%d > %d" % (blah[n],blah[n-1])
	if blah[n] > blah[n-1] :
		z = blah[n]
		blah[n] = blah[n-1]
		blah[n-1] = z
		n = anz
	else:
		n-=1
	print blah
