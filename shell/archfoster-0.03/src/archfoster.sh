#!/bin/bash
#############################################################
#This Script was writen by Mirko Messer (kru) <mirk@chao.ch>
#Website: www.chao.ch
#Description: Simple shell script to clean your archlinux box
#USAGE: just type `archfoster` as root
#THX to: _ke from #archlinux.de on freenode http://homeke.tk
#############################################################

#default stuff
VERSION=0.04
UIFILE=/tmp/uifile_archfoster


ARCHFOSTER_LIBDIR=/usr/lib/archfoster

#Options
HELP=0
VERS=0
REC=0

#end



if [ -r $ARCHFOSTER_LIBDIR/function.inc ]; then
      . $ARCHFOSTER_LIBDIR/function.inc
else
      error "Unable to source function file"
      exit
fi

if [ -r $ARCHFOSTER_LIBDIR/common.inc ]; then
      . $ARCHFOSTER_LIBDIR/common.inc
else
      error "Unable to source common functions"
      exit
fi



while getopts "vhr:-" opt; do
     case $opt in
          v) VERS=1 ;;
          h) HELP=1 ;;
          r) REC=1 ;;
          -) OPTIND=0
             break
             ;;
          *) HELP=1 ;;
     esac
     shift
done     
     

root_check

parse_options

uninstall

#EOF
