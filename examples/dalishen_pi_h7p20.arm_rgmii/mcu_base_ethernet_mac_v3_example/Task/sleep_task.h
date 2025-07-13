#ifndef __HME_SLEEP_TASK_H__
#define __HME_SLEEP_TASK_H__

#include <stdio.h>
#include <string.h>
#include "hme_gpio.h"
#include "gpio_task.h"
#include "sys_reg.h"


extern void sleep_wakeup_by_GpioInt_task(void);
extern void sleep_wakeup_by_SystickInt_task(void);

#endif
