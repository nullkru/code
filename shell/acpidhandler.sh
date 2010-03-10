#!/bin/sh
# Default acpi script that takes an entry for all actions

# NOTE: This is a 2.6-centric script.  If you use 2.4.x, you'll have to
#       modify it to not use /sys

minspeed=`cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq`
maxspeed=`cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq`
setspeed="/sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed"

set $*

case "$1" in
	button/power)
		#echo "PowerButton pressed!">/dev/tty5
		case "$2" in
			PWRF)	logger "PowerButton pressed: $2" ;;
			*)    logger "ACPI action undefined: $2" ;;
		esac
		;;
	button/sleep)
		case "$2" in
			SLPB) echo -n mem >/sys/power/state ;;
			*)    logger "ACPI action undefined: $2" ;;
		esac
		;;
	ac_adapter)
		case "$2" in
			AC)
				case "$4" in
					00000000)
						echo -n $minspeed >$setspeed
						#/etc/laptop-mode/laptop-mode start
					;;
					00000001)
						echo -n $maxspeed >$setspeed
						#/etc/laptop-mode/laptop-mode stop
					;;
				esac
				;;
			*) logger "ACPI action undefined: $2" ;;
		esac
		;;
	battery)
		case "$2" in
			BAT0)
				case "$4" in
					00000000)	#echo "offline" >/dev/tty5
					;;
					00000001)	#echo "online"  >/dev/tty5
					;;
				esac
				;;
			CPU0)	
				;;
			*) logger "ACPI action undefined: $2" ;;
		esac
		;;
	
	#fn special keys
	ibm/hotkey)
		case "$4" in                                                           
	    		00001018)
            			echo "Power state manager"
        			urxvt -e /home/kru/bin/pm.py
        			;;
    			00001002)
				echo "screen lock"
				su kru -c slock
            			;;
			00001007)
				echo "kxsw executed"
				su kru -c /home/kru/bin/kxsw.sh
				;;
			*)
				echo "ibm Hotkey Else: $4"
				;;
		esac
		;;

	#display close action
	button/lid)
		#echo "LID switched!">/dev/tty5
		sh /home/kru/bin/lidsuspend.sh
		;;
	
	#brightness buttons
	video)
		case "$3" in
			00000087)
				echo "bright down"
				echo down > /proc/acpi/ibm/brightness
				;;
			00000086)
				echo "bright up"
				echo up > /proc/acpi/ibm/brightness
				;;
			*)
				echo "video Hotkey Else: $3"
				;;
		esac
		;;

	*)
		logger "ACPI group/action undefined: $1 / $2"
		;;
esac

