#include "hme_uart.h"


void HME_UART_DeInit(UART_Type *UARTx)
{
    hme_assert(IS_UART_ALL_PERIPH(UARTx));
}
	
void HME_UART_Init(UART_Type *UARTx, HME_UART_InitTypeDef *Init)
{
    uint32_t MCR;
    uint32_t LCR;
    uint32_t FCR;
    uint32_t SerialClock;
    uint32_t Divisor16x;
    uint32_t DivisorI;
    uint32_t DivisorF;

    SerialClock = GetPeripheralCLOCK();

    hme_assert(IS_UART_ALL_PERIPH(UARTx));
    hme_assert(Init != NULL);
    hme_assert(IS_UART_STOPBITS(Init->StopBits));
    hme_assert(IS_UART_PARITY(Init->Parity));
    hme_assert(IS_UART_RX_FIFO_TRI(Init->RxFIFOTrigger));
    hme_assert(IS_UART_TX_FIFO_TRI(Init->TxFIFOTrigger));
    hme_assert(IS_UART_DMA_MODE(Init->DMAMode));
    hme_assert((0 < Init->BaudRate) && (Init->BaudRate <= SerialClock / 16));

    Divisor16x = SerialClock / Init->BaudRate;
    DivisorI = Divisor16x / 16;
    DivisorF = Divisor16x % 16;

    // TODO: support SIR Mode, Auto Flow Control
#define HME_UART_DEBUG
#ifdef HME_UART_DEBUG
    MCR = 0;//UART_MCR_LB_MSK;// | UART_MCR_RTS_MSK | UART_MCR_DTR_MSK;
#else
    MCR = 0;
#endif
    LCR = Init->DataLengthBits | Init->StopBits | Init->Parity;
    FCR = Init->RxFIFOTrigger | Init->TxFIFOTrigger | Init->DMAMode |
          UART_FCR_FIFOE_MSK | UART_FCR_RFIFOR_MSK | UART_FCR_XFIFOR_MSK;

    UARTx->IER = 0;
    UARTx->MCR = MCR;
    UARTx->LCR = LCR | UART_LCR_DLAB_MSK;
    UARTx->DLL = DivisorI & 0xFF;
    UARTx->DLH = DivisorI >> 8;
    UARTx->DLF = DivisorF;
    UARTx->LCR &= ~UART_LCR_DLAB_MSK;
    UARTx->FCR = FCR;
}

void HME_UART_StructInit(HME_UART_InitTypeDef *Init)
{
    hme_assert(Init != NULL);

    /* UART_InitStruct members default value */
    Init->BaudRate = 115200;
    Init->DataLengthBits = UART_DataLength_8Bits;
    Init->StopBits = UART_StopBits_1;
    Init->Parity = UART_Parity_None;
    Init->RxFIFOTrigger = UART_RxFIFOTrigger_1_CHARACTER;
    Init->TxFIFOTrigger = UART_TxFIFOTrigger_FIFO_EMPTY;
    Init->DMAMode = UART_DMA_MODE0;

    // TODO: Support Auto Flow
    Init->CtsEn = false;
}

void HME_UART_ITConfig(UART_Type *UARTx, uint32_t Int, bool enable)
{
    hme_assert(IS_UART_ALL_PERIPH(UARTx));
    hme_assert(IS_UART_INT(Int));

    if (enable) {
        UARTx->IER |= Int;
    } else {
        UARTx->IER &= ~Int;
    }
}

uint32_t HME_UART_GetAndCleanITStatus(UART_Type *UARTx)
{
    hme_assert(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->IIR & UART_IIR_MASK;
}

bool HME_UART_GetFlagStatus(UART_Type *UARTx, uint32_t Flag)
{
    hme_assert(IS_UART_ALL_PERIPH(UARTx));
    hme_assert(IS_UART_FLAG(Flag));

    return false;
}

uint32_t HME_UART_SendData(UART_Type *UARTx, uint32_t Size, uint8_t *Data)
{
    uint32_t count = 0;

    /* Check the parameters */
    hme_assert(IS_UART_ALL_PERIPH(UARTx));
    hme_assert(Data != NULL);
    hme_assert(Size > 0);

	while(count<Size)
	{
		if(UARTx->LSR_b.TEMT)
			UARTx->THR = Data[count++];
	}

    return count;
}

/* return value is actual read data size */
uint32_t HME_UART_ReceiveData(UART_Type *UARTx, uint32_t Size, uint8_t *Data)
{
    uint32_t count = 0;

    hme_assert(IS_UART_ALL_PERIPH(UARTx));
    hme_assert(Data != NULL);
    hme_assert(Size > 0);

	while(count<Size)
	{
		if(UARTx->LSR_b.DR)
			Data[count++] = UARTx->RBR;
	}

    return count;
}
