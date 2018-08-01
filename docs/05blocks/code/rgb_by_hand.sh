#!/bin/bash
# Toggle bits on RGB LED Matrix
# Run rgb_setup.sh first to configure the pins

export GPIO=/sys/class/gpio
export OE=gpio117 # P1_29
export LAT=gpio110
export CLK=gpio111
export R1=gpio52

export LA=gpio112
export LB=gpio113
export LC=gpio114
export LD=gpio115

# Enable the device
echo 1 > $GPIO/$OE/value

# Pull LAT low
echo 0 > $GPIO/$LAT/value

for i in {1..384}
do
    echo 1 > $GPIO/$R1/value
    echo 0 > $GPIO/$R1/value
    
    # Cycle clock
    echo 0 > $GPIO/$CLK/value
    echo 1 > $GPIO/$CLK/value
done

# Pull LAT high
echo 1 > $GPIO/$LAT/value
