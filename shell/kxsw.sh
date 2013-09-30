#!/bin/bash

#config
internaldev="LVDS1"
extdev="VGA1" #check xrandr for this name
placement="--right-of"
#placement="--above"
#mode="--mode 1280x1024" #resolution for second monitor
#mode="--mode 1024x768"
#mode="--mode 1920x1200"
mode="--auto"
#end config

#clone xrandr --output LVDS1 --auto --output VGA1 --auto --same-as LVDS1


vga0=$(xrandr | grep VGA | cut -f 2 -d " ")

if [[ "$vga0" == "connected" ]];
then
	checkres=$(xrandr | grep $extdev | cut -f 2 -d "+" -s)
	if [[ "$checkres" -ne "0" ]]; 
	then
		echo "Second monitor allready activated, exiting..."
		exit 0
	else
		echo "Activating second monitor right of $internaldev..."
		xrandr --output $extdev $mode $placement $internaldev
		#echo "restarting xfce panel"
		#xrandr --output LVDS1 --auto --output VGA1 --auto --same-as LVDS1
		xfce4-panel -r
		#nm-applet >& /dev/null &
	fi
else
	xrandr --output $extdev --off 
	echo "Second monitor is off..."
	#echo "restarting xfce4 panel..."
	xfce4-panel -r
	#nm-applet >& /dev/null &
fi
