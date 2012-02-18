local period = 5 --minutes period since last sensor trip
local motionSens = 40 -- id -> mirkMotionSensor
local roomLight = 34 -- id -> mirkHauptDimmer
local lightSens = 41 -- id -> mirkLightSensor


local SS_SID = "urn:micasaverde-com:serviceId:SecuritySensor1" -- Security Sensor Service ID
local SS_SP = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID -> mirkHauptDimmer
local SID_VS = "urn:upnp-org:serviceId:VSwitch1" -- Virtual Switch

local armed = luup.variable_get (SS_SID, "Armed", motionSens)
local autoScnIndicator = luup.variable_get("urn:upnp-org:serviceId:VSwitch1","Status",44)
local lightLevel = luup.variable_get("urn:micasaverde-com:serviceId:LightSensor1","CurrentLevel",lightSens) 


function pushMsg(msg, event)
	local apikeys = { mirk="4e8d89d158b93fe85a7b5e5c4014c34ae9c0c78d" }
	--loop throug apikeys
	for k,v in pairs(apikeys) do
		luup.log("mirkLog[i] push MSG: " .. msg .. " event: " .. event .. " to: " .. k)
		luup.inet.wget("https://api.prowlapp.com/publicapi/add?apikey=" .. v .. "&application=Vera2&event=" .. event .. "&description=" .. msg .. "&priority=+1")
	end
end

luup.log("mirkLog[i]: AutoMotionLightOnOff") 
if ((armed == "1") and ( 10 > tonumber(lightLevel) )) then
	local lightonA = luup.variable_get (SS_SIA, "Status", roomLight)

	local date = os.date('*t',os.time())
	local curTime = tonumber(date['hour']..date['min'])

	if ( (lightonA == "0") and (curTime > 1500) and (curTime <= 2330) ) then
		luup.log("mirkLog[i]: Auto Motion Light ON ")
		luup.call_action(SS_SP, "SetTarget", {newTargetValue = "1"}, roomLight)	
		luup.call_action(SID_VS, "SetTarget", {newTargetValue = "1"}, 44)	
		pushMsg("action exectuted", "Auto+MotionLight+On")
		return true
	else
		luup.log("mirkLog[i]: Not triggered allready on or too late")
		pushMsg("sorry+too+late", "Auto+Light+On")
	end
end
 
return false
