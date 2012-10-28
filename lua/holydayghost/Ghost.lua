--
-- Ghost Class
-- import require('Ghost')

Ghost = {}
Ghost.__index = Ghost

--[[
	Constructor  
	creates a new Ghost object
	e.g: geist = Ghost.new(name, ttl)	
]]
function Ghost.new(name, startTs, endTs)
	local attr = {}

	attr.name = name
	attr.startTs = startTs
	attr.endTs = endTs

	attr.ttl = ttl
	-- hier weitere attribute 
	attr.cor = coroutine.create(Ghost.spook)

	setmetatable(attr,Ghost)
	return attr
end

function Ghost:info()
	print("coroutine:".. coroutine.status(self.cor)..", name="..self.name..", start="..os.date('%c',self.startTs)..", stop="..os.date('%c',self.endTs))
end

-- the spook function 
function Ghost.spook(name, startTs, endTs)
    print("--->" .. name .. ": appeared (e.g: light on)")
    while startTs < os.time() and endTs > os.time()  do  
        print("--->" .. name .. ": Boo! ")
        coroutine.yield()
    end 
    print("--->".. name .. ": is eliminated! (e.g: light off) ")
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
