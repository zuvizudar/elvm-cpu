`timescale 1ns/1ns 
module cpu_tb ();
	reg clk_t=1'b0,btn_t=1'b0;
	wire seg_t=1'b0,segsel_t=1'b0,led_t=1'b0;
	cpu cpu_test(clk_t,btn_t,led_t);
	initial begin
	$display("running");
	forever #20 clk_t=!clk_t;
	end
endmodule 