
module cme_ip_emb5k_eth_m7_v3(
    clkw,
    cew,
    aw,
    dw,
    clkr,
    cer,
    ar,
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

wire [17:0] qr0;
assign qr = {qr0[15:0]};

M7S_EMB5K #(
        .modea_sel (4'b0000),
        .modeb_sel (4'b0000),
        .porta_wr_mode (2'b01),
        .portb_wr_mode (2'b01),
        .porta_reg_out (1'b0),
        .portb_reg_out (1'b0),
        .reset_value_a (9'b000000000),
        .reset_value_b (9'b000000000),
        .porta_data_width (16),
        .portb_data_width (16),
        .operation_mode ("simple_dual_port"),
        .init_file (""),
        .porta_prog (8'b11110000),
        .portb_prog (8'b00001111)
)
u_emb5k_0 (
        .clka (clkr),
        .clkb (clkw),
        .rstna (1'b1),
        .rstnb (1'b1),
        .cea (cer),
        .ceb (cew),
        .wea (1'b0),
        .web (cew),
        .aa ({ar[7:0], 4'b0}),
        .ab ({aw[7:0], 4'b0}),
        .da (),
        .db ({2'b0, dw[15:0]}),
        .q (qr0)
);

endmodule

// ============================================================
//                  emb Setting
//
// Warning: This part is read by Primace, please don't modify it.
// ============================================================
// Device          : M7A12N0F484C7
// Module          : emb_v1
// IP core         : emb
// IP Version      : 1

// EmbType         : sdp
// EmbResource     : emb5k
// AHBMode         : ahb_unused
// BaseAddr        : a0000000
// DataUsedA       : 16
// DataUsedB       : 16
// AddrUsedA       : 8
// InitFile        : 
// WriteModeA      : write_first
// WriteModeB      : write_first
// OutResetA       : false
// OutResetB       : false
// OutResetValA    : 
// OutResetValB    : 
// RegoutA         : false
// RegoutB         : false
// Emb18kWidth     : false
// Emb18kDepth     : false
// AddrWidthB      : 8
// ModeA           : 256x18
// ModeB           : 256x18
// DataExtA        : 1
// AddrExtA        : 1
// DataExtB        : 1
// AddrExtB        : 1
// BaseModeA       : 256x16
// BaseModeB       : 256x16
// Synthesis Files : 
// Simulation Files: 
