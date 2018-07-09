// Control a ws2812 (neo pixel) display, All on or all off
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"

#define out 1		// Bit number to output on

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	// These will be kept in registers and never witten to DRAM
	uint32_t cycle, stall;

	// Clear SYSCFG[STANDBY_INIT] to enable OCP master port
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	PRU0_CTRL.CTRL_bit.CTR_EN = 1;	// Enable cycle counter

	__R30 |= 0x1<<out;			// Set the GPIO pin to 1
	// Reset cycle counter, cycle is on the right side to force the compiler
	// to put it in it's own register
	PRU0_CTRL.CYCLE = cycle;
	__R30 &= ~(0x1<<out);		// Clear the GPIO pin
	cycle = PRU0_CTRL.CYCLE;	// Read cycle and store in a register
	stall = PRU0_CTRL.STALL;	// Ditto for stall

	__halt();
}
