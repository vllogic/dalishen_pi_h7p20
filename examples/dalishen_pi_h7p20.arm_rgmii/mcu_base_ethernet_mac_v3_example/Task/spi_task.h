#ifndef __HME_SPI_TASK_H__
#define __HME_SPI_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_spiflash.h"
#include "sys_reg.h"

#ifndef DEMO_SPI_NUM
#    define DEMO_SPI_NUM  3
#endif

#if DEMO_SPI_NUM == 0
# define DEMO_SPI            	SPI0           	//common interface
# define DEMO_SPI_IRQn       	SPI0_IRQn
# define DEMO_SPI_IRQHanlder 	SPI0_Handler
# define DMA_SPI_TX_REQ 		10
# define DMA_SPI_RX_REQ 		11
#elif DEMO_SPI_NUM == 1
# define DEMO_SPI            	SPI1			//common interface
# define DEMO_SPI_IRQn       	SPI1_IRQn
# define DEMO_SPI_IRQHanlder 	SPI1_Handler
# define DMA_SPI_TX_REQ 		12
# define DMA_SPI_RX_REQ 		13
#elif DEMO_SPI_NUM == 2
# define DEMO_SPI            	SPI2			//common interface
# define DEMO_SPI_IRQn       	SPI2_IRQn
# define DEMO_SPI_IRQHanlder 	SPI2_Handler
#elif DEMO_SPI_NUM == 3
# define DEMO_SPI            	QSPI          	//connect flash
# define DEMO_SPI_IRQn       	QSPI_IRQn
# define DEMO_SPI_IRQHanlder 	QSPI_Handler
# define DMA_SPI_TX_REQ 		14
# define DMA_SPI_RX_REQ 		15
#endif


#define SPI_MASTER_MODE				1
#define SPI_SLAVE_MODE				0

//master function

extern void Spiflash_Quad_Task(void);
extern void Spiflash_Quad_DMA_Task(void);
extern void Spiflash_Single_Task(void);
extern void Spiflash_Single_INT_Task(void);
extern void Spiflash_Single_DMA_Task(void);
extern void Flash_PageWr_SPISingle_withDMA(void);
extern void Flash_PageRd_SPISingle_withDMA(void);

//slave function
extern void SPI_Slave_DataOnly_R(void);


#endif
