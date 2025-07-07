create_clock -period 33.3333 -name {ifclk_i} [get_ports {ifclk_i}]
create_clock -period 16.6667 -name {t_usb_clk_i} [get_ports {t_usb_clk_i}]

create_clock -period 16.666700 -name {auto_0_usb334x_clk_60M_clk} [get_ports {usb334x_clk_60M}] -comment {auto_created}
set_clock_groups -asynchronous -group auto_0_usb334x_clk_60M_clk -comment {auto_created}
create_clock -period 16.666700 -name {auto_1_usb334x_clk_60M_clk} [get_ports {usb334x_clk_60M}] -comment {auto_created}
set_clock_groups -asynchronous -group auto_1_usb334x_clk_60M_clk -comment {auto_created}
