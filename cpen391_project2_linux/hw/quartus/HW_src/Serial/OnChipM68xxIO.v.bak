// Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, the Altera Quartus II License Agreement,
// the Altera MegaCore Function License Agreement, or other 
// applicable license agreement, including, without limitation, 
// that your use is for the sole purpose of programming logic 
// devices manufactured by Altera and sold by Altera or its 
// authorized distributors.  Please refer to the applicable 
// agreement for further details.

// PROGRAM		"Quartus II 64-Bit"
// VERSION		"Version 15.0.0 Build 145 04/22/2015 SJ Web Edition"
// CREATED		"Fri Mar  2 02:24:07 2018"

module OnChipM68xxIO(
	Reset_L,
	Clock_50Mhz,
	RS232_RxData,
	WE_L,
	GPS_RxData,
	BlueTooth_RxData,
	IOSelect_H,
	ByteSelect_L,
	TouchScreen_RxData,
	Biometric_RxData,
	Address,
	DataIn,
	RS232_TxData,
	ACIA_IRQ,
	GPS_TxData,
	BlueTooth_TxData,
	TouchScreen_TxData,
	DataOut
);


input wire	Reset_L;
input wire	Clock_50Mhz;
input wire	RS232_RxData;
input wire	WE_L;
input wire	GPS_RxData;
input wire	BlueTooth_RxData;
input wire	IOSelect_H;
input wire	ByteSelect_L;
input wire	TouchScreen_RxData;
input wire	Biometric_RxData;
input wire	[15:0] Address;
input wire	[7:0] DataIn;
output wire	RS232_TxData;
output wire	ACIA_IRQ;
output wire	GPS_TxData;
output wire	BlueTooth_TxData;
output wire	TouchScreen_TxData;
output wire	[7:0] DataOut;

wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_42;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_43;
wire	SYNTHESIZED_WIRE_44;
wire	SYNTHESIZED_WIRE_8;
wire	SYNTHESIZED_WIRE_10;
wire	SYNTHESIZED_WIRE_45;
wire	SYNTHESIZED_WIRE_46;
wire	SYNTHESIZED_WIRE_15;
wire	SYNTHESIZED_WIRE_17;
wire	SYNTHESIZED_WIRE_47;
wire	SYNTHESIZED_WIRE_20;
wire	SYNTHESIZED_WIRE_48;
wire	SYNTHESIZED_WIRE_24;
wire	SYNTHESIZED_WIRE_49;
wire	SYNTHESIZED_WIRE_50;
wire	SYNTHESIZED_WIRE_29;
wire	SYNTHESIZED_WIRE_30;
wire	SYNTHESIZED_WIRE_31;
wire	SYNTHESIZED_WIRE_32;
wire	SYNTHESIZED_WIRE_33;
wire	SYNTHESIZED_WIRE_34;
wire	SYNTHESIZED_WIRE_35;
wire	SYNTHESIZED_WIRE_37;
wire	SYNTHESIZED_WIRE_51;
wire	SYNTHESIZED_WIRE_52;

assign	SYNTHESIZED_WIRE_44 = 0;
assign	SYNTHESIZED_WIRE_46 = 0;
assign	SYNTHESIZED_WIRE_48 = 0;
assign	SYNTHESIZED_WIRE_50 = 0;
assign	SYNTHESIZED_WIRE_33 = 1;
assign	SYNTHESIZED_WIRE_52 = 0;




M68xxIODecoder	b2v_inst(
	.IOSelect_H(IOSelect_H),
	.ByteSelect_L(ByteSelect_L),
	.WE_L(WE_L),
	.Address(Address),
	.RS232_Port_Enable(SYNTHESIZED_WIRE_24),
	.RS232_Baud_Enable(SYNTHESIZED_WIRE_0),
	.GPS_Port_Enable(SYNTHESIZED_WIRE_37),
	.GPS_Baud_Enable(SYNTHESIZED_WIRE_29),
	.Bluetooth_Port_Enable(SYNTHESIZED_WIRE_3),
	.Bluetooth_Baud_Enable(SYNTHESIZED_WIRE_1),
	.TouchScreen_Port_Enable(SYNTHESIZED_WIRE_10),
	.TouchScreen_Baud_Enable(SYNTHESIZED_WIRE_8),
	.Biometric_Port_Enable(SYNTHESIZED_WIRE_17),
	.Biometric_Baud_Enable(SYNTHESIZED_WIRE_15));


ACIA_BaudRate_Generator	b2v_inst1(
	.Clk_50Mhz(Clock_50Mhz),
	.Enable_H(SYNTHESIZED_WIRE_0),
	.Clk(Clock_50Mhz),
	.Reset_L(Reset_L),
	.DataIn(DataIn[2:0]),
	.ACIA_Clock(SYNTHESIZED_WIRE_49));


ACIA_BaudRate_Generator	b2v_inst10(
	.Clk_50Mhz(Clock_50Mhz),
	.Enable_H(SYNTHESIZED_WIRE_1),
	.Clk(Clock_50Mhz),
	.Reset_L(Reset_L),
	.DataIn(DataIn[2:0]),
	.ACIA_Clock(SYNTHESIZED_WIRE_43));


ACIA_6850	b2v_inst11(
	.Clk(Clock_50Mhz),
	.Reset_H(SYNTHESIZED_WIRE_42),
	.CS_H(SYNTHESIZED_WIRE_3),
	.Write_L(WE_L),
	.RS(Address[1]),
	.RxClock(SYNTHESIZED_WIRE_43),
	.TxClock(SYNTHESIZED_WIRE_43),
	.RxData(BlueTooth_RxData),
	.DCD_L(SYNTHESIZED_WIRE_44),
	.CTS_L(SYNTHESIZED_WIRE_44),
	.DataIn(DataIn),
	.IRQ_L(SYNTHESIZED_WIRE_30),
	.TxData(BlueTooth_TxData),
	
	.DataOut(DataOut));



ACIA_BaudRate_Generator	b2v_inst13(
	.Clk_50Mhz(Clock_50Mhz),
	.Enable_H(SYNTHESIZED_WIRE_8),
	.Clk(Clock_50Mhz),
	.Reset_L(Reset_L),
	.DataIn(DataIn[2:0]),
	.ACIA_Clock(SYNTHESIZED_WIRE_45));


ACIA_6850	b2v_inst14(
	.Clk(Clock_50Mhz),
	.Reset_H(SYNTHESIZED_WIRE_42),
	.CS_H(SYNTHESIZED_WIRE_10),
	.Write_L(WE_L),
	.RS(Address[1]),
	.RxClock(SYNTHESIZED_WIRE_45),
	.TxClock(SYNTHESIZED_WIRE_45),
	.RxData(TouchScreen_RxData),
	.DCD_L(SYNTHESIZED_WIRE_46),
	.CTS_L(SYNTHESIZED_WIRE_46),
	.DataIn(DataIn),
	.IRQ_L(SYNTHESIZED_WIRE_34),
	.TxData(TouchScreen_TxData),
	
	.DataOut(DataOut));



ACIA_BaudRate_Generator	b2v_inst16(
	.Clk_50Mhz(Clock_50Mhz),
	.Enable_H(SYNTHESIZED_WIRE_15),
	.Clk(Clock_50Mhz),
	.Reset_L(Reset_L),
	.DataIn(DataIn[2:0]),
	.ACIA_Clock(SYNTHESIZED_WIRE_47));


ACIA_6850	b2v_inst17(
	.Clk(Clock_50Mhz),
	.Reset_H(SYNTHESIZED_WIRE_42),
	.CS_H(SYNTHESIZED_WIRE_17),
	.Write_L(WE_L),
	.RS(Address[1]),
	.RxClock(SYNTHESIZED_WIRE_47),
	.TxClock(SYNTHESIZED_WIRE_47),
	.RxData(SYNTHESIZED_WIRE_20),
	.DCD_L(SYNTHESIZED_WIRE_48),
	.CTS_L(SYNTHESIZED_WIRE_48),
	.DataIn(DataIn),
	.IRQ_L(SYNTHESIZED_WIRE_35),
	
	
	.DataOut(DataOut));




ACIA_6850	b2v_inst2(
	.Clk(Clock_50Mhz),
	.Reset_H(SYNTHESIZED_WIRE_42),
	.CS_H(SYNTHESIZED_WIRE_24),
	.Write_L(WE_L),
	.RS(Address[1]),
	.RxClock(SYNTHESIZED_WIRE_49),
	.TxClock(SYNTHESIZED_WIRE_49),
	.RxData(RS232_RxData),
	.DCD_L(SYNTHESIZED_WIRE_50),
	.CTS_L(SYNTHESIZED_WIRE_50),
	.DataIn(DataIn),
	.IRQ_L(SYNTHESIZED_WIRE_32),
	.TxData(RS232_TxData),
	
	.DataOut(DataOut));

assign	SYNTHESIZED_WIRE_20 =  ~Biometric_RxData;


ACIA_BaudRate_Generator	b2v_inst3(
	.Clk_50Mhz(Clock_50Mhz),
	.Enable_H(SYNTHESIZED_WIRE_29),
	.Clk(Clock_50Mhz),
	.Reset_L(Reset_L),
	.DataIn(DataIn[2:0]),
	.ACIA_Clock(SYNTHESIZED_WIRE_51));

assign	SYNTHESIZED_WIRE_42 =  ~Reset_L;


assign	ACIA_IRQ = ~(SYNTHESIZED_WIRE_30 & SYNTHESIZED_WIRE_31 & SYNTHESIZED_WIRE_32 & SYNTHESIZED_WIRE_33 & SYNTHESIZED_WIRE_34 & SYNTHESIZED_WIRE_35);


ACIA_6850	b2v_inst8(
	.Clk(Clock_50Mhz),
	.Reset_H(SYNTHESIZED_WIRE_42),
	.CS_H(SYNTHESIZED_WIRE_37),
	.Write_L(WE_L),
	.RS(Address[1]),
	.RxClock(SYNTHESIZED_WIRE_51),
	.TxClock(SYNTHESIZED_WIRE_51),
	.RxData(GPS_RxData),
	.DCD_L(SYNTHESIZED_WIRE_52),
	.CTS_L(SYNTHESIZED_WIRE_52),
	.DataIn(DataIn),
	.IRQ_L(SYNTHESIZED_WIRE_31),
	.TxData(GPS_TxData),
	
	.DataOut(DataOut));



endmodule
