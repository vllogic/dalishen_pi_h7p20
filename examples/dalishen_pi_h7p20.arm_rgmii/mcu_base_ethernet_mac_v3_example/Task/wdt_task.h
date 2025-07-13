#ifndef __HME_WDT_TASK_H__
#define __HME_WDT_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_wdt.h"
#include "sys_reg.h"

extern void wdt_interrupt_task(void);
extern void wdt_reset_task(void);

#endif
