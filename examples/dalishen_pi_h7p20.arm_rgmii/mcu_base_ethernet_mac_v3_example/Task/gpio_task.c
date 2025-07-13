#include "gpio_task.h"

void longdelay()
{
	int i;
	for(i=0;i<10;i++)
		delay_t(500);
		delay_t(50000);
}

void gpio_interrupt_task()
{
	HME_GPIO_InitTypeDef Init;
    HME_GPIOA_ExitITTypeDef ExitIT;

    NVIC_EnableIRQ(GPIO0_IRQn);
    HME_GPIO_DeInit(DEMO_GPIO);

    Init.Mode = PIN_MODE_OUTPUT;				//gpio1 output mode
    Init.Pins = GPIO_PIN1;
    HME_GPIO_Init(DEMO_GPIO, &Init);
	
	Init.Mode = PIN_MODE_INPUT;     			//gpio0 input mode
    Init.Pins = GPIO_PIN0;
    HME_GPIO_Init(DEMO_GPIO, &Init);

    HME_GPIO_ExitITStructInit(&ExitIT);
    ExitIT.Mode = GPIO_EXIT_MODE_RISING_EDGE;   //gpio0 input RISING_EDGE trigger Int
    HME_GPIO_ITConfig(DEMO_GPIO,GPIO_PIN0, &ExitIT);

    return;
}

void gpio_toggle_task(void)
{
	HME_GPIO_InitTypeDef Init;

	HME_GPIO_DeInit(DEMO_GPIO);

    Init.Mode = PIN_MODE_OUTPUT;
    Init.Pins = GPIO_PIN0 | GPIO_PIN1;
    HME_GPIO_Init(DEMO_GPIO, &Init);

    while (1) {
        HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0 | GPIO_PIN1);
        longdelay();
        HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0 | GPIO_PIN1);
        longdelay();

        HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0);
        longdelay();
        HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0);
        longdelay();
        
        HME_GPIO_Set(DEMO_GPIO, GPIO_PIN1);
        longdelay();
        HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN1);
		longdelay();
    }   
}

void soc_soft_rst_task(void)
{
	HME_GPIO_InitTypeDef Init;

	HME_GPIO_DeInit(DEMO_GPIO);

    Init.Mode = PIN_MODE_OUTPUT;
    Init.Pins = GPIO_PIN0 | GPIO_PIN1;
    HME_GPIO_Init(DEMO_GPIO, &Init);

	HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0);
	longdelay();
	
	printf("befor reset\r\n");
	*((volatile  uint32_t *) 0x51006010) = 0;
	printf("after reset\r\n");
}

/*

 *   #define DEVICE_REG0		 ((volatile unsigned long *) (0x40000000)) 
 *   #define DEVICE_REG0_BIT0 ((volatile unsigned long *) (0x42000000)) 
 *   #define DEVICE_REG0_BIT1 ((volatile unsigned long *) (0x42000004)) 
 *   
 *   *DEVICE_REG0 = 0xAB;   					//使用正常地址访问寄存器
 *   
 *   *DEVICE_REG0 = *DEVICE_REG0 | 0x2;  	//使用传统方法设置 bit1
 *   
 *   *DEVICE_REG0_BIT1 = 0x1; 				// 通过位带别名地址设置 bit1
 *   
 *   
 *   
 *   //把“位带地址＋位序号”转换成别名地址的宏
 *   #define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr & 0xFFFFF)<<5)+(bitnum<<2))
 *   
 *   //把该地址转换成一个指针
 *   #define MEM_ADDR(addr) *((volatile unsigned long *)
 *   
 *   
 *   MEM_ADDR(DEVICE_REG0) = 0xAB; 							//使用正常地址访问寄存器
 *   MEM_ADDR(DEVICE_REG0) = MEM_ADDR(DEVICE_REG0) | 0x2;   	//传统做法
 *   MEM_ADDR(BITBAND(DEVICE_REG0,1)) = 0x1; 				//使用位带别名地址
 
 */

#define BITBAND(addr, bitnum) 			((addr & 0xF0000000)+0x2000000+((addr & 0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr) 					*((volatile unsigned long *)(addr))

void gpio_bitband_task(void)
{
	HME_GPIO_InitTypeDef Init;

	HME_GPIO_DeInit(DEMO_GPIO);

    Init.Mode = PIN_MODE_OUTPUT;
    Init.Pins = GPIO_PIN0;
    HME_GPIO_Init(DEMO_GPIO, &Init);

    while (1) {

		MEM_ADDR(BITBAND(DEMO_GPIO_ADDRBASE,0)) = 0x1; 

		delay_t(500000);
		MEM_ADDR(BITBAND(DEMO_GPIO_ADDRBASE,0)) = 0x0; 

		delay_t(500000);
    }
}
