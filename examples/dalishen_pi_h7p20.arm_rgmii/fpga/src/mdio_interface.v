// ============================================================
//
// Company:
// Engineer:
//
// Create Date: 07/19/2024 15:19:55   
// Design Name:
// Module Name: mdio_interface
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
// ============================================================
module mdio_interface(

                input           i_mdc        ,					
                output          o_mdi        ,					
                input           i_mdo        ,					
                input           i_mdo_t      ,				
	
				output          o_mdc        ,
				inout           io_mdio      
);

assign o_mdc   = i_mdc                       ;
assign o_mdi   = ~i_mdo_t ? io_mdio : i_mdo  ;
assign io_mdio = i_mdo_t ? i_mdo : 1'bz      ;

endmodule
