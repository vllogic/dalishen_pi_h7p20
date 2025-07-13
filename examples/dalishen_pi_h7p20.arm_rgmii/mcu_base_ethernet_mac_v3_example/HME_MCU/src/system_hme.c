#include <stdint.h>
#include "hme_conf.h"
#include "sys_reg.h"

extern uint32_t GetAHBCLOCK(void)
{
	uint8_t hclkdiv=0;
	
	hclkdiv = SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.hclk_div_fp;
	
    return (HME_SYS_CLK/(hclkdiv+1));
}

uint32_t GetPeripheralCLOCK(void)            /* Get PCL Clock Frequency      */
{
	uint8_t pclkdiv=0;
	
	pclkdiv = SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.pclk_div;
	
    return (HME_SYS_CLK/(pclkdiv+1));
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
	sys_reg_config();

    return;
}
