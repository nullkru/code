#!/bin/bash
#
# mkvtom2ts.sh - a simple wrapper around the tsmuxeR
# Creates a m2ts from a "standard" mkv (assuming video is MPEG4, and sound is AC3 or DTS)
#
# v0.1 initial version
# v0.2 added DTS support
# v0.3 changed to tsmuxer linux version + added multiple audio lang support
#
# Usage: mkvtom2ts filename.mkv
#

AUDIO_LANGS="ger und eng" # English German"


BASENAME=$(basename "$1" .mkv)
DEST_DIRNAME=$(dirname $1)
DEST_FILE=${DEST_DIRNAME}/$BASENAME.m2ts

MPEG4_TRACK_NO=`mkvinfo "$1" | grep V_MPEG4/ISO/AVC -B10 | grep Track\ number\:\ | awk '{ print $5 }'`

for AUDIO_LANG in $AUDIO_LANGS
do
AC3_TRACK_NO=$(mkvinfo "$1" | grep A_AC3 -B10 -C3 | grep Language\:\ $AUDIO_LANG -B13 | grep Track\ number\:\ | awk '{ print $5 }' | head -1 )
DTS_TRACK_NO=`mkvinfo "$1" | grep A_DTS -B10 -C3 | grep Language\:\ $AUDIO_LANG -B13 | grep Track\ number\:\ | awk '{ print $5 }'`
# AAC support nullkru
AAC_TRACK_NO=$(mkvinfo "$1" | grep A_AAC -B10 -C3 | grep Name\:\ $AUDIO_LANG -B13 | grep Track\ number\:\ | awk '{ print $5 }' )
if [ -n "$AC3_TRACK_NO" -o -n "$DTS_TRACK_NO" -o -n "$AAC_TRACK_NO" ]
then
  break
fi
done

#hack fuer englische filme
#AC3_TRACK_NO=2
#DTS_TRACK_NO=1

echo "Video(V_MPEG4/ISO/AVC) track no : $MPEG4_TRACK_NO"
echo "Audio(A_AC3) $AUDIO_LANG track no      : $AC3_TRACK_NO"
echo "Audio(A_DTS) $AUDIO_LANG track no      : $DTS_TRACK_NO"
#AAC support - nullkru
echo "Audio(A_AAC) $AUDIO_LANG track no		 : $AAC_TRACK_NO"

#audio ac3->direct muxing
if [[ $AC3_TRACK_NO -gt "0" ]]
then
  echo "Found ac3 track, muxing directly..."
  rm -f mux.meta
  echo "MUXOPT --no-pcr-on-video-pid --new-audio-pes --vbr" >>mux.meta
  echo "V_MPEG4/ISO/AVC, "$1", level=4.1, insertSEI, contSPS, track=$MPEG4_TRACK_NO, lang=eng" >>mux.meta
  echo "A_AC3, "$1", track=$AC3_TRACK_NO, lang=eng" >>mux.meta
  tsMuxeR mux.meta $DEST_FILE
  rm -f mux.meta
else
	#checking for dts	
   	if [[ $DTS_TRACK_NO -gt "0" ]]; then
          echo "No ac3 but dts, converting to ac3.."
          mkvextract tracks "$1" $DTS_TRACK_NO:"$BASENAME.dts" $MPEG4_TRACK_NO:"$BASENAME.mpeg4"
          dcadec -r -o wavall "$BASENAME.dts" > "$BASENAME.wav"
          aften "$BASENAME.wav" "$BASENAME.ac3"
          echo "Muxing..."
          rm -f mux.meta
          echo "MUXOPT --no-pcr-on-video-pid --new-audio-pes --vbr" >>mux.meta
          echo "V_MPEG4/ISO/AVC, "$BASENAME.mpeg4", level=4.1, insertSEI, contSPS, track=1, lang=eng" >>mux.meta
          echo "A_AC3, "$BASENAME.ac3", track=1, lang=eng" >>mux.meta
          tsMuxeR mux.meta $DEST_FILE
	  	  #rm -f mux.meta $BASENAME.aac $BASENAME.dts $BASENAME.wav $BASENAME.ac3 $BASENAME.mpeg4  
	  fi
  	  #checking for aac - nullkru
	  if [[ $AAC_TRACK_NO -gt "0" ]]; then
	  	  #aac support - nullkru
          echo "No ac3 or dts but aac, converting to ac3.."
          mkvextract tracks "$1" $AAC_TRACK_NO:"$BASENAME.aac" $MPEG4_TRACK_NO:"$BASENAME.mpeg4"

		  faad -q -f 2 -w "$BASENAME.aac" | aften - "$BASENAME.ac3"

          echo "Muxing..."
          rm -f mux.meta
          echo "MUXOPT --no-pcr-on-video-pid --new-audio-pes --vbr" >>mux.meta
          echo "V_MPEG4/ISO/AVC, "$BASENAME.mpeg4", level=4.1, insertSEI, contSPS, track=1, lang=eng" >>mux.meta
          echo "A_AC3, "$BASENAME.ac3", track=1, lang=eng" >>mux.meta
          tsMuxeR mux.meta $DEST_FILE
	  	#	rm -f mux.meta $BASENAME.aac $BASENAME.dts $BASENAME.wav $BASENAME.ac3 $BASENAME.mpeg4  
  	  else
          echo "No ac3, aac or dts, exiting..."
		  exit 1
  	  fi                
      
fi

