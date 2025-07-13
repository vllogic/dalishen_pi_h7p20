#ifndef __HME_UART_TASK_H__
#define __HME_UART_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_uart.h"
#include "hme_dma.h"
#include "sys_reg.h"

#ifndef DEMO_UART_NUM
# define DEMO_UART_NUM 			0
#endif

#if DEMO_UART_NUM == 0
# define DEMO_UART            	UART0
# define DEMO_UART_IRQn       	UART0_IRQn
# define DEMO_UART_IRQHandler 	UART0_Handler
# define DMA_UART_TX_REQ      	6
# define DMA_UART_RX_REQ 		7
#elif DEMO_UART_NUM == 1
# define DEMO_UART            	UART1
# define DEMO_UART_IRQn       	UART1_IRQn
# define DEMO_UART_IRQHandler 	UART1_Handler
# define DMA_UART_TX_REQ      	8
# define DMA_UART_RX_REQ 		9
#elif DEMO_UART_NUM == 2
# define DEMO_UART            	UART2
# define DEMO_UART_IRQn       	UART2_IRQn
# define DEMO_UART_IRQHandler 	UART2_Handler
#endif


extern void uart_DMARX_task(void);
extern void uart_DMATX_task(void);
extern void uart_TXInt_task(void);
extern void uart_RXInt_task(void);
extern void uart_echo_task(void);

#endif
