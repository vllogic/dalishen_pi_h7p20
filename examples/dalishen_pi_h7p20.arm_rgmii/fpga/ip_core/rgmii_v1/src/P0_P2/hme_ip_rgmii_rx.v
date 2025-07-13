
module hme_ip_rgmii_rx#(
	parameter PDIV = 0
)(

    input               rgmii_rxc    ,
    input               rgmii_rx_ctl ,
    input       [3:0]   rgmii_rxd    ,
	
    output              gmii_rx_clk  ,
    output reg          gmii_rx_dv   ,
    output reg          gmii_rx_er   ,
    output reg  [7:0]   gmii_rxd
	
);

wire       gmii_rx_dv0;
wire       gmii_rx_ctl0;

wire       rgmii_rxc_dbuf;
wire [7:0] rgmii_rxd0;
/*
wire       rgmii_rxc_bufio;
IOBUF bufio_rgmii_rxcl (
    .i             (rgmii_rxc       ),
    .o             (rgmii_rxc_bufio )
);
*/
//assign rgmii_rxc_bufio = rgmii_rxc;

localparam NUM = PDIV?8:12;

generate
	if (PDIV == 1) begin
		PDIV_TOP  #(
			.CFG_PDIV_EN(1'b1),
			.CFG_PDIV_BPS(1'b0),
			.CFG_DIVNUM(3'b000),
			.CFG_DLYNUM(3'b000)
		)
		u_div(
			.CLKIN(rgmii_rxc),
			.CLKOUT(rgmii_rxc_dbuf),
			.CLR(1'd0)
		);
	end 
	else begin
		assign rgmii_rxc_dbuf = rgmii_rxc;
	end
endgenerate

//=============rgmii_rx_ctl=================================
/*
DDRIO_rx  U_DDIO_INEN( 
		.clk_en(1'b1),
		.clk     (rgmii_rxc_bufio ),   
		.oen     (1'd1            ),
		.rstn    (1'd1            ),  
		.PAD     (rgmii_rx_ctl    ),
		.q       ({gmii_rx_ctl0,gmii_rx_dv0})
	);
*/
ddr_rx u_DDRIO_rx( 
	.pad   (rgmii_rx_ctl),
	.clkrx (rgmii_rxc),
	.rst   (1'b0),
	.oen   (1'b1),  
	.dout  ({gmii_rx_ctl0,gmii_rx_dv0}) 
);
//==============rgmii_rxd===============================
genvar k;

/*
generate for (k=0;k<4;k=k+1)
  begin : rgmii_rx
    DDRIO_rx  U_DDIO_INDATA( 
		.clk_en  (1'b1            ),
		.clk     (rgmii_rxc_bufio ),   
		.oen     (1'd1            ),
		.rstn    (1'd1            ),  
		.PAD     (rgmii_rxd[k]    ),
		.q       ({rgmii_rxd0[k+4],rgmii_rxd0[k]})
	); 
  end                                    
endgenerate
*/
generate
	for (k = 0; k < 4; k=k + 1) begin
		ddr_rx U_DDIO_INDATA
		(       
			.pad   (rgmii_rxd[k]),
			.clkrx (rgmii_rxc),
			.rst   (1'b0),
			.oen   (1'b1),  
			.dout  ({rgmii_rxd0[k+4],rgmii_rxd0[k]})
		); 
	end
endgenerate

wire [15:0] gmii_rx_dv_delay;
wire [15:0] gmii_rx_ctl_delay;
wire  [7:0] gmii_rxd_delay[15:0];

assign gmii_rx_dv_delay[0]  = gmii_rx_dv0;
assign gmii_rx_ctl_delay[0] = gmii_rx_ctl0;
assign gmii_rxd_delay[0]    = rgmii_rxd0; 

generate
    genvar i,j;
    for(i=0;i<NUM;i=i+1)begin:rgmii_delay_loop
        DELAY_BUF delay_gmii_rx_dv(
            .in(gmii_rx_dv_delay[i]),
            .out(gmii_rx_dv_delay[i+1])
        );

        DELAY_BUF delay_gmii_rx_ctl(
            .in(gmii_rx_ctl_delay[i]),
            .out(gmii_rx_ctl_delay[i+1])
        );
		for(j=0;j<8;j=j+1)begin:rgmii_rxd_bitloop
			DELAY_BUF delay_gmii_rxd(
				.in(gmii_rxd_delay[i][j]),
				.out(gmii_rxd_delay[i+1][j])
			);
		end
    end
endgenerate

always @(posedge rgmii_rxc_dbuf)
begin
  gmii_rx_dv  <= gmii_rx_dv_delay[NUM]               ;
  gmii_rx_er  <= gmii_rx_ctl_delay[NUM]^gmii_rx_dv_delay[NUM];
  gmii_rxd    <= gmii_rxd_delay[NUM][7:0] ;   
end
assign gmii_rx_clk  = rgmii_rxc_dbuf                       ;

endmodule


module DDRIO_rx (
    input          clk_en ,
    input          clk    ,
    input          oen    ,
    input          rstn   ,
    output  [1:0]  q      ,

    inout          PAD      
);

    SIO SIO_u (
        .f_id  (q       ),
        .clk_en(clk_en  ),
        .fclk  (clk     ),
        .od    (),
        .oen   (oen     ),
        .rstn  (rstn    ),
        .setn  (1'b1    ),
        .PAD   (PAD     )
    );

    parameter   FIN_SEL =  1'b1;
		 		 
	defparam    SIO_u.KEEP        = 0      ;
    defparam    SIO_u.NDR         = 15     ;
    defparam    SIO_u.NS_LV       = 3      ;
    defparam    SIO_u.PDR         = 15     ;
	
    defparam    SIO_u.RX_DIG_EN   = 1      ;
    defparam    SIO_u.OEN_SEL     = 2'b00  ;//输入
    defparam    SIO_u.FOUT_SEL    = 1'b1   ;
    defparam    SIO_u.FIN_SEL     = FIN_SEL;
    defparam    SIO_u.DDR_PREG_EN = FIN_SEL;
    defparam    SIO_u.DDR_NREG_EN = FIN_SEL;

    // f_id[ne, po]

endmodule