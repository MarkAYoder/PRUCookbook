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
One of the PRUs can be programmed to perform the function of eight PWMs.

### Discussion
This example outputs a pulse with a very stable width.  The ARM says when to start the pulse, and the PRU outputs
the pulse and turns it off after a certain number of cycles. 

Here is the code (`servo-test.c`)that runs on the ARM.

```c
{% include_relative code/servo-test.c %}
```

It uses `mmap()` to directly access the PRU Shared Memory.
The line `prusharedMem_32int_ptr[ch-1] = num_loops;` writes a value to a location based on which channel
to run.  

This c-code runs on PRU1. 

```c
{% include_relative code/main_pru1.c %}
```

All it does is set a flag and then call the following assembly code.

```asm
{% include_relative code/main_pru1.c %}
```

This is too complex to discuss right now.

### MachineKit
MachineKit is a platform for machine control applications.  It can control 
machine tools, robots, or other automated devices. It can control servo 
motors, stepper motors, relays, and other devices related to machine tools.

### LEDScape

### ArduPilot

### BeagleLogic
