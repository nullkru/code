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

function Utils.log(msg)
	local file = io.open("/tmp/log/cmh/VacationGhost.log", "a")
	ts = os.date('%c',os.time())
	file:write(ts..": "..msg.."\n")
	file:close()
	luup.log(msg)
end

function Utils.writeInfo(ghost)
	local file = io.open("/tmp/vg.info","w")
	local fileraw = io.open("/tmp/vgraw.info","w")
	local jsArr = '['
	local raw = ''
	for i=1,#ghost do
		jsArr = jsArr..'{"name":"'..ghost[i].name..'"},'..
			'{"start":"'..os.date('%X %x',ghost[i].startTs)..'"},'..
			'{"end":"'..os.date('%X %x',ghost[i].endTs)..'"}'
		raw = raw .. ghost[i]:info() .."\n"
	end
	jsArr = jsArr..']'
	file:write(jsArr)
	fileraw:write(raw)
	file:close()
	fileraw:close()
end

-- END Utils Class
