// Shows how to call an assembly routine with a return value
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"

#define	TEST	100

// The function is defined in delay.asm in same dir
// We just need to add a declaration here, the defination can be
// seperately linked
extern uint32_t my_delay_cycles(uint32_t);

uint32_t ret;

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t gpio = P9_31;	// Select which pin to toggle.;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while(1) {
		__R30 |= gpio;		// Set the GPIO pin to 1
		ret = my_delay_cycles(1);
		__R30 &= ~gpio;		// Clear the GPIO pin
		ret = my_delay_cycles(1);
	}
}
