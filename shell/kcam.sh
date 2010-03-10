#!/bin/bash

###kcam - kru cam utiliti 
# uses ~/.kruconf with the following variables:
# CAMPATH="/dev/sdb1"
# CAMMOUNT="/dev/sdb"
# PHOTODIR="/home/kru/data/digicam"
#
# usage: kcam <dir_to_create>
###

notice(){
     echo -e "\033[1;33;40m  $1 \033[0;m"
}
error(){
     echo -e "\033[1;31;40mError: \033[m $1"
}
warn(){
     echo -e "\033[1;31;40mWarning: \033[m $1"
}
info(){
     echo -e "===>\033[1;32;40mInfo: \033[m $1"
}
                    



#/* check if .kruconf exist */
if [ -f "$HOME/.kruconf" ]; then
    . $HOME/.kruconf
else
   error "can't find $HOME/.kruconf"    
fi

usage() {
echo -e "usage:\n
      $0 <device eg. sdb1> <name_of_new_photodir>
      this will create a directory in $PHOTODIR 
      like photodir/year/<name_of_new_photodir>"
}

[[ ! $@ ]] && usage && exit 1
ACTUALDIR=$PWD
cd $PHOTODIR

DEVICE="$1"
CAMMOUNT="/media/$DEVICE/"
DIRNAME="$2"
yeardir=`date +%Y`

if [ -d `date +%Y` ]; then
    cd $yeardir
else    
    mkdir $yeardir
    cd $yeardir
fi

if [ -d $DIRNAME ]; then
    warn "$DIRNAME exists should i add the files to this dir [Y/n]? \c"
    read answer
    if [ "$answer" = "" ]; then
         answer="y"
    fi
    case "$answer" in
        "Y" | "y" ) /bin/true ;;
        "n" | "N" ) exit ;;
    esac
    unset $answer
else    
    mkdir -p  $DIRNAME/{movies,photos}
fi    

info "Mounting USB cam and beginn to process"
pmount $DEVICE

photos=`find $CAMMOUNT -iname *.jpg -o -iname *.jpeg -o -iname *.png -o -iname *gif -o -iname *.tiff`
videos=`find $CAMMOUNT -iname *.mov -o -iname *avi -o -iname *.mpg -o -iname *.mpeg`

notice "Should i remove the files from the cam after moving? [Y/n]? \c"
read answer
if [ "$answer" = "" ]; then
    answer="y"
fi
    case "$answer" in
        "Y" | "y" ) info "start moving files... please hold on" && mv -v $photos $PHOTODIR/$yeardir/$DIRNAME/photos/ && mv -vf $videos $PHOTODIR/$yeardir/$DIRNAME/movies/ ;;
        "N" | "n" ) info "start copy files... please hold on" && cp -rv $photos $PHOTODIR/$yeardir/$DIRNAME/photos/ && cp -rv $videos $PHOTODIR/$yeardir/$DIRNAME/movies/  ;;
    esac

notice "Setting file permissions"
sudo chmod 755 -R $PHOTODIR/$yeardir/$DIRNAME
chmod 644 -R $PHOTODIR/$yeardir/$DIRNAME/movies/*
chmod 644 -R $PHOTODIR/$yeardir/$DIRNAME/photos/*
info "unmounting cam"
cd $ACTUALDIR
pumount $DEVICE

notice "Photos and videos stored in $PHOTODIR/$yeardir/$DIRNAME"
notice "Done thx for using $0"
