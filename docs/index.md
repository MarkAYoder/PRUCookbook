## Outline

A cookbook for programming the PRUs in C using remoteproc and compiling on the Beagle.

1. Getting started
  1. Hardware:  BeagleBone family or Pocket Beagle
  1. Downloading and flashing current 
  1. Cloud 9 IDE
  1. Blinking an LED
1. Case Studies
MachineKit
LEDscape
ArduPilot
BeagleLogic
1. Details on compiling and running a file
The standard Makefile
clpru and lnkpru
Loading firmware
1.  and Benchmarking
LED and switch for debugging
Oscilloscope
dmesg –Hw
prubug?
UART?
1.  Blocks – Applications
PWM generator
Sine Wave Generator
Ultrasonic Sensor Application
neoPixel driver
1. Accessing more I/O
/boot/uEnv.txt to access P8 I/O
Accessing gpio
UART?
ECAP/PWM?
1. Talking to the ARM
PRU Architecture, DRAM, Shared RAM
mmap() 
rpmsg
Running on an older version
1. More performance, assembly language programming


You can use the [editor on GitHub](https://github.com/MarkAYoder/PRUCookbook/edit/master/README.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### C

```c
#include <stdio.h>

main() {
  printf("Hello, World!\n");
}

```

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/MarkAYoder/PRUCookbook/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
