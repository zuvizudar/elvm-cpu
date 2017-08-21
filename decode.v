module decoder(clk,in,is_sorce_im,op,rd,rs,im);
	input clk;
	input[23:0]in;
	output is_sorce_im;
	output	[4:0]op;
	output[2:0]	rs,rd;
	output[11:0] im;
	
	assign is_sorce_im=in[23];
	assign op=in[22:18];
	assign rd=in[17:15];
	assign rs=in[14:12];
	assign im=in[11:0];

endmodule 