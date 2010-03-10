#!/bin/bash -x
# by kru<@chao.ch> [http://chao.ch]
#date: 29.06.2006
#comment: localhack to switch between my xorg.confs

DIALOG=dialog

LIST=""
for i in $(ls /etc/X11/*.conf.*)
do
	ITEM=$(basename $i | sed -e 's/xorg.conf.//g' )
	LIST=$LIST" "$ITEM" "use_this 
done
LIST=$LIST
$DIALOG --menu "xorg.conf switcher" \
30 $COLUMNS 12  $LIST 2>/tmp/xcswitch


CONFNAME=$(cat /tmp/xcswitch)

sudo ln -sf /etc/X11/xorg.conf.$CONFNAME /etc/X11/xorg.conf
rm -rf /tmp/xcswitch
echo "DONE!"
