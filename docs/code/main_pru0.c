#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_pru0.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

#define LED (0x1<<5)
#define SW (0x1<<3)

/*
 * main.c
 */
int main(void)
{
	/* GPI Mode 0, GPO Mode 0 */
	CT_CFG.GPCFG0 = 0;

	while (1) {
		if(!(__R31 & SW)) {
			__R30 ^= LED;
			// __delay_cycles(10000000); // half-second delay
			__delay_cycles(1); // half-second delay
		}
	}
}
