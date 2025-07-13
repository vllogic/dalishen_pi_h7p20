#include "intr_task.h"
#include "hme_uart.h"
#include "uart_task.h"

void ex_intr_task(void)
{
	HME_UART_InitTypeDef init;

	HME_UART_StructInit(&init);
	HME_UART_Init(DEMO_UART, &init);

	*FPGA_INT_ENABLE |= fpga_int_bit1;
	NVIC_SetPriority(FP0_IRQn,0);
	NVIC_EnableIRQ(FP0_IRQn);
	
	printf("fpga interrupt test ...\r\n");	

	while(1){};
}
