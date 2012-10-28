-- TimeCalc
--
--
require('Utils')
math.randomseed(os.time())	

startTime = "07:00"
endTime = "23:00"
onTime = 60
onTimeVariation = 10
onCycles = 5

--[[
 - phasen länge zwischen startTime endTime berechnen [ endTime - startTime ]
 - wie lange brennt licht berechnen (random(onTimeVariation) +/- onTime) [ for 1 bis onCycles : random(onTimeVariation) +/- onTime ]
 - gesammte on dauer [ onTime's summieren ]
 - restliche zeit berechngen = gesammte länge - on dauer. zeit für pausen berechenen [ gesammte zeitspanne - gesammte onTime ]
 - onCycles+1 = anzahl pausen 
 - restliche zeit auf pausen verteilen 
 - rest auf pausen verteillen [ 

]]



ts = os.time()
print("now:"..ts)

print(os.date('%c',ts))


startt = Utils.split(startTime, ":")
startTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=startt[1], min=startt[2] })
print("startTs:"..startTs)

endt = Utils.split(endTime, ":")
endTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=endt[1], min=endt[2] })
print("endTs:"..endTs)

onPhase = endTs - startTs


-- phasen berechnen wie lange licht brennt
onCycleTime = {}
for i=0,onCycles do
	if math.random(10) > 5 then
		table.insert(onCycleTime, ((onTime*60) - (math.random(0,onTimeVariation*60))))
	else
		table.insert(onCycleTime, ((onTime*60) + (math.random(0,onTimeVariation*60))))
	end
end

for i,v in ipairs(onCycleTime) do print("onCycleTime"..i,v) end

-- totale brenndauer
local totalOnTime=0
for i,v in ipairs(onCycleTime) do totalOnTime=totalOnTime+v end
print("total on time:" .. totalOnTime)

-- break times
totalBreakTime = onPhase - totalOnTime
print("totalBreakTime:".. totalBreakTime)

breakCycles = {}
for i=0,onCycles do
	local res = math.random(300,totalBreakTime)
	table.insert(breakCycles, res)
	totalBreakTime=(totalBreakTime-breakCycles[i+1])
end

for i,v in ipairs(breakCycles) do print("breakTimes"..i,v) end

-- final phase start - end calculations
gPhases = {}
for i=1,onCycles do
	-- start der phase
	if i == 1 then 
		gStart = startTs + breakCycles[i]
	else
		gStart = gPhases[i-1][2] + breakCycles[i]
	end

	local gStop = gStart + onCycleTime[i]

	table.insert(gPhases,{gStart,gStop})
end

for i,v in ipairs(gPhases) do
	print("start: "..os.date('%c',gPhases[i][1]) .. "   stop: "..os.date('%c',gPhases[i][2]))
	print("startts: "..gPhases[i][1] .. "   stopts: " .. gPhases[i][2])
end
