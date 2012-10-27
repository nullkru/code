-- VirtualContainer functions
-- setVCvar() set a variable 
function setVCvar(devID, varN, msg)
	if(msg	== nil)then msg=0 end
	luup.variable_set("urn:upnp-org:serviceId:VContainer1", "Variable"..varN, msg, devID)
	luup.log("mirkLog[i] setVCvar("..devID..", Variable"..varN..", ".. msg..")")
end
-- getVCvar() get variable vom VirtualContainer
function getVCvar(devID, varN)
	local var = luup.variable_get("urn:upnp-org:serviceId:VContainer1", "Variable"..varN, devID)
	luup.log("mirkLog[i] getVCvar("..devID..", Variable"..varN..") is:" .. var)
	return var
end
-- END VirtualContainer functions
