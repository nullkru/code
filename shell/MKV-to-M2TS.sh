#!/bin/bash
#
# License
#
# Creates a PlayStation 3 compatible M2TS from a MKV
# Copyright (c) 2009 Flexion.Org, http://flexion.org/
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

IFS=$'\n'
VER="1.1"

echo "MKV-to-M2TS v${VER} - Creates a PlayStation 3 compatible M2TS from a MKV."
echo "Copyright (c) 2009 Flexion.Org, http://flexion.org. MIT License" 
echo

function usage {
    echo
    echo "Usage"
    echo "  ${0} movie.mkv [--split] [--help]"
    echo ""
    echo "You can also pass the following optional parameter"
    echo "  --split : If required, the .M2TS output will be split at a boundary less than"
    echo "            4GB for FAT32 compatibility"
    echo "  --help  : This help."
    echo
    exit 1
}

# Pass in the .mkv filename
function get_info {	
	MKV_FILENAME=${1}
	
	local MKV_TRACKS=`mktemp`
	mkvmerge -i ${MKV_FILENAME} > ${MKV_TRACKS}
	local MKV_INFO=`mktemp`
	mkvinfo ${MKV_FILENAME} > ${MKV_INFO}

	# Get the track ids for audio/video assumes one audio and one video track currently.
	VIDEO_ID=`grep video ${MKV_TRACKS} | cut -d' ' -f3 | sed 's/://'`
	#
	#
	#remove line for other audio
	#
	#audio_arr=($(grep audio ${MKV_TRACKS} | cut -d ' ' -f3 | sed 's/:/ /' | tr -d '\n'))
	
	AUDIO_ID=`grep audio ${MKV_TRACKS} | cut -d' ' -f3 | sed 's/://' | line`

	SUBS_ID=`grep subtitles ${MKV_TRACKS} | cut -d' ' -f3 | sed 's/://'`
	
	# Get the audio/video format. Strip the V_, A_ and brackets.
	VIDEO_FORMAT=`grep video ${MKV_TRACKS} | cut -d' ' -f5 | sed 's/(\|V_\|)//g'`
	AUDIO_FORMAT=`grep audio ${MKV_TRACKS} | cut -d' ' -f5 | sed 's/(\|A_\|)//g' | line`

	# Are there any subtitles in the .mkv
	if [ -z ${SUBS_ID} ]; then
		SUBS_FORMAT=""
	else
		SUBS_FORMAT=`grep subtitles ${MKV_TRACKS} | cut -d' ' -f5 | sed 's/(\|S_\|)//g'`
	fi

	# Get the video frames per seconds (FPS), number of audio channels and audio sample rate.
	if [[ $VIDEO_ID -lt $AUDIO_ID ]]; then
	    # Video is before Audio track
    	VIDEO_FPS=`grep fps ${MKV_INFO} | sed -n 1p | cut -d'(' -f2 | cut -d' ' -f1`
	else
    	# Video is after Audio track
	    VIDEO_FPS=`grep fps ${MKV_INFO} | sed -n 2p | cut -d'(' -f2 | cut -d' ' -f1`
	fi
	
	# Guess the FPS if we didn't find one (it seems tsMuxer does it that way)
	# see http://en.wikipedia.org/wiki/24p
	# Its needed for files with a subtitle track, otherwise tsMuxer compains
	if [ -z "${VIDEO_FPS}" ]; then
		echo "WARNING! H.264 stream does not contain fps field. Defaulting to 23.976."
		VIDEO_FPS="23.976"
	fi

	VIDEO_WIDTH=`grep "Pixel width" ${MKV_INFO} | cut -d':' -f2 | sed 's/ //g'`
	VIDEO_HEIGHT=`grep "Pixel height" ${MKV_INFO} | cut -d':' -f2 | sed 's/ //g'`

	# Get the sample rate
	AUDIO_RATE=`grep -A 1 "Audio track" ${MKV_INFO} | sed -n 2p | cut -c 27-31`        

	# Get the number of channels
	AUDIO_CH=`grep Channels ${MKV_INFO} | sed -e 1q | cut -d':' -f2 | sed 's/ //g'`
	
	# Is the video h264 and audio AC3 or DTS?
	if [ "${VIDEO_FORMAT}" != "MPEG4/ISO/AVC" ]; then
		echo "ERROR! The Video track is not H.264. I can't process ${VIDEO_FORMAT}, please use a different tool."
		exit 1
	elif [ "${AUDIO_FORMAT}" != "DTS" ] && [ "${AUDIO_FORMAT}" != "AC3" ]; then
		echo "ERROR! The audio track is not DTS or AC3. I can't process ${AUDIO_FORMAT}, please use a different tool."
		exit 1
	else
		echo -e "Video\t : Track ${VIDEO_ID} and of format ${VIDEO_FORMAT} (${VIDEO_WIDTH}x${VIDEO_HEIGHT} @ ${VIDEO_FPS}fps)"
		echo -e "Audio\t : Track ${AUDIO_ID} and of format ${AUDIO_FORMAT} with ${AUDIO_CH} channels @ ${AUDIO_RATE}hz"
		if [ -z ${SUBS_ID} ]; then
			echo -e "Subs\t : none"
		else
			# Check the format of the subtitles. If they are not TEXT/UTF8 we can't use them.
			if [ "${SUBS_FORMAT}" != "TEXT/UTF8" ]; then
				SUBS_ID=""
				echo -e "Subs\t : ${SUBS_FORMAT} is not supported, skipping subtitle processing"
			else
				echo -e "Subs\t : Track ${SUBS_ID} and of format ${SUBS_FORMAT}"
			fi
		fi	
	fi
	
	# Clean up the temp files
	rm ${MKV_TRACKS} 2>/dev/null
	rm ${MKV_INFO} 2>/dev/null
}

# Define the commands we will be using. If you don't have them, get them! ;-)
REQUIRED_TOOLS=`cat << EOF
aften
chmod
cut
dcadec
echo
file
grep
mktemp
mkvextract
mkvinfo
mkvmerge
rm
sed
stat
tsMuxeR
EOF`

for REQUIRED_TOOL in ${REQUIRED_TOOLS}
do
    # Is the required tool in the path?
    which ${REQUIRED_TOOL} >/dev/null  
         
    if [ $? -eq 1 ]; then
        echo "ERROR! \"${REQUIRED_TOOL}\" is missing. ${0} requires it to operate."
        echo "       Please install \"${REQUIRED_TOOL}\"."
        exit 1      
    fi        
done

# Get the first parameter passed in and validate it.
if [ $# -lt 1 ]; then
    echo "ERROR! ${0} requires a .mkv file as input"	
	usage
elif [ "${1}" == "-h" ] || [ "${1}" == "--h" ] || [ "${1}" == "-help" ] || [ "${1}" == "--help" ] || [ "${1}" == "-?" ]; then
    usage
else    
    MKV_FILENAME=${1}
        
    # Is the .mkv a real Matroska file?
    MKV_VALID=`file ${MKV_FILENAME} | grep Matroska`
    if [ -z "${MKV_VALID}" ]; then
        echo "ERROR! ${0} requires valid a Matroska file as input. \"${1}\" is not a Matroska file."
        usage
    fi	    
    
    # It appears to be a valid Matroska file.
    BASENAME=$(basename "$1" .mkv)        
    M2TS_FILENAME=${BASENAME}.m2ts
    META_FILENAME=${BASENAME}.meta
    
    # Audio filenames should we need to transcode DTS to AC3.
    AC3_FILENAME=${BASENAME}.ac3
    DTS_FILENAME=${BASENAME}.dts
    shift
fi

# Init optional parameters.
M2TS_SPLIT_SIZE=0

# Check for optional parameters
while [ $# -gt 0 ]; 
do	
	case "${1}" in
		-s|--split|-split)
            # Get the size of the .mkv file in bytes (b)
            MKV_SIZE=`stat -c%s "${MKV_FILENAME}"`            

            # The PS3 can't play files which are bigger than 4GB and FAT32 doesn't like files bigger than 4GB.
            # Lets figure out the M2TS split size should in kilo-bytes (kb)
            if [ ${MKV_SIZE} -ge 12884901888 ]; then    
	            # >= 12gb : Split into 3.5GB chunks ensuring PS3 and FAT32 compatibility
	            M2TS_SPLIT_SIZE="3670016"
            elif [ ${MKV_SIZE} -ge 9663676416 ]; then   
	            # >= 9gb  : Divide .mkv filesize by 3 and split by that amount
	            M2TS_SPLIT_SIZE=$(((${MKV_SIZE} / 3) / 1024))
            elif [ ${MKV_SIZE} -ge 4294967296 ]; then   
	            # >= 4gb  : Divide .mkv filesize by 2 and split by that amount
	            M2TS_SPLIT_SIZE=$(((${MKV_SIZE} / 2) / 1024))
            fi										                        
            shift;;  
        -h|--h|-help|--help|-?)
            usage;;                  
       	*)
           echo "ERROR! \"${1}\" is not s supported parameter."
           usage;;            
	esac    
done

# Add 'KB' to the split size for tsMuxeR compatibility
M2TS_SPLIT_SIZE=`echo "${M2TS_SPLIT_SIZE}KB"`

# Get the required infor from the MKV file and validate we can process it.
get_info ${MKV_FILENAME}

# Remove .meta file from previous run. Then create a new tsMuxeR .meta file.
rm ${META_FILENAME} 2>/dev/null

# Add split options, if required.
if [ "${M2TS_SPLIT_SIZE}" != "0KB" ]; then
    echo "MUXOPT --no-pcr-on-video-pid --new-audio-pes --vbr --vbv-len=500 --split-size=${M2TS_SPLIT_SIZE}" >> ${META_FILENAME}
else
    echo "MUXOPT --no-pcr-on-video-pid --new-audio-pes --vbr --vbv-len=500" >> ${META_FILENAME}    
fi    

# Adding video stream.
echo "V_MPEG4/ISO/AVC, \"${MKV_FILENAME}\", fps=${VIDEO_FPS}, level=4.1, insertSEI, contSPS, ar=As source, track=${VIDEO_ID}, lang=und" >> ${META_FILENAME}

# Add audio stream.
if [ "${AUDIO_FORMAT}" == "AC3" ]; then
    # We have AC3, no need to transcode.
    echo "A_AC3, \"${MKV_FILENAME}\", track=${AUDIO_ID}, lang=und" >> ${META_FILENAME}
else    
    # We have DTS, transcoding required.
    mkfifo ${DTS_FILENAME}
    mkfifo ${AC3_FILENAME}    
    dcadec -o wavall "${DTS_FILENAME}" | aften -v 0 -readtoeof 1 - "${AC3_FILENAME}" &
    mkvextract tracks "${MKV_FILENAME}" ${AUDIO_ID}:"${DTS_FILENAME}" &    
    echo "A_AC3, \"${AC3_FILENAME}\", track=1, lang=und" >> ${META_FILENAME}
fi

# Add any subtitles, if required.
if [ "${SUBS_ID}" != "" ]; then
    echo "S_TEXT/UTF8, \"${MKV_FILENAME}\", font-name=\"Arial\", font-size=65, font-color=0x00ffffff, bottom-offset=24, font-border=2, text-align=center, video-width=${VIDEO_WIDTH}, video-height=${VIDEO_HEIGHT}, fps=${VIDEO_FPS}, track=${SUBS_ID}, lang=und" >> ${META_FILENAME}
fi

# For debugging
#cat ${META_FILENAME}

# Convert the MKV to M2TS
tsMuxeR ${META_FILENAME} ${M2TS_FILENAME}

# Remove the transient files
rm ${META_FILENAME} 2>/dev/null
rm ${AC3_FILENAME} 2>/dev/null
rm ${DTS_FILENAME} 2>/dev/null

# Change the permission on the M2TS file(s) to something sane.
chmod 644 ${BASENAME}*.m2ts 2>/dev/null   

echo "All Done!"
