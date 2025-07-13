#include "i2c_task.h"

#if I2C_SLAVE_MODE

volatile bool rdreq_intr_flag = 0;
uint8_t data_buf[E2PROM_PAGE_SIZE];
static uint8_t cnt = 0;
uint16_t sta;

void DEMO_I2C_IRQHanlder(void)
{	
	sta = HME_I2C_GetITStatus(DEMO_I2C);
	
	// rd req intr
	if((sta&0x20) == 0x20)
	{
		if((sta&0x40) == 0x40)
		{
			HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_TX_Abort,false);
		}
		//HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_Read_Request,false);
		HME_I2C_SendData(DEMO_I2C,E2PROM_PAGE_SIZE, data_buf+cnt);
		cnt = cnt+8;
		rdreq_intr_flag = 1;
		HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_Read_Request,false);
		HME_I2C_Cmd(DEMO_I2C, false);
		HME_I2C_Cmd(DEMO_I2C, true);
	}
}

void I2C_Slave_Mode_Feedback_Interrupt_task()
{
	uint8_t i;

    HME_I2C_Slave_InitTypeDef SlaveInit;
    
	NVIC_EnableIRQ(DEMO_I2C_IRQn);
    
	for(i=0;i<E2PROM_PAGE_SIZE;i++)
	{
		data_buf[i] = i;
	}

    {
		SlaveInit.Slave_address 	 	= E2PROM_SLAVE_ADDR;
		SlaveInit.Slave_Enable 		 	= HME_I2C_SLAVE_ENABLE;					//slave enable
		SlaveInit.MasterAddrWidth 		= HME_I2C_MasterAddrWidth_7BIT;
		SlaveInit.SlaveAddrWidth  		= HME_I2C_SlaveAddrWidth_7BIT;
		SlaveInit.SpeedMode 		 	= HME_I2C_SpeedMode_Standard;
		SlaveInit.Mode 			 		= HME_I2C_Mode_Slave;
	}
	
	//slave init
	HME_I2C_Cmd(DEMO_I2C, false);
	HME_I2C_SLAVE_Init(DEMO_I2C, &SlaveInit);
	HME_I2C_Cmd(DEMO_I2C, true);
	
	//set rd req int
	HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_Read_Request,true);
	
	while(1)
	{
		if(rdreq_intr_flag == 1)
		{
			HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_Read_Request,true);
			rdreq_intr_flag = 0;
		}
	}
}


void I2C_Slave_Mode_Recieve_task()
{
	volatile uint8_t r_date;
	
    HME_I2C_Slave_InitTypeDef SlaveInit;
    
    {

		SlaveInit.Slave_address 	 	= E2PROM_SLAVE_ADDR;
		SlaveInit.Slave_Enable 		 	= HME_I2C_SLAVE_ENABLE;					//slave enable
		SlaveInit.MasterAddrWidth 		= HME_I2C_MasterAddrWidth_7BIT;
		SlaveInit.SlaveAddrWidth  		= HME_I2C_SlaveAddrWidth_7BIT;
		SlaveInit.SpeedMode 		 	= HME_I2C_SpeedMode_Standard;
		SlaveInit.Mode 			 		= HME_I2C_Mode_Slave;
	}
	
	
	HME_I2C_Cmd(DEMO_I2C, false);
    HME_I2C_SLAVE_Init(DEMO_I2C, &SlaveInit);									//i2c slave mode initialize
	HME_I2C_Cmd(DEMO_I2C, true);
	
	while(1)
	{
		if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Receive_FIFO_Not_Empty))
			r_date = DEMO_I2C->IC_DATA_CMD;										//i2C slave get data from master
	}
	

	HME_I2C_Cmd(DEMO_I2C, false);
	
	return;
}
#endif


#if I2C_MASTER_MODE

extern volatile bool dma_flag;

volatile bool tx_intr_flag = 0;
volatile bool rx_intr_flag = 0;
static unsigned char buf_cnt=0;
uint8_t iic_recv_buf[E2PROM_PAGE_SIZE];
uint16_t sta;

uint8_t HME_I2C_INTRGetdataReq(I2C_Type *I2Cx, uint8_t size)
{
	uint8_t times,left,i;
	uint32_t count = 0;
	
	times = size/8;
	left = size%8;

	while(1)
	{
		if(count >= size)
			break;
		
		while(times--)
		{
			for(i=0;i<8;i++)
			{
				HME_I2C_ReadReq(I2Cx);
				count++;
			}
			
			while(1)
			{
				if(HME_I2C_GetFlagStatus(I2Cx,HME_I2C_Flag_Transmit_FIFO_Empty))
					break;
			}
			
			while(!rx_intr_flag){};
			rx_intr_flag = 0;	
		}
		
		
		for(i=0;i<left;i++)
		{
			HME_I2C_ReadReq(I2Cx);
			count++;
		}
		
		while(1)
		{
			if(HME_I2C_GetFlagStatus(I2Cx,HME_I2C_Flag_Transmit_FIFO_Empty))
				break;
		}
		
		while(!rx_intr_flag){};
		rx_intr_flag = 0;	
	}	
	
	return count;
}

uint8_t HME_I2C_INTRSend(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
	uint8_t count = 0;
	
	while (1) {
		if(tx_intr_flag == 1)
		{
			tx_intr_flag = 0;
			
			if (count < size) {
				count += HME_I2C_Send(I2Cx,size-count,data+count);
				
				HME_I2C_ITConfig(I2Cx,HME_I2C_Int_TX_Empty,1);
			}
		}
		if(count >= size)
			break;
	}
	
	return count;
}

void DEMO_I2C_IRQHanlder(void)
{	
	sta = HME_I2C_GetITStatus(DEMO_I2C);
	
	if((sta&0x10) == 0x10)
	{
		HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_TX_Empty,false);  //close I2C_Int_TX_Empty
		
		tx_intr_flag = 1;
	}
	
	if((sta&0x04) == 0x04)
	{
		sta = HME_I2C_Clear_INTR(DEMO_I2C);						//clear intr

		while(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Receive_FIFO_Not_Empty))
		{
			HME_I2C_ReadFifo(DEMO_I2C,1,iic_recv_buf+buf_cnt);
			buf_cnt++;
		}
		rx_intr_flag = 1;
	}
}

int I2C_Master_Wr_Rd_EEPROM_AT24C256_Interrupt_task()
{
	volatile uint32_t count = 0;
	uint8_t i,data[E2PROM_PAGE_SIZE];

    HME_I2C_InitTypeDef Init;
    
	NVIC_EnableIRQ(DEMO_I2C_IRQn);

    HME_I2C_StructInit(&Init);
	
	for (i = 0; i < E2PROM_PAGE_SIZE; i++) {
		data[i] = E2PROM_PAGE_SIZE - i;
	}
	memset(iic_recv_buf,0,E2PROM_PAGE_SIZE);
	
	{
		Init.Target_address 	= E2PROM_ADDRESS;
		Init.Mode 				= HME_I2C_Mode_Master;
		Init.SpeedMode 			= HME_I2C_SpeedMode_Standard;
		Init.MasterAddressWidth = HME_I2C_MasterAddrWidth_7BIT;
		Init.SlaveAddressWidth 	= HME_I2C_SlaveAddrWidth_7BIT;
		Init.Slave_Disable 		= HME_I2C_SLAVE_DISABLE;
		Init.RX_ThresholdLevel 	= HME_I2C_RXFIFO_ThresholdLevel_0;
		Init.TX_ThresholdLevel 	= HME_I2C_TXFIFO_ThresholdLevel_0;
	}
	
	HME_I2C_Cmd(DEMO_I2C, false);
    HME_I2C_Init(DEMO_I2C, &Init);								//Init I2C controller
	HME_I2C_Cmd(DEMO_I2C, true);
	
	//send data
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x00);  		//at24c256 addr0
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x01);			//at24c256 addr1

	while(1)													//wait trans fifo empty (wait send addr0 addr1 complete)
	{															
		if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Transmit_FIFO_Empty))
			break;
	}	
	
	HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_TX_Empty,true);		//enable HME_I2C_Int_TX_Empty int flag 
	count = HME_I2C_INTRSend(DEMO_I2C, E2PROM_PAGE_SIZE, data);

	//disable DEMO_I2C
	while(1)
	{
		if(tx_intr_flag == 1)
		{
			HME_I2C_Cmd(DEMO_I2C, false);
			break;
		}
	}
	
	delay_t(5000);
	
    //read test
	HME_I2C_ITConfig(DEMO_I2C,HME_I2C_Int_RX_Full,true);
	HME_I2C_Cmd(DEMO_I2C, true);
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x00); 		//at24c256 addr0
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x01); 		//at24c256 addr1
	

	while(1)													//wait trans fifo empty (wait send addr0 addr1 complete)
	{
		if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Transmit_FIFO_Empty))   
			break;
	}	

	
	count = HME_I2C_INTRGetdataReq(DEMO_I2C, E2PROM_PAGE_SIZE);	//send N timers request for get data

	delay_t(5000);
	
	if(memcmp(data,iic_recv_buf,E2PROM_PAGE_SIZE) != 0)
	{	

		return 0;
	}
	
	return count;
}

int I2C_Master_Wr_Rd_EEPROM_AT24C256_task()
{
	int cnt = 0;
	uint8_t i,send_data[E2PROM_PAGE_SIZE],recv_data[E2PROM_PAGE_SIZE];

    HME_I2C_InitTypeDef Init;
    
	//printf("i2c Wr & Rd eeprom test ...\r\n");
	
	for (i = 0; i < E2PROM_PAGE_SIZE; i++) {
		send_data[i] = i;
	}
	
	memset(recv_data,0,E2PROM_PAGE_SIZE);
	
	{
		Init.Target_address 	= E2PROM_ADDRESS;
		Init.Mode 				= HME_I2C_Mode_Master;
		Init.SpeedMode 			= HME_I2C_SpeedMode_Standard;
		Init.MasterAddressWidth = HME_I2C_MasterAddrWidth_7BIT;
		Init.SlaveAddressWidth 	= HME_I2C_SlaveAddrWidth_7BIT;
		Init.Slave_Disable 		= HME_I2C_SLAVE_DISABLE;
		Init.RX_ThresholdLevel 	= HME_I2C_RXFIFO_ThresholdLevel_0;
		Init.TX_ThresholdLevel 	= HME_I2C_TXFIFO_ThresholdLevel_1;
	}

	//send data to eeprom
	HME_I2C_Cmd(DEMO_I2C, false);
	HME_I2C_Init(DEMO_I2C, &Init);												//Initialize i2c controller
	HME_I2C_Cmd(DEMO_I2C, true);												//enable i2c controller
	
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x00);  						//at24c256 addr0
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x01);							//at24c256 addr1

	while(1)
	{
		if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Transmit_FIFO_Empty)) 	//wait trans fifo empty (wait send addr0 addr1 complete)
			break;
	}
	
	HME_I2C_SendData(DEMO_I2C, E2PROM_PAGE_SIZE, send_data); 					//send data to at24c256

	HME_I2C_Cmd(DEMO_I2C, false);												//disable i2c controller
	
	//printf("send data complete...\r\n");
	delay_t(500);
	delay_t(500);
	delay_t(500);
	delay_t(500);
	delay_t(500);
	delay_t(500);
	
	//read data from eeprom
	HME_I2C_Cmd(DEMO_I2C, true);
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x00);
	HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x01);
	
	while(1)
	{
		if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Transmit_FIFO_Empty))
			break;
	}
	
	cnt = HME_I2C_GetData(DEMO_I2C,E2PROM_PAGE_SIZE,recv_data);					//read data from at24c256
	
	delay_t(500);
	delay_t(500);
	delay_t(500);
	
	if(memcmp(send_data,recv_data,E2PROM_PAGE_SIZE) != 0)
	{	
	//	printf("read data error ...\r\n");
		return 0;
	}
	
	//printf("read data complete...\r\n");
	
	return cnt;
}

int I2C_Master_Wr_Rd_EEPROM_AT24C256_ByDMA_task(void)
{
	uint8_t j,send_data[E2PROM_PAGE_SIZE],recv_data[E2PROM_PAGE_SIZE];
	
    HME_I2C_InitTypeDef Init;

	dma_flag = FALSE;
	
	NVIC_EnableIRQ(DMAC_IRQn);
   
	printf("i2c Wr & Rd eeprom by dma test ... \r\n");
	
	send_data[0] = 0x00;
	send_data[1] = 0x01;
	for(j=0;j<E2PROM_PAGE_SIZE;j++)
	{
		send_data[j+2] = E2PROM_PAGE_SIZE - j;
	}
	
	memset(recv_data,0,E2PROM_PAGE_SIZE);
	
    HME_I2C_StructInit(&Init);
	
	//send test
	HME_I2C_Cmd(DEMO_I2C, false);
    HME_I2C_Init(DEMO_I2C, &Init);
	HME_I2C_Cmd(DEMO_I2C, true);
	
	//dma mem to per test
	{
		HME_DMAC_InitTypeDef dmainit;
				
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype 		= Dmac_mem2prf_dma;
		dmainit.SRC_ADDR  		= (uint32_t *)send_data;
		dmainit.TAR_ADDR  		= (uint32_t *)(&(DEMO_I2C->IC_DATA_CMD));
		dmainit.SINC      		= Dmac_addr_increment;
		dmainit.DINC      		= Dmac_addr_nochange;
		dmainit.BLOCK_TS  		= E2PROM_PAGE_SIZE+2;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.TX_REQ_NUM		= DMA_I2C_TX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_TXMode;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);

		//enable IIC dma transmit
		HME_I2C_SETDMATx(DEMO_I2C,1,1);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
			
		while(1)    //waite complete
		{
			if(dma_flag == 1)
			{
				dma_flag = 0;
				
				//close dma and IIC
				HME_DMA_ENABLE_INTR(DMAC,0);	
				HME_DMA_CFGREG(DMAC,0x0);
				HME_DMA_CHENREG(DMAC,0x100);
				
				printf("DMA & IIC mem to per trans completed ...\r\n");
				
				break;
			}
		};
		delay_t(500);
		HME_I2C_Cmd(DEMO_I2C, false);
	}

	//dma per to mem test
	{
		uint32_t data;
		HME_DMAC_InitTypeDef dmainit;
				
		HME_DMA_ENABLE_INTR(DMAC,0);
			
		dmainit.transtype 		= Dmac_prf2mem_dma;
		dmainit.SRC_ADDR  		= (uint32_t *)(&(DEMO_I2C->IC_DATA_CMD));
		dmainit.TAR_ADDR  		= (uint32_t *)(recv_data);
		dmainit.SINC 	  		= Dmac_addr_nochange;
		dmainit.DINC 	  		= Dmac_addr_increment;
		dmainit.BLOCK_TS  		= E2PROM_PAGE_SIZE;
		dmainit.SRC_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.DST_TR_WIDTH 	= Dmac_trans_width_8;
		dmainit.SRC_MSIZE 		= Dmac_msize_1;
		dmainit.DEST_MSIZE 		= Dmac_msize_1;
		dmainit.RX_REQ_NUM		= DMA_I2C_RX_REQ;
		dmainit.TRANS_DIR		= HME_DMAC_RXMode;

		HME_DMA_Init(DMAC,(HME_DMAC_InitTypeDef *)&dmainit);
		
		//enable IIC dma transmit
		HME_I2C_SETDMARx(DEMO_I2C,0,1);
		
		//enable dma channel 
		HME_DMA_CFGREG(DMAC,0x1);
		HME_DMA_CHENREG(DMAC,0x101);
		
		HME_I2C_Cmd(DEMO_I2C, true);
		HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x00);  	//at24c256 addr0
		HME_I2C_WriteReq(DEMO_I2C, E2PROM_PAGE_SIZE, 0x01);		//at24c256 addr1

		while(1)
		{
			if(HME_I2C_GetFlagStatus(DEMO_I2C,HME_I2C_Flag_Transmit_FIFO_Empty))
				break;
		}
			
		delay_t(500);
			
		for(j=0;j<E2PROM_PAGE_SIZE;j++)         				//send read req
		{
			HME_I2C_ReadReq(DEMO_I2C);
			while(1)
			{
				data = DEMO_I2C->IC_STATUS;
				if(!(data&0x10)&&(data&0x02))   				//rx fifo not full && tx fifo no full 
					break;
			};
		}		
				
		while(1)   												//waite complete
		{
			if(dma_flag == 1)
			{
				dma_flag = 0;
				
				//close dma and IIC
				HME_DMA_ENABLE_INTR(DMAC,0);	
				HME_DMA_CFGREG(DMAC,0x0);
				HME_DMA_CHENREG(DMAC,0x100);
				HME_I2C_Cmd(DEMO_I2C, false);
				
				if(PRINTF_LOG)
				{
					for (j = 0; j < E2PROM_PAGE_SIZE; j++) {
						printf("recv_data[%d]:0x%x\r\n",j,recv_data[j]);
					}
				}
				
				printf("DMA & IIC per to mem trans completed ...\r\n");
				break;
			}
		};
	}
	
	if(memcmp(send_data+2,recv_data,E2PROM_PAGE_SIZE) != 0)
	{	
		printf("DMA IIC mem & prf test error ...\r\n");
		return 0;
	}
	
	printf("DMA IIC mem & prf test succeed\r\n");
	return 1;
}
	
#endif
