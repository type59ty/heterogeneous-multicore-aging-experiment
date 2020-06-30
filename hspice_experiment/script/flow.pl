#!/usr/bin/perl
use strict;
use warnings;

my @benchmark = ("c499", "c499d");
my $num_task = 20;
my $num_pat = 8;
my $mode = "N";

foreach my $bench (@benchmark) {
  system("./gen_input_pattern.pl $bench $num_task $num_pat");
  system("./run_ncverilog.pl $bench $num_task");
  system("./run_input_profile.pl $bench $num_pat $num_task");
  system("./run_hspice.pl $bench $mode |& tee log/run_hspice_$bench.log");
}
