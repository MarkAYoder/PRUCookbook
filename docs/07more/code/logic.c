// Access the CYCLE and STALL registers
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	// Copy lower 8 bits to r16
	struct {
	    uint8_t b0;
	    uint8_t b1;
	    uint8_t b2;
	    uint8_t b3;
	} r17;

	// Clear SYSCFG[STANDBY_INIT] to enable OCP master port
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
// 	r16.b0 = __R31.b0;
	__asm(" mov r17.b0, r31.b0");
	__delay_cycles(1);
	r17.b1 = (uint32_t) __R31;
	__delay_cycles(1);
	r17.b2 = (uint32_t) __R31;
	__delay_cycles(1);
	r17.b3 = (uint32_t) __R31;

    __xout(10, 16, 0, r17);

	__halt();
}
