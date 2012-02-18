dID = { motionSens=40, lightSensor=41, autoSceneIndicator=44, mainLight=34, greenLight=37, pultLight=35, bedLight=36 }
sID = { ss="urn:micasaverde-com:serviceId:SecuritySensor1", -- motionsensor
	sp="urn:upnp-org:serviceId:SwitchPower1",
	vs="urn:upnp-org:serviceId:VSwitch1",
	ls="urn:micasaverde-com:serviceId:LightSensor1" }

local armed = luup.variable_get(sID['ss'], "Armed", dID['motionSens'])
local autoScnIndicator = luup.variable_get(sID['vs'],"Status", dID['autoScnIndicator'])
local lightLevel = luup.variable_get(sID['ls'],"CurrentLevel",dID['lightSensor']) 

luup.log("mirkLog[i]: AutoMotionLightOnOff") 

if ((armed == "1") and ( 90 > tonumber(lightLevel) )) then

	local lightonA = luup.variable_get (sID['sp'], "Status", dID['mainLight'])

	local date = os.date('*t',os.time())
	local curTime = tonumber(date['hour']..date['min'])
  luup.log("mirkLog[i]: AutoMotionLightOnOff: start" .. curTime)
	if ( (lightonA == "0") and (curTime > 1500) and (curTime <= 2330) ) then
		luup.log("mirkLog[i]: Auto Motion Light ON ")
		luup.call_action(sID['sp'], "SetTarget", {newTargetValue = "1"}, dID['mainLight'])	
		luup.call_action(sID['vs'], "SetTarget", {newTargetValue = "1"}, dID['autoSceneIndicator'])	
		pushMsg("action exectuted", "Auto+MotionLight+On")
		return true
	else
		luup.log("mirkLog[i]: Not triggered allready on or too late")
		pushMsg("sorry+too+late", "Auto+Light+On")
		return false
	end
end
 

