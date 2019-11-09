  
module top (
  input           CLOCK_50,
  input  [3:0]    KEY_N,
  input  [9:0] 	SW,
  output [9:0]    LEDR,
 
  output [14:0]   HPS_DDR3_ADDR,
  output [2:0]    HPS_DDR3_BA,
  output          HPS_DDR3_CAS_N,
  output          HPS_DDR3_CKE,
  output          HPS_DDR3_CK_N,
  output          HPS_DDR3_CK_P,
  output          HPS_DDR3_CS_N,
  output [3:0]    HPS_DDR3_DM,
  inout  [31:0]   HPS_DDR3_DQ,
  inout  [3:0]    HPS_DDR3_DQS_N,
  inout  [3:0]    HPS_DDR3_DQS_P,
  output          HPS_DDR3_ODT,
  output          HPS_DDR3_RAS_N,
  output          HPS_DDR3_RESET_N,
  input           HPS_DDR3_RZQ,
  output          HPS_DDR3_WE_N,
  
  output          HPS_ENET_GTX_CLK,
  // inout           HPS_ENET_INT_N, //What is this one?
  output          HPS_ENET_MDC,
  inout           HPS_ENET_MDIO,
  input           HPS_ENET_RX_CLK,
  input  [3:0]    HPS_ENET_RX_DATA,
  input           HPS_ENET_RX_DV,
  output [3:0]    HPS_ENET_TX_DATA,
  output          HPS_ENET_TX_EN,
  
  //inout           HPS_KEY_N,
  
  output          HPS_SD_CLK,
  inout           HPS_SD_CMD,
  inout  [3:0]    HPS_SD_DATA,
  input           HPS_UART_RX,
  output          HPS_UART_TX,
  
  // inout           HPS_CONV_USB_N,
  // inout           HPS_CONV_USB_N,
  // input           HPS_USB_CLKOUT,
  // inout  [7:0]    HPS_USB_DATA,
  // input           HPS_USB_DIR,
  // input           HPS_USB_NXT,
  // output          HPS_USB_STP
  
  output wire        VGA_CLK,                         //             vga.CLK
  output wire        VGA_HS,                          //                .HS
  output wire        VGA_VS,                          //                .VS
  output wire        VGA_BLANK_N,                     //                .BLANK
  output wire        VGA_SYNC_N,                      //                .SYNC
  output wire [7:0]  VGA_R,                           //                .R
  output wire [7:0]  VGA_G,                           //                .G
  output wire [7:0]  VGA_B,                           //                .B
  
  output wire        DRAM_CLK,                  //       sdram_clk.clk
  output wire [12:0] DRAM_ADDR,                 //      sdram_ctrl.addr
  output wire [1:0]  DRAM_BA,                   //                .ba
  output wire        DRAM_CAS_N,                //                .cas_n
  output wire        DRAM_CKE,                  //                .cke
  output wire        DRAM_CS_N,                 //                .cs_n
  inout  wire [15:0] DRAM_DQ,                   //                .dq
  output wire        DRAM_UDQM,                 //                .dqm
  output wire        DRAM_LDQM, 
  output wire        DRAM_RAS_N,                //                .ras_n
  output wire        DRAM_WE_N,                 //                .we_n
  
  input  wire        AUD_ADCDAT,                    //        audio.ADCDAT
  input  wire        AUD_ADCLRCK,                   //             .ADCLRCK
  input  wire        AUD_BCLK,                      //             .BCLK
  output wire        AUD_DACDAT,                    //             .DACDAT
  input  wire        AUD_DACLRCK,                   //             .DACLRCK
  output wire        AUD_XCK,                   	 //    audio_clk.clk
  inout  wire        FPGA_I2C_SDAT,                 // audio_config.SDAT
  output wire        FPGA_I2C_SCLK,                  //             .SCLK

  inout wire [35:0]  GPIO_1,
  inout wire [35:0]  GPIO_0
);

wire reset_n;
wire sys_clk;
wire        hps_serial_acknowledge;
wire        hps_serial_irq;
wire [15:0] hps_serial_address;
wire        hps_serial_bus_enable;
wire [1:0]  hps_serial_byte_enable;
wire        hps_serial_rw;
wire [15:0] hps_serial_write_data; 
wire [15:0] hps_serial_read_data;
wire [9:0]  hps_leds_connector;
assign reset_n = KEY_N[0];
assign hps_serial_read_data[15:8] = 8'b0;

soc_system arm0 (
    .clk_clk                         (CLOCK_50),             //             clk.clk
    .reset_reset_n                   (reset_n),              //           reset.reset_n
	 .sys_clk_clk                     (sys_clk),
    .memory_mem_a                    (HPS_DDR3_ADDR),        //          memory.mem_a
    .memory_mem_ba                   (HPS_DDR3_BA),          //                .mem_ba
    .memory_mem_ck                   (HPS_DDR3_CK_P),        //                .mem_ck
    .memory_mem_ck_n                 (HPS_DDR3_CK_N),        //                .mem_ck_n
    .memory_mem_cke                  (HPS_DDR3_CKE),         //                .mem_cke
    .memory_mem_cs_n                 (HPS_DDR3_CS_N),        //                .mem_cs_n
    .memory_mem_ras_n                (HPS_DDR3_RAS_N),       //                .mem_ras_n
    .memory_mem_cas_n                (HPS_DDR3_CAS_N),       //                .mem_cas_n
    .memory_mem_we_n                 (HPS_DDR3_WE_N),        //                .mem_we_n
    .memory_mem_reset_n              (HPS_DDR3_RESET_N),     //                .mem_reset_n
    .memory_mem_dq                   (HPS_DDR3_DQ),          //                .mem_dq
    .memory_mem_dqs                  (HPS_DDR3_DQS_P),       //                .mem_dqs
    .memory_mem_dqs_n                (HPS_DDR3_DQS_N),       //                .mem_dqs_n
    .memory_mem_odt                  (HPS_DDR3_ODT),         //                .mem_odt
    .memory_mem_dm                   (HPS_DDR3_DM),          //                .mem_dm
    .memory_oct_rzqin                (HPS_DDR3_RZQ),         //                .oct_rzqin

    .switches_export                 (SW),                   //        switches.export
    .leds_export                     (hps_leds_connector),//(LEDR),                 //            leds.export
	 .keys_export							 (KEY_N),
    
	 .hps_io_hps_io_emac1_inst_TX_CLK (HPS_ENET_GTX_CLK),     //          hps_io.hps_io_emac1_inst_TX_CLK
    .hps_io_hps_io_emac1_inst_TXD0   (HPS_ENET_TX_DATA[0]),  //                .hps_io_emac1_inst_TXD0
    .hps_io_hps_io_emac1_inst_TXD1   (HPS_ENET_TX_DATA[1]),  //                .hps_io_emac1_inst_TXD1
    .hps_io_hps_io_emac1_inst_TXD2   (HPS_ENET_TX_DATA[2]),  //                .hps_io_emac1_inst_TXD2
    .hps_io_hps_io_emac1_inst_TXD3   (HPS_ENET_TX_DATA[3]),  //                .hps_io_emac1_inst_TXD3
    .hps_io_hps_io_emac1_inst_RXD0   (HPS_ENET_RX_DATA[0]),  //                .hps_io_emac1_inst_RXD0
    .hps_io_hps_io_emac1_inst_MDIO   (HPS_ENET_MDIO),        //                .hps_io_emac1_inst_MDIO
    .hps_io_hps_io_emac1_inst_MDC    (HPS_ENET_MDC),         //                .hps_io_emac1_inst_MDC
    .hps_io_hps_io_emac1_inst_RX_CTL (HPS_ENET_RX_DV),       //                .hps_io_emac1_inst_RX_CTL
    .hps_io_hps_io_emac1_inst_TX_CTL (HPS_ENET_TX_EN),       //                .hps_io_emac1_inst_TX_CTL
    .hps_io_hps_io_emac1_inst_RX_CLK (HPS_ENET_RX_CLK),      //                .hps_io_emac1_inst_RX_CLK
    .hps_io_hps_io_emac1_inst_RXD1   (HPS_ENET_RX_DATA[1]),  //                .hps_io_emac1_inst_RXD1
    .hps_io_hps_io_emac1_inst_RXD2   (HPS_ENET_RX_DATA[2]),  //                .hps_io_emac1_inst_RXD2
    .hps_io_hps_io_emac1_inst_RXD3   (HPS_ENET_RX_DATA[3]),  //                .hps_io_emac1_inst_RXD3
    
	 .hps_io_hps_io_sdio_inst_CMD     (HPS_SD_CMD),    		 //                .hps_io_sdio_inst_CMD
    .hps_io_hps_io_sdio_inst_D0      (HPS_SD_DATA[0]),       //                .hps_io_sdio_inst_D0
    .hps_io_hps_io_sdio_inst_D1      (HPS_SD_DATA[1]),       //                .hps_io_sdio_inst_D1
    .hps_io_hps_io_sdio_inst_CLK     (HPS_SD_CLK),     		 //                .hps_io_sdio_inst_CLK
    .hps_io_hps_io_sdio_inst_D2      (HPS_SD_DATA[2]),       //                .hps_io_sdio_inst_D2
    .hps_io_hps_io_sdio_inst_D3      (HPS_SD_DATA[3]),       //                .hps_io_sdio_inst_D3
    
	 // .hps_io_hps_io_usb1_inst_D0      (HPS_USB_DATA[0]),      //                .hps_io_usb1_inst_D0
    // .hps_io_hps_io_usb1_inst_D1      (HPS_USB_DATA[1]),      //                .hps_io_usb1_inst_D1
    // .hps_io_hps_io_usb1_inst_D2      (HPS_USB_DATA[2]),      //                .hps_io_usb1_inst_D2
    // .hps_io_hps_io_usb1_inst_D3      (HPS_USB_DATA[3]),      //                .hps_io_usb1_inst_D3
    // .hps_io_hps_io_usb1_inst_D4      (HPS_USB_DATA[4]),      //                .hps_io_usb1_inst_D4
    // .hps_io_hps_io_usb1_inst_D5      (HPS_USB_DATA[5]),      //                .hps_io_usb1_inst_D5
    // .hps_io_hps_io_usb1_inst_D6      (HPS_USB_DATA[6]),      //                .hps_io_usb1_inst_D6
    // .hps_io_hps_io_usb1_inst_D7      (HPS_USB_DATA[7]),      //                .hps_io_usb1_inst_D7
    // .hps_io_hps_io_usb1_inst_CLK     (HPS_USB_CLKOUT),     	 //                .hps_io_usb1_inst_CLK
    // .hps_io_hps_io_usb1_inst_STP     (HPS_USB_STP),     		 //                .hps_io_usb1_inst_STP
    // .hps_io_hps_io_usb1_inst_DIR     (HPS_USB_DIR),     		 //                .hps_io_usb1_inst_DIR
    // .hps_io_hps_io_usb1_inst_NXT     (HPS_USB_NXT),          //                .hps_io_usb1_inst_NXT
	 
    .hps_io_hps_io_uart0_inst_RX     (HPS_UART_RX),          	 //                .hps_io_uart0_inst_RX
    .hps_io_hps_io_uart0_inst_TX     (HPS_UART_TX),             //                .hps_io_uart0_inst_TX
	 
	 .vga_CLK 						(VGA_CLK),                         //             ,vga.CLK
	 .vga_HS							(VGA_HS),                          //                .HS
	 .vga_VS							(VGA_VS),                          //                .VS
	 .vga_BLANK						(VGA_BLANK_N),                     //                .BLANK
	 .vga_SYNC						(VGA_SYNC_N),                      //                .SYNC
	 .vga_R 							(VGA_R),                           //                .R
	 .vga_G 							(VGA_G),                           //                .G
	 .vga_B 							(VGA_B),                           //                .B

    .sdram_clk_1_clk           (DRAM_CLK),                  //       sdram_clk.clk
    .sdram_ctrl_addr		     (DRAM_ADDR),                 //      sdram_ctrl.addr
    .sdram_ctrl_ba			  (DRAM_BA),                   //                .ba
    .sdram_ctrl_cas_n	     (DRAM_CAS_N),                //                .cas_n
    .sdram_ctrl_cke		     (DRAM_CKE),                  //                .cke
    .sdram_ctrl_cs_n         (DRAM_CS_N),                 //                .cs_n
    .sdram_ctrl_dq           (DRAM_DQ),                   //                .dq
    .sdram_ctrl_dqm 	        ({DRAM_UDQM,DRAM_LDQM}),     //                .dqm
    .sdram_ctrl_ras_n        (DRAM_RAS_N),                //                .ras_n
    .sdram_ctrl_we_n         (DRAM_WE_N),                 //                .we_n

	 .audio_ADCDAT           (AUD_ADCDAT),                    //        audio.ADCDAT
    .audio_ADCLRCK          (AUD_ADCLRCK),                   //             .ADCLRCK
    .audio_BCLK             (AUD_BCLK),                      //             .BCLK
    .audio_DACDAT           (AUD_DACDAT),                    //             .DACDAT
    .audio_DACLRCK          (AUD_DACLRCK),                   //             .DACLRCK
    .audio_clk_clk          (AUD_XCK),                       //    audio_clk.clk
    .audio_config_SDAT      (FPGA_I2C_SDAT),                 // audio_config.SDAT
    .audio_config_SCLK      (FPGA_I2C_SCLK),                 //             .SCLK
	 
    .io_acknowledge         (hps_serial_acknowledge),                  //           io.acknowledge
    .io_irq                 (hps_serial_irq),                          //             .irq
    .io_address             (hps_serial_address),                      //             .address
    .io_bus_enable          (hps_serial_bus_enable),                   //             .bus_enable
    .io_byte_enable         (hps_serial_byte_enable),                  //             .byte_enable
    .io_rw                  (hps_serial_rw),                           //             .rw
    .io_write_data          (hps_serial_write_data),                   //             .write_data
    .io_read_data           (hps_serial_read_data)                     //             .read_data
);

// automaticly generates ack for serial io
dff_async_reset ack_delay_dff(
  .data     (hps_serial_bus_enable),
  .clk      (sys_clk),
  .reset    (reset_n), 
  .q        (hps_serial_acknowledge)
);

reg [31:0] req_count;
reg [31:0] ack_count;
always @(posedge hps_serial_bus_enable) begin
	req_count = req_count+1;
end

always @(posedge hps_serial_acknowledge) begin
	ack_count = ack_count+1;
end

reg [15:0] addr_reg;
reg [9:0] leds_reg;
assign LEDR = leds_reg;
always @ (posedge hps_serial_bus_enable) begin
		addr_reg <= hps_serial_address[15:0];
end

always @ (posedge sys_clk) begin
	if (SW[0] == 1'b1)
		leds_reg[9:0] = addr_reg[9:0];
	else if (SW[1] == 1'b1) begin
		leds_reg[5:0] = addr_reg[15:10];
		leds_reg[9:6] = 3'b0;
	end
	else if (SW[2] == 1'b1) begin
		leds_reg = req_count[9:0];
	end
	else if (SW[3] == 1'b1) begin
		leds_reg = ack_count[9:0];
	end

	else if (SW[4] == 1'b1) begin
		leds_reg[0] = hps_serial_bus_enable;
		leds_reg[1] = hps_serial_acknowledge;
		leds_reg[9:2] = 8'b0;
	end
	else 
		leds_reg = hps_leds_connector;
end

// io to serial decoders 
OnChipM68xxIO  Serial_decoder_chips(
	.Reset_L(reset_n),
	.Clock_50Mhz(sys_clk),

	.WE_L(hps_serial_rw),
	.IOSelect_H(hps_serial_bus_enable),
	.ByteSelect_L(~hps_serial_byte_enable[0]),
	.Address(hps_serial_address[15:0]),
	.DataIn(hps_serial_write_data[7:0]),
	.DataOut(hps_serial_read_data[7:0]),
	.ACIA_IRQ(hps_serial_irq),	
	
	.RS232_RxData(GPIO_1[24]),
	.GPS_RxData(GPIO_1[28]),
	.BlueTooth_RxData(GPIO_1[32]),
	.TouchScreen_RxData(GPIO_0[11]),
	.Biometric_RxData(GPIO_0[16]),
	
	.RS232_TxData(GPIO_1[22]),
	.GPS_TxData(GPIO_1[26]),
	.BlueTooth_TxData(GPIO_1[34]),
	.TouchScreen_TxData(GPIO_0[10])	
);
 
endmodule
