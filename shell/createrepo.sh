#!/bin/bash

repodir='/mnt/tera/appdata/svn/svnrepo/'
group='users'
url='svn+ssh://kru.ath.cx/svn/'


[[ ! $1 ]] && echo "usage: $0 <newreponame>" && exit

newrepopath=${repodir}${1}

[[ ! -d $newrepopath ]] && mkdir $newrepodir && echo "created dir $newrepodir"

svnadmin create ${repodir}$1
echo "svn repo created"

echo "chown -R kru.users $newrepodir"
chown -R kru.users $newrepodir

echo "chmod -R g+rw $newrepodir"
chmod -R g+rw $newrepodir

echo created new repo ${url}${1}




