#include <stddef.h>
#include "hme_spi.h"


#define SET_BIT(reg, bit)     ((reg) |= (bit))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(bit))


void HME_SPI_DeInit(SPI_Type *SPIx)
{

}

void SPI_Set_Cmd(SPI_Type *SPIx,uint8_t Cmd)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Command = Cmd;
}

void SPI_Set_Addr(SPI_Type *SPIx,uint32_t Addr)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Address = Addr;
}

void SPI_Set_Transfer_Control_Reg(SPI_Type *SPIx,uint8_t TransferMode,bool CmdEn,bool AddrEn,uint32_t RdCnt,uint32_t WrCnt)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Transfer_Control_b.TransMode = TransferMode;
	SPIx->Transfer_Control_b.AddrEn = AddrEn;
	SPIx->Transfer_Control_b.CmdEn  = CmdEn;
	SPIx->Transfer_Control_b.RdTranCnt = RdCnt;
	SPIx->Transfer_Control_b.WrTranCnt = WrCnt;
}

void HME_SPI_StructInit(SPI_InitTypeDef *Init)
{
	Init->AddrLen  			=	SPI_AddrLen_3Byte;		
	Init->DataLen			=	SPI_Data_Width_8bit;		
	Init->DataMerge			=	SPI_DataMerge_Disable;	
	Init->Mode				=	SPI_MasterMode;
	Init->CPOL				=	0;						
	Init->CPHA				=	0;	
	
	Init->TransMode 		=	SPI_Transfermode_Write_Read;		
	Init->DualQuad 			=	SPI_data_phase_format_Single_mode;	
	Init->DummyCnt 			=	0;
	Init->RdTranCnt			= 	0;
	Init->WrTranCnt			= 	0;
	Init->SPI_SlaveAddr 	=	0x30000;
	Init->SCLK_DIV			=	1;
}

void HME_SPI_Init(SPI_Type *SPIx,SPI_InitTypeDef *spi_init_struct)
{	
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Transfer_Format_b.AddrLen		= spi_init_struct->AddrLen;
	SPIx->Transfer_Format_b.DataLen   	= spi_init_struct->DataLen;
	SPIx->Transfer_Format_b.DataMerge 	= spi_init_struct->DataMerge;
	SPIx->Transfer_Format_b.SlvMode		= spi_init_struct->Mode;
	SPIx->Transfer_Format_b.CPOL		= spi_init_struct->CPOL;
	SPIx->Transfer_Format_b.CPHA		= spi_init_struct->CPHA;
	
	SPIx->Transfer_Control_b.CmdEn 		= SPI_CMD_Enable;
	SPIx->Transfer_Control_b.AddrEn 	= SPI_ADDR_Enable;
	SPIx->Transfer_Control_b.TransMode 	= spi_init_struct->TransMode;
	SPIx->Transfer_Control_b.DualQuad 	= spi_init_struct->DualQuad;
	SPIx->Transfer_Control_b.DummyCnt 	= spi_init_struct->DummyCnt;
	
	SPIx->Transfer_Control_b.RdTranCnt	= spi_init_struct->RdTranCnt;
	SPIx->Transfer_Control_b.WrTranCnt	= spi_init_struct->WrTranCnt;
	SPIx->Address  						= spi_init_struct->SPI_SlaveAddr;
	SPIx->Interface_Timing_b.SCLK_DIV 	= spi_init_struct->SCLK_DIV;
	
	SPIx->Interrupt_Enable 				= 0;  //disable all interrupt
	
	return;
}

void HME_SPI_Cmd(SPI_Type *SPIx, bool enable)
{
    hme_assert(IS_SPI_ALL_PERIPH(SPIx));

    SPIx->Transfer_Control_b.AddrEn = enable;
	SPIx->Transfer_Control_b.CmdEn = enable;
}

void HME_SPI_ITConfig(SPI_Type *SPIx, uint32_t Int, bool enable)
{
    hme_assert(IS_SPI_ALL_PERIPH(SPIx));

	(enable) ? SET_BIT(SPIx->Interrupt_Enable, Int) : CLEAR_BIT(SPIx->Interrupt_Enable, Int);
}

void HME_SPI_ClearITPendingBit(SPI_Type *SPIx, uint32_t Int)
{
	SET_BIT(SPIx->Interrupt_Status, Int);
}

bool HME_SPI_GetFlagStatus(SPI_Type *SPIx, uint32_t Flag)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
    return (SPIx->Status & Flag) == Flag;
}

uint32_t HME_SPI_GetFlagIntStatus(SPI_Type *SPIx)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	return SPIx->Interrupt_Status;
}

bool HME_SPI_GetITStatus(SPI_Type *SPIx, uint32_t Int)
{
    hme_assert(IS_SPI_ALL_PERIPH(SPIx));

    return (SPIx->Interrupt_Status & Int) == Int;
}

void SPI_SET_TX_DMA(SPI_Type *SPIx,bool Enable)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Control_b.TXDMAEN = Enable;

	return;
}

void SPI_SET_RX_DMA(SPI_Type *SPIx,bool Enable)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Control_b.RXDMAEN = Enable;

	return;
}

void SPI_Set_DualQuad_Mode(SPI_Type *SPIx,uint8_t dualquad_mode)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Transfer_Control_b.DualQuad = dualquad_mode;
}

void SPI_SendData(SPI_Type *SPIx, uint8_t *pSendBuf, uint32_t DataCnt)
{
	uint32_t OutCount = 0;
	
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
    hme_assert(DataCnt > 0);
    hme_assert((pSendBuf != NULL));
	
    while ((OutCount < DataCnt)) {
        if (!SPIx->Status_b.TXFULL) {   //TFNF
            SPIx->Data = pSendBuf[OutCount];;  
            OutCount++;
        }     
	}  
}

uint32_t SPI_RecieveData(SPI_Type *SPIx, uint32_t *pRecvBuf, uint32_t DataCnt)
{
	uint32_t InCount = 0;
	
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
    hme_assert((pRecvBuf != NULL));

	while ((InCount < DataCnt)) {
        if (!SPIx->Status_b.RXEMPTY) {
            pRecvBuf[InCount] = SPIx->Data;          
            InCount++;
        }
    }
	
	return InCount;
}

void SPI_Set_TransThreshold(SPI_Type *SPIx,uint8_t level)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));
	
	SPIx->Control_b.TXTHRES = level;
	
	SPIx->Control_b.TXFIFORST = 1;		
	while(SPIx->Control_b.TXFIFORST){};	
}

void SPI_Set_RecvThreshold(SPI_Type *SPIx,uint8_t level)
{
	hme_assert(IS_SPI_ALL_PERIPH(SPIx));

	SPIx->Control_b.RXTHRES = level;
	SPIx->Control_b.RXFIFORST = 1;
	while(SPIx->Control_b.RXFIFORST){};
}	
