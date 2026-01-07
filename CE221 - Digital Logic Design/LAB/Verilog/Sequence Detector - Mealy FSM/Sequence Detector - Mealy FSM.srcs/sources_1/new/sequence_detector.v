`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/15/2025 06:00:48 PM
// Design Name: 
// Module Name: sequence_detector
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sequence_detector (
    input  wire clk,
    input  wire rst,
    input  wire X,
    output reg  Y
);

    // State bits
    reg Q1, Q0;
    reg D1, D0;

    // -------------------------
    // Combinational Logic
    // -------------------------
    always @(*) begin

        // Flip-flop input equations
        D0 = ~X;
        D1 = (~Q1 & Q0 & X) | (Q1 & ~Q0 & ~X);

        // Mealy output
        // Default
        Y = 1'b0;
        if (Q1 & Q0 & X)
            Y = 1'b1;
    end

    // -------------------------
    // Sequential Logic
    // -------------------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            Q1 <= 1'b0;
            Q0 <= 1'b0;
        end else begin
            Q1 <= D1;
            Q0 <= D0;
        end
    end

endmodule

