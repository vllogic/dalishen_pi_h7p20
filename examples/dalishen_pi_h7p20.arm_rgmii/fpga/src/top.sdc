create_clock -period 16.6667 -name {usb334x_clk_60m} [get_ports {usb334x_clk_60m}]
create_clock -period 8 -name {i_rgmii_rxc} [get_ports {i_rgmii_rxc}]
create_clock -disable -period 40 -name {pll_v1_inst_pll_u0/CO0} [get_pins {pll_v1_inst_pll_u0/CO0}]
create_clock -disable -period 8 -name {pll_v1_inst_pll_u0/CO1} [get_pins {pll_v1_inst_pll_u0/CO1}]
create_clock -disable -period 10 -name {pll_v1_inst_pll_u0/CO2} [get_pins {pll_v1_inst_pll_u0/CO2}]

create_clock -period 8.000000 -name {auto_0_soc_system_v1_inst_u_m3soc_topbuffer_xy_net_clk} [get_pins {soc_system_v1_inst_u_m3soc_topbuffer/xy}] -comment {auto_created}
set_clock_groups -asynchronous -group {auto_0_soc_system_v1_inst_u_m3soc_topbuffer_xy_net_clk} -comment {auto_created}
