`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM
// Design Name: T Flip-Flop Derived from JK Flip-Flop
// Module Name: t_flipflop
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
//    T Flip-Flop implementation by connecting J and K inputs together.
//    This creates a JK flip-flop where J=K=T, resulting in:
//    - T=0: J=K=0 -> Hold state (no change)
//    - T=1: J=K=1 -> Toggle state (invert output)
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//    Fundamental relationship: T Flip-Flop = JK Flip-Flop with J=K=T
// 
//////////////////////////////////////////////////////////////////////////////////

module t_flipflop(
    output reg Q,        // Flip-flop output
    input wire T,        // Toggle enable input
    input wire CLK,      // Positive-edge trigger clock
    input wire RST       // Asynchronous active-high reset
);
    
    // Sequential logic with asynchronous reset
    always @(posedge CLK or posedge RST) begin 
        if (RST) // Same as: if (RST == 1'b1)
            Q <= 1'b0;           // Reset condition (highest priority)
        else begin
            // T Flip-Flop behavior derived from JK Flip-Flop truth table:
            // When J=K=T, the JK behavior becomes:
            case(T)
                1'b0: Q <= Q;    // T=0: J=0,K=0 -> Hold state (JK: no change)
                1'b1: Q <= ~Q;   // T=1: J=1,K=1 -> Toggle state (JK: toggle)
            endcase
            
            /* 
            JK Flip-Flop Truth Table (for reference):
            J  K  |  Q(t+1)
            ---------------
            0  0  |   Q(t)    // Hold
            0  1  |     0     // Reset  
            1  0  |     1     // Set
            1  1  |   ~Q(t)   // Toggle
            
            When we set J=K=T:
            T  |  J  K  |  Q(t+1)  | T Flip-Flop Behavior
            --------------------------------------------
            0  |  0  0  |   Q(t)   | Hold (no change)
            1  |  1  1  |   ~Q(t)  | Toggle (invert)
            */
        end
    end
    
endmodule