
startTime = "18:00"
endTime = "23:00"
onTime = 60
onTimeVariation = 10
onCycles = 3

--[[
 - phasen länge zwischen startTime endTime berechnen [ endTime - startTime ]
 - wie lange brennt licht berechnen (random(onTimeVariation) +/- onTime) [ for 1 bis onCycles : random(onTimeVariation) +/- onTime ]
 - gesammte on dauer [ onTime's summieren ]
 - restliche zeit berechngen = gesammte länge - on dauer. zeit für pausen berechenen [ gesammte zeitspanne - gesammte onTime ]
 - onCycles+1 = anzahl pausen 
 - restliche zeit auf pausen verteilen 
 - rest auf pausen verteillen [ 

]]



