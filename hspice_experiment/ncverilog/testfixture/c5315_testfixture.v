`timescale 1ns/10ps

`define cycle 10.0
`define terminate_cycle 400000//200000 // Modify your terminate ycle here

module c5315_testfixture;

`define in_file "c5315/rand_input_vector_c5315_0.out"
`define out_file "c5315/rand_output_vector_c5315_0.out"

parameter vec_width = 178;
parameter vec_length = 7;

reg clk = 0;


reg [vec_width-1:0] input_vec_mem [0:vec_length-1];
reg [vec_width-1:0] vec;

wire n709, n816, n1066, n1137, n1138, n1139, n1140, n1141, n1142, n1143, n1144, n1145, n1147, n1152, n1153, n1154, n1155, n1972, n2054, n2060, n2061, n2139, n2142, n2309, n2387, n2527, n2584, n2590, n2623, n3357, n3358, n3359, n3360, n3604, n3613, n4272, n4275, n4278, n4279, n4737, n4738, n4739, n4740, n5240, n5388, n6641, n6643, n6646, n6648, n6716, n6877, n6924, n6925, n6926, n6927, n7015, n7363, n7365, n7432, n7449, n7465, n7466, n7467, n7469, n7470, n7471, n7472, n7473, n7474, n7476, n7503, n7504, n7506, n7511, n7515, n7516, n7517, n7518, n7519, n7520, n7521, n7522, n7600, n7601, n7602, n7603, n7604, n7605, n7606, n7607, n7626, n7698, n7699, n7700, n7701, n7702, n7703, n7704, n7705, n7706, n7707, n7735, n7736, n7737, n7738, n7739, n7740, n7741, n7742, n7754, n7755, n7756, n7757, n7758, n7759, n7760, n7761, n8075, n8076, n8123, n8124, n8127, n8128;
initial begin
	$readmemb(`in_file, input_vec_mem );
end

always #(`cycle/2) clk = ~clk;

c5315 cc (.N1(vec[177]), .N4(vec[176]), .N11(vec[175]), .N14(vec[174]), .N17(vec[173]), .N20(vec[172]), .N23(vec[171]), .N24(vec[170]), .N25(vec[169]), .N26(vec[168]), .N27(vec[167]), .N31(vec[166]), .N34(vec[165]), .N37(vec[164]), .N40(vec[163]), .N43(vec[162]), .N46(vec[161]), .N49(vec[160]), .N52(vec[159]), .N53(vec[158]), .N54(vec[157]), .N61(vec[156]), .N64(vec[155]), .N67(vec[154]), .N70(vec[153]), .N73(vec[152]), .N76(vec[151]), .N79(vec[150]), .N80(vec[149]), .N81(vec[148]), .N82(vec[147]), .N83(vec[146]), .N86(vec[145]), .N87(vec[144]), .N88(vec[143]), .N91(vec[142]), .N94(vec[141]), .N97(vec[140]), .N100(vec[139]), .N103(vec[138]), .N106(vec[137]), .N109(vec[136]), .N112(vec[135]), .N113(vec[134]), .N114(vec[133]), .N115(vec[132]), .N116(vec[131]), .N117(vec[130]), .N118(vec[129]), .N119(vec[128]), .N120(vec[127]), .N121(vec[126]), .N122(vec[125]), .N123(vec[124]), .N126(vec[123]), .N127(vec[122]), .N128(vec[121]), .N129(vec[120]), .N130(vec[119]), .N131(vec[118]), .N132(vec[117]), .N135(vec[116]), .N136(vec[115]), .N137(vec[114]), .N140(vec[113]), .N141(vec[112]), .N145(vec[111]), .N146(vec[110]), .N149(vec[109]), .N152(vec[108]), .N155(vec[107]), .N158(vec[106]), .N161(vec[105]), .N164(vec[104]), .N167(vec[103]), .N170(vec[102]), .N173(vec[101]), .N176(vec[100]), .N179(vec[99]), .N182(vec[98]), .N185(vec[97]), .N188(vec[96]), .N191(vec[95]), .N194(vec[94]), .N197(vec[93]), .N200(vec[92]), .N203(vec[91]), .N206(vec[90]), .N209(vec[89]), .N210(vec[88]), .N217(vec[87]), .N218(vec[86]), .N225(vec[85]), .N226(vec[84]), .N233(vec[83]), .N234(vec[82]), .N241(vec[81]), .N242(vec[80]), .N245(vec[79]), .N248(vec[78]), .N251(vec[77]), .N254(vec[76]), .N257(vec[75]), .N264(vec[74]), .N265(vec[73]), .N272(vec[72]), .N273(vec[71]), .N280(vec[70]), .N281(vec[69]), .N288(vec[68]), .N289(vec[67]), .N292(vec[66]), .N293(vec[65]), .N299(vec[64]), .N302(vec[63]), .N307(vec[62]), .N308(vec[61]), .N315(vec[60]), .N316(vec[59]), .N323(vec[58]), .N324(vec[57]), .N331(vec[56]), .N332(vec[55]), .N335(vec[54]), .N338(vec[53]), .N341(vec[52]), .N348(vec[51]), .N351(vec[50]), .N358(vec[49]), .N361(vec[48]), .N366(vec[47]), .N369(vec[46]), .N372(vec[45]), .N373(vec[44]), .N374(vec[43]), .N386(vec[42]), .N389(vec[41]), .N400(vec[40]), .N411(vec[39]), .N422(vec[38]), .N435(vec[37]), .N446(vec[36]), .N457(vec[35]), .N468(vec[34]), .N479(vec[33]), .N490(vec[32]), .N503(vec[31]), .N514(vec[30]), .N523(vec[29]), .N534(vec[28]), .N545(vec[27]), .N549(vec[26]), .N552(vec[25]), .N556(vec[24]), .N559(vec[23]), .N562(vec[22]), .N566(vec[21]), .N571(vec[20]), .N574(vec[19]), .N577(vec[18]), .N580(vec[17]), .N583(vec[16]), .N588(vec[15]), .N591(vec[14]), .N592(vec[13]), .N595(vec[12]), .N596(vec[11]), .N597(vec[10]), .N598(vec[9]), .N599(vec[8]), .N603(vec[7]), .N607(vec[6]), .N610(vec[5]), .N613(vec[4]), .N616(vec[3]), .N619(vec[2]), .N625(vec[1]), .N631(vec[0]), .N709(n709), .N816(n816), .N1066(n1066), .N1137(n1137), .N1138(n1138), .N1139(n1139), .N1140(n1140), .N1141(n1141), .N1142(n1142), .N1143(n1143), .N1144(n1144), .N1145(n1145), .N1147(n1147), .N1152(n1152), .N1153(n1153), .N1154(n1154), .N1155(n1155), .N1972(n1972), .N2054(n2054), .N2060(n2060), .N2061(n2061), .N2139(n2139), .N2142(n2142), .N2309(n2309), .N2387(n2387), .N2527(n2527), .N2584(n2584), .N2590(n2590), .N2623(n2623), .N3357(n3357), .N3358(n3358), .N3359(n3359), .N3360(n3360), .N3604(n3604), .N3613(n3613), .N4272(n4272), .N4275(n4275), .N4278(n4278), .N4279(n4279), .N4737(n4737), .N4738(n4738), .N4739(n4739), .N4740(n4740), .N5240(n5240), .N5388(n5388), .N6641(n6641), .N6643(n6643), .N6646(n6646), .N6648(n6648), .N6716(n6716), .N6877(n6877), .N6924(n6924), .N6925(n6925), .N6926(n6926), .N6927(n6927), .N7015(n7015), .N7363(n7363), .N7365(n7365), .N7432(n7432), .N7449(n7449), .N7465(n7465), .N7466(n7466), .N7467(n7467), .N7469(n7469), .N7470(n7470), .N7471(n7471), .N7472(n7472), .N7473(n7473), .N7474(n7474), .N7476(n7476), .N7503(n7503), .N7504(n7504), .N7506(n7506), .N7511(n7511), .N7515(n7515), .N7516(n7516), .N7517(n7517), .N7518(n7518), .N7519(n7519), .N7520(n7520), .N7521(n7521), .N7522(n7522), .N7600(n7600), .N7601(n7601), .N7602(n7602), .N7603(n7603), .N7604(n7604), .N7605(n7605), .N7606(n7606), .N7607(n7607), .N7626(n7626), .N7698(n7698), .N7699(n7699), .N7700(n7700), .N7701(n7701), .N7702(n7702), .N7703(n7703), .N7704(n7704), .N7705(n7705), .N7706(n7706), .N7707(n7707), .N7735(n7735), .N7736(n7736), .N7737(n7737), .N7738(n7738), .N7739(n7739), .N7740(n7740), .N7741(n7741), .N7742(n7742), .N7754(n7754), .N7755(n7755), .N7756(n7756), .N7757(n7757), .N7758(n7758), .N7759(n7759), .N7760(n7760), .N7761(n7761), .N8075(n8075), .N8076(n8076), .N8123(n8123), .N8124(n8124), .N8127(n8127), .N8128(n8128));

integer i=0;
always @ (posedge clk) begin
	vec = input_vec_mem[i];
	$monitor(vec);
	i = i + 1;

end

always @ (negedge clk)begin
	$fdisplay ( fh_w, n709, n816, n1066, n1137, n1138, n1139, n1140, n1141, n1142, n1143, n1144, n1145, n1147, n1152, n1153, n1154, n1155, n1972, n2054, n2060, n2061, n2139, n2142, n2309, n2387, n2527, n2584, n2590, n2623, n3357, n3358, n3359, n3360, n3604, n3613, n4272, n4275, n4278, n4279, n4737, n4738, n4739, n4740, n5240, n5388, n6641, n6643, n6646, n6648, n6716, n6877, n6924, n6925, n6926, n6927, n7015, n7363, n7365, n7432, n7449, n7465, n7466, n7467, n7469, n7470, n7471, n7472, n7473, n7474, n7476, n7503, n7504, n7506, n7511, n7515, n7516, n7517, n7518, n7519, n7520, n7521, n7522, n7600, n7601, n7602, n7603, n7604, n7605, n7606, n7607, n7626, n7698, n7699, n7700, n7701, n7702, n7703, n7704, n7705, n7706, n7707, n7735, n7736, n7737, n7738, n7739, n7740, n7741, n7742, n7754, n7755, n7756, n7757, n7758, n7759, n7760, n7761, n8075, n8076, n8123, n8124, n8127, n8128);
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
