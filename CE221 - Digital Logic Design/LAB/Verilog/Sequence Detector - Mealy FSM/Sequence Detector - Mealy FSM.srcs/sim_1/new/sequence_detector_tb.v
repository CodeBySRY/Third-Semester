`timescale 1ns / 1ps

module sequence_detector_tb;

    reg clk;
    reg rst;
    reg X; // Input sequence bit (register)
    wire Y; // Output detection signal (wire)

    sequence_detector dut (
        .clk(clk),
        .rst(rst),
        .X(X),
        .Y(Y)
    );

    always #5 clk = ~clk;

    reg [27:0] bitstream = 28'b0010000000100100010110000101;
    integer i;

    initial begin
        clk = 0;
        rst = 1;
        X = 0;
        #20 rst = 0;

        for (i = 27; i >= 0; i = i - 1) begin
            @(posedge clk);
            X = bitstream[i];
        end

        repeat (5) @(posedge clk);
        $stop;
    end

endmodule