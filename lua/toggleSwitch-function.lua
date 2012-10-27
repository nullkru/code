
switchStatus=0

-- toggleSwitch(41, status or nil, serviceId eg: "VSwitch1" or "SecuritySensor1" empty for defaul)
function toggleSwitch(devID, newstatus, serviceID)
	local command = "Status"
	if(serviceID == nil) then
		serviceID = "urn:upnp-org:serviceId:SwitchPower1"
	elseif(serviceID == "urn:micasaverde-com:serviceId:SecuritySensor1") then
		command = "Armed"
	end

	if(newstatus == nil) then
		switchStatus = luup.variable_get(serviceID, command, devID)
		if(tonumber(switchStatus) == 1) then
			switchStatus=0
		else
			switchStatus=1
		end
	else
		switchStatus = newstatus
	end
	luup.log("mirkLog[i] switchToggle("..devID..", ".. switchStatus.. ", "..serviceID..")") 
	if(command == "Armed") then
		--luup.variable_set(serviceID, command, switchStatus, devID)
		luup.call_action(serviceID, "SetArmed", {newArmedValue = ""..switchStatus..""}, devID)
	else
		luup.call_action(serviceID, "SetTarget", {newTargetValue = ""..switchStatus..""}, devID)
	end
end
-- END toggleSwitch

toggleSwitch(44, nil, "VSwitch1")
