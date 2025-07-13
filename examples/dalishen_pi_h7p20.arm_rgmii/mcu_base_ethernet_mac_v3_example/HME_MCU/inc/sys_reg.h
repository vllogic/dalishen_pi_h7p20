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
	
	2		sync_mode_fp_slv		RW					��FP Slave�ӿڵ���ģʽ��
															0���첽��ģʽ
															1��ͬ����ģʽ��FP�ӿڵ�ʱ����m3���ߵ�������Ƶ	0
															
	1	    bypass_fp_slv			RW					��FP Slave�ӿڵ��ţ��Ƿ�ʹ��bypassģʽ��
															0������ģʽ��ͬ���Ż��첽�ţ�
															1�������ţ�ֱ��ģʽ								0
															
	0	    bypass_fp_mst			RW					��FP Master�ӿڵ��ţ��Ƿ�ʹ��bypassģʽ��
															0�����첽��ģʽ
															1�������ţ�ֱ��ģʽ								0
														
Bypassģʽָ�����ŵ�ֱ��ģʽ����ȫͬ����
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

	10	    Soc2ccb_clk_en	     RW	             ��ccb ϵͳʱ�ӣ��ߵ�ƽ��Ч	           0

	9		Soc2ccb_osc_en		 RW	             ��ccb osc���ߵ�ƽ��Ч	               0

	8:6	    hclk_div_fp	         RW	             M3socϵͳ��FP�����ߵ�AHB���߷�Ƶ��
													   Fm3:Ffp = hclk_div_fp + 1	       0

	5:3	    pclk_div	         RW	             M3socϵͳahb���ߺ�apb���߷�Ƶ��
												 Fahb:Fapb = pclk_div + 1	               0

	2	    m3cpr_m3bus_clk_en	 RW	             M3soc����ʱ�ӿ���
														0��ʱ�ӹرգ�
														1��ʱ�Ӵ򿪡�					   1

	1		m3cpr_m3soc_clk_en	 RW				 M3socϵͳʱ�ӿ���
														0��ʱ�ӹرգ�
														1��ʱ�Ӵ򿪡�					   1
														
	0		m3soc_clk_switch	 RW				M3socϵͳʱ��Դ�л���
														0��chip crg�����ʱ��
														1��ccbϵͳʱ��					   0

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
0��ʱ�Ӳ�ʹ�ܣ�
1��ʱ�Ӵ򿪡�
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
M3core��λ���Զ����
0��д0��λ��7��ʱ�����ں��Զ������
1������λ��
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
	3:2		gclk_soc_pll_po_en				RW						PLL power down��ÿbit��Ӧһ��PLL
																		0��power down
																		1��power on							0

	1:0		gclk_soc_pll_rst				RW						PLL reset��ÿbit��Ӧһ��PLL
																		0��not reset
																		1��reset							0
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

	6:5		   	clken_mux_41_sel			RW				M3socʱ��ʹ���ź�mux��4ѡ1
																0:1��b1
																1:1��b0
																2:fp�����ʱ��ʹ��
																3:�Ĵ�������					0

	4:3			rstn_mux_41_sel				RW				M3soc��λ�źŵڶ���mux��4ѡ1
																0:1��b0
																1:fp��λ����
																2:��һ����λmux���
																3:��λ						0

	2:0			rstn_mux_81_sel				RW				M3soc��λ�źŵ�һ��mux��8ѡ1��
																��Ӧpll��8bit���				0
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

	2:0		M3soc_clk_mux_81_sel		RW		M3socʱ���ź�mux��8ѡ1��
												��Ӧpll��8bit���						0
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
	Sram_N(0--8)ʱ���ź�mux��8ѡ1����Ӧpll��8bit���
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
	Sram_N(10--18)ʱ���ź�mux��8ѡ1����Ӧpll��8bit���
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

	26:18	Sram0_ram_switch	RW				0��9��SRAM�Ŀ��ƣ�ÿbit��Ӧһ��sram
													0��soc����
													1��FP����							9��h000

	17:9	Sram0_sd			RW				0��9��SRAM��shut downʹ���źţ�
												�ߵ�ƽ��Ч��ÿbit��Ӧһ��sram
													0��normal
													1��shut down	9��h1FF

	8:0		Sram0_slp			RW				0��9��SRAM��sleepʹ���źţ�
												�ߵ�ƽ��Ч��ÿbit��Ӧһ��sram
													0��normal
													1��sleep							9��h1FF
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

	26:18	Sram1_ram_switch	RW				1��9��SRAM�Ŀ��ƣ�ÿbit��Ӧһ��sram
													0��soc����
													1��FP����							9��h000

	17:9	Sram1_sd			RW				1��9��SRAM��shut downʹ���źţ�
												�ߵ�ƽ��Ч��ÿbit��Ӧһ��sram
													0��normal
													1��shut down	9��h1FF

	8:0		Sram1_slp			RW				1��9��SRAM��sleepʹ���źţ�
												�ߵ�ƽ��Ч��ÿbit��Ӧһ��sram
													0��normal
													1��sleep							9��h1FF
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
	Sram0ʱ���ź�mux��8ѡ1����Ӧpll��8bit���
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
	Sram1ʱ���ź�mux��8ѡ1����Ӧpll��8bit���
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
	18					Sram0_ram_switch			RW				SRAM0�Ŀ��ƣ�ÿbit��Ӧһ��sram
																			0��soc����
																			1��FP����						1��h0
	17:10				Reserved 					RO														8��h0
	9					Sram0_sd					RW				SRAM0��shut downʹ���źţ��ߵ�ƽ��Ч��
																	ÿbit��Ӧһ��sram
																			0��normal
																			1��shut down					1��h1
																			8:1	Reserved 	RO				8��h0
	0					Sram0_slp					RW				SRAM0��sleepʹ���źţ��ߵ�ƽ��Ч��
																			ÿbit��Ӧһ��sram
																			0��normal
																			1��sleep						1��h1
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
	18					Sram1_ram_switch			RW				SRAM1�Ŀ��ƣ�ÿbit��Ӧһ��sram
																			0��soc����
																			1��FP����						1��h0
	17:10				Reserved 					RO														8��h0
	9					Sram1_sd					RW				SRAM1��shut downʹ���źţ��ߵ�ƽ��Ч��
																	ÿbit��Ӧһ��sram
																			0��normal
																			1��shut down					1��h1
																			8:1	Reserved 	RO				8��h0
	0					Sram1_slp					RW				SRAM1��sleepʹ���źţ��ߵ�ƽ��Ч��
																			ÿbit��Ӧһ��sram
																			0��normal
																			1��sleep						1��h1
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
	0		Qspi_mst			RW						QSPI���ⲿspi flash��
														��configure done����˭���ƣ�
																0��CCB
																1��MCU						0
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
	18			Fp_sram_ctrl2_en		RW				Sram_ctrl2�Ƿ�����FP�ϵ�SRAM
															0����ʹ�ã�����źű���Ϊ��
															1��ʹ�ã�Ϊ�����ź�	0
	17:0	Fp_sram_en					RW				ÿ1bit��Ӧһ��SRAM����18��SRAM
															0����ʹ�ã�����Ϊ��
															1��ʹ�ã�Ϊ�����ź�				0
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
�üĴ���ΪFPGA������������ʱ��������ʼ��ַ���͵�ַģʽ���ƼĴ�����
���üĴ��������õ�ʱ��ϵͳ���Զ������������ã����ҴӸüĴ�����ָ���ĵ�ַ��ʼ��ȡ���������ñ��Ĵ���������CCBϵͳ��λ��

FP_RECFG_CTRL
Address : 0x 4170_0160

Bits 			Register Name			CPU Access			Description							Default Value

31:2			Fp_recfg_addr[31:2]			RW			Fp���³�ʼ����ַ�ĸ�30bit��					0
														flashÿ�ζ�ȡ32bit���ݣ�
														��˸õ�ַ��2bitʼ��Ϊ0��	
1				Reserved					RO		

0				Recfg_addr_mode				RW			1��32bit��ַģʽ
														0��24bit��ַģʽ
														ֻ��ͨ���ϵ縴λ�Լ�������λ����			0
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


void SYS_FP_BRG_MODE_CFG(void);					//������FP Slave�ӿڵ���ģʽ
void SYS_SOC_CLK_MODE_CFG(void);				//MCU���ʱ������
void SYS_MCU_SOFTRESET(bool val);				//MCU��λ   0��д0��λ��7��ʱ�����ں��Զ������1������λ��
void SYS_CLK_SWITCH(BOOL val);					//ʱ���л���crgʱ�ӻ�ccbʱ��
void SYS_SET_HCLK_DIV(uint8_t div);   			//����hclk�ķ�Ƶϵ��
void SYS_SET_PCLK_DIV(uint8_t div);				//����pclk�ķ�Ƶϵ��
void SYS_RST_MUX_CFG(void);
void SYS_CLK_MUX_CFG(void);
void SYS_SRAM0_CLK_MUX_CFG(void);
void SYS_SRAM1_CLK_MUX_CFG(void);
void SYS_SRAM0_MODE_CFG(void);
void SYS_SRAM1_MODE_MUX_CFG(void);
void SYS_SRAM0_SWITCH(bool val);				//sram0-8����Ȩ; 0 : soc����  1��FPGA����
void SYS_SRAM1_SWITCH(bool val);				//sram9-17����Ȩ; 0 : soc����  1��FPGA����
void SYS_MCU_DMA_ENABLE(void);					//MCU����dma����
void SYS_CFGDONE_FLASH_CTRL(uint8_t val);		//оƬconfigdone��flash��˭����
void SYS_IF_EN0_ForSRAM(void);					//FPGA����SRAMʹ�� 
void SYS_IF_EN1_ForPRIPHERAL(void);				//FPGA���������ahb��apb�ӿ�ʹ��

#ifdef HME_H7
void SYS_CHIP_IMAGE_RECONFIG(uint32_t offset);	//оƬreconfig��offsetΪ������flash�е���ʼ��ַ
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
