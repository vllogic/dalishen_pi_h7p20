//================================================================================
// Copyright (c) 2013 Capital-micro, Inc.(Beijing)  All rights reserved.
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
// Module Description: Top Module of Ethernet MAC IP core
//================================================================================
// Revision History :
//     V1.0   2013-03-18  FPGA IP Grp, first created
//     V2.0   2014-04-25  FPGA IP Grp, support EMIF/AHB bus, modify TX/RX
//     memory management 
//     V3.0   2014-12-18  FPGA IP Grp, add eth_mac_core_f_1k.v to support
//     1000M mode
//================================================================================
module hme_ip_eth_mac_top_ahb_f_1k_v3 (
    clk_tx_i,
    clk_rx_i,
    clk_app_i,
    rst_clk_tx_n,
    rst_clk_rx_n,
    rst_clk_app_n,
    
	gmii_mdc_o,
    gmii_mdi_i,
    gmii_mdo_o,
    gmii_mdo_o_e,
    phy_txen_o,
    phy_txer_o,
    phy_txd_o,
    phy_crs_i,
    phy_col_i,
    phy_rxdv_i,
    phy_rxer_i,
    phy_rxd_i,
//----- interface to directly access internal data path -----
    tx_valid_i,
    tx_data_i,
    tx_start_i,
    tx_end_i,
    tx_bytesel_i,
    tx_ready_o,
    tx_status_o,
    tx_status_valid_o,
    rx_valid_o,
    rx_data_o,
    rx_start_o,
    rx_end_o,
    rx_bytesel_o,
    rx_status_o,   
//-------------------------- end ----------------------------	
    s_ahb_sel,
    s_ahb_addr,
    s_ahb_write,
    s_ahb_trans,
    s_ahb_wdata,
    s_ahb_readyout,
    s_ahb_rdata,	

	irq
);

parameter BASE_ADDR = 32'ha000_0000;
parameter DATA_ACCESS_USE_MCU = 1; 
//---------------------------------------------------------------
// system interface
//---------------------------------------------------------------
input                  clk_tx_i;              // GMII/MII transmit reference
                                              // from PHY (2.5/25/125)Mhz.
input                  clk_rx_i;              // GMII/MII receive clock 
                                              // from PHY (2.5/25/125)Mhz.
input                  rst_clk_tx_n;          // Active Low reset synch to clk_tx_i.
input                  rst_clk_rx_n;          // Active Low reset synchronous to clk_rx_i.
input                  clk_app_i;             // clock for user application
input                  rst_clk_app_n;         // Active low reset for user application
//---------------------------------------------------------------
// MII Management Interface.
//---------------------------------------------------------------
output           gmii_mdc_o;       // GMII/MII management clock.
input            gmii_mdi_i;       // GMII/MII mgmt data input. 
output           gmii_mdo_o;       // GMII/MII mgmt data output.
output           gmii_mdo_o_e;     // GMII/MII mgmt data o/p enable.

//---------------------------------------------------------------
// Transmit PHY Interface.
//---------------------------------------------------------------
output           phy_txen_o;        // Transmit data Enable - GMII/MII, 
output           phy_txer_o;        // Transmit Error - GMII.
output [7:0]     phy_txd_o;         // Transmit Data[7:0] - GMII
                                    // Transmit Data[3:0] - MII.
//---------------------------------------------------------------
// PHY Receive Interface 
//---------------------------------------------------------------
input            phy_rxdv_i;        // Receive data valid signal - GMII/MII.
input            phy_rxer_i;        // Receive error-GMII/MII.
input  [7:0]     phy_rxd_i;         // Receive Data [7:0] in GMII.
                                    // Receive Data [3:0] in MII.
input            phy_crs_i;         // Carrier Sense in GMII/MII
input            phy_col_i;         // Collision Detect in GMII/MII.

//---------------------------------------------------------------
// Interface for directly accessing data path
//---------------------------------------------------------------
input            tx_valid_i;
input  [31:0]    tx_data_i;
input            tx_start_i;
input            tx_end_i;
input  [1:0]     tx_bytesel_i;
output           tx_ready_o;
output [7:0]     tx_status_o;
output           tx_status_valid_o;
output           rx_valid_o;
output [31:0]    rx_data_o;
output           rx_start_o;
output           rx_end_o;
output [1:0]     rx_bytesel_o;
output [7:0]     rx_status_o;

//---------------------------------------------------------------
// ARM Cortex-M3 AHB Bus
//---------------------------------------------------------------
input         s_ahb_sel;
input  [31:0] s_ahb_addr;
input         s_ahb_write;
input  [1:0]  s_ahb_trans;
input  [31:0] s_ahb_wdata;
output        s_ahb_readyout;
output [31:0] s_ahb_rdata;
output        irq;

`pragma protect begin_protected
`pragma protect version=4
`pragma protect vendor="Hercules Microelectronics"
`pragma protect email="supports@hercules-micro.com"
`pragma protect data_method="AES128-CBC"
`pragma protect data_encode="Base64"
`pragma protect key_method="RSA"
`pragma protect key_encode="Base64"
`pragma protect data_line_size=96
`pragma protect key_block
cLKDOzILQ/y7Xm1Ot833DGev2X5hbfdXtTh89L2TNZjmVfRWuZQ049VTaKKVTSw7NfQZdjL96+M3ttZ2/LueWtBbwjtERh2EvFO0Lv+O3Xhgqlt6AY7eu6XsHIWZ3YmQCQHEUNVQSeApMk8PhfB1pM1miy7c6PslTHh2e3+OoIc=
`pragma protect data_block
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
`pragma protect end_protected
endmodule

