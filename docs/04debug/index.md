## Debugging and Benchmarking

Here's where we learn how to debug. On of the challenges is getting debug
information out without slowing the real-time execution.

### LED and switch for debugging
### Oscilloscope
### dmesg –Hw

#### Problem
I'm getting an error message (`/sys/devices/platform/ocp/4a326000.pruss-soc-bus/4a300000.pruss/4a334000.pru0/remoteproc/remoteproc1/state: Invalid argument`)
when I load my code, but don't know what's causing it.

#### Solution
The command `dmesg` outputs usefull information when dealing with the kernel.
Simplying running `dmesg -H` can tell you a lot.  The `-H` flag puts the
dates in the human readable for.  Often I'll have a window open running `dmesg -Hw`;
the `-w` tells it to wait for more information.

Here's what `dmesg` said for the example above.

```
[  +0.000018] remoteproc remoteproc1: header-less resource table
[  +0.011879] remoteproc remoteproc1: Failed to find resource table
[  +0.008770] remoteproc remoteproc1: Boot failed: -22
```
It quickly told me I needed to add the line `#include "resource_table_empty.h"`
to my code.

### prubug?
### UART

One simple, get effective approach is taking from the Adruino playbook; 
use the UART (serial port) to output debug information.  