`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM
// Design Name: 
// Module Name: sr_flipflop_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Testbench for SR Flipflop verification
// 
// Dependencies: sr_flipflop.v
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module sr_flipflop_tb;

    // Testbench signals
    reg S, R, CLK; // inputs are defined as reg (in the testbench)
    wire Q, Qbar; // outputs are defined as wire (in the testbench)
    
    // Instantiate the Unit Under Test (UUT)
    sr_flipflop uut (
        .S(S),
        .R(R),
        .CLK(CLK),
        .Q(Q),
        .Qbar(Qbar)
    );
    
    // Clock generation (100MHz clock - 10ns period)
    initial begin
        CLK = 0;
        forever #5 CLK = ~CLK;  // 10ns period clock
    end
    
    // Test sequence
    initial begin
        // Initialize inputs
        S = 0;
        R = 0;
        
        // Wait for global reset
        #10;
        
        // Test case 1: No change (S=0, R=0)
        S = 0; R = 0;
        #10;
        
        // Test case 2: Reset (S=0, R=1)
        S = 0; R = 1;
        #10;
        
        // Test case 3: Set (S=1, R=0)
        S = 1; R = 0;
        #10;
        
        // Test case 4: Invalid state (S=1, R=1)
        S = 1; R = 1;
        #10;
        
        // Test case 5: Return to reset state
        S = 0; R = 1;
        #10;
        
        // Test case 6: Return to set state
        S = 1; R = 0;
        #10;
        
        // End simulation
        $display("SR Flipflop testbench completed");
        $finish; // DO NOT FORGET THE SEMI COLON AT THE END OF $finish;
    end
    
    

endmodule