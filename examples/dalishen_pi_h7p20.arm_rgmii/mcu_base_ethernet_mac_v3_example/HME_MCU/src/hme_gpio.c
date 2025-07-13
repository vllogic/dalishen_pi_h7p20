#include "hme_gpio.h"

void HME_GPIO_DeInit(GPIO_Type* GPIOx)
{
	GPIOx->PORT.DDR =0;
	GPIOx->PORT.DR =0;
}

void HME_GPIO_Init(GPIO_Type* GPIOx, HME_GPIO_InitTypeDef * Init)
{
    hme_assert(Init != NULL);
    hme_assert(IS_GPIO_MODE(Init->Mode));
    hme_assert(Init->Pins != 0);
    
    if (Init->Mode == PIN_MODE_HARTWARE) {
        GPIOx->PORT.CTL |= Init->Pins;
        return ;
    } else {
        GPIOx->PORT.CTL &= ~Init->Pins;
    }
    
    if (Init->Mode == PIN_MODE_INPUT) {
        GPIOx->PORT.DDR &= ~Init->Pins;
    } else {
        GPIOx->PORT.DDR |=  Init->Pins;
    }
}

void HME_GPIO_StructInit(HME_GPIO_InitTypeDef *Init)
{
    hme_assert(Init != NULL);

    /* HME_GPIO_InitTypeDef members default value */
    Init->Mode = PIN_MODE_INPUT;
    Init->Pins = GPIO_PIN0;
}

void HME_GPIO_ITConfig(GPIO_Type* GPIOx,uint32_t Pins, HME_GPIOA_ExitITTypeDef * ExitIT)
{
    hme_assert(ExitIT != NULL);
    
    if ((ExitIT->Mode == GPIO_EXIT_MODE_FALLING_EDGE) || (ExitIT->Mode == GPIO_EXIT_MODE_RISING_EDGE)) {
        GPIOx->INTTYPE_LEVEL |= Pins;    
    } else {
        GPIOx->INTTYPE_LEVEL &= ~Pins;    
    }
    
    if ((ExitIT->Mode == GPIO_EXIT_MODE_ACTIVE_HIGH) || (ExitIT->Mode == GPIO_EXIT_MODE_RISING_EDGE)) {
        GPIOx->INT_POLARITY |= Pins;    
    } else {
        GPIOx->INT_POLARITY &= ~Pins;    
    }
    
    if (ExitIT->Debounce) {
        GPIOx->DEBOUNCE |= Pins;    
    } else {
        GPIOx->DEBOUNCE &= ~Pins;    
    }
    
    if (ExitIT->Enable) {
        GPIOx->INTEN |= Pins;    
    } else {
        GPIOx->INTEN &= ~Pins;    
    } 
}

void HME_GPIO_ExitITStructInit(HME_GPIOA_ExitITTypeDef *ExitIT)
{
    hme_assert(ExitIT != NULL);

    /* HME_GPIOA_ExitITTypeDef members default value */
    ExitIT->Mode = GPIO_EXIT_MODE_FALLING_EDGE;
    ExitIT->Enable = true;
    ExitIT->Debounce = false;
}

void HME_GPIO_ITMask(GPIO_Type* GPIOx,uint32_t Pins)
{
    GPIOx->INTMASK |= Pins;
}

void HME_GPIO_ITUnMask(GPIO_Type* GPIOx,uint32_t Pins)
{
    GPIOx->INTMASK &= Pins;
}

uint32_t HME_GPIO_GetITStatus(GPIO_Type* GPIOx)
{
    return GPIOx->INTSTATUS;
}

void HME_GPIO_ClearITPendingBit(GPIO_Type* GPIOx,uint32_t Pins)
{
    GPIOx->PORTA_EOI = Pins;
}

uint32_t HME_GPIO_Read(GPIO_Type* GPIOx)
{
    return GPIOx->EXT_PORT;
}

void HME_GPIO_Write(GPIO_Type* GPIOx, uint32_t Pins, uint32_t Values)
{
    GPIOx->PORT.DR = (GPIOx->PORT.DR & (~Pins)) | (Values & Pins);
}

void HME_GPIO_Toggle(GPIO_Type* GPIOx, uint32_t Pins)
{
    GPIOx->PORT.DR ^= Pins;
}

void HME_GPIO_Set(GPIO_Type* GPIOx, uint32_t Pins)
{
    GPIOx->PORT.DR |= Pins;
}

void HME_GPIO_Clear(GPIO_Type* GPIOx, uint32_t Pins)
{
    GPIOx->PORT.DR &= ~Pins;
}

