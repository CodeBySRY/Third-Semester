module fsm_practice_tb;

    reg clk;
    reg reset_n;
    reg [1:0] i;
    wire [1:0] O;

    // Instantiate DUT
    fsm_practice dut (
        .clk(clk),
        .reset_n(reset_n),
        .i(i),
        .O(O)
    );

    // Clock generation (10ns period)
    always #5 clk = ~clk;

    initial begin
        // Initial conditions
        clk = 0;
        reset_n = 0;
        i = 2'b00;

        // Hold reset
        #20;
        reset_n = 1;

        // ---- FSM stimulus ----

        // IDLE -> PIN_WAIT (card inserted)
        @(posedge clk);
        i = 2'b10;

        // PIN_WAIT -> GO (pin correct)
        @(posedge clk);
        i = 2'b11;

        // GO -> IDLE (automatic)
        @(posedge clk);
        i = 2'b00;

        // IDLE -> PIN_WAIT
        @(posedge clk);
        i = 2'b10;

        // PIN_WAIT -> ALARM (wrong pin)
        @(posedge clk);
        i = 2'b10;

        // Stay in ALARM
        repeat (2) @(posedge clk);

        // Reset from ALARM
        reset_n = 0;
        #10;
        reset_n = 1;

        repeat (3) @(posedge clk);
        $stop;
    end

endmodule
