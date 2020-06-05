// Version of xout.c with code to use CYCLE to count cycle times.
#include <stdint.h>
#include <pru_intc.h>
#include <pru_ctrl.h>
#include "resource_table_pru0.h"

#define PRU0

volatile register uint32_t __R30;
volatile register uint32_t __R31;

typedef struct {
	uint32_t reg5;
	uint32_t reg6;
	uint32_t reg7;
	uint32_t reg8;
	uint32_t reg9;
	uint32_t reg10;
} bufferData;

bufferData dmemBuf;

/* PRU-to-ARM interrupt */
#define PRU1_PRU0_INTERRUPT (18)
#define PRU0_ARM_INTERRUPT (19+16)

void main(void)
{
	uint32_t cycleXX;		// Use a name that's easy to search
	/* Clear the status of all interrupts */
	CT_INTC.SECR0 = 0xFFFFFFFF;
	CT_INTC.SECR1 = 0xFFFFFFFF;
	
	/* Load the buffer with default values to transfer */
	dmemBuf.reg5 = 0xDEADBEEF;
	dmemBuf.reg6 = 0xAAAAAAAA;
	dmemBuf.reg7 = 0x12345678;
	dmemBuf.reg8 = 0xBBBBBBBB;
	dmemBuf.reg9 = 0x87654321;
	dmemBuf.reg10 = 0xCCCCCCCC;

	/* Poll until R31.30 (PRU0 interrupt) is set
	 * This signals PRU1 is initialized */
	while ((__R31 & (1<<30)) == 0) {
	}

	/* XFR registers R5-R10 from PRU0 to PRU1 */
	/* 14 is the device_id that signifies a PRU to PRU transfer */
	PRU0_CTRL.CTRL_bit.CTR_EN = 1;	// Enable cycle counter

	__xout(14, 5, 0, dmemBuf);
	
	cycleXX = PRU0_CTRL.CYCLE;	// Read cycle and store in a register

	/* Clear the status of the interrupt */
	CT_INTC.SICR = PRU1_PRU0_INTERRUPT;

	dmemBuf.reg5 = cycleXX;

	/* Halt the PRU core */
	__halt();
}
