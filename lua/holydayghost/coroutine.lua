-- funktion zum erzeugen der geister

function spook(name, ttl)
	print("--->"..name .. " appeared (e.g: light on)")
	while ttl > 0  do
		print("--->".. name .. ": Boo! " .. ttl)
		ttl = ttl - 1
		coroutine.yield()
	end
	print("--->"..name .. ": is eliminated! (e.g: light off ")
end


function sleep(timeout)
	os.execute("sleep " .. timeout)
end


-- 3 Geister erzeugen
ghost = {}
for i=1,4 do
	ghost[i] = { cr = coroutine.create(spook), name="ghost" .. i, ttl=5-math.random(3)+math.random(3) }
end


-- informationen der Geister anzeigen
for i=1,#ghost do
	print("ghost["..i.."] = { cr = " .. coroutine.status(ghost[i]['cr']) .. ", name=".. ghost[i]['name'] ..", ttl="..ghost[i]['ttl'].."}")
end

print("Starting main loop\n\n")
-- main loop

run = true
while run do

	for i=1,#ghost do
		coroutine.resume(ghost[i]['cr'], ghost[i]['name'], ghost[i]['ttl'] )
		print("status: " .. ghost[i]['name'] .. " " .. coroutine.status(ghost[i]['cr']))
	end

	c = #ghost
	for i=1,#ghost do
		if coroutine.status(ghost[i]['cr']) == "dead" then		
			c = c-1
		end
	end

	if c == 0 then
		run = false
	end
	sleep(3)
end
