/*
 * @file     hme_gpio.h
 * @brief    HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_INCLUDES_H
#define __HME_INCLUDES_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "hme_conf.h"
#include "hme_it.h"

#ifdef HME_USE_TIMER
	#include "hme_timer.h"
	#include "timer_task.h"
#endif

#ifdef HME_USE_WDT
	#include "hme_wdt.h"
	#include "wdt_task.h"
#endif

#ifdef HME_USE_GPIO
	#include "hme_gpio.h"
	#include "gpio_task.h"
#endif

#ifdef HME_USE_SPI
	#include "hme_spi.h"
	#include "spi_task.h"
	#include "spi_slave_task.h"
#endif

#ifdef HME_USE_UART
	#include "hme_uart.h"
	#include "uart_task.h"
	#include "isp_task.h"
#endif

#ifdef HME_USE_I2C
	#include "hme_i2c.h"
	#include "i2c_task.h"
#endif

#ifdef HME_USE_DMA
	#include "hme_dma.h"
	#include "dma_task.h"
#endif

#ifdef HME_USE_SLEEP
#include "sleep_task.h"
#endif

#ifdef HME_USE_INTR
#include "intr_task.h"
#endif

#include "sys_reg.h"


#ifdef __cplusplus
}
#endif

#endif
