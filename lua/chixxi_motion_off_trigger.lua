local period = 5 --minutes period since last sensor trip
local deviceNo = 8 --deviceid
local deviceNoA = 5 --deviceid Light A
local deviceNoB = 6 --deviceid Light B
local deviceNoC = 7 --deviceid Light C

 
local SS_SID = "urn:micasaverde-com:serviceId:SecuritySensor1" -- Security Sensor Service ID
local SS_SIA = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID Light A
local SS_SIB = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID Light B
local SS_SIC = "urn:upnp-org:serviceId:SwitchPower1" -- Lamp Sensor Service ID Light C
 
local armed = luup.variable_get (SS_SID, "Armed", deviceNo)
	local skip = luup.variable_get("urn:upnp-org:serviceId:VSwitch1","Status",75)

if ((armed == "1") and (skip == "1")) then
	local lightonA = luup.variable_get (SS_SIA, "Status", deviceNoA)
	local lightonB = luup.variable_get (SS_SIB, "Status", deviceNoB)
	local lightonC = luup.variable_get (SS_SIC, "Status", deviceNoC)
	if ((lightonA == "1") or (lightonB == "1") or (lightonC == "1")) then
	   local lastTrip = luup.variable_get (SS_SID, "LastTrip", deviceNo) or os.time()
	   lastTrip = tonumber (lastTrip)
           lastCalc = (os.difftime (os.time(), lastTrip) / 60)
           luup.log("Value of Variable lastTrip: " .. lastTrip)
           luup.log("Value of Variable lastCalc: " .. lastCalc)
	   	if ((os.difftime (os.time(), lastTrip) / 60) >= period) then
			return true
	   	end
	end
end
 
return false
