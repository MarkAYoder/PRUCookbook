## Building Blocks - Applications

Here are some examples that use the basic PRU building blocks.

### PWM generator
One of the simplest things a PRU can to is generate a simple
**p**ulse **w**width **m**odulated signal.  Here we'll solve a series of
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


### Sine Wave Generator
### Ultrasonic Sensor Application
### neoPixel driver
