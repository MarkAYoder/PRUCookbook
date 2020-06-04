// This code does MAXCH parallel PWM channels.
// It's period is 510ns.
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

#define PRU0_DRAM		0x00000			// Offset to DRAM
// Skip the first 0x200 byte of DRAM since the Makefile allocates
// 0x100 for the STACK and 0x100 for the HEAP.
volatile unsigned int *pru0_dram = (unsigned int *) (PRU0_DRAM + 0x200);

#define MAXCH	4	// Maximum number of channels per PRU

#define update(ch) \
			if(onCount[ch]) {			\
				onCount[ch]--;			\
				__R30 |= 0x1<<ch;		\
			} else if(offCount[ch]) {	\
				offCount[ch]--;			\
				__R30 &= ~(0x1<<ch);	\
			} else {					\
				onCount[ch] = pru0_dram[2*ch];	\
				offCount[ch]= pru0_dram[2*ch+1];	\
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
		pru0_dram[2*ch  ] = on[ch];		// Copy to DRAM0 so the ARM can change it
		pru0_dram[2*ch+1] = off[ch];	// Interleave the on and off values
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
