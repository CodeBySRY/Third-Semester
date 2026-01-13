# 📚 Verilog HDL for Digital Logic Design

## Introduction to Verilog

Verilog (Verification Logic) is a Hardware Description Language (HDL) used to model electronic systems at various levels of abstraction. Unlike software programming languages, Verilog describes hardware that operates in parallel.

## Sequential vs Combinational Logic

### Combinational Circuits (Blocking Assignments =)

```verilog
// Example: 2-to-1 Multiplexer
module mux2to1 (
    input wire a, b, sel,
    output reg out
);
    always @(*) begin
        if (sel == 1'b0)
            out = a;  // Blocking assignment
        else
            out = b;  // Blocking assignment
    end
endmodule
```

**Characteristics:**
- Output depends only on current inputs
- No memory elements
- Use `always @(*)` or `always @(sensitivity_list)`
- Use blocking assignments (=)
- Executes sequentially within the always block
- Mimics software behavior for combinational logic

### Sequential Circuits (Non-blocking Assignments <=)

```verilog
// Example: D Flip-Flop with Async Reset
module dff_async_reset (
    input wire clk,
    input wire reset_n,  // Active-low reset
    input wire d,
    output reg q
);
    always @(posedge clk or negedge reset_n) begin
        if (!reset_n)
            q <= 1'b0;      // Async reset
        else
            q <= d;         // Non-blocking assignment
    end
endmodule
```

**Characteristics:**
- Output depends on current state + inputs
- Contains memory elements (flip-flops, registers)
- Use `always @(posedge clk)` for synchronous
- Use non-blocking assignments (<=)
- All assignments happen simultaneously at clock edge
- Prevents race conditions in sequential logic

## Assignment Types Comparison

| Aspect | Blocking (=) | Non-blocking (<=) |
|--------|--------------|-------------------|
| Execution | Immediate, sequential | All at end of timestep |
| Use Case | Combinational logic | Sequential logic |
| Hardware | Wires, combinational gates | Flip-flops, registers |
| Example | `a = b; c = a;` (c gets b's new value) | `a <= b; c <= a;` (c gets a's old value) |
| Timing | Like software assignment | Parallel, synchronized to clock |

## Understanding reg vs wire

### reg Data Type

```verilog
module example (
    input wire clk,
    input wire data_in,
    output reg data_out,     // reg because assigned in always block
    output wire status       // wire because continuous assignment
);
    
    reg internal_reg;        // Can store value
    
    always @(posedge clk) begin
        data_out <= data_in; // reg assigned in always block
        internal_reg <= data_in;
    end
    
    assign status = (data_out == 1'b1); // wire assigned with assign
endmodule
```

**When to use reg:**
- Any signal assigned inside an `always` or `initial` block
- Outputs of sequential elements
- Temporary variables in procedural blocks
- **Important:** `reg` doesn't necessarily imply a hardware register!

### wire Data Type

```verilog
module adder (
    input wire [3:0] a, b,
    output wire [3:0] sum,
    output wire carry
);
    
    // Continuous assignment - combinational logic
    assign {carry, sum} = a + b;
    
    // wire can also be used for connections
    wire [3:0] temp = a & b;  // AND operation
endmodule
```

**When to use wire:**
- Signals assigned with `assign` statements
- Module input/output ports (unless declared as reg)
- Connections between modules
- Outputs of combinational logic

## Always Blocks and Sensitivity Lists

### Combinational Sensitivity

```verilog
// Method 1: Wildcard (Verilog 2001+)
always @(*) begin
    // Automatically includes all inputs used in block
    y = a & b | c;
end

// Method 2: Explicit list
always @(a or b or c) begin  // Verilog 1995 style
    y = a & b | c;
end

// Method 3: For complex combinational logic
always @* begin
    case(opcode)
        2'b00: result = a + b;
        2'b01: result = a - b;
        2'b10: result = a & b;
        2'b11: result = a | b;
        default: result = 4'b0;
    endcase
end
```

### Sequential Sensitivity

```verilog
// Positive edge-triggered
always @(posedge clk) begin
    q <= d;
end

// Negative edge-triggered  
always @(negedge clk) begin
    q <= d;
end

// Multiple signals in sensitivity list
always @(posedge clk or posedge reset) begin
    if (reset)
        count <= 4'b0000;
    else
        count <= count + 1;
end

// Async reset (active-low)
always @(posedge clk or negedge reset_n) begin
    if (!reset_n)
        state <= IDLE;
    else
        state <= next_state;
end
```

## Synchronous vs Asynchronous Circuits

### Synchronous Design (Single Clock Domain)

```verilog
module sync_counter (
    input wire clk,
    input wire reset,
    input wire enable,
    output reg [7:0] count
);
    
    always @(posedge clk) begin
        if (reset)
            count <= 8'b0;
        else if (enable)
            count <= count + 1;
    end
endmodule
```

**Benefits:**
- One master clock synchronizes all flip-flops
- Predictable timing behavior
- Easier to design and verify
- Recommended for beginners and most designs

### Asynchronous Design (Multiple Clock Domains)

```verilog
module async_interface (
    input wire clk_a,     // 50 MHz
    input wire clk_b,     // 100 MHz  
    input wire data_in,
    output reg data_out
);
    
    reg sync_stage1, sync_stage2;
    
    // Clock domain A
    always @(posedge clk_a) begin
        sync_stage1 <= data_in;
    end
    
    // Clock domain B  
    always @(posedge clk_b) begin
        sync_stage2 <= sync_stage1;
        data_out <= sync_stage2;  // Double synchronization
    end
endmodule
```

**Challenges with Asynchronous Circuits:**
- Clock Domain Crossing (CDC)
- Metastability issues
- Need synchronization circuits (2-FF synchronizer)
- Data consistency problems

**Timing Analysis Complexity:**
- Multiple clock constraints
- False paths need explicit definition
- Setup/hold checks across domains

**Design Verification:**
- Difficult to simulate timing accurately
- Requires formal verification methods
- Higher risk of bugs in silicon

## Building Blocks for RISC-V (COAL Preparation)

### 1. Register File (32 registers like RISC-V)

```verilog
module register_file (
    input wire clk,
    input wire we,           // Write enable
    input wire [4:0] addr1,  // Read address 1 (rs1)
    input wire [4:0] addr2,  // Read address 2 (rs2)
    input wire [4:0] addr3,  // Write address (rd)
    input wire [31:0] wdata, // Write data
    output reg [31:0] rdata1,// Read data 1
    output reg [31:0] rdata2 // Read data 2
);
    
    // 32 registers x 32 bits each
    reg [31:0] registers [0:31];
    
    // Initialize register x0 to zero (RISC-V requirement)
    integer i;
    initial begin
        for (i = 0; i < 32; i = i + 1)
            registers[i] = 32'b0;
        // Note: In real RISC-V, only x0 is hardwired to zero
    end
    
    // Read ports (combinational)
    always @(*) begin
        rdata1 = registers[addr1];
        rdata2 = registers[addr2];
        // Register x0 always returns zero
        if (addr1 == 5'b0) rdata1 = 32'b0;
        if (addr2 == 5'b0) rdata2 = 32'b0;
    end
    
    // Write port (sequential)
    always @(posedge clk) begin
        if (we && addr3 != 5'b0) begin  // Never write to x0
            registers[addr3] <= wdata;
        end
    end
endmodule
```

### 2. ALU (Arithmetic Logic Unit)

```verilog
module alu (
    input wire [31:0] a, b,
    input wire [3:0] alu_control,
    output reg [31:0] result,
    output reg zero_flag
);
    
    // ALU operations (matching RISC-V)
    parameter ALU_ADD  = 4'b0000;
    parameter ALU_SUB  = 4'b0001;
    parameter ALU_AND  = 4'b0010;
    parameter ALU_OR   = 4'b0011;
    parameter ALU_XOR  = 4'b0100;
    parameter ALU_SLT  = 4'b0101;  // Set less than (signed)
    parameter ALU_SLTU = 4'b0110;  // Set less than (unsigned)
    parameter ALU_SLL  = 4'b0111;  // Shift left logical
    parameter ALU_SRL  = 4'b1000;  // Shift right logical
    parameter ALU_SRA  = 4'b1001;  // Shift right arithmetic
    
    always @(*) begin
        case (alu_control)
            ALU_ADD:  result = a + b;
            ALU_SUB:  result = a - b;
            ALU_AND:  result = a & b;
            ALU_OR:   result = a | b;
            ALU_XOR:  result = a ^ b;
            ALU_SLT:  result = ($signed(a) < $signed(b)) ? 32'b1 : 32'b0;
            ALU_SLTU: result = (a < b) ? 32'b1 : 32'b0;
            ALU_SLL:  result = a << b[4:0];  // Shift amount in lower 5 bits
            ALU_SRL:  result = a >> b[4:0];
            ALU_SRA:  result = $signed(a) >>> b[4:0];
            default:  result = 32'b0;
        endcase
        
        // Zero flag (for branch instructions)
        zero_flag = (result == 32'b0);
    end
endmodule
```

### 3. Single-Cycle RISC-V Datapath (Conceptual)

```verilog
module single_cycle_riscv (
    input wire clk,
    input wire reset,
    output wire [31:0] pc,
    output wire [31:0] instruction
);
    
    // Program Counter
    reg [31:0] pc_reg;
    wire [31:0] pc_next;
    
    // Instruction Memory
    reg [31:0] imem [0:1023];  // 1KB instruction memory
    
    // Register File
    wire [31:0] rs1_data, rs2_data;
    
    // ALU
    wire [31:0] alu_result;
    
    // Control Unit outputs
    wire reg_write, mem_to_reg, mem_write, alu_src, branch;
    wire [3:0] alu_control;
    
    // --- Sequential Logic ---
    always @(posedge clk or posedge reset) begin
        if (reset)
            pc_reg <= 32'b0;
        else
            pc_reg <= pc_next;  // Non-blocking for sequential
    end
    
    // --- Combinational Logic ---
    assign pc = pc_reg;
    assign pc_next = pc_reg + 4;  // Default: next instruction
    
    // Instruction fetch
    assign instruction = imem[pc_reg[11:2]];  // Word-aligned
    
    // Control Unit (combinational)
    control_unit ctrl (
        .opcode(instruction[6:0]),
        .funct3(instruction[14:12]),
        .funct7(instruction[31:25]),
        .reg_write(reg_write),
        .mem_to_reg(mem_to_reg),
        .mem_write(mem_write),
        .alu_src(alu_src),
        .branch(branch),
        .alu_control(alu_control)
    );
    
    // Register File (mixed sequential/combinational)
    register_file rf (
        .clk(clk),
        .we(reg_write),
        .addr1(instruction[19:15]),  // rs1
        .addr2(instruction[24:20]),  // rs2
        .addr3(instruction[11:7]),   // rd
        .wdata(write_data),
        .rdata1(rs1_data),
        .rdata2(rs2_data)
    );
    
    // ALU (combinational)
    alu alu_unit (
        .a(rs1_data),
        .b(alu_src ? immediate : rs2_data),
        .alu_control(alu_control),
        .result(alu_result),
        .zero_flag(zero)
    );
endmodule
```

## Best Practices for DLD/COAL

### 1. Code Organization

```verilog
// Good structure:
module module_name (
    // 1. Clock and reset
    input wire clk,
    input wire reset_n,
    
    // 2. Control signals
    input wire enable,
    input wire [1:0] mode,
    
    // 3. Data inputs
    input wire [7:0] data_in,
    
    // 4. Outputs
    output reg [7:0] data_out,
    output wire ready
);

    // 5. Internal parameters
    parameter WIDTH = 8;
    parameter IDLE = 2'b00, RUN = 2'b01, DONE = 2'b10;
    
    // 6. Internal signals
    reg [1:0] state, next_state;
    wire [WIDTH-1:0] temp_result;
    
    // 7. Sequential always block
    always @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            state <= IDLE;
            data_out <= {WIDTH{1'b0}};
        end else begin
            state <= next_state;
            if (state == DONE)
                data_out <= temp_result;
        end
    end
    
    // 8. Combinational always block
    always @(*) begin
        case (state)
            IDLE: next_state = enable ? RUN : IDLE;
            RUN:  next_state = DONE;
            DONE: next_state = IDLE;
            default: next_state = IDLE;
        endcase
    end
    
    // 9. Continuous assignments
    assign temp_result = data_in * 2;
    assign ready = (state == DONE);
    
endmodule
```

### 2. Common Pitfalls to Avoid

```verilog
// ❌ WRONG: Mixing assignment types
always @(posedge clk) begin
    a = b;      // Blocking in sequential block - BAD!
    c <= a;     // Non-blocking
end

// ✅ CORRECT: Use only non-blocking in sequential
always @(posedge clk) begin
    a <= b;     // Good
    c <= a;     // Good (gets old value of a)
end

// ❌ WRONG: Incomplete sensitivity list
always @(a) begin  // Missing b and c!
    y = a & b | c;
end

// ✅ CORRECT: Use @* or @(*) 
always @(*) begin
    y = a & b | c;
end

// ❌ WRONG: Latches unintentionally created
always @(*) begin
    if (enable)
        q = data;  // No else -> creates latch!
end

// ✅ CORRECT: Always assign all outputs
always @(*) begin
    if (enable)
        q = data;
    else
        q = 1'b0;  // Default assignment
end
```

### 3. Testbench Writing Tips

```verilog
`timescale 1ns/1ps

module testbench;
    // 1. Declare signals
    reg clk, reset;
    reg [3:0] a, b;
    wire [3:0] sum;
    wire carry;
    
    // 2. Instantiate DUT
    adder dut (
        .a(a),
        .b(b),
        .sum(sum),
        .carry(carry)
    );
    
    // 3. Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // 100 MHz clock
    end
    
    // 4. Test stimulus
    initial begin
        // Initialize
        reset = 1;
        a = 4'b0;
        b = 4'b0;
        
        #20 reset = 0;
        
        // Test cases
        #10 a = 4'b0011; b = 4'b0010;  // 3 + 2 = 5
        #10 a = 4'b1111; b = 4'b0001;  // 15 + 1 = 16 (with carry)
        #10 a = 4'b1000; b = 4'b1000;  // 8 + 8 = 16
        
        // Finish simulation
        #50 $display("Simulation complete");
        $finish;
    end
    
    // 5. Monitoring
    initial begin
        $monitor("Time=%t, a=%b, b=%b, sum=%b, carry=%b",
                 $time, a, b, sum, carry);
    end
    
    // 6. Waveform dumping (for GTKWave)
    initial begin
        $dumpfile("waves.vcd");
        $dumpvars(0, testbench);
    end
endmodule
```

## Resources for Further Learning

### Books
- "Digital Design and Computer Architecture: RISC-V Edition" - Harris & Harris
- "Verilog HDL: A Guide to Digital Design and Synthesis" - Palnitkar
- "Principles of Digital Design" - Gajski

### Online Simulators
- EDA Playground (online Verilog simulator)
- Icarus Verilog (open-source compiler)
- GTKWave (waveform viewer)

### For RISC-V Specific
- RISC-V Official ISA Specification
- Chisel (Scala-based HDL that generates Verilog)
- Rocket Chip Generator (RISC-V SoC generator)

## Final Advice for Juniors

1. **Think in hardware, not software** - Everything happens in parallel
2. **Start with small modules** - Build and test incrementally
3. **Always write testbenches** - If it's not tested, it doesn't work
4. **Understand timing diagrams** - Critical for debugging
5. **Learn both Verilog and SystemVerilog** - Industry uses SystemVerilog
6. **Connect DLD theory to Verilog** - Gates → Modules, Flip-flops → always @(posedge clk)

**Remember:** In COAL, you'll see how this Verilog hardware gets turned into actual RISC-V processors. The datapath you design in Verilog is exactly what executes those assembly instructions!