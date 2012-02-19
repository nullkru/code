
switchStatus=0

function toggleSwitch(devID, newstatus, serviceID)
	if(serviceID == nil) then
		serviceID = "SwitchPower1"
	end
	if(newstatus == nil) then
		switchStatus = luup.variable_get("urn:upnp-org:serviceId:"..serviceID, "Status", devID)
		if(tonumber(switchStatus) == 1) then
			switchStatus=0
		else
			switchStatus=1
		end
	else
		switchStatus = newstatus
	end
	luup.log("mirkLog[i] switchToggle("..devID..", ".. switchStatus.. ", "..serviceID..")") 
	luup.call_action("urn:upnp-org:serviceId:"..serviceID, "SetTarget", {newTargetValue = ""..switchStatus..""}, devID)
end

toggleSwitch(44, nil, "VSwitch1")
