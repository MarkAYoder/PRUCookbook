// Control a ws2812 (neo pixel) display, green, red, blue, green, ...
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define	oneCyclesOn		700/5	// Stay on 700ns
#define oneCyclesOff	800/5
#define zeroCyclesOn	350/5
#define zeroCyclesOff	600/5
#define out 1		// Bit number to output one
#define STRING_LEN		24

// #define ONE

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	uint32_t color[STRING_LEN] = {0x0f000000, 0x000f0000, 0x0000f00};	// green, red, blue
	uint32_t i, j;

	for(j=0; j<3; j++) {
		for(i=31; i>=8; i--) {
			if(color[j] & (0x1<<i)) {
				__R30 |= 0x1<<out;		// Set the GPIO pin to 1
				__delay_cycles(oneCyclesOn-1);
				__R30 &= ~(0x1<<out);	// Clear the GPIO pin
				__delay_cycles(oneCyclesOff-2);
			} else {
				__R30 |= 0x1<<out;		// Set the GPIO pin to 1
				__delay_cycles(zeroCyclesOn-1);
				__R30 &= ~(0x1<<out);	// Clear the GPIO pin
				__delay_cycles(zeroCyclesOff-2);
			}
		}
	}
}
