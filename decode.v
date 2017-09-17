module decoder(clk,in,is_sorce_im,op,rd,rs,is_negative_num,im);
	input clk;
	input[41:0]in;
	output is_sorce_im;
	output[4:0]op;
	output[7:0]rd;
	output[2:0]rs;
	output is_negative_num;
	output[23:0] im;
	
	assign is_sorce_im=in[41:41];
	assign op=in[40:36];
	assign rd=in[35:28];
	assign rs=in[27:25];
	assign is_negative_num=in[24:24];
	assign im=in[23:0];

endmodule 