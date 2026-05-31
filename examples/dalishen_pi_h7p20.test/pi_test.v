// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023, Alex Taradov <alex@taradov.com>. All rights reserved.

`timescale 1ns / 1ps

module pi_test (
	input usb334x_clk_60M,
	
	output [1:0] out_25m,
	output [1:0] out_50m,
	output [1:0] out_100m,
	output [1:0] out_200m,
	output [1:0] out_300m,
	
	output etha_25M
);

pll_v1 pll_v1_inst (
  .clkin0(usb334x_clk_60M),
  .locked(),
  .clkout0(pll_c0),
  .clkout1(pll_c1),
  .clkout2(pll_c2),
  .clkout3(pll_c3),
  .clkout4(pll_c4)
);

assign etha_25M = pll_c0;

assign out_25m[0] = pll_c0;
assign out_25m[1] = pll_c0;

assign out_50m[0] = pll_c1;
assign out_50m[1] = pll_c1;

assign out_100m[0] = pll_c2;
assign out_100m[1] = pll_c2;

assign out_200m[0] = pll_c3;
assign out_200m[1] = pll_c3;

assign out_300m[0] = pll_c4;
assign out_300m[1] = pll_c4;

endmodule

