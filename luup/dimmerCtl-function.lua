function toggleSwitch(devID)
	print(devID)
end

luup = {}
function luup.variable_get(a,b,c)
	return 30
end
function luup.call_action(a,b,c,d)
	--print("luu.call_action: " .. abcd)
end
function luup.log(a)
	print(a)
end

-- dimmrCtl(37, "up" or "down" or 50 or nil, {25, 50, 75, 0} or nil)
function dimmerCtl(devID, loadLevel, dimStepsTbl)
	if(dimStepsTbl == nil) then
		dimSteps = {10,25,50,70}
	else
		dimSteps = dimStepsTbl
	end
	local curLvl = luup.variable_get("urn:upnp-org:serviceId:Dimming1", "LoadLevelStatus", devID)

	if(tonumber(loadLevel) == nil) then
		curLvl = tonumber(curLvl) or 0
		if(loadLevel == "down" or loadLevel == nil) then 
			local i=#dimSteps
			while(curLvl <= dimSteps[i] and (i > 1)) do
				i=(i-1)
			end
			newLvl = dimSteps[i]
			if(curLvl == 0) then
				luup.log("dimStep")
				dimmerCtl(devID,dimSteps[#dimSteps])
			elseif(curLvl <= dimSteps[1]) then 
				toggleSwitch(devID)
				newLvl=0
			end
		elseif(loadLevel == "up") then
			local i=1
			while(curLvl >= dimSteps[i] and i <= #dimSteps) do
				i=(i+1)
			end
			newLvl = dimSteps[i]
			if(newLvl > dimSteps[#dimSteps]) then 
				toggleSwitch(devID)
				newLvl=0
			end
		end
	else
		newLvl = loadLevel
	end
	luup.log("mirkLog[i]: dimmerCtl(".. devID ..", ".. newLvl ..") was:" ..curLvl)
	luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = "".. newLvl ..""}, devID)
end
-- END dimmerCtl

dimmerCtl(50,"up")
dimmerCtl(51,"down")
dimmerCtl(52)
dimmerCtl(53,80)


