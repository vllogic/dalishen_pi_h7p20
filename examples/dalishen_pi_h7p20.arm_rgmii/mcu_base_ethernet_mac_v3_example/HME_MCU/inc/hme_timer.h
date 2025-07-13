/*
 * @file     hme_timer.h
 * @brief HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_TIMER_H__
#define __HME_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_Timer
 * @{
 */

/*****************************************************************************/

/**
 * \~english @addtogroup HME_Timer_Types HME Timer Types
 * \~chinese @addtogroup HME_Timer_Types HME Timer 类型
 * \~ @{
 */

/**
 * \~english @defgroup HME_Timer_Instance
 * \~chinese @defgroup HME_Timer_Instance
 * \~ @{
 */
typedef enum HME_TIM_ {
    TIMER_0 = 0,
    TIMER_1,
	TIMER_2,
	TIMER_3,
	TIMER_4,
	TIMER_5,
	TIMER_6,
	TIMER_7
} HME_TIM;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_Timer_Mode
 * \~chinese @defgroup HME_Timer_Mode
 * \~ @{
 */
enum {
    TIM_FREE_RUNNING_COUNT_MODE = 0,
    TIM_USER_DEFINED_COUNT_MODE = 1,
};
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_Timer_Configuration_Structure
 * \~chinese @defgroup HME_Timer_Configuration_Structure
 * \~ @{
 */
typedef struct {
    uint32_t LoadCount;
    bool Mode;
} HME_TIM_InitTypeDef;
/**
 * \~ @}
 */

/**
 * \~ @}
 */

/*****************************************************************************/

/**
 * \~english @brief Initialize HME Timer
 * \~english @param[in] Init A pointer to structure HME_TIM_InitTypeDef
 * \~english @retval None
 *
 * \~chinese @brief 初始化 HME Timer
 * \~chinese @param[in] Init: 结构体 @ref HME_TIM_InitTypeDef 的指针
 * \~chinese @retval 无
 */
extern void HME_TIM_Init(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, HME_TIM_InitTypeDef* Init);

/**
  * \~english @brief Fills each HME_TIM_InitTypeDef member with its default value.
  * \~english @param[in] Init: A pointer to structure SPI_InitTypeDef which will be initialized.
  * \~english @retval None
  *
  * \~chinese @brief 填充结构体 @ref HME_TIM_InitTypeDef 的成员
  * \~chinese @param[in] Init: 已初始化的结构体 @ref HME_TIM_InitTypeDef 的指针
  * \~chinese @retval 无
  */
extern void HME_TIM_StructInit(HME_TIM_InitTypeDef *Init);

/**
 * \~english @brief Enable or disable Timer.
 * \~english @param[in] Timx Timer peripheral, which is TIMER0 or TIMER1
 * \~english @param[in] Enable specific Timer is enable or not
 * \~english @retval None
 *
 * \~chinese @brief Enable or disable Timer.
 * \~chinese @param[in] Timx: 定时器外设, 可能是 TIMER0 或 TIMER1
 * \~chinese @param[in] Enable 给定定时器是否使能
 * \~chinese @retval 无
 */
extern void HME_TIM_Cmd(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, bool Enable);

/**
 * \~english @brief Enable or disable Timer interrupt.
 * \~english @param[in] Timx Timer peripheral, which is TIMER0 or TIMER1
 * \~english @param[in] Enable the status of Timer
 * \~english @retval None
 *
 * \~chinese @brief 使能或者禁能定时器中断
 * \~chinese @param[in] Timx: 定时器外设, 可能是 TIMER0 或 TIMER1
 * \~chinese @param[in] Enable 定时器的状态
 * \~chinese @retval 无
 */
extern void HME_TIM_ITConfig(TIMER_Type* TIMER_GROUPx,HME_TIM Timx, bool Enable);

/**
 * \~english @brief Check All Timer Status
 * \~english @retval None
 *
 * \~chinese @brief 获取所有定时器的中断状态
 * \~chinese @retval 无
 *
 */
extern uint32_t HME_TIM_GetAllITStatus(TIMER_Type* TIMER_GROUPx);

/**
 * \~english @brief Check specific timer interrupts are set or not
 * \~english @param[in] Timx Timer peripheral, which is TIMER0 or TIMER1
 * \~english @retval bool The specific timer interrupts status
 *
 * \~chinese @brief 检查特定定时器中断是否被设置
 * \~chinese @param[in] Timx: 定时器外设, 可能是 TIMER0 或 TIMER1
 * \~chinese @retval bool 给定定时器的中断状态
 */
extern bool HME_TIM_GetITStatus(TIMER_Type* TIMER_GROUPx,HME_TIM Timx);

/**
 * \~english @brief Clear specific timer interrupts
 * \~english @param[in] Timx Timer peripheral, which is TIMER0 or TIMER1
 * \~english @retval None
 *
 * \~chinese @brief 清除特定定时器的中断标志
 * \~chinese @param[in] Timx: 定时器外设, 可能是 TIMER0 或 TIMER1
 * \~chinese @retval 无
 */
extern void HME_TIM_ClearITPendingBit(TIMER_Type* TIMER_GROUPx,HME_TIM Timx);

/**
 * \~english @brief Get specific timer counter
 * \~english @param[in] Timx Timer peripheral, which is TIMER0 or TIMER1
 * \~english @retval None
 *
 * \~chinese @brief 获取特定定时器的计数值
 * \~chinese @param[in] Timx: 定时器外设, 可能是 TIMER0 或 TIMER1
 * \~chinese @retval 无
 */
extern uint32_t HME_TIM_GetCounter(TIMER_Type* TIMER_GROUPx,HME_TIM Timx);

/*****************************************************************************/

/**
 * \~english @defgroup HME_TIMER_Private_Macro HME Timer Private Macros
 * \~chinese @defgroup HME_TIMER_Private_Macro HME Timer 私有宏
 * \~ @{
 */
#define IS_HME_TIM_ALL_PERIPH(__P) (((__P) == TIMER_0) || ((__P) == TIMER_1)|| ((__P) == TIMER_2)|| ((__P) == TIMER_3)|| ((__P) == TIMER_4)|| ((__P) == TIMER_5)|| ((__P) == TIMER_6)|| ((__P) == TIMER_7))

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
