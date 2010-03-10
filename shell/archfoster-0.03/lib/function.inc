#-*- mode:sh -*-


root_check() {
if [ `echo $UID` != "0" ]; then
     error "make sure you're root!"
     exit 0
else
     /bin/true

fi
}


welcome() {
     echo -e "Welcome to $0\nUse ctrl+c to abort"
}

uninstall() {
     clear
     info "Selected the following packages:"
     echo $(cat $UIFILE)
     pacman -Rns $(cat $UIFILE)
     info "Removing $UIFILE ..."
     sleep 1
     rm -rf $UIFILE
     exit 
}

ask() {
     echo -e "\nShould i [s]kip,[u]ninstall,[f]inish:"
     echo -e "$i $ \c"
     read answer

     case "$answer" in
          u | U | uninstall ) echo $i >> $UIFILE ;;
          s | S | skip ) echo -e "skiped!\n" ;;
          f | F | finish ) uninstall ;;
     esac
}


parse_options() {
     version; help ; main_rec
     
     main
}


main() {
     welcome
     info "Will ask you `pacman -Qe | wc -l` packages\n"
     sleep 1
     for i in $( pacman -Qe | awk '{ print $1 }' ); do
          pnotice   $i
          echo -e "`pacman -Qi $i | grep Description`" | line ; ask
     done
}

main_rec() {
     if [ "$REC" = "1" ]; then
          welcome
          info "You have choosen recurive option (hope you have a lot of time)"
          info "Will ask you `pacman -Qi | wc -l` packages\n"
          sleep 1
          for i in $( pacman -Qi | awk '{ print $1 }' ); do
               pnotice   $i
               echo -e "`pacman -Qi $i | grep Description`" | line ; ask
          done 
     fi
}
