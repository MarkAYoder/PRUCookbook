#!/bin/bash
model=$(awk '{print $NF}' /proc/device-tree/model)
echo model=$model

export TARGET=hello2

if [ $model != "AI" ]; then
    export PRUN=0
    export MODEL=BLACK
else
    export PRUN=1_1
    export MODEL=AI
fi

echo PRUN=$PRUN
echo TARGET=$TARGET
echo MODEL=$MODEL

echo none > /sys/class/leds/beaglebone\:green\:usr1/trigger
echo none > /sys/class/leds/beaglebone\:green\:usr2/trigger
echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger
