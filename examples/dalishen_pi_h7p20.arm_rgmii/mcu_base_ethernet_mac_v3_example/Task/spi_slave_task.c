#include "spi_slave_task.h"

spi_slave_t spi_slave_dev;

/*******************************************************************************************
��������  :     HME_Spi_Slave_Init         

��������  :  	spi slave��ʼ������

�䡡    ��:   	pdev	SPI_InitTypeDef*
                        
�䡡    ��:   	
*******************************************************************************************/
void HME_Spi_Slave_Init(SPI_Type *SPIx)
{	
	SPIx->Transfer_Format_b.SlvMode = 1 ;    		//slave mode
	SPIx->Transfer_Format_b.MOSIBiDir = 0;
	
	SPIx->Transfer_Format_b.CPOL = 0;				//clk idle 0
	SPIx->Transfer_Format_b.CPHA = 0;              	//posedge sample
	
	SPIx->Transfer_Format_b.DataMerge = 0;
	SPIx->Transfer_Format_b.DataLen   = 7;
		
	SPIx->Transfer_Control_b.TransMode = 0;
	SPIx->Transfer_Control_b.DualQuad = 0;
	SPIx->Transfer_Control_b.SlvDataOnly = 1;
		
	SPIx->Interrupt_Enable = 0;
	
	SPI_Set_TransThreshold(SPIx,1);
	
	SPI_Set_RecvThreshold(SPIx,1);
	
	return;
}
/*******************************************************************************************
��������  :     SPI1_NVIC_CONFIG         

��������  :  	SPI1�ж�ʹ��

�䡡    ��:   	
                        
�䡡    ��:   	
*******************************************************************************************/
void SPI0_NVIC_CONFIG(void)
{
	NVIC_EnableIRQ(SPI0_IRQn);
	NVIC_SetPriority(SPI0_IRQn,0);
}

/*******************************************************************************************
��������  :     Spi_SlaveTask_Init         

��������  :  	slave task��ʼ������

�䡡    ��:   	pdev
                        
�䡡    ��:   	
*******************************************************************************************/
void Spi_SlaveTask_Init(spi_slave_t *pdev)
{
	pdev->device = SPI0;
	
	SPI0_NVIC_CONFIG();
		
	HME_Spi_Slave_Init(pdev->device);
	
	pdev->status = SPI_READY;
    pdev->ptran_buf = pdev->tran_buffer;
    pdev->precv_buf = pdev->recv_buffer;
    pdev->tran_count = 0;
    pdev->recv_count = 0;
	
	return;
}

/*******************************************************************************************
��������  :     Spi_Slave_Recv_Data         

��������  :  	�������ݺ���

�䡡    ��:   	pdev	��������buffָ��
                        
�䡡    ��:   	������������
*******************************************************************************************/
int16_t Spi_Slave_Recv_Data(spi_slave_t *pdev,uint8_t *pd)
{
    uint8_t count;
 
    if(pd == NULL || pdev == NULL) 
        return -1;
	
	pdev->status = SPI_RECV_DATA;

	HME_SPI_ITConfig(pdev->device,SPI_RXFIFOInt_ENABLE,TRUE);

	while(1)
	{
		if(pdev->status == SPI_IDLE){
			//__disable_irq();      
			for(count = 0; count < pdev->recv_count; count++){
				pd[count] = pdev->recv_buffer[count];
			}
			pdev->recv_count = 0;
			pdev->precv_buf = pdev->recv_buffer;
		   // __enable_irq();
					
			break;
		}else{
			count = 0;
		}
	}

    return count;
}

/*******************************************************************************************
��������  :     Spi_Slave_Send_Data         

��������  :  	�������ݺ���

�䡡    ��:   	pdev	buff��index����   ��������buffָ��  ��������
                        
�䡡    ��:   	������������
*******************************************************************************************/
int16_t Spi_Slave_Send_Data(spi_slave_t *pdev,uint8_t *pd,uint16_t count)
{
	uint16_t i;
  
    if(pd == NULL || pdev == NULL || (( count) > SPI_SLAVE_TX_BUF_SIZE))
        return -1;
   
    for(i = 0; i < count; i++){
        pdev->tran_buffer[i] = pd[i];
    }
	
	pdev->status = SPI_TRAN_DATA;						
	
	HME_SPI_ITConfig(pdev->device,SPI_TXFIFOInt_ENABLE,TRUE); 	

	while(1)
	{
		if(pdev->status == SPI_IDLE){
			//__disable_irq();      
		
			pdev->tran_count = 0;
			pdev->ptran_buf = pdev->tran_buffer;
		   // __enable_irq();
			
			break;
		}
	}

    return 1;
}

/*******************************************************************************************
��������:     spi_slave_isr         

��������:  SPI�жϺ���

�䡡    ��:   pdev        SPI�ṹ
                       
�䡡    ��:   ��
*******************************************************************************************/
void spi0_slave_isr(spi_slave_t *pdev)
{
	volatile uint32_t state;
	
	//rx int
	if(HME_SPI_GetITStatus(pdev->device, SPI_INT_STATUS_RXFIFOInt)){
		
		HME_SPI_ClearITPendingBit(pdev->device,SPI_INT_STATUS_RXFIFOInt);
		
		if(!HME_SPI_GetFlagStatus(pdev->device,SPI_Status_RXEMPTY)) { //rxfifo not empty  
			*pdev->precv_buf++  = pdev->device->Data;
			pdev->recv_count++;	
		}
		
		if(pdev->recv_count==SPI_SLAVE_RX_BUF_SIZE)
		{
			HME_SPI_ITConfig(pdev->device,SPI_RXFIFOInt_ENABLE,FALSE); //Disable SPI_RXFIFOInt_ENABLE
			pdev->status = SPI_IDLE;
		}
	}
	
	//tx int
	if(HME_SPI_GetITStatus(pdev->device, SPI_INT_STATUS_TXFIFOInt)){
		
		HME_SPI_ClearITPendingBit(pdev->device,SPI_INT_STATUS_TXFIFOInt);
		
		if(pdev->tran_count == SPI_SLAVE_TX_BUF_SIZE)  
		{
			HME_SPI_ITConfig(pdev->device,SPI_TXFIFOInt_ENABLE,FALSE);  //Disable SPI_TXFIFOInt_ENABLE
			pdev->status = SPI_IDLE;
		}
		
		while(!HME_SPI_GetFlagStatus(pdev->device, SPI_Status_TXFULL) && (pdev->tran_count<SPI_SLAVE_TX_BUF_SIZE))
		{
			SPI_SendData(pdev->device,pdev->tran_buffer+pdev->tran_count,1);
			pdev->tran_count++;
		}
	}
}

/*******************************************************************************
* Function Name  : spi_slave_transfer
* Description    : spi1 slave mode ,Recv data and Send data function.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void spi_slave_transfer(void)
{
	uint8_t buffer[SPI_SLAVE_RX_BUF_SIZE];
    uint16_t len;
	
	memset(buffer,0,sizeof(buffer));

	Spi_SlaveTask_Init(&spi_slave_dev);    								//spi slave��ʼ��
	
	len =  Spi_Slave_Recv_Data(&spi_slave_dev,buffer);  				//�������ݵ�buffer
	
	Spi_Slave_Send_Data(&spi_slave_dev,buffer,len); 					//��������

	return;
}
