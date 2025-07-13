#include "hme_timer.h"

#ifndef HME_TIMER_LOADER_VALUE
#   define  HME_TIMER_LOADER_VALUE  0xFFFFFFFFul
#endif

void HME_TIM_Init(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, HME_TIM_InitTypeDef* Init)
{
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));

    TIMER_GROUPx->NUM[Timx].CONTROLREG_b.TIMER_ENABLE = 0x00; // disalbe timer
    TIMER_GROUPx->NUM[Timx].CONTROLREG_b.TIMER_MODE = (Init->Mode == TIM_USER_DEFINED_COUNT_MODE) ? 1 : 0;
    TIMER_GROUPx->NUM[Timx].CONTROLREG_b.TIMER_INT_MASK = 1;
    TIMER_GROUPx->NUM[Timx].LOADCOUNT = Init->LoadCount;
}

void HME_TIM_StructInit(HME_TIM_InitTypeDef *Init)
{
    Init->Mode = TIM_USER_DEFINED_COUNT_MODE;
    Init->LoadCount = HME_TIMER_LOADER_VALUE;
}

void HME_TIM_Cmd(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, bool Enable)
{
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));
    TIMER_GROUPx->NUM[Timx].CONTROLREG_b.TIMER_ENABLE = Enable ? 1 : 0;
}

void HME_TIM_ITConfig(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, bool Enable)
{
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));
    TIMER_GROUPx->NUM[Timx].CONTROLREG_b.TIMER_INT_MASK = Enable ? 0 : 1;
}

bool HME_TIM_GetITStatus(TIMER_Type* TIMER_GROUPx,HME_TIM Timx)
{
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));
    return TIMER_GROUPx->NUM[Timx].INTSTATUS;
}

uint32_t HME_TIM_GetAllITStatus(TIMER_Type* TIMER_GROUPx)
{
    return TIMER_GROUPx->TIMERSINTSTATUS;
}

void HME_TIM_ClearITPendingBit(TIMER_Type* TIMER_GROUPx,HME_TIM Timx)
{
    uint32_t eoi;
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));
    eoi = TIMER_GROUPx->NUM[Timx].EOI;
    (void)eoi;
}

uint32_t HME_TIM_GetCounter(TIMER_Type* TIMER_GROUPx,HME_TIM Timx)
{
    hme_assert(IS_HME_TIM_ALL_PERIPH(Timx));
    return TIMER_GROUPx->NUM[Timx].CURRENTVALUE;
}

