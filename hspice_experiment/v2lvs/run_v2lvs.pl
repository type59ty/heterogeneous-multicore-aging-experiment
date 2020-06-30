#!/usr/bin/perl 
# Program: run_v2lvs.pl
# Author: Kun-Wei Chiu
# Last Update: 2017/02/16
# example: ./run_benchmark ur_input_dir_name
# warning: Don't forget change current shell to tcsh firstly !
use strict;

my $input_dir;
my @read;
my @input_files;
my @output_files;
my $output_file;

$ARGV[0] = "isca85_v";
opendir (DIR, $ARGV[0]) or die "can't open the directory !\n";
@read = readdir (DIR); 

# put .v file_name into @input_files
foreach (@read) {
 next if (substr($_,0,1) eq ".");
 print "$_\n";
 push (@input_files,$_);
 }

# do v2lvs and output to v2lvs_result/.sp
print "\n";

# if v2lvs doesn't exist, make the dir.
if (-e "v2lvs_result") { }
else {
	mkdir ("v2lvs_result", 0755);
}

foreach (@input_files) {
 $output_file = $_;
 $output_file =~ s/\.v$/.sp/;
 system("v2lvs -v $ARGV[0]/$_ -o v2lvs_result/$output_file");
 #print	"$output_file\n";
 }

#closedir DIR;

