
dID = { motionSens=40, lightSensor=41, autoSceneIndicator=44, mainLight=34, greenLight=37, pultLight=35, bedLight=36 }
sID = { ss="urn:micasaverde-com:serviceId:SecuritySensor1", -- motionsensor
    sp="urn:upnp-org:serviceId:SwitchPower1",
    vs="urn:upnp-org:serviceId:VSwitch1",
    ls="urn:micasaverde-com:serviceId:LightSensor1" }


local period = 30 --minutes period since last sensor trip
local armed = luup.variable_get (sID['ss'], "Armed", dID['motionSens'])                                                                       
local autoScnIndicator = luup.variable_get(sID['vs'],"Status", dID['autoSceneIndicator'])

local c=0

if ((armed == "1") and (autoScnIndicator == "1")) then

	local lightID = { 34,35,36,37 }
	for i,id in pairs(lightID) do
		if (luup.variable_get(sID['sp'],"Status",id) == "1") then c=c+1 end
	end

    if ( c > 0 ) then
		
		local tripped = luup.variable_get(sID['ss'], "Tripped", dID['motionSens'])
		if ((tripped == "0")) then
			toggleSwitch(dID['autoSceneIndicator'], 0, "VSwitch1")
			luup.log("mirkLog[i]: mirAutoAllLightOff successfully executed")
			return true
		end
    end
else
	local lastTrip = luup.variable_get (sID['ss'], "LastTrip", dID['motionSens'])
	if((os.difftime (os.time(), lastTrip) / 60) >= period ) then
		luup.log("mirkLog[i]: mirAutoAllLightOff successfully executed lastTrip")
		return true
	end
end

return false


