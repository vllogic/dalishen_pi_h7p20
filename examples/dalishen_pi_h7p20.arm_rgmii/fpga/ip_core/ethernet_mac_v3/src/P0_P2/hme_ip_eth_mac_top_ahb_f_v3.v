//================================================================================
// Copyright (c) 2013 Hercules-micro, Inc.(Shanghai)  All rights reserved.
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
// Module Description: Top Module of Ethernet MAC IP core
//================================================================================
// Revision History :
//     V1.0   2013-03-18  FPGA IP Grp, first created
//     V2.0   2014-04-25  FPGA IP Grp, support EMIF/AHB bus, modify TX/RX
//     memory management 
//     V3.0   2014-12-18  FPGA IP Grp, add eth_mac_core_f_1k.v to support
//     1000M mode
//================================================================================
module hme_ip_eth_mac_top_ahb_f_v3 (
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

parameter BASE_ADDR = 32'h0000_0000;
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
X9xbmTgnIDOChnYRPXw6hz/Pg9P/xvPjW9CDPdYuo8eyJCa3LDJ28Jbq0w0/jvkMG/JNQLOzk59Joz1Oe99HwfEnYCScPypXM/Q6Hvj5Xz7j0KYKH+/ZOn04vans5rpeRfpGEzH0FiI0t9elNFKEnzceeuhp3QBA1Hbi8anffAA=
`pragma protect data_block
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
`pragma protect end_protected
endmodule
