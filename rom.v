module rom_out(dout, addr);
	output [36:0] dout;
	input [7:0] addr;
	reg[36:0] mem[256:0];
	initial begin
		/*mem[8'b00000000]=37'b1_00001_000_000_0_000000000000000001000001;		//add
		mem[8'b00000001]=37'b1_00001_000_000_0_000000000000000000000001;		//add
		mem[8'b00000010]=37'b0_00101_000_000_0_000000000000000000000000;  //outs
		*/
		$readmemb("~/rom.ecpu",mem);
		//$display("%37b",mem[0]);
	end
	//rom memory(dout,addr,mem);
	assign dout = mem[addr];
endmodule
