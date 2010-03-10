#!/bin/bash


## TODO
# - help
# - get infos
# - verbose mode
# - web gui :P
# - get group sed 's/^[0-9]\+_\([0-9]*\)_\?.*\+$/\1/'


SAVEPATH="/mnt/data/kloader"
TEMP="$SAVEPATH/tmp"
LOADSPATH="$HOME/.kloader/"
OLDLOADS="$HOME/.kloader/old/"
OLDLOG="$HOME/.kloader/old/$(date +%d.%m.%Y-)_leechedlog.txt"
LOGFILE="$HOME/.kloader/kloader.log"
MOZCOOKIE="/home/kru/temp/cookies.txt"
DEFAULTSPEED="50k"
RETRY="5"
VERBOSE=1
CRAWLINTERVAL=5
osdcommand="osd_cat -A center -p middle -f -*-*-*-*-*-*-32-*-*-*-*-*-*-* -d 3"

function nextNumber()
{
	local numFiles=$(ls -A $LOADSPATH | wc -l )
	local numFiles2=$(ls -A $OLDLOADS | wc -l)
	local nextNum=$(($numFiles+$numFiles2))

	while [[ -e $LOADSPATH/${nextNum}_load || -e $OLDLOADS/${nextNum}_load ]]
	do
		nextNum=$(($nextNum+1))
	done

	echo $nextNum
}

function showInfo()
{
	local curfile=$(ls $LOADSPATH | head -n 1)
	
	if [[  "$curfile" != "old" ]];
	then
		local curleech=$(cat $LOADSPATH/$(basename $curfile))
		echo Currently leeching: $(basename $curleech)
		echo In Queue: $(($(ls $LOADSPATH | wc -l)-2))
	else
		echo $(basename $0) is idling... dumdidum 
	fi

}


function addUrlToQueue()
{
	local file=$(echo $@ | sed s/-a//g)
	echo $file > $LOADSPATH/$(nextNumber;)_load
}

function add_fileContentToQueue()
{
	local file=$1
	i=0
	for line in $(cat $file);
	do
		echo $line > $LOADSPATH/$(nextNumber;)_load
		((i++))	
	done

	echo Added $i new links to leech!
}

function addMultiUrlToQueue()
{
		
	local string=$(echo $@ | sed s/-m//g)

	local range=$(echo $string | cut -d \[ -f 2 | cut -d \] -f 1)
	local firstelement=$(echo $string | cut -d \[ -f 1)
	local secondelement=$(echo $string | cut -d \] -f 2)

	echo range:$range

	local startrange=$(echo $range | cut -d \- -f 1)
	local stoprange=$(echo $range | cut -d \- -f 2)

	for (( i= $startrange ; i <= $stoprange; i++ ))
	{
		local file="$LOADSPATH/$(nextNumber;)_load"
		echo $firstelement$i$secondelement >> $file
	}
}

function getFile()
{
	if [[ $SPEED -eq "K" ]];
	then
		SPEED=$DEFAULTSPEED
	fi

	echo ======================Leeching with: $SPEED
	WGET="wget -T 15 -c -P $TEMP --tries $RETRY --limit-rate=$SPEED --load-cookies=$MOZCOOKIE"
	local GETFILE=$1
	local LOADTHIS=$(cat $GETFILE)
	
	if [ "$LOADTHIS" == "" ]; 
	then
		rm -rf $GETFILE
		echo empty _load file deleted!
	else
		$($WGET $LOADTHIS)
		if [ $? == 0 ];
		then
			local leeched=$(cat $GETFILE | xargs basename)
			mv $TEMP/$leeched $SAVEPATH
			#mv $GETFILE  $OLDLOADS
			cat $GETFILE >> $OLDLOG
			rm -rf $GETFILE

			echo kloader: $GETFILE dloaded. in queue  $(($(ls $LOADSPATH | wc -l)-2)) | $osdcommand
		else
			echo "=================>ou fuck terminated!!!"
		#	addUrlToQueue $LOADTHIS
		#	rm -rf $GETFILE
		fi
	fi
}

function crawlDir()
{
	for i in $(ls $LOADSPATH | grep -v old | line); 
	do 
		currdate=$(date)
		echo $currdate $LOADSPATH$i
		getFile $LOADSPATH$i
	done
}

function clean_loaddir
{
	echo "Clean kloader dirs (y)?"
	read a
	if [[ "$a" == "y" ]]; then
		
		rm -rf $LOADSPATH/*_load
		rm -rf $OLDLOADS/*
	
		find $SAVEPATH -size -6k | xargs rm -f
		echo Cleaned!
	fi
}

function logpw()
{
	if [[ "$1" == "-" ]];
	then
		vim $OLDLOADS/pwstorage.txt
	else
		echo $1 >> $OLDLOADS/pwstorage.txt
	fi
}


function run_daemon() 
{
	while [ 1 ]; 
	do
		crawlDir
		sleep $CRAWLINTERVAL
	done
}

	while getopts "damcif:s:p:" opt;
	do
		case $opt in
			s) SPEED=${OPTARG}K;;
			d) run_daemon ;;
			a) addUrlToQueue $@ ;;
			m) addMultiUrlToQueue $@ ;;
			c) clean_loaddir ;;
			i) showInfo ;;
			f) add_fileContentToQueue $OPTARG ;;
			p) logpw $OPTARG ;;
		   	-) OPTIND=0
				break
				;;	
		esac
	done
