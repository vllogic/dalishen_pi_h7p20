#ifndef __HME_GPIO_TASK_H__
#define __HME_GPIO_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_gpio.h"
#include "sys_reg.h"


#ifndef DEMO_GPIO_NUM
#    define DEMO_GPIO_NUM  0
#endif

#if DEMO_GPIO_NUM == 0
#	define DEMO_GPIO            	GPIO0
#	define DEMO_GPIO_IRQn       	GPIO0_IRQn
# 	define DEMO_GPIO_IRQHanlder 	GPIO0_Handler
#	define DEMO_GPIO_ADDRBASE		GPIO0_BASE
#elif DEMO_GPIO_NUM == 1
#	define DEMO_GPIO            	GPIO1
#	define DEMO_GPIO_IRQn       	GPIO1_IRQn
# 	define DEMO_GPIO_IRQHanlder 	GPIO1_Handler
#	define DEMO_GPIO_ADDRBASE		GPIO1_BASE
#endif

void gpio_bitband_task(void);
void gpio_toggle_task(void);
void gpio_interrupt_task(void);
void soc_soft_rst_task(void);

#endif
