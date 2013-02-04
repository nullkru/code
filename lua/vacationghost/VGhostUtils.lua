--
-- Utils Class
-- import require('Utils')

Utils = {}
Utils.__index = Utils

math.randomseed(os.time())

-- Split string into table 
-- param s: string
-- param re: delmiter
function Utils.split(s,re)
    local i1 = 1 
    local ls = {}
    local append = table.insert
    if not re then re = '%s+' end 
    if re == '' then return {s} end 
    while true do
        local i2,i3 = s:find(re,i1)
        if not i2 then
            local last = s:sub(i1)
            if last ~= '' then append(ls,last) end 
            if #ls == 1 and ls[1] == '' then
                return {}
            else
                return ls
            end 
        end 
        append(ls,s:sub(i1,i2-1))
        i1 = i3+1
    end 
end

function Utils.sleep(timeout)
	os.execute("sleep " .. timeout)
end

function Utils.existsInTbl(table, str)
	local status = false
	for i, name in ipairs(table) do
		if name == str then 
			status = true
			break
		end
	end
	return status
end


function Utils.tblRemove(tbl, str)
	for i,name in ipairs(tbl) do
		if name == str then
			table.remove(tbl, i)
			break
		end
	end
end

function Utils.genUIinfos(lul_device,ghost) 
	local fileName = "/www/cmh/VacationGhost.id"..lul_device..".log"
	local file = io.open(fileName, "w")
	local str = ''
	for i=1,#ghost do
		str = str .. ghost[i]:info()	
		file:write(ghost[i]:info())
	end
	file:close()
	return str
end	

function Utils.log(lul_device,msg)
	local fileName = "/www/cmh/VacationGhost.id"..lul_device..".log"
	--local file = io.open(fileName, "a")
	ts = os.date('%c',os.time())
	--file:write(ts..": "..msg.."\n")
	--file:close()
	luup.log(msg)
end

function Utils.clearLog(lul_device)
	-- remove this on next release
	os.execute("rm -rf /www/cmh/VGhostInfo.log ; rm -rf /www/cmh/VacationGhost.info.txt ; rm -rf /www/cmh/VacationGhost.log")

	local fileName = "/www/cmh/VacationGhost.id"..lul_device..".log"
	local file = io.open(fileName, "w")
	ts = os.date('%X %x',os.time())
	file:write(ts.." New Phase \n")
	file:close()
end


function Utils.writeJson(lul_device,ghost)
	--local file = io.open("/tmp/VGhostInfo.json","w")
	local fileName = "/www/cmh/VGhostInfo.id"..lul_device..".json"
	local file = io.open(fileName,"w")
	local jsArr = '['
	for i=1,#ghost do
		endchar = "},"
		if i == #ghost then
			endchar	= "}"
		end
		jsArr = jsArr..'{"name":"'..ghost[i].name..'",'..
			'"lightId":"'..ghost[i].lightId..'",'..
			'"dimLevel":"'..ghost[i].dimLevel..'",'..
			'"start":"'..ghost[i].startTs..'",'..
			'"end":"'..ghost[i].endTs..'",'..
			'"date":"'..ghost[i].endTs..'"'.. endchar

	end
	jsArr = jsArr..']'
	file:write(jsArr)
	file:close()
end

function Utils.clearJson(lul_device)
	--local file = io.open("/tmp/VGhostInfo.json","w")
	-- remove this on next release
	os.execute("rm -rf /www/cmh/VGhostInfo.json")
	--
	local fileName = "/www/cmh/VGhostInfo.id"..lul_device..".json"
	local file = io.open(fileName,"w")
	file:write("")
	file:close()
end

function Utils.switchDev(id, value)
	local type = luup.devices[id].device_type

	if type == "urn:schemas-upnp-org:device:DimmableLight:1" then
		luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = value}, id)
	elseif type == "urn:schemas-upnp-org:device:BinaryLight:1" then
		if value > 0 then
			value = 1
		end
		luup.call_action("urn:upnp-org:serviceId:SwitchPower1","SetTarget", {newTargetValue = value}, id)
	else
		luup.log("VGinfo: Device type not supported. Please report deatails on forum.micasaverde.com. Details: " .. type )
	end
end
-- END Utils Class
