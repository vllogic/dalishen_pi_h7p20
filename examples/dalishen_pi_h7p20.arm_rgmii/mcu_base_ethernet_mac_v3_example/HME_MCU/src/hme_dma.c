#include "hme_dma.h"


void HME_DMAC_StructInit(HME_DMAC_InitTypeDef *ExitIT)
{
	ExitIT->transtype = Dmac_mem2mem_dma;
	
	return;
}

void HME_DMA_Init(DMAC_Type *DMACx, HME_DMAC_InitTypeDef *DMAC_Init)
{
	//1 clear dma intr
	DMACx->CLEARTFR = 1;
	DMACx->CLEARBLOCK = 1;
	DMACx->CLEARSRCTRAN = 1;
	DMACx->CLEARDSTTRAN = 1;
	DMACx->CLEARERR = 1;
	
	//2 close dma
	DMACx->CHENREG = 0;
	while(DMAC->CHENREG){};
	
	//set SAR ADDR 
	DMACx->SAR0 = (uint32_t)(DMAC_Init->SRC_ADDR);
	//set DARx_0
	DMACx->DAR0 = (uint32_t)(DMAC_Init->TAR_ADDR);
	
	
	DMACx->CTLx_0_b.DONE = 0;
	DMACx->CTLx_0_b.BLOCK_TS = DMAC_Init->BLOCK_TS;
	
	DMACx->CTLx_0_b.LLP_DST_EN  = 0;
	DMACx->CTLx_0_b.LLP_SRC_EN  = 0;
	
	DMACx->CTLx_0_b.SMS = 0;   //00 = AHB master 1
	DMACx->CTLx_0_b.DMS = 0;   //00 = AHB master 1
	
	//type :  Memory to Memory  CTLx_0  22: 20
	DMACx->CTLx_0_b.TT_FC  = DMAC_Init->transtype;   
	
	DMACx->CTLx_0_b.SRC_MSIZE = DMAC_Init->SRC_MSIZE;
	DMACx->CTLx_0_b.DEST_MSIZE = DMAC_Init->DEST_MSIZE;
	
	DMAC->CTLx_0_b.SRC_GATHER_EN = 0;
	DMAC->CTLx_0_b.DST_SCATTER_EN = 0;
	
	DMACx->CTLx_0_b.SINC = DMAC_Init->SINC;
	DMACx->CTLx_0_b.DINC = DMAC_Init->DINC;
	
	DMACx->CTLx_0_b.SRC_TR_WIDTH = DMAC_Init->SRC_TR_WIDTH;
	DMACx->CTLx_0_b.DST_TR_WIDTH = DMAC_Init->SRC_TR_WIDTH;
	
	DMAC->CTLx_0_b.INT_EN = 1;
	
	
	if(DMAC_Init->transtype != Dmac_mem2mem_dma)
	{
		if(DMAC_Init->TRANS_DIR == HME_DMAC_TXMode)  // 1 dma tx mode
		{	DMACx->CFGx_0_b.DEST_PER = DMAC_Init->TX_REQ_NUM;
			DMACx->CFGx_0_b.SRC_PER = 0;
		}
		else										//	0 : dma rx mode
		{
			DMACx->CFGx_0_b.DEST_PER = 0;
			DMACx->CFGx_0_b.SRC_PER = DMAC_Init->RX_REQ_NUM;
		}
	}
	
	DMACx->CFGx_0_b.CH_PRIOR     = 0;
	DMACx->CFGx_0_b.CH_SUSP      = 0;
	DMACx->CFGx_0_b.FIFO_EMPTY   = 0;   
	DMACx->CFGx_0_b.HS_SEL_DST   = 0;
	DMACx->CFGx_0_b.HS_SEL_SRC   = 0;   
	DMACx->CFGx_0_b.LOCK_CH_L    = 0;
	DMACx->CFGx_0_b.LOCK_B_L     = 0;
	DMACx->CFGx_0_b.LOCK_CH      = 0;
	DMACx->CFGx_0_b.LOCK_B       = 0;
	DMACx->CFGx_0_b.DST_HS_POL   = 0;
	DMACx->CFGx_0_b.SRC_HS_POL   = 0;
	DMACx->CFGx_0_b.MAX_ABRST    = 0;
	DMACx->CFGx_0_b.RELOAD_SRC   = 0;
	DMACx->CFGx_0_b.RELOAD_DST   = 0;
	DMACx->CFGx_0_b.FCMODE       = 0;
	DMACx->CFGx_0_b.FIFO_MODE    = 0;
	DMACx->CFGx_0_b.PROTCTL      = 0;  
	DMACx->CFGx_0_b.DS_UPD_EN    = 0;
	DMACx->CFGx_0_b.SS_UPD_EN    = 0;
	
	DMACx->MASKTFR = 0x101;
}

void HME_DMA_ENABLE_INTR(DMAC_Type *DMACx,bool enable)
{
	DMACx->CTLx_0_b.INT_EN = enable;
}

void HME_DMA_CFGREG(DMAC_Type *DMACx,uint32_t value)
{
	DMACx->DMACFGREG_b.DMA_EN = value;
}

void HME_DMA_CHENREG(DMAC_Type *DMACx,uint32_t val)
{
	DMACx->CHENREG = val;
}

void HME_DMAC_CLEARTFR(DMAC_Type *DMACx,uint32_t val)
{
	DMACx->CLEARTFR = val;
}

uint32_t HME_DMAC_GETINTSTATE(DMAC_Type *DMACx)
{
	return (DMACx->STATUSINT);
}

void HME_DMAC_DISABLE(DMAC_Type *DMACx)
{
	HME_DMA_CFGREG(DMACx,0x0);
	HME_DMA_CHENREG(DMACx,0x100);
	return;
}

void HME_DMAC_ENABLE(DMAC_Type *DMACx)
{
	HME_DMA_CFGREG(DMACx,0x1);
	HME_DMA_CHENREG(DMACx,0x101);
	return;
}
