#! /bin/sh
# Script by FLX: http://flx.me
# Requirements: curl
# Usage: ./prowl.sh priority(-2 to 2) appname description
# Example: ./prowl.sh 0 "linux" "this is a test"
app=$(hostname)
priority=$1
eventname=$2
description=$3
apikey="4e8d89d158b93fe85a7b5e5c4014c34ae9c0c78d"

if [ $# -ne 3 ]; then
echo "Prowl 4 Linux"
echo "Usage: ./prowl.sh priority(-2 to 2) appname description"
echo 'Example: ./prowl.sh 0 "linux" "this is a test"'
else
curl https://prowl.weks.net/publicapi/add -F apikey=$apikey -F priority=$priority -F application="$app" -F event="$eventname" -F description="$description"
fi
