// *******************************************************************
//
//  Copyright (c) 2012  Capital Microelectronics Inc.
//
// *******************************************************************
//
//  Please review the terms of the license agreement before using
//  this file. If you are not an authorized user, please destroy this
//  source code file and notify CME immediately that you inadvertently
//  received an unauthorized copy.
//
// *******************************************************************
//  Project name        : CME-M5-N-L144-EVB
//  Project description : Board interfaces service
//  File name           : BasicDataType.h
//  File version        : 1.00
//  File contents       : Code file for header module
//  Design Engineer     : qrzhou,lkzhang
//  Quality Engineer    : Allen Zhang
//  Last modification   : 2012-12-24
// *******************************************************************
//
//  Modifications with respect to Version 1.00 :

// *******************************************************************

#ifndef __BASICDATATYPE_H__
#define __BASICDATATYPE_H__

// *******************************************************************


// *******************************************************************
//  variable type redefine
#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef UINT32
#define UINT32 unsigned long
#endif

#ifndef INT8
#define INT8 signed char
#endif

#ifndef INT16
#define INT16 signed short
#endif

#ifndef INT32
#define INT32 signed long
#endif

#ifndef SINT8
#define SINT8 signed char
#endif

#ifndef SINT16
#define SINT16 signed short
#endif

#ifndef SINT32
#define SINT32 signed long
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef I8
#define I8 signed char
#endif

#ifndef I16
#define I16 signed short
#endif

#ifndef I32
#define I32 signed int
#endif

#ifndef FLOAT32
#define FLOAT32 float
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef false
#define false 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef true
#define true 1
#endif

#ifndef BOOL
#define BOOL UINT8
#endif

#ifndef bool
#define bool UINT8
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif




#endif

















