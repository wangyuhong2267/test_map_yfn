#!/bin/bash
log_file=/home/ubuntu/my.log
log=`date +"%Y-%m-%d_%H-%M-%S ---- wechat server is not running, restarting it."`
echo $log >> $log_file
ser=`/usr/bin/pgrep $1`
setterm -blank 0
if [ "$ser" != "" ]
then
echo "The $1 service is running."
else
echo "The $1 service is NOT running."
/home/ubuntu/test_map/test_map/main &
fi
