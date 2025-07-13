// ============================================================
// File Name: rx_dpram_768x32_ahb.v
// IP core  : ethernet_mac_v2 
// Function : RX memory management
// ============================================================

module hme_ip_rx_dpram_768x32_ahb_v3(
        clkw,
        cew,
        aw,
        dw,

        clkr,
        cer,
        ar,
        qr
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
lzi2kjWjEj4WBNUkBH1NeiBYZjarPMwlxm/2JIdkiRTY8kam7jXg6mh0XTh0yKZA5JXPdOIAOPWFo8FOfIYcSCv7ef5da32kf35mDZjek+ZAGwUKMaDWo++AkaKLDQzpJQKnuxv9Ed39VNJ+UaN9g3+Ij+SiAHw5nm1dE7qmLew=
`pragma protect data_block
dWOLZntfdBFJYV8TaE6RXY9MjvfkUrULFUnE/aVnV2p4I27cZ0pZnon1TzM6gp9A9Mxyp4tPMCxor1kJM3mzKQEWqQVafRpCwCV1faYA9wg0yHS5y5cdGOsM5udG+Lre
0yCjE2QbgiQbLu2FhD3oFnRODQC4nDsz3N/7VFovEv8c3vfedgfMfIml/C0QvUIqPvC7ekspZ7mqFMz/qcGkTwgvbl2Pgp7ZqnXecKX7ySXMI7ahMKZHSu1DpRqMG9uq
EvB1Szada1reLPTPNqA7qBD2PACCs2AHZydcMMA6jpNKsvrVhOlMPwH6QSL6L+qitJsEHvSwBaqDC3hKz1SBv+PL94VC0E9lGgI8Q16GCBcal77aAW+0vdTIFl4ZsR58
LqLl9rWNToMSWqnSo9MWbf8oaYuq6oi8+++nglTbLEOZPKBCIyVr7wmDO2FuCJ7dh58gKIj/lQewc4is1/IJRNdXPFh0QerBObQ4WNrJGaj8OPpzYzkU7WJ0OI8Q6dSr
d22bn6c54c/AZV7iIZZOGWT8jZ88PJe/wMLUlViX3eMjNlyq3WcSsRDlCxdZzfQ5WHR1VpcfczaOfCReWMGcyu1MpJzo8Pa3thgy5ZwwLdQKnfCA2b11cXqUXtgJyZwX
vINQ2FVJ2WBcGe6SLYse1byDUNhVSdlgXBnuki2LHtW8g1DYVUnZYFwZ7pItix7VtN0O96EQLBiHJT+4nRqIgYpTuTldx0OcXf+VywaE46qGPL8motbkb6ptEeKmAWFD
vINQ2FVJ2WBcGe6SLYse1bZsoIz0/PfS6h+2Kt3H18a8g1DYVUnZYFwZ7pItix7VvINQ2FVJ2WBcGe6SLYse1byDUNhVSdlgXBnuki2LHtW/BspAcopZSLtKMEIYKu+Q
4HRqoICA29g7C1Dz+zd+T+8+UFTK39LOkcHYr5QyVWs6eEWV5QkVgijoaXOyU/pK+ZO5OcqLfYX5X+bDzYq8n8sd0+yzo/rOdTGFLFvHfzmA06Y8CkTD+tS2oQWxZD6R
qQSx/jsJ4QNWTZPjXDE3AMFyCdR3Nha8kOmSfNGxBH/Rk2lRY8vJJnzl8Q0tsJy0gYGYmj3qOhl9PhmECyhY4iDIs8g+C69i4cACQOfVIt1tXSjlac2pWLrV9h8bk67F
2ndhd4eNGlak50MObXQZJDDEH5ZbDVUORmegs25Y53eV6Qa6OzI8TkzubKZiWfmgprrLXZRc4qe1ZnE37+l+GYJSSJ7lqKKvWsH7ddXAkkcpJ/MzonD3FZ0bMfFcYrQn
EegFJkqQrWYesnVf7OLPy8+V2SLDMYXQXmGxzfgheBu+NKz1BZ2wLd3Aau1sdwOaDp7IEQ4C3GYA8ZQB+9FuE3NVv9wkrJVH8yN3FVw4NBbPQ/4sZBQU7MaNyljPGTkM
Lfk4SXeVMKYUgevL2z+sQpbS3THA7H5TbF1YcViorLa8g1DYVUnZYFwZ7pItix7VvINQ2FVJ2WBcGe6SLYse1byDUNhVSdlgXBnuki2LHtW2bKCM9Pz30uoftirdx9fG
jWTihOFdwwKcNayuIvRichIOHbo9Uf8fnc3WH/gJjQO8g1DYVUnZYFwZ7pItix7VeTkO7IHwQ8hzeOC1cgLwnbyDUNhVSdlgXBnuki2LHtW8g1DYVUnZYFwZ7pItix7V
vINQ2FVJ2WBcGe6SLYse1QJLdBbfc6ZSF69SSIgv4lIH2L9Og7iZz5ViDqVXAG4HcA+FuwIiyLupbRpdrtyFtMVNHoKwbp7EBLzPuCIpwYWx5K57i+e814HPzhon7fBW
Ra10gdg4PPh+Ne5Th4DPAVYkoU7VCIOUPVe6+s/bPkjZWDEnz5l7o38FEAHaQ+Z8wvFYwxEYpE1yxU1Niti4lsSsnsfOJ473mS4KOKQ5e5nxRVTAVzXBBv1T8xjV48p3
vwObdiKtoDagFpNNHKH3NidBMIGEge1iZu30IsDEDNrq0NoB3IAMBeDE8v1+bLBZv7PFv1PCcrr2g0kraQlJzltpjhdiLypG1sQnrCBxmDWohhplQl6xmz3fWhvJXR18
Iah8pXuJTaJeFVEQqwHEhXRokb/pgJupe4pM+ubsj7oK4RhcMO67uAVINApNozMj981N/RhQXwiagRXVYlBHmSnEe4OmOxw7d1Cu1DMgi3Zkxv83CXtmyVGUPAyDY85i
3JQrcqy5HgEqZ8o/p9W8Mken/Yfdb9CaucUiZbBDBvytCM1obKBdeLGUu9DyR1mF9H/To2N7SJbTORfIGxYHfryDUNhVSdlgXBnuki2LHtW8g1DYVUnZYFwZ7pItix7V
vINQ2FVJ2WBcGe6SLYse1bsc2u2zXXY2QSrOXsJF6ur5aILV+6AM3eYSfHqIYAWt3EE0yMsLfWX9Wakim8eWa7yDUNhVSdlgXBnuki2LHtW03Q73oRAsGIclP7idGoiB
vINQ2FVJ2WBcGe6SLYse1byDUNhVSdlgXBnuki2LHtW8g1DYVUnZYFwZ7pItix7VjD6C3ApFeMNyC+g6aZbtLrTrBC8oAg3jSRJ7qYEyGyy0cpbpdtq4cSuFjsQ5bMlC
mWOrbrP5npluJPjrwoYA0c4in037KrUcsjWoeIzYmmwXczpP6/SkWYbk1e7tLBLJjQXWsxVwdewvTt4IPrcwyIYfb/I0gpH43hnsI7QwCbChjBl3qFPVVOL2yaLEL4NU
jQz+SS/f07W9VTjGlumY55lDG/shjn46yIoadyuGN7RutPsU3vrxEu+xsTNB1ZKXjUxXSXTzLVnPywR7XmziBPY4/nFNd2G/fRIKyrirN+vjgFBoFaCrdqimAg27TRU+
phMaaOwMtpIQPo5pHrKyqv2i53Ow+42i4beQ0gPMEdLvLPQB/kyOX+eVcy/R3L9w7z5QVMrf0s6RwdivlDJVazp4RZXlCRWCKOhpc7JT+kpMi9/lCPrIfW0oMbgY2VYM
fGMx0DdLcazSG103U8pxdVYkoU7VCIOUPVe6+s/bPkjZWDEnz5l7o38FEAHaQ+Z8hdtXWqvs1P6CLaORTHCFEDDMctR0/HIgPRJVBb6iZ/FiQC4s9rlOwySvaEuUNlQ7
`pragma protect end_protected
endmodule

