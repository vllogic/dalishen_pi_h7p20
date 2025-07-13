#ifndef __HME_I2C_TASK_H__
#define __HME_I2C_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_i2c.h"
#include "hme_dma.h"
#include "sys_reg.h"

#ifndef DEMO_I2C_NUM
#    define DEMO_I2C_NUM 0
#endif

#if DEMO_I2C_NUM == 0
#    define DEMO_I2C            I2C0
#    define DEMO_I2C_IRQn       I2C0_IRQn
#    define DEMO_I2C_IRQHanlder I2C0_Handler
# 	 define DMA_I2C_TX_REQ 		0
# 	 define DMA_I2C_RX_REQ 		1
#elif DEMO_I2C_NUM == 1
#    define DEMO_I2C            I2C1
#    define DEMO_I2C_IRQn       I2C1_IRQn
#    define DEMO_I2C_IRQHanlder I2C1_Handler
# 	 define DMA_I2C_TX_REQ 		2
# 	 define DMA_I2C_RX_REQ 		3
#endif

// 1010 A2 A1 A0
#define E2PROM_ADDRESS               	0x50
#define E2PROM_PAGE_SIZE             	32
#define E2PROM_SLAVE_ADDR            	0x48

#define I2C_MASTER_MODE 				1		//1: master mode ;  0: slave mode
#define I2C_SLAVE_MODE 					0

#define PRINTF_LOG						0

extern int I2C_Master_Wr_Rd_EEPROM_AT24C256_task(void);
extern int I2C_Master_Wr_Rd_EEPROM_AT24C256_ByDMA_task(void);
extern int I2C_Master_Wr_Rd_EEPROM_AT24C256_Interrupt_task(void);
extern void I2C_Slave_Mode_Recieve_task(void);
extern void I2C_Slave_Mode_Feedback_Interrupt_task(void);


#endif
