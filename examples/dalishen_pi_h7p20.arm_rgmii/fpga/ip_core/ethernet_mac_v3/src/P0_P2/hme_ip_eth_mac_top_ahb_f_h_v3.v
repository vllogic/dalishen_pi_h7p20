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

module hme_ip_eth_mac_top_ahb_f_h_v3 (

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
AqwR/xAL/L8Qqtcx7PA79Z60N1mhqGv3tPQig4o8qw/uUExOjpPITEVDpZTsNltY1enbu+fZSFkNy5AoXGWPsIm0lQ7EGp4KGROw9nMs1uuxFSlH+Divqbab3raLZjnHpWsvZKKdtPWZhhXXKKP2pG/WLnsV98URwKn+2Qw4wI8=
`pragma protect data_block
tAmSOs0JaVk2yijU+u2OhHn964rGRxQs/QtN1lOB6t55/euKxkcULP0LTdZTgereef3risZHFCz9C03WU4Hq3gj/xzui5DBOuPcDhpdVnMkSftlwSQebd7WZ2WRLHpd+
ef3risZHFCz9C03WU4Hq3nn964rGRxQs/QtN1lOB6t55/euKxkcULP0LTdZTgereQSGOqmnolBRtLBH6o2NfO+MyPVKLZMbhoLsYScypMVVhXwk8ni/FFcl+MJmPpCP/
8ApX4ratbVHeSiyLwh26K216gxL/cKfcUKkfFiHuzBc4gYWjp3hpJp8EqkCtuF/m2v1XBVjzNXEXfDxkSJqSKlkgIzo7T8ZtoMOqfc3nOuAiu7xCDsQUF7BITMwx2Smg
XP/zTSmTjhjfK1QiMb/PPTf+nDXRhI2JGnqeeCxTuTsvgUaoC6gazsaQgwAaN6DGN/6cNdGEjYkaep54LFO5Ow2uD0sw0vQ5QVznQlBJLxPhCQVOYM4dA7gLW81qH+uD
+XhtRdCys03jXKVVmdVxhZLjqdrw+oHUZsA60uyU32jhdk8xJbLbglkSA7fSS1pXSTaaMR64tdHBNHBdOv70O7R0QXCaQ84bysFN/Wb3nLUUNbDtE+aTunt2xCHByEJ/
Xv7btzhFFW25qXI92H5SJ5YKAPMQkdqlSf/+4JPihO3hdk8xJbLbglkSA7fSS1pXKyJ7C0ALB664aZxUs5aG8bR0QXCaQ84bysFN/Wb3nLVjlksXKSVnUZQDDi3WzNKq
y42ueVVsOpmIDD4NWE2Xpgc5nRaqSTdoEjcUVG3rilDTDmEk5PLceXtnZyXDdJ7fsZsAFcsQYK5USfg0nAY9myAeBbguiFhi0oiWyRaCl+GFUZWphTuVJJeaXe1cZ/x3
tHK2wjoDlFRJZpZ63fDHtj11gtsxt0vyVYKRCOxlTnKEB4e/2Hvenf1EEpPY3TcFZIllSIBRlq02CkYCEGfOmGeoFaCvh17nC696IQo48hAt/Jxo9kHjKSDf0iDJ20x+
KpHcB7WVaQYlMg+kXry9Fe6GvAG38Xo3zSAG5C4VqGFS1Lbk+1YxqpWpcYT05b9CKdLCSVFUB5Oh/jmbI7krW3F28C9/IQjKOB+I82UJ2XbhdTv49Q83y7sI7Qpv3YbP
4ikebEJyW3RMv7kIgj1EgZPR290fBIYl5wm1Mwqk/GgY65LUMow0JK+JIgm8AsKQQix6qnrXcjl0tPB1TDTxb571cubWDilehf7HQpoCejAKKDDlHqWQ7fAlvfSesIMO
qNZ+KqTjam8mhQPo38q5bbdy35zZDMb+KQlYv0clJrAucK0qy/GRt+hLqsYnXwbbeS8pU8+P4Do7aOcfrIQDk3XfuS7J7yvaA43Krf0+iXJw9nBoceMUPZXNpxyKtbK9
rOeOac+CwZpUPgymu7lDgwQSv4XMkNCvRJvsT/fnII4IdZKh3gQeAoaR+NEilCuiSaPUJycNlP3yUGHhyRDPi3J6z4GAPd9Jj6mnhrbEfOgQxXlLFCMSvvYBTutQ9jEo
murLBY4T7839li2d+yImXxQZQv5i/P8PN8pYIbkvIPLEnBHgKg7SSejTLUxR4kFLwZfO5XPpIJv74KN/dhNBzHW59WD2lmAvAgSQ6O0af8YOPKgeMGHeJbxd72qkMnRz
vdURq7J1aTYJV+7wIwytMiLlft3XF6/pzDFHgQUjC/FS6hArZqDaqWgJu/33Gwlhgy7iSGcnBz7j7iacphp+ZKsrzYv+BFWzUhn/xYiUNzmSHnR9sYM8mwgoJQqy7W7h
8MCitsEVnF3ySM5sqpGh/nD2cGhx4xQ9lc2nHIq1sr0HwKsNXLOmYYRIycdzJyQN2LJS0feVwfzohQq+e8/dcPHEQLenu187oVIM1nuxgLzMB04Bczr3+eo6HJIsiEww
HUGrrbqEChJIkqJunz1J2zY+dSb+SYn623M6H+qWW7O84mqk7Tpeyj8ycyyc4OytgkPBKXUPqVSXsUW7qM3YJ12lJEV6e8vWXfQnwLyoasBZhbpwDcBYOaER7FAaj31E
zUnFQ7JeSy4dBnVe+/iRMl1dbGIVb/OuC1iT42r5WuF5/euKxkcULP0LTdZTgereef3risZHFCz9C03WU4Hq3nn964rGRxQs/QtN1lOB6t4xTC22FB1ekvvT4w2OGkOV
bBG0WSrscLvuk66Bjskj17R9sWo9I2eOd6gtcnl/mc9dJ/b5TMi2aaTIDZMaPBqxErCC16cjMXVi5+K54iLSA3n964rGRxQs/QtN1lOB6t55/euKxkcULP0LTdZTgere
ef3risZHFCz9C03WU4Hq3ikM4kRA5HYFsfQFSQN+HVtv0/EN9LpSKy5patFENX/kRYo1iPemgvmaw923vgZ5MuiiMmr739xLuC/PrLabOhsK0OFWfHnj0mRRW+G5kxjY
s2fIgAsXti/1UeO1l8kn4m9PWtkmCjz7J1oW1//FAMho1RWjx7SAKXb32uOW9OvJufr4of3EmTm7GRQRBmxsIquefK/2dI3VsjTnevj3CXlhmt/zDGUCoIK8+O6E1BRD
bw0w4RJcgElz6py1eyF4jdIdI30Q9Uh6dWZA97hC+rsv8rAN9G6WS+YnrBCXBsO/d00rn9s6HsIoCUo6wWQspeoin88PufaDRUPeCHEdtn9FijWI96aC+ZrD3be+Bnky
jAC9RCyo0Xq5yS/dUoBYQL45tYdRKHdNPowyvP06LUrhSgNoOohkeCuPR4nz+61pZGnO8CWY1QN+hbsqjE/aslC8+ePn+RV5gNpKqgYdjZBFBuzXsPB2B55qScFueXGo
bFQGGh6xJIJZLkTYvmVyn2asB2CzN8ZpNMoOsWzGMMwHN1DAPWwQx/knbdvefr7ZaNUVo8e0gCl299rjlvTryafaCwHr4DguvLNZEv4TnbQ9r38b32Bm4wFQU/sXYSE/
lCZuI0HxbSMsJ6oPzeG1YGoQdlr8m4EkcPA78CL72hVXZ+cxvnPqR6Dvp7O7XLCoVM3crCho6NuqGugRf4ZEd0i4Dz0Bl+Wwkhdde8G60cr2nyvwVCrc054gfx0uTMxL
fOwbpaXDJdRkMumfQd6hPcKKvB9Dpo+DEZ8paCqLcEeuA0GuL/GWmd0AmTycqsnNOV5vB3qjisapQadKs4zlzKTjocBdQoHJiPdB74/gUYY7AJMSfmeumpj+93x6Txyi
WmdSw+7upkaeoH85RpH88L/Z0FiaXUD+bgGARdk+w4IK5x/bzgbyCacT9Mr1PUZ3davzY8eApT8pFMQgFDqN8+Cual2kYXZKBXoQnNfbaSyCC6oBNdN5F9Y+SLboRcOg
5HS/am0/o2JEpUeAVa6fCHL/liTyUgxJ8i0C0ji487Pjqpu96YPvVH5kUZAzF3raRYo1iPemgvmaw923vgZ5MitkaoD5sBeTtbIn5EuLOVfBx9O8WWIRb6RntFmZNMLi
KrcDUNgPA8PESuEKRa+ZLSiaghgfGb3OfkDzlRDWGtSYYZKSFr6xlVsOfq1CwlcntAIH1IFGCrl/ZCu0Et5k+a4zqlcGUlur9ZaYAEeV5VRy5sEpRXeIT7vPDP1UNSgM
LCHAj0YFoWj1xnthMbympRGD/85PnUVsUjpxAS5QpGMuRx1q1HDsEEAGO22Wf756ULz54+f5FXmA2kqqBh2NkNtW2pbICKcFhOf9zdazoGnlPjmA4drjjBAmmbJjzIE8
W2OCGAs0K2l47QVG4QnnJdpX9Qyji2r+xtj5MqxXDd8+1gj6cYPPhk9inzDndrmhtUikFnCnnjKlB3B7yGsltfsRBPRplMpxMs0QCXLJEJbAX/DHvwRv2B4aFzz3bzI0
esBRwm+UZqo2GwgYZlMJdyy+fPqcv07DJUbqqKLgwjmjGTZpK50QwKrdz4cWL4oOKJqCGB8Zvc5+QPOVENYa1GDVcYWXoX8RJse9tYhYB9L17CHJzzIMv2mD/Py7BVDP
LgStW+YyLpKtN3RPf+DxC3n964rGRxQs/QtN1lOB6t55/euKxkcULP0LTdZTgereef3risZHFCz9C03WU4Hq3tqv1CEzkh7kJRlL7tqV0qWMGrLHph1sG9JBkB1VvyZ+
QfRQ+Z5W4+QMQck9Bog5Tnn964rGRxQs/QtN1lOB6t55/euKxkcULP0LTdZTgereef3risZHFCz9C03WU4Hq3tV1Dh1PwQDbk1Lwhdt6KgKE42caZPnKIwW0ttbWbGCv
tdSIjjgYnGA08SKL8xw+ER3W9ScoUhY83XxEseGklz3Tho14KsV/+aULK97rS6t8iEvaGzLo9yriqWv8/mWYzkj1c+9un+0qfcRahlfuT46fa6vaESjzWCbSCl7yrOhx
/qVYhMDnif7wXRIjRvfhXDRWEeHjDWKTNy/3qmkTiw2pEJ+8Vu4q04/LidfKjKufF3YDBj1yeRCt+RcjqkMk3vJzVxwC+8iJG6fCK5cYUN/YQ6zAlVlm6wqlDVlCSu6s
ff+jJ5qZBXGKhgKFMxJ2O7vg6tfpzkmAZ6bkWgECSz5EUTEMRttrE/SfVaJk1mNQY9k8zpvqf64pkFEOpwGGEFnjGgwFrvjSuaU+dB10TnOERtOfOLv2Xkr95D81MMS6
1F6RPfC2ukcq1JbF3JZJ9zHNheeRiPuP/zKo7nYj2Xa8mk53HcwWPXSYpyCWGoRJSI8zVnf6uzIWZBNfKrCCfL9j4qiAo3PJJRPoapupbwoNjCwWKS8BZlfh0cj0AEpj
B2dxvSf/4PU4tjYbR9yLm3l5V2mgrJT+QJJzXX6Hc8wrcOUXMh7uWLeTeG1HkCjP6Esvn1ClKzJZCkCp7eZbpO4RfXqpbpIpx0q9h+7Vq7hWOW9pFImEXCg1lv5UJi+L
BJ+x0Hk0QiKYFlB/o1zKcn0eG2lfO+gmp9v94vytBiTk1/67VmlFVzenU6HvCuxW/59DaLDPH4n+Jncpqya2wK12MgqaWe2buoqdFuuQadMcMtaNRaVB2Xh4IxUcKPaq
seCpXZIFl+ZgmZRC4LOSHK/brVX30TAJ0joNRsATZdPYJB6kU3/1xYh5RkAef6zI8369zUQ8Ek+snOsueZ7w0UQlX8g5ZZIsJ0cNVtxXSjDoPb2nTZM/SHbP972DA6Xz
zOVDb1mza/GRxS5o48CjQ+HPH10UgHFqw7L+BaSa2E4qmKOn+dnWlXu+fIiKAU5wePBdXcGL4uIIivDrUeoNFIn9cBoz25LhQfkt53b8UbuscdDsgvvkHfU8/hEoB4sG
87Tf60sUmaJcDIyY/3QAbAdf/4sLchr5/NoKmiolaWWn3ipHhzay2Al5JetZB+l0PcyCV82fJozdtMelUToOZ070HS8N8a6+TN3CCu5wUdRDz6kz1FonpAJQdkkgU4L/
e+w601wQV1btLhg55Gxttmg1XsCZczcOspNCGi1m6Y539zkcFjxxhCXG5omG4IUaDcCzf9Eatte21s+ELSQiUQjtAHP+PbG8I9kCzHXQZC118dwM9x83VXp0lE7Y2DMQ
fX2GQOE5VtQrBVZPrPYwpaUjCsrne95dDkXE5zLQNidDg2NUJJC9TyvFcff5GxzG7GgGsSVaY2nLgr6miU4hFFlj8a25h3QVeoxpoZcYj7xYMSL4upx+2eUX3fRs+1pY
Wgo3m+pyz56metQBz9A6Vt1jXwKbJuAupYVO5milz+dVMCu8yyhKiNwCdJZehJDxS28Av2qLrO23nHNwjVCAAAIR1Jjju+9FGikr/oCdK6xD7+q1SxCtO8vYaiYo+oxz
K8B89mqsj6aIPW9CoZIS5rZzK2y6FIzXepsTiNNa4MBCBEYQ8rLADFofP8w1riKT8NxwlvI2yb9kvOosMXTq6VsvHyp/UYooOxnWIAeEhOEWXACORGvV1UA6wzus2zS0
mnmFWzDGIiAI6rojCM2w/O8ceTag/+5bOxtBxuN9TubVc8q75E/KI/cN88fer/vE8wKazniYH4mROSN60bmSlhHeWOHJeMKzysIJ+PQu+h/Wkj74yf542K6Bb33hQXme
OGhSjmy4pfCWvWvSjwppfvWLcBUMbeMdiOkJL8JfPcJITJXGTqyytCJKw+7ULmWsbGUFlQJJXzRCcZn5Egs+If+0rYSxKT1c8+CB0nXJ7l4y1iO/QI7IvYBmBDLgySF0
K+NZZ5K5toqGyMiNUwiKFTUUYiNeXSSy+E3de/VCKUXZLH8wLBI3xK/zwXBhSHMNDQtEU0tkdAoNfxpZtFFcfaR3czOQEUp0v44+qCPMMiXtTPP5OActzA3SBY6ovVd6
5Aak6SpBJNnhw9/Rwzf3WFI+voQ76qtZf/G99D5QZjBb13n329hvrylFVIO9lHFbqqiqKebLg0uznrgEslOpXbL9emRUJRarR074uCtp2yiyYtW4m0R/S7bo0Tac8UcO
rDY9tmhtfZE2QGQeq6WsRJxYrExoUy/MKWEBw/ZSiyNf+LgW8mqaKbWr40Z5TfHOcubBKUV3iE+7zwz9VDUoDIeWqcsUDEG04mpTdZjSAlwZLTzKy/DmBJVPk13uCWpG
//tUJZlQ0eaC7o757hDqvGzNP2GUD9h7hJ44pnspK9mjVIx66eK+Y4VyWCuYQJ8yVGv/UUjO3PsKsZgBkY+hhMS24NE9P7vo9wEe+hFZWlJuc2LBDYDAbTBbZ3pt+DD4
hevitzLXvnFEKkNUWWHRKxMkMvK7JFDOVvhsxAyEHsKLERDhCI+dwu7kNMz/bXQi2bSxPXIeO0LV9e1B+Iy6MPd9oSdoGupANQhtVCifVfG/ZAE4Ux4Sy7kEzlB51ZCp
5ZrglyMQyKePZZw7VqrnJWfKHoGmxa8WV3sZyKmH5vpn8mgQacQgP7RFN9f7VgaOGl1oC6l9D7rgftdkkigjEUy/HFVexgySkaj2wRsUJcIdWh0SGMhskTc8wJLx8D6X
hbM7lGBvKeGBdImqv0WBezBZTzXmv1Teh4PJFLAW3riX/+HpzUv3ovziGEhr/CrqDDGKoxSiMxPOPW8ZxIBgBn1p0zN3BRaO7EL0Ui3pl+0gXMBUhEs/YiN0AXDGmTKA
/K7bivMLO4VVedPqK496w79kAThTHhLLuQTOUHnVkKlKmdh0env+14NvxJiCH58Z6rKztiZrFma2aKatPQ06Jlcuy5U7KEtJcNyNhwKcKWAmfzrmY1U2ib2tQHrgeUSe
1XPKu+RPyiP3DfPH3q/7xIxKJT0MJ8eLw4NCS8Y2rdgR3ljhyXjCs8rCCfj0Lvof1mSVhXERHHvvn7VNflbdujhoUo5suKXwlr1r0o8KaX5vzj/ykfzLYqzLqXuY859k
SEyVxk6ssrQiSsPu1C5lrDTWEPGAiTHqk86zc5Rr3EGzDgtD6MON0N+3vnnJgmzwPWxivlTPq7tx8NFM56cF4PbSJbArszwxphm63mT3XGZ5DJ2tZNB2RFx/ZuK/C+X/
buyVsSFOC1ynKDVkxdlsNtjCGPZbbseUmnaX63XMQSX/T0XHSRVPHa6LAOohIkPGTfvvnh7D8tMcmb6pspZsCp2YHcRVeHhEUQv+8jeR8JTEO0uGeHcY/wlDh4arLzVW
51w7Qyo7fajH7qeVyfuJ/XXk2wECZVHwCkzts6Jy+Rg+CPr6pAoni5u6lYe5kVsxr/YqLtO/Ar6KPy1fJ1m7FLzQC3NZqnxWb6AIaL/rT1N35y14P55tPpu0dPXR+t7a
yWwQJqGDZi/QE9frj4z5Tr6sYD16PQHlSLnE+6lheUyEs6hrU6oNgteu+mhb8hL3u57NlET4U7Y8uvbXU+crtpA0Uneix5NyxWj5Hnt0RA4thLg8jlceiyZvELLIhVty
CM3mr6FOWUFtF+raXb8l9i1KGdyGW9kvdB+uPZbJgfTvToy7k01yTBvcms/OHx6bmCXzlEmjjQ4VEpfLhWNOTj72pORtLHVKmGaNV2MmGK+zLKSPfeeVGObgBGhZ8B6U
pyiNLFCsSqZnIBiOc+dS8apgo6LLbtBn+y5Qwkw/+zvdKfJeFPzz00ZiZYrXTFrDt3UAooQbikJfrxdTwQgH1FLjxheXYwnFX6YqdyO3RnZx3Yj6pmM8ZQPdLq5CHCuQ
NI/ChzVmi1uI/uLGxCHsMnaPpBoj+zzqLcwifFSiqfzRwUIDM01coOLjjxIO6rTRgV2PbEh1rqfL/xJhdEwdeYJ8hCt2hRW8qUF18on6g9yWuDpE1EAWe2RjTAJEZxfj
SZ7aSttsBCS6yK5rfSjOW6anpD8nwVbqFXxuwhOdIZsag367ICc+w67rAiCww26MHOJIh/Oagb+826q8ve/UH7AAfq4R05YpdGmKIxec2Vz+8/cx03qm3FOCAYL89pkb
+UprU+n14uA7NxxU44E55/T9eJJgdvE/KOra4uBD63Y1mYrllA+dH4tych/Eut22wYeh4NMgWHvQnOH2IySKWHhEs5UXf4VvTQfiOtEody7eWdlaHWeV6IJ0pwna2hO7
eA7FiZj2E4vQc1zI3gtxtfDp4UEjWGDL94mn2ibaxf1b40RnzkfnloxdoxiVsDUCSn5jpclr4jfnEcLalcNWlJZx8WkxQS7FR8HAVmAN1nyid1W4434iOccIFVLhPeQ0
YKNZ+5P8ain+y4IlTYdtZO/j7XsADmHjlsFayrVDbgFWEUAcneN6rz4sUaYE/Jd4KkUhhncfdlRTcqi+GvN+aXTeRuEAuth7jMPU3Ya5q7lztpzifTtRK9qXBNDa2TZO
sWdkQ9BQcb5wRQxBjD6GFiUrTLdPeucBYK4qigOowbVec1gJFj5IYJa3kgRJl8u62yeSQ8CjKME0OWEVVU0f8Pg0vblDTFTucDlqMoIDqTRUa/9RSM7c+wqxmAGRj6GE
xLbg0T0/u+j3AR76EVlaUiupIG/ZAbSwMllp9ElBzNbN2+1nsAAATaoWzoF86L/qXDzQnIV3hoz2JqS23QoG/bJmditKQuZKyH1WEHGGyeCJ9s3s1GxMYopDP7dJs9e9
SBFJg9UHpCkMX/6Pjfeyl+09D1G2JV5bW4ge8GxRYgbrs6YAKt0SLyqfW/VCqZ/89XPnwOSpDStwb//BulpljuUqsvFlUajZWsutUh/LZ3fEHzkR++nvzfA6DuMIzlxU
PrSJ59ETzvcvDWow7dbXMrpk+JJiVFYTBtlJVoLPBeAVgYErZSTMsyse9uXdfVHzVTArvMsoSojcAnSWXoSQ8fgtTMH/emPbiOxndXBq6ZGx4KldkgWX5mCZlELgs5Ic
bYVohXg+sVR/To9ZLxO97FJ8Q2KUsNIiphtMVAeZBvs3rnzdEDS8tYZKF3whk8H8nEoBhSImzfBMIB976dVmRAfB+YwGi8cnRcpT8Xf2fe73fEfavPDlHnrHFfbJ6+MI
7wLIiaFYBD+OM6bHSND7hgeqzwmvuMmNh5K6wyQeoKdJqj3YZL7J6FbamLMUIa4CEH15GcjTF1VtlTHxoOlVsVED/DOdqMLQCO7nwBSaWcsEv3nvkeHy02IbXlAu7tb+
hMFPiJKDEcXDF0xGxIQh8EYRSMjyBzXye6YJ8wqwrVe6wBwpj2ms78wXLCirjyeZbd9S0qbIpZYzntxmj3h5Z/IzkxxVuj7ajnbuukPe1B/aBf/QHgv/dsN5sa1hl2l6
KpDqiNx3AD25hxaLjYcxP/iH2fVdJAQEbuXKAj6Ubb0JbJ9E7PKFyqKz/WLrqA1CT4A3CUr0cy1qvRUaiBwbibg3KtFcVxKxnRqL4YBOxgQw9qa3NTFv7rWSh7y3VKx7
dmpBPQDRkFkV++T7LiuSknkvM57pFxX7QfP9nX7qeEYPvP+cSxKCqmejk5FinNl/S+ETSYKlBn8RH89UqCl3jehLbVSSfx9oXB0+XYq4kUqjEmm+J/sEFhbBqM83SRh0
uvgEmIZkaCs6JzJrhLrGzdccVyaKZXPXcU8mc8z6vZLGosBaKyoiUggtsKX/bC444gNWyR2yXihFxHWLZ5x8l6OuiSnmDJf1pxRObcfYhN1AulFhN4g0OoNKGLO6ZYfq
zvIRP2/2HnyJkxQg1/WJD2nQ4LKbN8c/TASbP1yi2p58McL0rh0BaHgF83HjjKrzkDRSd6LHk3LFaPkee3REDnUpsRH5XHDmPiYuwJobJgdVMCu8yyhKiNwCdJZehJDx
0pzxUffs9PO+CliYRw1sETUM9+nweG/V7V39jSNE2LeDa9FIKvFBBBU71aXrczJpKKOgV/JPKRco1MgI56ShJsgmAD8ovRrxkhTPDhbY5Cr2IfaNrvk1SuzP4+UfvF8w
vOleqsc36nLq7m33znaBWGdycIfxUUeGjl+ol3ISB4bquEcT61dQCe9wpj25LZWVaLKGGAFy47u/P0HlvmLsSVTKH2dxIeGlLKZoRU+xLxKFG7pDSX0Y0NigtG5Kgyjn
CbGg3Nj6G+XgAEckdBEWcZ24OGCffY1MO4cIcs4er0wGzNgVlm2d6C7R7wYPA3T+ZURKTWtA8Ny8bGdfrTmpwmdqQSPD9dygHrKI12tJ1vVRk+jLBw7rbtfvOXKBNKOX
GuUEOJJxPHmEGOExYvmlyYr6g/VU7bOLXz76AqodKHgusbAQrU1Y58KTT58swv8E0eaumgdRUnjwYZ7x9jIwpN2kEjldma+Ozuax+InVoEdZqkrNWOv+Y4NzjLDlaHQ7
2HIq0rpaljRY5XRHM3eEE6ODsEK/yCjz645aHq1fOG0iXNQaUm4krh1CyRmx4ZDyOsmGrly/ojGkMFJtKWzp06w8VSZR2ZyQDAb45A86FzeUHVyOxBMbJOvVhi83Rv5R
`pragma protect end_protected

endmodule



