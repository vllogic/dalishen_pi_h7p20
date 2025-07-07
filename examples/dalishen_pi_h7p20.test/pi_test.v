// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2023, Alex Taradov <alex@taradov.com>. All rights reserved.

`timescale 1ns / 1ps

module pi_test (
	input usb334x_clk_60M,
	
	
	output etha_25M
);

pll_v1 pll_v1_inst (
  .clkin0(usb334x_clk_60M),
  .locked(),
  .clkout0(etha_25M)
);

endmodule

