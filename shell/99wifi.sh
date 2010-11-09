#!/bin/bash
# /etc/NetworkManager/dispatcher.d/99wifi.sh
# run specific shell funtions on network join
# all functions are saved in shell.functions file and named <ESSID>_action
# and takes the parameters $1 up/down
#chao.ch_action() {
#    if [[ "$1" == "up" ]]; then
#        runaskru "sshfs cube:/mnt/tera/multimedia/ /mnt/cube/multimedia"
#    fi
#    if [[ "$1" == "down" ]]; then
#        fusermount -uz /mnt/cube/multimedia
#    fi
#}


. /etc/profile
. /home/kru/bin/shell.functions

IF=$1
STATUS=$2
logfile=/var/log/nm-dispatcher

wait_for_process() {
  PNAME=$1
  PID=$(/usr/bin/pgrep $PNAME)

  while [ -z "$PID" ]; do
        sleep 3;
        PID=$(/usr/bin/pgrep $PNAME)
  done
}

logthis() {
	echo "$(date): $@" >> $logfile
}

wait_for_connection() {
	state=unavailable
	while [[ "$state" != "connected" ]]; do
		state=$(nm-tool | grep -A3 $IF | awk '/State/ { print $2 }')
		sleep 1
	done
}

logthis $@

#wifi scripts
if [ "$IF" = "wlan0" ]; then
	curEssid=$(cat /tmp/essid 2> /dev/null)
	if [ -z "$curEssid"  ]; then
		logthis "Waiting for connection..."
		wait_for_connection
		ESSID=$(iwconfig $IF | sed -r -n '/SSID/{s/.*SSID:"([^"]+)".*/\1/g;p;q}')
		echo $ESSID > /tmp/essid
	else
		ESSID=$(cat /tmp/essid)
		rm /tmp/essid
	fi

	eval ${ESSID}_action $STATUS
	logthis "called ${ESSID}_action $STATUS"
fi
