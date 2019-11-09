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
// CREATED		"Fri Mar  2 02:21:26 2018"

module ACIA_BaudRate_Generator(
	Clk,
	Clk_50Mhz,
	Reset_L,
	Enable_H,
	DataIn,
	ACIA_Clock
);


input wire	Clk;
input wire	Clk_50Mhz;
input wire	Reset_L;
input wire	Enable_H;
input wire	[2:0] DataIn;
output wire	ACIA_Clock;

wire	[2:0] SYNTHESIZED_WIRE_0;





Register3Bit	b2v_inst(
	.Enable(Enable_H),
	.Clk(Clk),
	.Reset(Reset_L),
	.DataIn(DataIn),
	.Q(SYNTHESIZED_WIRE_0));


ACIA_Clock	b2v_inst2(
	.Clk(Clk_50Mhz),
	.BaudRateSelect(SYNTHESIZED_WIRE_0),
	.ACIA_Clk(ACIA_Clock));


endmodule
