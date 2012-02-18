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


