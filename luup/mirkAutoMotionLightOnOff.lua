
<<<<<<< HEAD

local SS_SID = "urn:micasaverde-com:serviceId:SecuritySensor1" -- Security Sensor Service ID
local SS_SP = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID -> mirkHauptDimmer
local SID_VS = "urn:upnp-org:serviceId:VSwitch1" -- Virtual Switch

local armed = luup.variable_get (SS_SID, "Armed", motionSens)
local autoScnIndicator = luup.variable_get("urn:upnp-org:serviceId:VSwitch1","Status",44)
local lightLevel = luup.variable_get("urn:micasaverde-com:serviceId:LightSensor1","CurrentLevel",lightSens) 
=======
local motionSens = 40 -- id  mirkMotionSensor
local roomLight = 34 -- id  mirkHauptDimmer
local lightSens = 41 -- id mirkLightSensor
local vSwitch = 44

local SID_SS = "urn:micasaverde-com:serviceId:SecuritySensor1" -- Security Sensor Service ID
local SID_SP = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID  mirkHauptDimmer
local SID_VS = "urn:upnp-org:serviceId:VSwitch1" -- Virtual Switch
local SID_LS = "urn:micasaverde-com:serviceId:LightSensor1"
>>>>>>> 67eea8beb4e8e877e77d88b34eac653c55c3ed02

dID = { motionSens=40, lightSensor=41, autoSceneIndicator=44, mainLight=34, greenLight=37, pultLight=35, bedLight=36 }

sID = { ss="urn:micasaverde-com:serviceId:SecuritySensor1", -- motionsensor
	sp="urn:upnp-org:serviceId:SwitchPower1",
	vs="urn:upnp-org:serviceId:VSwitch1",
	ls="urn:micasaverde-com:serviceId:LightSensor1" }

local armed = luup.variable_get(sID['ss'], "Armed", dID['motionSens'])
local autoScnIndicator = luup.variable_get(sID['vs'],"Status", dID['autoScnIndicator'])
local lightLevel = luup.variable_get(sID['ls'],"CurrentLevel",dID['lightSensor']) 

luup.log("mirkLog[i]: AutoMotionLightOnOff") 
<<<<<<< HEAD
if ((armed == "1") and ( 10 > tonumber(lightLevel) )) then
	local lightonA = luup.variable_get (SS_SIA, "Status", roomLight)
=======

if ((armed == "1") and ( 90 > tonumber(lightLevel) )) then

	local lightonA = luup.variable_get (sID['sp'], "Status", dID['mainLight'])
>>>>>>> 67eea8beb4e8e877e77d88b34eac653c55c3ed02

	local date = os.date('*t',os.time())
	local curTime = tonumber(date['hour']..date['min'])
  luup.log("mirkLog[i]: AutoMotionLightOnOff: start" .. curTime)
	if ( (lightonA == "0") and (curTime > 1500) and (curTime <= 2330) ) then
		luup.log("mirkLog[i]: Auto Motion Light ON ")
<<<<<<< HEAD
		luup.call_action(SS_SP, "SetTarget", {newTargetValue = "1"}, roomLight)	
		luup.call_action(SID_VS, "SetTarget", {newTargetValue = "1"}, 44)	
=======
		luup.call_action(sID['sp'], "SetTarget", {newTargetValue = "1"}, dID['mainLight'])	
		luup.call_action(sID['vs'], "SetTarget", {newTargetValue = "1"}, dID['autoSceneIndicator'])	
>>>>>>> 67eea8beb4e8e877e77d88b34eac653c55c3ed02
		pushMsg("action exectuted", "Auto+MotionLight+On")
		return true
	else
		luup.log("mirkLog[i]: Not triggered allready on or too late")
		pushMsg("sorry+too+late", "Auto+Light+On")
		return false
	end
end
 

