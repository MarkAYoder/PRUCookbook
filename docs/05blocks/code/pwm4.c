// This code does three parallel PWM channels.
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t gpio;
	uint32_t ch;
	uint32_t on[] = {1, 2, 3};
	uint32_t off[] = {3, 2, 1};
	uint32_t onCount[3], offCount[3];

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	onCount[ch] = on[ch];
	offCount[ch]= off[ch];

	while (1) {
		ch=0;
		if(onCount[ch]) {
			onCount[ch]--;
			__R30 |= 0x1<<ch;		// Set the GPIO pin to 1
		} else if(offCount[ch]) {
			offCount[ch]--;
			__R30 &= ~(0x1<<ch);		// Clear the GPIO pin
		} else {
			onCount[ch] = on[ch];
			offCount[ch]= off[ch];
		}
		ch=1;
		if(onCount[ch]) {
			onCount[ch]--;
			__R30 |= 0x1<<ch;		// Set the GPIO pin to 1
		} else if(offCount[ch]) {
			offCount[ch]--;
			__R30 &= ~(0x1<<ch);		// Clear the GPIO pin
		} else {
			onCount[ch] = on[ch];
			offCount[ch]= off[ch];
		}
		ch=2;
		if(onCount[ch]) {
			onCount[ch]--;
			__R30 |= 0x1<<ch;		// Set the GPIO pin to 1
		} else if(offCount[ch]) {
			offCount[ch]--;
			__R30 &= ~(0x1<<ch);		// Clear the GPIO pin
		} else {
			onCount[ch] = on[ch];
			offCount[ch]= off[ch];
		}
	}
}
