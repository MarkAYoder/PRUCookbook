#!/bin/bash
# Setup for 64x32 RGB Matrix
export PRUN=0
export TARGET=rgb1
echo PRUN=$PRUN
echo TARGET=$TARGET

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
    prupins="P2_32 P1_31 P1_33 P1_29 P2_30 P2_34 P1_36"
    gpiopins="P2_10 P2_06 P2_04 P2_01 P2_08 P2_02"
else
    echo " Not Found"
    pins=""
fi

for pin in $prupins
do
    echo $pin
    config-pin $pin pruout
    # config-pin $pin out
    config-pin -q $pin
done

for pin in $gpiopins
do
    echo $pin
    config-pin $pin out
    config-pin -q $pin
done
