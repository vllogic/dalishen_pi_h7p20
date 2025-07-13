#include "sys_reg.h"



//*******************************************************************//
//*******************************************************************//
//*******************************************************************//
//M3 AHB
#ifdef P0_USER_AHB_ENABLE

void user_ahb_wr(uint32_t offset, uint32_t din)
{
	__IO uint32_t *reg_set;
	reg_set=(__IO uint32_t *)(USER_AHB_SLV_BASE+offset);
	*reg_set=din;
}

uint32_t user_ahb_rd(uint32_t offset)
{
	__IO uint32_t *reg_set;
	uint32_t tmp;
	reg_set=(__IO uint32_t *)(USER_AHB_SLV_BASE+offset);
	tmp=*reg_set;
	return tmp;
}

#endif
//*******************************************************************//
//*******************************************************************//
//*******************************************************************//
// APB
#ifdef USER_APB_ENABLE
void user_apb_wr(uint32_t offset, uint32_t din)
{
	__IO uint32_t *reg_set;
	reg_set=(__IO uint32_t *)(USER_APB_REG_BASE+offset);
	*reg_set=din;
}

uint32_t user_apb_rd(uint32_t offset)
{
	__IO uint32_t *reg_set;
	uint32_t tmp;
	reg_set=(__IO uint32_t *)(USER_APB_REG_BASE+offset);
	tmp=*reg_set;
	return tmp;
}

#endif


void delay_t(int n) 
{
	int i,j;
	for (i=0; i<=n; i++)
		for (j=0; j<=5; j++);
}

void SYS_FP_BRG_MODE_CFG(void)
{
	FP_BRG_MODE_CFG->FP_BRG_MODE_b.bypass_fp_mst = 0;
	FP_BRG_MODE_CFG->FP_BRG_MODE_b.bypass_fp_slv = 0;
	FP_BRG_MODE_CFG->FP_BRG_MODE_b.sync_mode_fp_slv = 0;
	return;
}

void SYS_RST_MUX_CFG(void)
{
	RST_MUX_CFG->RST_MUX_b.rstn_mux_81_sel = 0;
	RST_MUX_CFG->RST_MUX_b.rstn_mux_41_sel = 0;
	RST_MUX_CFG->RST_MUX_b.clken_mux_41_sel = 0;
}

void SYS_CLK_MUX_CFG(void)
{
	CLK_MUX_CFG->CLK_MUX_b.M3soc_clk_mux_81_sel = 0;
}

void SYS_SRAM0_CLK_MUX_CFG(void)
{
	SRAM0_CLK_MUX_CFG->SRAM0_CLK_MUX = 0;
}

void SYS_SRAM1_CLK_MUX_CFG(void)
{
	SRAM1_CLK_MUX_CFG->SRAM1_CLK_MUX = 0;
}

#ifdef HME_H7

void SYS_SRAM0_MODE_CFG(void)
{
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_slp = 0x1FF;
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_sd = 0x1FF;
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_ram_switch = 0x0;
	return;
}
	
void SYS_SRAM1_MODE_MUX_CFG(void)
{
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_slp = 0x1FF;
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_sd = 0x1FF;
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_ram_switch = 0x0;
	return;
}

void SYS_SOC_CLK_MODE_CFG(void)
{
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3soc_clk_switch   = 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3cpr_m3soc_clk_en = 1;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3cpr_m3bus_clk_en = 1;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.pclk_div 			= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.hclk_div_fp 		= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.Soc2ccb_osc_en 	= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.Soc2ccb_clk_en 	= 0;
	
	return;	
}

#endif

#ifdef HME_P2

void SYS_SRAM0_MODE_CFG(void)
{
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_slp = 0x1;
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_sd = 0x1;
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_ram_switch = 0x0;
	return;
}
	
void SYS_SRAM1_MODE_MUX_CFG(void)
{
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_slp = 0x1;
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_sd = 0x1;
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_ram_switch = 0x0;
	return;
}

void SYS_SOC_CLK_MODE_CFG(void)
{
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3soc_clk_switch   = 1;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3cpr_m3soc_clk_en = 1;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3cpr_m3bus_clk_en = 1;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.pclk_div 			= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.hclk_div_fp 		= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.Soc2ccb_osc_en 	= 0;
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.Soc2ccb_clk_en 	= 0;
	
	return;	
}

#endif

void SYS_MCU_SOFTRESET(bool val)
{
	hme_assert(IS_CLK_SWITCH_RANGE(val));
	SOFT_RESET_EN_CFG->SOFT_RESET_b.m3cpr_m3soc_sft_rstn = val;
}

void SYS_SRAM0_SWITCH(bool val)
{
	hme_assert(IS_CLK_SWITCH_RANGE(val));
	SRAM0_MODE_CFG->SRAM0_MODE_b.Sram0_ram_switch = val;
}

void SYS_SRAM1_SWITCH(bool val)
{
	hme_assert(IS_CLK_SWITCH_RANGE(val));
	SRAM1_MODE_CFG->SRAM1_MODE_b.Sram1_ram_switch = val;
}

//设置hclk的分频系数 分频系数 = div + 1
void SYS_SET_HCLK_DIV(uint8_t div)
{
	hme_assert(IS_PCLK_DIV_RANGE(div));
	
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.hclk_div_fp = div;
	
	return;
}

//设置pclk的分频系数 分频系数 = div + 1
void SYS_SET_PCLK_DIV(uint8_t div)
{
	hme_assert(IS_PCLK_DIV_RANGE(div));
	
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.pclk_div = div;
	
	return;
}

//时钟切换，crg时钟或ccb时钟
void SYS_CLK_SWITCH(BOOL val)
{
	hme_assert(IS_CLK_SWITCH_RANGE(val));
	
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3soc_clk_switch = val;   	//val--0 ：crg clk , val--1 : ccb clk
	
	return;
}

//MCU启用dma功能
void SYS_MCU_DMA_ENABLE(void)
{
	DMA_MODE_CFG->DMA_MODE = ENABLE_ALLDMA;
	return;
}

//芯片configdone后flash由谁控制
void SYS_CFGDONE_FLASH_CTRL(uint8_t val)
{
	hme_assert(IS_SPI_MODE_RANGE(val));
	
	SPI_MODE_CFG->SPI_MODE_b.Qspi_mst = val;    				//0:ccb   1 : mcu
	
	return;
}

//FPGA访问SRAM使能 
void SYS_IF_EN0_ForSRAM(void)
{
	FP_IF_EN0_CFG->FP_IF_EN0_b.Fp_sram_en = 0x03FFFF;
}	

//MCU启用所有外设和ahb、apb接口
void SYS_IF_EN1_ForPRIPHERAL(void)
{
	FP_IF_EN1_CFG->FP_IF_EN1 	= ENABLE_ALLINTERFACE;
	
	return;
}


//芯片reconfig，offset为镜像在flash中的起始地址
#ifdef HME_H7

void SYS_CHIP_IMAGE_RECONFIG(uint32_t offset)
{
	SYS_CLK_SWITCH(1); 												//切换到ccb系统时钟
	
	delay_t(1000);

	FP_RECFG_CTRL_CFG->FP_RECFG_CTRL_b.As_source_addr = offset;		//配置recfg的地址 ,bit[23:0] : As_source_addr 
	
	delay_t(100);

	FP_RECFG_CTRL_CFG->FP_RECFG_CTRL_b.Fp_recfg_start = TRUE;		//启动recfg       ,bit[31] : Fp_recfg_start
	
	while(1){};
}

#endif

#ifdef HME_P2

void SYS_CHIP_IMAGE_RECONFIG(uint32_t imgaddr,uint8_t addr_mode)
{ 			
	volatile uint32_t rcfg_val=0;
	
	rcfg_val= imgaddr | addr_mode;
	
	SOC_CLK_MODE_CFG->SOC_CLK_MODE_b.m3soc_clk_switch   = 0;				//切换到ccb系统时钟
	
	delay_t(1000);

	FP_RECFG_CTRL_CFG->FP_RECFG_CTRL = rcfg_val;							//配置recfg的地址和地址模式
	
	while(1){};
}

#endif

void sys_reg_config()
{
	SYS_CFGDONE_FLASH_CTRL(1);	//0:ccb  1：mcu
	SYS_SOC_CLK_MODE_CFG();     //clk cfg
	SYS_MCU_DMA_ENABLE();
	
    return;
}
