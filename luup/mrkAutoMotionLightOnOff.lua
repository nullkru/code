dID = { motionSens=40, lightSensor=41, autoSceneIndicator=44, mainLight=34, greenLight=37, pultLight=35, bedLight=36 }
sID = { ss="urn:micasaverde-com:serviceId:SecuritySensor1", -- motionsensor
	sp="urn:upnp-org:serviceId:SwitchPower1",
	vs="urn:upnp-org:serviceId:VSwitch1",
	ls="urn:micasaverde-com:serviceId:LightSensor1" }

local times = { startH=16,startM=30,endH=23,endM=55}

local armed = luup.variable_get(sID['ss'], "Armed", dID['motionSens'])
local autoScnIndicator = luup.variable_get(sID['vs'],"Status", dID['autoScnIndicator'])
local lightLevel = luup.variable_get(sID['ls'],"CurrentLevel",dID['lightSensor']) 

luup.log("mirkLog[i]: AutoMotionLightOn Triggered") 

if ((armed == "1") and ( 90 > tonumber(lightLevel) )) then

	local lightonA = luup.variable_get (sID['sp'], "Status", dID['mainLight'])

	curSeconds = os.date('*t',os.time())["hour"] * 3600 + os.date('*t',os.time())["min"] * 60
	minSeconds =  times['startH'] * 3600 + times['startM'] * 60
	maxSeconds = times['endH'] * 3600 + times['endM'] * 60

	if ( (lightonA == "0") and (curSeconds > minSeconds) and (curSeconds <= maxSeconds) ) then
		-- licht an
		toggleSwitch(dID['mainLight'], 1, nil)
		dimmerCtl(dID['pultLight'], 40)
		-- scenen indikator auf an
		toggleSwitch(dID['autoSceneIndicator'], 1, "VSwitch1")
		setVCvar(51,1,"AutoMotionOn")
		pushMsg("Main+Light+On", "AutoMotionOn", "mirk")
		return true
	else
		luup.log("mirkLog[i]: Not triggered allready on or too late")
		return false
	end
end
 

