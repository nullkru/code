#!/bin/bash

# original from: 2005 Erik Groeneveld, erik@cq2.nl
# It makes sure the fan is on in case of errors
# and only turns it off when all temps are ok.
# Recoded by  kru<@chao.ch> [http://chao.ch]
# date: 31.7.2007
#
# cat /proc/acpi/ibm/thermal description
# 1: CPU, 2: Between PCMCIA slot and CPU (same as HDAPS module)
# 3: PCMCIA, 4: GPU, 5: System Battery, 6: Ultrabay Bat
# 7: System Battery, 8: UltraBay bat
#

IBM_ACPI=/proc/acpi/ibm
THERMOMETER=$IBM_ACPI/thermal
FAN=$IBM_ACPI/fan
MAXTRIPPOINT=63
MINTRIPPOINT=58
HELLTRIPPOINT=66
TRIPPOINT=$MINTRIPPOINT
THERMALZONE="/proc/acpi/thermal_zone/THM0/temperature"
QUIET=1
FANLEVELLOW=0
FANLEVELHIGH=2

if [[ "$QUIET" == "0" ]];
then
	echo fancontrol: Thermometer: $THERMOMETER, Fan: $FAN
	echo fancontrol: Current `cat $THERMOMETER`
	echo fancontrol: Controlling temperatures between $MINTRIPPOINT and $MAXTRIPPOINT degrees.
fi

# Make sure the fan is turned on when the script crashes or is killed
trap "echo enable > $FAN; exit 0" HUP KILL INT ABRT STOP QUIT SEGV TERM

checktemp()
{
	command="level $FANLEVELHIGH"
	temperatures=$( sed s/temperatures:// < $THERMOMETER )
        
	#the result $var should be 6 for each thermal sensor +1 excluding the 128 values
	result=0
	for temp in $temperatures
	do
		if [[ "$temp" -le "$TRIPPOINT" && "$temp" -ne "-128" ]];
		then
			let result=$result+1
		fi
	done

	if [[ "$result" == "10" ]];
	then
		command="level 0"
		TRIPPOINT=$MINTRIPPOINT
	elif [[ "$result" == "4" || "$result" == "5" ]];
	then
		command="level 1"
		TRIPPONT=$MAXTRIPPOINT
	else
		#command="level auto"
		command="level $FANLEVELHIGH"
		TRIPPOINT=$MINTRIPPOINT
	fi

	if [[ "$QUIET" == "0" ]];
	then
		echo trippoint: $TRIPPOINT 
		echo result: $result
		echo command : $command
	fi
	echo -ne "$command" > $FAN
}

while [ 1 ];
do
	THERMALZONETEMP=$(cat $THERMALZONE | awk '{ print $2 }')
	GPUTEMP=$(cat $THERMOMETER | awk '{ print $5 }')
	if [[ "$THERMALZONETEMP" -le "$MAXTRIPPOINT" ]]; then
		echo -ne "level $FANLEVELLOW" > $FAN
		if [[ "$QUIET" == "0" ]];
		then
			echo "level $FANLEVELLOW temp: $THERMALZONETEMP"
		fi
	else
		#function from above
		checktemp
	fi
       	
	# Temperature ramps up quickly, so pick this not too large:
	sleep 5
done
