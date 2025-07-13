
module cme_ip_emb5k_eth_m5_v3(
	clkw,
	aw,
	cew,
	dw,
	
	clkr,
	ar,
	cer,
	qr
  );
	
	input clkw;      
	input cew;
	input [7:0] aw; 
	input [15:0] dw; 
       
	input clkr;      
	input cer;
	input [7:0] ar;
	output [15:0] qr; 

	
	wire emb_clka;
	wire emb_cea;
	wire emb_wea;
	wire [11:0] emb_aa;

	wire emb_clkb;
	wire emb_ceb;
	wire emb_web;
	wire [11:0] emb_ab;
	wire [17:0] emb_db;
	wire [17:0] emb_q;

												
	assign emb_clka = clkr;
	assign emb_cea = cer;
	assign emb_wea = 1'b0;	
	assign emb_aa = {ar,4'b0};
	
	
	assign emb_clkb = clkw;
	assign emb_ceb = cew;
	assign emb_web = cew;	
	assign emb_ab = {aw,4'b0};
	assign emb_db = {2'b0,dw};
	
	assign qr = emb_q[15:0];

	EMB5K emb5k_u0(
         	.clka		(emb_clka		),  
         	.cea		(emb_cea		),  
         	.wea		(emb_wea		),  
         	.aa			(emb_aa			),
         	.da			(),
         	.clkb		(emb_clkb		),  
         	.ceb		(emb_ceb		),   
         	.web		(emb_web		),  
         	.ab			(emb_ab			),
         	.db			(emb_db			),
         	.q			(emb_q			),
         	.wq_in	(),
         	.wq_out ()                 
            );

	defparam emb5k_u0.operation_mode	 =  "simple_dual_port";
	defparam emb5k_u0.porta_data_width	=  16;
	defparam emb5k_u0.portb_data_width	=  16;
	defparam emb5k_u0.modea_sel	=  "256x18";
	defparam emb5k_u0.modeb_sel	=  "256x18";
	defparam emb5k_u0.porta_wr_through	 =  "false";
	defparam emb5k_u0.portb_wr_through	 =  "false";
	defparam emb5k_u0.init_file = "";
	//parameter user can not set
	defparam emb5k_u0.porta_prog = 8'b11110000;
	defparam emb5k_u0.portb_prog = 8'b00001111;
	
//synthesis translate_on

endmodule
// ==================================================================
//                           emb Setting
//
// Warning: This part is read by Primace, please don't modify it.
// ==================================================================
// Device          : M5C06N3F256C7
// Module          : MyEmb
// IP core         : emb
// IP Version      : 1 

// EmbType         : sdp
// isRom           : false
// DataUsedA       : 16
// AddrUsedA       : 8
// WriteThroughA   : false

// DataUsedB       : 16
// AddrUsedB       : 8
// WriteThroughB   : false

// IsExtendMode	   : 0
// InitFile        : 
// DependentPort   : 1

// BaseMode        : 256x16
// AddrExt         : 1
// DataExt         : 1


