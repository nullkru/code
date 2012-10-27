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
function Ghost.new(name, ttl)
	local attr = {}

	attr.name = name
	attr.ttl = ttl
	-- hier weitere attribute 
	attr.cor = coroutine.create(Ghost.spook)

	setmetatable(attr,Ghost)
	return attr
end

function Ghost:info()
	print("coroutine:".. coroutine.status(self.cor)..", name="..self.name..", ttl="..self.ttl)
end

-- the spook function 
function Ghost.spook(name, ttl)
    print("--->" .. name .. " appeared (e.g: light on)")
    while ttl > 0  do  
        print("--->" .. name .. ": Boo! " .. ttl)
        ttl = ttl - 1 
        coroutine.yield()
    end 
    print("--->".. name .. ": is eliminated! (e.g: light off) ")
end

-- resumes the ghost coroutine
function Ghost:resume()
	coroutine.resume(self.cor, self.name, self.ttl)
end

-- return ghost status
function Ghost:status()
	return coroutine.status(self.cor)
end

-- END Class
