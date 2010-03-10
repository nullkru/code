#-*- mode:sh -*-

#common functions
pnotice(){
     echo "[1;33;40mPackage ==> [m   $1"
}

notice(){
     echo "[1;33;40mNotice ==> [m $1"
}

error(){
     echo -e "[1;31;40mError: [m $1"
}

warning(){
     echo -e "[1;31;40mWarning: [m $1"
}

info(){
     echo -e "===>[1;32;40mInfo: [m $1"
}
     
version() {
    if [ "$VERS" = "1" ]; then
         echo "scripted by kru <mirk@chao.ch>"
         echo "thx to _ke(http://homeke.tk)"
         echo Version: $VERSION
         exit 0
    fi
}

help() {          
     if [ "$HELP" = "1" ]; then
          echo "Usage: \``basename $0`\` as root"
          echo "Options:"
          echo    "  -h      show this here"
          echo    "  -v      version of `basename $0`"
          echo -e "  -r      ask all `pacman -Qi | wc -l` installed packages"
          exit 0   
     fi            
}      

