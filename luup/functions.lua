-- Send push message to all or custom reciver
-- send to all devices: use param ALL 
-- usage: pushMsg("licht+an", "Haupt+Licht", "mirk")

apikeys = { mirk="4e8d89d158b93fe85a7b5e5c4014c34ae9c0c78d", chix="256627a0492771c7aa76fdd8c15ca2992f509b1a" }


function pushMsg(msg, event, reciver)                                          
	if ( reciver ~= "ALL" ) then 
		luup.log("mirkLog[i] push MSG: " .. msg .. " event: " .. event .. " to: " .. reciver .. "=".. apikeys[reciver])
		luup.inet.wget("https://api.prowlapp.com/publicapi/add?apikey=" .. apikeys[reciver] .. "&application=Vera2&event=" .. event .. "&description=" .. msg .. "&priority=+1")
	else 
		--loop throug apikeys
		for k,v in pairs(apikeys) do
			-- print(msg .. "event: " .. event .. " to: " .. k .. " apikey" .. v )
			luup.log("mirkLog[i] push MSG: " .. msg .. " event: " .. event .. " to: " .. k)
			luup.inet.wget("https://api.prowlapp.com/publicapi/add?apikey=" .. v .. "&application=Vera2&event=" .. event .. "&description=" .. msg .. "&priority=+1")
		end
	end
end


pushMsg("miau", "reciver = ALL", "ALL")

pushMsg("an mirk", "reciver spezifisch", "chix")

