#!/bin/bash
#kru's backup script
#Feel free to customize 
#Mirko Messer <mirk@chao.ch>


## /etc/backuprc example
##Files that will be backuped
#BACKUP_FILE="/bin /boot /etc /opt /usr /var /sbin /lib"
##Name prefix for backup (e.g: $name_prefix_`date`.tar.bz)
#name_prefix="backup`date +_%d-%m-%Y`"
##END 




BACKUP_CONFFILE="/home/kru/.kruconf"
BACKUP_HOME_CONFFILE="/home/kru/.kruconf"
EXCLUDEFILE="/home/kru/.kbackupexclude"
version=0.5


#common functions
notice(){
     echo -e "\\033[1;33;40m Notice: \\033[m $1"
}

error(){
     echo -e "\\033[1;31;40mError: \\033[m $1"
}

warning(){
     echo -e "\\033[1;31;40mWarning: \\033[m $1"
}     

info(){
     echo -e "===>\\033[1;32;40mInfo: \\033[m $1"
}     


#functions
welcome() {
     
     echo    "#################################################"
     echo    "           welcome to `basename $0`              "
     echo    "use `basename $0` -h for help or ctrl+c to cancel"
     echo -e "################################################# \n"
}

help() {
     echo "usage: `basename $0` [options]"
     echo "version:$version www.chao.ch"
     echo "options:"
     echo "  -f | --files   backup only this files *"
     echo "  -F | --force   faster and quiet"
     echo "  -h | --help    this help"
     echo "  -N <alt_name>  set alternative name direct"  
     echo "  --name | -n    ask for an alternative name"
     echo "  -c | --create  create local config"
     echo -e "  -s | --server  server mode \n"
     echo "* please set -f option at the end of the string otherwise it wouldn't work."
     exit 0
}

servermode() {

if [ "$SERVERMODE" = "1" ]; then
     clear
     echo "server mode comming soooon, sorry"
     exit 
fi
}

namepre() {

if [ "$NAME" = "1" ]; then
     echo "enter alternative name for backup (eg:foo,foo_bar, foobar) or press enter"
     echo -e "`basename $0`> \c"
     read altname
     alt_name_prefix=$altname
fi
}


backup() {
         
  create_config  welcome namepre servermode
         
        #counter and checker :)
         echo "The following files/directorys will be backuped"
         echo $BACKUP_FILE
          sleep 2
         echo "Backup beginns in"
         echo -n "3 " && sleep 1 &&echo -n "2 "
          sleep 1
         echo -e "1  \n... Now its time to roll a joint or something else..."
          sleep 1
        
        #name of the tar.bz2
        name=${alt_name_prefix:-$name_prefix}.tar
        
        if [ -f $name ]; then
             error "Sorry $name allready exists, rename or move it."
             exit 0
        fi
        #backup line
        tar cvfX $name $EXCLUDEFILE $BACKUP_FILE
        
        echo ""
        echo -e "backuped and stored under: \\033[0;32;40m $PWD/$name \\033[m"
        echo "Size/Name:` du -sh $name`"
        echo "Free Space:"
        echo "`df -h $PWD`"
        echo "THX for using kru's backup solution :)"
        echo ""
        exit 0
}

forcebackup() {
    
    namepre servermode

    #name of the tar.bz2
    name=${alt_name_prefix:-$name_prefix}.tar.bz2
                    
    tar cvfX $name $EXCLUDEFILE $BACKUP_FILE
    echo ""
    echo -e "backuped and stored under: \\033[0;32;40m $PWD/$name \\033[m"
    echo ""
    exit 0
    
}
    
read_config() {
     if [ -f "$BACKUP_CONFFILE" ]; then
          . "$BACKUP_CONFFILE"
     fi     

     if [ -f "$BACKUP_HOME_CONFFILE" ]; then
          . "$BACKUP_HOME_CONFFILE" ];
     else
     notice "no user config found "
     BACKUP_FILE="/bin /boot /etc /opt /usr /var /sbin /lib"
     name_prefix="backup`date +_%d-%m-%Y`"
     fi
     

}

create_config(){
if [ "$CREATE" = "1" ]; then
    
    touch $HOME/.backuprc
    file=.backuprc
    echo "#Files that will be backuped" >> $file
    echo "BACKUP_FILE=\"/bin /boot /etc /opt /usr /var /sbin /lib \"" >> $file
    echo "\#Name prefix for backup \(e.g: \$name_prefix_date.tar.bz\)" >> $file
    echo "name_prefix=\"backup\`date +_%d-%m-%Y\`\"" >> $file
    echo "" >> $file
    
    echo -e "$HOME/$file created you can move and rename it to /etc/backuprc for system wide usage"

exit
fi    
            
}

#end functions


#Options
NAME=0         #ask by default for name (off)
SERVERMODE=0   #copy backup to remote host (off)
FORCE=0        #force mode (off)
CREATE=0
#end options

#include config
read_config


while [ "$#" -ne "0" ]; do
    case "$1" in
         --files) 
               BACKUP_FILE="`echo $@ | sed -e "s/--files//" -e "s/-f//" -e "s/-N//" -e "s/--force//" -e "s/.//" -e "s/..//" `" ;;
         --help)   help ;;
         --server) SERVERMODE=1 ;;
         --name)   NAME=1 ;;
         --force)  FORCE=1 ;;
         --create) CREATE=1 ;;
         --*) help ;;
         
         -*)   
               # getopts das : ermöglicht neues $OPTARG
               while getopts "cfF:hsnN:-" opt; do
                     case $opt in
                          c) CREATE=1 ;;
                          f) 
                             BACKUP_FILE="`echo $@ | sed -e "s/--files//" -e "s/-f//" -e "s/--force//" -e "s/-N//" -e "s/\.//" -e "s/\..//"  `" ;;
                          F) FORCE=1 ;;
                          h) help ;;
                          s) SERVERMODE=1 ;;
                          n) NAME=1 ;;
                          N) export alt_name_prefix="$OPTARG" ;;
                          -) OPTIND=0
                             break
                             ;;
                          *) help ;;
                     esac
               done      
    esac                     
    shift                 
done


if [ "$FORCE" = 1 ]; then

forcebackup

else

backup

fi
#EOF
