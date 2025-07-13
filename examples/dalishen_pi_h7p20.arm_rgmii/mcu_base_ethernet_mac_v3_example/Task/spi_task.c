#include "spi_task.h"

#define FLASH_TRANS_SIZE 		256
#define FLASH_ADDR_OFFSET 		0x0F0000

extern volatile bool dma_flag;

void Spiflash_Quad_DMA_Task()
{
	uint8_t real_getdata[FLASH_TRANS_SIZE*4];
	volatile uint32_t txDataBuf[FLASH_TRANS_SIZE];
	volatile uint32_t InCount = 0;
	volatile HME_DMAC_InitTypeDef dmainit;
	uint32_t i,j,index;
	volatile uint32_t rxDataBuf[FLASH_TRANS_SIZE];
	volatile SPI_InitTypeDef spi_init_struct;
	
	dma_flag = FALSE;
	
	NVIC_EnableIRQ(DMAC_IRQn);
	
	for (i = 0; i < FLASH_TRANS_SIZE; i++) {
		txDataBuf[i] =  FLASH_TRANS_SIZE - i;
	}
	
	memset(real_getdata,0,FLASH_TRANS_SIZE*4);
	
	//wr test
	{
		spiFlashEraseSector(FLASH_ADDR_OFFSET);
		spiFlashQE();
		spiFlashWrEn();

		//param init			
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_32bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Write_only;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Quad_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	0;
		spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;

		
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);
		SPI_SET_TX_DMA(DEMO_SPI,TRUE);
	
		//dma mem to per cfg		
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype 		= Dmac_mem2prf_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)txDataBuf;
		dmainit.TAR_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_nochange;
		dmainit.BLOCK_TS 		= 64;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_32;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_32;
		dmainit.SRC_MSIZE 		= Dmac_msize_32;
		dmainit.DEST_MSIZE 		= Dmac_msize_32;
		dmainit.TX_REQ_NUM		= DMA_SPI_TX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_TXMode;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		SPI_Set_Cmd(DEMO_SPI,0x32);								//start transfer	

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
	
	delay_t(5000);delay_t(5000);delay_t(5000);

	//rd test
	{		
		SPI_Set_DualQuad_Mode(DEMO_SPI,SPI_data_phase_format_Single_mode);
		spiFlashQE();
		
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_32bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Dummy_Read;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Quad_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	FLASH_TRANS_SIZE-1;
		spi_init_struct.WrTranCnt			=	0;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;
		
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);		
		SPI_SET_RX_DMA(DEMO_SPI,TRUE);
		
		//dma per to mem cfg	
		dmainit.transtype 		= Dmac_prf2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));
		dmainit.TAR_ADDR 		= (uint32_t *)rxDataBuf;
		dmainit.SINC 			= Dmac_addr_nochange;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= 64;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_32;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_32;
		dmainit.SRC_MSIZE 		= Dmac_msize_32;
		dmainit.DEST_MSIZE 		= Dmac_msize_32;
		dmainit.RX_REQ_NUM		= DMA_SPI_RX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_RXMode;
		
		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
	
		//enable spi dma revieve	
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
	
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		SPI_Set_Cmd(DEMO_SPI,0x6B);								//start transfer

		while(1)   												//wait dma transfer complete
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

	delay_t(5000);delay_t(5000);delay_t(5000);
	
	index=0;
	for(i=0;i<FLASH_TRANS_SIZE;i++)
	{
		for(j=0;j<4;j++)
		{
			real_getdata[index] = (rxDataBuf[i] & 0xFF000000) >> 24;
			index++;
			rxDataBuf[i] = rxDataBuf[i] << 8;
		}
	}	
	delay_t(5000);
	return;
}

void Spiflash_Quad_Task()
{
	uint32_t data[FLASH_TRANS_SIZE];
	uint8_t txDataBuf[FLASH_TRANS_SIZE];
	uint8_t real_getdata[FLASH_TRANS_SIZE];
	uint8_t index=0;
	uint32_t i,j;
	SPI_InitTypeDef spi_init_struct;
	
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		data[i] = 0;
	
	memset(real_getdata,0,FLASH_TRANS_SIZE);

	for(i=0;i<FLASH_TRANS_SIZE;i++)
		txDataBuf[i] = FLASH_TRANS_SIZE - i;

	//wr test
	{			
		//1 erase flash	
		spiFlashEraseSector(FLASH_ADDR_OFFSET);
		spiFlashQE();		
		spiFlashWrEn();
	
		//param init
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Write_only;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Quad_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	0;
		spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;
		
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);
		
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		
		SPI_Set_Cmd(DEMO_SPI,0x32);								//start transfer
		
		SPI_SendData(DEMO_SPI, txDataBuf, (spi_init_struct.WrTranCnt+1));
	}
	
	delay_t(5000);delay_t(5000);delay_t(5000);
	
	//rd test
	{	
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_32bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Dummy_Read;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Quad_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	0x0F;
		spi_init_struct.WrTranCnt			=	0;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;
			
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);	
		
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		
		SPI_Set_Cmd(DEMO_SPI,0x6B);								//start transfer
			
		SPI_RecieveData(DEMO_SPI, data, (spi_init_struct.RdTranCnt+1));
	}

	delay_t(5000);
	
	for(i=0;i<FLASH_TRANS_SIZE;i++)								//get real data
	{
		for(j=0;j<4;j++)
		{
			real_getdata[index] = (data[i] & 0xFF000000) >> 24;
			index++;
			data[i] = data[i] << 8;
		}
	}	
	
	delay_t(5000);
	return;
}
	
void Spiflash_Single_DMA_Task()
{
	volatile uint8_t txDataBuf[FLASH_TRANS_SIZE];
	volatile uint8_t real_getdata[FLASH_TRANS_SIZE];
	volatile HME_DMAC_InitTypeDef dmainit;
	volatile SPI_InitTypeDef spi_init_struct;
	uint32_t i;
	volatile uint8_t rxDataBuf[FLASH_TRANS_SIZE];

	dma_flag = FALSE;
	
	NVIC_EnableIRQ(DMAC_IRQn);
	//NVIC_EnableIRQ(QSPI_IRQn);
	
	for (i = 0; i < FLASH_TRANS_SIZE; i++) {
		txDataBuf[i] =  FLASH_TRANS_SIZE - i;
	}

	//wr test
	{
		spiFlashEraseSector(FLASH_ADDR_OFFSET);
		spiFlashWrEn();
		
		//param init
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Write_only;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	0;
		spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;
		
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);
		SPI_SET_TX_DMA(DEMO_SPI,TRUE);

		//dma mem to per cfg		
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype 		= Dmac_mem2prf_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)txDataBuf;
		dmainit.TAR_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));//0x5100F02C;
		dmainit.SINC 			= Dmac_addr_increment;
		dmainit.DINC 			= Dmac_addr_nochange;
		dmainit.BLOCK_TS 		= FLASH_TRANS_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.TX_REQ_NUM		= DMA_SPI_TX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_TXMode;
		
		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);

		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);

		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		SPI_Set_Cmd(DEMO_SPI,0x02);								//start transfer
				
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
	
	delay_t(5000);
	
	//rd test
	{	
		spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
		spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
		spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
		spi_init_struct.Mode				=	SPI_MasterMode;
		spi_init_struct.CPOL				=	0;						
		spi_init_struct.CPHA				=	0;	
		spi_init_struct.TransMode 			=	SPI_Transfermode_Read_only;		
		spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
		spi_init_struct.DummyCnt 			=	0;
		spi_init_struct.RdTranCnt			=	FLASH_TRANS_SIZE-1;
		spi_init_struct.WrTranCnt			=	0;
		spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
		spi_init_struct.SCLK_DIV			=	1;
		
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);		
		SPI_SET_RX_DMA(DEMO_SPI,TRUE);
	
		//dma per to mem cfg		
		dmainit.transtype 		= Dmac_prf2mem_dma;
		dmainit.SRC_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));//0x5100F02C;
		dmainit.TAR_ADDR 		= (uint32_t *)rxDataBuf;
		dmainit.SINC 			= Dmac_addr_nochange;
		dmainit.DINC 			= Dmac_addr_increment;
		dmainit.BLOCK_TS 		= FLASH_TRANS_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.RX_REQ_NUM		= DMA_SPI_RX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_RXMode;
		
		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
	
		//enable spi dma revieve	
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); //wait for spi controller idle
		SPI_Set_Cmd(DEMO_SPI,0x03);								//start transfer
		
		while(1)   												//wait dma transfer complete
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
		
	delay_t(100);
	return;
}


void Spiflash_Single_Task(void)
{
	volatile uint8_t txDataBuf[FLASH_TRANS_SIZE];
	volatile uint32_t rxData[FLASH_TRANS_SIZE];
	volatile uint8_t data[FLASH_TRANS_SIZE];
	volatile uint32_t i=0;
	SPI_InitTypeDef spi_init_struct;

	for(i=0;i<FLASH_TRANS_SIZE;i++)
		txDataBuf[i] = i;
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		rxData[i] = 0;
	
	spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
	spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
	spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
	spi_init_struct.Mode				=	SPI_MasterMode;
	spi_init_struct.CPOL				=	0;						
	spi_init_struct.CPHA				=	0;	
	spi_init_struct.TransMode 			=	SPI_Transfermode_Write_read_same_time;		
	spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
	spi_init_struct.DummyCnt 			=	0;
	spi_init_struct.RdTranCnt			=	0;
	spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
	spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
	spi_init_struct.SCLK_DIV			=	7;
	
	HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);

	spiFlashEraseSector(FLASH_ADDR_OFFSET);
	
	spiFlashPageRead((uint32_t *)rxData,FLASH_ADDR_OFFSET,FLASH_TRANS_SIZE);
	
	spiFlashPageProgram((uint8_t *)txDataBuf,FLASH_ADDR_OFFSET,FLASH_TRANS_SIZE);
	
	spiFlashPageRead((uint32_t *)rxData,FLASH_ADDR_OFFSET,FLASH_TRANS_SIZE);
	
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		data[i] = rxData[i] & 0xFF;
		
	return;
}

void Spiflash_Single_INT_Task(void)
{
	volatile uint8_t txDataBuf[FLASH_TRANS_SIZE];
	volatile uint32_t rxData[FLASH_TRANS_SIZE];
	volatile uint8_t data[FLASH_TRANS_SIZE];
	volatile uint32_t i=0;
	SPI_InitTypeDef spi_init_struct;
	
	NVIC_EnableIRQ(DEMO_SPI_IRQn);
	
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		txDataBuf[i] = i;
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		rxData[i] = 0;
	
	spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
	spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
	spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
	spi_init_struct.Mode				=	SPI_MasterMode;
	spi_init_struct.CPOL				=	0;						
	spi_init_struct.CPHA				=	0;	
	spi_init_struct.TransMode 			=	SPI_Transfermode_Write_read_same_time;		
	spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
	spi_init_struct.DummyCnt 			=	0;
	spi_init_struct.RdTranCnt			=	0;
	spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
	spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
	spi_init_struct.SCLK_DIV			=	1;
	
	HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);
	
	SPI_Set_TransThreshold(DEMO_SPI,1);
	
	SPI_Set_RecvThreshold(DEMO_SPI,1);
	
	spiFlashEraseSector(FLASH_ADDR_OFFSET);

	spiFlashPageRead((uint32_t *)rxData,FLASH_ADDR_OFFSET,64);
	
	spiFlashPageProgram((uint8_t *)txDataBuf,FLASH_ADDR_OFFSET,64);
	
	spiFlashPageRead((uint32_t *)rxData,FLASH_ADDR_OFFSET,64);
	
	for(i=0;i<FLASH_TRANS_SIZE;i++)
		data[i] = rxData[i] & 0xFF;
		
	return;
}

volatile uint8_t txDataBuf[FLASH_TRANS_SIZE];
void Flash_PageWr_SPISingle_withDMA()
{
	volatile HME_DMAC_InitTypeDef dmainit;
	volatile SPI_InitTypeDef spi_init_struct,r_spi_init_struct;
	uint32_t i;
	uint8_t j;
	
	dma_flag = FALSE;
	
	NVIC_EnableIRQ(DMAC_IRQn);
	
	for (i = 0; i < FLASH_TRANS_SIZE; i++) {
		txDataBuf[i] =  i;
	}
	
	spiFlashEraseSector(FLASH_ADDR_OFFSET);	//erase before write data to flash
		
	//spi param init
	spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
	spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
	spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
	spi_init_struct.Mode				=	SPI_MasterMode;
	spi_init_struct.CPOL				=	0;						
	spi_init_struct.CPHA				=	0;	
	spi_init_struct.TransMode 			=	SPI_Transfermode_Write_only;		
	spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
	spi_init_struct.DummyCnt 			=	0;
	spi_init_struct.RdTranCnt			=	0;
	spi_init_struct.WrTranCnt			=	FLASH_TRANS_SIZE-1;;
	spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
	spi_init_struct.SCLK_DIV			=	3;
	
	//dma param init
	dmainit.transtype 		= Dmac_mem2prf_dma;
	dmainit.SRC_ADDR 		= (uint32_t *)txDataBuf;
	dmainit.TAR_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));//0x5100F02C;
	dmainit.SINC 			= Dmac_addr_increment;
	dmainit.DINC 			= Dmac_addr_nochange;
	dmainit.BLOCK_TS 		= FLASH_TRANS_SIZE;
	dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
	dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
	dmainit.SRC_MSIZE 		= Dmac_msize_1;
	dmainit.DEST_MSIZE 		= Dmac_msize_1;
	dmainit.TX_REQ_NUM		= DMA_SPI_TX_REQ;
	dmainit.TRANS_DIR		= HME_DMAC_TXMode;
	
	SPI_Set_TransThreshold(DEMO_SPI,1);
	SPI_SET_TX_DMA(DEMO_SPI,TRUE);
	
	for(j=0;j<16;j++)
	{	
		spiFlashWrEn();							//Wr enable
		spi_init_struct.SPI_SlaveAddr =	FLASH_ADDR_OFFSET+j*FLASH_TRANS_SIZE;// 1 sector = 16 page,  1 page = 256Byte
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);//SPI_SlaveAddr change, need to init spi once more

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		HME_DMAC_ENABLE(DMAC);										//enable dma channel 

		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); 	//wait for spi controller idle
		SPI_Set_Cmd(DEMO_SPI,0x02);									//start transfer,0x02 : flash page write 
				
		while(!dma_flag){};   										//wait dma transfer complete
		dma_flag = FALSE;
		
		HME_DMA_ENABLE_INTR(DMAC,0);	
		HME_DMAC_DISABLE(DMAC);
		
		delay_t(100);
	}
	
	SPI_SET_TX_DMA(DEMO_SPI,FALSE);
	
	return;
}

uint8_t rxDataBuf[FLASH_TRANS_SIZE];
void Flash_PageRd_SPISingle_withDMA(void)
{
	volatile HME_DMAC_InitTypeDef dmainit;
	volatile SPI_InitTypeDef spi_init_struct;
	uint8_t j;
	//uint8_t rxDataBuf[FLASH_TRANS_SIZE];

	dma_flag = FALSE;
	
	NVIC_EnableIRQ(DMAC_IRQn);
	
	//spi init cfg
	spi_init_struct.AddrLen  			=	SPI_AddrLen_3Byte;		
	spi_init_struct.DataLen				=	SPI_Data_Width_8bit;		
	spi_init_struct.DataMerge			=	SPI_DataMerge_Disable;	
	spi_init_struct.Mode				=	SPI_MasterMode;
	spi_init_struct.CPOL				=	0;						
	spi_init_struct.CPHA				=	0;	
	spi_init_struct.TransMode 			=	SPI_Transfermode_Read_only;		
	spi_init_struct.DualQuad 			=	SPI_data_phase_format_Single_mode;	
	spi_init_struct.DummyCnt 			=	0;
	spi_init_struct.RdTranCnt			=	FLASH_TRANS_SIZE-1;
	spi_init_struct.WrTranCnt			=	0;
	spi_init_struct.SPI_SlaveAddr 		=	FLASH_ADDR_OFFSET;
	spi_init_struct.SCLK_DIV			=	1;
	
	//dma peripheral to memory cfg		
	dmainit.transtype 		= Dmac_prf2mem_dma;
	dmainit.SRC_ADDR 		= (uint32_t *)(&(DEMO_SPI->Data));
	dmainit.TAR_ADDR 		= (uint32_t *)rxDataBuf;
	dmainit.SINC 			= Dmac_addr_nochange;
	dmainit.DINC 			= Dmac_addr_increment;
	dmainit.BLOCK_TS 		= FLASH_TRANS_SIZE;
	dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
	dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
	dmainit.SRC_MSIZE 		= Dmac_msize_1;
	dmainit.DEST_MSIZE 		= Dmac_msize_1;
	dmainit.RX_REQ_NUM		= DMA_SPI_RX_REQ;
	dmainit.TRANS_DIR		= HME_DMAC_RXMode;
	
	SPI_Set_RecvThreshold(DEMO_SPI,1);
	SPI_SET_RX_DMA(DEMO_SPI,TRUE);										
	
	for(j=0;j<16;j++)
	{
		memset(rxDataBuf,0,sizeof(rxDataBuf));
		spi_init_struct.SPI_SlaveAddr =	FLASH_ADDR_OFFSET+j*FLASH_TRANS_SIZE;  // 1 sector = 16 page,  1 page = 256Byte
		HME_SPI_Init(DEMO_SPI,(SPI_InitTypeDef *)&spi_init_struct);	//SPI_SlaveAddr change, need to init spi once more
		
		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);        //init dma
		
		HME_DMAC_ENABLE(DMAC);										//enable dma channel
		
		while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)); 	//wait for spi controller idle
		
		SPI_Set_Cmd(DEMO_SPI,0x03);									//start transfer,0x03 : flash page read
		
		while(!dma_flag){};   										//wait dma transfer complete
			
		dma_flag = FALSE;

		HME_DMA_ENABLE_INTR(DMAC,0);	
		HME_DMAC_DISABLE(DMAC);
			
		delay_t(100);
	}
	
	SPI_SET_RX_DMA(DEMO_SPI,FALSE);
	
	return;
}
