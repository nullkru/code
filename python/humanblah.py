#!/usr/bin/python

blah = [3,4,1,5,2,6,8,44,44,2]
anz = len(blah)-1
stapel = anz
while stapel is not 0:
	linkehand = blah[stapel]    #oberster zettel von stapel
	rechtehand = blah[stapel-1] #naechster zettel von stapel
	if linkehand > rechtehand :
		tisch = linkehand                                                                                                                              
		linkehand = rechtehand
		rechtehand = tisch
		stapel -= 1
	else:
		tisch = linkehand
		linkehand = rechtehand
		rechtehand = tisch
		stapel = anz
print blah

