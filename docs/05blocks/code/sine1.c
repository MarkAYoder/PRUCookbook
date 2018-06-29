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

#define MAXT	100	// Maximum number of time samples

#define SINE		// Pick which waveform

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t onCount;		// Current count
	uint32_t offCount;
	uint32_t t;
	
	// Generate a periodic sine wave in an array of 100 values - using ints
	int i;
	unsigned int waveform[MAXT];
#ifdef SINE
	float gain = 50.0f;
	float phase = 0.0f;
	float bias = 50.0f;
	float freq = 2.0f * 3.14159f / 100.0f;
	for (i=0; i<MAXT; i++){
		waveform[i] = (unsigned int)(bias + (gain * sin((i * freq) + phase)));
	}
#endif
#ifdef SAWTOOTH
	for(i=0; i<MAXT; i++) {
		waveform[i] = i;
	}
#endif
#ifdef TRIANGLE
	for(i=0; i<MAXT/2; i++) {
		waveform[i]        = 2*i;
		waveform[MAXT-i-1] = 2*i;
	}
#endif

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while (1) {
		for(t=0; t<MAXT; t++) {
			onCount = waveform[t];
			offCount = 100 - onCount;
			while(onCount | offCount) {
				if(onCount) {
					onCount--;
					__R30 |= 0x1;		// Set the GPIO pin to 1
				} else if(offCount) {
					offCount--;
					__R30 &= ~(0x1);	// Clear the GPIO pin
				}
			}
		}
	}
}
