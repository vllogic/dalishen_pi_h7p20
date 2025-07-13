/*
 * @file hme_uart.h
 * @brief HME HeaderFile
 * @version 0.1
 * @date 01. March 2021
 */

#ifndef __HME_UART_H__
#define __HME_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_UART
 * @{
 */

/*****************************************************************************/

/**
 * \~english @addtogroup HME_UART_Types
 * \~chinese @addtogroup HME_UART_Types
 * \~ @{
 */

/**
 * \~english @defgroup UART_DataLength
 * \~chinese @defgroup UART_DataLength
 * \~ @{
 */
#define UART_DataLength_5Bits (0ul << UART_LCR_DLS)
#define UART_DataLength_6Bits (1ul << UART_LCR_DLS)
#define UART_DataLength_7Bits (2ul << UART_LCR_DLS)
#define UART_DataLength_8Bits (3ul << UART_LCR_DLS)
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_StopBits
 * \~chinese @defgroup UART_StopBits
 * \~ @{
 */
#define UART_StopBits_1        (0ul << UART_LCR_STOP)
#define UART_StopBits_1_5_OR_2 (1ul << UART_LCR_STOP)
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_Parity
 * \~chinese @defgroup UART_Parity
 * \~ @{
 */
#define UART_Parity_None    ((0ul << UART_LCR_PEN) | (0ul << UART_LCR_EPS) | (0ul << UART_LCR_SP))
#define UART_Parity_Odd     ((1ul << UART_LCR_PEN) | (0ul << UART_LCR_EPS) | (0ul << UART_LCR_SP))
#define UART_Parity_Even    ((1ul << UART_LCR_PEN) | (1ul << UART_LCR_EPS) | (0ul << UART_LCR_SP))
#define UART_Parity_FORCE_0 ((1ul << UART_LCR_PEN) | (1ul << UART_LCR_EPS) | (1ul << UART_LCR_SP))
#define UART_Parity_FORCE_1 ((1ul << UART_LCR_PEN) | (0ul << UART_LCR_EPS) | (1ul << UART_LCR_SP))
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_RxFIFOTrigger
 * \~chinese @defgroup UART_RxFIFOTrigger
 * \~ @{
 */
#define UART_RxFIFOTrigger_1_CHARACTER      (0x00ul << UART_FCR_RCVR)
#define UART_RxFIFOTrigger_1_OUT_OF_4       (0x01ul << UART_FCR_RCVR)
#define UART_RxFIFOTrigger_1_OUT_OF_2       (0x02ul << UART_FCR_RCVR)
#define UART_RxFIFOTrigger_2_LESS_THAN_FULL (0x03ul << UART_FCR_RCVR)
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_TxFIFOTrigger
 * \~chinese @defgroup UART_TxFIFOTrigger
 * \~ @{
 */
#define UART_TxFIFOTrigger_FIFO_EMPTY       (0x00ul << UART_FCR_TET)
#define UART_TxFIFOTrigger_2_CHAR           (0x01ul << UART_FCR_TET)
#define UART_TxFIFOTrigger_1_OUT_OF_4       (0x02ul << UART_FCR_TET)
#define UART_TxFIFOTrigger_1_OUT_OF_2       (0x03ul << UART_FCR_TET)
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_DMA_MODE
 * \~chinese @defgroup UART_DMA_MODE
 * \~ @{
 */
#define UART_DMA_MODE0 (0x00ul << UART_FCR_DMAM)
#define UART_DMA_MODE1 (0x01ul << UART_FCR_DMAM)
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_Int
 * \~chinese @defgroup UART_Int
 * \~ @{
 */
#define UART_Int_Programmable_THRE_Mode  UART_IER_PTIME_MSK
#define UART_Int_Model_Status            UART_IER_EDSSI_MSK
#define UART_Int_Receiver_Line_Status    UART_IER_ELSI_MSK
#define UART_Int_Transmit_Holding_Empty  UART_IER_ETBEI_MSK
#define UART_Int_Received_Data_Available UART_IER_ERBFI_MSK
/**
 * \~ @}
 */

/**
 * \~english @defgroup UART_Flag
 * \~chinese @defgroup UART_Flag
 * \~ @{
 */
#define UART_Flag_RxNotEmpty        0x00000001
#define UART_Flag_TxEmpty           0x00000002
#define UART_Flag_TxHalfEmpty       0x00000004
#define UART_Flag_TxTimeoutNotEmpty 0x00000008
#define UART_Flag_TxTimeoutEmpty    0x00000010
#define UART_Flag_RxHalfFull        0x00000020
#define UART_Flag_TxFull            0x00000040
#define UART_Flag_All               0x0000007F
/**
 * \~ @}
 */

#define UART_IIR_MODEM_STATUS            0x00
#define UART_IIR_THR_EMPTY               0x02
#define UART_IIR_RECEIVED_DATA_AVAILABLE 0x04
#define UART_IIR_RECEIVED_LINE_STATUS    0x06
#define UART_IIR_BUSY_DETECT             0x07
#define UART_IIR_CHARACTER_TIMEOUT       0x0C
#define UART_IIR_MASK                    0x0F

/**
 * \~english @defgroup HME_UART_InitTypeDef UART initialization structure
 * \~chinese @defgroup HME_UART_InitTypeDef UART initialization structure
 * \~ @{
 */
typedef struct {
    uint32_t BaudRate;
    uint8_t DataLengthBits;
    uint8_t StopBits;
    uint8_t Parity;
    uint8_t RxFIFOTrigger;
    uint8_t TxFIFOTrigger;
    uint8_t DMAMode;
    bool RxEn;  /*!< Receive enable bit */
    bool CtsEn; /*!< Clear to set */
} HME_UART_InitTypeDef;
/**
 * \~ @}
 */

/**
 * \~ @}
 */

/*****************************************************************************/

/**
 * ~english @brief Deinitializes the UART peripheral registers to their default reset * values.
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @retval None
 *
 * ~chinese @brief 复位 UART 外设寄存器为默认值
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @retval 无
 */
extern void HME_UART_DeInit(UART_Type *UARTx);

/**
 * ~english @brief Initialize UART
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @param[in] init A pointer to structure HME_UART_InitTypeDef
 * ~english @retval None
 *
 * ~chinese @brief 初始化 UART
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @param[in] Init: 指向 @ref HME_UART_InitTypeDef 的指针
 * ~chinese @retval 无
 */
extern void HME_UART_Init(UART_Type *UARTx, HME_UART_InitTypeDef *Init);
/**
 * ~english @brief Fills each HME_UART_InitTypeDef member with its default value.
 * ~english @param[in] Init A pointer to structure HME_UART_InitTypeDef which will be initialized.
 * ~english @retval None
 *
 * ~chinese @brief 填充结构体 @ref HME_UART_InitTypeDef 的成员
 * ~chinese @param[in] 已初始化的结构体 @ref HME_UART_InitTypeDef 的指针。
 * ~chinese @retval 无
 */
extern void HME_UART_StructInit(HME_UART_InitTypeDef *Init);

/**
 * ~english @brief Enable or disable UART interrupt.
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @param[in] Int interrupt mask bits, which can be the combination of @ref UART_Int
 * ~english @param[in] Enable The bit indicates if specific interrupts are enable or not
 * ~english @retval None
 *
 * ~chinese @brief 使能或者禁能给定中断
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @param[in] Int 中断掩码位, 是 @ref UART_Int 的任意组合
 * ~chinese @param[in] Enable 中断的状态，可以是使能或者禁能
 * ~chinese @retval 无
 */
extern void HME_UART_ITConfig(UART_Type *UARTx, uint32_t Int, bool Enable);

/**
 * ~english @brief Check current interrupts Identity
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @retval uint32_t Interrupt ID
 *
 * ~chinese @brief 检查UART当前中断状态
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @retval uint32_t UART中断状态
 */
extern uint32_t HME_UART_GetAndCleanITStatus(UART_Type *UARTx);

/**
 * ~english @brief Check UART specific flags are set or not
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @param[in] Flag which can be the combination of @ref UART_Flag
 * ~english @retval bool The bit indicates if specific flags are set or not
 *
 * ~chinese @brief 检查UART特定标志是否已经设置
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @param[in] Flag 可以是 @ref UART_Flag 的任意组合
 * ~chinese @retval bool 获取给定所有标志是否都触发
 */
extern bool HME_UART_GetFlagStatus(UART_Type *UARTx, uint32_t Flag);

/**
 * ~english @brief Write data to UART
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @param[in] Size Expected data size to be written
 * ~english @param[in] Data A pointer to the data to be written
 * ~english @retval uint8_t Actual written data size
 *
 * ~chinese @brief 往UART写入数据
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @param[in] Size 预期传输的数据的个数
 * ~chinese @param[in] Data 用户提供的buffer用来存储将要发送的数据
 * ~chinese @retval uint8_t 实际写入的大小
 */
extern uint32_t HME_UART_SendData(UART_Type *UARTx, uint32_t Size, uint8_t *Data);

/**
 * ~english @brief Read data from UART
 * ~english @param[in] UARTx UART peripheral, which is UART0, UART1
 * ~english @param[in] Size Expected data size to be read
 * ~english @param[out] Data A user-allocated buffer to fetch data to be read
 * ~english @retval uint8_t Actual read data size
 *
 *
 * ~chinese @brief 从UART读取数据
 * ~chinese @param[in] UARTx UART 外设, 可以是 UART0 或 UART1
 * ~chinese @param[in] Size 预期传输的数据的个数
 * ~chinese @param[out] Data 用户提供的buffer用来存储读取到的数据
 * ~chinese @retval uint8_t 实际读取的大小
 *
 */
extern uint32_t HME_UART_ReceiveData(UART_Type *UARTx, uint32_t Size, uint8_t *Data);

/*****************************************************************************/

/**
 * \~english @defgroup HME_GPIO_Private_Macro HME GPIO Private Macros
 * \~chinese @defgroup HME_GPIO_Private_Macro HME GPIO 私有宏
 * \~ @{
 */
#define IS_UART_ALL_PERIPH(__PERIPH) (((__PERIPH) == UART0) || ((__PERIPH) == UART1) || ((__PERIPH) == UART2))
// clang-format off
// FCR Register
#define UART_FCR_RCVR 6
#define UART_FCR_RCVR_MSK (3ul << UART_FCR_RCVR)
#define UART_FCR_TET 4
#define UART_FCR_TET_MSK (3ul << UART_FCR_TET)
#define UART_FCR_DMAM 3
#define UART_FCR_DMAM_MSK (1ul << UART_FCR_DMAM)
#define UART_FCR_XFIFOR 2
#define UART_FCR_XFIFOR_MSK (1ul << UART_FCR_XFIFOR)
#define UART_FCR_RFIFOR 1
#define UART_FCR_RFIFOR_MSK (1ul << UART_FCR_RFIFOR)
#define UART_FCR_FIFOE 0
#define UART_FCR_FIFOE_MSK (1ul << UART_FCR_FIFOE)
// LCR Register
#define UART_LCR_DLAB 0x07
#define UART_LCR_DLAB_MSK (0x01ul << UART_LCR_DLAB)
#define UART_LCR_BC 0x06
#define UART_LCR_BC_MSK (0x01ul << UART_LCR_BC)
#define UART_LCR_SP 0x05
#define UART_LCR_SP_MSK (0x01ul << UART_LCR_SP)
#define UART_LCR_EPS 0x04
#define UART_LCR_EPS_MSK (0x01ul << UART_LCR_EPS)
#define UART_LCR_PEN 0x03
#define UART_LCR_PEN_MSK (0x01ul << UART_LCR_PEN)
#define UART_LCR_STOP 0x02
#define UART_LCR_STOP_MSK (0x01ul << UART_LCR_STOP)
#define UART_LCR_DLS 0x00
#define UART_LCR_DLS_MSK (0x03ul << UART_LCR_DLS)
// MCR Register
#define UART_MCR_SIRE 0x06
#define UART_MCR_SIRE_MSK (0x01ul << UART_MCR_SIRE)
#define UART_MCR_AFCE 0x05
#define UART_MCR_AFCE_MSK (0x01ul << UART_MCR_AFCE)
#define UART_MCR_LB 0x04
#define UART_MCR_LB_MSK (0x01ul << UART_MCR_LB)
#define UART_MCR_OUT2 0x03
#define UART_MCR_OUT2_MSK (0x01ul << UART_MCR_OUT2)
#define UART_MCR_OUT1 0x02
#define UART_MCR_OUT1_MSK (0x01ul << UART_MCR_OUT1)
#define UART_MCR_RTS 0x01
#define UART_MCR_RTS_MSK (0x01ul << UART_MCR_RTS)
#define UART_MCR_DTR 0x00
#define UART_MCR_DTR_MSK (0x01ul << UART_MCR_DTR)
// IER Register
#define UART_IER_PTIME 7
#define UART_IER_PTIME_MSK (0x01 << UART_IER_PTIME)
#define UART_IER_EDSSI 3
#define UART_IER_EDSSI_MSK (0x01 << UART_IER_EDSSI)
#define UART_IER_ELSI 2
#define UART_IER_ELSI_MSK (0x01 << UART_IER_ELSI)
#define UART_IER_ETBEI 1
#define UART_IER_ETBEI_MSK (0x01 << UART_IER_ETBEI)
#define UART_IER_ERBFI 0
#define UART_IER_ERBFI_MSK (0x01 << UART_IER_ERBFI)
// clang-format on

#define IS_UART_DATA_LENGTH(__LEN)                                                                                     \
    (((__LEN) == UART_DataLength_5Bits) || ((__LEN) == UART_DataLength_6Bits) || ((__LEN) == UART_DataLength_7Bits) || \
     ((__LEN) == UART_DataLength_8Bits))

#define IS_UART_STOPBITS(__STOPBITS) (((__STOPBITS) == UART_StopBits_1) || ((__STOPBITS) == UART_StopBits_1_5_OR_2))

#define IS_UART_PARITY(__PARITY)                                                                                       \
    (((__PARITY) == UART_Parity_None) || ((__PARITY) == UART_Parity_Even) || ((__PARITY) == UART_Parity_Odd) ||        \
     ((__PARITY) == UART_Parity_FORCE_0) || ((__PARITY) == UART_Parity_FORCE_1))

#define IS_UART_RX_FIFO_TRI(__TRI)                                                                                     \
    (((__TRI) == UART_RxFIFOTrigger_1_CHARACTER) || ((__TRI) == UART_RxFIFOTrigger_1_OUT_OF_4) ||                      \
     ((__TRI) == UART_RxFIFOTrigger_1_OUT_OF_2) || ((__TRI) == UART_RxFIFOTrigger_2_LESS_THAN_FULL))

#define IS_UART_TX_FIFO_TRI(__TRI)                                                                                     \
    (((__TRI) == UART_TxFIFOTrigger_FIFO_EMPTY) || ((__TRI) == UART_TxFIFOTrigger_2_CHAR) ||                      \
     ((__TRI) == UART_TxFIFOTrigger_1_OUT_OF_4) || ((__TRI) == UART_TxFIFOTrigger_1_OUT_OF_2))

#define IS_UART_DMA_MODE(__MODE) (((__MODE) == UART_DMA_MODE0) || ((__MODE) == UART_DMA_MODE1))

#define IS_UART_INT(__INT)                                                                                             \
    ((__INT & ~(UART_Int_Programmable_THRE_Mode | UART_Int_Model_Status | UART_Int_Receiver_Line_Status |              \
                UART_Int_Transmit_Holding_Empty | UART_Int_Received_Data_Available)) == 0)

#define IS_UART_FLAG(FLAG) (((FLAG) != 0) && (((FLAG) & ~UART_Flag_All) == 0))
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
