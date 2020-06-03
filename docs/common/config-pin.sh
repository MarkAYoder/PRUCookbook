#!/bin/bash
# Adds "in" and "out" to config-pin
#
# Usage:  config-pin.sh P9_11 out

pin=$1  # Name of pin to be changed
dir=$2  # Direction, either in or out

if [ "$dir" != "in" ] && [ "$dir" != "out" ] ; then
    # Use config-pin
    /usr/bin/config-pin $*
    exit
fi

# Maps pin name (P9_11) to gpio number (gpio30) via libgpiod
# Find which gpio
chip=0
found=0

# Check each gpio chip
while [ $chip -lt 4 ] ; do
    # echo $chip
    # Remove : from line number
    line=$(gpioinfo $chip | grep $pin | awk '{ print substr($2, 1, length($2)-1) }')
    
    [ ! -z "$line" ] && found=1 && break
    chip=$[$chip+1]
done

# echo chip: $chip line:  $line

if [ $found -ne 0 ] ; then
    gpio=gpio$[32*$chip+$line]
    # echo $gpio
    echo $dir > /sys/class/gpio/$gpio/direction
    
else
    echo $pin not found
fi
