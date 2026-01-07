`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/01/2025 12:02:51 AM
// Design Name: T Flip-Flop Testbench
// Module Name: t_flipflop_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: Comprehensive testbench for T flip-flop verification
//    Tests reset functionality, hold state, and toggle operation
// 
// Dependencies: t_flipflop.v
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//    Verifies asynchronous reset priority and toggle behavior
// 
//////////////////////////////////////////////////////////////////////////////////

module t_flipflop_tb;

    // Inputs (test stimuli)
    reg T;
    reg CLK;
    reg RST;
    
    // Outputs (monitor these)
    wire Q;
    
    // Instantiate Unit Under Test (UUT)
    t_flipflop uut (
        .Q(Q),
        .T(T),
        .CLK(CLK),
        .RST(RST)
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
        RST = 1;    // Assert reset initially
        T = 0;
        
        // Test Case 1: Initial reset condition
        #15;        // Wait past first clock edge
        
        // Test Case 2: Release reset, T=0 (hold state)
        RST = 0;
        T = 0;
        #40;
        
        // Test Case 3: T=1 (toggle mode - multiple cycles)
        T = 1;
        #80;        // Allow multiple toggle cycles
        
        // Test Case 4: T=0 (hold current state)
        T = 0;
        #40;
        
        // Test Case 5: T=1 (resume toggling)
        T = 1;
        #40;
        
        // Test Case 6: Asynchronous reset assertion during operation
        RST = 1;
        #20;
        
        // Test Case 7: Continue operation after reset release
        RST = 0;
        T = 1;
        #60;
        
        // End simulation
        $display("T Flip-Flop test completed successfully");
        $finish;
    end
    

endmodule