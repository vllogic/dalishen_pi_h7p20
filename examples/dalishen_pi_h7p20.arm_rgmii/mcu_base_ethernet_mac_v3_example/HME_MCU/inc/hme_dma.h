/*
 * @file hme_dma.h
 * @brief HME HeaderFile
 * @version 0.1
 * @date 01. March 2021
 */

#ifndef __HME_DMA_H__
#define __HME_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_conf.h"

/****d* dmac.data/dw_dmac_channel_number
 * DESCRIPTION
 *  This data type is used to describe the DMA controller's channel
 *  number. The assigned enumerated value matches the register
 *  value that needs to be written to enable the channel. This data
 *  type is used by many of the API functions in the driver, a
 *  select few are listed:
 * SEE ALSO
 *  dw_dmac_enableChannel(), dw_dmac_disableChannel(),
 *  dw_dmac_suspendChannel(), dw_dmac_setAddress()
 * SOURCE
 */
enum dw_dmac_channel_number {
    Dmac_no_channel   = 0x0000,
    Dmac_channel0     = 0x0101,
    Dmac_channel1     = 0x0202,
    Dmac_channel2     = 0x0404,
    Dmac_channel3     = 0x0808,
    Dmac_channel4     = 0x1010,
    Dmac_channel5     = 0x2020,
    Dmac_channel6     = 0x4040,
    Dmac_channel7     = 0x8080,
    Dmac_all_channels = 0xffff
};
/*****/

/****d* dmac.data/dw_dmac_src_dst_select
 * DESCRIPTION
 *  This data type is used to select the source and/or the
 *  destination for a specific DMA channel when using some
 *  of the driver's API functions.
 *  This data type is used by many of the API functions in
 *  the driver, a select few are listed:
 * SEE ALSO
 *  dw_dmac_setAddress(), dw_dmac_setMstSelect(),
 *  dw_dmac_setBurstTransLength(), dw_dmac_setHsPolarity()
 * SOURCE
 */
enum dw_dmac_src_dst_select {
    Dmac_src     = 0x1,
    Dmac_dst     = 0x2,
    Dmac_src_dst = 0x3
};
/*****/

/****d* dmac.data/dw_dmac_lock_bus_ch
 * DESCRIPTION
 *  This data type is used to select the bus and/or the channel
 *  when using the specified driver API functions to lock DMA
 *  transfers. The selection affects which DMA Controller
 *  bit field within the CFGx register is accessed.
 * SEE ALSO
 *  dw_dmac_setLockLevel(), dw_dmac_getLockLevel(),
 *  dw_dmac_setLockEnable(), dw_dmac_getLockEnable()
 * SOURCE
 */
enum dw_dmac_lock_bus_ch {
    Dmac_lock_bus     = 0x1,
    Dmac_lock_channel = 0x2,
    Dmac_lock_bus_ch  = 0x4
};
/*****/

/****d* dmac.data/dw_dmac_sw_hw_hs_select
 * DESCRIPTION
 *  This data type is used to select a software or hardware interface
 *  when using the specified driver API functions to access the
 *  handshaking interface on a specified DMA channel.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CFGx.HS_SEL_SRC, CFGx.HS_SEL_DST
 * SEE ALSO
 *  dw_dmac_setHandshakingMode(), dw_dmac_getHandshakingMode()
 * SOURCE
 */
enum dw_dmac_sw_hw_hs_select {
    Dmac_hs_hardware   = 0x0,
    Dmac_hs_software   = 0x1
};
/*****/

/****d* dmac.data/dw_dmac_scatter_gather_param
 * DESCRIPTION
 *  This data type is used to select the count or interval bit field
 *  when using the specified driver API functions to access the
 *  scatter or gather registers on the DMA controller.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - SGRx.SGC, SGRx.SGI, DSRx.DSC, DSRx.DSI
 * SEE ALSO
 *  dw_dmac_setScatterParam(), dw_dmac_getScatterParam(),
 *  dw_dmac_setGatherParam(), dw_dmac_getGatherParam()
 * SOURCE
 */
enum dw_dmac_scatter_gather_param {
    Dmac_sg_count    = 0x0,
    Dmac_sg_interval = 0x1
};
/*****/

/****d* dmac.data/dw_dmac_irq
 * DESCRIPTION
 *  This data type is used to select the interrupt type on a specified
 *  DMA channel when using the specified driver API functions to access
 *  interrupt registers within the DMA Controller.
 * SEE ALSO
 *  dw_dmac_maskIrq(), dw_dmac_unmaskIrq(), dw_dmac_clearIrq(),
 *  dw_dmac_isIrqActive(), dw_dmac_isRawIrqActive()
 * SOURCE
 */
enum dw_dmac_irq {
    Dmac_irq_none       = 0x00,     // no interrupts
    Dmac_irq_tfr        = 0x01,     // transfer complete
    Dmac_irq_block      = 0x02,     // block transfer complete
    Dmac_irq_srctran    = 0x04,     // source transaction complete
    Dmac_irq_dsttran    = 0x08,     // destination transaction complete
    Dmac_irq_err        = 0x10,     // error
    Dmac_irq_all        = 0x1f      // all interrupts
};
/*****/

/****d* dmac.data/dw_dmac_software_req
 * DESCRIPTION
 *  This data type is used to select which of the software request
 *  registers are accessed within the DMA Controller when using the
 *  specified driver API functions.
 * SEE ALSO
 *  dw_dmac_setSoftwareRequest(), dw_dmac_getSoftwareRequest()
 * SOURCE
 */
enum dw_dmac_software_req {
    Dmac_request        = 0x1, /* ReqSrcReq/ReqDstReq */
    Dmac_single_request = 0x2, /* SglReqSrcReq/SglReqDstReq */
    Dmac_last_request   = 0x4  /* LstReqSrcReq/LstReqDstReq */
};
/*****/

/****d* dmac.data/dw_dmac_master_number
 * DESCRIPTION
 *  This data type is used to select the master interface number
 *  on the DMA Controller when using the specified driver API
 *  functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CTLx.SMS, CTLx.DMS, LLPx.LMS
 * SEE ALSO
 *  dw_dmac_setMstSelect(), dw_dmac_getMstSelect(),
 *  dw_dmac_setListMstSelect(), dw_dmac_getListMstSelect()
 * SOURCE
 */
enum dw_dmac_master_number {
    Dmac_master1 = 0x0,
    Dmac_master2 = 0x1,
    Dmac_master3 = 0x2,
    Dmac_master4 = 0x3
};
/*****/

/****d* dmac.data/dw_dmac_transfer_type
 * DESCRIPTION
 *  This data type is used for selecting the transfer type for a
 *  specified DMA channel when using the specified driver API
 *  functions. See the DW_ahb_dmac databook for a detailed
 *  description on these transfer types.
 * SEE ALSO
 *  dw_dmac_setTransferType(), dw_dmac_getTransferType()
 * SOURCE
 */
enum dw_dmac_transfer_type {
    Dmac_transfer_row1  = 0x1, /* single block or last multi-block */
                               /*  no write back                   */
    Dmac_transfer_row2  = 0x2, /* multi-block auto-reload DAR      */
                               /*  contiguous SAR no write back    */
    Dmac_transfer_row3  = 0x3, /* multi-block auto reload SAR      */
                               /*  contiguous DAR no write back    */
    Dmac_transfer_row4  = 0x4, /* multi-block auto-reload SAR DAR  */
                               /*  no write back                   */
    Dmac_transfer_row5  = 0x5, /* single block or last multi-block */
                               /*  with write back                 */
    Dmac_transfer_row6  = 0x6, /* multi-block linked list DAR      */
                               /*  contiguous SAR with write back  */
    Dmac_transfer_row7  = 0x7, /* multi-block linked list DAR auto */
                               /*  reload SAR  with write back     */
    Dmac_transfer_row8  = 0x8, /* multi-block linked list SAR      */
                               /*  contiguous DAR with write back  */
    Dmac_transfer_row9  = 0x9, /* multi-block linked list SAR auto */
                               /*  reload DAR with write back      */
    Dmac_transfer_row10 = 0xa  /* multi-block linked list SAR DAR  */
                               /*  with write back                 */
};
/*****/

/****d* dmac.data/dw_dmac_transfer_flow
 * DESCRIPTION
 *  This data type is used for selecting the transfer flow device
 *  (memory or peripheral device) and for setting the flow control
 *  device for the DMA transfer when using the specified driver
 *  API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CTLx.TT_FC
 * SEE ALSO
 *  dw_dmac_setMemPeriphFlowCtl(), dw_dmac_getMemPeriphFlowCtl()
 * SOURCE
 */
enum dw_dmac_transfer_flow {
    Dmac_mem2mem_dma    = 0x0, /* mem to mem - DMAC   flow ctlr */
    Dmac_mem2prf_dma    = 0x1, /* mem to prf - DMAC   flow ctlr */
    Dmac_prf2mem_dma    = 0x2, /* prf to mem - DMAC   flow ctlr */
    Dmac_prf2prf_dma    = 0x3, /* prf to prf - DMAC   flow ctlr */
    Dmac_prf2mem_prf    = 0x4, /* prf to mem - periph flow ctlr */
    Dmac_prf2prf_srcprf = 0x5, /* prf to prf - source flow ctlr */
    Dmac_mem2prf_prf    = 0x6, /* mem to prf - periph flow ctlr */
    Dmac_prf2prf_dstprf = 0x7  /* prf to prf - dest   flow ctlr */
};
/*****/

/****d* dmac.data/dw_dmac_burst_trans_length
 * DESCRIPTION
 *  This data type is used for selecting the burst transfer length
 *  on the source and/or destination of a DMA channel when using the
 *  specified driver API functions. These transfer length values do
 *  not relate to the AMBA HBURST parameter.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CTLx.SRC_MSIZE, CTLx.DEST_MSIZE
 * SEE ALSO
 *  dw_dmac_setBurstTransLength(), dw_dmac_getBurstTransLength()
 * SOURCE
 */
enum dw_dmac_burst_trans_length {
    Dmac_msize_1   = 0x0,
    Dmac_msize_4   = 0x1,
    Dmac_msize_8   = 0x2,
    Dmac_msize_16  = 0x3,
    Dmac_msize_32  = 0x4,
    Dmac_msize_64  = 0x5,
    Dmac_msize_128 = 0x6,
    Dmac_msize_256 = 0x7
};
/*****/

/****d* dmac.data/dw_dmac_address_increment
 * DESCRIPTION
 *  This data type is used for selecting the address increment
 *  type for the source and/or destination on a DMA channel when using
 *  the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CTLx.SINC, CTLx.DINC
 * SEE ALSO
 *  dw_dmac_setAddressInc(), dw_dmac_getAddressInc()
 * SOURCE
 */
enum dw_dmac_address_increment {
    Dmac_addr_increment = 0x0,
    Dmac_addr_decrement = 0x1,
    Dmac_addr_nochange  = 0x2
};
/*****/

/****d* dmac.data/dw_dmac_transfer_width
 * DESCRIPTION
 *  This data type is used for selecting the transfer width for the
 *  source and/or destination on a DMA channel when using the specified
 *  driver API functions. This data type maps directly to the AMBA AHB
 *  HSIZE parameter.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CTLx.SRC_TR_WIDTH, CTLx.DST_TR_WIDTH
 * SEE ALSO
 *  dw_dmac_setTransWidth(), dw_dmac_getTransWidth()
 * SOURCE
 */
enum dw_dmac_transfer_width {
    Dmac_trans_width_8   = 0x0,
    Dmac_trans_width_16  = 0x1,
    Dmac_trans_width_32  = 0x2,
    Dmac_trans_width_64  = 0x3,
    Dmac_trans_width_128 = 0x4,
    Dmac_trans_width_256 = 0x5
};
/*****/

/****d* dmac.data/dw_dmac_hs_interface
 * DESCRIPTION
 *  This data type is used for selecting the handshaking interface
 *  number for the source and/or destination on a DMA channel when
 *  using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CFGx.DEST_PER, CFGx.SRC_PER
 * SEE ALSO
 *  dw_dmac_setHsInterface(), dw_dmac_getHsInterface()
 * SOURCE
 */
enum dw_dmac_hs_interface {
    Dmac_hs_if0  = 0x0,
    Dmac_hs_if1  = 0x1,
    Dmac_hs_if2  = 0x2,
    Dmac_hs_if3  = 0x3,
    Dmac_hs_if4  = 0x4,
    Dmac_hs_if5  = 0x5,
    Dmac_hs_if6  = 0x6,
    Dmac_hs_if7  = 0x7,
    Dmac_hs_if8  = 0x8,
    Dmac_hs_if9  = 0x9,
    Dmac_hs_if10 = 0xa,
    Dmac_hs_if11 = 0xb,
    Dmac_hs_if12 = 0xc,
    Dmac_hs_if13 = 0xd,
    Dmac_hs_if14 = 0xe,
    Dmac_hs_if15 = 0xf
};
/*****/

/****d* dmac.data/dw_dmac_prot_level
 * DESCRIPTION
 *  This data type is used for selecting the tranfer protection level
 *  on a DMA channel when using the specified driver API functions.
 *  This data type maps directly to the AMBA AHB HPROT parameter.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CFGx.PROTCTL
 * SEE ALSO
 *  dw_dmac_setProtCtl(), dw_dmac_getProtCtl()
 * SOURCE
 */
enum dw_dmac_prot_level {
   Dmac_noncache_nonbuff_nonpriv_opcode = 0x0, /* default prot level */
   Dmac_noncache_nonbuff_nonpriv_data   = 0x1,
   Dmac_noncache_nonbuff_priv_opcode    = 0x2,
   Dmac_noncache_nonbuff_priv_data      = 0x3,
   Dmac_noncache_buff_nonpriv_opcode    = 0x4,
   Dmac_noncache_buff_nonpriv_data      = 0x5,
   Dmac_noncache_buff_priv_opcode       = 0x6,
   Dmac_noncache_buff_priv_data         = 0x7,
   Dmac_cache_nonbuff_nonpriv_opcode    = 0x8,
   Dmac_cache_nonbuff_nonpriv_data      = 0x9,
   Dmac_cache_nonbuff_priv_opcode       = 0xa,
   Dmac_cache_nonbuff_priv_data         = 0xb,
   Dmac_cache_buff_nonpriv_opcode       = 0xc,
   Dmac_cache_buff_nonpriv_data         = 0xd,
   Dmac_cache_buff_priv_opcode          = 0xe,
   Dmac_cache_buff_priv_data            = 0xf
};
/*****/

/****d* dmac.data/dw_dmac_fifo_mode
 * DESCRIPTION
 *  This data type is used for selecting the FIFO mode on a DMA
 *  channel when using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit field(s): (x = channel number)
 *    - CFGx.FIFO_MODE
 * SEE ALSO
 *  dw_dmac_setFifoMode(), dw_dmac_getFifoMode
 * SOURCE
 */
enum dw_dmac_fifo_mode {
    Dmac_fifo_mode_single = 0x0,
    Dmac_fifo_mode_half   = 0x1
};
/*****/

/****d* dmac.data/dw_dmac_flow_ctl_mode
 * DESCRIPTION
 *  This data type is used for selecting the flow control mode on a
 *  DMA channel when using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CFGx.FCMODE
 * SEE ALSO
 *  dw_dmac_setFlowCtlMode(), dw_dmac_getFlowCtlMode()
 * SOURCE
 */
enum dw_dmac_flow_ctl_mode {
    Dmac_data_prefetch_enabled  = 0x0,
    Dmac_data_prefetch_disabled = 0x1
};
/*****/

/****d* dmac.data/dw_dmac_polarity_level
 * DESCRIPTION
 *  This data type is used for selecting the polarity level for the
 *  source and/or destination on a DMA channel's handshaking interface
 *  when using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s) / bit-field(s): (x = channel number)
 *    - CFGx.SRC_HS_POL, CFGx.DST_HS_POL
 * SEE ALSO
 *  dw_dmac_setHsPolarity(), dw_dmac_getHsPolarity()
 * SOURCE
 */
enum dw_dmac_polarity_level {
    Dmac_active_high = 0x0,
    Dmac_active_low  = 0x1
};
/*****/

/****d* dmac.data/dw_dmac_lock_level
 * DESCRIPTION
 *  This data type is used for selecting the lock level on a DMA
 *  channel when using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s)/bit field(s): (x = channel number)
 *    - CFGx.LOCK_B_L, CFGx.LOCK_CH_L
 * SEE ALSO
 *  dw_dmac_setLevel(), dw_dmac_getLockLevel()
 * SOURCE
 */
enum dw_dmac_lock_level {
    Dmac_lock_level_dma_transfer   = 0x0,
    Dmac_lock_level_block_transfer = 0x1,
    Dmac_lock_level_transaction    = 0x2
};
/*****/

/****d* dmac.data/dw_dmac_channel_priority
 * DESCRIPTION
 *  This data type is used for selecting the priority level of a DMA
 *  channel when using the specified driver API functions.
 * NOTES
 *  This data type relates directly to the following DMA Controller
 *  register(s)/bit field(s): (x = channel number)
 *    - CFGx.CH_PRIOR
 * SEE ALSO
 *  dw_dmac_setChannelPriority(), dw_dmac_getChannelPriority()
 * SOURCE
 */
enum dw_dmac_channel_priority {
    Dmac_priority_0 = 0x0,
    Dmac_priority_1 = 0x1,
    Dmac_priority_2 = 0x2,
    Dmac_priority_3 = 0x3,
    Dmac_priority_4 = 0x4,
    Dmac_priority_5 = 0x5,
    Dmac_priority_6 = 0x6,
    Dmac_priority_7 = 0x7
};

typedef enum HME_DMAC_CFGREG {
    HME_DMAC_DISABLED,
    HME_DMAC_ENABLED
} HME_DMAC_CFGREG;

typedef enum HME_DMAC_TRANS_MODE {
    HME_DMAC_RXMode,
    HME_DMAC_TXMode
} HME_DMAC_TRANS_MODE;

typedef struct {
	HME_DMAC_CFGREG DMA_ENABLE;
	uint32_t *SRC_ADDR;
	uint32_t *TAR_ADDR;
	uint8_t transtype;
	uint8_t SINC;
	uint8_t DINC;
	uint32_t BLOCK_TS;
	uint8_t SRC_MSIZE;
	uint8_t DEST_MSIZE;
	uint8_t SRC_TR_WIDTH;
	uint8_t DST_TR_WIDTH;
	uint8_t TX_REQ_NUM;
	uint8_t RX_REQ_NUM;
	uint8_t TRANS_DIR;
} HME_DMAC_InitTypeDef;


extern void HME_DMAC_StructInit(HME_DMAC_InitTypeDef *ExitIT);
extern void HME_DMA_Init(DMAC_Type *DMACx, HME_DMAC_InitTypeDef *DMAC_Init);
extern void HME_DMA_CFGREG(DMAC_Type *DMACx,uint32_t value);
extern void HME_DMA_CHENREG(DMAC_Type *DMACx,uint32_t val);
extern void HME_DMA_ENABLE_INTR(DMAC_Type *DMACx,bool enable);
extern void HME_DMAC_CLEARTFR(DMAC_Type *DMACx,uint32_t val);
extern uint32_t HME_DMAC_GETINTSTATE(DMAC_Type *DMACx);
extern void HME_DMAC_DISABLE(DMAC_Type *DMACx);
extern void HME_DMAC_ENABLE(DMAC_Type *DMACx);

#ifdef __cplusplus
}
#endif

#endif
