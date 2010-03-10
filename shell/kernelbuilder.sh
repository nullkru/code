#!/bin/bash
#
#kernel builder script für kernel version 2.6.x
#

###
#Configuration
###

#pfad zu einer kopie der bestehenden .config
path_to_config="/usr/src/_config"

#version des kernel
kernel_version="2.6.16.16"

###End config

PATCH_FUNC=1
EXTERNAL=1


##
#Treiber oder Module die nicht im kernel sind
##

external() {
### ab hier kann verändert werden
cd /usr/src

#build ipw2200
cd /usr/src/ipw2200/ieee80211-1.1.12 && make && make install
cd /usr/src/ipw2200/ipw2200-1.0.12 && make && make install 

echo "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"
echo "firmware sollte in /lib/firmware (oder so) sein"
echo "modul ipw2200 beim booten laden"
echo "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"
### end ipw2200

exit 0
}

##
#patchs die in den kernel eingespielt werden sollen
##


func_patch() {
#
echo "beginn patching!!!" ; sleep 2
cd /usr/src/linux

### Ab hier verändern

#orinoco patch
#patch -p0 -i ../patches/

#ibm acpi fan patch
patch -p0 -l -i ../patches/ibm_acpi2.6.14.patch

#suspend patches
#patch -p1 -l -i ../patches/sata_pm.2.6.15-rc6.patch
#patch -p1 -l -i ../patches/100-suspend2-2.2-for-2.6.15.1.patch
#patch -p1 -l -i ../patches/suspend.patch
#patch -p1 -l -i ../patches/02_libata_passthru.fixed.patch
#patch -p1 -l -i ../patches/03_libata_passthru_bugfix.patch

### stop editing here
if [ "$PEXIT" = "1" ]; then
	exit
fi

}





###don't edit after the line :)!!
#----------------------------------
#checken ob files existieren


main() {
  
  
  if [ "$PATCH_FUNC" == "1" ]; then
    func_patch
  fi
  
  if [ ! -f "/usr/src/linux/.config" ]; then
  	cp $path_to_config /usr/src/linux
	continue
  fi
  
  cd /usr/src/linux && make && make modules_install
  echo -e "\n\n\n "
  echo "enter  vmlinuz-<name>"
  echo -e "vmlinuz-\c "
  read name
  mv arch/i386/boot/bzImage /boot/vmlinuz-$name
  
  ##comment if i don't should build external kernel stuff
  if [ "$EXTERNAL" == "1" ]; then
    external
  fi

}


cd /usr/src

if [ `id -u` != "0" ]; then
 echo "make sure you're root!!!"
 exit
fi

while getopts "ehmEp-" opt; do
       case $opt in
             e) external ;;
             h)
               echo "help:  -m to build only main kernel"
               echo "       -e if you only want to build external modules"
               echo "       -h for this"
               echo "       -p to patch only"
               echo "       -E to edit this script"
               exit ;;
             m) PATCH_FUNC=0 && EXTERNAL=0 && main ;;
             E) jed `which kernelbuilder.sh` && exit ;;
             p) PEXIT=1 && func_patch ;;
             -) OPTIND=0
                break ;;
             *) echo "use -h" ;;
             
       esac
done
shift


if [ ! -e "$path_to_config" ]; then
  echo "keine existierende .config konfiguration gefunden. das heisst das dieses script nix für dich ist"
  exit
else
   echo ".config found          [OK]"
fi

if [ ! -e "/usr/src/linux-$kernel_version.tar.bz2" ]; then
  echo "downloading kernel source"
  wget -c http://www.kernel.org/pub/linux/kernel/v2.6/linux-$kernel_version.tar.bz2
  tar xjvf kernel-$kernel_version.tar.bz2
  rm -rf /usr/src/linux
  ln -s /usr/src/linux
else
   echo "kernel src in place    [OK]"
fi


if [ ! -e  "/usr/src/linux-$kernel_version" ]; then
  echo "linking linux-$kernel_version.tar.bz2 to /usr/src/linux"
else
   echo "kernel source unpacked [OK]"
fi

if [ ! -e "/usr/src/linux" ]; then
   echo "linking source"
   echo "kenrel source linked   [OK]"
 ln -s /usr/src/linux-$kernel_version /usr/src/linux
else
   echo "kernel source linked   [OK]"
   main
fi

