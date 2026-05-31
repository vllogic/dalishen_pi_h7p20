//================================================================================
// Copyright (c) 2015 Capital-micro, Inc.(Beijing)  All rights reserved.
//
// Capital-micro, Inc.(Beijing) Confidential.
//
// No part of this code may be reproduced, distributed, transmitted,
// transcribed, stored in a retrieval system, or translated into any
// human or computer language, in any form or by any means, electronic,
// mechanical, magnetic, manual, or otherwise, without the express
// written permission of Capital-micro, Inc.
//
//================================================================================
// Module Description: 
// This is the core of debugware IP 
//================================================================================
// Revision History :
//     V2.0   2015-05-28  FPGA IP Grp, first created
//     V2.1   2015-09-08  FPGA IP Grp, support C1 device
//	   V2.2   2025-09-01  FPGA IP Grp, support Muti-windows function
//						  optimized trigger module, support up to 1024 data width
//================================================================================

module la_core(
    ref_clk,
    tck,
    tdi,
    update,
    shift,

    status_sel,
    ctrl_sel,
    mem_sel,
    offset_sel,
    cfg_sel,
    sel,
    reset,
    reset_raddr,
    update_clk,
    trig_out,
    data_in,
    tdo,
	debug_sig
);
parameter CAP_MODE = 1;
parameter DATA_WIDTH   = 90;   
parameter INPUT_DFF_LEVEL   = 0;  //Valid value is 0-6
parameter SAMPLE_DEPTH = 2048;  
parameter ADDR_WIDTH   = 11;
//parameter DEVICE_NAME  = 2'b00; 
parameter DEVICE_NAME  = 3'b000;  //M5-3'b000, M7-3'b001, HR3-3'b010, HR2-3'b011, C1-3'b100


input ref_clk;
input tck;
input tdi;
input update;
input shift;
input status_sel;
input ctrl_sel;
input mem_sel;
input offset_sel;
input cfg_sel;
input sel;
input reset;
input reset_raddr;
input update_clk;
//input trig_in;
input [DATA_WIDTH-1:0] data_in;
output trig_out;
output tdo;

output [127:0]debug_sig;

endmodule

module la_manager (
                   tck1, tdi1, tdo1, sel1, 
						 tck2, tdi2, tdo2, sel2, 
                   update, update_clk, shift, reset, 
						 status, ctrl, mem, offset,cfg,
                   la_sel, la_reset, la_tck, la_update, la_shift, la_tdi, la_tdo
						 );//add update_clk 0521 
parameter NUM_OF_LA = 1;
input tck1, tdi1, sel1, tck2, tdi2, sel2, update, update_clk, shift, reset; 
input [NUM_OF_LA-1:0] la_tdo;
output tdo1, tdo2, status, ctrl, mem, offset,cfg, la_reset, la_tck, la_update, la_shift, la_tdi;
output [NUM_OF_LA-1:0] la_sel;

endmodule

module tap(
    tck1,
    tdi1,
    tdo1,
    sel1,
    tck2,
    tdi2,
    tdo2,
    sel2,
    update,
    shift,
    reset
);

parameter DEVICE_NAME = 3'b000; //00 - M5,01 - M7,10 - HR3,11 - HR2 ,100 - C1

output tck1;
output tdi1;
input tdo1;
output sel1;
output tck2;
output tdi2;
input tdo2;
output sel2;
output update;
output shift;
output reset;



endmodule
