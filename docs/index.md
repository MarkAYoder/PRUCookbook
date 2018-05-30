## Outline

A cookbook for programming the PRUs in C using remoteproc and 
compiling on the Beagle

[Notes](notes.md)

1. Getting started
  * Hardware:  BeagleBone family or PocketBeagle
  * Downloading and flashing current 
  * Cloud9 IDE
  * Blinking an LED
2. [Case Studies](CaseStudies.md)
{% include CaseStudies.md %}
  * MachineKit
  * LEDscape
  * Robotics Control Library
  * ArduPilot
  * BeagleLogic
3. Details on compiling and running a file
  * The standard Makefile
  * clpru and lnkpru
  * Loading firmware
4. [Debugging and Benchmarking][debug]
  * LED and switch for debugging
  * Oscilloscope
  * dmesg –Hw
  * prubug?
  * UART?
5. Building Blocks – Applications
  * PWM generator
  * Sine Wave Generator
  * Ultrasonic Sensor Application
  * neoPixel driver
6. [Accessing more I/O][io]
  * /boot/uEnv.txt to access [P8 I/O][P8]
  * Accessing gpio
  * UART?
  * ECAP/PWM?
7. Talking to the rest of the processor
  * PRU Architecture, DRAM, Shared RAM
  * interrupts to ARM
  * ARM interrupts to PRU
  * mmap() 
  * rpmsg
  * use of OCP peripherals
9. [Running on an older version][older]
10. More performance, assembly language programming

[debug]: # "Roadmap-wise, I'd want to consider how to plug RPMsg into a printf function to aide debug. I'm sure you've seen that with CCS in the past."
[common]: # "Some kind of intro to these building blocks is needed. Look at the TI examples for a good list."
[io]: # "The split with talking to the ARM is a little confusing to me as I don't know what the 'more' is."
[P8]: # "What is the P8 issue?"
[older]: # "You might make this just about *alternate* tools rather than necessarily older. You could provide relatively minimal pointers for anything beyond what is needed understand how the Case Studies work. Things like the gcc port could go here."
