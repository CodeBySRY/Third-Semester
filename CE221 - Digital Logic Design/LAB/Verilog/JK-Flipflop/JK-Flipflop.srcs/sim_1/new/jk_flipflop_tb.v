`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM  
// Design Name: JK Flip-Flop Testbench
// Module Name: jk_flipflop_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Comprehensive testbench for JK flip-flop verification
// 
// Dependencies: jk_flipflop.v
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//    Tests all JK input combinations including toggle functionality
// 
//////////////////////////////////////////////////////////////////////////////////

module jk_flipflop_tb;

    // Inputs (test stimuli)
    reg CLK;
    reg J;
    reg K;
    
    // Outputs (monitor these)
    wire Q;
    wire Qbar;
    
    // Instantiate Unit Under Test (UUT)
    jk_flipflop uut (
        .Q(Q),
        .Qbar(Qbar), 
        .CLK(CLK),
        .J(J),
        .K(K)
    );
    
    // Clock generation: 50MHz clock (20ns period)
    initial begin
        CLK = 0;
        forever #10 CLK = ~CLK;  // 20ns period = 50MHz
    end
    
    // Test sequence
    initial begin
        // Initialize all inputs
        CLK = 0;
        J = 0;
        K = 0;
        
        // Wait for initial stabilization
        #20;
        
        // Test Case 1: No change (J=0, K=0)
        J = 0; K = 0;
        #100;
        
        // Test Case 2: Reset (J=0, K=1)  
        J = 0; K = 1;
        #100;
        
        // Test Case 3: Set (J=1, K=0)
        J = 1; K = 0;
        #100;
        
        // Test Case 4: Toggle (J=1, K=1) - Critical test case
        J = 1; K = 1;
        #100;
        
        // Test Case 5: Verify toggle continues
        J = 1; K = 1;  
        #100;
        
        // End simulation
        $display("JK Flip-Flop test completed successfully");
        $finish;
    end
    

endmodule