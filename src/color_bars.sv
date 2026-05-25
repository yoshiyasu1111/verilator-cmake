module color_bars (
    output logic [7:0] r [0:6],
    output logic [7:0] g [0:6],
    output logic [7:0] b [0:6]
);

  always_comb begin
    // グレー
    r[0] = 8'd192; g[0] = 8'd192; b[0] = 8'd192;
    // イエロー
    r[1] = 8'd192; g[1] = 8'd192; b[1] = 8'd0;
    // シアン
    r[2] = 8'd0;   g[2] = 8'd192; b[2] = 8'd192;
    // グリーン
    r[3] = 8'd0;   g[3] = 8'd192; b[3] = 8'd0;
    // マゼンタ
    r[4] = 8'd192; g[4] = 8'd0;   b[4] = 8'd192;
    // レッド
    r[5] = 8'd192; g[5] = 8'd0;   b[5] = 8'd0;
    // ブルー
    r[6] = 8'd0;   g[6] = 8'd0;   b[6] = 8'd192;
  end

endmodule
