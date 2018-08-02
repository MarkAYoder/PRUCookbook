// This code drives the RGB LED Matrix
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

// These are from https://github.com/FalconChristmas/fpp/blob/master/src/pru/PocketScrollerV1.hp
// _gpio tells which gpio port and _pin tells which bit in the port
// The first 1 in r11 is for the J1 connector
// See the githuub file for the other connectors
#define r11_gpio 1
#define r11_pin 20
#define g11_gpio 1
#define g11_pin 28
#define b11_gpio 1
#define b11_pin 25

#define r12_gpio 1
#define r12_pin 26
#define g12_gpio 1
#define g12_pin 27
#define b12_gpio 1
#define b12_pin 18

#define pru_latch  0	// These are the bit positions in R30
#define pru_oe     7
#define pru_clock  1

#define pru_sel0   2	// These are called LA, LB, LC and LD in the python code
#define pru_sel1   3	// Also bit positions
#define pru_sel2   4
#define pru_sel3   5

// This is mine
#define GPIO0	0x44e07000		// GPIO Bank 0  See Table 2.2 of TRM
#define GPIO1	0x4804c000		// GPIO Bank 1
#define GPIO2	0x481ac000		// GPIO Bank 2
#define GPIO3	0x481ae000		// GPIO Bank 3
#define GPIO_CLEARDATAOUT	0x190	// For clearing the GPIO registers
#define GPIO_SETDATAOUT		0x194	// For setting the GPIO registers
#define GPIO_DATAOUT		0x138	// For reading the GPIO registers

#define DELAY 100	// Number of cycles (5ns each) to wait after a write

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	// Set up the pointers to each of the GPIO ports 
	uint32_t *gpio[] = {
			(uint32_t *)GPIO0, 
			(uint32_t *)GPIO1, 
			(uint32_t *)GPIO2, 
			(uint32_t *)GPIO3
		};
	
	uint32_t i, row;

	while(1) {
	    for(row=0; row<16; row++) {
	    	// Set the row address
			// Here we take advantage of the select bits (LA,LB,LC,LD)
			// being sequential in the R30 register (bits 2,3,4,5)
			// We shift row over so it lines up with the select bits
			// Oring (|=) with R30 sets bits to 1 and
			// Anding (&=) clears bits to 0, the 0xffc mask makes sure the
			// other bits aren't changed.
	        __R30 |=  row<<pru_sel0;
	        __R30 &= (row<<pru_sel0)|0xffc3;

    	    for(i=0; i<64; i++) {
    	    	// Top row white
    	    	// Combining these to one write works because they are all in 
    	    	// the same gpio port
    	      	gpio[r11_gpio][GPIO_SETDATAOUT/4] = (0x1<<r11_pin)
    	      			|(0x1<<g11_pin)|(0x1<<b11_pin);
    	    	__delay_cycles(DELAY);;
    	      	
    	      	// Bottom row red
    	      	gpio[r11_gpio][GPIO_SETDATAOUT/4]   = (0x1<<r12_pin);
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_CLEARDATAOUT/4] = (0x1<<g12_pin)|(0x1<<b12_pin);
    	    	__delay_cycles(DELAY);
    	      	
                __R30 |=  (0x1<<pru_clock);	// Toggle clock
    	    	__delay_cycles(DELAY);
        		__R30 &= ~(0x1<<pru_clock);
    	    	__delay_cycles(DELAY);
    	    	
    	    	// Top row black
    	    	gpio[r11_gpio][GPIO_CLEARDATAOUT/4] = (0x1<<r11_pin)
    	    			|(0x1<<g11_pin)|(0x1<<b11_pin);
    	    	__delay_cycles(DELAY);
    	      	
    	      	// Bottom row green
    	    	gpio[r11_gpio][GPIO_CLEARDATAOUT/4] = (0x1<<r12_pin)|(0x1<<b12_pin);
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_SETDATAOUT/4]   = (0x1<<g12_pin);
    	    	__delay_cycles(DELAY);
    	      	
                __R30 |=  (0x1<<pru_clock);	// Toggle clock
    	    	__delay_cycles(DELAY);
        		__R30 &= ~(0x1<<pru_clock);
    	    	__delay_cycles(DELAY);
    	    }
    	    __R30 |=  (0x1<<pru_oe);        // Disable display
    	   	__delay_cycles(DELAY);
    	    __R30 |=  (0x1<<pru_latch);     // Toggle latch
    	   	__delay_cycles(DELAY);
    	    __R30 &= ~(0x1<<pru_latch);
    	   	__delay_cycles(DELAY);
    	    __R30 &= ~(0x1<<pru_oe);        // Enable display
    	    __delay_cycles(DELAY);
	    }
	}
}
