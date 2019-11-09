//1 bit D-flip flop
module dff_async_reset (
  input wire data,   // Data Input
  input wire clk,    // Clock Input
  input wire reset,  // Reset input 
  output reg q       // Q output
);
 
  reg data_1delay = 1'b0;
  reg data_2delay = 1'b0;
  always @( posedge clk or negedge reset) begin
    if (~reset) begin
      data_1delay <= 1'b0;
		data_2delay <= 1'b0;
		q <= 1'b0;
    end else begin
      data_2delay <= data_1delay;
		data_1delay <= data;
		if( data_1delay == 1'b1 && data_2delay == 1'b0) begin
		  q <= 1'b1;
		end else begin
        q <= 1'b0;
      end
    end
  end  

endmodule
