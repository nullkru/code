--
-- TimeCalc Class
--
require('Utils')
math.randomseed(os.time())	

--[[
startTime = "07:00"
endTime = "23:00"
onTime = 60
onTimeVariation = 10
onCycles = 5
]]
TimeCalc = {}
TimeCalc.__index = TimeCalc

function TimeCalc.new(startTime, endTime, onTime, onTimeVariation, onCycles, onProbability)
	local attr = {}

	attr.startTime = startTime
	attr.endTime = endTime
	attr.onTime = onTime * 60
	attr.onTimeVariation = onTimeVariation * 60
	attr.onCycles = onCycles
	attr.onProbability = onProbability

	-- Timestamps berechnen
	ts = os.time()
	startt = Utils.split(startTime, ":")
	startTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=startt[1], min=startt[2] })
	endt = Utils.split(endTime, ":")
	endTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=endt[1], min=endt[2] })

	attr.onPhase = endTs - startTs

	
	setmetatable(attr,TimeCalc)
	return attr
end

function TimeCalc:getTimes()
	-- tables für berechnungen
	onCycleTime = {}
	breakCycles = {}
	gPhases = {}

	--print("oncyc: " .. self.onCycles)
	while (self.onPhase - (self.onCycles * (self.onTime + 300 + self.onTimeVariation))) < 1 do
		self.onCycles=self.onCycles - 1
	end
	--print("oncyc after: " .. self.onCycles)

	-- phasen berechnen wie lange licht brennt
	for i=0,self.onCycles do
		if math.random(10) > 5 then
			table.insert(onCycleTime, ((self.onTime) - (math.random(0,self.onTimeVariation))))
		else
			table.insert(onCycleTime, ((self.onTime) + (math.random(0,self.onTimeVariation))))
		end
	end

	-- totale brenndauer
	totalOnTime=0
	for i,v in ipairs(onCycleTime) do totalOnTime=totalOnTime + v end

	-- break times
	totalBreakTime = self.onPhase - totalOnTime - (self.onCycles*300)
	for i=0,self.onCycles do
		if totalBreakTime < 300 then totalBreakTime=300 end
		local res = math.random(300,totalBreakTime)
		table.insert(breakCycles, res)
		totalBreakTime=totalBreakTime-breakCycles[i+1]
	end

	-- final phase start - end calculations
	for i=1,self.onCycles do
		if i == 1 then 
			gStart = startTs + breakCycles[i]
		else
			gStart = gPhases[i-1][2] + breakCycles[i]
		end

		local gStop = gStart + onCycleTime[i]
		table.insert(gPhases,{gStart,gStop})
	end
	
	return gPhases
end

function TimeCalc.showTimes(gPhases)
	for i,v in ipairs(gPhases) do
		print("start: "..os.date('%c',gPhases[i][1]) .. "   stop: "..os.date('%c',gPhases[i][2]))
		print("startts: "..gPhases[i][1] .. "   stopts: " .. gPhases[i][2])
	end
end

-- END TimeCalc
