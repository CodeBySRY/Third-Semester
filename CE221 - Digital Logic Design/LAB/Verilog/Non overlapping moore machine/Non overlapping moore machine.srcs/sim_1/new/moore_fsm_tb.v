`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/23/2025 11:49:04 PM
// Design Name: 
// Module Name: moore_fsm_tb
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


module moore_fsm_tb;
    
    // Outputs: wire
    // Inputs: reg
    
    reg clk;
    reg reset_n;
    reg x;
    wire y;
    
    // Instantiate the Unit Under Test
    moore_sequence_detector dut(
        .clk(clk),
        .reset_n(reset_n),
        .x(x),
        .y(y)
    );
    
    // Generate a clock signal
    always #5 clk = ~clk;
    
    reg [7:0] simple_test = 8'b10111011;
    // Should detect ONLY once (non-overlapping)
    integer i; // iterative variable to loop through all the input bit stream and assign to the input var;
    
    initial
    begin
        clk = 0;
        reset_n = 0; // Assert reset (active low)
        x = 0;
        #20 reset_n = 1; // Release reset after 20ns 
        
        for (i = 7; i >= 0; i = i-1) // Count DOWN from 7 to 0
        begin
            @(posedge clk);
            
            x = simple_test[i];
        end
        
        repeat (5) @(posedge clk);
        $stop;
    end
    
    
    
endmodule
