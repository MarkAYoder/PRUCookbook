// Control a ws2812 (neo pixel) display, green, red, blue, green, ...
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"

#define STR_LEN 24
#define	oneCyclesOn		700/5	// Stay on 700ns
#define oneCyclesOff	800/5
#define zeroCyclesOn	350/5
#define zeroCyclesOff	600/5
#define resetCycles		60000/5	// Must be at least 50u, use 60u
#define gpio P9_16				// output pin

#define SPEED 20000000/5		// Time to wait between updates

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t background = 0x00000f;
	uint32_t foreground = 0x000f00;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	uint32_t color[STR_LEN];	// green, red, blue
	int i, j;
	int k, oldk = 0;;
	// Set everything to background
	for(i=0; i<STR_LEN; i++) {
		color[i] = background;
	}
	
	while(1) {
		// Move forward one position
		for(k=0; k<STR_LEN; k++) {
			color[oldk] = background;
			color[k]    = foreground;
			oldk=k;

			// Output the string
			for(j=0; j<STR_LEN; j++) {
				for(i=23; i>=0; i--) {
					if(color[j] & (0x1<<i)) {
						__R30 |= gpio;		// Set the GPIO pin to 1
						__delay_cycles(oneCyclesOn-1);
						__R30 &= ~gpio;		// Clear the GPIO pin
						__delay_cycles(oneCyclesOff-2);
					} else {
						__R30 |= gpio;		// Set the GPIO pin to 1
						__delay_cycles(zeroCyclesOn-1);
						__R30 &= ~gpio;		// Clear the GPIO pin
						__delay_cycles(zeroCyclesOff-2);
					}
				}
			}
			// Send Reset
			__R30 &= ~gpio;	// Clear the GPIO pin
			__delay_cycles(resetCycles);

			// Wait
			__delay_cycles(SPEED);
		}
	}
}
