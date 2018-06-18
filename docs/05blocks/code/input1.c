#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t led;
	uint32_t sw;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	led = 0x1<<0;	// P9_31 or P1_36
	sw  = 0x1<<7;	// P9_25 or P1_29
		
	while (1) {
		if((__R31&sw) == sw) {
			__R30 |= led;		// Turn on LED
		} else
			__R30 &= ~led;		// Turn off LED
	}
}

