`define RGMII_ETH


module top (
    input  uart_rx,
    output uart_tx,

    input usb334x_clk_60m,

    output [3:0] o_rgmii_txd,
    output o_rgmii_tx_ctl,
    output o_rgmii_txc,

    input [3:0] i_rgmii_rxd,
    input i_rgmii_rx_ctl,
    input i_rgmii_rxc,

    output o_mdc,
    inout io_mdio,

    output o_phy_rstn,
    
    output etha_25m
);

wire etha_25m;
wire eth_125m;
wire sys_clk;

pll_v1 pll_v1_inst (
    .clkin0             (usb334x_clk_60m),  // input 60M
    .locked             (locked),
    .clkout0            (etha_25m),         // out0 25M
    .clkout1            (eth_125m),         // out1 125M
    .clkout2            (sys_clk)           // out2 100M
);

`ifdef RGMII_ETH

wire reset;
wire rstn_cpu;
wire rst_clk_rx_n;
wire rst_clk_tx_n;
wire rst_clk_app_n;
wire locked;

wire hclk;
wire hresetn;
wire hsel;
wire hresp;
wire hready_resp;
wire [31:0] hrdata;
wire [31:0] haddr;
wire [1:0] htrans;
wire [2:0] hsize;
wire [2:0] hburst;
wire hwrite;
wire [31:0] hwdata;

wire gmii_tx_en;
wire gmii_tx_er;
wire [9:0] gmii_txd;
wire [7:0] gmii_rxd;
wire gmii_crs;
wire gmii_col;
wire gmii_rx_dv;
wire gmii_rx_er;

wire gmii_mdi;
wire gmii_mdo;
wire gmii_mdo_t;
wire gmii_mdc;


assign reset = !locked;
assign rstn_cpu = locked;

assign rst_clk_rx_n = locked;
assign rst_clk_tx_n = locked;
assign rst_clk_app_n = locked;

assign o_phy_rstn = locked;

assign hclk = sys_clk;
assign hresetn = locked;
assign hsel = 1'b1;


rgmii_v1 rgmii_v1(
    .clk_eth            (eth_125m),
    
    .i_tx_clk_d0        (0),
    .i_tx_clk_d1        (1),

    .gmii_tx_en         (gmii_tx_en),
    .gmii_txd           (gmii_txd),
    .gmii_tx_er         (gmii_tx_er),

    .rgmii_txc          (o_rgmii_txc),
    .rgmii_tx_ctl       (o_rgmii_tx_ctl),
    .rgmii_txd          (o_rgmii_txd),

    .rgmii_rxc          (i_rgmii_rxc),
    .rgmii_rx_ctl       (i_rgmii_rx_ctl),
    .rgmii_rxd          (i_rgmii_rxd),

    .gmii_rx_clk        (gmii_rx_clk),
    .gmii_rx_dv         (gmii_rx_dv),
    .gmii_rx_er         (gmii_rx_er),
    .gmii_rxd           (gmii_rxd)
);

mdio_interface mdio_interfac_inst (
    .i_mdc              (gmii_mdc),
    .o_mdi              (gmii_mdi),
    .i_mdo              (gmii_mdo),
    .i_mdo_t            (gmii_mdio_t),

    .o_mdc              (o_mdc),
    .io_mdio            (io_mdio)
);

EthernetMAC_v3 EthernetMAC_v3_inst (
    .clk_tx_i           (eth_125m),
    .clk_rx_i           (gmii_rx_clk),
    .clk_app_i          (sys_clk),
    .rst_clk_rx_n       (rst_clk_rx_n),
    .rst_clk_tx_n       (rst_clk_tx_n),
    .rst_clk_app_n      (rst_clk_app_n),
    .s_ahb_addr         (haddr),
    .s_ahb_sel          (hsel),
    .s_ahb_write        (hwrite),
    .s_ahb_trans        (htrans),
    .s_ahb_wdata        (hwdata),
    .s_ahb_readyout     (hready_resp),
    .s_ahb_rdata        (hrdata),
    .phy_txen_o         (gmii_tx_en),
    .phy_txer_o         (gmii_tx_er),
    .phy_txd_o          (gmii_txd),
    .phy_rxd_i          (gmii_rxd),
    .phy_crs_i          (gmii_crs),
    .phy_col_i          (gmii_col),
    .phy_rxdv_i         (gmii_rx_dv),
    .phy_rxer_i         (gmii_rx_er),
    .gmii_mdc_o         (gmii_mdc),
    .gmii_mdi_i         (gmii_mdi),
    .gmii_mdo_o         (gmii_mdo),
    .gmii_mdo_o_e       (gmii_mdio_t),
    .irq                ()
);
`endif

soc_system_v1 soc_system_v1_inst (
    .m3soc_clk_o                    (sys_clk),
    .m3soc_clken                    (1'b1),
    .m3soc_rstn                     (rstn_cpu),

    .u_m3soc_gpio0_ext_porta_i      (),
    .u_m3soc_gpio0_porta_ddr_o      (),
    .u_m3soc_gpio0_porta_dr_o       (),

    .u_m3soc_fp_clk                 (sys_clk),
    .u_m3soc_fp_rst_n               (rstn_cpu),

    .hclk_fp_brg_gate               (),

`ifdef RGMII_ETH
    .u_m3soc_hrdata_s1_fp           (hrdata),
    .u_m3soc_hready_resp_s1_fp      (hready_resp),
    .u_m3soc_hresp_s1_fp            ({1'b0,hresp}),
    .u_m3soc_haddr_s1_fp            (haddr),
    .u_m3soc_hburst_s1_fp           (hburst),
    .u_m3soc_hsize_s1_fp            (hsize),
    .u_m3soc_htrans_s1_fp           (htrans),
    .u_m3soc_hwdata_s1_fp           (hwdata),
    .u_m3soc_hwrite_s1_fp           (hwrite),
`endif

    .u_m3soc_ic0_clk_in_a           (),
    .u_m3soc_ic0_clk_oe             (),
    .u_m3soc_ic0_data_in_a_i        (),
    .u_m3soc_ic0_data_oe_o          (),

    .u_m3soc_spi0_clk_in_i          (),
    .u_m3soc_spi0_cs_n_in_i         (),
    .u_m3soc_spi0_clk_oe_o          (),
    .u_m3soc_spi0_clk_out_o         (),
    .u_m3soc_spi0_cs_n_oe_o         (),
    .u_m3soc_spi0_cs_n_out_o        (),
    .u_m3soc_spi0_mosi_in_i         (),
    .u_m3soc_spi0_mosi_oe_o         (),
    .u_m3soc_spi0_mosi_out_o        (),
    .u_m3soc_spi0_miso_in_i         (),
    .u_m3soc_spi0_miso_oe_o         (),
    .u_m3soc_spi0_miso_out_o        (),
    .u_m3soc_spi0_hold_n_in_i       (),
    .u_m3soc_spi0_hold_n_oe_o       (),
    .u_m3soc_spi0_hold_n_out_o      (),
    .u_m3soc_spi0_wp_n_in_i         (),
    .u_m3soc_spi0_wp_n_oe_o         (),
    .u_m3soc_spi0_wp_n_out_o        (),

    .u_m3soc_uart0_cts_n_i          (),
    .u_m3soc_uart0_dcd_n_i          (),
    .u_m3soc_uart0_dsr_n_i          (),
    .u_m3soc_uart0_ri_n_i           (),
    .u_m3soc_uart0_dtr_n_o          (),
    .u_m3soc_uart0_out1_n_o         (),
    .u_m3soc_uart0_out2_n_o         (),
    .u_m3soc_uart0_rts_n_o          (),
    .u_m3soc_uart0_sin_i            (uart_rx),
    .u_m3soc_uart0_sout_o           (uart_tx),
    .u_m3soc_uart0_sir_in_i         (),
    .u_m3soc_uart0_sir_out_n_o      (),
    .u_m3soc_uart0_baudout_n_o      (),

    .u_m3soc_fp_intr                ()
);

endmodule
