#!/bin/bash
export PRUN=1_0
export TARGET=hello
export MODEL=AI
export CHIP=am57xx
echo PRUN=$PRUN
echo TARGET=$TARGET
echo MODEL=$MODEL
echo CHIP=$CHIP

echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger