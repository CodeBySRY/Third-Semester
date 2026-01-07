`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/16/2025 12:02:23 AM
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
    input clk,
    input rst,
    input X,
    output reg Y
);

    // State bits (flip-flops)
    reg Q0, Q1, Q2;        // Q0 = MSB, Q2 = LSB
    reg D0, D1, D2;        // D inputs

    // ==========================
    // Sequential Logic (D-FFs)
    // ==========================
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            Q0 <= 1'b0;
            Q1 <= 1'b0;
            Q2 <= 1'b0;
        end else begin
            Q0 <= D0;
            Q1 <= D1;
            Q2 <= D2;
        end
    end

    // ==========================
    // Combinational Logic
    // ==========================
    always @(*) begin
        // Default hold state
        D0 = Q0;
        D1 = Q1;
        D2 = Q2;

        // State A: 000
        if (Q0==0 && Q1==0 && Q2==0) begin
            if (X==0) begin D2=1; end // B
        end

        // State B: 001
        else if (Q0==0 && Q1==0 && Q2==1) begin
            if (X==1) begin D1=1; D2=0; end // C
        end

        // State C: 010
        else if (Q0==0 && Q1==1 && Q2==0) begin
            if (X==0) begin D1=1; D2=1; end // D
            else begin D1=0; D2=0; end     // A
        end

        // State D: 011
        else if (Q0==0 && Q1==1 && Q2==1) begin
            if (X==1) begin D0=1; D1=0; D2=0; end // E
            else begin D1=0; D2=1; end            // B
        end

        // State E: 100
        else if (Q0==1 && Q1==0 && Q2==0) begin
            if (X==0) begin D0=0; D2=1; end // B
            else begin D0=0; D1=0; D2=0; end // A
        end
    end

    // ==========================
    // Moore Output Logic
    // ==========================
    always @(*) begin
        if (Q0==1 && Q1==0 && Q2==0)
            Y = 1'b1;
        else
            Y = 1'b0;
    end

endmodule

