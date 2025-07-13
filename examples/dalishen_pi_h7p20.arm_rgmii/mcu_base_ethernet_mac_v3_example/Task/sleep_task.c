#include "sleep_task.h"


/******************************************* wakeup by systick interrupt function****************************/
void SysTick_Handler()
{  
	//NVIC_DisableIRQ(SysTick_IRQn);
	SysTick->CTRL  = 0;
	printf("disable systick irq\r\n");
}

uint32_t uSysTick_Config(uint32_t ticks)
{
	if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
	{
		return (1UL);                                                   /* Reload value impossible */
	}

	SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         	/* set reload register */
	NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 	/* set Priority for Systick Interrupt */
	SysTick->VAL   = 0UL;                                             	/* Load the SysTick Counter Value */
	SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         	/* Enable SysTick IRQ and SysTick Timer */
	return (0UL);                                                     	/* Function successful */
}

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

//进入待机模式	  
void Sys_Standby(void)
{ 
	SCB->SCR|=0<<2;		//使能SLEEPDEEP位 (SYS->CTRL)
    SCB->SCR|=1<<4;		//使能SLEEPDEEP位 (SYS->CTRL)	    

	WFI_SET();			//执行WFI指令,进入待机模式		 
}

void sleep_wakeup_by_SystickInt_task(void)
{
	uSysTick_Config(1000000);			//init systick
	printf("befor sleep ...\r\n");
	Sys_Standby();						//sleep
	delay_t(5000);
	printf("after sleep ...\r\n");
	
    while(1){};
}

/******************************************* wakeup by gpio interrupt function****************************/

void sleep_wakeup_by_GpioInt_task(void)
{
	HME_GPIO_InitTypeDef Init;
    HME_GPIOA_ExitITTypeDef ExitIT;

    NVIC_EnableIRQ(GPIO0_IRQn);

    HME_GPIO_DeInit(DEMO_GPIO);

    Init.Mode = PIN_MODE_OUTPUT;
    Init.Pins = GPIO_PIN1;
    HME_GPIO_Init(DEMO_GPIO, &Init);

	Init.Mode = PIN_MODE_INPUT;
    Init.Pins = GPIO_PIN0;
    HME_GPIO_Init(DEMO_GPIO, &Init);
	
	//init GPIO_PIN0 INT mode
    HME_GPIO_ExitITStructInit(&ExitIT);
    ExitIT.Mode = GPIO_EXIT_MODE_FALLING_EDGE;
    HME_GPIO_ITConfig(DEMO_GPIO,GPIO_PIN0, &ExitIT);
    
	
	printf("befor sleep ...\r\n");
	Sys_Standby();
	printf("after sleep ...\r\n");
	
    while (1)
	{
		HME_GPIO_Set(DEMO_GPIO, GPIO_PIN1);
        delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
        HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN1);
        delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
		delay_t(50000);
	};
}
