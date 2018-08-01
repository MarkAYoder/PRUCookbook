#!/usr/bin/env python

import Adafruit_BBIO.GPIO as GPIO
import time

OE="P1_29"
LAT="P1_36"
CLK="P1_33"

R1="P2_10"

LA="P2_32"
LB="P2_30"
LC="P1_31"
LD="P2_34"

GPIO.setup(OE,  GPIO.OUT)
GPIO.setup(LAT, GPIO.OUT)
GPIO.setup(CLK, GPIO.OUT)

GPIO.setup(R1, GPIO.OUT)

GPIO.setup(LA, GPIO.OUT)
GPIO.setup(LB, GPIO.OUT)
GPIO.setup(LC, GPIO.OUT)
GPIO.setup(LD, GPIO.OUT)

GPIO.output(OE,  0)
GPIO.output(LAT, 0)

while True:
    for bank in range(16):
        GPIO.output(LA, bank&0x1)
        for i in range(64):
            GPIO.output(R1,  1)
    
            GPIO.output(CLK, 0)
            GPIO.output(CLK, 1)
    
            GPIO.output(R1,  0)
    
            GPIO.output(CLK, 0)
            GPIO.output(CLK, 1)
    
        GPIO.output(OE,  1)
        GPIO.output(LAT, 1)
        GPIO.output(LAT, 0)
        GPIO.output(OE,  0)
