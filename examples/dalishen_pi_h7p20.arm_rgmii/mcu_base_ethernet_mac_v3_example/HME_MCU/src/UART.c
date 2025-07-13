
//  Include section
#include "UARTMan.h"
#include "hme_includes.h"


#define BASE_ADDR_USER  BASE_ADDR 
// Global variables section

// Last Error global variable
unsigned char ucLastError[CHANNEL_CNT];
// Circle buffer head pointer
unsigned int  uiReceiveBufferHead[CHANNEL_CNT];
// Circle buffer tail pointer
unsigned int  uiReceiveBufferTail[CHANNEL_CNT];
// Circle buffer table
unsigned int uctReceiveBuffer[CHANNEL_CNT][RS_BUFFER_SIZE];


// *****************************************************************
#ifdef BATCHRDEN

void FP0_IRQHandler(void)
{
  uint32_t ucFifoStateTmp;
	
	uint32_t ucDataTmp;	
  uint32_t  i;
  uint32_t ucRegAddr;
	
	unsigned char ChannelNo;
	ChannelNo = 0;

  
	 ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (STATE << 2);
	 ucDataTmp = *((volatile uint32_t *)ucRegAddr);
	 ucFifoStateTmp = ucDataTmp & RXFIFO_PFULL;
	 if(ucFifoStateTmp == RXFIFO_PFULL)
	 {
      for(i=0;i<RCVFIFOTH;i++)
		  {
         ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (PDATA << 2);
		     uctReceiveBuffer[ChannelNo][uiReceiveBufferTail[ChannelNo]++] = *((volatile uint32_t *)ucRegAddr);
	       // Check buffer range
	       if (uiReceiveBufferTail[ChannelNo] >= RS_BUFFER_SIZE)
		     uiReceiveBufferTail[ChannelNo] = 0;
	       // Buffer overflow rutine
	       if (uiReceiveBufferTail[ChannelNo] == uiReceiveBufferHead[ChannelNo]){
	       #ifdef FLUSH_BUFFER_IF_OVERFLOW
		     uiReceiveBufferHead[ChannelNo]=0;
		     uiReceiveBufferTail[ChannelNo]=0;
	       #else
		     uiReceiveBufferTail[ChannelNo]--;
	       #endif
		     ucLastError[ChannelNo] = BUFFER_OVERFLOV_ERR;
				 }
			}
	 }
	 ucFifoStateTmp = ucDataTmp & RX_OVERTIME;
	 if(ucFifoStateTmp == RX_OVERTIME)
	 {
      ucFifoStateTmp = ucDataTmp & RXFIFO_EMPTY;
		  while (ucFifoStateTmp != RXFIFO_EMPTY)
	    {
	       ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (PDATA << 2);
		     uctReceiveBuffer[ChannelNo][uiReceiveBufferTail[ChannelNo]++] = *((volatile uint32_t *)ucRegAddr);
	       // Check buffer range
	       if (uiReceiveBufferTail[ChannelNo] >= RS_BUFFER_SIZE)
		     uiReceiveBufferTail[ChannelNo] = 0;
	       // Buffer overflow rutine
	       if (uiReceiveBufferTail[ChannelNo] == uiReceiveBufferHead[ChannelNo]){
	       #ifdef FLUSH_BUFFER_IF_OVERFLOW
		     uiReceiveBufferHead[ChannelNo]=0;
		     uiReceiveBufferTail[ChannelNo]=0;
	       #else
		     uiReceiveBufferTail[ChannelNo]--;
	       #endif
		     ucLastError[ChannelNo] = BUFFER_OVERFLOV_ERR;
				 }	 
				 ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (STATE << 2);
		     ucFifoStateTmp =  (*((volatile uint32_t *)ucRegAddr)) & RXFIFO_EMPTY;
	    }
			ucRegAddr  = BASE_ADDR_USER + (ChannelNo << 7) + (SCOMM << 2);
	    *((volatile uint32_t *)ucRegAddr) = 0x61;
	 }
}

void OverTimeCounterWrite(unsigned char ChannelNo, unsigned int CounterInitialValue)
{
	 uint32_t ucDataTmp;
   uint32_t ucRegAddr;
	
	
	ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (OVERTIMECNTADDR << 2);
   ucDataTmp = (unsigned int)(CounterInitialValue);
	*((volatile uint32_t *)ucRegAddr)= ucDataTmp;
}

unsigned int OverTimeCounterRead(unsigned char ChannelNo)
{
	uint32_t ucDataTmp;
  uint32_t ulCounterValue = 0x0;
  uint32_t  ucRegAddr;
	
	ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (OVERTIMECNTADDR << 2);
   ucDataTmp = *((volatile uint32_t *)ucRegAddr);
	ulCounterValue = ulCounterValue | (unsigned int)(ucDataTmp);
	
	
   return ulCounterValue;
}

#endif

//*****************************************************************
//if not define BATCHRDEN, the function below is used
//*****************************************************************

//  void FP0_IRQHandler(void)
// {
// 	uint32_t ucFifoStateTmp;
//   uint32_t ucRegAddr;
// 	
// 	unsigned char ChannelNo;
// 	ChannelNo = 0;

// 	ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (STATE << 2);
// 	ucFifoStateTmp = (*((volatile uint32_t *)ucRegAddr)) & RXFIFO_EMPTY;
// 	while (ucFifoStateTmp != RXFIFO_EMPTY)
// 	{
// 	  ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (PDATA << 2);
// 		uctReceiveBuffer[ChannelNo][uiReceiveBufferTail[ChannelNo]++] = *((volatile uint32_t *)ucRegAddr);
// 	    // Check buffer range
// 	    if (uiReceiveBufferTail[ChannelNo] >= RS_BUFFER_SIZE)
// 		   uiReceiveBufferTail[ChannelNo] = 0;
// 	    // Buffer overflow rutine
// 	    if (uiReceiveBufferTail[ChannelNo] == uiReceiveBufferHead[ChannelNo])
// 				{
// 				#ifdef FLUSH_BUFFER_IF_OVERFLOW
// 					uiReceiveBufferHead[ChannelNo]=0;
// 					uiReceiveBufferTail[ChannelNo]=0;
// 				#else
// 					uiReceiveBufferTail[ChannelNo]--;
// 				#endif
// 					ucLastError[ChannelNo] = BUFFER_OVERFLOV_ERR;
// 	      }
// 		 ucRegAddr = BASE_ADDR_USER + (ChannelNo << 7) + (STATE << 2);
// 		 ucFifoStateTmp =  (*((volatile uint32_t *)ucRegAddr)) & RXFIFO_EMPTY;	    
// 	}
// }

/*****************************************************************/

uint32_t RSWrite(uint32_t *pucBuffer, uint32_t ucToWrite, unsigned char ChannelNo)
{
    uint32_t ucToWriteTmp = ucToWrite;
    uint32_t ucTmp;
	  uint32_t ucRegAddr;

    while (ucToWriteTmp)
	 {
		 ucRegAddr=0;
		 ucRegAddr  = BASE_ADDR_USER + (ChannelNo << 7) + (STATE << 2);
		 while( ( *((volatile uint32_t *)ucRegAddr) & TX_FULL ) == TX_FULL );
		 ucTmp = *pucBuffer;
		 ucRegAddr  = BASE_ADDR_USER + (ChannelNo << 7) + (PDATA << 2);
		 *((volatile uint32_t *)ucRegAddr) = ucTmp; 	
  	 ++pucBuffer;
		 --ucToWriteTmp;
    }    
    return ucToWrite;
}


/*****************************************************************/

/*****************************************************************/

uint32_t RSRead(uint32_t *pucBuffer, uint32_t ucToRead, unsigned char ChannelNo)
{
    uint32_t ucWasReaded = 0;
	
    // Start read buffer if not empty AND ucToRead is >0
    while ((uiReceiveBufferTail[ChannelNo] != uiReceiveBufferHead[ChannelNo]) && (ucToRead)) 
	 {
	 // Copy value from serial buffer into program buffer
	 	*((volatile uint32_t *)pucBuffer) = uctReceiveBuffer[ChannelNo][uiReceiveBufferHead[ChannelNo]];
		++pucBuffer;
		++uiReceiveBufferHead[ChannelNo];
		++ucWasReaded;
		--ucToRead;
	 // Check buffer-pointer range
		if (uiReceiveBufferHead[ChannelNo] >= RS_BUFFER_SIZE)
	   	uiReceiveBufferHead[ChannelNo] = 0;
    }
    // Return number of readed bytes
    return ucWasReaded;
}

/*****************************************************************/
void RSFlush(unsigned char ChannelNo)
{
    // Flush Receive buffer
    uiReceiveBufferHead[ChannelNo]=0;
    // Set Head and Tail on the first table elenent
    uiReceiveBufferTail[ChannelNo]=0;
}


//************************************************************************/
void SetCommandUart(unsigned int addr, unsigned int data)
{
  *((volatile unsigned int *)addr) = data;

}
