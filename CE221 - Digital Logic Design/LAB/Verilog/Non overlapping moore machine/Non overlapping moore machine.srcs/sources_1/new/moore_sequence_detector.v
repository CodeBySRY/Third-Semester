`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/23/2025 11:44:50 PM
// Design Name: 
// Module Name: moore_sequence_detector
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


module moore_sequence_detector(
    // After each definition of the input and output, is the comma ','.
	input clk,
	input reset_n,
	input x, // Input bit
	output y // there is no comma at the end here
	);

	reg[2:0] state_reg, state_next;
	localparam A = 3'b000; 
	localparam B = 3'b001;
	localparam C = 3'b010;
	localparam D = 3'b011;
	localparam E = 3'b100;

	// state register
	always @ (posedge clk, negedge reset_n)
	begin
		if(~reset_n)
			state_reg <= A;
		else
			state_reg <= state_next;
	end

	// Next state logic
	always @ (*) // start the always block by defining your begin and end statements in the beginning
	begin
		case(state_reg) // make sure to include the endcase (IMPORTANT)
			A: if(x)
				state_next = B;
			else
				state_next = A;
			B: if(x)
				state_next = B;
			else
				state_next = C;
			C: if(x)
				state_next = D;
			else
				state_next = A;
			D: if(x)
				state_next = E;
			else
				state_next = A;
			E: if(x)
				state_next = A;
			else
				state_next = A;
			default: state_next = state_reg;
		endcase
	end

	// Output logic
	assign y = (state_reg == E);

endmodule
