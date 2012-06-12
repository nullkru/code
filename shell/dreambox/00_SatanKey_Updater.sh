#!/bin/sh
clear
if [ -e /tmp/satan ]; then
	echo "deleting folder satan now, please wait..."
	rm -rf /tmp/satan
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
wget http://cori.homeip.net -O /tmp/satan.tar.gz
echo "installing keys now, please wait..."
mkdir /tmp/satan
tar -xzf /tmp/satan.tar.gz -C /tmp/satan/
rm -rf /var/keys/nagra_roms
mv -f /tmp/satan/var/keys/* /var/keys/
mv -f /tmp/satan/var/scce/* /var/scce/
cd /tmp
echo "deleting temporary files now..."
rm -rf /tmp/satan/*
rm -rf /tmp/satan
rm -rf /tmp/satan.tar.gz

echo "key-update procedur finished, HAVE FUN NOW..."

KeyDate=`/bin/date -r /var/keys/SoftCam.Key +%d.%m.%y-%H:%M:%S`

echo ""
echo "Date of the bundle: $KeyDate"
echo "Yeah may you should roll one!"
echo ""
sleep 2
exit 0
