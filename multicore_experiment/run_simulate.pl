#!/usr/bin/perl
use strict;
# my @benchmark = ("c17", "c432", "c499", "c1908", "c5315", "c7552");
#my $benchmark_lit = "c432";
#my $benchmark_big = "c432d";
#my $benchmark_lit = "c499";
#my $benchmark_big = "c499d";
my $benchmark_lit = "b14";
my $benchmark_big = "b21";
#my $benchmark_lit = "c1908";
#my $benchmark_big = "c1908d";
#policy:
# 0 => symmetric
# 1 => asymmetric
# 2 => symmetric migration
# 3 => asymmetric migration 

if (-d "result/big_little/") {
    system("rm -rf /home/forest/experiment/new_multicore_experiment/result/big_little/${benchmark_lit}_${benchmark_big}");
}

#system("./simulate_parameter.pl $benchmark_big $benchmark_lit 0 &");
#system("sleep 1s");
#system("./simulate_parameter.pl $benchmark_big $benchmark_lit 1 &");
#system("sleep 1s");
#
system("./simulate_parameter.pl $benchmark_big $benchmark_lit 2 &");
system("sleep 1s");
system("./simulate_parameter.pl $benchmark_big $benchmark_lit 3 &");
system("sleep 1s");

#system("./simulate_parameter.pl $benchmark_big $benchmark_lit 4 &");
#system("sleep 1s");
#
#system("./simulate_parameter.pl $benchmark_big $benchmark_lit 5 &");
#system("sleep 1s");

exit(0);

