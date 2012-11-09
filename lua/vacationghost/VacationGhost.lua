-- Vacation Ghost Plugin for Vera


-- import der klassen
require("VGhostGhost") -- Ghost.
require("VGhostUtils") -- Utils.
require("VGhostTimeCalc") -- TimeCalc.

-- Globale Variablen

sid = "urn:upnp-org:serviceId:VGhost1"


-- main function
ghost = {}
function main(lul_device)

	lul_device = tonumber(lul_device)
	luup.log("VGinfo: Calling main loop with lul_device: " .. lul_device)

	-- start der phase: auslesen der vars
	onOff = luup.variable_get(sid,"OnOff", lul_device)
	if tonumber(onOff) == 1 then
		for row=1,8 do
			lightId = luup.variable_get(sid,"LightID" ..row, lul_device)
			timeStart = luup.variable_get(sid,"TimeStart" ..row, lul_device)
			timeStop = luup.variable_get(sid,"TimeStop" ..row, lul_device)
			onTime = luup.variable_get(sid,"OnTime" ..row, lul_device)
			onVariation = luup.variable_get(sid,"OnVariation" ..row, lul_device)
			onPropability = luup.variable_get(sid,"OnPropability" ..row, lul_device) 
			dimLevel = luup.variable_get(sid,"DimLevel" ..row, lul_device)
			onCycle  = luup.variable_get(sid,"OnCycle" ..row, lul_device)


			-- Zeiten für Geister berechnen
			calcTimes = TimeCalc.new(timeStart,timeStop,tonumber(onTime),tonumber(onVariation),tonumber(onCycle),tonumber(onPropability))
			times = calcTimes:getTimes()

			for t=1,#times do
				curTs = os.time()
				if not (curTs > times[t][1]) and not (curTs > times[t][2]) then
					g = Ghost.new("Ghost"..row..t..#times, tonumber(lightId), times[t][1],times[t][2],tonumber(dimLevel))
					table.insert(ghost, g)
				end
			end
		end

		-- informationen der Geister anzeigen
		if not #ghost == 0 then
			for n=1,#ghost do
				luup.log("VGinitPhase: "..ghost[n]:info())
			end
			-- phase aufrufen
			phase(lul_device)
		else
			luup.log("VGinitPhase: no more Ghosts for today")
			luup.call_timer("main", 1, 10, "", lul_device)
		end

	else
		luup.log("VGinitPhase: VacationGhost is disabled, sleep and start over")
		luup.call_timer("main", 1, 10, "", lul_device)
	end
end


function phase(lul_device)
	-- abarbeiten der phase
	status = {} -- currently running ghosts
	cemetery = {} -- dead ghosts

	luup.log("VGdebug: total ghosts: "..#ghost)
	luup.log("VGdebug: running ghosts: "..#status)
	luup.log("VGdebug: ghosts in cemetery: "..#cemetery)

	curTs = os.time()
	for i=1,#ghost do
		if curTs > ghost[i].startTs then

			ghost[i]:resume()
			
			-- cleanup unused but generated ghosts : startTs < curTs
			if ghost[i]:status() == "dead" and not Utils.existsInTbl(status,ghost[i].name) and not Utils.existsInTbl(cemetery,ghost[i].name) then
				--luup.log("VGinfo: Not used Ghost:" .. ghost[i].name)
				table.insert(cemetery, ghost[i].name) 

			elseif ghost[i]:status() ~= "dead" then
				
				if not Utils.existsInTbl(status,ghost[i].name) then
					luup.log("VGaction: Light ON ".. ghost[i]:info())
					luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = ghost[i].dimLevel}, ghost[i].lightId)
					table.insert(status, ghost[i].name)
				end
			end

			if curTs > ghost[i].endTs and not Utils.existsInTbl(cemetery, ghost[i].name) then

				luup.log("VGaction: Light Off:"..ghost[i]:info())
				luup.call_action("urn:upnp-org:serviceId:Dimming1", "SetLoadLevelTarget", {newLoadlevelTarget = 0}, ghost[i].lightId)

				if Utils.existsInTbl(status,ghost[i].name) then 
					Utils.tblRemove(status, ghost[i].name) 
					table.insert(cemetery, ghost[i].name)
					luup.log("VGinfo: moved ghost to cemetery:" .. ghost[i].name)
				end

			end
		end


		-- beenden der phase
		if #ghost == #cemetery then
			luup.log("VGinfo: Phase ended recalculation ghost times and starting over.")
			main(lul_device)
		else
			luup.call_timer("phase", 1, 10, "", lul_device)
		end

	end
end
