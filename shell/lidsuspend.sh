#!/bin/bash

. /home/kru/.kruconf

lockfile='/tmp/lidclose'

trap "rm -rf $lockfile" HUP KILL INT ABRT STOP QUIT SEGV TERM

batstate=x$(grep 'discharging' /proc/acpi/battery/BAT0/state | awk '{print $3}')

if [[ $LIDSUSPEND == '1' && "$batstate" != 'x' ]];
then
	if [[ ! -e "$lockfile" ]];
	then 
		touch $lockfile
		
		sleep $LIDTIMEOUT
		
		lidstatus=$(cat /proc/acpi/button/lid/LID/state | awk '{ print $2 }')
		if [[ -e "$lockfile" && "$lidstatus" != 'open' ]];
		then
			rm -rf $lockfile
			batcharge=$(acpi | awk '{ print $4 }' | sed 's/,//' | sed 's/%//')
			if [ $batcharge => 15 ];
		       	then
			       pm-hibernate
		       else	       
			pm-suspend
		fi
			#echo "suspend" 
		else
			echo "lid is open remove $lockfile"
			rm -rf $lockfile
		fi
	fi
else
	echo "lid suspend is off"
fi
