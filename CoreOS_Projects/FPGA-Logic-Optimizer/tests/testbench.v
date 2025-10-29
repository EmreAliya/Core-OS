`timescale 1ns/1ps
module testbench;
    reg [7:0] a, b;
    wire [7:0] y;
    top_module dut (.a(a), .b(b), .y(y));

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, testbench);
        for (integer i = 0; i < 10; i = i + 1) begin
            a = $random;
            b = $random;
            #10;
        end
        $finish;
    end
endmodule
