module rom(dout, addr);
	output [23:0] dout;
	input [7:0] addr;
	integer i;
	reg[23:0] mem[3:0];
	initial begin
		mem[8'b00000000]=24'b1_00001_000_000_000001000001;		//add
		mem[8'b00000001]=24'b1_00001_000_000_000000000001;		//add
		mem[8'b00000010]=24'b0_00101_000_000_000000000000;  //outs

	end
	

	assign dout = mem[addr];
endmodule