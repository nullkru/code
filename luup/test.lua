--[[
-- nil == null in java,c,usw...
-- ]]

print("miau")

t = {"miau",
	"blah", -- comment
	"uff",w="blah"}

print("t table:" ..  t[2] ..  t[3])

test = true

if test then
	print ("haha" , t[1])
	print(t['w'])
end

if ((3 < 4) and (test == true)) then
	print("yeah")
end


curSeconds = os.date('*t',os.time())["hour"] * 3600 + os.date('*t',os.time())["min"] * 60

local times = { startH=16,startM=30,endH=23,endM=30}
minSeconds =  times['startH'] * 3600 + times['startM'] * 60
maxSeconds = times['endH'] * 3600 + times['endM'] * 60

if((curSeconds > minSeconds) and (curSeconds <= maxSeconds) ) then
	print("yay")
end
