/*
 * @file hme_wdt.h
 * @brief HME HeaderFile
 * @version 0.1
 * @date 01. March 2021
 */

#ifndef __HME_WDT_H__
#define __HME_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_WDT
 * @{
 */

/*****************************************************************************/

/**
 * \~english @addtogroup HME_WDT_Types
 * \~chinese @addtogroup HME_WDT_Types
 * \~ @{
 */


/**
 * \~english @defgroup HME_WDT_TimeoutPeriod
 * \~chinese @defgroup HME_WDT_TimeoutPeriod
 * \~ @{
 */
typedef enum HME_WDT_TIMEOUTPERIOD {
    WDT_TIMEOUT_PERIOD_16_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_17_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_18_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_19_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_20_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_21_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_22_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_23_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_24_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_25_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_26_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_27_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_28_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_29_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_30_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_31_POWER_OF_2,
    WDT_TIMEOUT_PERIOD_32_POWER_OF_2,
} HME_WDT_TIMEOUTPERIOD;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_WDT_Initialization_Structure
 * \~chinese @defgroup HME_WDT_Initialization_Structure
 * \~ @{
 */
typedef struct {
    bool InterruptFirst;  //!< First generate an interrupt and if it is not cleared by the time a second timeout occurs
    //!< then generate a system reset
    HME_WDT_TIMEOUTPERIOD InitTimeoutPeriod;
    HME_WDT_TIMEOUTPERIOD TimeoutPeriod;
} HME_WDT_InitTypeDef;
/**
 * \~ @}
 */

/**
 * \~ @}
 */

/*****************************************************************************/

/**
 * ~english @brief Initialize WDT
 * ~english @param[in] Init @ref HME_WDT_InitTypeDef
 * ~english @retval None
 *
 * ~chinese @brief 初始化 WDT
 * ~chinese @param[in] Init @ref HME_WDT_InitTypeDef
 * ~chinese @retval 无
 */
extern void HME_WDT_Init(HME_WDT_InitTypeDef *Init);

/**
 * ~english @brief Fills each HME_WDT_InitTypeDef member with its default value.
 * ~english @param[in] Init: A pointer to structure HME_WDT_InitTypeDef which will be initialized.
 * ~english @retval None
 *
 * ~chinese @brief 填充结构体 @ref HME_WDT_InitTypeDef 的成员
 * ~chinese @param[in] Init: 已初始化的结构体 @ref HME_WDT_InitTypeDef 的指针。
 * ~chinese @retval 无
 */
extern void HME_WDT_StructInit(HME_WDT_InitTypeDef *Init);

/**
 * ~english @brief WDT Restart Counter
 * ~english @retval None
 *
 * ~chinese @brief 复位 WDT 的计数器
 * ~chinese @retval None
 */
extern void HME_WDT_Restart(void);

/**
 * ~english @brief Check interrupt flag is set or not
 * ~english @retval bool WDT current interrupt flag
 *
 * ~chinese @brief 检查 WDT 中断标志位是否已经设置
 * ~chinese @retval bool WDT中断标志位已经设置
 */
extern bool HME_WDT_GetITStatus(void);

/**
 * ~english @brief Clear WDT interrupt
 * ~english @retval None
 *
 * ~chinese @brief 清除WDT中断
 * ~chinese @retval None
 */
extern void HME_WDT_ClearITPendingBit(void);

/*****************************************************************************/

/**
 * \~english @defgroup HME_WDT_Private_Macro HME_WDT_Private_Macro
 * \~chinese @defgroup HME_WDT_Private_Macro HME_WDT_Private_Macro
 * \~ @{
 */
#define WDT_CR_ENABLE                       (0x01 << 0)
#define WDT_CR_RMOD_GEN_SYSTEN_RESET        (0x00 << 1)
#define WDT_CR_RMOD_GEN_INT_FIRST           (0x01 << 1)
#define IS_HME_WDT_VAILD_TIMOUT_PERIOD(__P) (__P < 16)
/**
 * \~ @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
