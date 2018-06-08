#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	volatile uint32_t gpio;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/* Toggle GPO pins TODO: Figure out which to use */
	gpio = 0x0001;

	/* TODO: Create stop condition, else it will toggle indefinitely */
	while (1) {
		__R30 ^= gpio;
		__delay_cycles(100000000);
	}
}

