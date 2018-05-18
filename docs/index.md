## Outline

A cookbook for programming the PRUs in C using remoteproc and compiling on the Beagle.

1. Getting started
  * Hardware:  BeagleBone family or Pocket Beagle
  * Downloading and flashing current 
  * Cloud 9 IDE
  * Blinking an LED
1. Case Studies
  * MachineKit
  * LEDscape
  * ArduPilot
  * BeagleLogic
1. Details on compiling and running a file
  * The standard Makefile
  * clpru and lnkpru
  * Loading firmware
1.  and Benchmarking
  * LED and switch for debugging
  * Oscilloscope
  * dmesg –Hw
  * prubug?
  * UART?
1.  Blocks – Applications
  * PWM generator
  * Sine Wave Generator
  * Ultrasonic Sensor Application
  * neoPixel driver
1. Accessing more I/O
  * /boot/uEnv.txt to access P8 I/O
  * Accessing gpio
  * UART?
  * ECAP/PWM?
1. Talking to the ARM
  * PRU Architecture, DRAM, Shared RAM
  * mmap() 
  * rpmsg
1. Running on an older version
1. More performance, assembly language programming
