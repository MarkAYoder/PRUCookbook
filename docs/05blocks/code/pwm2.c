#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t gpio;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	gpio = 0x0001;	// Select which pin to toggle.

	while (1) {
		__R30 |= gpio;		// Set the GPIO pin to 1
		__delay_cycles(1);	// Delay one cycle to correct for loop time
		__R30 &= ~gpio;		// Clear the GPIO pin
		__delay_cycles(0);
	}
}

