--
-- Ghost Class
-- import require('Ghost')
math.randomseed(os.time())
Ghost = {}
Ghost.__index = Ghost

--[[
	Constructor  
	creates a new Ghost object
]]
function Ghost.new(name,lightId, startTs, endTs, dimLevel)
	local attr = {}

	attr.name = name
	attr.lightId = lightId
	attr.startTs = startTs
	attr.endTs = endTs
	attr.dimLevel = dimLevel
	if dimLevel == 0 then
		attr.dimLevel = math.random(0,100)
	end

	attr.cor = coroutine.create(Ghost.spook)

	setmetatable(attr,Ghost)
	return attr
end

function Ghost:info()
	return "status="..coroutine.status(self.cor)..", name="..self.name..", lightId="..self.lightId..", start="..os.date('%X %x',self.startTs)..", stop="..os.date('%X %x',self.endTs)..", dimLevel="..self.dimLevel
end

-- the spook function 
function Ghost.spook(name, startTs, endTs)
    --print("--->" .. name .. ": appeared (e.g: light on)")
    while startTs < os.time() and endTs > os.time()  do  
        print("--->" .. name .. ": Boo! ")
        coroutine.yield(name)
    end 
    --print("--->".. name .. ": is eliminated! (e.g: light off) ")
end

-- resumes the ghost coroutine
function Ghost:resume()
	coroutine.resume(self.cor, self.name, self.startTs, self.endTs)
end

-- return ghost status
function Ghost:status()
	return coroutine.status(self.cor)
end

-- END Class
