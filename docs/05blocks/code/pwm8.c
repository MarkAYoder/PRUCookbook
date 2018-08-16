// This code does MAXCH parallel PWM channels on both PRU 0 and PRU 1
// All channels start at the same time. 
// It's period is 430ns
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"

#define PRU0_DRAM		0x00000			// Offset to DRAM
// Skip the first 0x200 byte of DRAM since the Makefile allocates
// 0x100 for the STACK and 0x100 for the HEAP.
volatile unsigned int *pru0_dram = (unsigned int *) (PRU0_DRAM + 0x200);

#define MAXCH	2	// Maximum number of channels per PRU

#define update(ch) \
			if(onCount[ch]) {			\
				onCount[ch]--;			\
				Rtmp |= 0x1<<ch;		\
			} else if(offCount[ch]) {	\
				offCount[ch]--;			\
				Rtmp &= ~(0x1<<ch);	\
			} else {					\
				onCount[ch] = pru0_dram[2*ch];	\
				offCount[ch]= pru0_dram[2*ch+1];	\
			}

volatile register uint32_t __R30;
volatile register uint32_t __R31;

// Initialize interupts so the PRUs can be syncronized.
// PRU1 is started first and then waits for PRU0
// PRU0 is then started and tells PRU1 when to start going
#if PRUN==0
void configIntc(void) {	
	__R31 = 0x00000000;					// Clear any pending PRU-generated events
	CT_INTC.CMR4_bit.CH_MAP_16 = 1;		// Map event 16 to channel 1
	CT_INTC.HMR0_bit.HINT_MAP_1 = 1;	// Map channel 1 to host 1
	CT_INTC.SICR = 16;					// Ensure event 16 is cleared
	CT_INTC.EISR = 16;					// Enable event 16
	CT_INTC.HIEISR |= (1 << 0);			// Enable Host interrupt 1
	CT_INTC.GER = 1; 					// Globally enable host interrupts
}
#endif

void main(void)
{
	uint32_t ch;
	uint32_t on[]  = {1, 2, 3, 4};
	uint32_t off[] = {4, 3, 2, 1};
	uint32_t onCount[MAXCH], offCount[MAXCH];
	register uint32_t Rtmp;

#if PRUN==0
	CT_CFG.GPCFG0 = 0x0000;				// Configure GPI and GPO as Mode 0 (Direct Connect)
	configIntc();						// Configure INTC
#endif

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

#pragma UNROLL(MAXCH)
	for(ch=0; ch<MAXCH; ch++) {
		pru0_dram[2*ch  ] = on [ch+PRUN*MAXCH];	// Copy to DRAM0 so the ARM can change it
		pru0_dram[2*ch+1] = off[ch+PRUN*MAXCH];	// Interleave the on and off values
		onCount[ch] = on [ch+PRUN*MAXCH];
		offCount[ch]= off[ch+PRUN*MAXCH];
	}
	Rtmp = __R30;

	while (1) {
#if PRUN==1
		while((__R31 & (0x1<<31))==0) {		// Wait for PRU 0
		}
		CT_INTC.SICR = 16;					// Clear event 16
#endif
		__R30 = Rtmp;
		update(0)
		update(1)
#if PRUN==0
#define PRU0_PRU1_EVT 16
		__R31 = (PRU0_PRU1_EVT-16) | (0x1<<5);	//Tell PRU 1 to start
		__delay_cycles(1);
#endif
	}
}
