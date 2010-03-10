#!/bin/sh

# tstats - terminal stats resp realtime stats on terminal
#          new also with a high speed progress bar
#
# P: [way=termstat/progressbar] [columns=<n>] tstats <fmt> <var names>
#
# by xmb{@skilled.ch} - http://xmb.ath.cx

# EXAMPLE
# { echo 1 20 ; while sleep .05; do (( ++x % 10 )) && echo 0 $((RANDOM%5)) ; echo 1 ; done ; } | way=progressbar columns=$COLUMNS sh -x tstats.sh
# 
# INPUT FORMAT
# <n> <n> [n] [n] ..

# two ways, one fmt one static sep

: ${FMT=%-3g / %-3g}
: ${fmt=${1-$s / %s}}
: ${es=\\r}

[ "$1" != *%* ] && fmt=$FMT
shift
[ ! -n "$@" ] && set -- a b c d e f g h i j k l m n o p q r s t u v w x y z

make_add() { local arg n=141 ; for arg; do (( ${n::1} && n+=3 || n++, x++ )); echo -e \\$n += $x ; done ; }
make_add() { local arg s x ; for arg; do (( x++ )) ; s=$s$arg+=0+\$$x\ ; done ; s=${s%% } ; echo -n ${s// /, } ; }

size=( $( stty size ) )
: ${columns=${size[1]}}
: ${way=progressbar} # termstat/processbar

: ${cont='$(make_add $@)'}
: ${cont2='$(make_add $@ | sed "s/+=[+\$0-9]\+//g")'}
: ${cont3='NR, a, b '}
: ${message="%-3d - $fmt$es"}
: ${content='NR, $(make_add $@)'}
: ${progress_message="-----\n\33[%dm|---\33[%dm\33[%dm --- $message\n|---\33[K %s\33[m\33[K\n-----\n"}
: ${progress_content='color, title, color, $cont3, progress\(columns, avg, max\)'} # needs percent in awk

termstat() {
  ${awk-awk} $aap "\$1 == \"exit\" { exit 1 } { printf \"$message\", $(eval echo $content) } END { printf \"\n\" }" $aas
}

progressbar() {
  # color, title
  set -- a b
  vars=$( eval echo $cont )
  vars2=$( eval echo $cont2 )
#  echo vars / $vars
#  echo 2 / $vars2
  ${awk-awk} -v lines=4 -v columns=$(( columns -5 )) -v color=42 $aap "\$1 == \"exit\" { exit 1 }
{
  if( ! x ) x = 1
  else      printf \"\33[%sF\", lines
  
  pbar( title, $(eval echo $cont) )
  fflush()
}

function pbar( title, avg, max ) {
  printf \"$progress_message\", $(eval echo $progress_content)
}

function mkbg( len, max,   s,i ) { while( ++i <= len && i <= max ) s = s \" \" ; return s }

function progress( columns, avg, max ) { return mkbg( columns / (max / avg), columns ) }"

}

if [ "$1" != . ]; then
  if [ "$1" == fifo ]; then

    file=$2
    shift 2

    #[[ -n $1 ]] && fmt=$1 && shift || fmt=$FMT

    #while aas=$file termstat $@ ; do :; done || exit
    while aas=$file $way $@ ; do :; done || exit
  fi

  #termstat $@
  $way $@
v
fi
