#!/bin/bash

##
# export my configs, functions and aliases for nice look&feel
# to source use '. krufunctions.sh' or 'source krufunctions.sh', and use it from
# /etc/profile /etc/bash.bashrc or .bashrc bash_profile or what ever...
# Tip: add this lines at the end of the above files and uncomment lines you won't use 
#      for faster sourcing :)
#
# by kru<@choa.ch> [http://chao.ch]
#
# For full power you should install: w3m(dict), awk, sed, firefox(fflocal),
#
# time to source on my notebook(intel pentium M): 600MHz: ~0.09s  1400Mhz: 0.004s
#
# latest updates: (29.8.07)
# + changed the PS1 
# + added khostup: check if a host is up and save 1 or 0 in $khostup var (usage: khostup <ip or host>)
# + added ksgrep: grep for words in current cwd files
# + renamed ffind to kfind
# + added kfpwd (kru find pwd) to search from current working directory usage: kfpwd $string (eg kfpwd *blah* #   to search for stuff that contains blah in filename
# older stuff
# + dict work now better
# + weeded out user specific stuff use .bashrc for this stuff (example on: http://chao.ch/code/shell/_bashrc)
# + fuck you asks you to shutdown the computer (a wish from iwan.chao.ch)
# + fixed kunX
##


##
#User Section removed use $HOME/.bashrc (example http://chao.ch/code/shell/_bashrc)
##

###
# Start krufunctions
###

# System PATHs
PATH="/bin:/usr/bin:/usr/local/bin:/opt/bin:/usr/X11R6/bin:~/bin:${PATH}:"

if [[ $0 == "bash" || $0 == "-bash" ]]; then
	if [ "$SSH_TTY" = "" ]; then
		if [ "$PS1" ]; then
			if [ "`id -u`" = 0 ]; then
				#root on local tty    
				PATH="/sbin:/usr/sbin:/usr/local/sbin:/${PATH}:"
				PS1="\[\033[1;34m\]\u\[\033[0m\]@\[\033[1;31m\]\h\[\033[0m\]:\[\033[1;36m\](\[\033[1;36m\]\w\[\033[1;36m\])\[\033[0m\]\n\[\033[1;30m\]#>\[\033[0m\]"
				#PS1="\[\033[1;34m\]\u\[\033[0m\]@\[\033[1;31m\]\h\[\033[0m\]:\[\033[1;36m\](\[\033[1;36m\]\w\[\033[1;36m\])\[\033[0m\] # "
			else
				#user local
				#PS1="\[\033[1;31m\]\u\[\033[0m\]@\[\033[1;33m\]\h\[\033[0m\]:\[\033[1;32m\](\[\033[1;32m\]\w\[\033[1;32m\])\[\033[0m\] $ "
				PS1="\[\033[1;31m\]\u\[\033[0m\]@\[\033[1;33m\]\h\[\033[0m\]:\[\033[1;32m\](\[\033[0;32m\]\w\[\033[1;32m\])\[\033[0m\]\n\[\033[1;30m\]$>\[\033[0m\]"
				#PS1="\[\033[1;31m\]\u\[\033[0m\]@\[\033[1;33m\]\h\[\033[0m\]:\[\033[1;32m\](\[\033[0;32m\]\w\[\033[1;32m\])\[\033[0m\] $ "
			fi
		fi
	else
		#underlined root on ssh
		if [ "`id -u`" = 0 ]; then
			PS1="[\[\033[1;4;34m\]\u\[\033[0;4m\]@\[\033[1;4;31;40m\]\h\[\033[0m\]:\[\033[1;36m\](\[\033[1;36m\]\w\[\033[1;36m\])\[\033[0m\] #] "
			PATH="/sbin:/usr/sbin:/usr/local/sbin:${PATH}"
		else
			#user
			PS1="[\[\033[1;4;31m\]\u\[\033[0;4m\]@\[\033[1;4;33m\]\h\[\033[0m\]:\[\033[1;32m\](\[\033[1;32m\]\w\[\033[1;32m\])\[\033[0m\] $] "
		fi
	fi
fi


#special screen-specific stuff for window titles
#case $TERM in
#    screen*)
#        trap 'echo -ne "\ek${BASH_COMMAND%%\ *}\e\\"' DEBUG 
#        #PROMPT_COMMAND='echo -ne "\ek$(short_pwd 15)\e\\"'
#        ;;
#esac




#for nice ls output ( `dicolors -b` but on  mac osx they aren't any dircolors
#so i add the whole output here)
LS_COLORS='no=00:fi=00:di=01;33:ln=01;36:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.gz=01;31:*.bz2=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.avi=01;35:*.fli=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.ogg=01;35:*.mp3=01;35:*.wav=01;35:'
export LS_COLORS


##
# aliases
##
alias wgetdircontent="wget -r -l inf -np -t 0 -nc -nd -R *php*,*html* $@"
alias ls="ls  --color=y -F" # -F append indicator (one */=@I) to entries
alias la="ls -la"
alias ll="ls --color=n -l"
alias l="ls -l"
alias cls="clear; ls"
# aliases for cowards...
alias cp="cp -i"
alias mv="mv -i"
alias rm="rm -i"

##
# PROMPT_COMMAND == precommand... or so
##
PROMPT_COMMAND='kill -WINCH $$ '
#PROMPT_COMMAND='echo -ne "\033]0;`$0`\007"'
#PROMPT_COMMAND='echo -ne "k\\"' # <esc>k<esc>\ used to set  screen title dynamic
# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

##
# make flags
##
export MAKEFLAGS="-j2"

##
# functions
##

kps() { ps ax | grep -v grep | grep -v kps | grep $@ | awk '{ print $1 }' ; }

#kill a process with fuck <appname>
fuck() 
{
	[[ ! $@ ]] && echo "usage: fuck <command> or fuck you to shutdown" && return 1
	local x=$@
	# wish from iwan.chao.ch ;)  
	if [[ `echo $x` = "you" ]]; then
		echo -e "Are you shure you want to shutdown[y/N]?\c "
		read answer
		if [[ `echo $answer` = "y" ]]; then
			shutdown -h 0
		else
			return
		fi
	fi		
	
	process=$(kps $x)
	[[ ! $process ]] && echo nothing to kill && return
	kill -9 $process
}
                                                                       

#process search utility pss <processname>
pss() { ps aux | grep -v grep | grep -v pss | grep $@; }

#calc usage: eg. calc 23+23 result should be stored in the var. $calc

calc() 
{ 
	echo -e "$@ ="
	calc=$(perl -e "printf $@")
	echo $calc
	echo 'Result stored in $calc'
}

#usage: dict <search pattern>
#help: if you search e.g blow job try dict blow+job
dict() 
{
[[ ! $1 ]] && echo "usage: $ dict <searchterm>" && return 1
	suchterm=($@)
	echo "cancel with ctrl + c or q"
	w3m -dump -S  http://www.woerterbuch.info/?query=$suchterm | \
	grep -A $COLUMNS "Direkte Treffer:" | \
	sed -e 's/Sprachausgabe//g'| \
	sed -e 's/\[blind]//g' | \
	grep -v Mitmachen | \
	grep -v Suchen | \
	grep -v "\(*\)" | \
	grep -v "Alle Treffer anzeigen" | more
	echo "Whole list: http://www.woerterbuch.info/?query=$suchterm&dl=0"
}

#fasfind ffind
#usage: ffind <path> <string>
kfind() 
{
	[[ ! $@ ]] && echo "usage: $ kfind <path> <searchstring>" && return 1
        searchstring=($2)
        path=($1)
	echo "kfind: searching for $searchstring"
        find $path -iname $searchstring
}                                 

kfpwd()
{
	[[ ! $@ ]] && echo "usage: $ kfpwd <search pattern>" && return 1
	searchstring="$1"
	echo "searching for $searchstring"
	find $(pwd) -iname $searchstring
}

ksgrep()
{
	[[ ! $@ ]] && echo "usage: $ ksgrep <string>" && return 1
	searchstring="$1"
	echo "greping for $searchstring in $(pwd)/*"
	grep --colour=auto -n "$searchstring" ./*
}

#kru un zip tar.bz2 bz2 tar.gz gz er: kunx ( X stands for x or X :)
#usage kunX file [ path/to/extract

kunX() 
{
     
     [[ ! $1 ]] && echo -e "usage: \n kunx <file> [path/to/extract]\nsupported files: *gz,*bz*,*rar,*ace,*zip" && return
     
     ###TODO: schlaues suchmuster für .GZ, .tar.GZ usw
     if [[ `echo $1 | grep "gz"` != "" ]]; then
       if [ `echo  $2` ]; then 
               tar xzvf $1 -C $2
               echo "extracted to: $2"
               return
          else
               tar xzvf $1
               return
          fi
     elif [[ `echo $1 | grep "bz"` != "" ]]; then
          if [ `echo $2` ]; then
               tar xjvf $1 -C $2
               echo "extracted to: $2"
               return
       else
               tar xjvf $1
          return
          fi
     elif [[ `echo $1 | grep "rar"` != "" ]]; then
          if [ `echo $2` ]; then
               unrar x $1 $2
               return
          else
          unrar x $1
          return
          fi
     elif [[ `echo $1 | grep "ace"` != "" ]]; then
          if [ `echo $2`  ]; then
               echo sorry not available
               return
          else
          unace x $1
          return
          fi
     elif [[ `echo $1 | grep "zip"` != "x" ]]; then
          if [ `echo $2` ]; then
               echo sorry not available
               return
          else
          unzip $1
          return
          fi
     else
         echo "error: unrecognized format"
     fi
}

#firefox local file launcher 
fflocal() 
{ 
          [[ ! $1 ]] && echo "usage: $ fflocal <localfile>" && return 1
          local file=$1
          firefox file:$PWD/$file; return 1; 
}

#host online checker
khostup()
{
	[[ ! $1 ]] && echo -e "usage: khostup <host>\n check if host is up and save 1 or 0 in \$khostup" && return 1
	khostup=$(ping -W 1 -c 3 -n -q $1 | sed -n '/received/p' | awk '{ print $4 }')
	if [[ $khostup = 3 ]]; then
		khostup=1
	fi
}

serienplay() {
	_dirname=$(basename $PWD)
	
	echo $@ >> $_dirname
	mplayer $@
}

### EOF          


