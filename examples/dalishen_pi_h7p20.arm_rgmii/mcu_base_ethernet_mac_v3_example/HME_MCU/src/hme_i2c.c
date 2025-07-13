#include "hme_i2c.h"
#include "stdio.h"

#define SS_MIN_SCL_HIGH         4000
#define SS_MIN_SCL_LOW          4700
#define FS_MIN_SCL_HIGH         600
#define FS_MIN_SCL_LOW          1300
#define HS_MIN_SCL_HIGH_100PF   60
#define HS_MIN_SCL_LOW_100PF    120

typedef struct {
    union {
        uint32_t DATA_CMD;

        struct {
            uint32_t DATA : 8;
            uint32_t RD_CMD : 1;
            uint32_t WR_CMD : 1;
            uint32_t WR_RD_CMD : 1;
        } DATA_CMD_b;
    } INNER;
} I2C_INNER_DATA_CMD;

static bool __HME_I2C_IS_ENABLED(I2C_Type *I2Cx)
{
    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));

    return I2Cx->IC_ENABLE_b.ENABLE ? true : false;
}

void HME_I2C_DeInit(I2C_Type *I2Cx)
{
    // TODO
    // Reset I2C
}

__USED uint32_t status[128];

void HME_I2C_Init(I2C_Type *I2Cx, HME_I2C_InitTypeDef *Init)
{
	uint32_t pclk1         = 0;
    uint32_t minSclLowTime = 0;
    uint32_t i2cPeriod     = 0;
    uint32_t pclk1Period   = 0;

    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert(Init != NULL);
    hme_assert(IS_HME_I2C_MODE(Init->Mode));
    hme_assert(IS_HME_I2C_SPEEDMODE(Init->SpeedMode));
    hme_assert(IS_HME_I2C_MASTER_ADDR_WIDTH(Init->MasterAddressWidth));
    hme_assert(IS_HME_I2C_SLAVE_ADDR_WIDTH(Init->SlaveAddressWidth));
    hme_assert(IS_HME_I2C_RX_THRESHOLDLEVEL(Init->RX_ThresholdLevel));
    hme_assert(IS_HME_I2C_TX_THRESHOLDLEVEL(Init->TX_ThresholdLevel));

	I2Cx->IC_INTR_MASK = 0x00;
	I2Cx->IC_TAR = Init->Target_address;
    I2Cx->IC_CON = Init->Mode | Init->SpeedMode | Init->MasterAddressWidth | Init->SlaveAddressWidth | Init->Slave_Disable;
    I2Cx->IC_RX_TL = Init->RX_ThresholdLevel;
    I2Cx->IC_TX_TL = Init->TX_ThresholdLevel;
    
	
	pclk1       =  GetPeripheralCLOCK();
    pclk1Period = 1000000000 / pclk1;
    i2cPeriod   = 1000000000 / 100000;

    minSclLowTime = pclk1 / 100000 ;
    i2cPeriod = 82 / pclk1Period;

   // if (init_struct->I2C_ClockSpeed <= 100000) {
    I2Cx->IC_SS_SCL_LCNT = (minSclLowTime - 13 - i2cPeriod) / 2;
    I2Cx->IC_SS_SCL_HCNT = (minSclLowTime - 13 - i2cPeriod - I2Cx->IC_SS_SCL_LCNT);

//    switch (Init->SpeedMode) {
//    case HME_I2C_SpeedMode_Standard:
//        I2Cx->IC_SS_SCL_HCNT = ((uint16_t) (((SS_MIN_SCL_HIGH * clock) / 100) + 1));
//        I2Cx->IC_SS_SCL_LCNT = ((uint16_t) (((SS_MIN_SCL_LOW * clock) / 100) + 1));
//        break;
//    case HME_I2C_SpeedMode_Fast:
//        I2Cx->IC_FS_SCL_HCNT = ((uint16_t) (((FS_MIN_SCL_HIGH * clock) / 100) + 1));
//        I2Cx->IC_FS_SCL_LCNT = ((uint16_t) (((FS_MIN_SCL_LOW * clock) / 100) + 1));
//        break;
//    case HME_I2C_SpeedMode_High:
//        I2Cx->IC_HS_SCL_HCNT = ((uint16_t) (((HS_MIN_SCL_HIGH_100PF * clock) / 100)+ 1));
//        I2Cx->IC_HS_SCL_LCNT = ((uint16_t) (((HS_MIN_SCL_LOW_100PF * clock) / 100) +1));
//        break;
//    default:
//        hme_assert(0);
//    }
}

void HME_I2C_StructInit(HME_I2C_InitTypeDef *Init)
{
    hme_assert(Init);

	Init->Target_address 		= 0x50;
    Init->Mode 					= HME_I2C_Mode_Master;
    Init->SpeedMode 			= HME_I2C_SpeedMode_Standard;
    Init->MasterAddressWidth 	= HME_I2C_MasterAddrWidth_7BIT;
    Init->SlaveAddressWidth 	= HME_I2C_SlaveAddrWidth_7BIT;
	Init->Slave_Disable 		= HME_I2C_SLAVE_DISABLE;
    Init->RX_ThresholdLevel 	= HME_I2C_RXFIFO_ThresholdLevel_0;
    Init->TX_ThresholdLevel 	= HME_I2C_TXFIFO_ThresholdLevel_0;
}

void HME_I2C_SLAVE_Init(I2C_Type *I2Cx, HME_I2C_Slave_InitTypeDef *Init)
{
	I2Cx->IC_INTR_MASK 					= 0x00;
	I2Cx->IC_SAR 						= Init->Slave_address;
	
	I2Cx->IC_CON_b.IC_SLAVE_DISABLE 	= Init->Slave_Enable;		//slave enable
	I2Cx->IC_CON_b.IC_RESTART_EN		= 1;
	I2Cx->IC_CON_b.IC_10BITADDR_MASTER 	= Init->MasterAddrWidth;
	I2Cx->IC_CON_b.IC_10BITADDR_SLAVE 	= Init->SlaveAddrWidth;
	I2Cx->IC_CON_b.SPEED 				= Init->SpeedMode;
	I2Cx->IC_CON_b.MASTER_MODE 			= Init->Mode;
}

void HME_I2C_Cmd(I2C_Type *I2Cx, bool enable)
{
    I2Cx->IC_ENABLE_b.ENABLE = enable ? 1 : 0;
}

void HME_I2C_ITConfig(I2C_Type *I2Cx, HME_I2C_IntTypedef Int, bool enable)
{
    if (enable) {
		I2Cx->IC_INTR_MASK |= Int;
    } else {
        
		I2Cx->IC_INTR_MASK &= ~Int;
    }
}

uint16_t HME_I2C_GetITStatus(I2C_Type *I2Cx)
{
    return (I2Cx->IC_INTR_STAT);
}

void HME_I2C_ClearITPendingBit(I2C_Type *I2Cx, uint32_t Int)
{
    uint32_t value;

    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert(IS_HME_I2C_INT(Int));

    if (Int & HME_I2C_Int_RX_Underflow) {
        value = I2Cx->IC_CLR_RX_UNDER;
    }

    if (Int & HME_I2C_Int_RX_Overflow) {
        value = I2Cx->IC_CLR_RX_OVER;
    }

    if (Int & HME_I2C_Int_RX_Full) {
        // do nothing
    }

    if (Int & HME_I2C_Int_TX_Overflow) {
        value = I2Cx->IC_CLR_TX_OVER;
    }

    if (Int & HME_I2C_Int_TX_Empty) {
        // do nothing
    }

    if (Int & HME_I2C_Int_Read_Request) {
        value = I2Cx->IC_CLR_RD_REQ;
    }

    if (Int & HME_I2C_Int_TX_Abort) {
        value = I2Cx->IC_CLR_TX_ABRT;
    }

    if (Int & HME_I2C_Int_RX_Done) {
        value = I2Cx->IC_CLR_RX_DONE;
    }

    if (Int & HME_I2C_Int_Activity) {
        value = I2Cx->IC_CLR_ACTIVITY;
    }

    if (Int & HME_I2C_Int_Stop_Detect) {
        value = I2Cx->IC_CLR_STOP_DET;
    }

    if (Int & HME_I2C_Int_Start_Detect) {
        value = I2Cx->IC_CLR_START_DET;
    }

    if (Int & HME_I2C_Int_General_Call) {
        value = I2Cx->IC_CLR_GEN_CALL;
    }

    (void)value;    // avoid unused warning
}

bool HME_I2C_GetFlagStatus(I2C_Type *I2Cx, HME_I2C_FlagTypedef Flag)
{

	if((I2Cx->IC_STATUS)&Flag)
		return true;
	else
		return false;
}

void HME_I2C_ClearFlag(I2C_Type *I2Cx, uint32_t Flag)
{

}

uint8_t HME_I2C_Clear_INTR(I2C_Type *I2Cx)
{
	return I2Cx->IC_CLR_INTR;
}

bool HME_I2C_ReadReq(I2C_Type *I2Cx)
{
    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert((I2Cx->IC_ENABLE & 0x01) == 0x01);

    I2Cx->IC_DATA_CMD = 0x100;

    return true;
}

uint8_t HME_I2C_SendData(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
	uint8_t i,times,left;
	uint8_t cnt = 0;
	
	times = size/8;
	left = size%8;
	
	while(times--)
	{
		for(i=0;i<8;i++)
		{
			HME_I2C_WriteReq(I2Cx, size, data[cnt]);
			cnt++;
		}
		
		while(1)
		{
			if(I2Cx->IC_STATUS_b.TFE)
				break;
		}
	}
	
	for(i=0;i<left;i++)
	{
		HME_I2C_WriteReq(I2Cx, size, data[cnt]);
		cnt++;
	}
	
	while(1)
	{
		if(I2Cx->IC_STATUS_b.TFE)
			break;
	}
	return cnt;
}

uint8_t HME_I2C_GetData(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
    uint8_t count = 0;
	uint8_t times,left,i;
	uint8_t total=0;
	uint8_t index = 0;

    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert(data != NULL);
    hme_assert(__HME_I2C_IS_ENABLED(I2Cx));
	
	times = size/8;
	left = size%8;

	while(total < size)
	{
		if(count >= size)
			break;
		
		while(times--)
		{
			for(i=0;i<8;i++)
			{	
				HME_I2C_ReadReq(I2Cx);
				total++;
			}
			
			while(1)
			{
				if(I2Cx->IC_STATUS_b.TFE)
					break;
			}
			
			while(1)
			{
				if(index >= 8)
				{
					index = 0;
					break;
				}
				if(I2Cx->IC_STATUS_b.RFNE)
				{
					HME_I2C_ReadFifo(I2Cx,1,data+count);
					count++;
					index++;
				}
			}
		}
		
		for(i=0;i<left;i++)
		{	
			HME_I2C_ReadReq(I2Cx);
			total++;
		}
			
		while(1)
		{
			if(I2Cx->IC_STATUS_b.TFE)
				break;
		}
		while(1)
		{
			if(index == left)
				break;
			
			if(I2Cx->IC_STATUS_b.RFNE)
			{
				HME_I2C_ReadFifo(I2Cx,1,data+count);
				count++;
				index++;
			}
		}		
	}
	
    return count;
}

uint8_t HME_I2C_ReadFifo(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
    uint8_t count = 0;

    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert(data != NULL);
    hme_assert(__HME_I2C_IS_ENABLED(I2Cx));

	*(data + count++) = I2Cx->IC_DATA_CMD;

    return count;
}

bool HME_I2C_WriteReq(I2C_Type *I2Cx, uint32_t size, uint8_t firstData)
{
  //  hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
  //  hme_assert((I2Cx->IC_ENABLE & 0x01) == 0x01);

    I2Cx->IC_DATA_CMD = firstData | (0x00 << 8) | (0x1 << 10);

    return true;
}

uint8_t HME_I2C_Send(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
	uint8_t count = 0;

    while (I2Cx->IC_STATUS_b.TFNF && count < size) {
        I2Cx->IC_DATA_CMD = *(data + count++);
    }
	
    return count;
}

uint8_t HME_I2C_WriteFifo(I2C_Type *I2Cx, uint8_t size, uint8_t *data)
{
    uint8_t count = 0;

    hme_assert(IS_HME_I2C_ALL_PERIPH(I2Cx));
    hme_assert(data != NULL);
    hme_assert(__HME_I2C_IS_ENABLED(I2Cx));

    while (I2Cx->IC_STATUS_b.TFNF && count < size) {
        *(data + count++) = I2Cx->IC_DATA_CMD;
    }
	
    return count;
}

void HME_I2C_SETDMATx(I2C_Type *I2Cx, uint8_t t_level, uint8_t enbale)
{
	I2Cx->IC_DMA_TDLR = t_level;		
	I2Cx->IC_DMA_CR_b.TDMAE = enbale;
}
void HME_I2C_SETDMARx(I2C_Type *I2Cx, uint8_t r_level, uint8_t enbale)
{
	I2Cx->IC_DMA_RDLR = r_level;	
	I2Cx->IC_DMA_CR_b.RDMAE = enbale;
}
