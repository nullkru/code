#!/bin/bash
# chekcen mit lsof mkv file
srcdir=/data/multimedia/movies/new
donedir=${srcdir}/remuxed
findcmd="find ${srcdir} -wholename ${donedir} -prune -o -name '*.mkv' -print"

pidFile=/tmp/$(basename $0).pid

if [ ! -e ${donedir} ]; then
	mkdir ${donedir}
fi

if [ -e $pidFile ]; then
	echo -e "====[W]\n $(basename $0) running already\n"
	exit 23
else
	echo $BASHPID > $pidFile
fi
echo -en "====[i] start $(date)"

for i in $(eval $findcmd | awk -F.mkv '{ print $1 }' )
do
	if [ -e $i.m2ts ]
   	then
	   	echo -e "====[i]\n $i.m2ts existiert verschieben nach ${donedir}\n"
		mv $i.mkv ${donedir}
	else
		sudo lsof $i.mkv
		if [ $? == 1 ]; then
			echo -e "====[i]\n $i.mkv Seems ready to transcode\n\n"

			/home/kru/bin/mkvtom2ts.sh $i.mkv
			if [ $? == 0 ]; then
				mv $i.mkv ${donedir}
				echo -e "====[i]\n $i.mkv converted and moved to ${donedir}\n"
			else
				mv $i.mkv ${donedir}
				echo -e "====[E]\n $i.mkv FAILED to convert but moved to ${donedir}\n"
			fi

		else
			echo "file in use, next time..."
		fi
	fi
done

echo -en "====[i] done $(date)"
rm -rf $pidFile
