module fsm_practice(
    input clk,
    input reset_n,
    input [1:0] i,
    output reg [1:0] O
);

    reg [1:0] state_reg, state_next;

    localparam I  = 2'b00;
    localparam PW = 2'b01;
    localparam GO = 2'b10;
    localparam A  = 2'b11;

    // 1?? State register
    always @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            state_reg <= I;
        else
            state_reg <= state_next;
    end

    // 2?? Next-state logic
    always @(*) begin
        state_next = state_reg; // default

        case (state_reg)
            I: begin
                if (i[1] == 1'b1)
                    state_next = PW;
                else
                    state_next = I;
            end

            PW: begin
                if (i[0] == 1'b1)
                    state_next = GO;
                else
                    state_next = A;
            end

            GO: begin
                state_next = I; // single-cycle pulse
            end

            A: begin
                state_next = A; // absorb state
            end
        endcase
    end

    // 3?? Output logic (Moore)
    always @(*) begin
        case (state_reg)
            I:  O = 2'b00;
            PW: O = 2'b00;
            GO: O = 2'b10;
            A:  O = 2'b01;
            default: O = 2'b00;
        endcase
    end

endmodule
