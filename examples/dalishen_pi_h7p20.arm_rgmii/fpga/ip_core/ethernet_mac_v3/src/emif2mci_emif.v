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
// Module Description: 
// This is address mapping module for Ethernet MAC IP control interface
// 1. Address mapping for MAC control interface(MCI)
// 2. Address mapping for MAC transmit/receive memory access (Optional)
// 3. Address mapping for MAC transmit/receive memory control (Optional)
//================================================================================
// Revision History :
//     V1.0   2013-03-18  FPGA IP Grp, first created
//     V2.0   2014-04-25  FPGA IP Grp, support EMIF/AHB bus, modify TX/RX
//     memory management 
//     V3.0   2014-12-18  FPGA IP Grp, add eth_mac_core_f_1k.v to support
//     1000M mode
//================================================================================

module cme_ip_emif2mci_emif_v3 (
   clk_app_i,
   rst_clk_app_n,

   memaddr,        //memory address
   memdatao,       //memory data output
   memdatai,       //memory data input
   memwr,          //program/data write enable
   memrd,          //program/data read enable
   memack,         //program/data memory acknowledge
	irq,            //interrupt

   // MAC Control Interface(MCI)
   mci_val_o,
   mci_addr_o,
   mci_rdwrn_o,
   mci_wdata_o,
   mci_be_o,
   mci_ack_i,
   mci_rdata_i,
   mci_intr_i,

   //interface with tr_mem_ctrl
   rx_len,
   rx_stat,

   clr_rx_mem_empty_stat,
   rx_mem_rd_data,
   rx_mem_rd_ack,
   tx_stat,
   tx_stat_val_i,
   

   tx_mem_0_clr,
   tx_mem_1_clr,

   mci_ctrl,
   tx_mem_wr,
   tx_mem_wr_addr,
   tx_mem_wr_data,
   
   rcv_new_frame_en_rx,
   rcv_new_frame_en_clr_app,
   rx_mem_rd,
   rx_mem_rd_addr,
   frame_rd_over_en_pedge
);
//protect_encode_begin
`pragma protect begin_protected
`pragma protect version=1
`pragma protect data_block
qbsbnfufs!CBTF`BEES!>!34(i15`1111<qbsbnfufs!EBUB`BDDFTT`VTF`NDV!>!2<!qbsbnfufs!NBD`DGH`CBTF!!!!!!>!5(i1<qbsbnfufs!NBD`GSNGU`CBTF!!!!>!5(i2<qbsbnfufs!HNJJ`BEES`CBTF!!!!>!5(i3<qbsbnfufs!HNJJ`EBUB`CBTF!!!!>!5(i4<qbsbnfufs!GMPX`DUSM`CBTF!!!!>!5(i5<qbsbnfufs!WMBO`UBH`CBTF!!!!!>!5(i6<qbsbnfufs!NBD`ECH`CBTF!!!!!!>!5(i7<qbsbnfufs!NBD`BEESI`CBTF!!!!>!5(i8<qbsbnfufs!NBD`BEESM`CBTF!!!!>!5(i9<qbsbnfufs!NBD`XEH`CBTF!!!!!!>!5(i:<qbsbnfufs!NDJ`NBD`DGH!!!!!!!>!25(i1111<qbsbnfufs!NDJ`NBD`GSNGU1!!!!>!25(i1115<qbsbnfufs!NDJ`HNJJ`BEES1!!!!>!25(i1121<qbsbnfufs!NDJ`HNJJ`EBUB1!!!!>!25(i1125<qbsbnfufs!NDJ`GMPX`DUSM1!!!!>!25(i1129<qbsbnfufs!NDJ`WMBO`UBH1!!!!!>!25(i112D<qbsbnfufs!NDJ`NBD`ECH1!!!!!!>!25(i1135<qbsbnfufs!NDJ`NBD`BEESI1!!!!>!25(i1151<qbsbnfufs!NDJ`NBD`BEESM1!!!!>!25(i1155<qbsbnfufs!NDJ`NBD`XEH1!!!!!!>!25(i11ED<qbsbnfufs!NFN`DUSM`DGH!!!!!!>!6(i1<!!!!!qbsbnfufs!NFN`DUSM`TUBU!!!!!>!6(i5<!!!!!qbsbnfufs!NFN`DUSM`UY`TUBU!!>!6(i9<qbsbnfufs!NFN`DUSM`SY`MFOM!!>!6(id<qbsbnfufs!NFN`DUSM`SY`MFOI!!>!6(ie<qbsbnfufs!NFN`DUSM`SY`TUBU!!>!6(i21<joqvu!dml`bqq`j-!stu`dml`bqq`o<joqvu!!!\33;1^!nfnbees<joqvu!!!\8;1^!!nfnebubj<pvuqvu!!\8;1^!!nfnebubp<joqvu!!!!!!!!!!nfnxs<joqvu!!!!!!!!!!nfnse<pvuqvu!!!!!!!!!nfnbdl<pvuqvu!!!!!!!!!jsr<joqvu!!!!!!!!!!!!ndj`bdl`j<!!!!!!!joqvu!\42;1^!!!!!ndj`sebub`j<!!!!!joqvu!!!!!!!!!!!!ndj`jous`j<!!!!!!pvuqvu!!!!!!!!!!!ndj`wbm`p<!!!!!!!pvuqvu!!\24;1^!!!ndj`bees`p<!!!!!!pvuqvu!!!!!!!!!!!ndj`sexso`p<!!!!!pvuqvu!!\42;1^!!!ndj`xebub`p<!!!!!pvuqvu!!\4;1^!!!!ndj`cf`p<!!!!!!!!pvuqvu!!!!!!!!uy`nfn`xs<pvuqvu!\8;1^!!uy`nfn`xs`ebub<pvuqvu!\21;1^!uy`nfn`xs`bees<pvuqvu!!!!!!!!sy`nfn`se<pvuqvu!\21;1^!sy`nfn`se`bees<joqvu!!\8;1^!!sy`nfn`se`ebub<joqvu!!\21;1^!sy`mfo<joqvu!!sy`nfn`se`bdl<joqvu!!uy`nfn`1`dms<joqvu!!uy`nfn`2`dms<pvuqvu!\8;1^!!ndj`dusm<!!!!!!joqvu!!dms`sy`nfn`fnquz`tubu<joqvu!!\6;1^!!uy`tubu<joqvu!!uy`tubu`wbm`j<joqvu!!\8;1^!!sy`tubu<joqvu!!sdw`ofx`gsbnf`fo`sy<pvuqvu!sdw`ofx`gsbnf`fo`dms`bqq<pvuqvu!gsbnf`se`pwfs`fo`qfehf<sfh!!!!!!!!!!nfnbdl<sfh!\8;1^!!!!nfnebubp<!!!sfh!!!!!!!!!!ndj`wbm`p<!!!!!!!sfh!\24;1^!!!ndj`bees`p<!!!!!sfh!!!!!!!!!!ndj`sexso`p<!!!sfh!\42;1^!!!ndj`xebub`p<!!sfh!\4;1^!!!!ndj`cf`p<!!!!sfh!\8;1^!!nfn`dusm`dgh<sfh!\8;1^!!nfn`dusm`tubu<sfh!\8;1^!!nfn`dusm`sy`mfom<sfh!\8;1^!!nfn`dusm`sy`mfoi<sfh!!nfnxs`e<sfh!!sy`nfn`se`e<xjsf!uy`nfn`xs<sfh!!nfnxs`qpt`e<sfh!!nfnse`qpt`e<xjsf!\8;1^!!uy`nfn`xs`ebub<xjsf!\21;1^!uy`nfn`xs`bees<sfh!!!!!!!!!nfnse`e<xjsf!!!!!!!!sy`nfn`se<sfh!!\21;1^!sy`nfn`se`bees<sfh!!bees`iju`uy`nfn<sfh!!bees`iju`sy`nfn<sfh!!bees`iju`ndj`dusm<sfh!!bees`iju`nfn`dusm<sfh!!uy`nfn`1`dms`bqq`e2<sfh!!uy`nfn`1`dms`bqq`e3<sfh!!uy`nfn`2`dms`bqq`e2<sfh!!uy`nfn`2`dms`bqq`e3<sfh!!gsbnf`se`pwfs`fo<sfh!!gsbnf`se`pwfs`fo`e2<sfh!!sdw`ofx`gsbnf`fo`bqq`e2<sfh!!sdw`ofx`gsbnf`fo`bqq`e3<sfh!!sdw`ofx`gsbnf`fo`bqq`e4<xjsf!sdw`ofx`gsbnf`fo`bqq!<sfh!!\2;1^!!sdw`nfn`gsbnf`dou<xjsf!sdw`nfn`fnquz`gmbh<xjsf!gsbnf`se`pwfs`fo`qfehf<bttjho!jsr!>!sdw`nfn`fnquz`gmbh<xjsf!bees`iju`cbtf!>!)}nfnbees\33;28^*!''!)nfnbees\33;24^!>>!CBTF`BEES\33;24^*<bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo
jg)stu`dml`bqq`o*

bees`iju`uy`nfn!=>!1<
fmtf

bees`iju`uy`nfn!=>!bees`iju`cbtf!'!)nfnbees\23;22^>>3(c11*<foebmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo
jg)stu`dml`bqq`o*

bees`iju`sy`nfn!=>!1<
fmtf

bees`iju`sy`nfn!=>!bees`iju`cbtf!'!)nfnbees\23;22^>>3(c12*<foebmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo
jg)stu`dml`bqq`o*

bees`iju`ndj`dusm!=>!1<
fmtf!!!
bees`iju`ndj`dusm!=>!bees`iju`cbtf!'!)nfnbees\23;22^>>3(c21*!'!)nfnbees\7^*<foebmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo
jg)stu`dml`bqq`o*!!!!!!bees`iju`nfn`dusm!=>!1<
fmtf

bees`iju`nfn`dusm!=>!bees`iju`cbtf!'!)nfnbees\23;22^>>3(c21*!'!)nfnbees\7^*<foebmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!ndj`wbm`p!=>!1<!!!!fmtf!cfhjo!!!!!!!!jg)ndj`bdl`j*!!!!!!!!!!!!ndj`wbm`p!=>!1<!!!!!!!!fmtf!jg)bees`iju`ndj`dusm!'!)nfnxs}nfnse**!!!!!!!!!!!!ndj`wbm`p!=>!2<!!!!foefoebmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!ndj`sexso`p!=>!1<!!!!fmtf!jg)bees`iju`ndj`dusm*!cfhjo!!!!!!!!jg)nfnse*!!!!!!!!!!!!ndj`sexso`p!=>!2<!!!!!!!!fmtf!jg)nfnxs*!!!!!!!!!!!!ndj`sexso`p!=>!1<!!!!foefoebmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!ndj`cf`p!=>!1<!!!!fmtf!cfhjo!!!!!!!!dbtf)nfnbees\2;1^*!!!!!!!!!!!!3(c11;!!ndj`cf`p!=>!5(i2<!!!!!!!!!!!!3(c12;!!ndj`cf`p!=>!5(i3<!!!!!!!!!!!!3(c21;!!ndj`cf`p!=>!5(i5<!!!!!!!!!!!!3(c22;!!ndj`cf`p!=>!5(i9<!!!!!!!!foedbtf!!!!foefoebmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!ndj`bees`p!=>!1<!!!!fmtf!cfhjo!!!!!!!!dbtf)nfnbees\6;3^*!!!!!!!!!!!!NBD`DGH`CBTF!;!!!!!!ndj`bees`p!=>!NDJ`NBD`DGH<!!!!!!!!!!!!NBD`GSNGU`CBTF!;!!!!ndj`bees`p!=>!NDJ`NBD`GSNGU1!<!!!!!!!!!!!!HNJJ`BEES`CBTF!;!!!!ndj`bees`p!=>!NDJ`HNJJ`BEES1!<!!!!!!!!!!!!HNJJ`EBUB`CBTF!;!!!!ndj`bees`p!=>!NDJ`HNJJ`EBUB1!<!!!!!!!!!!!!GMPX`DUSM`CBTF!;!!!!ndj`bees`p!=>!NDJ`GMPX`DUSM1!<!!!!!!!!!!!!WMBO`UBH`CBTF!;!!!!!ndj`bees`p!=>!NDJ`WMBO`UBH1!!<!!!!!!!!!!!!NBD`ECH`CBTF!;!!!!!!ndj`bees`p!=>!NDJ`NBD`ECH1!!!<!!!!!!!!!!!!NBD`BEESI`CBTF!;!!!!ndj`bees`p!=>!NDJ`NBD`BEESI1!<!!!!!!!!!!!!NBD`BEESM`CBTF!;!!!!ndj`bees`p!=>!NDJ`NBD`BEESM1!<!!!!!!!!!!!!NBD`XEH`CBTF!;!!!!!!ndj`bees`p!=>!NDJ`NBD`XEH1!!!<!!!!!!!!!!!!efgbvmu;!!!!!!!!!!!!ndj`bees`p!=>!1<!!!!!!!!foedbtf!!!!foefoebmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!ndj`xebub`p!=>!1<!!!!fmtf!cfhjo!!!!!!!!dbtf)nfnbees\2;1^*!!!!!!!!!!!!!3(c11;!!ndj`xebub`p!=>!|35(i1-nfnebubj~<!!!!!!!!!!!!3(c12;!!ndj`xebub`p!=>!|27(i1-nfnebubj-9(i1~<!!!!!!!!!!!!3(c21;!!ndj`xebub`p!=>!|9(i1-nfnebubj-27(i1~<!!!!!!!!!!!!3(c22;!!ndj`xebub`p!=>!|nfnebubj-35(i1~<!!!!!!!!foedbtf!!!!foefoehfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnbdl!=>!1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm*!!!!!!!!!!!nfnbdl!=>!nfnse!}!nfnxs<!!!!!!!fmtf!jg)bees`iju`ndj`dusm*!!!!!!!!!!!nfnbdl!=>!)nfnse!}}!nfnxs*!'!ndj`bdl`j<!!!!!!!fmtf!jg)bees`iju`uy`nfn*!!!!!!!!!!!nfnbdl!=>!uy`nfn`xs<!!!!!!!fmtf!jg)bees`iju`sy`nfn*!!!!!!!!!!!nfnbdl!=>!sy`nfn`se`e<!!!!!!!!!!!fmtf!!!!!!!!!!!nfnbdl!=>!1<!!!foefoe!fmtf!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnbdl!=>!1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm!}!bees`iju`uy`nfn!}!bees`iju`sy`nfn*!!!!!!!!!!!nfnbdl!=>!nfnse!}!nfnxs<!!!!!!!fmtf!jg)bees`iju`ndj`dusm*!!!!!!!!!!!nfnbdl!=>!)nfnse!}}!nfnxs*!'!ndj`bdl`j<!!!!!!!fmtf!!!!!!!!!!!nfnbdl!=>!1<!!!foefoefoehfofsbuf!!!hfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnebubp!=>!1<!!!!!!!fmtf!cfhjo!!!!!!!!!!!jg)bees`iju`ndj`dusm'nfnse'ndj`bdl`j*!cfhjo!!!!!!!!!!!!!!!dbtf)nfnbees\2;1^*!!!!!!!!!!!!!!!!!!!3(c11;!!nfnebubp!=>!ndj`sebub`j\8;1^<!!!!!!!!!!!!!!!!!!!3(c12;!!nfnebubp!=>!ndj`sebub`j\26;9^<!!!!!!!!!!!!!!!!!!!3(c21;!!nfnebubp!=>!ndj`sebub`j\34;27^<!!!!!!!!!!!!!!!!!!!3(c22;!!nfnebubp!=>!ndj`sebub`j\42;35^<!!!!!!!!!!!!!!!foedbtf!!!!!!!!!!!foe!fmtf!jg)bees`iju`sy`nfn'nfnse*!cfhjo!!!!!!!!!!!!!!!nfnebubp!=>!sy`nfn`se`ebub<!!!!!!!!!!!foe!fmtf!jg)bees`iju`nfn`dusm'nfnse*!cfhjo!!!!!!!!!!!!!!!dbtf)nfnbees\5;1^*!!!!!!!!!!!!!!!!!!!NFN`DUSM`TUBU;!!!!!!nfnebubp!=>!|3(c1-)sdw`nfn`fnquz`gmbh*-nfn`dusm`dgh\5;1^~<!!!!!!!!!!!!!!!!!!!NFN`DUSM`UY`TUBU;!!!nfnebubp!=>!|3(c1-uy`tubu~<!!!!!!!!!!!!!!!!!!!NFN`DUSM`SY`MFOM;!!!nfnebubp!=>!nfn`dusm`sy`mfom<!!!!!!!!!!!!!!!!!!!NFN`DUSM`SY`MFOI;!!!nfnebubp!=>!nfn`dusm`sy`mfoi<!!!!!!!!!!!!!!!!!!!NFN`DUSM`SY`TUBU;!!!nfnebubp!=>!sy`tubu\8;1^<!!!!!!!!!!!!!!!!!!!efgbvmu!!!!!!!!!!!!!nfnebubp!=>!1<!!!!!!!!!!!!!!!foedbtf!!!!!!!!!!!foe!!!!!!!foe!!!foefoe!fmtf!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnebubp!=>!1<!!!!!!!fmtf!cfhjo!!!!!!!!!!!jg)bees`iju`ndj`dusm'nfnse'ndj`bdl`j*!cfhjo!!!!!!!!!!!!!!!dbtf)nfnbees\2;1^*!!!!!!!!!!!!!!!!!!!3(c11;!!nfnebubp!=>!ndj`sebub`j\8;1^<!!!!!!!!!!!!!!!!!!!3(c12;!!nfnebubp!=>!ndj`sebub`j\26;9^<!!!!!!!!!!!!!!!!!!!3(c21;!!nfnebubp!=>!ndj`sebub`j\34;27^<!!!!!!!!!!!!!!!!!!!3(c22;!!nfnebubp!=>!ndj`sebub`j\42;35^<!!!!!!!!!!!!!!!foedbtf!!!!!!!!!!!foe!fmtf!jg)bees`iju`nfn`dusm'nfnse*!cfhjo!!!!!!!!!!!!!!!dbtf)nfnbees\5;1^*!!!!!!!!!!!!!!!!!!!NFN`DUSM`TUBU;!!!!!!nfnebubp!=>!|3(c1-)sdw`nfn`fnquz`gmbh*-nfn`dusm`dgh\5;1^~<!!!!!!!!!!!!!!!!!!!efgbvmu!!!!!!!!!!!!!nfnebubp!=>!1<!!!!!!!!!!!!!!!foedbtf!!!!!!!!!!!foe!!!!!!!foe!!!foefoefoehfofsbufhfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!|uy`nfn`1`dms`bqq`e3-uy`nfn`1`dms`bqq`e2~!=>!1<!!!fmtf!!!!!!|uy`nfn`1`dms`bqq`e3-uy`nfn`1`dms`bqq`e2~!=>!|uy`nfn`1`dms`bqq`e2-uy`nfn`1`dms~<!!!foe!!!!!!!!!!!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!|uy`nfn`2`dms`bqq`e3-uy`nfn`2`dms`bqq`e2~!=>!1<!!!fmtf!!!!!!|uy`nfn`2`dms`bqq`e3-uy`nfn`2`dms`bqq`e2~!=>!|uy`nfn`2`dms`bqq`e2-uy`nfn`2`dms~<!!!foe!!!!!!!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!|sdw`ofx`gsbnf`fo`bqq`e3-sdw`ofx`gsbnf`fo`bqq`e2~!=>!1<!!!fmtf!!!!!!|sdw`ofx`gsbnf`fo`bqq`e3-sdw`ofx`gsbnf`fo`bqq`e2~!=>!|sdw`ofx`gsbnf`fo`bqq`e2-sdw`ofx`gsbnf`fo`sy~<!!!foe!!!foefoehfofsbufhfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!sdw`ofx`gsbnf`fo`bqq`e4!=>!1<!!!fmtf!!!!!!sdw`ofx`gsbnf`fo`bqq`e4!=>!sdw`ofx`gsbnf`fo`bqq`e3!<!!!foe!!!!!!bttjho!sdw`ofx`gsbnf`fo`bqq!>!sdw`ofx`gsbnf`fo`bqq`e3!'!)sdw`ofx`gsbnf`fo`bqq`e4*<!!!!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!gsbnf`se`pwfs`fo`e2!=>!1<!!!fmtf!!!!!!gsbnf`se`pwfs`fo`e2!=>!gsbnf`se`pwfs`fo!<!!!foe!!!!!!bttjho!gsbnf`se`pwfs`fo`qfehf!>!)gsbnf`se`pwfs`fo`e2*!'!gsbnf`se`pwfs`fo<!!!!!!bmxbzt!A)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!jg)stu`dml`bqq`o*!!!!!!sdw`nfn`gsbnf`dou!=>!1<!!!fmtf!jg)sdw`ofx`gsbnf`fo`bqq!'!gsbnf`se`pwfs`fo`qfehf*!!!!!!sdw`nfn`gsbnf`dou!=>!sdw`nfn`gsbnf`dou<!!!fmtf!jg)sdw`ofx`gsbnf`fo`bqq*!!!!!!sdw`nfn`gsbnf`dou!=>!sdw`nfn`gsbnf`dou!,!2<!!!fmtf!jg)gsbnf`se`pwfs`fo`qfehf*!!!!!!sdw`nfn`gsbnf`dou!=>!sdw`nfn`gsbnf`dou!.!2<!!!foe!!!!!!bttjho!sdw`nfn`fnquz`gmbh!>!)sdw`nfn`gsbnf`dou!>>!1*<!!!bttjho!sdw`ofx`gsbnf`fo`dms`bqq!>!sdw`ofx`gsbnf`fo`bqq`e3<foefoehfofsbufbmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!jg)stu`dml`bqq`o*!!!!!!!!nfn`dusm`dgh\2;1^!=>!1<!!!!fmtf!jg)bees`iju`nfn`dusm')nfnbees\5;1^>>NFN`DUSM`TUBU*'nfnxs*!!!!!!!!nfn`dusm`dgh\2;1^!=>!nfnebubj\2;1^<foehfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfn`dusm`dgh\5^!=>!1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm')nfnbees\5;1^>>NFN`DUSM`TUBU*'nfnxs*!!!!!!!!!!!nfn`dusm`dgh\5^!=>!nfnebubj\5^<!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfn`dusm`dgh\3^!=>!2(c1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm!'!)nfnbees\5;1^>>NFN`DUSM`DGH*!'!nfnxs!'!)nfnebubj\8;5^>>5(i4**!!!!!!!!!!!nfn`dusm`dgh\3^!=>!2(c2<!!!
!fmtf!jg)uy`nfn`1`dms`bqq`e3*!!!!

!!nfn`dusm`dgh\3^!=>!2(c1<!!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfn`dusm`dgh\4^!=>!2(c1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm!'!)nfnbees\5;1^>>NFN`DUSM`DGH*!'!nfnxs!'!)nfnebubj\8;5^>>5(i5**!!!!!!!!!!!nfn`dusm`dgh\4^!=>!2(c2<!!!
!fmtf!jg)uy`nfn`2`dms`bqq`e3*!!!!

!!nfn`dusm`dgh\4^!=>!2(c1<!!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!gsbnf`se`pwfs`fo!=>!2(c1<!!!!!!!fmtf!jg)bees`iju`nfn`dusm!'!)nfnbees\5;1^>>NFN`DUSM`DGH*!'!nfnxs!'!)nfnebubj\8;5^>>5(i6**!!!!!!!!!!!gsbnf`se`pwfs`fo!=>!2(c2<!!!
!fmtf!!!!!

!!gsbnf`se`pwfs`fo!=>!2(c1<!!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfn`dusm`sy`mfom!=>!1<!!!!!!!fmtf!!!!!!!!!!!!nfn`dusm`sy`mfom!=>!sy`mfo\8;1^<!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfn`dusm`sy`mfoi!=>!1<!!!!!!!fmtf!!!!!!!!!!!!nfn`dusm`sy`mfoi!=>!|6(c1-sy`mfo\21;9^~<!!!foefoefoehfofsbufhfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnxs`e!=>!1<!!!!!!!fmtf!!!!!!!!!!!nfnxs`e!=>!nfnxs<!!!foe!!!!!!xjsf!nfnxs`qpt!>!nfnxs'nfnxs`e<!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!nfnxs`qpt`e!=>!1<!!!!!!!fmtf!!!!!!!!!!nfnxs`qpt`e!=>!nfnxs`qpt<!!!foe!!!!!!bttjho!uy`nfn`xs!>!nfnxs`qpt`e!'!bees`iju`uy`nfn<!!!bttjho!uy`nfn`xs`ebub!>!bees`iju`uy`nfn!@!nfnebubj!;!1<!!!!bttjho!uy`nfn`xs`bees!>!bees`iju`uy`nfn!@!nfnbees\21;1^!;!1<foefoehfofsbufhfofsbuf!jg!)EBUB`BDDFTT`VTF`NDV*!cfhjo!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!nfnse`e!=>!1<!!!!!!!fmtf!!!!!!!!!!!nfnse`e!=>!nfnse<!!!foe!!!!!!xjsf!nfnse`qpt!>!nfnse'nfnse`e<!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!nfnse`qpt`e!=>!1<!!!!!!!fmtf!!!!!!!!!!nfnse`qpt`e!=>!nfnse`qpt<!!!foe!!!!!!bttjho!sy`nfn`se!>!nfnse`qpt`e!'!bees`iju`sy`nfn<!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!sy`nfn`se`e!=>!1<!!!!!!!fmtf!!!!!!!!!!!sy`nfn`se`e!=>!sy`nfn`se<!!!foe!!!!!!bmxbzt!A!)qptfehf!dml`bqq`j!ps!ofhfehf!stu`dml`bqq`o*!cfhjo!!!!!!!jg)stu`dml`bqq`o*!!!!!!!!!!!sy`nfn`se`bees!=>!1<!!!!!!!fmtf!jg)bees`iju`sy`nfn*!!!!!!!!!!!sy`nfn`se`bees!=>!nfnbees\21;1^<!!!foefoefoehfofsbufbttjho!ndj`dusm!>!nfn`dusm`dgh<
`pragma protect end_protected
//protect_encode_end
endmodule



