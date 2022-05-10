#!/bin/bash
source /etc/profile

ser=`/usr/bin/pgrep main`
if [ "$ser" != "" ]
then
echo "The $1 service is running." >> /home/ubuntu/my.log
else
echo "The $1 service is NOT running."  >> /home/ubuntu/my.log
/home/ubuntu/test_map/test_map/main &
fi

