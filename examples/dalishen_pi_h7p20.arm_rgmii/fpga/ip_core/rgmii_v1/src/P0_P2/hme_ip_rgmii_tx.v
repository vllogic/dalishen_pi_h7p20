//================================================================================
// Copyright (c) 2024 Hercules-micro, Inc.(Shanghai)  All rights reserved.
//
// Hercules-micro, Inc.(Shanghai) Confidential.
//
// No part of this code may be reproduced, distributed, transmitted,
// transcribed, stored in a retrieval system, or translated into any
// human or computer language, in any form or by any means, electronic,
// mechanical, magnetic, manual, or otherwise, without the express
// written permission of Hercules-micro, Inc.
//
//================================================================================
// Module Description: 
// This is the core of rgmii_tx IP 
//================================================================================
// Revision History :
//     V1.0   2024-09-02  FPGA IP Grp, first created
//================================================================================
// Author :
//     zhangrunmin
//================================================================================
module hme_ip_rgmii_tx(

	input          clk_eth        ,
	input          clk_eth_90d    ,
	input          i_tx_clk_d0    ,
	input          i_tx_clk_d1    ,

	input          gmii_tx_en     ,
	input  [7:0]   gmii_txd       ,
	input          gmii_tx_er     ,

	output         rgmii_txc      ,
	output         rgmii_tx_ctl   ,
	output [3:0]   rgmii_txd
);

/*
	//high 4 bit first
	DDRIO_tx U_DDRIO_TX_CLK(
			.clk_en	 ( 1'b1             ),
			.clk     (clk_eth           ),
			.oen  	 ( 1'd1             ),
			.d       ({i_tx_clk_d1,i_tx_clk_d0}),
			.rstn    (1'd1              ),
			.PAD     (rgmii_txc         )
		); 
*/
	ddr_tx U_DDRIO_OUT_CLK(   
		.pad   (rgmii_txc),
		.clktx (clk_eth),
		.rst   (1'b0),
		.oen   (1'b0),
		.din   ({i_tx_clk_d1,i_tx_clk_d0})
	);


/*
	DDRIO_tx U_DDRIO_TX_EN (
			.clk_en	 ( 1'b1             ),
			.clk     (clk_eth           ),
			.oen  	 ( 1'd1             ),
			.d       ({gmii_tx_en,gmii_tx_en^gmii_tx_er}),
			.rstn    (1'd1              ),
			.PAD     (rgmii_tx_ctl      )
		);    
*/       
	ddr_tx U_DDRIO_OUT_EN (    
		.pad   (rgmii_tx_ctl),
		.clktx (clk_eth),
		.rst   (1'b0),
		.oen   (1'b0),
		.din   ({gmii_tx_en,gmii_tx_en^gmii_tx_er})
	);

	genvar i;
/*
	generate for(i=0;i<4;i=i+1)
	begin :txdata_out
	DDRIO_tx U_DDRIO_TX_DATA(
			.clk_en	 ( 1'b1 ),
			.clk     (clk_eth           ),
			.oen  	 ( 1'd1             ),
			.d       ({gmii_txd[i] ,gmii_txd[i+4]}),
			.rstn    (1'd1              ),
			.PAD     (rgmii_txd[i]      )
		);                           
	end
	endgenerate
*/
generate
	for (i = 0; i < 4; i=i+1) begin
		ddr_tx U_DDRIO_OUT_DATA
			(
			.pad   (rgmii_txd[i]),
			.clktx (clk_eth),
			.rst   (1'b0),
			.oen   (1'b0),
			.din   ({gmii_txd[i],gmii_txd[i+4]})
			);
	end
endgenerate


endmodule

module DDRIO_tx (
    input           clk_en ,
    input           clk    ,
    input           oen    ,
    input   [1:0]   d      ,
    input           rstn   ,

    output          PAD    
);

    SIO SIO_u (
        .f_id  (),
        .clk_en(clk_en  ),
        .fclk  (clk     ),
        .od    (d       ),
        .oen   (oen     ),
        .rstn  (rstn    ),
        .setn  (1'b1    ),
        .PAD   (PAD     )
    );
	
	defparam    SIO_u.KEEP        = 0      ;
    defparam    SIO_u.NDR         = 8      ;
    defparam    SIO_u.NS_LV       = 1      ;
    defparam    SIO_u.PDR         = 20     ;
	
    defparam    SIO_u.OEN_SEL    = 2'b01   ; //输出 
    defparam    SIO_u.OUT_SEL    = 2'b10   ; //11：~od  10：od
    defparam    SIO_u.DDR_EN     = 1'b1    ; //DDR enable
    defparam    SIO_u.FOUT_SEL   = 1'b1    ;
    defparam    SIO_u.DDR_REG_EN = 1'b1    ;

    // od[ne, po]

    //defparam SIO_u.OEN_SEL = 2'b11;	//oen   0:输出关闭，1:输出开启
    //defparam SIO_u.OEN_SEL = 2'b10;	//oen   0:输出开启，1:输出关闭
    //defparam SIO_u.OEN_SEL = 2'b01;	//输出开启
    //defparam SIO_u.OEN_SEL = 2'b00;	//输出关闭
endmodule