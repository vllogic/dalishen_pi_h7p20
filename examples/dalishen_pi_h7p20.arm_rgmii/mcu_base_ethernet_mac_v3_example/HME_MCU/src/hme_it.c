#include "hme_it.h"

/***************************************** gpio0 interrupt handle function ************************/
void GPIO0_Handler(void)
{
    uint32_t status = HME_GPIO_GetITStatus(DEMO_GPIO);

	HME_GPIO_ClearITPendingBit(DEMO_GPIO,status);

    if (status & GPIO_PIN0) {
        HME_GPIO_Toggle(DEMO_GPIO, GPIO_PIN1);
    }
}

/***************************************** dma interrupt handle function ************************/
volatile bool dma_flag = false;

void DMAC_Handler()
{
	uint32_t state;
	state = HME_DMAC_GETINTSTATE(DMAC);
	
	if(state&0x01)
	{
		HME_DMAC_CLEARTFR(DMAC,0x1);
		dma_flag = TRUE;
	}	
}

/***************************************** uart interrupt handle function ************************/

extern volatile bool isDone;
extern uint8_t ubuf[133];
extern uint8_t uartRnum;

void DEMO_UART_IRQHandler(void)
{
    uint32_t iid = HME_UART_GetAndCleanITStatus(DEMO_UART);

    switch (iid) {
        case UART_IIR_MODEM_STATUS:
            break;

        case UART_IIR_THR_EMPTY:
            isDone = true;
            break;
		
#if UART_IRQ_FOR_ISP
		
		case UART_IIR_RECEIVED_DATA_AVAILABLE: {
            if (1 == HME_UART_ReceiveData(DEMO_UART, 1, ubuf+uartRnum)) {			
				uartRnum ++;
            }
            break;
        } 	
		
#else		
		
		case UART_IIR_RECEIVED_DATA_AVAILABLE:{
            uint8_t c_read = 0;
            if (1 == HME_UART_ReceiveData(DEMO_UART, 1, &c_read)) {
                while (1 != HME_UART_SendData(DEMO_UART, 1, &c_read));
            }
            break;
        }  
		
#endif
		
        case UART_IIR_RECEIVED_LINE_STATUS:
            break;

        case UART_IIR_BUSY_DETECT:
            break;

        case UART_IIR_CHARACTER_TIMEOUT:
            break;

        default:
            hme_assert(0);
    }
}

/***************************************** spi master interrupt handle function ************************/
#if SPI_MASTER_MODE
void DEMO_SPI_IRQHanlder()
{
	bool rxfifoInt_flag = 0;
	bool txfifoInt_flag = 0;
	bool endInt_flag 	= 0;
	
	if(HME_SPI_GetITStatus(DEMO_SPI,SPI_INT_STATUS_RXFIFOInt))
	{
		HME_SPI_ClearITPendingBit(DEMO_SPI,SPI_INT_STATUS_RXFIFOInt);
		rxfifoInt_flag = 1;
	}
	if(HME_SPI_GetITStatus(DEMO_SPI,SPI_INT_STATUS_TXFIFOInt))
	{
		HME_SPI_ClearITPendingBit(DEMO_SPI,SPI_INT_STATUS_TXFIFOInt);
		txfifoInt_flag = 1;
	}
	if(HME_SPI_GetITStatus(DEMO_SPI,SPI_INT_STATUS_EndInt))
	{
		HME_SPI_ClearITPendingBit(DEMO_SPI,SPI_INT_STATUS_EndInt);
		endInt_flag 	= 1;
	}
}
#endif

/***************************************** spi slave interrupt handle function ************************/
#if SPI_SLAVE_MODE

extern spi_slave_t spi_slave_dev;

void SPI0_Handler(void)
{
	spi0_slave_isr(&spi_slave_dev);
}
#endif

/***************************************** timer interrupt handle function ************************/
__USED uint32_t __counter[8];

void DEMO_TIMER_IRQHanlder(void)
{
    uint32_t status = HME_TIM_GetAllITStatus(DEMO_TIMER_GROUP);
    hme_assert((status & 0xFF) != 0);

    if (status & (1 << TIMER_0)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_0);
        __counter[0]++;
    }

    if (status & (1 << TIMER_1)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_1);
        __counter[1]++;
    }
	
	  if (status & (1 << TIMER_2)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_2);
        __counter[2]++;
    }
	
	if (status & (1 << TIMER_3)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_3);
        __counter[3]++;
    }

    if (status & (1 << TIMER_4)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_4);
        __counter[4]++;
    }
	
	if (status & (1 << TIMER_5)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_5);
        __counter[5]++;
    }
	
	if (status & (1 << TIMER_6)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_6);
        __counter[6]++;
    }

    if (status & (1 << TIMER_7)) {
        HME_TIM_ClearITPendingBit(DEMO_TIMER_GROUP,TIMER_7);
        __counter[7]++;
    }
}

/***************************************** wdt interrupt handle function ************************/
volatile bool wdt_isDone = false;;

static uint32_t cnt;

void WDT_Handler(void)
{
    HME_WDT_ClearITPendingBit();
    wdt_isDone = true;

    cnt++;
}

/***************************************** fpga external interrupt handle function **************/
/*
void FP0_IRQHandler()
{
	static uint32_t num0;
	printf("fp intr0 : %d\r\n",num0);
	num0++;
}
*/
