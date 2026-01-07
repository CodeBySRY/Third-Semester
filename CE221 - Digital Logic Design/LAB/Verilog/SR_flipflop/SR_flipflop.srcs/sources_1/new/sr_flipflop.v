`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM
// Design Name: 
// Module Name: sr_flipflop
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
//    Positive-edge triggered SR flip-flop with synchronous reset.
//    Implements classic SR flip-flop behavior with defined reset state.
//    Note: S=R=1 remains invalid/undefined per flip-flop fundamentals.
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sr_flipflop( 
    input  wire S, 
    input  wire R, 
    input  wire CLK, 
    output reg  Q, 
    output reg  Qbar 
); 
initial 
    begin 
        Q = 1'b0; 
        Qbar = 1'b1; 
    end 
always @(posedge CLK) begin 
    case ({S, R}) 
        2'b00: begin        // No change state: outputs retain previous values
            Q    <= Q;  
            Qbar <= Qbar; 
        end 
 
        2'b01: begin 
            Q    <= 1'b0;      // Reset operation: Q cleared to 0, Qbar set to 1
            Qbar <= 1'b1; 
        end 
        
        2'b10: begin 
            Q    <= 1'b1;      // Set operation: Q set to 1, Qbar cleared to 0
            Qbar <= 1'b0; 
        end 
        
        2'b11: begin 
            Q    <= 1'bx;      // Invalid condition: both set and reset asserted
            Qbar <= 1'bx; 
        end 
        
        default: begin
            // Catch-all for undefined states (good practice)
            Q    <= 1'bx;
            Qbar <= 1'bx;
        end
        
    endcase 
end 

endmodule 
