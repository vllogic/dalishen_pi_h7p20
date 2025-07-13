//================================================================================
// Copyright (c) 2012 Capital-micro, Inc.(Beijing)  All rights reserved.
//
// Capital-micro, Inc.(Beijing) Confidential.
//
// No part of this code may be reproduced, distributed, transmitted,
// transcribed, stored in a retrieval system, or translated into any
// human or computer language, in any form or by any means, electronic,
// mechanical, magnetic, manual, or otherwise, without the express
// written permission of Capital-micro, Inc.
//
//================================================================================
// File Description: 
// Header file for external UART 
//================================================================================
// Revision History :
//     V1.0   2012-12-12  FPGA IP Grp, first created
//     V2.0   2013-03-18  FPGA IP Grp, support fifo in transmit/receive data path
//     v2.1   2013-06-20  FPGA IP Grp, add receive fifo threshold for interrupt and
//                                     receive overtime control 
//================================================================================
#include "hme_includes.h"
#ifndef UART_H
#define UART_H

//******************************************************************
//  Include section
//*******************************************************************
#define BASE_ADDR 0xa0000000 //0x040000
#define FIFO_EN
#define BATCHRDEN        
#define CHANNEL_CNT   1

#define OVERTIMETH   0x00104b00//0x00004b00
#define RCVFIFOTH    0x4


#define  LCR   1
#define  BDR   2
#define  PDATA  3

#define  STATE  4 
#define  SCOMM  5  


#define  TFIFO_DATA_CNT_ADDR  6
#define  RFIFO_DATA_CNT_ADDR  7
#define  OVERTIMETHADDR  8  
#define  OVERTIMECNTADDR 9  
#define  RCVFIFOTHADDR 10  



#define RXFIFO_EMPTY  0x1
#define RXFIFO_PFULL  0x4
#define RX_OVERTIME   0x8

// Receive buffer size
#define RS_BUFFER_SIZE 50


// Define 1 if you want to flush buffer if overflow
#define FLUSH_BUFFER_IF_OVERFLOW

// LastError value definitions
// Receive Buffer overflow
#define BUFFER_OVERFLOV_ERR 	0x01
// RSReadBlk() function timeout
#define BUFFER_READ_TIMEOUT_ERR	0x02

//TX fifo status
#define TX_FULL      0x20



//*****************************************************************
// Function Prototype Section

//******************************************************************
//	Function name: 	unsigned long OverTimeCounterRead (
//	                     unsigned char ChannelNo);
//	Description:      read the real-time value of overtime counter 
// Parameters:
//          			unsigned char ChannelNo	: channel selected
//	Returns:
//******************************************************************
unsigned int OverTimeCounterRead(unsigned char ChannelNo);

//******************************************************************
//	Function name: 	void OverTimeCounterWrite (
//	                     unsigned char ChannelNo,
//                      unsigned long CounterInitialValue
//                      );
//	Description:      set the value of overtime counter in batch data 
//	                  read mode
// Parameters:
//          			unsigned char ChannelNo	: channel selected
//                   unsigned long CounterInitialValue: counter value
//	Returns:
//******************************************************************
void OverTimeCounterWrite(unsigned char ChannelNo, unsigned int CounterInitialValue);

//******************************************************************
//	Function name: 	void RcvFifoThreHandler (unsigned char ChannelNo);
//	Description:   	Read data from hardware register to reception buffer
//	                  in batch data read mode
// Parameters:
//          			unsigned char ChannelNo	: channel selected
//	Returns:
//******************************************************************
void RcvFifoThreHandler(unsigned char ChannelNo);

//******************************************************************
//	Function name: 	void SerialReceiveHandler (unsigned char ChannelNo);
//	Description:   	Read data from hardware register to reception buffer
// Parameters:
//          			unsigned char ChannelNo	: channel selected
//	Returns:
//******************************************************************
void SerialReceiveHandler(unsigned char ChannelNo);

//******************************************************************
//	Function name: 	void SetCommandUart( unsigned int addr, unsigned int data );
//	Description:   	Initialize UART settings
//			            
// Parameters:
//			            unsigned int addr	: com_addr
//                  unsigned int data : command value
//                   
//	Returns:
//******************************************************************
void SetCommandUart( unsigned int addr, unsigned int data); 
//******************************************************************
//	Function name: 	unsigned char RSWrite(
//						      unsigned char *pucBuffer,
//						      unsigned char ucToWrite,
//						      unsigned char ChannelNo);
//	Description:   	Function writes buffer content to the specific serial port.
// Parameters:
//			            unsigned char *pucBuffer : buffer
//			            unsigned char ucWrite	 : number of bytes to send
//                   unsigned char ChannelNo  : channel selected
//	Returns:	Functions returns received byte count.
//******************************************************************

uint32_t RSWrite(uint32_t *pucBuffer, uint32_t ucToWrite, unsigned char ChannelNo);

//******************************************************************
//	Function name: 	unsigned char RSRead(
//							   unsigned char *pucBuffer,
//							   unsigned char ucToRead,
//						      unsigned char ChannelNo);
//	Description:   	Read bytes from received buffer to pucBuffer.
//			            If number of bytes in receive buffer is less
//			            that ucToRead function returns.
// Parameters:
//			            unsigned char *pucBuffer : buffer
//			            unsigned char ucToRead	 : number of bytes to read
//                   unsigned char ChannelNo  : channel selected
//	Returns:	Functions returns received byte count.
//******************************************************************

uint32_t RSRead(uint32_t *pucBuffer, uint32_t ucToRead, unsigned char ChannelNo); 


//******************************************************************
//	Function name: 	void RSFlush(unsigned char ChannelNo);
//	Description:   	Receive buffer of specified channel flush.
// Parameters:       
//                   unsigned char ChannelNo  : channel selected	
//	Returns: 
//******************************************************************
void RSFlush(unsigned char ChannelNo);

//******************************************************************
//	Function name: 	void FP0_IRQHandler(void)
//	Description:   	Interrupt handler
// Parameters:       
//                  
//	Returns: 
//******************************************************************
void FP0_IRQHandler(void);

#endif
