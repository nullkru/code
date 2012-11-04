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


function Utils.tblRemove(table, str)
	for i, name in ipair(table) do
		if name == str then
			table.remove(table, i)
			break
		end
	end
end

-- END Utils Class
