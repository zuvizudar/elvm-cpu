module cpu(clk,btn,led);
	input clk;
	input[3:0] btn;
	output[3:0] led;
	
	wire [4:0] op;
	wire[2:0] rs_p;
	wire[7:0] rd_p;
	wire[7:0] im;
	//wire [3:0] nbtn;
	wire is_sorce_im;
	wire is_negative_num;
	wire [25:0] dout;
	reg [7:0]addr=8'b00000000;
	//assign nbtn=~btn;

	reg[8:0]register[5:0];//A,B,C,D,SP,BP; 桁溢れ対策に9bitにしている
	reg[25:0]out=26'h00000;
	reg c_flag=1'b0;
	reg[8:0] data_mem[255:0];
	reg[7:0]label[11:0];
	reg[7:0]label_cnt=8'b00000000;
	integer i;
	initial begin
		for(i=1'b0;i<256;i=i+1'b1)
			data_mem[i]=26'h0000;
	
	
		for(i=1'b0;i<6;i=i+1'b1)
			register[i]=26'h0000;
		
		for(i=1'b0;i<12;i=i+1'b1)
			label[i]=8'b00000000;

	end
	
	rom_out rom(dout,addr);
	decoder decode(clk,dout,is_sorce_im,op,rd_p,rs_p,is_negative_num,im);
			
	always @(posedge clk)begin
				case(op)
					5'b00000:begin //mov
						if(is_sorce_im==1'b0)
							register[rd_p]<=register[rs_p];
						else
							register[rd_p]<=im;
					end
					5'b00001:begin //add
						if(is_sorce_im==1'b0)//reg+reg
							register[rd_p]<=(register[rd_p]+register[rs_p])&9'b011111111;
						else//reg+im
							register[rd_p]<=(register[rd_p]+im)&9'b011111111;
					end
					5'b00010:begin //sub
						if(is_sorce_im==1'b0)
							register[rd_p]<=(register[rd_p]-register[rs_p])&9'b011111111;
						else
							register[rd_p]<=(register[rd_p]-im)&9'b011111111;
					end
					
					5'b00011:begin//load	
						if(is_sorce_im==1'b0)		
							register[rd_p]<=data_mem[register[rs_p]];
						else
							register[rs_p]<=data_mem[data_mem[rd_p]];
						//register[rs_p]<=data_mem[rd_p];
						//register[rs_p]<=data_mem[rd_p];
					end
					5'b00100:begin//store
						//data_mem[register[rd_p]]<=register[rs_p];
						if(is_sorce_im==1'b0)
							data_mem[register[rs_p]]<=register[rd_p];
						else
							data_mem[rd_p]<=im;
					end
					5'b00101:begin//putc
						//out<=register[rd_p];
						$display("%c",register[rd_p]);									
					end
					/*6'b000110:begin//exit
							;
					end
					*/
						5'b01000:begin//eq01					
						register[rd_p]<=(register[rd_p]==register[rs_p]);
					end
					5'b01001:begin//ne01					
						register[rd_p]<=(register[rd_p]!=register[rs_p]);
					end
					5'b01010:begin//lt01					
						register[rd_p]<=(register[rd_p]<register[rs_p]);
					end
					5'b01011:begin//gt01					
						register[rd_p]<=(register[rd_p]>register[rs_p]);
					end
					5'b01100:begin//le01					
						register[rd_p]<=(register[rd_p]<=register[rs_p]);
					end
					5'b01101:begin//ge01					
						register[rd_p]<=(register[rd_p]>=register[rs_p]);
					end
				
					5'b01110:begin//jeq
						if(is_sorce_im==1'b0)begin
							if(register[rs_p]==register[rd_p])begin
								addr<=(label[im]+label_cnt);
							end
							else addr<=addr+1;
						end
						else begin
							if(register[rd_p]==rs_p)begin
								addr<=(label[im]+label_cnt);
							end
							else addr<=addr+1;
						end
						
					end
					
					5'b01111:begin//jne
						if(register[rs_p]!=register[rd_p])begin
							addr<=label[im];
						end
					end
					5'b10000:begin//jlt
						if(register[rs_p]<register[rd_p])begin
							addr<=label[im];
						end
					end
					5'b10001:begin//jgt
						if(register[rs_p]>register[rd_p])begin
							addr<=label[im];
						end
					end

					5'b10010:begin//jle
						if(register[rs_p]<=register[rd_p])begin
							addr<=label[im];
						end
					end
					5'b10011:begin//jge
						if(register[rs_p]>=register[rd_p])begin
							addr<=label[im];
						end
					end
					
					5'b10100:begin//jmp
						addr<=(label[im]+label_cnt);
					end
					
					5'b10101:begin//label_memo
						if(is_sorce_im==1'b0)
							label[rd_p]=im-1'b1; //addrをメモ
					end
					5'b10110:begin//lebel_cnt_memo
						label_cnt=im;
					end
					default:;
		endcase
		if(op<5'b01000||op>5'b10100)begin
			addr<=addr+1;
		end
	end

endmodule 
