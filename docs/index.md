## Outline

A cookbook for programming the PRUs in C using remoteproc and compiling on the Beagle.

1. Getting started
  * Hardware:  BeagleBone family or Pocket Beagle
  * Downloading and flashing current 
  * Cloud 9 IDE
  * Blinking an LED
2. [Case Studies](CaseStudies.md)
  * MachineKit
  * LEDscape
  * ArduPilot
  * BeagleLogic
3. Details on compiling and running a file
  * The standard Makefile
  * clpru and lnkpru
  * Loading firmware
4. Debugging and Benchmarking
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
6. Accessing more I/O
  * /boot/uEnv.txt to access P8 I/O
  * Accessing gpio
  * UART?
  * ECAP/PWM?
7. Talking to the ARM
  * PRU Architecture, DRAM, Shared RAM
  * mmap() 
  * rpmsg
8. Running on an older version
9. More performance, assembly language programming
