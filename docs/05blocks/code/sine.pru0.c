// Generate an analog waveform and use a filter to reconstruct it.
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include <math.h>

#define MAXT	100	// Maximum number of time samples
#define SAWTOOTH	// Pick which waveform

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t onCount;		// Current count for 1 out
	uint32_t offCount;		// count for 0 out
	uint32_t i;
	uint32_t waveform[MAXT]; // Waveform to be produced

	// Generate a periodic wave in an array of MAXT values
#ifdef SAWTOOTH
	for(i=0; i<MAXT; i++) {
		waveform[i] = i*100/MAXT;
	}
#endif
#ifdef TRIANGLE
	for(i=0; i<MAXT/2; i++) {
		waveform[i]        = 2*i*100/MAXT;
		waveform[MAXT-i-1] = 2*i*100/MAXT;
	}
#endif
#ifdef SINE
	float gain = 50.0f;
	float bias = 50.0f;
	float freq = 2.0f * 3.14159f / MAXT;
	for (i=0; i<MAXT; i++){
		waveform[i] = (uint32_t)(bias+gain*sin(i*freq));
	}
#endif

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while (1) {
		// Generate a PWM signal whose duty cycle matches
		// the amplitude of the signal.
		for(i=0; i<MAXT; i++) {
			onCount = waveform[i];
			offCount = 100 - onCount;
			while(onCount--) {
				__R30 |= 0x1;		// Set the GPIO pin to 1
			}
			while(offCount--) {
				__R30 &= ~(0x1);	// Clear the GPIO pin
			}
		}
	}
}
