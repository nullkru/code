#!/bin/bash
# 28.1.2013 Mirko Messer
#

# Functions 
function usage(){
cat <<EOF
Usage: $0 [OPTIONS...] -d <destination>

	-s SRC		use this as source dir (Default: $HOME)
	-d DST		use this as destination dir
	-t 			try run - shows what would be backuped
	-e FILE		exclude files/patterns according to this file (See rsync man page for more info)
	-l <Current full backup dir>	use this directory to create hardlinks for unchanged files. (This saves time and space)
	-n			ignore config file
	-h			this help text

You can also use a config file in your user home named .backthisup.conf syntax:

source="/boot /etc /home/kru"
destination="/media/datasd/data/backups/"
linkdest=$destination/current
excludefile=/home/kru/.kbackupexclude
rsyncopt=" --delete-excluded "
#postcmd="eg: mv  $backupdir blah  "

EOF
exit 0
}

function printConf() {
	echo "running $0 with the following arguments"
	echo "source: ${SRC}"
   	echo "destination: ${DST}"
	echo "exclude file: ${EXCLUDEFILE}"
	echo "full path and backup name: $backup"
	echo -e "hard link location: ${LINK}\n"
	echo "rsync cli args: ${RSYNCPARAM}"

	if [[ $TRYRUN == "true" ]]; then
		echo "Try run (-t). stopping here"
		exit 0
	fi
}
# end functions

# initialize variables with default values
BACKUPCONF="$HOME/.backthisup.conf"
SRC=false
DST=false
TRYRUN=false
EXCLUDEFILE=false
LINK=false
DATE=$(date "+%d-%m-%y_%H:%M")

# getting cli args
while getopts "s:d:e:l:thn" args;
do
	case $args in
		s) SRC=$OPTARG ;;
		d) DST=$OPTARG ;;
		t) TRYRUN=true ;;
		e) EXCLUDEFILE=$OPTARG ;;
		l) LINK=$OPTARG ;;
		h) usage  ;;
		n) BACKUPCONF=false ;;
		-) OPTIND=0
		   	break ;;
	esac	
done

# check for config
if [[ -e $BACKUPCONF ]]; then
	source $BACKUPCONF
	#comand line args are stronger than the config file	
	if [[ $SRC == "false" ]]; then SRC=${source} ; fi
	if [[ $DST == "false" ]]; then DST=${destination} ; fi
	if [[ $EXCLUDEFILE == "false" ]]; then EXCLUDEFILE=${excludefile} ; fi
	if [[ $LINK == "false" ]]; then LINK=${linkdest} ; fi
fi


# build rsync cli args
RSYNCPARAM="-RaP --delete "
if [[ $SRC == "false" ]]; then SRC=$HOME ; fi

if [[ $DST == "false" || ! -e $DST ]]; then
	echo "(E) No destination was given or the directory: $DST does not exists!"
	exit 1
fi

if [[ $LINK != "false" ]]; then
	RSYNCPARAM="${RSYNCPARAM} --link-dest=${LINK} "
fi

if [[ $EXCLUDEFILE != "false" ]]; then
	RSYNCPARAM="${RSYNCPARAM} --exclude-from=${EXCLUDEFILE} "
fi

# backup name
backup=${DST}/$(hostname)-${DATE}	
RSYNCPARAM="${RSYNCPARAM} $SRC $backup"

printConf

# main code
echo -e "\n(i) $DATE - starting backup"
sleep 2

rsync $RSYNCPARAM
exitcode=$?

echo -e "\n(i) RSYNC exit status: $exitcode" 
if [[ $exitcode == 0 ]]; then
	rm -f $destination/current
	echo "(i) symlinking newest backup to 'current' "
	ln -s $backup $DST/current
	[[ $postcmd ]] && $postcmd && echo "(i) post cmd executed"
else
	echo "(W) rsync ended with some warnings or errors. please check the last rsync messages"
fi
echo "(i) your backup is available here: $backup"
exit 0
