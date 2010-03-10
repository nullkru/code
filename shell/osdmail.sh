#!/bin/bash
names=(craphead biatch siffbire prick)

_osd='osd_cat -A center -o 500 -c green -f -*-terminus-bold-*-normal-*-32-*-*-*-*-*-*-*'
RND=$RANDOM%${#names[@]}
echo "Hey ${names[RND]}, you've got mail ($1 new)" | $_osd
