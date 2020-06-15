// This code drives the RGB LED Matrix on J1 connector
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"
#include "rgb_pocket.h"

#define DELAY 100

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	// Set up the pointers to each of the GPIO ports 
	uint32_t *gpio[] = {
			(uint32_t *) GPIO0, 
			(uint32_t *) GPIO1, 
			(uint32_t *) GPIO2, 
			(uint32_t *) GPIO3
		};
	
	uint32_t i, row;
	
	while(1) {
	    for(row=0; row<16; row++) {
	        if(row&(0x1<<0)) __R30|=(0x1<<pru_sel0); else __R30&=~(0x1<<pru_sel0);
	        __delay_cycles(DELAY);
	        if(row&(0x1<<1)) __R30|=(0x1<<pru_sel1); else __R30&=~(0x1<<pru_sel1);
	        __delay_cycles(DELAY);
	        if(row&(0x1<<2)) __R30|=(0x1<<pru_sel2); else __R30&=~(0x1<<pru_sel2);
	        __delay_cycles(DELAY);
	        if(row&(0x1<<3)) __R30|=(0x1<<pru_sel3); else __R30&=~(0x1<<pru_sel3);
	        __delay_cycles(DELAY);
	        
    	    for(i=0; i<64; i++) {
    	    	// red
    	      	gpio[r11_gpio][GPIO_SETDATAOUT]   = r11_pin;
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_CLEARDATAOUT] = g11_pin | b11_pin;
    	    	__delay_cycles(DELAY);

				// green
    	      	gpio[r11_gpio][GPIO_CLEARDATAOUT] = r12_pin |  b12_pin;
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_SETDATAOUT]   = g12_pin;
    	    	__delay_cycles(DELAY);

                __R30 |=  pru_clock;     // Toggle clock
    	    	__delay_cycles(DELAY);
        		__R30 &= ~pru_clock;
    	    	__delay_cycles(DELAY);
    	    	
    	    	// blue
    	    	gpio[r11_gpio][GPIO_CLEARDATAOUT] = r11_pin | g11_pin;
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_SETDATAOUT]   = b11_pin;
    	    	__delay_cycles(DELAY);
    	      	
    	      	//blue
    	    	gpio[r11_gpio][GPIO_CLEARDATAOUT] = r12_pin | g12_pin;
    	    	__delay_cycles(DELAY);
    	      	gpio[r11_gpio][GPIO_SETDATAOUT]   = b12_pin;
    	    	__delay_cycles(DELAY);
    	      	
                __R30 |=  pru_clock;      // Toggle clock
    	    	__delay_cycles(DELAY);
        		__R30 &= ~pru_clock;
    	    	__delay_cycles(DELAY);
    	    }
    	    __R30 |=  pru_oe;        // Disable display
    	    	__delay_cycles(DELAY);
    	    __R30 |=  pru_latch;     // Toggle latch
    	    	__delay_cycles(DELAY);
    	    __R30 &= ~pru_latch;
    	    	__delay_cycles(DELAY);
    	    __R30 &= ~pru_oe;        // Enable display
    	    __delay_cycles(DELAY);
	    }
	}
}
