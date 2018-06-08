## Building Blocks - Applications

Here are some examples that use the basic PRU building blocks.

### PWM generator
One of the simplest things a PRU can to is generate a simple
**p**ulse **w**idth **m**odulated signal.  Here we'll solve a series of
problems starting with a single channel PWM that has a fixed frequency and
duty cycle and ending with a multi channel PWM that the ARM can change
the frequency and duty cycle on the fly.

#### Problem
I want to generate a PWM signal that has a fixed frequency and duty cycle.

#### Solution
The solution is fairly easy, but be sure to check the **Discussion** section
for details on making it work.

Here's the code (`pwm1.c`).

```c
{% include_relative code/pwm1.c %}
```

#### Discussion
Since this is our first example we'll discuss the many parts in detail.
##### pwm1.c
Here's a line-by-line expanation of the c code.

|Line|Explantion|
|----|----------|
|1   |Standard c-header include|
|2   |Include for the PRU.  The compiler know where to find this since the Makefile says to look for includes in `/usr/lib/ti/pru-software-support-package`|
|3   |The file `resource_table_empty.h` is used by the PRU loader.  Generally we'll use the same file, but don't need to modify it.|

Here's what's in `resource_table_empty.h`
```c
{% include_relative code/resource_table_empty.h %}
```

|Line|Explantion|
|----|----------|
|5-6 |`__R30` and `__R31` are two variables that refer to the PRU output (`__R30`) and input (`__R31`) registers. When you write something to `__R30` it will show up on the corresponding output pins.  When you read from `__RR31` you read the data on the input pins.  NOTE:  Both names begin with two underscore's. Section 5.7.2 of the [PRU Optimizing C/C++ Compiler, v2.2, User's Guide](http://www.ti.com/lit/ug/spruhv7b/spruhv7b.pdf) gives more details.|
|13    |`CT_CFG.SYSCFG_bit.STANDBY_INIT` is set to `0` to enable the OCP master port. More details on this and thousands of other regesters see the [AM335x Technical Reference Manual](https://www.ti.com/lit/ug/spruh73p/spruh73p.pdf). Section 4 is on the PRU and section 4.5 gives details for all the registers.|
|15    |This line selects which GPIO pin to toggle.  The table below shows which bits in `__R30` map to which pins|

Bit 0 is the LSB.

|PRU|Bit|Black pin|Blue pin|Pocket pin|
|---|---|---------|--------|----------|
|0  |0  |P9_31    |        |P1.16     |
|0  |1  |P9_29    |        |P1.33     |
|0  |2  |P9_30    |        |P2.32     |
|0  |3  |P9_28    |        |P2.30     |
|0  |4  |P9_92    |        |P1.31     |
|0  |5  |P9_27    |        |P2.34     |
|0  |6  |P9_91    |        |P2.28     |
|0  |7  |P9_25    |        |P1.29     |
|0  |14 |P8_12    |        |P2.24     |
|0  |15 |P8_11    |        |P2.33     |

### Sine Wave Generator
### Ultrasonic Sensor Application
### neoPixel driver
