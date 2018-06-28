// Generates a signusoid.
// 
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include <math.h>

#define PRU0_DRAM		0x00000			// Offset to DRAM
// Skip the first 0x200 byte of DRAM since the Makefile allocates
// 0x100 for the STACK and 0x100 for the HEAP.
volatile unsigned int *pru0_dram = (unsigned int *) (PRU0_DRAM + 0x200);

#define MAXCH	4	// Maximum number of channels per PRU

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t ch;
	uint32_t on[]  = {1, 2, 3, 4};	// Number of cycles to stay on
	uint32_t off[] = {4, 3, 2, 1};	// Number to stay off
	uint32_t onCount[MAXCH];		// Current count
	uint32_t offCount[MAXCH];
	
	// Generate a periodic sine wave in an array of 100 values - using ints
	int i;
	unsigned int waveform[100];
	float gain = 50.0f;
	float phase = 0.0f;
	float bias = 50.0f;
	float freq = 2.0f * 3.14159f / 100.0f;
	for (i=0; i<100; i++){
	  waveform[i] = (unsigned int)(bias + (gain * sin((i * freq) + phase)));
	}

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	// Initialize the channel counters.
	for(ch=0; ch<MAXCH; ch++) {
		pru0_dram[2*ch  ] = on[ch];		// Copy to DRAM0 so the ARM can change it
		pru0_dram[2*ch+1] = off[ch];	// Interleave the on and off values
		onCount[ch] = on[ch];
		offCount[ch]= off[ch];
	}

	while (1) {
		for(ch=0; ch<MAXCH; ch++) {
			if(onCount[ch]) {
				onCount[ch]--;
				__R30 |= 0x1<<ch;		// Set the GPIO pin to 1
			} else if(offCount[ch]) {
				offCount[ch]--;
				__R30 &= ~(0x1<<ch);	// Clear the GPIO pin
			} else {
				onCount[ch] = pru0_dram[2*ch];		// Read from DRAM0
				offCount[ch]= pru0_dram[2*ch+1];
			}
		}
	}
}
