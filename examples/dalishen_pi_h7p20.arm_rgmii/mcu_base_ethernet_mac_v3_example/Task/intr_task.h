#ifndef __HME_INTR_TASK_H__
#define __HME_INTR_TASK_H__

#include <stdint.h>

#define FPGA_INT_ENABLE				((volatile  uint32_t *) 0x4570041C)
#define fpga_int_bit1				(1<<1)	

extern void ex_intr_task(void);

#endif
