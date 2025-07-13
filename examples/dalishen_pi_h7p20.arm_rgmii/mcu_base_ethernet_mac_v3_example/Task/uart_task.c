#include "uart_task.h"

extern volatile bool dma_flag;
volatile bool isDone = false;

void uart_TXInt_task(void)
{
	uint8_t c = 'a';

    HME_UART_InitTypeDef init;

    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    NVIC_EnableIRQ(DEMO_UART_IRQn);

    while (1) {
        HME_UART_ITConfig(DEMO_UART, UART_Int_Transmit_Holding_Empty, true);

        while (1 != HME_UART_SendData(DEMO_UART, 1, &c));
        while (!isDone);
        HME_UART_ITConfig(DEMO_UART, UART_Int_Transmit_Holding_Empty, false);
        isDone = false;

        if (c == 'z') {
            c = 'a';
        } else {
            c++;
        }
    }
}

void uart_RXInt_task(void)
{
    HME_UART_InitTypeDef init;

    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    NVIC_EnableIRQ(DEMO_UART_IRQn);
    
    HME_UART_ITConfig(DEMO_UART, UART_Int_Received_Data_Available, true);

    while (1);
	
}

void uart_echo_task(void)
{
	uint8_t c_read = 0;

    HME_UART_InitTypeDef init;

    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    while (1) {
        while (1 != HME_UART_ReceiveData(DEMO_UART, 1, &c_read));
        while (1 != HME_UART_SendData(DEMO_UART, 1, &c_read));
    }
}

void uart_DMATX_task(void)
{
	uint8_t i;
	volatile uint8_t outDataab[128];
	
    HME_UART_InitTypeDef init;
	HME_DMAC_InitTypeDef dmainit;

	dma_flag = FALSE;
	
    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    NVIC_EnableIRQ(DMAC_IRQn);

	for (i = 0; i < 128; i++) {
		outDataab[i] = i;
	}
	
	{
		//dma mem to per cfg		
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype 		= Dmac_mem2prf_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)outDataab;
		dmainit.TAR_ADDR 		= (uint32_t *)(&(UART0->THR));
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_nochange;
		dmainit.BLOCK_TS 		= 64;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.TX_REQ_NUM		= DMA_UART_TX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_TXMode;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);

		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
			
		while(1)	//wait dma transfer complete
		{
			if(dma_flag == TRUE)
			{
				dma_flag = FALSE;
				break;
			}
		}
		HME_DMA_ENABLE_INTR(DMAC,0);	
		HME_DMA_CFGREG(DMAC,0x0);
		HME_DMA_CHENREG(DMAC,0x100);
	}
}

void uart_DMARX_task(void)
{
	uint8_t i;
	volatile uint8_t rx_buf[16];
	
    HME_UART_InitTypeDef init;
	HME_DMAC_InitTypeDef dmainit;

	dma_flag = FALSE;
	
    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    NVIC_EnableIRQ(DMAC_IRQn);

	for (i = 0; i < 128; i++) {
			rx_buf[i] = 0;
	}


	{
		//dma mem to per cfg		
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype = Dmac_prf2mem_dma;
		dmainit.SRC_ADDR = (uint32_t *)&(UART0->RBR);
		dmainit.TAR_ADDR = (uint32_t *)(rx_buf);
		dmainit.SINC =	Dmac_addr_nochange;
		dmainit.DINC =  Dmac_addr_increment;
		dmainit.BLOCK_TS =  16;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.RX_REQ_NUM		= DMA_UART_RX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_RXMode;
		
		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
			
		while(1)	//wait dma transfer complete
		{
			if(dma_flag == TRUE)
			{
				dma_flag = FALSE;
				break;
			}
		}
		HME_DMA_ENABLE_INTR(DMAC,0);	
		HME_DMA_CFGREG(DMAC,0x0);
		HME_DMA_CHENREG(DMAC,0x100);
	}
}
