#!/bin/bash
# Toggle bits on RGB LED Matrix
# Run rgb_setup.sh first to configure the pins

export GPIO=/sys/class/gpio

cd $GPIO

for dir in $( ls ); do
    if [ -d $dir ]; then
        # read -n 1
        echo $dir
        cat $dir/value
        echo out > $dir/direction
        echo 1 > $dir/value
    fi
done
# export OE=gpio117 # P1_29
# export LAT=gpio110
# export CLK=gpio111

# export R1=gpio52
# export B1=gpio57
# export R2=gpio58
# export B2=gpio50
# export G1=gpio60
# export G2=gpio59

# export LA=gpio112
# export LB=gpio113
# export LC=gpio114
# export LD=gpio115

# # Switch to row 0
# ADDR=1
# echo $ADDR > $GPIO/$LA/value
# echo $ADDR > $GPIO/$LB/value
# echo $ADDR > $GPIO/$LC/value
# echo $ADDR > $GPIO/$LD/value

# # DISPLAY_ON
# echo 0 > $GPIO/$OE/value

# # while true
# # do
#     for i in {1..64}
#     do
#         echo 1 > $GPIO/$R1/value
#         echo 1 > $GPIO/$R2/value
#         echo 1 > $GPIO/$B1/value
#         echo 1 > $GPIO/$B2/value
#         echo 0 > $GPIO/$G1/value
#         echo 0 > $GPIO/$G2/value

#         # Cycle clock
#         echo 0 > $GPIO/$CLK/value
#         echo 1 > $GPIO/$CLK/value
#     done
    
#     # DISPLAY_OFF
#     echo 1 > $GPIO/$OE/value
    
#     # Pull LAT high
#     echo 1 > $GPIO/$LAT/value
    
#     # Pull LAT low
#     echo 0 > $GPIO/$LAT/value
    
#     # sleep 0.01
#     # DISPLAY_ON
#     echo 0 > $GPIO/$OE/value

#     # echo Done
# # done