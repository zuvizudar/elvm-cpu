module uart_sender #(
    parameter clock = 50_000_000,
    parameter baudrate = 9600
) (
    input clk,
    input go,
    input [7:0] data,
    output tx,
    output ready
);

parameter wait_time = clock / baudrate;

parameter send_ready = 10'b0000000000,
          send_start = 10'b0000000001,
          send_stop  = 10'b1000000000;

reg [31:0] wait_count = wait_time,
           wait_count_next = wait_time;
reg [9:0] state = send_ready,
          state_next  = send_ready;
reg [8:0] send_buf = 9'b111111111,
          send_buf_next = 9'b111111111;
      
always @(posedge clk) begin
    state <= state_next;
    wait_count <= wait_count_next;
    send_buf <= send_buf_next;
end

always @(*) begin
    state_next = state;
    wait_count_next = wait_count;
    send_buf_next = send_buf;
    case (state)
        send_ready: begin
            if (go == 1) begin
                state_next = send_start;
                wait_count_next = wait_time;
                send_buf_next = {data, 1'b0};
            end
        end
        default: begin
            if (wait_count == 0) begin
                if (state == send_stop)
                    state_next = send_ready;
                else
                    state_next = {state[8:0], 1'b0};
                wait_count_next = wait_time;
                send_buf_next = {1'b1, send_buf[8:1]};
            end
            else begin
                wait_count_next = wait_count - 1;
            end
        end
    endcase
end

assign tx = send_buf[0];
assign ready = state == send_ready;

endmodule
