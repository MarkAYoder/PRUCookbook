#!/bin/bash
# Setup for 64x32 RGB Matrix
# export PRUN=0
# export TARGET=pwm7
# echo PRUN=$PRUN
# echo TARGET=$TARGET

# Configure the PRU pins based on which Beagle is running
machine=$(awk '{print $NF}' /proc/device-tree/model)
echo -n $machine
if [ $machine = "Black" ]; then
    echo " Found"
    pins=""
elif [ $machine = "Blue" ]; then
    echo " Found"
    pins=""
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    prupins="P2_32 P1_31 P1_33 P1_29"
    gpioping=
else
    echo " Not Found"
    pins=""
fi

for pin in $pins
do
    echo $pin
    # config-pin $pin pruout
    config-pin -q $pin
done
