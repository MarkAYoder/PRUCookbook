// From: http://git.ti.com/pru-software-support-package/pru-software-support-package/trees/master/examples/am335x/PRU_Direct_Connect1
#include <stdint.h>
#include "resource_table_empty.h"

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
#define PRU1_ARM_INTERRUPT (20+16)

void main(void)
{
	/* Let PRU0 know that I am awake */
	__R31 = PRU1_PRU0_INTERRUPT+16;

	/* XFR registers R5-R10 from PRU0 to PRU1 */
	/* 14 is the device_id that signifies a PRU to PRU transfer */
	__xin(14, 5, 0, dmemBuf);

	/* Halt the PRU core */
	__halt();
}
