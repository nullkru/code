

local lightID = { 84 }
local SID="urn:upnp-org:serviceId:SwitchPower1" 
local c=0
for i,id in pairs(lightID) do
	if (luup.variable_get(SID,"Status",lightID) == "1") then c=c+1 end
end

if ( c == #lightID ) then
	for i,id in pairs(lightID) do
		luup.call_action(SID, "SetTarget", {newTargetValue = "0"}, id)
	end
	return false
end
