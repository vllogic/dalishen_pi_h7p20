/*
 * @file     hme_gpio.h
 * @brief   HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_GPIO_H__
#define __HME_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_GPIO
 * @{
 */

/*****************************************************************************/

/**
 * \~english @defgroup GPIO_PINS GPIO Pins
 * \~chinese @defgroup GPIO_PINS GPIO 引脚
 * \~ @{
 */
#define GPIO_PIN0  (1 << 0) /* Pin 0 selected */
#define GPIO_PIN1  (1 << 1)
#define GPIO_PIN2  (1 << 2)
#define GPIO_PIN3  (1 << 3)
#define GPIO_PIN4  (1 << 4)
#define GPIO_PIN5  (1 << 5)
#define GPIO_PIN6  (1 << 6)
#define GPIO_PIN7  (1 << 7)
#define GPIO_PIN8  (1 << 8)
#define GPIO_PIN9  (1 << 9)
#define GPIO_PIN10 (1 << 10)
#define GPIO_PIN11 (1 << 11)
#define GPIO_PIN12 (1 << 12)
#define GPIO_PIN13 (1 << 13)
#define GPIO_PIN14 (1 << 14)
#define GPIO_PIN15 (1 << 15)
#define GPIO_PIN16 (1 << 16)
#define GPIO_PIN17 (1 << 17)
#define GPIO_PIN18 (1 << 18)
#define GPIO_PIN19 (1 << 19)
#define GPIO_PIN20 (1 << 20)
#define GPIO_PIN21 (1 << 21)
#define GPIO_PIN22 (1 << 22)
#define GPIO_PIN23 (1 << 23)
#define GPIO_PIN24 (1 << 24)
#define GPIO_PIN25 (1 << 25)
#define GPIO_PIN26 (1 << 26)
#define GPIO_PIN27 (1 << 27)
#define GPIO_PIN28 (1 << 28)
#define GPIO_PIN29 (1 << 29)
#define GPIO_PIN30 (1 << 30)
#define GPIO_PIN31 (1 << 31)
/**
 * \\~ @}
 */

/**
 * \~english @defgroup GPIO_EXIT_MODE GPIO External Interrupt
 * \~chinese @defgroup GPIO_EXIT_MODE GPIO 外部中断
 * \~ @{
 */
/*!< \~english GPIO Ex */
/*!< \~chinese GPIO GPIO_Pins @ref GPIO_PINS */
#define GPIO_EXIT_MODE_ACTIVE_LOW   (0x0)
#define GPIO_EXIT_MODE_FALLING_EDGE (0x1)
#define GPIO_EXIT_MODE_ACTIVE_HIGH  (0x2)
#define GPIO_EXIT_MODE_RISING_EDGE  (0x3)
/**
 * \\~ @}
 */

/**
 * \~english @defgroup HME_GPIO_Mode GPIO Mode, Include Hareware/Software(INPUT, OUTPUT)
 * \~chinese @defgroup HME_GPIO_Mode GPIO 模式，包括输入模式、输出模式、硬件模式
 * \~ @{
 */
typedef enum HME_GPIO_Mode {
    /*! \~english GPIO Software Input Mode */
    /*! \~chinese GPIO 软件输入模式 */
    PIN_MODE_INPUT = 0x0,

    /*! \~english GPIO Software Output Mode */
    /*! \~chinese GPIO 软件输出模式 */
    PIN_MODE_OUTPUT,

    /*! \~english GPIO Hardware Mode */
    /*! \~chinese GPIO 硬件模式 */
    PIN_MODE_HARTWARE,
} HME_GPIO_Mode;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_GPIO_InitTypeDef GPIO Init structure definition
 * \~chinese @defgroup HME_GPIO_InitTypeDef GPIO 初始化结构体
 * \~ @{
 */
typedef struct {
    uint32_t Pins; /*!< \~english GPIO GPIO_Pins @ref GPIO_PINS */
                   /*!< \~chinese GPIO 引脚 @ref GPIO_PINS 使用或的方式支持多个引脚 */
    /*! \~english GPIO Mode @ref GPIO_MODE */
    /*! \~chinese GPIO 模式 @ref GPIO_MODE */
    uint32_t Mode;
} HME_GPIO_InitTypeDef;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_GPIOA_ExitITTypeDef GPIO Exit Interrupt Structure Definition
 * \~chinese @defgroup HME_GPIOA_ExitITTypeDef GPIO 外部中断结构体定义
 * \~ @{
 */
typedef struct {
    uint32_t Mode; /*!< TODO */
    bool Debounce; /*!< TODO */
    bool Enable;   /*!< TODO */
} HME_GPIOA_ExitITTypeDef;
/**
 * \~ @}
 */

/**
 * \~ @}
 */

/*****************************************************************************/

/**
 * \~english @brief Deinitializes the GPIO registers to their default reset values.
 * \~english @note This function is optional.
 * \~english @retval None
 *
 * \~chinese @brief 将 GPIO 寄存器复位成默认值。
 * \~chinese @note 这个函数是可选的。
 * \~chinese @retval 无
 */
extern void HME_GPIO_DeInit(GPIO_Type* GPIOx);

/**
 * \~english @brief Initialize GPIO
 * \~english @param[in] GPIO_PORT: GPIO group, which is a value of @ref GPIO_PORT
 * \~english @param[in] GPIO_Init : A pointer to structure HME_GPIO_InitTypeDef that contains
 * \~english @retval None
 *
 * \~chinese @brief 初始化 GPIO
 * \~chinese @param[in] GPIO_PORT: GPIO group, which is a value of @ref GPIO_PORT
 * \~chinese @param[in] GPIO_Init : 结构体 @ref HME_GPIO_InitTypeDef 的指针
 * \~chinese @retval 无
 */
extern void HME_GPIO_Init(GPIO_Type* GPIOx, HME_GPIO_InitTypeDef * Init);

/**
 * \~english @brief Fills each @ref HME_GPIO_InitTypeDef member with its default value.
 * \~english @param[in] GPIO_Init: A pointer to structure HME_GPIO_InitTypeDef which will be initialized.
 * \~english @retval None
 *
 * \~chinese @brief 填充结构体 @ref HME_GPIO_InitTypeDef 的成员
 * \~chinese @param[in] GPIO_Init: 已初始化的结构体 @ref HME_GPIO_InitTypeDef 的指针
 * \~chinese @retval 无
 */
extern void HME_GPIO_StructInit(HME_GPIO_InitTypeDef *GPIO_Init);

/**
 * \~english @brief Enable or disable GPIO interrupt in the PORTA.
 * \~english @param[in] GPIO_Pins: GPIO GPIO_Pins, which is a value of @ref GPIO_PINS
 * \~english @param[in] ExitIT: @ref HME_GPIOA_ExitITTypeDef
 * \~english @retval None
 *
 * \~chinese @brief 使能或者禁能PORTA的中断.
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @param[in] ExitIT: @ref HME_GPIOA_ExitITTypeDef
 * \~chinese @retval 无
 */
extern void HME_GPIO_ITConfig(GPIO_Type* GPIOx,uint32_t Pins, HME_GPIOA_ExitITTypeDef * ExitIT);

/**
 * \~english @brief Fills each HME_GPIOA_ExitITTypeDef member with its default value.
 * \~english @param[in] ExitIT A pointer to structure HME_UART_InitTypeDef which will be initialized.
 * \~english @retval None
 *
 * \~chinese @brief 填充结构体 @ref HME_GPIOA_ExitITTypeDef 的成员.
 * \~chinese @param[in] ExitIT 结构体 @ref HME_UART_InitTypeDef 的指针.
 * \~chinese @retval 无
 */
extern void HME_GPIO_ExitITStructInit(HME_GPIOA_ExitITTypeDef *ExitIT);

/**
 * \~english @brief Get PORTA All Pins interrupts
 * \~english @retval uint32_t each bit indicates if the corresponding GPIO pin interrupt is set or not
 *
 * \~chinese @brief 获取PORTA的所有引脚的中断
 * \~chinese @retval uint32_t 每个位对应一个引脚的中断
 */
extern uint32_t HME_GPIO_GetITStatus(GPIO_Type* GPIOx);

/**
 * \~english @brief Clear PORTA interrupt.
 * \~english @param[in] GPIO_PINS: GPIO GPIO_Pins, which is a value of @ref GPIO_PINS
 * \~english @retval None
 *
 * \~chinese @brief 清除PORTA中断.
 * \~chinese @param[in] GPIO_PINS: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_ClearITPendingBit(GPIO_Type* GPIOx,uint32_t GPIO_PINS);

/**
 * \~english @brief Enable or disable GPIO interrupt in the specific group.
 * \~english @param[in] GPIO_Pins: GPIO GPIO_Pins, which is a value of @ref GPIO_PINS
 * \~english @retval None
 *
 * \~chinese @brief 使能屏蔽 PORTA 的中断
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_ITMask(GPIO_Type* GPIOx,uint32_t Pins);

/**
 * \~english @brief Enable or disable GPIO interrupt in the specific group.
 * \~english @param[in] GPIO_Pins: GPIO GPIO_Pins, which is a value of @ref GPIO_PINS
 * \~english @retval None
 *
 * \~chinese @brief 失能屏蔽 PORTA 的中断
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_ITUnMask(GPIO_Type* GPIOx,uint32_t Pins);

/**
 * \~english @brief Get value of each GPIO pin in the specific group
 * \~english @param[in] Port: GPIO group, which is a value of @ref GPIO_PORT
 * \~english @retval uint32_t each bit indicates value of the corresponding GPIO pin in the specific GPIO group
 *
 * \~chinese @brief 获取特定端口的所有引脚的值
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~chinese @retval uint32_t 每一个位对应者特定Port的不同GPIO引脚
 */
extern uint32_t HME_GPIO_Read(GPIO_Type* GPIOx);

/**
 * \~english @brief Write value of each GPIO pin in the specific group
 * \~english @param[in] Port GPIO group, which is a value of @ref GPIO_PORT
 * \~english @param[in] GPIO_Pins each bit indicates value of the corresponding GPIO pin in the specific GPIO Port is set or not
 * \~english @param[in] GPIO_Values each bit indicates value of the corresponding GPIO pin
 *	 					 in the specific GPIO group to be set
 * \~english @retval 无
 *
 * \~chinese @brief Write value of each GPIO pin in the specific group
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @param[in] GPIO_Values: 每一个位对应者特定Port的不同GPIO引脚
 * \~chinese @retval 无
 */
extern void HME_GPIO_Write(GPIO_Type* GPIOx, uint32_t Pins, uint32_t Values);

/**
 * \~english @brief Toggle value of each GPIO pin in the specific group
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~english @param[in] GPIO_Pins each bit indicates value of the corresponding GPIO pin in the specific GPIO group is set or not
 * \~english @retval 无
 *
 * \~chinese @brief Toggle value of each GPIO pin in the specific group
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_Toggle(GPIO_Type* GPIOx, uint32_t Pins);

/**
 * \~english @brief Set value of each GPIO pin in the specific group
 * \~english @param[in] GPIO_Port GPIO group, which is a value of @ref GPIO_PORT
 * \~english @param[in] GPIO_Pins each bit indicates value of the corresponding GPIO pin in the specific GPIO group is set or not
 * \~english @retval 无
 *
 * \~chinese @brief Set value of each GPIO pin in the specific group
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_Set(GPIO_Type* GPIOx, uint32_t GPIO_Pins);

/**
 * \~english @brief Clear value of each GPIO pin in the specific group
 * \~english @param[in] GPIO_PORT: GPIO group, which is a value of @ref GPIO_PORT
 * \~english @param[in] GPIO_PINS : each bit indicates value of the corresponding GPIO pin in the specific GPIO group is set or not
 * \~english @retval None
 *
 * \~chinese @brief Clear value of each GPIO pin in the specific group
 * \~chinese @param[in] GPIO_PORT: GPIO 端口, 端口可是是 @ref GPIO_PORT 的其中一个。
 * \~chinese @param[in] GPIO_Pins: GPIO 引脚, 引脚可以是任意 @ref GPIO_PINS 的组合。
 * \~chinese @retval 无
 */
extern void HME_GPIO_Clear(GPIO_Type* GPIOx, uint32_t GPIO_PINS);

/*****************************************************************************/

/**
 * \~english @defgroup HME_GPIO_Private_Macro HME GPIO Private Macros
 * \~chinese @defgroup HME_GPIO_Private_Macro HME GPIO 私有宏
 * \~ @{
 */
#define IS_GPIO_PORT(__G) (((__G) == PORTA) || ((__G) == PORTB) || ((__G) == PORTC) || ((__G) == PORTD))
#define IS_GPIO_MODE(__M) (((__M) == PIN_MODE_INPUT) || ((__M) == PIN_MODE_OUTPUT) || ((__M) == PIN_MODE_HARTWARE))
/**
 * \~ @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
