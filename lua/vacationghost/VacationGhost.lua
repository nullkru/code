-- Vacation Ghost Plugin for Vera

-- import der klassen
require("VGhostGhost") -- Ghost.
require("VGhostUtils") -- Utils.
require("VGhostTimeCalc") -- TimeCalc.

-- Globale Variablen

sid = "urn:upnp-org:serviceId:VGhost1"
ghost = {} -- table for created ghosts
status = {} -- currently running ghosts
cemetery = {} -- dead ghosts

-- main function
function main(lul_device)
	
	vgPluginId = tonumber(lul_device)
	Utils.clearLog(vgPluginId)
	Utils.log(vgPluginId,"VGinfo: Calling main loop with lul_device: " .. vgPluginId)

	-- start der phase: auslesen der vars
	onOff = luup.variable_get(sid,"OnOff", vgPluginId)
	if tonumber(onOff) == 1 then
		status = {}
		cemetery = {}
		ghost = {}

		for row=1,8 do
			-- Daten aus web interface abfragen
			lightId = luup.variable_get(sid,"LightID" ..row, vgPluginId)
			timeStart = luup.variable_get(sid,"TimeStart" ..row, vgPluginId)
			timeStop = luup.variable_get(sid,"TimeStop" ..row, vgPluginId)
			onTime = luup.variable_get(sid,"OnTime" ..row, vgPluginId)
			onVariation = luup.variable_get(sid,"OnVariation" ..row, vgPluginId)
			onPropability = luup.variable_get(sid,"OnPropability" ..row, vgPluginId) 
			dimLevel = luup.variable_get(sid,"DimLevel" ..row, vgPluginId)
			onCycle  = luup.variable_get(sid,"OnCycle" ..row, vgPluginId)

			-- Zeiten für Geister berechnen
			calcTimes = TimeCalc.new(timeStart,timeStop,tonumber(onTime),tonumber(onVariation),tonumber(onCycle),tonumber(onPropability))
			times = calcTimes:getTimes()
			
			-- create ghosts and push to ghost array
			for t=1,#times do
				if not (os.time() > times[t][2]) and tonumber(lightId) > 0 then
					g = Ghost.new("Ghost"..row..t..#times, tonumber(lightId), times[t][1],times[t][2],tonumber(dimLevel))
					table.insert(ghost, g)
				end
			end
		end

		-- abfragen der isNight() variable
		cbNight = luup.variable_get(sid,"Night",vgPluginId)
		run = true
		if tonumber(cbNight) > 0 then 
			if not luup.is_night() then run = false end
		end 

		-- informationen der Geister anzeigen
		if #ghost > 0 and run then
			for n=1,#ghost do
				Utils.log(vgPluginId,"VGinitPhase: "..ghost[n]:info())
			end
			Utils.writeJson(vgPluginId,ghost)
			Utils.genUIinfos(vgPluginId,ghost)
			luup.variable_set(sid,"State",50,tonumber(lul_device))
			-- phase aufrufen
			phase(lul_device)
		else
			Utils.log(vgPluginId,"VGinitPhase: no more Ghosts for today")
			luup.call_timer("main", 1, 10, "", vgPluginId)
		end

	else
		Utils.log(vgPluginId,"VGinitPhase: VacationGhost is disabled, sleep and start over")
		Utils.clearJson(vgPluginId)
		luup.variable_set(sid,"State",0,tonumber(lul_device))
		luup.call_timer("main", 1, 10, "", lul_device)
	end
end

function phase(lul_device)
	local vgPluginId = lul_device
	-- abarbeiten der phase
	curTs = os.time()

	Utils.log(vgPluginId,"VGdebug: total ghosts: "..#ghost)
	Utils.log(vgPluginId,"VGdebug: running ghosts: "..#status)
	Utils.log(vgPluginId,"VGdebug: ghosts in cemetery: "..#cemetery)

	for i=1,#ghost do
		if curTs > ghost[i].startTs then

			ghost[i]:resume()
			
			-- cleanup unused but generated ghosts : startTs < curTs
			if ghost[i]:status() == "dead" and not Utils.existsInTbl(status,ghost[i].name) and not Utils.existsInTbl(cemetery,ghost[i].name) then
				--luup.log("VGinfo: Not used Ghost:" .. ghost[i].name)
				table.insert(cemetery, ghost[i].name) 

			elseif ghost[i]:status() ~= "dead" then
				
				if not Utils.existsInTbl(status,ghost[i].name) then
					Utils.log(vgPluginId,"VGaction: Light ON ".. ghost[i]:info())
					--luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = ghost[i].dimLevel}, ghost[i].lightId)
					Utils.switchDev(ghost[i].lightId, ghost[i].dimLevel)
					table.insert(status, ghost[i].name)
				end
			end

			if curTs > ghost[i].endTs and not Utils.existsInTbl(cemetery, ghost[i].name) then
				Utils.log(vgPluginId,"VGaction: Light Off:"..ghost[i]:info())
				--luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = 0}, ghost[i].lightId)
				Utils.switchDev(ghost[i].lightId, 0)

				if Utils.existsInTbl(status,ghost[i].name) then 
					Utils.tblRemove(status, ghost[i].name) 
					table.insert(cemetery, ghost[i].name)
					Utils.log(vgPluginId,"VGinfo: moved ghost to cemetery:" .. ghost[i].name)
				end
			end
		end
	end
	-- phase end or re-rune
	if #ghost == #cemetery then
		Utils.log(vgPluginId,"VGinfo: Phase ended recalculation ghost times and starting over.")
		luup.variable_set(sid,"State",0,tonumber(lul_device))
		main(lul_device)
	else
		recalc = 0
		recalc = luup.variable_get(sid,"Changes", tonumber(lul_device))
		if tonumber(recalc) > 0 then 
			luup.log("VGinfo: need to recalculate ghost times.")
			luup.variable_set(sid,"Changes",0,tonumber(lul_device))
			main(lul_device)
		else
			if #status > 0 then
				luup.variable_set(sid,"State",100,tonumber(lul_device))
			else
				luup.variable_set(sid,"State",50,tonumber(lul_device))
			end
			luup.call_timer("phase", 1, 10, '',lul_device)
		end
	end
end
