// Control a ws2812 (neo pixel) display, All on or all off
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"

#define out 1		// Bit number to output on

volatile register uint32_t __R30;
volatile register uint32_t __R31;

volatile uint32_t cycle, stall;		// volatile forces it to DRAM

void main(void)
{
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	PRU0_CTRL.CTRL_bit.CTR_EN = 1;	// Enable cycle counter

	while(1) {
		__R30 |= 0x1<<out;			// Set the GPIO pin to 1
		PRU0_CTRL.CYCLE = 0;		// Reset cycle counter
		__R30 &= ~(0x1<<out);		// Clear the GPIO pin
		cycle = PRU0_CTRL.CYCLE;	// Read cycles and store in DRAM
		stall = PRU0_CTRL.STALL;
	}
}
