#!/bin/bash

SOCKETDIR="/tmp/screens/S-$USER"
D=dialog
TMPFILE="/tmp/kscr.tmp"

num=0
for i in $(ls --color=no $SOCKETDIR); 
do
	((num++))
	item_list=$item_list" "$i" "$num
done

#create menu point add session

rm -rf $TMPFILE
$D --menu "get your screen back..." 20 $COLUMNS 12  $item_list 2>$TMPFILE
if [[ $(cat $TMPFILE) == "" ]];
then
	exit
else
	screen -x $(cat $TMPFILE)
fi
