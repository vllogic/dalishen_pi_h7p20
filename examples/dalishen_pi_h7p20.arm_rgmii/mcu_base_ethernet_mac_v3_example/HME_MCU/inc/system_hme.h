/*
 * @file     system_hme.h
 * @brief    HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */


#ifndef __SYSTEM_HEM_HME_H__
#define __SYSTEM_HEM_HME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

extern uint32_t GetAHBCLOCK(void);
extern uint32_t GetPeripheralCLOCK(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_MVCM3_H */
