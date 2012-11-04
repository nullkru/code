-- testing the class

require 'Ghost'
require 'TimeCalc'
-- calc times

tcO = TimeCalc.new("07:00", "23:00", 60, 10, 6)
timeTable = tcO:getTimes()

g = {}
for i,v in ipairs(timeTable) do
	g[i] = Ghost.new("HippieGspaengst"..i,23 , v[1], v[2],80)
	print(g[i]:info())
end

-- create new object
print("\n------>Static ghost")
gs = Ghost.new("HippiGspaengst",42,1351418657,1351425882,100 )
print(gs:info())
gs:resume()
print(gs:info())
gs:resume()



-- Utils
--
--
print("Utils tests:\n\n\n")
require('Utils')

tbl = {'ghost', 2, 3}
print(tbl[1], tbl[2],tbl[3])
tblN = {name="ghost", id=23}
print(tblN.name, tblN['id'])

if Utils.existsInTbl(tbl, tblN.name) then
	print(tblN['name'], tblN['id'])
end

print("before remove")
for k,v in ipairs(tbl) do print(k,v) end

Utils.tblRemove(tbl,"ghost")
Utils.tblRemove(tbl,3)

print("after remove")
for k,v in ipairs(tbl) do print(k,v) end
