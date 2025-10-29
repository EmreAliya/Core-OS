// top_module.v
module top_module (
    input  wire [7:0] a,
    input  wire [7:0] b,
    output wire [7:0] y
);
    assign y = ((a & b) | (a ^ b)) & ~(a & b);
endmodule
