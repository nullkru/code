-- testing the class

require 'Ghost'
require 'TimeCalc'

-- calc times

tcO = TimeCalc.new("07:00", "23:00", 60, 10, 6)
timeTable = tcO:getTimes()

g = {}
for i,v in ipairs(timeTable) do
	g[i] = Ghost.new("HippieGspaengst"..i, v[1], v[2],80)
	g[i]:info()
end

-- create new object
print("\n------>Static ghost")
gs = Ghost.new("HippiGspaengst",1351418657,1351425882 )
gs:info()
gs:resume()
gs:info()
gs:resume()
