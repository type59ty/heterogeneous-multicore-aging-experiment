`timescale 1ns/10ps

`define cycle 10.0
`define terminate_cycle 400000//200000 // Modify your terminate ycle here

module c499d_testfixture;

`define in_file "c499d/rand_input_vector_c499d_0.out"
`define out_file "c499d/rand_output_vector_c499d_0.out"

parameter vec_width = 82;
parameter vec_length = 4;

reg clk = 0;


reg [vec_width-1:0] input_vec_mem [0:vec_length-1];
reg [vec_width-1:0] vec;

wire n1724, n1725, n1726, n1727, n1728, n1729, n1730, n1731, n1732, n1733, n1734, n1735, n1736, n1737, n1738, n1739, n1740, n1741, n1742, n1743, n1744, n1745, n1746, n1747, n1748, n1749, n1750, n1751, n1752, n1753, n1754, n1755, n2724, n2725, n2726, n2727, n2728, n2729, n2730, n2731, n2732, n2733, n2734, n2735, n2736, n2737, n2738, n2739, n2740, n2741, n2742, n2743, n2744, n2745, n2746, n2747, n2748, n2749, n2750, n2751, n2752, n2753, n2754, n2755;
initial begin
	$readmemb(`in_file, input_vec_mem );
end

always #(`cycle/2) clk = ~clk;

c499d cc (.N11(vec[81]), .N15(vec[80]), .N19(vec[79]), .N113(vec[78]), .N117(vec[77]), .N121(vec[76]), .N125(vec[75]), .N129(vec[74]), .N133(vec[73]), .N137(vec[72]), .N141(vec[71]), .N145(vec[70]), .N149(vec[69]), .N153(vec[68]), .N157(vec[67]), .N161(vec[66]), .N165(vec[65]), .N169(vec[64]), .N173(vec[63]), .N177(vec[62]), .N181(vec[61]), .N185(vec[60]), .N189(vec[59]), .N193(vec[58]), .N197(vec[57]), .N1101(vec[56]), .N1105(vec[55]), .N1109(vec[54]), .N1113(vec[53]), .N1117(vec[52]), .N1121(vec[51]), .N1125(vec[50]), .N1129(vec[49]), .N1130(vec[48]), .N1131(vec[47]), .N1132(vec[46]), .N1133(vec[45]), .N1134(vec[44]), .N1135(vec[43]), .N1136(vec[42]), .N1137(vec[41]), .N21(vec[40]), .N25(vec[39]), .N29(vec[38]), .N213(vec[37]), .N217(vec[36]), .N221(vec[35]), .N225(vec[34]), .N229(vec[33]), .N233(vec[32]), .N237(vec[31]), .N241(vec[30]), .N245(vec[29]), .N249(vec[28]), .N253(vec[27]), .N257(vec[26]), .N261(vec[25]), .N265(vec[24]), .N269(vec[23]), .N273(vec[22]), .N277(vec[21]), .N281(vec[20]), .N285(vec[19]), .N289(vec[18]), .N293(vec[17]), .N297(vec[16]), .N2101(vec[15]), .N2105(vec[14]), .N2109(vec[13]), .N2113(vec[12]), .N2117(vec[11]), .N2121(vec[10]), .N2125(vec[9]), .N2129(vec[8]), .N2130(vec[7]), .N2131(vec[6]), .N2132(vec[5]), .N2133(vec[4]), .N2134(vec[3]), .N2135(vec[2]), .N2136(vec[1]), .N2137(vec[0]), .N1724(n1724), .N1725(n1725), .N1726(n1726), .N1727(n1727), .N1728(n1728), .N1729(n1729), .N1730(n1730), .N1731(n1731), .N1732(n1732), .N1733(n1733), .N1734(n1734), .N1735(n1735), .N1736(n1736), .N1737(n1737), .N1738(n1738), .N1739(n1739), .N1740(n1740), .N1741(n1741), .N1742(n1742), .N1743(n1743), .N1744(n1744), .N1745(n1745), .N1746(n1746), .N1747(n1747), .N1748(n1748), .N1749(n1749), .N1750(n1750), .N1751(n1751), .N1752(n1752), .N1753(n1753), .N1754(n1754), .N1755(n1755), .N2724(n2724), .N2725(n2725), .N2726(n2726), .N2727(n2727), .N2728(n2728), .N2729(n2729), .N2730(n2730), .N2731(n2731), .N2732(n2732), .N2733(n2733), .N2734(n2734), .N2735(n2735), .N2736(n2736), .N2737(n2737), .N2738(n2738), .N2739(n2739), .N2740(n2740), .N2741(n2741), .N2742(n2742), .N2743(n2743), .N2744(n2744), .N2745(n2745), .N2746(n2746), .N2747(n2747), .N2748(n2748), .N2749(n2749), .N2750(n2750), .N2751(n2751), .N2752(n2752), .N2753(n2753), .N2754(n2754), .N2755(n2755));

integer i=0;
always @ (posedge clk) begin
	vec = input_vec_mem[i];
	$monitor(vec);
	i = i + 1;

end

always @ (negedge clk)begin
	$fdisplay ( fh_w, n1724, n1725, n1726, n1727, n1728, n1729, n1730, n1731, n1732, n1733, n1734, n1735, n1736, n1737, n1738, n1739, n1740, n1741, n1742, n1743, n1744, n1745, n1746, n1747, n1748, n1749, n1750, n1751, n1752, n1753, n1754, n1755, n2724, n2725, n2726, n2727, n2728, n2729, n2730, n2731, n2732, n2733, n2734, n2735, n2736, n2737, n2738, n2739, n2740, n2741, n2742, n2743, n2744, n2745, n2746, n2747, n2748, n2749, n2750, n2751, n2752, n2753, n2754, n2755);
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
