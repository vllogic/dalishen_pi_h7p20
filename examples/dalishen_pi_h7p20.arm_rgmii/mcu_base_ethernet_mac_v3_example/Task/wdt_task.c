#include "wdt_task.h"

extern volatile bool wdt_isDone;

void wdt_interrupt_task()
{
	HME_WDT_InitTypeDef Init;

    NVIC_EnableIRQ(WDT_IRQn);

    HME_WDT_StructInit(&Init);
    HME_WDT_Init(&Init);
	
    while (1) {
        if (wdt_isDone) {
            wdt_isDone = false;
        }
    }
}

void wdt_reset_task(void)
{
	HME_WDT_InitTypeDef Init;
    volatile int cnt = 0;

    printf("Before WDT enable\r\n");
    
    HME_WDT_StructInit(&Init);
    Init.InterruptFirst = false;
    HME_WDT_Init(&Init);

	delay_t(5000);
	delay_t(5000);
	delay_t(5000);

    while (1) {
        printf("\r\ncnt: %d\r\n", cnt++);
    }
}
