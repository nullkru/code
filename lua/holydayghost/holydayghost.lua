-- import der klassen

require("Ghost")

function sleep(timeout)
	os.execute("sleep " .. timeout)
end


-- 3 Geister erzeugen
ghost = {}
for i=1,3 do
	ghost[i] = Ghost.new("ghost" .. i, 5-math.random(3)+math.random(3))
end


-- informationen der Geister anzeigen
for i=1,#ghost do
	ghost[i]:info()	
end

print("Starting main loop\n\n")
-- main loop

run = true
while run do

	for i=1,#ghost do
		ghost[i]:resume()
	end

	for i=1,#ghost do
		ghost[i]:info()	
		--print(ghost[i]:status())
	end

	c = #ghost
	for i=1,#ghost do
		if ghost[i]:status() == "dead" then		
			c = c-1
		end
	end

	if c == 0 then
		run = false
	else
		sleep(3)
	end
end
