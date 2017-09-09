module decoder(clk,in,is_sorce_im,op,rd,rs,is_negative_num,im);
	input clk;
	input[36:0]in;
	output is_sorce_im;
	output[4:0]op;
	output[2:0]	rs,rd;
	output is_negative_num;
	output[23:0] im;
	
	assign is_sorce_im=in[36:36];
	assign op=in[35:31];
	assign rd=in[30:28];
	assign rs=in[27:25];
	assign is_negative_num=in[24:24];
	assign im=in[23:0];

endmodule 