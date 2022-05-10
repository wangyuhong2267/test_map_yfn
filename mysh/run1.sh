#!/bin/bash
source /etc/profile
log=`date +"%Y-%m-%d_%H-%M-%S ---- main server is not running, restarting it."`
log2=`date +"%Y-%m-%d_%H-%M-%S ---- main server is running, restarting it."`
ser=`/usr/bin/pgrep main`
if [ "$ser" != "" ]
then
echo $log2 >> /home/ubuntu/my.log
#echo "The $1 service is running." >> /home/ubuntu/my.log
else
echo $log >> /home/ubuntu/my.log
#echo "The $1 service is NOT running."  >> /home/ubuntu/my.log
sudo /home/ubuntu/test_map/test_map/rerun.sh
fi

