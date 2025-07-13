// ============================================================
//
// Company:
// Engineer:
//
// Create Date: 08/26/2024 18:27:40   
// Design Name:
// Module Name: ddr_tx
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
// ============================================================

`define RGMII_3V3_EN
//`define RGMII_2V5_EN

module ddr_tx(
	pad,
	clkrx,
	clktx,
	rst,
	oen,
	din,
	dout
);

inout pad;
input clkrx, clktx, oen, rst;
input [1:0] din;
output [1:0] dout;

wire int_rxd;

P0_GPIO_HR #(


`ifdef RGMII_3V3_EN

             .CFG_25_EN    (1'b0),//bank shared 
             .CFG_MSC      (1'b0),  //bank shared
			 .CFG_RX_EN12  (1'b0),
             .CFG_RX_EN15  (1'b0),
             .CFG_RX_EN33  (1'b1),
			 
`elsif RGMII_2V5_EN

             .CFG_25_EN    (1'b1),//bank shared 
             .CFG_MSC      (1'b0),  //bank shared
			 .CFG_RX_EN12  (1'b0),
             .CFG_RX_EN15  (1'b0),
             .CFG_RX_EN33  (1'b0),
`else

             .CFG_25_EN    (1'b0),//bank shared  //1.8V
             .CFG_MSC      (1'b1),  //bank shared
			 .CFG_RX_EN12  (1'b0),
             .CFG_RX_EN15  (1'b0),
             .CFG_RX_EN33  (1'b0),
			 
`endif
			

             .CFG_RX_DIG_EN(1'b0), //in

             .CFG_RX_ST_EN (1'b0),

             .CFG_NS_LV    (1'b1),			 
			 // .CFG_NDR (4'b1111),
             // .CFG_PDR (5'b11111), //16mA

            // .CFG_NDR (4'b1101),
            // .CFG_PDR (5'b11111), //14mA
			 
			 // .CFG_NDR (4'b1100),
             // .CFG_PDR (5'b11100), //12mA
			 
			  .CFG_NDR (4'b1000),
             .CFG_PDR (5'b10100), //8mA
			 
			  // .CFG_NDR (4'b0110),
              // .CFG_PDR (5'b01110), //6mA
			 
			 // .CFG_NDR (4'b0100),
             // .CFG_PDR (5'b01010), //4mA
			 
             .CFG_KEEP(2'b00),
             .CFG_RSE (4'b0000) 
      ) i_pad (
		.RXD(int_rxd), 
		.PAD(pad), 
		.TED(int_ted),
		.TXD(int_txd)
      );

P0_IOC_GPIO #(
        .CFG_OEN_SEL(4'b1000),//0000:1, 0001:0, 0010: oen4, 0100:oen2, 1000:oen3
        .CFG_CK_PAD_EN(1'b0),
        .CFG_DDR_IN_NREG(1'b0),
        .CFG_DDR_IN_NREG_DFF(1'b1),//in
        .CFG_DDR_IN_PREG(1'b0),
        .CFG_DDR_IN_PREG_DFF(1'b1),//in
        .CFG_DDR_OUT(1'b1),
        .CFG_DDR_OUT_REG(1'b1),
        .CFG_FASTIN_0(1'b0),
        .CFG_FASTIN_1(1'b0),
        .CFG_FCLK_INV(1'b1),
        .CFG_FOUT_SEL(1'b0),
        .CFG_OEN_DDR_OUT_REG(1'b0),
        .CFG_OEN_INV(1'b0), //
        .CFG_OFDBK(1'b0),
        .CFG_OUT_INV(1'b0),

//**** from IOC_LBUF_GPIO.ckgate_block_GPIO
        .CFG_FCLK0_I_EN(1'b1),
        .CFG_FCLK0_O_EN(1'b1),
        .CFG_FCLK1_I_EN(1'b1),
        .CFG_FCLK1_O_EN(1'b1),
        .CFG_FCLK_OEN_EN(1'b1),
        .CFG_FCLK_SR_I_EN(1'b1),
        .CFG_FCLK_SR_O_EN(1'b1),

//**** from IOC_LBUF_GPIO.CLK_MUX_GPIO
        .CFG_SET_INV_I(1'b1),
        .CFG_SET_EN_I(2'b01), //[1] not use
        .CFG_SET_SYN_I(1'b0),
        .CFG_SET_INV_O(1'b1),
        .CFG_SET_EN_O(2'b11), //[1] to control oe
        .CFG_SET_SYN_O(1'b0),

        .CFG_RST_INV_I(1'b0),
        .CFG_RST_EN_I(2'b01), //[1] not use
        .CFG_RST_SYN_I(1'b1),
        .CFG_RST_INV_O(1'b0),
        .CFG_RST_EN_O(2'b11), //[1] to control oe
        .CFG_RST_SYN_O(1'b1),

        .CFG_EN0_I(1'b0),
        .CFG_EN1_I(1'b0),
        .CFG_CKEN_INV_I(1'b0),
        .CFG_EN0_O(1'b0),
        .CFG_EN1_O(1'b0),
        .CFG_CKEN_INV_O(1'b0)
      ) i_ioc (
	    .rxd_in(int_rxd),
	    .txd_out(int_txd),
	    .oen_out(int_ted),

	    .rxd_dr(),//clk

	    .fclk_il(clkrx),
	    .fclk_ol(clktx),
	    .cken_il(),
	    .cken_ol(),
	    .rst_il(rst),
	    .rst_ol(rst),
	    .setn_il(1'b1),
	    .setn_ol(1'b1),//high active
	    .oen(oen),
	    .d(din), // bit0: falling , bit1 : rising
	    .q(dout)
	  );
	  

	  
endmodule



