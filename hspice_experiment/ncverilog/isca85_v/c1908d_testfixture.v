`timescale 1ns/10ps

`define cycle 10.0
`define terminate_cycle 400000//200000 // Modify your terminate ycle here

module c1908d_testfixture;

`define in_file "c1908d/rand_input_vector_c1908d_0.out"
`define out_file "c1908d/rand_output_vector_c1908d_0.out"

parameter vec_width = 66;
parameter vec_length = 4;

reg clk = 0;


reg [vec_width-1:0] input_vec_mem [0:vec_length-1];
reg [vec_width-1:0] vec;

wire n12753, n12754, n12755, n12756, n12762, n12767, n12768, n12779, n12780, n12781, n12782, n12783, n12784, n12785, n12786, n12787, n12811, n12886, n12887, n12888, n12889, n12890, n12891, n12892, n12899, n22753, n22754, n22755, n22756, n22762, n22767, n22768, n22779, n22780, n22781, n22782, n22783, n22784, n22785, n22786, n22787, n22811, n22886, n22887, n22888, n22889, n22890, n22891, n22892, n22899;
initial begin
	$readmemb(`in_file, input_vec_mem );
end

always #(`cycle/2) clk = ~clk;

c1908d cc (.N11(vec[65]), .N14(vec[64]), .N17(vec[63]), .N110(vec[62]), .N113(vec[61]), .N116(vec[60]), .N119(vec[59]), .N122(vec[58]), .N125(vec[57]), .N128(vec[56]), .N131(vec[55]), .N134(vec[54]), .N137(vec[53]), .N140(vec[52]), .N143(vec[51]), .N146(vec[50]), .N149(vec[49]), .N153(vec[48]), .N156(vec[47]), .N160(vec[46]), .N163(vec[45]), .N166(vec[44]), .N169(vec[43]), .N172(vec[42]), .N176(vec[41]), .N179(vec[40]), .N182(vec[39]), .N185(vec[38]), .N188(vec[37]), .N191(vec[36]), .N194(vec[35]), .N199(vec[34]), .N1104(vec[33]), .N21(vec[32]), .N24(vec[31]), .N27(vec[30]), .N210(vec[29]), .N213(vec[28]), .N216(vec[27]), .N219(vec[26]), .N222(vec[25]), .N225(vec[24]), .N228(vec[23]), .N231(vec[22]), .N234(vec[21]), .N237(vec[20]), .N240(vec[19]), .N243(vec[18]), .N246(vec[17]), .N249(vec[16]), .N253(vec[15]), .N256(vec[14]), .N260(vec[13]), .N263(vec[12]), .N266(vec[11]), .N269(vec[10]), .N272(vec[9]), .N276(vec[8]), .N279(vec[7]), .N282(vec[6]), .N285(vec[5]), .N288(vec[4]), .N291(vec[3]), .N294(vec[2]), .N299(vec[1]), .N2104(vec[0]), .N12753(n12753), .N12754(n12754), .N12755(n12755), .N12756(n12756), .N12762(n12762), .N12767(n12767), .N12768(n12768), .N12779(n12779), .N12780(n12780), .N12781(n12781), .N12782(n12782), .N12783(n12783), .N12784(n12784), .N12785(n12785), .N12786(n12786), .N12787(n12787), .N12811(n12811), .N12886(n12886), .N12887(n12887), .N12888(n12888), .N12889(n12889), .N12890(n12890), .N12891(n12891), .N12892(n12892), .N12899(n12899), .N22753(n22753), .N22754(n22754), .N22755(n22755), .N22756(n22756), .N22762(n22762), .N22767(n22767), .N22768(n22768), .N22779(n22779), .N22780(n22780), .N22781(n22781), .N22782(n22782), .N22783(n22783), .N22784(n22784), .N22785(n22785), .N22786(n22786), .N22787(n22787), .N22811(n22811), .N22886(n22886), .N22887(n22887), .N22888(n22888), .N22889(n22889), .N22890(n22890), .N22891(n22891), .N22892(n22892), .N22899(n22899));

integer i=0;
always @ (posedge clk) begin
	vec = input_vec_mem[i];
	$monitor(vec);
	i = i + 1;

end

always @ (negedge clk)begin
	$fdisplay ( fh_w, n12753, n12754, n12755, n12756, n12762, n12767, n12768, n12779, n12780, n12781, n12782, n12783, n12784, n12785, n12786, n12787, n12811, n12886, n12887, n12888, n12889, n12890, n12891, n12892, n12899, n22753, n22754, n22755, n22756, n22762, n22767, n22768, n22779, n22780, n22781, n22782, n22783, n22784, n22785, n22786, n22787, n22811, n22886, n22887, n22888, n22889, n22890, n22891, n22892, n22899);
	if(i == vec_length)begin
		$finish;
	end
end

integer fh_w;
initial begin
	fh_w = $fopen(`out_file, "w");
end
 
initial begin
	//$fsdbDumpfile("SET.fsdb");
	//$fsdbDumpvars;
	//$fsdbDumpMDA;
	$dumpfile("test_result.vcd");
    $dumpvars;

end
endmodule
