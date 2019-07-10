#!/bin/bash
export PRUN=1_0
export TARGET=hello
export MODEL=AI
export AI

echo PRUN=$PRUN
echo TARGET=$TARGET
echo MODEL=$MODEL

echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger