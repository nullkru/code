--
-- TimeCalc Class
--
require('VGhostUtils')
--Utils = VGhostUtils
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

function TimeCalc.new(startTime, endTime, onTime, onTimeVariation, onCycles, onPropability)
	local attr = {}

	attr.startTime = startTime
	attr.endTime = endTime
	attr.onTime = onTime * 60
	attr.onTimeVariation = onTimeVariation * 60
	attr.onCycles = onCycles
	attr.onPropability = onPropability

	-- Timestamps berechnen
	ts = os.time()
	startt = Utils.split(startTime, ":")
	startTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=startt[1], min=startt[2] })
	endt = Utils.split(endTime, ":")
	endTs = os.time({year=os.date('%Y',ts), month=os.date('%m',ts), day=os.date('%d',ts), hour=endt[1], min=endt[2] })
	
	-- miternacht handling
	if(endTs > startTs) then
		attr.onPhase = endTs - startTs
	else
		attr.onPhase = (endTs + 86400) - startTs
	end

	setmetatable(attr,TimeCalc)
	return attr
end

function TimeCalc:getTimes()
	-- tables für berechnungen
	onCycleTime = {}
	breakCycles = {}
	gPhases = {}
	minBreak = 60 

	-- on cycles berechnen 
	while (self.onPhase - (self.onCycles * (self.onTime + minBreak + self.onTimeVariation))) < 1 do
		self.onCycles=self.onCycles - 1
	end

	-- phasen berechnen wie lange licht brennt
	for i=0,self.onCycles do
		if self.onTimeVariation > 0 then
			if math.random(10) > 5 then
				-- abfangen zu grosser onTimeVariation werten
				calcTime = ((self.onTime) - (math.random(1,self.onTimeVariation)))
				if calcTime > 1 then
					table.insert(onCycleTime, calcTime)
				else
					table.insert(onCycleTime, 0)
				end

			else
				table.insert(onCycleTime, ((self.onTime) + (math.random(1,self.onTimeVariation))))
			end
		else
			table.insert(onCycleTime, self.onTime)
		end
	end

	-- totale brenndauer
	totalOnTime=0
	for i,v in ipairs(onCycleTime) do totalOnTime=totalOnTime + v end

	-- break times
	totalBreakTime = self.onPhase - totalOnTime - (self.onCycles * minBreak)
	for i=0,self.onCycles do
		
		if totalBreakTime < minBreak then totalBreakTime=minBreak end

		local res = math.random(minBreak,totalBreakTime)
		table.insert(breakCycles, res)
		totalBreakTime=totalBreakTime-breakCycles[i+1]
	end

	-- final phase start - end calculations -> number of ghosts
	for i=1,self.onCycles do
		--if math.random(100) <= tonumber(self.onPropability) then
			if i == 1 then 
				gStart = startTs + breakCycles[i]
			else
				gStart = gPhases[i-1][2] + breakCycles[i]
			end

			local gStop = gStart + onCycleTime[i]
			if gStop ~= gStart then
				table.insert(gPhases,{gStart,gStop})
		--	end
			else
				table.insert(gPhases,{0,0})
			end
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
