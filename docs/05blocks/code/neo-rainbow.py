#!/usr/bin/python3
from time import sleep
import math

len = 24
amp = 12
f = 25
shift = 3
phase = 0

# Open a file
fo = open("/dev/rpmsg_pru30", "wb", 0)

while True:
    for i in range(0, len):
        r = (amp * (math.sin(2*math.pi*f*(i-phase-0*shift)/len) + 1)) + 1;
        g = (amp * (math.sin(2*math.pi*f*(i-phase-1*shift)/len) + 1)) + 1;
        b = (amp * (math.sin(2*math.pi*f*(i-phase-2*shift)/len) + 1)) + 1;
        fo.write(b"%d %d %d %d\n" % (i, r, g, b))
        # print("0 0 127 %d" % (i))

    fo.write(b"-1 0 0 0\n");
    phase = phase + 1
    sleep(0.05)

# Close opened file
fo.close()