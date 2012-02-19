function toggleSwitch(devID)
	print(devID)
end

-- dimmrCtl(37, "up" or "down" or 50 or nil, {25, 50, 75, 0} or nil)
function dimmerCtl(devID, loadLevel, dimStepsTbl)
	local dimSteps = {10,25,50,70}
	if(dimStepsTbl ~= nil) then
		dimSteps = dimStepsTbl
	end
	local curLvl = luup.variable_get("urn:upnp-org:serviceId:Dimming1", "LoadLevelStatus", devID)
	--local curLvl = 100

	if(tonumber(loadLevel) == nil) then
		if(loadLevel == "up") then
			local i=1
			while(curLvl <= dimSteps[i] and i <= #dimSteps) do
				i=(i+1)
			end
			newLvl = dimSteps[i]
			if(newLvl < dimSteps[#dimSteps]) then 
				toggleSwitch(devID)
				newLvl=0
			end
		else 
			local i=#dimSteps
			while(curLvl >= dimSteps[i] and (i <= 1)) do
				i=(i-1)
			end
			newLvl = dimSteps[i]
			if(newLvl <= dimSteps[1]) then 
				toggleSwitch(devID)
				newLvl=0
			end
		end
	else
		newLvl = loadLevel
	end
	--print("mirkLog[i]: dimmerCtl(".. devID ..", ".. newLvl ..") was: " .. curLvl )
	luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = "".. newLvl ..""}, devID)
	luup.log("mirkLog[i]: dimmerCtl(".. devID ..", ".. newLvl ..") was:" ..curLvl)
end
-- END dimmerCtl



dimmerCtl(40,"up")

dimmerCtl(45,"down")

dimmerCtl(23)

