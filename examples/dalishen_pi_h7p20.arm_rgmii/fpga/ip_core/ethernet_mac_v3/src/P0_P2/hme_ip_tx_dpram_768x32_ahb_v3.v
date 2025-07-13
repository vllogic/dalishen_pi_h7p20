// ============================================================
// File Name: tx_dpram_768x32_ahb.v
// IP core  : ethernet_mac_v2 
// Function : TX memory management
// ============================================================

module hme_ip_tx_dpram_768x32_ahb_v3(
        clkw,
        cew,
        aw,
        dw,
        wr_ram_sel,

        clkr,
        cer,
        ar,
        qr,
        mti_rdy_i,
        rd_ram_sel
        );
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
IqnSzEMAwSXq0B00EAQ4RrUaQ+pkw1EylBIVvH8fSCakg+QYVT487sPTaJjOES+aARke44eNAMxdSUbuHHDB8jhqU1lR2+4X+isPoccz5E42JSSRkZtE4RsskTwudFJO21z9If1zntNAvNcFACZ5TQNMiHUCrydEhBZengce9+Q=
`pragma protect data_block
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
`pragma protect end_protected
endmodule


