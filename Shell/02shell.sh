#!/bin/bash

mount --bind /dev/ /mnt/UDISK/dev
[ `echo $?` -ne 0 ] && echo "mount wrong" && exit -1
mount --bind /proc/ /mnt/UDISK/proc
[ `echo $?` -ne 0 ] && echo "mount wrong" && exit -1

mount --bind /sys/ /mnt/UDISK/sys
[ `echo $?` -ne "0" ] && echo "mount wrong" && exit -1
