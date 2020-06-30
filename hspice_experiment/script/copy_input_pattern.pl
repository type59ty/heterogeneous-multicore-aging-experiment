#!/usr/bin/perl
# Proram: gen_input_pattern
# Author: Jian-Ting
# Last Update: 2019/09/3
# Objective: generate input pattern 
# $ARGV[0];  # benchmark_name 
# $ARGV[1];  # number_of_task
# $ARGV[2];  # input_vec_length
# output: rand_input_vector_$benchmark_name\_$input_vec_length.out


use strict;
use gen_hspice_header;


# add by Forest on 2019/12/29
sub copy_pat {
	my $fr_input_vec_file_name = shift; #"rand_input_vector.out"
	my $to_input_vec_file_name = shift; #"rand_input_vector.out"
	my $fr_input_vec_length = shift;
	my $fr_input_port = shift;
	my $to_input_port = shift;
    my @fr_vec;
    my @to_vec;

    my $fr_vec_count; 
    my $to_vec_count; 
    
	unless ( open FR_IN_VEC_FH,"<$fr_input_vec_file_name" ) {die "Error : Cannot open the $fr_input_vec_file_name\n";}
    while (my $row = <FR_IN_VEC_FH>) {
        if ($row =~ m/^[0-1].+/) {
            chomp $row;
            push @fr_vec, $row;
        }
    }
    close (FR_IN_VEC_FH);
    for (my $i=0; $i<$fr_input_vec_length; $i+=2) {
        # push @to_vec, "$fr_vec[$i]$fr_vec[$fr_input_vec_length/2+$i]";
        push @to_vec, "$fr_vec[$i]$fr_vec[$i+1]";
    }
	unless ( open TO_IN_VEC_FH,">$to_input_vec_file_name" ) {die "Error : Cannot open the $to_input_vec_file_name\n";}
    print TO_IN_VEC_FH "$to_input_port\n";
    foreach my $vec (@to_vec) {
        print TO_IN_VEC_FH "$vec\n";
    }
    close (TO_IN_VEC_FH);
}


my $fr_benchmark_name = $ARGV[0];
my $to_benchmark_name = $ARGV[1];
my $benchmark_verilog_dir = "./benchmark/isca85_v";
my @fr_input_port;
my @to_input_port;

my $number_of_task = $ARGV[2];
my $input_vec_length = $ARGV[3]; # determine how many input vectors will be generated in the input vec. file

my $input_vec_file_name;
my $trans_input_vec_file_name;
my $input_dir = "input_pattern";

# if dir. hspice_result doesn't exist, make the dir.
if (-e "$input_dir/$to_benchmark_name"){
}
else {
	mkdir("$input_dir/$to_benchmark_name", 0755);
}

# 1) parser
@fr_input_port = parse_verilog_file($benchmark_verilog_dir, $fr_benchmark_name,3); # 3:return input_port
@to_input_port = parse_verilog_file($benchmark_verilog_dir, $to_benchmark_name,3); # 3:return input_port

for (my $i = 0; $i < $number_of_task; $i++ ){
  #generate input vector for you
	# gen_input_vec_file("$input_dir\/$benchmark_name/rand_input_vector_$benchmark_name\_$i.out", $input_vec_length, @input_port);
    copy_pat("$input_dir\/$fr_benchmark_name/rand_input_vector_$fr_benchmark_name\_$i.out","$input_dir\/$to_benchmark_name/rand_input_vector_$to_benchmark_name\_$i.out",$input_vec_length, "@fr_input_port", "@to_input_port");
  #translate input vector for program 
	$trans_input_vec_file_name = transpose_input_vec_file($to_benchmark_name, "rand_input_vector_$to_benchmark_name\_$i.out");
}

#generate the idle input vectors for idle power
my $index = $number_of_task-1;
open my $file, '<', "$input_dir\/$to_benchmark_name/rand_input_vector_$to_benchmark_name\_$index.out";
open my $wfile, '>', "$input_dir\/$to_benchmark_name/rand_input_vector_$to_benchmark_name\_$number_of_task.out";
my $Line = <$file>;
#print $Line;
print $wfile $Line;
$Line = <$file>;
for (my $i = 0; $i < $input_vec_length; $i++ ){
  print $wfile $Line;
	#print $Line;
}
close $wfile;
close $file;
#translate the idle input vector for program
$trans_input_vec_file_name = transpose_input_vec_file($to_benchmark_name, "rand_input_vector_$to_benchmark_name\_$number_of_task.out");



