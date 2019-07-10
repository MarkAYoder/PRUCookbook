#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define GPIO1 0x4804C000
#define GPIO2 0x48055000
#define GPIO3 0x48057000
#define GPIO4 0x48059000
#define GPIO5 0x4805B000
#define GPIO6 0x4805D000
#define GPIO7 0x48051000
#define GPIO8 0x48053000
#define GPIO_CLEARDATAOUT 0x190
#define GPIO_SETDATAOUT 0x194
// GPIO3
#define USR0 (1<<17)
#define USR2 (1<<15)
#define USR3 (1<<14)
#define USR4 (1<< 7)
// GPIO5
#define USR1 (1<< 5)


unsigned int volatile * const GPIO1_CLEAR = (unsigned int *) (GPIO3 + GPIO_CLEARDATAOUT);
unsigned int volatile * const GPIO1_SET   = (unsigned int *) (GPIO3 + GPIO_SETDATAOUT);

volatile register unsigned int __R30;
volatile register unsigned int __R31;

void main(void) {
	int i;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	for(i=0; i<5; i++) {
		*GPIO1_SET = USR3;      // The the USR3 LED on
		__delay_cycles(500000000/5);    // Wait 1/2 second

		*GPIO1_CLEAR = USR3;
		 __delay_cycles(500000000/5); 
	}
	__halt();
}
