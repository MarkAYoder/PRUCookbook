#!/bin/bash
# Toggle bits on RGB LED Matrix
# Run rgb_setup.sh first to configure the pins

export GPIO=/sys/class/gpio
export OE=$GPIO/gpio117 # P1_29
export LAT=$GPIO/gpio110
export CLK=$GPIO/gpio111

export R1=$GPIO/gpio52
export B1=$GPIO/gpio57
export R2=$GPIO/gpio58
export B2=$GPIO/gpio50
export G1=$GPIO/gpio60
export G2=$GPIO/gpio59

export LA=$GPIO/gpio112
export LB=$GPIO/gpio113
export LC=$GPIO/gpio114
export LD=$GPIO/gpio115

# Switch to row 0
ADDR=0
echo $ADDR > $LA/value
echo $ADDR > $LB/value
echo $ADDR > $LC/value
echo $ADDR > $LD/value

# DISPLAY_ON
echo 0 > $OE/value
# Pull LAT low
echo 0 > $LAT/value


# while true
# do
    for i in {1..64}
    do
        echo 0 > $R1/value
        echo 0 > $R2/value
        echo 0 > $B1/value
        echo 0 > $B2/value
        echo 1 > $G1/value
        echo 1 > $G2/value

        # Cycle clock
        echo 0 > $CLK/value
        echo 1 > $CLK/value
        
        echo 1 > $R1/value
        echo 1 > $R2/value
        echo 0 > $B1/value
        echo 0 > $B2/value
        echo 0 > $G1/value
        echo 0 > $G2/value

        # Cycle clock
        echo 0 > $CLK/value
        echo 1 > $CLK/value
    done
    
    # DISPLAY_OFF
    echo 1 > $OE/value
    
    # Pull LAT high
    echo 1 > $LAT/value
    
    # Pull LAT low
    echo 0 > $LAT/value
    
    # DISPLAY_ON
    echo 0 > $OE/value

    # echo Done
# done