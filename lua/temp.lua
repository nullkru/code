local lightID = { 34,35,36,37 }
local SID="urn:upnp-org:serviceId:SwitchPower1" 
local c=0
for i,id in pairs(lightID) do
    if (luup.variable_get(SID,"Status",id) == "1") then c=c+1 end
end

if ( c > 0 ) then
    for i,id in pairs(lightID) do
        luup.call_action(SID, "SetTarget", {newTargetValue = "0"}, id)
    end
    return false
end  


		luup.call_action("urn:upnp-org:serviceId:SwitchPower1", "SetTarget", {newTargetValue = "1"}, 34)	
		
		luup.call_action("urn:upnp-org:serviceId:SwitchPower1", "SetTarget", {newTargetValue = "1"}, 44)	

