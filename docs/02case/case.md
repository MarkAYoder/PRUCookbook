## Case Studies

The **P**rogrammable **R**eal-Time **U**nit (PRU) has two 32-bit cores which run
independently of the ARM processor that is running Linux.  Therefore they can
be programmed to respond quickly to inputs and produce very precisely timed 
outputs. A good way to learn how to use the PRUs is to study how others have 
used them.  Here we present some case studies that do just that.  

In these study you'll see a high-level view of using the PRUs.  In later
chapters you will see the details.

Here we present

  * Robotics Control Library [http://strawsondesign.com/docs/roboticscape/](http://strawsondesign.com/docs/roboticscape/)
  * LEDscape [https://github.com/Yona-Appletree/LEDscape](https://github.com/Yona-Appletree/LEDscape)
  * MachineKit [http://www.machinekit.io/](http://www.machinekit.io/)
  * ArduPilot [http://ardupilot.org/](http://ardupilot.org/)
  * BeagleLogic [https://github.com/abhishek-kakkar/BeagleLogic/wiki](https://github.com/abhishek-kakkar/BeagleLogic/wiki)
  
### Robotics Control Library
The Robotics Control Library is a package that contains a C library and example/testing programs for the BeagleBone Blue
and the BeagleBone Black with Robotics Cape. It uses the PRU to extend the real-time hardware of the Bone.

#### Problem
I need to control eight servos, but the Bone doesn't have enough PWMs.  

#### Solution
The Robotics Control Library provides eight additional PWM channels via the PRU that can be used out of the box.  Just run:

```bash
sudo rc_test_servos -f 10 -p 1.5
```
The `-f 10` says to use a frequency of 10 Hz and the -p 1.5` says to set the position to `1.5`.  The range of positions is
`-1.5` to `.15.   Run `rc_test_servos -h` to see all the options.

```bash
rc_test_servos -h

 Options
 -c {channel}   Specify one channel from 1-8.
                Otherwise all channels will be driven equally
 -f {hz}        Specify pulse frequency, otherwise 50hz is used
 -p {position}  Drive servo to a position between -1.5 & 1.5
 -w {width_us}  Send pulse width in microseconds (us)
 -s {limit}     Sweep servo back/forth between +- limit
                Limit can be between 0 & 1.5
 -r {ch}        Use DSM radio channel {ch} to control servo
 -h             Print this help messege 

sample use to center servo channel 1:
   rc_test_servo -c 1 -p 0.0
```
The BeagleBone Blue sends these eight outputs to it's servo channels.  The Black and the Pocket use the pins shown in this table.

|Pru pin    |Blue pin|Black pin|Pocket pin|
|-----------|--------|---------|----------|
|pru1_r30_8 |1       |P8_27    |          |
|pru1_r30_10|2       |P8_28    |P1.02     |
|pru1_r30_9 |3       |P8_29    |P1.35     |
|pru1_r30_11|4       |P8_30    |P1.04     |
|pru1_r30_6 |5       |P8_39    | |
|pru1_r30_7 |6       |P8_40    | |
|pru1_r30_4 |7       |P8_41    | |
|pru1_r30_5 |8       |P8_42    | |

This comes from: 
* [https://github.com/beagleboard/pocketbeagle/wiki/System-Reference-Manual#673_PRUICSS_Pin_Access]
(https://github.com/beagleboard/pocketbeagle/wiki/System-Reference-Manual#673_PRUICSS_Pin_Access)
* [Robotics_Cape_Installer/pru_firmware/src/pru1-servo.asm](Robotics_Cape_Installer/pru_firmware/src/pru1-servo.asm)
* [https://github.com/derekmolloy/exploringBB/blob/master/chp06/docs/BeagleboneBlackP8HeaderTable.pdf](https://github.com/derekmolloy/exploringBB/blob/master/chp06/docs/BeagleboneBlackP8HeaderTable.pdf)
* [https://github.com/derekmolloy/exploringBB/blob/master/chp06/docs/BeagleboneBlackP9HeaderTable.pdf](https://github.com/derekmolloy/exploringBB/blob/master/chp06/docs/BeagleboneBlackP9HeaderTable.pdf)

#### Discussion


#### Problem
ToDo
This is a placeholder for later.
#### Solution
One of the PRUs can be programmed to perform the function of eight PWMs.

### Discussion
This example outputs a pulse with a very stable width.  The ARM says when to start the pulse, and the PRU outputs
the pulse and turns it off after a certain number of cycles. 

Here is the code (`servo-test.c`) that runs on the ARM.

```c
{% include_relative code/servo-test.c %}
```

It uses `mmap()` to directly access the PRU Shared Memory.
The line `prusharedMem_32int_ptr[ch-1] = num_loops;` writes a value to a location based on which channel
to run.  

This c-code (`main_pru1.c') runs on PRU1. 

```c
{% include_relative code/main_pru1.c %}
```

All it does is set a flag and then call the following assembly code (`pru1-servo.asm`).

```asm
{% include_relative code/pru1-servo.asm %}
```

This is too complex to discuss right now.

### MachineKit
MachineKit is a platform for machine control applications.  It can control 
machine tools, robots, or other automated devices. It can control servo 
motors, stepper motors, relays, and other devices related to machine tools.

### LEDScape

### ArduPilot

### BeagleLogic
