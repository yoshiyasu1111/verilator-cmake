module top (
    input  logic       clk,
    input  logic       rst_n,
    output logic [7:0] count0,
    output logic [3:0] count1,
    output logic [7:0] bar_r [0:6],
    output logic [7:0] bar_g [0:6],
    output logic [7:0] bar_b [0:6]
);

    // 8bit counter instance
    counter8 u_counter8 (
        .clk   (clk),
        .rst_n (rst_n),
        .en    (1'b1),
        .count (count0)
    );

    // 4bit counter instance
    counter4 u_counter4 (
        .clk   (clk),
        .rst_n (rst_n),
        .en    (1'b1),
        .count (count1)
    );

    color_bars u_color_bars (
        .r (bar_r),
        .g (bar_g),
        .b (bar_b)
    );

endmodule
