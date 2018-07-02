// Control a ws2812 (neo pixel) display, All on or all off
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define	oneCyclesOn		700/5	// Stay on 700ns
#define oneCyclesOff	800/5
#define zeroCyclesOn	350/5
#define zeroCyclesOff	600/5
#define out 1		// Bit number to output one

// #define ONE

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while (1) {
#ifdef ONE
		__R30 |= 0x1<<out;		// Set the GPIO pin to 1
		__delay_cycles(oneCyclesOn-1);
		__R30 &= ~(0x1<<out);	// Clear the GPIO pin
		__delay_cycles(oneCyclesOff-2);
#else
		__R30 |= 0x1<<out;		// Set the GPIO pin to 1
		__delay_cycles(zeroCyclesOn-1);
		__R30 &= ~(0x1<<out);	// Clear the GPIO pin
		__delay_cycles(zeroCyclesOff-2);
#endif
	}
}
