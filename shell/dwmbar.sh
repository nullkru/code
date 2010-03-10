#!/bin/bash

# display some stuff in dwm bar

function batinfo() {
	local bat0=$(acpi | awk '{ print $4 }' | sed 's/,//')
	local charg=$(acpi | awk '{ print $3 }' | sed 's/,//')

	if [[ "$charg" == "discharging" ]]; then 
		local stat=""
	else
		local stat="<c>"
	fi

	echo $stat$bat0
}

#time date
MPCINFO=$(mpctitle)
DATE=$(date "+%H:%M:%S %d.%m.%Y")
BAT0=BAT0:$(batinfo)
echo ${MPCINFO} \| ${BAT0} \| ${DATE} 
	



