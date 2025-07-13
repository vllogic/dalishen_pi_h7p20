/*
 * @file     hme_conf.h
 * @brief    HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_CONF_H__
#define __HME_CONF_H__


#define 								HME_H7    			//HME_H7  HME_P2  HME_P3

#ifndef HME_SYS_CLK
#   define HME_SYS_CLK          		(100 * 1000 * 1000)
#endif


#define HME_USE_TIMER
#define HME_USE_WDT
#define HME_USE_GPIO
#define HME_USE_SPI
#define HME_USE_UART
#define HME_USE_I2C
#define HME_USE_DMA
#define HME_USE_SLEEP
#define HME_USE_INTR

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef HME_USE_FULL_ASSERT
#   define HME_USE_FULL_ASSERT     1
#endif

#if HME_USE_FULL_ASSERT
#   ifndef hme_assert
#       define hme_assert(...)   do { if (!(__VA_ARGS__)) {while(1);} } while(0)
#   endif
#else
#   define hme_assert(...)   
#endif


#include "HME_MCU.h"


/**
  * System clock frequency, unit is Hz.
  */
extern uint32_t SystemCoreClock;

/*! \mainpage A simple manual

Some general info.

This manual is divided in the following sections:
- \subpage intro
- \subpage advanced "Advanced usage"
*/

//-----------------------------------------------------------

/*! \page intro Introduction
This page introduces the user to the topic.
Now you can proceed to the \ref advanced "advanced section".
*/

//-----------------------------------------------------------

/*! \page advanced Advanced Usage
This page is for advanced users.
Make sure you have first read \ref intro "the introduction".
*/

/*! \page page1 A documentation page
  \tableofcontents
  Leading text.
  \section sec An example section
  This page contains the subsections \ref subsection1 and \ref subsection2.
  For more info see page \ref page2.
  \subsection subsection1 The first subsection
  Text.
  \subsection subsection2 The second subsection
  More text.
*/
 
/*! \page page2 Another page
  Even more info.
*/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

#endif

