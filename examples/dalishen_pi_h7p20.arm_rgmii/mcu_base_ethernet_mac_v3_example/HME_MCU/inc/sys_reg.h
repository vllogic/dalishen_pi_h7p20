#ifndef __HME_H7_SYS_REG_H__
#define __HME_H7_SYS_REG_H__

#include <stdint.h>
#include "hme_conf.h"
#include "BasicDataType.h"
 

//M3 APB
//#define USER_APB_ENABLE 							1
//AHB
#define P0_USER_AHB_ENABLE	1
#define apb_reg_test  								0x3c

#define USER_APB_REG_BASE  							0x51800000
#define USER_AHB_SLV_BASE								0xa0000000
void user_apb_wr(uint32_t offset, uint32_t din);
uint32_t user_apb_rd(uint32_t offset);


extern void delay_t(int n);
extern void sys_reg_config(void);


/*
	FP_BRG_MODE
	Address : 0x5100_6004

	Bits 	Register Name			CPU Access			Description										Default Value
	
	31:3	Reserved 				RO																		0
	
	2		sync_mode_fp_slv		RW					与FP Slave接口的桥模式：
															0：异步桥模式
															1：同步桥模式，FP接口的时钟是m3总线的整数分频	0
															
	1	    bypass_fp_slv			RW					与FP Slave接口的桥，是否使用bypass模式：
															0：走桥模式（同步桥或异步桥）
															1：不走桥，直连模式								0
															
	0	    bypass_fp_mst			RW					与FP Master接口的桥，是否使用bypass模式：
															0：走异步桥模式
															1：不走桥，直连模式								0
														
Bypass模式指不走桥的直连模式，即全同步。
*/
typedef struct{

  union {
    __IOM uint32_t FP_BRG_MODE;            

    struct {
		__IOM uint32_t bypass_fp_mst      		: 1;   
		__IOM uint32_t bypass_fp_slv      		: 1;    
		__IOM uint32_t sync_mode_fp_slv      	: 1;    		
			  uint32_t            				: 29;
    } FP_BRG_MODE_b;
  } ;

}FP_BRG_MODE_Type;


/*

	SOC_CLK_MODE
	Address : 0x5100_6008

	Bits 	Register Name	   CPU Access	     Description	                       Default Value
	31:11	Reserved 	         RO		                                                   0

	10	    Soc2ccb_clk_en	     RW	             打开ccb 系统时钟，高电平有效	           0

	9		Soc2ccb_osc_en		 RW	             打开ccb osc，高电平有效	               0

	8:6	    hclk_div_fp	         RW	             M3soc系统和FP桥两边的AHB总线分频比
													   Fm3:Ffp = hclk_div_fp + 1	       0

	5:3	    pclk_div	         RW	             M3soc系统ahb总线和apb总线分频比
												 Fahb:Fapb = pclk_div + 1	               0

	2	    m3cpr_m3bus_clk_en	 RW	             M3soc总线时钟开关
														0：时钟关闭；
														1：时钟打开。					   1

	1		m3cpr_m3soc_clk_en	 RW				 M3soc系统时钟开关
														0：时钟关闭；
														1：时钟打开。					   1
														
	0		m3soc_clk_switch	 RW				M3soc系统时钟源切换：
														0：chip crg输入的时钟
														1：ccb系统时钟					   0

*/
typedef struct{

  union {
    __IOM uint32_t SOC_CLK_MODE;            

    struct {
		__IOM uint32_t m3soc_clk_switch      		: 1;   
		__IOM uint32_t m3cpr_m3soc_clk_en      		: 1;    
		__IOM uint32_t m3cpr_m3bus_clk_en      		: 1;    		
		__IOM uint32_t pclk_div           			: 3;
		__IOM uint32_t hclk_div_fp           		: 3;
		__IOM uint32_t Soc2ccb_osc_en      			: 1;    
		__IOM uint32_t Soc2ccb_clk_en      			: 1; 
				uint32_t							: 21;
    } SOC_CLK_MODE_b;
  } ;

}SOC_CLK_MODE_Type;

/*
0：时钟不使能；
1：时钟打开。
*/
typedef struct{
	union {
    __IOM uint32_t SRAM_CLK_EN;            

    struct {
		__IOM uint32_t m3cpr_sram00_clk_en      		: 1;   
		__IOM uint32_t m3cpr_sram01_clk_en      		: 1;     
		__IOM uint32_t m3cpr_sram02_clk_en      		: 1;  		
		__IOM uint32_t m3cpr_sram03_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram04_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram05_clk_en      		: 1;   
		__IOM uint32_t m3cpr_sram06_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram07_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram08_clk_en      		: 1; 
				uint32_t								: 7;
		__IOM uint32_t m3cpr_sram10_clk_en      		: 1;   
		__IOM uint32_t m3cpr_sram11_clk_en      		: 1;     
		__IOM uint32_t m3cpr_sram12_clk_en      		: 1;  		
		__IOM uint32_t m3cpr_sram13_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram14_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram15_clk_en      		: 1;   
		__IOM uint32_t m3cpr_sram16_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram17_clk_en      		: 1;  
		__IOM uint32_t m3cpr_sram18_clk_en      		: 1; 
				uint32_t								: 7;
    } SRAM_CLK_EN_b;
  } ;
	
}SRAM_CLK_EN_Type;

/*
M3core软复位，自动清除
0：写0复位，7个时钟周期后自动清除；
1：不复位。
*/
typedef struct{
	union {
    __IOM uint32_t SOFT_RESET_EN;            

    struct {
		__IOM uint32_t m3cpr_m3soc_sft_rstn      		: 1;    
				uint32_t								: 31;
    } SOFT_RESET_b;
  } ;
	
}SOFT_RESET_EN_Type;


/*
	PLL_PAR
	Address : 0x5100_6014

	Bits 	Register Name				CPU Access					Description							Default Value
	31:4	Reserved 						RO																0
	3:2		gclk_soc_pll_po_en				RW						PLL power down，每bit对应一个PLL
																		0：power down
																		1：power on							0

	1:0		gclk_soc_pll_rst				RW						PLL reset，每bit对应一个PLL
																		0：not reset
																		1：reset							0
*/
typedef struct{
	union {
    __IOM uint32_t  PLL_PAR;            

    struct {
		__IOM uint32_t gclk_soc_pll_rst      			: 2;   
		__IOM uint32_t gclk_soc_pll_po_en      			: 2;    		
				uint32_t								: 28;
    } PLL_PAR_b;
  } ;
	
} PLL_PAR_Type;


/*
	RST_MUX
	Address : 0x5100_6018

	Bits 	  Register Name				CPU Access		    Description						Default Value

	31:7       	Reserved 		  			RO													0

	6:5		   	clken_mux_41_sel			RW				M3soc时钟使能信号mux，4选1
																0:1’b1
																1:1’b0
																2:fp输入的时钟使能
																3:寄存器控制					0

	4:3			rstn_mux_41_sel				RW				M3soc复位信号第二级mux，4选1
																0:1’b0
																1:fp复位输入
																2:第一级复位mux输出
																3:软复位						0

	2:0			rstn_mux_81_sel				RW				M3soc复位信号第一级mux，8选1，
																对应pll的8bit输出				0
*/
typedef struct{
	union {
    __IOM uint32_t  RST_MUX;            

    struct {
		__IOM uint32_t rstn_mux_81_sel      			: 2;   
		__IOM uint32_t rstn_mux_41_sel      			: 2;  
		__IOM uint32_t clken_mux_41_sel      			: 2;    		
				uint32_t								: 26;
    } RST_MUX_b;
  } ;
	
} RST_MUX_Type;


/*
	CLK_MUX
	Address : 0x5100_601C

	Bits 	Register Name			CPU Access	Description							Default Value

	31:3	Reserved 					RO												0

	2:0		M3soc_clk_mux_81_sel		RW		M3soc时钟信号mux，8选1，
												对应pll的8bit输出						0
*/
typedef struct{
	union {
    __IOM uint32_t  CLK_MUX;            

    struct {
		__IOM uint32_t M3soc_clk_mux_81_sel      		: 3;   
				uint32_t      							: 29;
    } CLK_MUX_b;
  } ;
	
} CLK_MUX_Type;

#ifdef HME_H7
/*
	Sram_N(0--8)时钟信号mux，8选1，对应pll的8bit输出
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM0_CLK_MUX;            

    struct {
		__IOM uint32_t Sram00_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram01_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram02_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram03_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram04_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram05_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram06_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram07_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram08_clk_mux_81_sel      		: 3; 
				uint32_t      							: 5;
    } SRAM0_CLK_MUX_b;
  } ;
	
} SRAM0_CLK_MUX_Type;


/*
	Sram_N(10--18)时钟信号mux，8选1，对应pll的8bit输出
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM1_CLK_MUX;            

    struct {
		__IOM uint32_t Sram10_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram11_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram12_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram13_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram14_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram15_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram16_clk_mux_81_sel      		: 3;  
		__IOM uint32_t Sram17_clk_mux_81_sel      		: 3;
		__IOM uint32_t Sram18_clk_mux_81_sel      		: 3; 
				uint32_t      							: 5;
    } SRAM1_CLK_MUX_b;
  } ;
	
} SRAM1_CLK_MUX_Type;


/*
	SRAM0_MODE 
	Address : 0x5100_602C

	Bits 	Register Name		CPU Access		Description							Default Value

	31:27	Reserved 			RO														0

	26:18	Sram0_ram_switch	RW				0组9个SRAM的控制，每bit对应一个sram
													0：soc控制
													1：FP控制							9’h000

	17:9	Sram0_sd			RW				0组9个SRAM的shut down使能信号，
												高电平有效，每bit对应一个sram
													0：normal
													1：shut down	9’h1FF

	8:0		Sram0_slp			RW				0组9个SRAM的sleep使能信号，
												高电平有效，每bit对应一个sram
													0：normal
													1：sleep							9’h1FF
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM0_MODE;            

    struct {
		__IOM uint32_t Sram0_slp      					: 9;  
		__IOM uint32_t Sram0_sd      					: 9;
		__IOM uint32_t Sram0_ram_switch      			: 9;  
				uint32_t      							: 5;
    } SRAM0_MODE_b;
  } ;
	
} SRAM0_MODE_Type;


/*
	SRAM0_MODE 
	Address : 0x5100_6030

	Bits 	Register Name		CPU Access		Description							Default Value

	31:27	Reserved 			RO														0

	26:18	Sram1_ram_switch	RW				1组9个SRAM的控制，每bit对应一个sram
													0：soc控制
													1：FP控制							9’h000

	17:9	Sram1_sd			RW				1组9个SRAM的shut down使能信号，
												高电平有效，每bit对应一个sram
													0：normal
													1：shut down	9’h1FF

	8:0		Sram1_slp			RW				1组9个SRAM的sleep使能信号，
												高电平有效，每bit对应一个sram
													0：normal
													1：sleep							9’h1FF
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM1_MODE;            

    struct {
		__IOM uint32_t Sram1_slp      					: 9;  
		__IOM uint32_t Sram1_sd      					: 9;
		__IOM uint32_t Sram1_ram_switch      			: 9;  
				uint32_t      							: 5;
    } SRAM1_MODE_b;
  } ;
	
} SRAM1_MODE_Type;
#endif


#ifdef HME_P2

/*
	Sram0时钟信号mux，8选1，对应pll的8bit输出
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM0_CLK_MUX;            

    struct {
		__IOM uint32_t Sram0_clk_mux_81_sel      		: 3;  
				uint32_t      							: 29;
    } SRAM0_CLK_MUX_b;
  } ;
	
} SRAM0_CLK_MUX_Type;


/*
	Sram1时钟信号mux，8选1，对应pll的8bit输出
*/
typedef struct{
	union {
    __IOM uint32_t  SRAM1_CLK_MUX;            

    struct {
		__IOM uint32_t Sram1_clk_mux_81_sel      		: 3; 
				uint32_t      							: 29;
    } SRAM1_CLK_MUX_b;
  } ;
	
} SRAM1_CLK_MUX_Type;


/*
	SRAM0_MODE
	Address : 0x5100_602C
	
	Bits 				Register Name			CPU Access			Description							Default Value
	31:19				Reserved 					RO														0
	18					Sram0_ram_switch			RW				SRAM0的控制，每bit对应一个sram
																			0：soc控制
																			1：FP控制						1’h0
	17:10				Reserved 					RO														8’h0
	9					Sram0_sd					RW				SRAM0的shut down使能信号，高电平有效，
																	每bit对应一个sram
																			0：normal
																			1：shut down					1’h1
																			8:1	Reserved 	RO				8’h0
	0					Sram0_slp					RW				SRAM0的sleep使能信号，高电平有效，
																			每bit对应一个sram
																			0：normal
																			1：sleep						1’h1
*/	

typedef struct{
	union {
    __IOM uint32_t  SRAM0_MODE;            

    struct {
		__IOM uint32_t Sram0_slp      					: 1;  
				uint32_t								: 8;
		__IOM uint32_t Sram0_sd      					: 1;
				uint32_t								: 8;
		__IOM uint32_t Sram0_ram_switch      			: 1;  
				uint32_t      							: 13;
    } SRAM0_MODE_b;
  } ;
	
} SRAM0_MODE_Type;



/*
	SRAM1_MODE
	Address : 0x5100_6030
	
	Bits 				Register Name			CPU Access			Description							Default Value
	31:19				Reserved 					RO														0
	18					Sram1_ram_switch			RW				SRAM1的控制，每bit对应一个sram
																			0：soc控制
																			1：FP控制						1’h0
	17:10				Reserved 					RO														8’h0
	9					Sram1_sd					RW				SRAM1的shut down使能信号，高电平有效，
																	每bit对应一个sram
																			0：normal
																			1：shut down					1’h1
																			8:1	Reserved 	RO				8’h0
	0					Sram1_slp					RW				SRAM1的sleep使能信号，高电平有效，
																			每bit对应一个sram
																			0：normal
																			1：sleep						1’h1
*/	
	
	
typedef struct{
	union {
    __IOM uint32_t  SRAM1_MODE;            

    struct {
		__IOM uint32_t Sram1_slp      					: 1;  
				uint32_t								: 8;
		__IOM uint32_t Sram1_sd      					: 1;
				uint32_t								: 8;
		__IOM uint32_t Sram1_ram_switch      			: 1;  
				uint32_t      							: 13;
    } SRAM1_MODE_b;
  } ;
	
} SRAM1_MODE_Type;


#endif

/*
DMA_MODE
Address : 0x5100_6084
*/
typedef struct{
	union {
    __IOM uint32_t  DMA_MODE;            

    struct {
		__IOM uint32_t 	i2c0_tx      					: 1;  
		__IOM uint32_t 	i2c0_rx      					: 1;  
		__IOM uint32_t 	i2c1_tx      					: 1;  
		__IOM uint32_t 	i2c1_rx      					: 1; 
		__IOM uint32_t 	i2c2_tx      					: 1;  
		__IOM uint32_t 	i2c2_rx      					: 1;  
		__IOM uint32_t 	uart0_tx      					: 1;  
		__IOM uint32_t 	uart0_rx      					: 1;
		__IOM uint32_t 	uart1_tx      					: 1;  
		__IOM uint32_t 	uart1_rx      					: 1; 
		__IOM uint32_t 	spi0_tx      					: 1;  
		__IOM uint32_t 	spi0_rx      					: 1;  
		__IOM uint32_t 	spi1_tx      					: 1;  
		__IOM uint32_t 	spi1_rx      					: 1;  
		__IOM uint32_t 	spi2_tx      					: 1;  
		__IOM uint32_t 	spi2_rx      					: 1; 
				uint32_t								: 16;
		
    } DMA_MODE_b;
  } ;
	
} DMA_MODE_Type;


/*
	SPI_MODE
	Address : 0x5100_608C

	Bits 	Register Name	CPU Access					Description					Default Value
	31:1	Reserved 			RO															0
	0		Qspi_mst			RW						QSPI即外部spi flash，
														在configure done后由谁控制：
																0：CCB
																1：MCU						0
*/
typedef struct{
	union {
    __IOM uint32_t  SPI_MODE;            

    struct {
		__IOM uint32_t Qspi_mst      					: 1;  
				uint32_t      							: 31;
    } SPI_MODE_b;
  } ;
} SPI_MODE_Type;



/*
	FP_IF_EN0
	Address : 0x5100_6090
	Bits 	Register Name			CPU Access			Description						Default Value
	31:19		Reserved 				RO													0
	18			Fp_sram_ctrl2_en		RW				Sram_ctrl2是否连接FP上的SRAM
															0：不使用，输出信号保持为高
															1：使用，为正常信号	0
	17:0	Fp_sram_en					RW				每1bit对应一块SRAM，共18块SRAM
															0：不使用，保持为高
															1：使用，为正常信号				0
*/
typedef struct{
	union {
    __IOM uint32_t  FP_IF_EN0;            

    struct {
		__IOM uint32_t Fp_sram_en      					: 18; 
				uint32_t      							: 23;
    } FP_IF_EN0_b;
  } ;
} FP_IF_EN0_Type;



typedef struct{
	union {
    __IOM uint32_t  FP_IF_EN1;            

    struct {
		__IOM uint32_t 	Fp_ahb_mst_en      					: 1;  
		__IOM uint32_t 	Fp_ahb_slv_en      					: 1;  
		__IOM uint32_t 	Fp_gpio0_en      					: 1;  
		__IOM uint32_t 	Fp_gpio1_en      					: 1; 
		__IOM uint32_t 	Fp_gpio2_en      					: 1;  
		__IOM uint32_t 	Fp_ic0_en      						: 1;  
		__IOM uint32_t 	Fp_ic1_en      						: 1;  
		__IOM uint32_t 	Fp_ic2_en      						: 1;
		__IOM uint32_t 	Fp_uart0_en      					: 1;  
		__IOM uint32_t 	Fp_uart1_en      					: 1; 
		__IOM uint32_t 	Fp_uart2_en      					: 1;  
		__IOM uint32_t 	Fp_spi0_en      					: 1;  
		__IOM uint32_t 	Fp_spi1_en      					: 1;  
		__IOM uint32_t 	Fp_spi2_en      					: 1;  
		__IOM uint32_t 	Fp_spi3_en      					: 1;  
		__IOM uint32_t 	Fp_wdt_en      						: 1; 
		__IOM uint32_t 	Fp_timer0_en      					: 1;  
		__IOM uint32_t 	Fp_timer1_en      					: 1;  
		__IOM uint32_t 	fp_dma_en      						: 1;  
		__IOM uint32_t 	fp_apb_en      						: 1;  
		__IOM uint32_t 	hclk_fp_gate_en       				: 1; 
				uint32_t									: 11;
		
    } FP_IF_EN1_b;
  } ;
	
} FP_IF_EN1_Type;

#ifdef HME_H7
/*
	FP_RECFG_CTRL
	Address : 0x 4170_0160

	Bits 	Register Name	CPU Access		Description										Default Value
	31		Fp_recfg_start		RW			FPGA start reconfig, active high, self clear.		0
	30:24	Reserved 			RO																0
	23:0	As_source_addr		RW			FPGA reconfig start address							0
*/
typedef struct{
	union {
    __IOM uint32_t  FP_RECFG_CTRL;            

    struct {
		__IOM uint32_t As_source_addr      					: 24; 
				uint32_t      								: 7;
		__IOM uint32_t Fp_recfg_start						: 1;
    } FP_RECFG_CTRL_b;
  } ;
} FP_RECFG_CTRL_Type;
#endif

#ifdef HME_P2
/*
该寄存器为FPGA启动重新配置时，码流起始地址，和地址模式控制寄存器。
当该寄存器被配置的时候，系统会自动启动重新配置，并且从该寄存器所指定的地址开始读取码流。配置本寄存器会启动CCB系统软复位。

FP_RECFG_CTRL
Address : 0x 4170_0160

Bits 			Register Name			CPU Access			Description							Default Value

31:2			Fp_recfg_addr[31:2]			RW			Fp重新初始化地址的高30bit，					0
														flash每次读取32bit数据，
														因此该地址低2bit始终为0。	
1				Reserved					RO		

0				Recfg_addr_mode				RW			1：32bit地址模式
														0：24bit地址模式
														只能通过上电复位以及按键复位清零			0
*/

typedef struct{
	union {
    __IOM uint32_t  FP_RECFG_CTRL;            

    struct {
		__IOM uint32_t Recfg_addr_mode      				: 1; 
				uint32_t      								: 1;
		__IOM uint32_t Fp_recfg_addr_31_2					: 30;
    } FP_RECFG_CTRL_b;
  } ;
} FP_RECFG_CTRL_Type;



#endif



#define FP_BRG_MODE_ADDR									0x51006004UL
#define SOC_CLK_MODE_ADDR									0x51006008UL
#define SRAM_CLK_EN_ADDR									0x5100600CUL
#define SOFT_RESET_EN_ADDR									0x51006010UL
#define PLL_PAR_ADDR										0x51006014UL
#define RST_MUX_ADDR										0x51006018UL
#define CLK_MUX_ADDR										0x5100601CUL
#define SRAM0_CLK_MUX_ADDR									0x51006020UL
#define SRAM1_CLK_MUX_ADDR									0x51006024UL
#define SRAM0_MODE_ADDR										0x5100602CUL
#define SRAM1_MODE_ADDR										0x51006030UL
#define SPI_MODE_ADDR                						0x5100608CUL
#define FP_IF_EN0_ADDR										0x51006090UL
#define FP_IF_EN1_ADDR										0x51006094UL
#define DMA_MODE_ADDR										0x51006084UL
#define FP_RECFG_CTRL_ADDR  								0x45700160UL

#define ENABLE_ALLDMA                  						0xFFFFFFFF;
#define DISABLE_ALLDMA                 						0x0;
#define ENABLE_ALLINTERFACE                 				0xFFFFFFFF;


#define FP_RECFG_CTRL_CFG	                   	((FP_RECFG_CTRL_Type*)		FP_RECFG_CTRL_ADDR)
#define FP_IF_EN1_CFG	                       	((FP_IF_EN1_Type*)			FP_IF_EN1_ADDR)
#define FP_IF_EN0_CFG	                      	((FP_IF_EN0_Type*)			FP_IF_EN0_ADDR)
#define SPI_MODE_CFG	                       	((SPI_MODE_Type*)			SPI_MODE_ADDR)
#define DMA_MODE_CFG	                       	((DMA_MODE_Type*)			DMA_MODE_ADDR)
#define SRAM1_MODE_CFG	       				   	((SRAM1_MODE_Type*)			SRAM1_MODE_ADDR)
#define SRAM0_MODE_CFG	                   	   	((SRAM0_MODE_Type*)			SRAM0_MODE_ADDR) 
#define SRAM1_CLK_MUX_CFG	                   	((SRAM1_CLK_MUX_Type*)		SRAM1_CLK_MUX_ADDR) 
#define SRAM0_CLK_MUX_CFG	                   	((SRAM0_CLK_MUX_Type*)		SRAM0_CLK_MUX_ADDR) 
#define RST_MUX_CFG	                   		   	((RST_MUX_Type*)			RST_MUX_ADDR) 
#define CLK_MUX_CFG	                   		   	((CLK_MUX_Type*)			CLK_MUX_ADDR) 
#define SOFT_RESET_EN_CFG                       ((SOFT_RESET_EN_Type*)		SOFT_RESET_EN_ADDR)
#define SOC_CLK_MODE_CFG                       	((SOC_CLK_MODE_Type*)		SOC_CLK_MODE_ADDR)
#define FP_BRG_MODE_CFG	                   	   	((FP_BRG_MODE_Type*)		FP_BRG_MODE_ADDR)


void SYS_FP_BRG_MODE_CFG(void);					//设置与FP Slave接口的桥模式
void SYS_SOC_CLK_MODE_CFG(void);				//MCU相关时钟配置
void SYS_MCU_SOFTRESET(bool val);				//MCU软复位   0：写0复位，7个时钟周期后自动清除；1：不复位。
void SYS_CLK_SWITCH(BOOL val);					//时钟切换，crg时钟或ccb时钟
void SYS_SET_HCLK_DIV(uint8_t div);   			//设置hclk的分频系数
void SYS_SET_PCLK_DIV(uint8_t div);				//设置pclk的分频系数
void SYS_RST_MUX_CFG(void);
void SYS_CLK_MUX_CFG(void);
void SYS_SRAM0_CLK_MUX_CFG(void);
void SYS_SRAM1_CLK_MUX_CFG(void);
void SYS_SRAM0_MODE_CFG(void);
void SYS_SRAM1_MODE_MUX_CFG(void);
void SYS_SRAM0_SWITCH(bool val);				//sram0-8控制权; 0 : soc控制  1：FPGA控制
void SYS_SRAM1_SWITCH(bool val);				//sram9-17控制权; 0 : soc控制  1：FPGA控制
void SYS_MCU_DMA_ENABLE(void);					//MCU启用dma功能
void SYS_CFGDONE_FLASH_CTRL(uint8_t val);		//芯片configdone后flash由谁控制
void SYS_IF_EN0_ForSRAM(void);					//FPGA访问SRAM使能 
void SYS_IF_EN1_ForPRIPHERAL(void);				//FPGA访问外设和ahb、apb接口使能

#ifdef HME_H7
void SYS_CHIP_IMAGE_RECONFIG(uint32_t offset);	//芯片reconfig，offset为镜像在flash中的起始地址
#endif

#ifdef HME_P2

enum RCFG_ADDR_MODE{
	RCFG_24BIT_ADDR=0,
	RCFG_32BIT_ADDR=1
};

void SYS_CHIP_IMAGE_RECONFIG(uint32_t imgaddr,uint8_t addr_mode);
#endif


#define IS_PCLK_DIV_RANGE(DIV) (DIV<=7)
#define IS_SPI_MODE_RANGE(VAL) ((VAL==1)||(VAL==0))
#define IS_CLK_SWITCH_RANGE(VAL) ((VAL==1)||(VAL==0))

#endif
