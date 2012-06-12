#!/bin/sh
clear
if [ -e /tmp/minicat ]; then
	echo "deleting folder minicat now, please wait..."
	rm -rf /tmp/minicat
fi

if [ ! -e /var/keys ]; then
	echo "creating keys now, please wait..."
	mkdir /var/keys
fi

if [ ! -e /var/scce ]; then
	echo "creating folder scce now, please wait..."
	mkdir /var/scce
fi

echo "downloading needet keys now, please wait..."
wget http://www.minicat.tv/Minicat_Keyfiles/minicat_keybundle.tar.gz -O /tmp/minicat.tar.gz 

echo "installing keys now, please wait..."
mkdir /tmp/minicat
tar -xzf /tmp/minicat.tar.gz -C /tmp/minicat/
rm -rf /var/keys/nagra_roms
mv -f /tmp/minicat/var/keys/* /var/keys/
mv -f /tmp/minicat/var/scce/* /var/scce/
cd /tmp
echo "deleting temporary files now..."
rm -rf /tmp/minicat/*
rm -rf /tmp/minicat
rm -rf /tmp/minicat.tar.gz
echo "key-update procedur finished"

KeyDate=$(/bin/date -r /var/keys/SoftCam.Key +%d.%m.%y-%H:%M:%S)

echo ""
echo "Date of the bundle: $KeyDate"
echo "Yeah may u have to roll one!"
echo ""
sleep 2
exit 0
