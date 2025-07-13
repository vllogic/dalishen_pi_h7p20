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
module cme_ip_eth_mac_top_ahb_f_1k_v3 (
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

//protect_encode_begin
`pragma protect begin_protected
`pragma protect version=1
`pragma protect data_block
xjsf!!!!!!!!ndj`bdl`p<xjsf!!!!!!!!ndj`wbm`p<xjsf!!!!!!!!ndj`sexso`p<xjsf!!!!\4;1^!!!ndj`cf`p<xjsf!!!!\24;1^!!ndj`bees`p<xjsf!!!!\42;1^!!ndj`sebub`p<xjsf!!!!\42;1^!!ndj`xebub`p<xjsf!!!!\8;1^!!!ndj`dusm<xjsf!!!!uy`nfn`xs<xjsf!!!!\42;1^!!uy`nfn`xs`ebub<xjsf!!!!\9;1^!!!uy`nfn`xs`bees<xjsf!!!!sy`nfn`se<xjsf!!!!\42;1^!!sy`nfn`se`ebub<xjsf!!!!\9;1^!!!sy`nfn`se`bees<xjsf!!!!\21;1^!!sy`mfo<xjsf!!!!dms`sy`nfn`fnquz`tubu<xjsf!!!!\6;1^!!uy`tubu<xjsf!!!!\8;1^!!sy`tubu<xjsf!!!!uy`tubu`wbm`p<xjsf!!!!nuj`sez`p<xjsf!!!!nuj`wbm`p<xjsf!!!!nuj`tpg`p<xjsf!!!!nuj`fpg`p<xjsf!!!!nuj`ejtdsd`p<xjsf!!!!nuj`ejtqbe`p<xjsf!!!!nuj`ejtdsd`j<xjsf!!!!nuj`ejtqbe`j<xjsf!!!!nuj`gmpxdusm`p<xjsf!!!!\2;1^!!!nuj`cf`p<xjsf!!!!\42;1^!!nuj`ebub`p<xjsf!!!!nuj`uytubuvt`wbm`p<xjsf!!!!\42;1^!!nuj`uytubuvt`p<xjsf!!!!dpsf`nuj`wbm`j<xjsf!!!!dpsf`nuj`tpg`j<xjsf!!!!dpsf`nuj`fpg`j<xjsf!!!!\42;1^!!dpsf`nuj`ebub`j<xjsf!!!!\2;1^!!!dpsf`nuj`cf`j<xjsf!!!!nsj`wbm`p<xjsf!!!!nsj`tpg`p<xjsf!!!!nsj`fpg`p<xjsf!!!!\2;1^!!!nsj`cf`p<xjsf!!!!\42;1^!!nsj`ebub`p<xjsf!!!!\42;1^!!nsj`sytubuvt`p<xjsf!!!!ndj`jous`p<xjsf!!!!uy`nfn`1`dms<xjsf!!!!uy`nfn`2`dms<xjsf!!!!gsbnf`se`pwfs`fo`qfehf<xjsf!!!!sdw`ofx`gsbnf`fo`dms<xjsf!!!!sdw`ofx`gsbnf`fo<bttjho!dpsf`nuj`wbm`j!!>!EBUB`BDDFTT`VTF`NDV!@!nuj`wbm`p!!;!uy`wbmje`j<bttjho!dpsf`nuj`ebub`j!>!EBUB`BDDFTT`VTF`NDV!@!nuj`ebub`p!;!uy`ebub`j<bttjho!dpsf`nuj`tpg`j!!>!EBUB`BDDFTT`VTF`NDV!@!nuj`tpg`p!!;!uy`tubsu`j<bttjho!dpsf`nuj`fpg`j!!>!EBUB`BDDFTT`VTF`NDV!@!nuj`fpg`p!!;!uy`foe`j<bttjho!dpsf`nuj`cf`j!!!>!EBUB`BDDFTT`VTF`NDV!@!nuj`cf`p!!!;!uy`czuftfm`j<bttjho!uy`sfbez`p!!!!!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nuj`sez`p<bttjho!uy`tubuvt`p!!!!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!|3(c1-nuj`uytubuvt`p\3:;38^-nuj`uytubuvt`p\4;3^-nuj`uytubuvt`p\1^~<bttjho!uy`tubuvt`wbmje`p>!EBUB`BDDFTT`VTF`NDV!@!1!;!nuj`uytubuvt`wbm`p<bttjho!sy`wbmje`p!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nsj`wbm`p<bttjho!sy`ebub`p!!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nsj`ebub`p<bttjho!sy`tubsu`p!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nsj`tpg`p<bttjho!sy`foe`p!!!!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nsj`fpg`p<bttjho!sy`czuftfm`p!>!EBUB`BDDFTT`VTF`NDV!@!1!;!nsj`cf`p<bttjho!sy`tubuvt`p!!>!EBUB`BDDFTT`VTF`NDV!@!1!;!|nsj`sytubuvt`p\37^-nsj`sytubuvt`p\35;32^-nsj`sytubuvt`p\28;26^~<bttjho!nuj`ejtdsd`j!>!EBUB`BDDFTT`VTF`NDV!@!nuj`ejtdsd`p!;!ndj`dusm\1^!<bttjho!nuj`ejtqbe`j!>!EBUB`BDDFTT`VTF`NDV!@!nuj`ejtqbe`p!;!ndj`dusm\2^!<dnf`jq`fui`nbd`dpsf`g`2l`w4!v`fui`nbd`dpsf!)!!!!
/dml`dts`j

)dml`bqq`j*-!!!!
/stu`dml`dts`o

)stu`dml`bqq`o*-!!!!
/nuj`wbm`j

)dpsf`nuj`wbm`j*-!!!!
/nuj`ebub`j

)dpsf`nuj`ebub`j*-!!!!
/nuj`tpg`j

)dpsf`nuj`tpg`j*-!!!!
/nuj`fpg`j

)dpsf`nuj`fpg`j*-!!!!
/nuj`cf`j!!!!!!!)dpsf`nuj`cf`j*-!!!!
/nuj`ejtdsd`j

)nuj`ejtdsd`j*-!!!!
/nuj`ejtqbe`j

)nuj`ejtqbe`j*-!!!!
/nuj`gmpxdusm`j

)nuj`gmpxdusm`p*-!!!!
/dml`uy`j

)dml`uy`j*-!!!!
/dml`sy`j

)dml`sy`j*-!!!!
/stu`dml`uy`o

)stu`dml`uy`o*-!!!!
/stu`dml`sy`o

)stu`dml`sy`o*-!!!!
/ndj`wbm`j

)ndj`wbm`p*-!!!!
/ndj`bees`j

)ndj`bees`p*-!!!!
/ndj`sexso`j

)ndj`sexso`p*-!!!!
/ndj`xebub`j

)ndj`xebub`p*-!!!!
/ndj`cf`j

)ndj`cf`p*-!!!!
/hnjj`nej`j

)hnjj`nej`j*-!!!!
/qiz`syew`j

)qiz`syew`j*-!!!!
/qiz`syfs`j

)qiz`syfs`j*-!!!!
/qiz`sye`j

)qiz`sye`j*-!!!!
/qiz`dst`j

)qiz`dst`j*-!!!!
/qiz`dpm`j

)qiz`dpm`j*-!!!!!!!!
/nuj`sez`p

)nuj`sez`p*-!!!!
/nuj`uytubuvt`p

)nuj`uytubuvt`p*-!!!!
/nuj`uytubuvt`wbm`p
)nuj`uytubuvt`wbm`p*-!!!!
/nsj`wbm`p

)nsj`wbm`p*-!!!!
/nsj`ebub`p

)nsj`ebub`p*-!!!!
/nsj`tpg`p

)nsj`tpg`p*-!!!!
/nsj`fpg`p

)nsj`fpg`p*-!!!!!!!!/nsj`cf`p!!!!!!!)nsj`cf`p*-!!!!
/nsj`sytubuvt`p

)nsj`sytubuvt`p*-!!!!
/ndj`bdl`p

)ndj`bdl`p*-!!!!
/ndj`sebub`p

)ndj`sebub`p*-!!!!
/ndj`jous`p

)ndj`jous`p*-!!!!
/hnjj`ned`p

)hnjj`ned`p*-!!!!
/hnjj`nep`p

)hnjj`nep`p*-!!!!
/hnjj`nep`p`f

)hnjj`nep`p`f*-!!!!
/qiz`uyfo`p

)qiz`uyfo`p*-!!!!
/qiz`uyfs`p

)qiz`uyfs`p*-!!!!
/qiz`uye`p

)qiz`uye`p*!!!!!*<efgqbsbn!v`bic3ndj/CBTF`BEES!>!CBTF`BEES<efgqbsbn!v`bic3ndj/EBUB`BDDFTT`VTF`NDV!>!EBUB`BDDFTT`VTF`NDV<dnf`jq`bic3ndj`bic`w4!v`bic3ndj!)!!!!
/dml`bqq`j

)dml`bqq`j*-!!!!
/stu`dml`bqq`o

)stu`dml`bqq`o*-!!!!
!!!!!!/gq1`t`bic`tfm!!!!!)t`bic`tfm*-!!!!!!!!!!!!!!!!!!!!/gq1`t`bic`bees!!!!)t`bic`bees*-!!!!!!/gq1`t`bic`xsjuf!!!)t`bic`xsjuf*-!!!!!!!!/gq1`t`bic`usbot!!!)t`bic`usbot*-!!!!!!!!!/gq1`t`bic`xebub!!!)t`bic`xebub*-!!!!!!!!/gq1`t`bic`sfbezpvu)t`bic`sfbezpvu*-!!!!!!/gq1`t`bic`sebub!!!)t`bic`sebub*-!!!!!!!
/jsr!!!!!!!!!!!!!!!)jsr*-!!!!
/ndj`bdl`j

)ndj`bdl`p*-!!!!
/ndj`sebub`j

)ndj`sebub`p*-!!!!
/ndj`jous`j

)ndj`jous`p*-!!!!!!/ndj`wbm`p

)ndj`wbm`p*-!!!!
/ndj`bees`p

)ndj`bees`p*-!!!!
/ndj`sexso`p

)ndj`sexso`p*-!!!!
/ndj`xebub`p

)ndj`xebub`p*-!!!!
/ndj`cf`p

)ndj`cf`p*-!!!!
/sy`nfn`se`ebub

)sy`nfn`se`ebub*-!!!!!!/sy`nfn`se`bdl!!)2(c2*-!!!!
/sy`mfo


)sy`mfo\21;1^*-!!!
/dms`sy`nfn`fnquz`tubu
)dms`sy`nfn`fnquz`tubu*-!!!!
/uy`tubu

)uy`tubu\6;1^*-!!!!
/uy`tubu`wbm`j

)uy`tubu`wbm`p*-!!!!
/sy`tubu

)sy`tubu\8;1^*-!!!!!!/uy`nfn`1`dms!!)uy`nfn`1`dms*-!!!!!!/uy`nfn`2`dms!!)uy`nfn`2`dms*-!!!!!!/sdw`ofx`gsbnf`fo`sy)sdw`ofx`gsbnf`fo*-!!!!!!/sdw`ofx`gsbnf`fo`dms`bqq)sdw`ofx`gsbnf`fo`dms*-!!!!!!!!
/uy`nfn`xs

)uy`nfn`xs*-!!!!
/uy`nfn`xs`ebub

)uy`nfn`xs`ebub*-!!!!
/uy`nfn`xs`bees

)uy`nfn`xs`bees*-!!!!!
/sy`nfn`se

)sy`nfn`se*-!!!!
/sy`nfn`se`bees

)sy`nfn`se`bees*-!!!!!!/gsbnf`se`pwfs`fo`qfehf)gsbnf`se`pwfs`fo`qfehf*-!!!!
/ndj`dusm

)ndj`dusm\8;1^*!!!!!*<hfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjodnf`jq`us`nfn`dusm`bic`w4!v`us`nfn`dusm!)!!!!
/dml`uy`j

)dml`uy`j*-!!!!
/dml`sy`j

)dml`sy`j*-!!!!
/dml`bqq`j

)dml`bqq`j*-!!!!
/stu`dml`uy`o
)stu`dml`uy`o*-!!!!
/stu`dml`sy`o
)stu`dml`sy`o*-!!!!
/stu`dml`bqq`o
)stu`dml`bqq`o*-!!!!
/nuj`sez`j

)nuj`sez`p*-!!!!
/nuj`uytubuvt`j

)nuj`uytubuvt`p*-!!!!
/nuj`uytubuvt`wbm`j
)nuj`uytubuvt`wbm`p*-!!!!
/nuj`wbm`p

)nuj`wbm`p*-!!!!
/nuj`ebub`p

)nuj`ebub`p*-!!!!
/nuj`tpg`p

)nuj`tpg`p*-!!!!
/nuj`fpg`p

)nuj`fpg`p*-!!!!
/nuj`cf`p

)nuj`cf`p*-!!!!
/nuj`ejtdsd`p

)nuj`ejtdsd`p*-!!!!
/nuj`ejtqbe`p

)nuj`ejtqbe`p*-!!!!
/nuj`gmpxdusm`p

)nuj`gmpxdusm`p*-!!!!
/nsj`wbm`j

)nsj`wbm`p*-!!!!
/nsj`ebub`j

)nsj`ebub`p*-!!!!
/nsj`cf`j

)nsj`cf`p*-!!!!
/nsj`tpg`j

)nsj`tpg`p*-!!!!
/nsj`fpg`j

)nsj`fpg`p*-!!!!
/nsj`sytubuvt`j

)nsj`sytubuvt`p*-

!!!!
/ndj`dusm

)ndj`dusm\8;1^*-!!!!
/uy`nfn`xs

)uy`nfn`xs*-!!!!
/uy`nfn`xs`bees

)uy`nfn`xs`bees*-!!!!
/uy`nfn`xs`ebub

)uy`nfn`xs`ebub*-!!!!
/uy`tubu`wbm`p

)uy`tubu`wbm`p*-!!!!
/uy`tubu

)uy`tubu\6;1^*-!!!!!!/uy`nfn`1`dms!!)uy`nfn`1`dms*-!!!!!!/uy`nfn`2`dms!!)uy`nfn`2`dms*-!!!!
/sy`nfn`se

)sy`nfn`se*-!!!!
/sy`nfn`se`ebub

)sy`nfn`se`ebub*-!!!!
/sy`nfn`gsbnf`mfo
)sy`mfo\21;1^*-!!!!
/sy`nfn`gsbnf`tubuvt

)sy`tubu\8;1^*-!!!!!!/sdw`ofx`gsbnf`fo`sy!!!!)sdw`ofx`gsbnf`fo*-!!!!!!/sdw`ofx`gsbnf`fo`dms`bqq)sdw`ofx`gsbnf`fo`dms*-!!!!!!/gsbnf`se`pwfs`fo`qfehf)gsbnf`se`pwfs`fo`qfehf*!!!!*<foefoehfofsbuf
`pragma protect end_protected
//protect_encode_end
endmodule

