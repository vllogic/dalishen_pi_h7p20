#include "timer_task.h"

void timer_task(void)
{
	uint32_t count_1sec = GetPeripheralCLOCK();
	
	HME_TIM_InitTypeDef Init;
    HME_TIM_StructInit(&Init);

	Init.LoadCount = count_1sec;
    HME_TIM_Init(DEMO_TIMER_GROUP,TIMER_0, &Init);
    HME_TIM_ITConfig(DEMO_TIMER_GROUP,TIMER_0, true);
    HME_TIM_Cmd(DEMO_TIMER_GROUP,TIMER_0, true);

    Init.LoadCount = count_1sec;
    HME_TIM_Init(DEMO_TIMER_GROUP,TIMER_1, &Init);
    HME_TIM_ITConfig(DEMO_TIMER_GROUP,TIMER_1, true);
    HME_TIM_Cmd(DEMO_TIMER_GROUP,TIMER_1, true);
	
    NVIC_EnableIRQ(DEMO_TIMER_IRQn);
}
