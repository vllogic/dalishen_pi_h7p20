// SPDX-License-Identifier: BSD-3-Clause
`timescale 1ns / 1ps

module speed_detect (
  input         clk_i,
  input   [1:0] dm_i,
  input   [1:0] dp_i,
  input         vbus_i,
  input         rx_active_i,
  output  [1:0] speed_o
);

localparam
  USB_SPEED_LS      = 2'b00,
  USB_SPEED_FS      = 2'b01,
  USB_SPEED_HS      = 2'b10,
  USB_SPEED_UNKNOWN = 2'b11;

// ===========================================================================
// 1. 硬件级消抖 (Debounce) 
// ===========================================================================
reg [1:0] dm_deb_r  = 2'b00;
reg [1:0] dp_deb_r  = 2'b00;
reg [5:0] deb_cnt_r = 6'd0;

wire ls_stable_w = (dm_i == dm_deb_r) && (dp_i == dp_deb_r);

always @(posedge clk_i) begin
  if (ls_stable_w) deb_cnt_r <= 6'd0;
  else begin
    deb_cnt_r <= deb_cnt_r + 6'd1;
    if (deb_cnt_r == 6'd60) begin // 1 us @ 60MHz
      dm_deb_r <= dm_i;
      dp_deb_r <= dp_i;
      deb_cnt_r <= 6'd0;
    end
  end
end

wire is_se0 = (dp_deb_r[0] == 1'b0) && (dm_deb_r[0] == 1'b0);
wire is_k   = (dp_deb_r[0] == 1'b0) && (dm_deb_r[0] == 1'b1); // 低速设备的空闲特征

// ===========================================================================
// 2. 指纹特征提取器 (包宽测量 & 低速电平计时)
// ===========================================================================
reg [11:0] rx_len_r    = 12'd0;
reg        rx_active_d = 1'b0;

always @(posedge clk_i) rx_active_d <= rx_active_i;
wire rx_falling = !rx_active_i && rx_active_d; // 捕捉数据包结束的瞬间

// 测量数据包的存活周期
always @(posedge clk_i) begin
  if (rx_active_i) begin
    if (rx_len_r != 12'hFFF) rx_len_r <= rx_len_r + 12'd1;
  end else begin
    rx_len_r <= 12'd0;
  end
end

// 测量纯净 K 状态的持续时间
reg [15:0] ls_k_cnt_r = 16'd0;
always @(posedge clk_i) begin
  // 必须是 K 状态且没有数据正在传输
  if (is_k && !rx_active_i) begin
    if (ls_k_cnt_r != 16'hFFFF) ls_k_cnt_r <= ls_k_cnt_r + 16'd1;
  end else begin
    ls_k_cnt_r <= 16'd0;
  end
end

// ===========================================================================
// 3. 终极三速指纹状态机
// ===========================================================================
localparam S_WAIT_LOCK = 1'b0;
localparam S_LOCKED    = 1'b1;

reg        state_r     = S_WAIT_LOCK;
reg [1:0]  speed_r     = USB_SPEED_FS; 
reg [19:0] reset_cnt_r = 20'd0;
reg [3:0]  frag_cnt_r  = 4'd0;

always @(posedge clk_i) begin
  if (!vbus_i) begin
    state_r     <= S_WAIT_LOCK;
    speed_r     <= USB_SPEED_FS;
    reset_cnt_r <= 20'd0;
    frag_cnt_r  <= 4'd0;
  end else begin

    // 【全局复位监测】：超过 2.5ms 的纯净 SE0，打断一切锁定状态，重新测速
    if (is_se0 && !rx_active_i) begin
      if (reset_cnt_r != 20'hFFFFF) reset_cnt_r <= reset_cnt_r + 20'd1;
      if (reset_cnt_r > 20'd150_000) begin
        state_r    <= S_WAIT_LOCK;
        speed_r    <= USB_SPEED_FS;
        frag_cnt_r <= 4'd0;
      end
    end else begin
      reset_cnt_r <= 20'd0;
    end

    // 【智能指纹测速】
    if (state_r == S_WAIT_LOCK) begin
      
      // 路线 A：低速电平指纹 (LS)
      // 如果总线连续 500us (30,000个周期) 处于 K 状态，无视其他，绝对是低速设备！
      if (ls_k_cnt_r > 16'd30_000) begin
        state_r <= S_LOCKED;
        speed_r <= USB_SPEED_LS;
      end
      
      // 路线 B：全速/高速包宽指纹 (FS / HS)
      else if (rx_falling) begin
        if (rx_len_r > 12'd70) begin
          // 长于 1.16us 的稳健合法包 -> 全速
          state_r <= S_LOCKED;
          speed_r <= USB_SPEED_FS;
        end else if (rx_len_r > 12'd0) begin
          // 极短碎片包 -> 高速流量爆破
          if (frag_cnt_r == 4'd2) begin
            // 连抓 3 个碎片，秒切高速
            state_r <= S_LOCKED;
            speed_r <= USB_SPEED_HS;
          end else begin
            frag_cnt_r <= frag_cnt_r + 4'd1;
          end
        end
      end
      
    end
  end
end

// 未锁定时向外输出 UNKNOWN，联动 usb_capture 里的防火墙，拦截所有碎片垃圾！
assign speed_o = (state_r == S_WAIT_LOCK) ? USB_SPEED_UNKNOWN : speed_r;

endmodule