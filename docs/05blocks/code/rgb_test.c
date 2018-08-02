// This code accesses GPIO without using R30 and R31
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define GPIO0	0x44e07000		// GPIO Bank 0  See Table 2.2 of TRM <1>
#define GPIO1	0x4804c000		// GPIO Bank 1
#define GPIO2	0x481ac000		// GPIO Bank 2
#define GPIO3	0x481ae000		// GPIO Bank 3
#define GPIO_CLEARDATAOUT	0x190	// For clearing the GPIO registers
#define GPIO_SETDATAOUT		0x194	// For setting the GPIO registers
#define GPIO_DATAOUT		0x138	// For reading the GPIO registers
#define P9_11	(0x1<<20)			// Bit position tied to P9_11

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t *gpio1 = (uint32_t *)GPIO1;
	
	while(1) {
		gpio1[GPIO_SETDATAOUT/4] = P9_11;
		__delay_cycles(0);
		gpio1[GPIO_CLEARDATAOUT/4] = P9_11;
		__delay_cycles(0);
	}
}
