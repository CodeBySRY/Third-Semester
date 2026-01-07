`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM
// Design Name: JK Flip-Flop
// Module Name: jk_flipflop
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Positive-edge triggered JK flip-flop with synchronous operation
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//    JK flip-flop eliminates invalid state of SR flip-flop using toggle functionality
// 
//////////////////////////////////////////////////////////////////////////////////

module jk_flipflop(
    output reg Q,        // Main output
    output reg Qbar,     // Complementary output  
    input wire CLK,      // Positive-edge trigger clock
    input wire J,        // Set condition input
    input wire K         // Reset condition input
);
    
    // Sequential logic with positive-edge trigger
    always @(posedge CLK) begin 
        case({J, K})
            2'b00: Q <= Q;       // No change: retain previous state
            2'b01: Q <= 1'b0;    // Reset: clear output to 0
            2'b10: Q <= 1'b1;    // Set: set output to 1  
            2'b11: Q <= ~Q;      // Toggle: invert current state
        endcase 
        
        Qbar <= ~Q;  // Generate complementary output
        // This is another syntax to define the sequential logic inside the 'always' block.
    end 
    
endmodule