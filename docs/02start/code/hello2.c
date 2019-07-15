#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#pragma DATA_SECTION(init_pins, ".init_pins")
#pragma RETAIN(init_pins)
const char init_pins[] =  
	"/sys/class/leds/beaglebone:green:usr1/trigger\0none\0" \
	"/sys/class/leds/beaglebone:green:usr2/trigger\0none\0" \
	"/sys/class/leds/beaglebone:green:usr3/trigger\0none\0" \
	"\0\0";

#if AI == 1
#warning "Found AI"
#define GPIO1 0x4AE10000
#define GPIO2 0x48055000
#define GPIO3 0x48057000
#define GPIO4 0x48059000
#define GPIO5 0x4805B000
#define GPIO6 0x4805D000
#define GPIO7 0x48051000
#define GPIO8 0x48053000
// GPIO3
#define USR0 (1<<17)
#define USR2 (1<<15)
#define USR3 (1<<14)
#define USR4 (1<< 7)
// GPIO5
#define USR1 (1<< 5)
// R30 bits - Output on pru1_1
#define P9_14	(0x1<<14)
#define P9_16	(0x1<<15)
#define P8_15	(0x1<<16)
#define P8_26	(0x1<<17)
#define P8_16	(0x1<<18)
// R31 bits - Input on pru1_1
#define P8_18	(0x1<<5)
#define P8_19	(0x1<<6)
#define P8_13	(0x1<<7)

#else

#warning "Found else"
#define GPIO0 0x44E09000
#define GPIO1 0x4804C000
#define GPIO2 0x481AC000
#define GPIO3 0x481AE000

// GPIO 1
#define USR0 (1<<21)
#define USR1 (1<<22)
#define USR2 (1<<23)
#define USR3 (1<<24)

#endif

#define GPIO_CLEARDATAOUT	0x190/4	// /4 to convert from byte address to word address
#define GPIO_SETDATAOUT 	0x194/4
#define GPIO_DATAOUT		0x138/4   // For reading the GPIO registers

volatile register unsigned int __R30;
volatile register unsigned int __R31;

void main(void) {
	int i;
	
	// uint32_t *gpio1 = (uint32_t *)GPIO1;
	// uint32_t *gpio2 = (uint32_t *)GPIO2;
	uint32_t *gpio3 = (uint32_t *)GPIO3;
	// uint32_t *gpio4 = (uint32_t *)GPIO4;
	uint32_t *gpio5 = (uint32_t *)GPIO5;
	// uint32_t *gpio6 = (uint32_t *)GPIO6;
	// uint32_t *gpio7 = (uint32_t *)GPIO7;
	// uint32_t *gpio8 = (uint32_t *)GPIO8;
	
	// Select which pins to toggle.  These are all on pru1_1
	uint32_t gpio = P9_14 | P9_16 | P8_15 | P8_16 | P8_26;

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	for(i=0; i<10; i++) {
		gpio5[GPIO_SETDATAOUT]   = USR1;			// The the USR3 LED on
		gpio3[GPIO_CLEARDATAOUT] = USR2;
		// gpio4[GPIO_SETDATAOUT]   = (1<<29);
		// gpio8[GPIO_SETDATAOUT]   = (1<<18);
		// gpio4[GPIO_SETDATAOUT]   = (1<<28);
		// gpio6[GPIO_SETDATAOUT]   = (1<<17);
		
		__R30 |= gpio;		// Set the GPIO pin to 1

		__delay_cycles(500000000/5);    // Wait 1/2 second

		gpio5[GPIO_CLEARDATAOUT] = USR1;
        gpio3[GPIO_SETDATAOUT]   = USR2;
		// gpio4[GPIO_CLEARDATAOUT] = (1<<29);
		// gpio8[GPIO_CLEARDATAOUT] = (1<<18);
		// gpio4[GPIO_CLEARDATAOUT] = (1<<28);
		// gpio6[GPIO_CLEARDATAOUT] = (1<<17);
		
		__R30 &= ~gpio;		// Clearn the GPIO pin

		__delay_cycles(500000000/5); 
		
		if((__R31&P8_19) == P8_19) {
            gpio3[GPIO_CLEARDATAOUT]   = USR3;      // Turn on LED
        } else
            gpio3[GPIO_SETDATAOUT]     = USR3;      // Turn off LED
	}
	__halt();
}
