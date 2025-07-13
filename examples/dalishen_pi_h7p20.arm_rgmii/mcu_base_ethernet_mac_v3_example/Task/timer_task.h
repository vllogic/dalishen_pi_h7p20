#ifndef __HME_TIMER_TASK_H__
#define __HME_TIMER_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_timer.h"
#include "sys_reg.h"

#ifndef TIMER_GROUP
#    define TIMER_GROUP  0
#endif

#if TIMER_GROUP == 0
#	define DEMO_TIMER_GROUP         TIMER0
#	define DEMO_TIMER_IRQn       	TIMER0_IRQn
# 	define DEMO_TIMER_IRQHanlder 	TIMER0_Handler
#elif TIMER_GROUP == 1
#	define DEMO_TIMER_GROUP         TIMER1
#	define DEMO_TIMER_IRQn       	TIMER1_IRQn
# 	define DEMO_TIMER_IRQHanlder 	TIMER1_Handler
#endif


extern void timer_task(void);

#endif
