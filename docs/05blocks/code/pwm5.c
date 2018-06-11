// This code does three parallel PWM channels.
// It's period is 1.9 us
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define MAXCH	4	// Maximum number of channels

#define update(ch) \
			if(onCount[ch]) {			\
				onCount[ch]--;			\
				__R30 |= 0x1<<ch;		\
			} else if(offCount[ch]) {	\
				offCount[ch]--;			\
				__R30 &= ~(0x1<<ch);	\
			} else {					\
				onCount[ch] = on[ch];	\
				offCount[ch]= off[ch];	\
			}

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t ch;
	uint32_t on[]  = {1, 2, 3, 4};
	uint32_t off[] = {4, 3, 2, 1};
	uint32_t onCount[MAXCH], offCount[MAXCH];

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

#pragma UNROLL(MAXCH)
	for(ch=0; ch<MAXCH; ch++) {
		onCount[ch] = on[ch];
		offCount[ch]= off[ch];
	}

	while (1) {
		update(0)
		update(1)
		update(2)
		update(3)
	}
}
