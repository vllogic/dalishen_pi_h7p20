/*
 * @file hme_i2c.h
 * @brief HME HeaderFile
 * @version 0.1
 * @date 01. March 2021
 */

#ifndef __HME_I2C_H__
#define __HME_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_I2C
 * @{
 */

/*****************************************************************************/

/**
 * \~english @addtogroup HME_I2C_Types
 * \~chinese @addtogroup HME_I2C_Types
 * \~ @{
 */

/**
 * \~english @defgroup HME_I2C_Mode
 * \~chinese @defgroup HME_I2C_Mode
 * \~ @{
 */
typedef enum {
    HME_I2C_Mode_Slave  = 0x00ul << 0,
    HME_I2C_Mode_Master = 0x01ul << 0,
} HME_I2C_ModeTypeDef;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_I2C_Speed
 * \~chinese @defgroup HME_I2C_Speed
 * \~ @{
 */
typedef enum {
    HME_I2C_SpeedMode_Standard   = 0x01ul << 1,
    HME_I2C_SpeedMode_Fast       = 0x02ul << 1,
    HME_I2C_SpeedMode_High       = 0x03ul << 1,
    HME_I2C_SpeedMode_Ultra_Fast = 0x03ul << 1,
} HME_I2C_SpeedModeTypeDef;
/**
 * \~ @}
 */

/**
 * \~english @defgroup HME_I2C_SlaveAddrWidth
 * \~chinese @defgroup HME_I2C_SlaveAddrWidth
 * \~ @{
 */
typedef enum {
    HME_I2C_SlaveAddrWidth_7BIT  = 0x00ul << 3,
    HME_I2C_SlaveAddrWidth_10BIT = 0x01ul << 3,
} HME_I2C_SlaveAddrWidthTypedef;
/**
 * \~ @}
 */


/**
 * \~english @defgroup HME_I2C_MasterAddrWidth
 * \~chinese @defgroup HME_I2C_MasterAddrWidth
 * \~ @{
 */
typedef enum {
    HME_I2C_MasterAddrWidth_7BIT  = 0x00ul << 4,
    HME_I2C_MasterAddrWidth_10BIT = 0x01ul << 4,
} HME_I2C_MasterAddrWidthTypedef;
/**
 * @}
 */

/**
 * \~english @defgroup HME_I2C_SLAVE_DISABLE
 * \~chinese @defgroup HME_I2C_SLAVE_DISABLE
 * \~ @{
 */
typedef enum {
    HME_I2C_SLAVE_ENABLE   = 0x00ul << 5,
    HME_I2C_SLAVE_DISABLE  = 0x01ul << 5,
} HME_I2C_SLAVE_DISABLETypedef;
/**
 * @}
 */

/**
 * \~english @defgroup HME_I2C_RXFIFO_ThresholdLevelTypedef
 * \~chinese @defgroup HME_I2C_RXFIFO_ThresholdLevelTypedef
 * \~ @{
 */
typedef enum {
    HME_I2C_RXFIFO_ThresholdLevel_0 = 0x00ul,
    HME_I2C_RXFIFO_ThresholdLevel_1 = 0x01ul,
    HME_I2C_RXFIFO_ThresholdLevel_2 = 0x02ul,
    HME_I2C_RXFIFO_ThresholdLevel_3 = 0x03ul,
    HME_I2C_RXFIFO_ThresholdLevel_4 = 0x04ul,
    HME_I2C_RXFIFO_ThresholdLevel_5 = 0x05ul,
    HME_I2C_RXFIFO_ThresholdLevel_6 = 0x06ul,
    HME_I2C_RXFIFO_ThresholdLevel_7 = 0x07ul,

    HME_I2C_RXFIFO_ThresholdLevel_MAX = HME_I2C_RXFIFO_ThresholdLevel_7,

} HME_I2C_RXFIFO_ThresholdLevelTypedef;
/**
 * @}
 */

/**
 * \~english @defgroup HME_I2C_TXFIFO_ThresholdLevelTypedef
 * \~chinese @defgroup HME_I2C_TXFIFO_ThresholdLevelTypedef
 * \~ @{
 */
typedef enum {
    HME_I2C_TXFIFO_ThresholdLevel_0 = 0x00ul,
    HME_I2C_TXFIFO_ThresholdLevel_1 = 0x01ul,
    HME_I2C_TXFIFO_ThresholdLevel_2 = 0x02ul,
    HME_I2C_TXFIFO_ThresholdLevel_3 = 0x03ul,
    HME_I2C_TXFIFO_ThresholdLevel_4 = 0x04ul,
    HME_I2C_TXFIFO_ThresholdLevel_5 = 0x05ul,
    HME_I2C_TXFIFO_ThresholdLevel_6 = 0x06ul,
    HME_I2C_TXFIFO_ThresholdLevel_7 = 0x07ul,

    HME_I2C_TXFIFO_ThresholdLevel_MAX = HME_I2C_TXFIFO_ThresholdLevel_7,

} HME_I2C_TXFIFO_ThresholdLevelTypedef;
/**
 * @}
 */

/**
 * \~english @defgroup HME_I2C_HighSpeedMasterModeCodeTypedef
 * \~chinese @defgroup HME_I2C_HighSpeedMasterModeCodeTypedef
 * \~ @{
 */
typedef enum {
    HME_I2C_HighSpeedMasterModeCode_8  = 0x00ul,
    HME_I2C_HighSpeedMasterModeCode_9  = 0x01ul,
    HME_I2C_HighSpeedMasterModeCode_10 = 0x02ul,
    HME_I2C_HighSpeedMasterModeCode_11 = 0x03ul,
    HME_I2C_HighSpeedMasterModeCode_12 = 0x04ul,
    HME_I2C_HighSpeedMasterModeCode_13 = 0x05ul,
    HME_I2C_HighSpeedMasterModeCode_14 = 0x06ul,
    HME_I2C_HighSpeedMasterModeCode_15 = 0x07ul,

    HME_I2C_HighSpeedMasterModeCode_MAX = HME_I2C_HighSpeedMasterModeCode_15,

} HME_I2C_HighSpeedMasterModeCodeTypedef;
/**
 * @}
 */

/**
 * \~english @defgroup HME_I2C_IntTypedef
 * \~chinese @defgroup HME_I2C_IntTypedef
 * \~ @{
 */
typedef enum {
    /*< Set if the processor attempts to read the receive buffer when it is empty */
    HME_I2C_Int_RX_Underflow = (0x01ul << 0),
    /*< Set if the receive buffer is full and an additional byte is received from an external I2C device */
    HME_I2C_Int_RX_Overflow = (0x01ul << 1),
    /*< Set when the receive buffer reaches or goes above the RX_TL threshold in the IC_RX_TL register */
    HME_I2C_Int_RX_Full = (0x01ul << 2),
    /*< Set during transmit if the transmit buffer is full and the processor attempts to issue another I2C command by
    writing to the IC_DATA_CMD register. */
    HME_I2C_Int_TX_Overflow = (0x01ul << 3),
    /*< The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL selection in the IC_CON
     * register.
     *
     * When TX_EMPTY_CTRL = 0:
     * This bit is set to 1 when the transmit buffer is at or below the threshold
     * value set in the IC_TX_TL register.
     *
     * When TX_EMPTY_CTRL = 1:
     * This bit is set to 1 when the transmit buffer is at or below the threshold value set in the IC_TX_TL
     * register and the transmission of the address/data from the internal shift register for the most recently
     * popped command is completed.
     * */
    HME_I2C_Int_TX_Empty = (0x01ul << 4),
    /*< This bit is set to 1 when I2C is acting as a slave and another I2C master is attempting to read data from I2C.
     */
    HME_I2C_Int_Read_Request = (0x01ul << 5),
    /*< This bit indicates if I2C, as an I2C transmitter, is unable to complete the intended actions on the contents of
    the transmit FIFO */
    HME_I2C_Int_TX_Abort = (0x01ul << 6),
    /*< When the I2C is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a
    transmitted byte. */
    HME_I2C_Int_RX_Done = (0x01ul << 7),
    /*< This bit captures I2C activity and stays set until it is cleared */
    HME_I2C_Int_Activity = (0x01ul << 8),
    /*< Indicates whether a STOP condition has occurred on the I2C interface regardless of whether I2C is operating in
    slave or master mode */
    HME_I2C_Int_Stop_Detect = (0x01ul << 9),
    /*< Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether I2C is
    operating in slave or master mode */
    HME_I2C_Int_Start_Detect = (0x01ul << 10),
    /*< Set only when a General Call address is received and it is acknowledged */
    HME_I2C_Int_General_Call = (0x01ul << 11),
    HME_I2C_Int_All =
        (HME_I2C_Int_RX_Underflow | HME_I2C_Int_RX_Overflow | HME_I2C_Int_RX_Full | HME_I2C_Int_TX_Overflow |
         HME_I2C_Int_TX_Empty | HME_I2C_Int_Read_Request | HME_I2C_Int_TX_Abort | HME_I2C_Int_RX_Done |
         HME_I2C_Int_Activity | HME_I2C_Int_Stop_Detect | HME_I2C_Int_Start_Detect | HME_I2C_Int_General_Call),
} HME_I2C_IntTypedef;
/**
 * @}
 */

/**
 * @defgroup HME_I2C_FlagTypedef
 * @{
 */
// TODO
typedef enum {
    HME_I2C_Flag_Activity               = (0x01 << 0), /*!< I2C Activity */
    HME_I2C_Flag_Transmit_FIFO_Not_Full = (0x01 << 1), /*!< Transmit FIFO Not Full */
    HME_I2C_Flag_Transmit_FIFO_Empty    = (0x01 << 2), /*!< Transmit FIFO Completely Empty */
    HME_I2C_Flag_Receive_FIFO_Not_Empty = (0x01 << 3), /*!< Receive FIFO Not Empty */
    HME_I2C_Flag_Receive_FIFO_Full      = (0x01 << 4), /*!< Receive FIFO Completely Full */
    HME_I2C_Flag_Master_Activity        = (0x01 << 5), /*!< Master FSM Activity Status */
    HME_I2C_Flag_Slave_Activity         = (0x01 << 6), /*!< Slave FSM Activity Status */
    HME_I2C_Flag_ALL = (HME_I2C_Flag_Activity | HME_I2C_Flag_Transmit_FIFO_Not_Full | HME_I2C_Flag_Transmit_FIFO_Empty |
                        HME_I2C_Flag_Receive_FIFO_Not_Empty | HME_I2C_Flag_Receive_FIFO_Full |
                        HME_I2C_Flag_Master_Activity | HME_I2C_Flag_Slave_Activity),
} HME_I2C_FlagTypedef;
/**
 * @}
 */

/**
 * @~english @defgroup I2C_Speed_Mode I2C Speed Mode
 * @~ @{
 */
typedef enum HME_I2C_SpeedMode {
    HME_I2C_SPEED_HIGH_SPEED_MODE,
    HME_I2C_SPEED_STANDARD_MODE,
    HME_I2C_SPEED_FAST_SPEED_MODE,
} HME_I2C_SpeedMode;
/**
 * \@~ @}
 */

/**
 * @brief I2C timing structure
 */
typedef struct {
    uint16_t I2C_High_Count;                    /*!< nano second of TSU:DAT */
    uint16_t I2C_Low_Count;                     /*!< nano second of THD:STA and TSU:STO */
    uint16_t SS_And_FS_Spike_Suppression_Limit; /*!< nano second of TBUF */
} HME_I2C_InitTimingDef;

/**
 * @brief I2C initialization structure
 */
typedef struct {
	int Target_address;
    /*< Specifies the I2C mode. This parameter can be a value of @ref HME_I2C_Mode */
    HME_I2C_ModeTypeDef Mode;
    /*< Specifies the I2C mode. This parameter can be a value of @ref HME_I2C_Mode */
    HME_I2C_SpeedModeTypeDef SpeedMode;
    /*< 7- or 10-bits width address, ref as @ref HME_I2C_MasterAddrWidth */
    HME_I2C_MasterAddrWidthTypedef MasterAddressWidth;
    /*< 7- or 10-bits width address, ref as @ref HME_I2C_SlaveAddrWidth */
    HME_I2C_SlaveAddrWidthTypedef SlaveAddressWidth;
	
	HME_I2C_SLAVE_DISABLETypedef Slave_Disable;
	
    HME_I2C_HighSpeedMasterModeCodeTypedef MasterModeCode;

    HME_I2C_RXFIFO_ThresholdLevelTypedef RX_ThresholdLevel;
    HME_I2C_TXFIFO_ThresholdLevelTypedef TX_ThresholdLevel;

    /*< timing structure, null if don't set */
    HME_I2C_InitTimingDef *timing;
} HME_I2C_InitTypeDef;
/**
 * @}
 */

/**
 * @brief I2C Slave initialization structure
 */
typedef struct {
	int Slave_address;
	HME_I2C_SLAVE_DISABLETypedef 	Slave_Enable;
	HME_I2C_MasterAddrWidthTypedef 	MasterAddrWidth;
	HME_I2C_SlaveAddrWidthTypedef	SlaveAddrWidth;
	HME_I2C_SpeedModeTypeDef 		SpeedMode;
	HME_I2C_ModeTypeDef 			Mode;
 
} HME_I2C_Slave_InitTypeDef;
/**
 * @}
 */


/**
 * @}
 */

/*****************************************************************************/

/**
 * ~english @brief Deinitializes the I2C peripheral registers to their default reset values.
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @retval None
 *
 * ~chinese @brief 复位 I2C 外设寄存器为默认值
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @retval 无
 */
extern void HME_I2C_DeInit(I2C_Type *I2Cx);

/**
 * ~english @brief I2C initialization
 * ~english @note This function should be called at first before any other interfaces.
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] init A pointer to structure I2C_InitTypeDef
 * ~english @retval None
 *
 * ~chinese @brief I2C initialization
 * ~chinese @note This function should be called at first before any other interfaces.
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] init A pointer to structure I2C_InitTypeDef
 * ~chinese @retval 无
 */
extern void HME_I2C_Init(I2C_Type *I2Cx, HME_I2C_InitTypeDef *I2C_Init);

/**
 * ~english @brief Fills each I2C_InitTypeDef member with its default value.
 * ~english @param[in] init A pointer to structure I2C_InitTypeDef which will be initialized.
 * ~english @retval None
 *
 * ~chinese @brief Fills each I2C_InitTypeDef member with its default value.
 * ~chinese @param[in] init A pointer to structure I2C_InitTypeDef which will be initialized.
 * ~chinese @retval 无
 */
extern void HME_I2C_StructInit(HME_I2C_InitTypeDef *init);

/**
 * ~english @brief Enable or disable I2C.
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Enable The bit indicates if the specific I2C is enable or not
 * ~english @retval None
 *
 * ~chinese @brief 使用或者禁能 I2C.
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Enable The bit indicates if the specific I2C is enable or not
 * ~chinese @retval 无
 */
extern void HME_I2C_Cmd(I2C_Type *I2Cx, bool enable);

/**
 * ~english @brief Enable or disable I2C interrupt.
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Int interrupt mask bits, which can be the combination of @ref HME_I2C_IntTypedef
 * ~english @param[in] Enable The bit indicates if specific interrupts are enable or not
 * ~english @retval None
 *
 * ~chinese @brief 使用或者禁能 I2C 中断。
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Int interrupt mask bits, which can be the combination of @ref HME_I2C_IntTypedef
 * ~chinese @param[in] Enable The bit indicates if specific interrupts are enable or not
 * ~chinese @retval 无
 */
extern void HME_I2C_ITConfig(I2C_Type *I2Cx, HME_I2C_IntTypedef Int, bool enable);

/**
 * ~english @brief Check specific interrupts are set or not
 * ~english @param[in] I2Cx: I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Int: interrupt mask bits, which can be the combination of @ref HME_I2C_IntTypedef
 * ~english @retval bool: The bit indicates if specific interrupts are enable or not
 *
 * ~chinese @brief 检查 I2C 特定中断是否被设置
 * ~chinese @param[in] I2Cx: I2C 外设, 包括 I2C0 和 I2C1
 * ~chinese @param[in] Int: interrupt mask bits, which can be the combination of @ref HME_I2C_IntTypedef
 * ~chinese @retval bool: The bit indicates if specific interrupts are enable or not
 */
extern uint16_t HME_I2C_GetITStatus(I2C_Type *I2Cx);

/**
 * ~english @brief Clear specific interrupts
 * ~english @note Specific interrupt clear will clear correspective status as well
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Int interrupt mask bits, which can be the combination of @ref I2C_Int
 * ~english @retval None
 *
 * ~chinese @brief Clear specific interrupts
 * ~chinese @note Specific interrupt clear will clear correspective status as well
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Int interrupt mask bits, which can be the combination of @ref I2C_Int
 * ~chinese @retval 无
 */
extern void HME_I2C_ClearITPendingBit(I2C_Type *I2Cx, uint32_t Int);

/**
 * ~english @brief Check specific status are set or not
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Flag Status mask bits, which can be the combination of @ref HME_I2C_FlagTypedef
 * ~english @retval bool The bit indicates if specific status are set or not
 *
 * ~chinese @brief Check specific status are set or not
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Flag Status mask bits, which can be the combination of @ref HME_I2C_FlagTypedef
 * ~chinese @retval bool The bit indicates if specific status are set or not
 */
extern bool HME_I2C_GetFlagStatus(I2C_Type *I2Cx, HME_I2C_FlagTypedef Flag);

/**
 * ~english @brief Clear specific status
 * ~english @note Specific status clear will clear correspective interrupt as well
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Flag Status mask bits, which can be the combination of @ref I2C_Flag
 * ~english @retval None
 *
 * ~chinese @brief Clear specific status
 * ~chinese @note Specific status clear will clear correspective interrupt as well
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Flag Status mask bits, which can be the combination of @ref I2C_Flag
 * ~chinese @retval 无
 */
extern void HME_I2C_ClearFlag(I2C_Type *I2Cx, uint32_t Flag);
extern uint8_t HME_I2C_Clear_INTR(I2C_Type *I2Cx);

/**
 * ~english @brief I2C send read request in master mode
 * ~english @note Users must call I2C_StopReq between 2 requests
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] Addr 7- or 10-bits address
 * ~english @param[in] size Expected data size to be read
 * ~english @retval bool The bit indicates if read request to be sent is valid
 * ~english @see I2C_StopReq
 *
 * ~chinese @brief I2C send read request in master mode
 * ~chinese @note Users must call I2C_StopReq between 2 requests
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] Addr 7- or 10-bits address
 * ~chinese @param[in] size Expected data size to be read
 * ~chinese @retval bool The bit indicates if read request to be sent is valid
 * ~chinese @see I2C_StopReq
 */
//extern bool HME_I2C_ReadReq(I2C_Type *I2Cx, uint16_t Addr, uint8_t size);
extern bool HME_I2C_ReadReq(I2C_Type *I2Cx);
/**
 * ~english @brief Read data from I2C
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] size Expected data size to be read
 * ~english @param[out] Data A user-allocated buffer to fetch data to be read
 * ~english @retval uint8_t Actual read data size
 *
 * ~chinese @brief Read data from I2C
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] size Expected data size to be read
 * ~chinese @param[out] Data A user-allocated buffer to fetch data to be read
 * ~chinese @retval uint8_t Actual read data size
 */
extern uint8_t HME_I2C_ReadFifo(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern uint8_t HME_I2C_GetData(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern uint8_t HME_I2C_INTRGetdataReq(I2C_Type *I2Cx, uint8_t size);
/**
 * ~english @brief I2C send write request in master or slave mode
 * ~english @note Users must call I2C_StopReq between 2 requests
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] size Expected data size to be written, includes the first data
 * ~english @param[in] Addr 7- or 10-bits address
 * ~english @param[in] firstData The first data to be written
 * ~english @retval bool The bit indicates if write request to be sent is valid
 * ~english @see I2C_StopReq
 *
 * ~chinese @brief I2C send write request in master or slave mode
 * ~chinese @note Users must call I2C_StopReq between 2 requests
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] size Expected data size to be written, includes the first data
 * ~chinese @param[in] Addr 7- or 10-bits address
 * ~chinese @param[in] firstData 将要写的第一个数据
 * ~chinese @retval bool 表示写请求是否有效
 * ~chinese @see I2C_StopReq
 */
extern bool HME_I2C_WriteReq(I2C_Type *I2Cx, uint32_t size, uint8_t firstData);

/**
 * ~english @brief Write data to I2C
 * ~english @param[in] I2Cx I2C peripheral, which is I2C0 or I2C1
 * ~english @param[in] size Expected data size to be written
 * ~english @param[in] Data A pointer to the data to be written
 * ~english @retval uint8_t Actual written data size
 *
 * ~chinese @brief Write data to I2C
 * ~chinese @param[in] I2Cx I2C 外设, 可以是 I2C0 或 I2C1
 * ~chinese @param[in] size 预期传输的数据的个数
 * ~chinese @param[in] Data 用户提供的buffer用来存储读取到的数据
 * ~chinese @retval uint8_t 实际写入的数据
 */
extern uint8_t HME_I2C_WriteFifo(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern uint8_t HME_I2C_Send(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern uint8_t HME_I2C_INTRSend(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern uint8_t HME_I2C_SendData(I2C_Type *I2Cx, uint8_t size, uint8_t *data);
extern void HME_I2C_SETDMATx(I2C_Type *I2Cx, uint8_t t_level, uint8_t enbale);
extern void HME_I2C_SETDMARx(I2C_Type *I2Cx, uint8_t r_level, uint8_t enbale);
extern void HME_I2C_SLAVE_Init(I2C_Type *I2Cx, HME_I2C_Slave_InitTypeDef *Init);

/*****************************************************************************/

/** @defgroup HME_I2C_Private_Macro HME I2C Private Macros
 * @{
 */
#define IS_HME_I2C_ALL_PERIPH(__P) (((__P) == I2C0) || ((__P) == I2C1))

#define IS_HME_I2C_MODE(__M) (((__M) == HME_I2C_Mode_Slave) || ((__M) == HME_I2C_Mode_Master))

#define IS_HME_I2C_SPEEDMODE(__SM)                                                                                     \
    (((__SM) == HME_I2C_SpeedMode_Standard) || ((__SM) == HME_I2C_SpeedMode_Fast) || ((__SM) == HME_I2C_SpeedMode_High))

#define IS_HME_I2C_MASTER_ADDR_WIDTH(__W)                                                                              \
    (((__W) == HME_I2C_MasterAddrWidth_7BIT) || ((__W) == HME_I2C_MasterAddrWidth_10BIT))

#define IS_HME_I2C_SLAVE_ADDR_WIDTH(__W)                                                                               \
    (((__W) == HME_I2C_SlaveAddrWidth_7BIT) || ((__W) == HME_I2C_SlaveAddrWidth_10BIT))

#define IS_HME_I2C_INT(INT) (((INT) != 0) && (((INT) & ~HME_I2C_Int_All) == 0))

#define IS_HME_I2C_FLAG(FLAG) (((FLAG) != 0) && (((FLAG) & ~I2C_Flag_ALL) == 0))

#define IS_HME_I2C_RX_THRESHOLDLEVEL(__L) (__L <= HME_I2C_RXFIFO_ThresholdLevel_MAX)

#define IS_HME_I2C_TX_THRESHOLDLEVEL(__L) (__L <= HME_I2C_TXFIFO_ThresholdLevel_MAX)

/**
 * @}
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
