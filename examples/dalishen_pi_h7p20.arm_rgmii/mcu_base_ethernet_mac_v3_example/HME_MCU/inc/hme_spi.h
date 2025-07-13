/*
 * @file     hme_spi.h
 * @brief HME HeaderFile
 * @version  0.1
 * @date     01. March 2021
 */

#ifndef __HME_SPI_H__
#define __HME_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/**
 * @addtogroup HME
 * @{
 */

/**
 * @addtogroup HME_SPI
 * @{
 */
enum {
	SPI_AddrLen_1Byte = 0,
	SPI_AddrLen_2Byte = 1,
	SPI_AddrLen_3Byte = 2,
	SPI_AddrLen_4Byte = 3,
};


enum {
	SPI_Transfermode_Write_read_same_time = 0,
	SPI_Transfermode_Write_only,
	SPI_Transfermode_Read_only,
	SPI_Transfermode_Write_Read,
	SPI_Transfermode_Read_Write,
	SPI_Transfermode_Write_Dummy_Read,
	SPI_Transfermode_Read_Dummy_Write,
	SPI_Transfermode_None_Data,
	SPI_Transfermode_Dummy_Write,
	SPI_Transfermode_Dummy_Read,
};

enum {
	SPI_data_phase_format_Single_mode = 0,
	SPI_data_phase_format_Dual_mode ,
	SPI_data_phase_format_Quad_mode ,
};

enum {
	SPI_CMD_Disable = 0,
	SPI_CMD_Enable = 1,
};

enum {
	SPI_ADDR_Disable = 0,
	SPI_ADDR_Enable = 1,
};

enum {
	SPI_MasterMode 	= 0,
	SPI_SlaveMode 	= 1,
};

enum {
	SPI_DataMerge_Disable 	= 0,
	SPI_DataMerge_Enable 	= 1,
};
/*****************************************************************************/

#define SPI_Data_Width_8bit 			7
#define SPI_Data_Width_32bit 			31

#define SPI_Status_Active 				(0x01 << 0)
#define SPI_Status_RXEMPTY				(0x01 << 14)
#define SPI_Status_RXFULL				(0x01 << 15)
#define SPI_Status_TXEMPTY				(0x01 << 22)
#define SPI_Status_TXFULL				(0x01 << 23)

/**
 * \~ @}
 */

#define SPI_RXFIFOORInt_ENABLE  		0x01
#define SPI_TXFIFOURInt_ENABLE  		0x02
#define SPI_RXFIFOInt_ENABLE	 		0x04
#define SPI_TXFIFOInt_ENABLE	 		0x08
#define SPI_EndInt_ENABLE	 			0x10
#define SPI_SlvCmdInt_ENABLE			0x20


#define SPI_INT_STATUS_RXFIFOORInt  	0x01
#define SPI_INT_STATUS_TXFIFOURInt  	0x02
#define SPI_INT_STATUS_RXFIFOInt	 	0x04
#define SPI_INT_STATUS_TXFIFOInt	 	0x08
#define SPI_INT_STATUS_EndInt	 		0x10
#define SPI_INT_STATUS_SlvCmdInt		0x20


/**
 * \~english @defgroup SPI_InitTypeDef SPI initialization structure
 * \~chinese @defgroup SPI_InitTypeDef SPI 初始化结构体
 */
typedef struct {
    uint8_t AddrLen;
	uint8_t DataLen;
	uint8_t DataMerge;
	uint8_t Mode;
	uint8_t CPOL;
	uint8_t CPHA;
	uint8_t TransMode ;
	uint8_t DualQuad ;
	uint8_t DummyCnt ;
	uint16_t RdTranCnt ;
	uint16_t WrTranCnt ;
	uint32_t SPI_SlaveAddr ;
	uint8_t SCLK_DIV;	
} SPI_InitTypeDef;
/**
 * \~ @}
 */

/*****************************************************************************/

/**
 * \~english @brief Initialize SPI
 * \~english @param[in] Init: A pointer to structure @ref SPI_InitTypeDef
 * \~english @retval None
 *
 * \~chinese @brief 初始化 SPI
 * \~chinese @param[in] Init: 指向 @ref SPI_InitTypeDef 的指针
 * \~chinese @retval 无
 */
extern void HME_SPI_Init(SPI_Type *SPIx, SPI_InitTypeDef *Init);

/**
  * \~english @brief Fills each SPI_InitTypeDef member with its defaUt value.
  * \~english @param[in] Init: A pointer to structure SPI_InitTypeDef which will be initialized.
  * \~english @retval None
  *
  * \~chinese @brief 填充结构体 @ref SPI_InitTypeDef 的成员
  * \~chinese @param[in] Init: 已初始化的结构体 @ref SPI_InitTypeDef 的指针。
  * \~chinese @retval 无
  */
extern void HME_SPI_StructInit(SPI_InitTypeDef *Init);

/**
 * \~english @brief Enable or disable SPI.
 * \~english @param[in] SPIx: SPI peripheral, which is SPI0 or SPI1
 * \~english @param[in] Enable The bit indicates if the specific SPI is enable or not
 * \~english @retval None
 *
 * \~chinese @brief 使能或者禁能 SPI.
 * \~chinese @param[in] SPIx: SPI 外设, 可以是 SPI0 或者 SPI1。
 * \~chinese @param[in] Enable: 这个位表示SPI使能或者禁能
 * \~chinese @retval 无
 */
extern void HME_SPI_Cmd(SPI_Type *SPIx, bool Enable);

/**
 * \~english @brief Enable or disable SPI interrupt.
 * \~english @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
 * \~english @param[in] Int interrupt mask bits, which can be the combination of @ref SPI_Int
 * \~english @param[in] Enable: The bit indicates if specific interrupts are enable or not
 * \~english @retval None
 *
 * \~chinese @brief 使能或者禁能 SPI interrupt.
 * \~chinese @param[in] SPIx: SPI 外设, 可以是 SPI0 或者 SPI1。
 * \~chinese @param[in] Int: 中断掩码位, 是 @ref SPI_Int 的任意组合
 * \~chinese @param[in] Enable: 使能或者禁能给定中断
 * \~chinese @retval 无
 */
extern void HME_SPI_ITConfig(SPI_Type *SPIx, uint32_t Int, bool Enable);

/**
 * \~english @brief Check specific flags are set or not
 * \~english @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
 * \~english @param[in] Flag which can be the combination of @ref SPI_Flag
 * \~english @retval bool The bit indicates if specific flags are set or not
 *
 * \~chinese @brief Check specific flags are set or not
 * \~chinese @param[in] SPIx: SPI 外设, 可以是 SPI0 或者 SPI1。
 * \~chinese @param[in] Flag: 标志掩码位, 是 @ref SPI_Flag 的任意组合
 * \~chinese @retval bool 获取给定所有标志是否都触发
 */
extern bool HME_SPI_GetFlagStatus(SPI_Type *SPIx, uint32_t Flag);
extern uint32_t HME_SPI_GetFlagIntStatus(SPI_Type *SPIx);
extern bool HME_SPI_GetITStatus(SPI_Type *SPIx, uint32_t Int);
/**
 * \~english @brief Clear specific interrupts
 * \~english @param[in] SPIx SPI peripheral, which is SPI0 or SPI1
 * \~english @param[in] Int interrupt mask bits, which can be the combination of @ref SPI_Int
 * \~english @retval None
 *
 * \~chinese @brief Clear specific interrupts
 * \~chinese @param[in] SPIx: SPI 外设, 可以是 SPI0 或者 SPI1。
 * \~chinese @param[in] Int: 中断掩码位, 是 @ref SPI_Int 的任意组合
 * \~chinese @retval 无
 */
extern void HME_SPI_ClearITPendingBit(SPI_Type *SPIx, uint32_t Int);

/*****************************************************************************/
extern void SPI_Set_Transfer_Control_Reg(SPI_Type *SPIx,uint8_t TransferMode,bool CmdEn,bool AddrEn,uint32_t RdCnt,uint32_t WrCnt);
extern void SPI_Set_Cmd(SPI_Type *SPIx,uint8_t Cmd);
extern void SPI_Set_Addr(SPI_Type *SPIx,uint32_t Addr);
extern void SPI_Set_DualQuad_Mode(SPI_Type *SPIx,uint8_t dualquad_mode);
extern void SPI_SendData(SPI_Type *SPIx, uint8_t *pSendBuf, uint32_t DataCnt);
extern uint32_t SPI_RecieveData(SPI_Type *SPIx, uint32_t *pRecvBuf, uint32_t DataCnt);
extern void SPI_Set_TransThreshold(SPI_Type *SPIx,uint8_t level);
extern void SPI_Set_RecvThreshold(SPI_Type *SPIx,uint8_t level);
extern void SPI_SET_TX_DMA(SPI_Type *SPIx,bool Enable);
extern void SPI_SET_RX_DMA(SPI_Type *SPIx,bool Enable);
/**-
 * \~english @defgroup HME_SPI_Private_Macro HME SPI Private Macros
 * \~chinese @defgroup HME_SPI_Private_Macro HME SPI 私有宏
 * \~ @{
 */
#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI0) || ((PERIPH) == SPI1) || ((PERIPH) == SPI2) || ((PERIPH) == QSPI))
#define IS_SPI_Trasmit_FIFO_Threshold_Level_Vaild(__L) (__L <= 0x07)
#define IS_SPI_Receive_FIFO_Threshold_Level_Vaild(__L) (__L <= 0x07)
#define HME_SPI_SLAVE_0      (1U << 0)          // select line number is 1

/**
 * \~ @}
 */

#ifdef __cplusplus
}
#endif

#endif
