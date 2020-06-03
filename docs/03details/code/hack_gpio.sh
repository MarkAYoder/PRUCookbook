#!/bin/bash
# Maps pin name (P9_11) to gpio number via libgpiod
#
# Usage:  hack_gpio.sh P9_11

chip="0"
found=0

while [ $chip -lt 4 ] ; do
    # echo $chip
    # Remove : from line number
    line=$(gpioinfo $chip | grep $1 | awk '{ print substr($2, 1, length($2)-1) }')
    
    [ ! -z "$line" ] && found=1 && break
    chip=$[$chip+1]
done

# echo chip: $chip line:  $line

if [ $found -ne 0 ] ; then
    echo gpio$[32*$chip+$line]
else
    echo $1 not found
fi
