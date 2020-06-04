// From: http://git.ti.com/pru-software-support-package/pru-software-support-package/blobs/master/examples/am335x/PRU_access_const_table/PRU_access_const_table.c
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"

#define PRU_SRAM  __far __attribute__((cregister("PRU_SHAREDMEM", near)))
#define PRU_DMEM0 __far __attribute__((cregister("PRU_DMEM_0_1",  near)))
#define PRU_DMEM1 __far __attribute__((cregister("PRU_DMEM_1_0",  near)))

/* NOTE:  Allocating shared_x to PRU Shared Memory means that other PRU cores on
 *        the same subsystem must take care not to allocate data to that memory.
 *		  Users also cannot rely on where in shared memory these variables are placed
 *        so accessing them from another PRU core or from the ARM is an undefined behavior.
 */
volatile uint32_t shared_0;
PRU_SRAM  volatile uint32_t shared_1;
PRU_DMEM0 volatile uint32_t shared_2;
PRU_DMEM1 volatile uint32_t shared_3;
#pragma DATA_SECTION(shared_4, ".bss")
volatile uint32_t shared_4;

/* NOTE:  Here we pick where in memory to store shared_5.  The stack and
 *		  heap take up the first 0x200 words, so we must start after that.
 *		  Since we are hardcoding where things are stored we can share
 *		  this between the PRUs and the ARM.
*/
#define PRU0_DRAM		0x00000			// Offset to DRAM
// Skip the first 0x200 bytes of DRAM since the Makefile allocates
// 0x100 for the STACK and 0x100 for the HEAP.
volatile unsigned int *shared_5 = (unsigned int *) (PRU0_DRAM + 0x200);


int main(void)
{
	volatile uint32_t shared_6;
	volatile uint32_t shared_7;
	/*****************************************************************/
	/* Access PRU peripherals using Constant Table & PRU header file */
	/*****************************************************************/

	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	/*****************************************************************/
	/* Access PRU Shared RAM using Constant Table                    */
	/*****************************************************************/

	/* C28 defaults to 0x00000000, we need to set bits 23:8 to 0x0100 in order to have it point to 0x00010000	 */
	PRU0_CTRL.CTPPR0_bit.C28_BLK_POINTER = 0x0100;

	shared_0 =  0xfeef;
	shared_1 = 0xdeadbeef;
	shared_2 = shared_2 + 0xfeed;
	shared_3 = 0xdeed;
	shared_4 = 0xbeed;
	shared_5[0] = 0x1234;
	shared_6 = 0x4321;
	shared_7 = 0x9876;

	/* Halt PRU core */
	__halt();
}
