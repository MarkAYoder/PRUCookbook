#!/usr/bin/env python
import Adafruit_BBIO.GPIO as GPIO

OE="P1_29"
LAT="P1_36"
CLK="P1_33"

R1="P2_10"
R2="P2_4"
B1="P2_6"
B2="P2_1"
G1="P2_8"
G2="P2_2"

LA="P2_32"
LB="P2_30"
LC="P1_31"
LD="P2_34"

GPIO.setup(OE,  GPIO.OUT)
GPIO.setup(LAT, GPIO.OUT)
GPIO.setup(CLK, GPIO.OUT)

GPIO.setup(R1, GPIO.OUT)
GPIO.setup(R2, GPIO.OUT)
GPIO.setup(B1, GPIO.OUT)
GPIO.setup(B2, GPIO.OUT)
GPIO.setup(G1, GPIO.OUT)
GPIO.setup(G2, GPIO.OUT)

GPIO.setup(LA, GPIO.OUT)
GPIO.setup(LB, GPIO.OUT)
GPIO.setup(LC, GPIO.OUT)
GPIO.setup(LD, GPIO.OUT)

GPIO.output(OE,  0)
GPIO.output(LAT, 0)

while True:
    for bank in range(16):
        GPIO.output(LA, bank>>0&0x1)    # Select rows
        GPIO.output(LB, bank>>1&0x1)
        GPIO.output(LC, bank>>2&0x1)
        GPIO.output(LD, bank>>3&0x1)
        for i in range(16):
            GPIO.output(R1,  1)     # Top row
            GPIO.output(B1,  1)
            GPIO.output(G1,  1)
            
            GPIO.output(R2,  1)     # Bottom row
            GPIO.output(B2,  0)
            GPIO.output(G2,  0)

            GPIO.output(CLK, 0)     # Toggle clock
            GPIO.output(CLK, 1)
    
            GPIO.output(R1,  0)     # Top row
            GPIO.output(B1,  0)
            GPIO.output(G1,  0)
            GPIO.output(R2,  0)     # Bottom row
            GPIO.output(B2,  0)
            GPIO.output(G2,  1)
    
            GPIO.output(CLK, 0)     # Toggle clock
            GPIO.output(CLK, 1)
    
        GPIO.output(OE,  1)     # Disable display
        GPIO.output(LAT, 1)     # Toggle latch
        GPIO.output(LAT, 0)
        GPIO.output(OE,  0)     # Enable display
