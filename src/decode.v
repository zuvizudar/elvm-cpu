module decoder(clk,in,is_sorce_im,op,rd,rs,is_negative_num,im);
	input clk;
	input[25:0]in;
	output is_sorce_im;
	output[4:0]op;
	output[7:0]rd;
	output[2:0]rs;
	output is_negative_num;
	output[7:0] im;
	
	assign is_sorce_im=in[25:25];
	assign op=in[24:20];
	assign rd=in[19:12];
	assign rs=in[11:9];
	assign is_negative_num=in[8:8];
	assign im=in[7:0];

endmodule 