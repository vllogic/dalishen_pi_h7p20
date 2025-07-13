#include "hme_wdt.h"

// As a safety feature to prevent accidental restarts, 
// the value 0x76 must be written to the Current Counter Value Register
#define WDT_CRR_RESTART_VALUE 0x76

void HME_WDT_Init(HME_WDT_InitTypeDef *Init)
{
    hme_assert(Init != NULL);
    hme_assert(IS_HME_WDT_VAILD_TIMOUT_PERIOD(Init->InitTimeoutPeriod));
    hme_assert(IS_HME_WDT_VAILD_TIMOUT_PERIOD(Init->TimeoutPeriod));

    WDT->WDT_TORR = (Init->InitTimeoutPeriod << 4) | Init->TimeoutPeriod;
    WDT->WDT_CR = WDT_CR_ENABLE | (Init->InterruptFirst ? WDT_CR_RMOD_GEN_INT_FIRST : WDT_CR_RMOD_GEN_SYSTEN_RESET);
}

void HME_WDT_StructInit(HME_WDT_InitTypeDef *Init)
{
    Init->InterruptFirst    = true;
    Init->InitTimeoutPeriod = WDT_TIMEOUT_PERIOD_16_POWER_OF_2;
    Init->TimeoutPeriod     = WDT_TIMEOUT_PERIOD_26_POWER_OF_2;//WDT_TIMEOUT_PERIOD_16_POWER_OF_2;
}

void HME_WDT_Restart(void)
{
    // Restart WDT
    WDT->WDT_CRR = WDT_CRR_RESTART_VALUE;
}

bool HME_WDT_GetCounter(void)
{
    // Get Current Counter
    return WDT->WDT_CCVR;
}

bool HME_WDT_GetITStatus(void)
{
    // Get Interrupt Status
    return (WDT->WDT_STAT == 1);
}

void HME_WDT_ClearITPendingBit(void)
{
    uint32_t eoi = WDT->WDT_EOI;
    (void)eoi;
}
