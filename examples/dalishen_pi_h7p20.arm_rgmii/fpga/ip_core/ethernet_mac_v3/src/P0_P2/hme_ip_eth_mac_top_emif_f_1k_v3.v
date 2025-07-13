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
module hme_ip_eth_mac_top_emif_f_1k_v3 (
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
	 memaddr,
	 memdatao,
	 memrd,
	 memwr,
	 memack,
	 memdatai,
	 irq
);

parameter BASE_ADDR = 23'h04_0000;   // IP base address in the MCU address space

parameter DATA_ACCESS_USE_MCU = 1;   // Whether to use the mcu to implement data access
                                     // 1: use        0: do not use
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
// External memory interface (EMIF)
//---------------------------------------------------------------
input   [22:0]	memaddr;
input   [7:0]	memdatai;
output  [7:0]	memdatao;
input		memrd;
input		memwr;
output	memack;
output   irq;
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
Qa/Zs/ie7Va9kyQRpUrKFvmDtmg1byW3pv3Mg6uGzxDTaxmFMm/GHv1q6uT16eg+kDX7wrKZoRwFMsHGyXW6WiiNFUP6zahRhktXhH4q1iqQvjfKqZ9+kwgBmD2mueLza7f5qQzWy6HKt1BMPKDWPyXnADTF3Ww2tVDoBVHfEk8=
`pragma protect data_block
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
w/XGd+AeeW7Ty3j+9aKIBQ==
`pragma protect end_protected
endmodule

