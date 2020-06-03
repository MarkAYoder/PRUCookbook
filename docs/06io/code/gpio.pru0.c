// This code accesses GPIO without using R30 and R31
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"

#define P9_11	(0x1<<30)			// Bit position tied to P9_11

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t *gpio0 = (uint32_t *)GPIO0;
	
	while(1) {
		gpio0[GPIO_SETDATAOUT] = P9_11;
		__delay_cycles(100000000);
		gpio0[GPIO_CLEARDATAOUT] = P9_11;
		__delay_cycles(100000000);
	}
}
