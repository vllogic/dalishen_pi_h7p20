#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dma_task.h"

#define TRANSFER_SIZE 		1024
#define TOTAL_TIME		 	TRANSFER_SIZE
extern volatile bool dma_flag;

uint8_t src_arry[TRANSFER_SIZE];
uint8_t dst_arry[TRANSFER_SIZE];

#if 1
int DMA_Mem_to_Mem()
{
	int i;
	HME_DMAC_InitTypeDef dmainit;
	
	 ;
	dma_flag = FALSE;

	NVIC_EnableIRQ(DMAC_IRQn);

	for(i=0;i<128;i++)
	{
		src_arry[i] = i;
		dst_arry[i] = 0;
	}
	
	//dma mem to mem cfg
	HME_DMA_ENABLE_INTR(DMAC,0);
			
	dmainit.transtype 		= Dmac_mem2mem_dma;
	dmainit.SRC_ADDR 		= (uint32_t *)src_arry;
	dmainit.TAR_ADDR 		= (uint32_t *)dst_arry;
	dmainit.SINC 			= Dmac_addr_increment;
	dmainit.DINC 			= Dmac_addr_increment;
	dmainit.BLOCK_TS 		= TRANSFER_SIZE;
	dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_32;
	dmainit.DST_TR_WIDTH 	= Dmac_trans_width_32;
	dmainit.SRC_MSIZE 		= Dmac_msize_4;
	dmainit.DEST_MSIZE 		= Dmac_msize_4;

	HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
	
	//enable dma channel 
	HME_DMA_CFGREG(DMAC,0x1);
	HME_DMA_CHENREG(DMAC,0x101);
	
	while(1)						//wait dma transfer complete
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
		
	delay_t(100);
	if(memcmp(src_arry,dst_arry,TRANSFER_SIZE) != 0)
	{	
		return 0;
	}

	return 1 ;
}
#endif
#if 0
int DMA_Mem_to_Mem()
{
	int i,j;
	HME_DMAC_InitTypeDef dmainit;

	dma_flag = FALSE;

	NVIC_EnableIRQ(DMAC_IRQn);
	
   
	
	for(i=0;i<1024;i++)
	{
		src_arry[i] = rand()%256;;
		dst_arry[i] = 0;
	}
	
	// ICODE AREA
	for(j=0;j<TRANSFER_SIZE;j++)
	{
		//dma mem to mem cfg
		HME_DMA_ENABLE_INTR(DMAC,0);
				
		dmainit.transtype 		= Dmac_mem2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)src_arry;
		dmainit.TAR_ADDR 		= (uint32_t *)(0x20000+j*TRANSFER_SIZE);
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= TRANSFER_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_4;
		dmainit.DEST_MSIZE 		= Dmac_msize_4;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(1)						//wait dma transfer complete
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
		
		
		
		
		
		
		dmainit.transtype 		= Dmac_mem2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)(0x20000+j*TRANSFER_SIZE);
		dmainit.TAR_ADDR 		= (uint32_t *)dst_arry;
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= TRANSFER_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_4;
		dmainit.DEST_MSIZE 		= Dmac_msize_4;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(1)						//wait dma transfer complete
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
		
		
		
		
		
		if(memcmp(src_arry,dst_arry,TRANSFER_SIZE) != 0)
		{	
			return 0;
		}
		
		if(j==TRANSFER_SIZE-1)
			dma_flag = FALSE;
		memset(dst_arry,0,TRANSFER_SIZE);
		
	}
	
	// DCODE AREA
	for(j=0;j<TRANSFER_SIZE;j++)
	{
		//dma mem to mem cfg
		HME_DMA_ENABLE_INTR(DMAC,0);
				
		dmainit.transtype 		= Dmac_mem2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)src_arry;
		dmainit.TAR_ADDR 		= (uint32_t *)(0x10020000+j*TRANSFER_SIZE);
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= TRANSFER_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_4;
		dmainit.DEST_MSIZE 		= Dmac_msize_4;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(1)						//wait dma transfer complete
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
		
		
		
		
		
		
		dmainit.transtype 		= Dmac_mem2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)(0x10020000+j*TRANSFER_SIZE);
		dmainit.TAR_ADDR 		= (uint32_t *)dst_arry;
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= TRANSFER_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_4;
		dmainit.DEST_MSIZE 		= Dmac_msize_4;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(1)						//wait dma transfer complete
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
		
		
		
		
		
		if(memcmp(src_arry,dst_arry,TRANSFER_SIZE) != 0)
		{	
			return 0;
		}
		
		if(j==TRANSFER_SIZE-1)
			dma_flag = FALSE;
		memset(dst_arry,0,TRANSFER_SIZE);
		
	}
	
	delay_t(100);
	

	return 1 ;
}
#endif
