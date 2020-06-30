#!/usr/bin/perl
use strict;
use warnings;
use File::Copy;
use Switch;


sub ltrim { my $s = shift; $s =~ s/^\s+//; return $s };
sub rtrim { my $s = shift; $s =~ s/\s+$//; return $s };
sub trim  { my $s = shift; $s =~ s/^\s+|\s+$//g; return $s };


my $bench = "b14_b21";
#my $bench = "c1908_c1908d";
#my $bench = "c499_c499d";
#my $bench = "c432_c432d";

my $base_path = "/home/forest/experiment/new_multicore_experiment/result/big_little/$bench";
my $output_path = "/home/forest/experiment/new_multicore_experiment/parse_result";
my $output_file;

if (-e "$output_path/result.csv") {
    move "$output_path/result.csv", "$output_path/backup_result.csv"
}
if (-e "$output_path/err.log") {
    unlink "$output_path/err.log";
}
# my $life = 0;
# my $eng = 0;
# my $tot_life = 0;
# my $tot_eng = 0;
# my $tot_pow = 0;
# my @BC  = ($tot_life, $tot_eng, $tot_pow);
# my @LC  = ($tot_life, $tot_eng, $tot_pow);
# my @TOT = ($tot_life, $tot_eng, $tot_pow);
# 
# 
# my @sym      = (@BC, @LC, @TOT);
# my @asym     = (@BC, @LC, @TOT);
# my @sym_mig  = (@BC, @LC, @TOT);
# my @asym_mig = (@BC, @LC, @TOT);

sub cvt_age {
    my $op_time = shift;
    my $month = 0;
    my $year = 0;
    if ($op_time =~ /.+y.+/) {
        my @op = split('_', $op_time);
        $year = substr $op[0], 0, -1;
        $month = substr $op[1], 0, -1;
        
    } else {
        $month = substr $op_time, 0, -1;
    }
    my $tot = $year * 12 + $month;
    return $tot;
}

open(my $new_env, ">$output_path/new_env");

open(my $err_file, ">>$output_path/err.log") or die $!;
open(my $bad_file, ">$output_path/bad.log") or die $!;
opendir (DIR, $base_path) or die $!;
# 4 8 12
while (my $ratio = readdir(DIR)) {
    if ($ratio eq '.' or $ratio eq '..') {
        next;
    }
    my $round = 0;
    print $new_env "# $ratio\n";

    opendir (SDIR, "$base_path/$ratio") or die $!;
    my @sym      = ();
    my @asym     = ();
    my @sym_mig  = ();
    my @asym_mig = ();
    my @spare = ();
    my @spare_mig = ();
    my $num_env = 0;
    my $full = ();
    # TASK_1_2_3_4 ...
    while (my $env = readdir(SDIR)) {
        if ($env eq '.' or $env eq '..') {
            next;
        }

        # gen new env
        my @all_task = (1..20);
        my @c_task = split('_', $env);
        my @nc_task;
        my $cap =  substr $c_task[0], 4, 2;
        $cap = &rtrim($cap); 
        shift @c_task;
        unshift (@c_task, $cap);
        
        foreach my $tk (@all_task) {
            if ( grep(/^$tk$/, @c_task) ) {
                next;
            } else {
                push(@nc_task, $tk);
            }
        }

        # print "$cap @t_task ";
        # print "\n";
        print $new_env "round $round\n";
        # print $new_env "@c_task \n";
        print $new_env join(',', @c_task);
        print $new_env "\n";
        print $new_env join(',', @nc_task);
        print $new_env "\n";
        $round++;
        # foreach my $tk () {
        #     if ( any() )
        # }

        ###################
        

        opendir (SSDIR, "$base_path/$ratio/$env") or die $!;
        $full = "$base_path/$ratio/$env";

        if ((!-e "$full/Sym.log") || (!-e "$full/Asym.log") || (!-e "$full/Sym_mig.log") || (!-e "$full/Asym_mig.log")) {
            print $err_file "$base_path/$ratio/$env\n";
            next;
        }

        $num_env += 1;

        my $sym_tot = 0;
        my $asym_tot = 0;
        my $sym_m_tot = 0;
        my $asym_m_tot = 0;
        # each policy
        while (my $file = readdir(SSDIR)) {
            if ($file eq '.' or $file eq '..' or $file =~ 'csv$') {
                next;
            }
            open(my $fh, "$base_path/$ratio/$env/$file") or die $!;
            # each file
            my $v = 0 ;

            while (my $row = <$fh>) {
                chomp $row;
                # print "$row\n";
                my @value = split(',', $row);
                my $str_age  = $value[0]; 
                my $life = $value[1];
                my $eng  = $value[2];
                my $age = &cvt_age($str_age);
                switch($file) {
                    case "Sym.log" {
                        $sym[$v][0] += $life;
                        $sym[$v][1] += $eng;
                        $sym[$v][3] += $age;
                        if ($v == 2) {
                            $sym_tot = $life;
                        }
                    }
                    case "Asym.log" {
                        $asym[$v][0] += $life;
                        $asym[$v][1] += $eng;
                        $asym[$v][3] += $age;
                        if ($v == 2) {
                            $asym_tot = $life;
                        }
                    }
                    case "Sym_mig.log" {
                        $sym_mig[$v][0] += $life;
                        $sym_mig[$v][1] += $eng;
                        $sym_mig[$v][3] += $age;
                        if ($v == 2) {
                            $sym_m_tot = $life;
                        }
                    }
                    case "Asym_mig.log" {
                        $asym_mig[$v][0] += $life;
                        $asym_mig[$v][1] += $eng;
                        $asym_mig[$v][3] += $age;
                        if ($v == 2) {
                            $asym_m_tot = $life;
                        }
                    }   
                    case "Spare.log" {
                        $spare[$v][0] += $life;
                        $spare[$v][1] += $eng;
                        $spare[$v][3] += $age;
                        # if ($v == 2) {
                        #     $asym_m_tot = $life;
                        # }
                    }   
                    case "Spare_mig.log" {
                        $spare_mig[$v][0] += $life;
                        $spare_mig[$v][1] += $eng;
                        $spare_mig[$v][3] += $age;
                        # if ($v == 2) {
                        #     $asym_m_tot = $life;
                        # }
                    }   
                }
                $v += 1;
                # if ($v == 3) {
                #     next;
                # }
            }
            close($fh); 

        }
        # if (($sym_m_tot > $asym_m_tot) || ($sym_tot > $asym_tot)){
        # if ( ($sym_m_tot > $asym_m_tot) || ($sym_tot > $asym_tot) ){
        if ($sym_m_tot > $asym_m_tot){
            print $bad_file "$env\n";
        }
        if ($sym_tot > $sym_m_tot) {
            # print $bad_file "$env\n";
        }
        closedir(SSDIR);

        print $new_env "\n";

    }
    print "$ratio: $num_env\n";
    closedir(SDIR);
    if ($num_env == 0) {
        next;
    }
    my $tmp1;
    my $tmp2;
    for (my $i = 0; $i < 4; $i++) {
        $sym[$i][0]      /= $num_env;
        $sym[$i][1]      /= $num_env;
        $sym[$i][2]       = $sym[$i][1] / $sym[$i][0];

        $asym[$i][0]     /= $num_env;
        $asym[$i][1]     /= $num_env;
        $asym[$i][2]      = $asym[$i][1] / $asym[$i][0];

        $sym_mig[$i][0]  /= $num_env;
        $sym_mig[$i][1]  /= $num_env;
        $sym_mig[$i][2]   = $sym_mig[$i][1] / $sym_mig[$i][0];

        $asym_mig[$i][0] /= $num_env;
        $asym_mig[$i][1] /= $num_env;
        $asym_mig[$i][2]  = $asym_mig[$i][1] / $asym_mig[$i][0];

        $spare[$i][0] /= $num_env;
        $spare[$i][1] /= $num_env;
        $spare[$i][2]  = $spare[$i][1] / $spare[$i][0];

        $spare_mig[$i][0] /= $num_env;
        $spare_mig[$i][1] /= $num_env;
        $spare_mig[$i][2]  = $spare_mig[$i][1] / $spare_mig[$i][0];
        # if ($i==2) {
        #     print "$sym[$i][0] \n";
        #     print "$asym[$i][0] \n"
        # }
        $sym[$i][3]      /= $num_env;
        $tmp1 = int(int($sym[$i][3])/12);
        $tmp2 = int(int($sym[$i][3])%12);
        if ($tmp1 > 0) {
            $sym[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $sym[$i][3] = "${tmp2}m";
        }

        $asym[$i][3]     /= $num_env;
        $tmp1 = int(int($asym[$i][3])/12);
        $tmp2 = int(int($asym[$i][3])%12);
        if ($tmp1 > 0) {
            $asym[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $asym[$i][3] = "${tmp2}m";
        }

        $sym_mig[$i][3]  /= $num_env;
        $tmp1 = int(int($sym_mig[$i][3])/12);
        $tmp2 = int(int($sym_mig[$i][3])%12);
        if ($tmp1 > 0) {
            $sym_mig[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $sym_mig[$i][3] = "${tmp2}m";
        }

        $asym_mig[$i][3] /= $num_env;
        $tmp1 = int(int($asym_mig[$i][3])/12);
        $tmp2 = int(int($asym_mig[$i][3])%12);
        if ($tmp1 > 0) {
            $asym_mig[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $asym_mig[$i][3] = "${tmp2}m";
        }

        $spare[$i][3] /= $num_env;
        $tmp1 = int(int($spare[$i][3])/12);
        $tmp2 = int(int($spare[$i][3])%12);
        if ($tmp1 > 0) {
            $spare[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $spare[$i][3] = "${tmp2}m";
        }

        $spare_mig[$i][3] /= $num_env;
        $tmp1 = int(int($spare_mig[$i][3])/12);
        $tmp2 = int(int($spare_mig[$i][3])%12);
        if ($tmp1 > 0) {
            $spare_mig[$i][3] = "${tmp1}y_${tmp2}m";
        } else {
            $spare_mig[$i][3] = "${tmp2}m";
        }
        
    }


    # write the result of each ratio
    # open (my $OFS, "> $output_path/$ratio/result_$ratio.csv") or die $!;
    open (my $OFS, ">> $output_path/result.csv") or die $!;
    # write BC, LC, TOT's lifetime and energy respectly

    # origin data  
    print $OFS "$ratio,,,Sym,,,Spare,,,Asym,,,Sym_mig,,,Spare_mig,,,Asym_mig\n";
    print $OFS ",big core,little core,total,big core,little core,total,big core,little core,total,big core,little core,total\n";
    print $OFS "lifetime,$sym[0][0],$sym[1][0],$sym[2][0],$spare[0][0],$spare[1][0],$spare[2][0],$asym[0][0],$asym[1][0],$asym[2][0],$sym_mig[0][0],$sym_mig[1][0],$sym_mig[2][0],$spare_mig[0][0],$spare_mig[1][0],$spare_mig[2][0],$asym_mig[0][0],$asym_mig[1][0],$asym_mig[2][0]\n";
    print $OFS "energy  ,$sym[0][1],$sym[1][1],$sym[2][1],$spare[0][1],$spare[1][1],$spare[2][1],$asym[0][1],$asym[1][1],$asym[2][1],$sym_mig[0][1],$sym_mig[1][1],$sym_mig[2][1],$spare_mig[0][1],$spare_mig[1][1],$spare_mig[2][1],$asym_mig[0][1],$asym_mig[1][1],$asym_mig[2][1]\n";
    print $OFS "power   ,$sym[0][2],$sym[1][2],$sym[2][2],$spare[0][2],$spare[1][2],$spare[2][2],$asym[0][2],$asym[1][2],$asym[2][2],$sym_mig[0][2],$sym_mig[1][2],$sym_mig[2][2],$spare_mig[0][2],$spare_mig[1][2],$spare_mig[2][2],$asym_mig[0][2],$asym_mig[1][2],$asym_mig[2][2]\n";
    print $OFS "age     ,$sym[0][3],$sym[1][3],$sym[2][3],$spare[0][3],$spare[1][3],$spare[2][3],$asym[0][3],$asym[1][3],$asym[2][3],$sym_mig[0][3],$sym_mig[1][3],$sym_mig[2][3],$spare_mig[0][3],$spare_mig[1][3],$spare_mig[2][3],$asym_mig[0][3],$asym_mig[1][3],$asym_mig[2][3]\n";


    my $l_base = $sym[2][0];
    my $e_base = $sym[3][1];
    my $p_base = $sym[2][2];
    
    my @sym_n      = ($sym[2][0]/$l_base,          $sym[3][1]/$e_base,        $sym[2][2]/$p_base);
    my @asym_n     = ($asym[2][0]/$l_base,         $asym[3][1]/$e_base,       $asym[2][2]/$p_base);
    my @sym_mig_n  = ($sym_mig[2][0]/$l_base,      $sym_mig[3][1]/$e_base,    $sym_mig[2][2]/$p_base);
    my @asym_mig_n = ($asym_mig[2][0]/$l_base,     $asym_mig[3][1]/$e_base,   $asym_mig[2][2]/$p_base);
    my @spare_n    = ($spare[2][0]/$l_base,        $spare[3][1]/$e_base,      $spare[2][2]/$p_base);
    my @spare_mig_n = ($spare_mig[2][0]/$l_base,   $spare_mig[3][1]/$e_base,  $spare_mig[2][2]/$p_base);

    # normalized total data
    print $OFS "$ratio,Sym,Spare_core,Asym,Sym_mig,Asym_mig\n";
    print $OFS "lifetime, $sym_n[0], $spare_n[0], $asym_n[0], $sym_mig_n[0], $spare_mig_n[0], $asym_mig_n[0]\n"; 
    print $OFS "energy  , $sym_n[1], $spare_n[1], $asym_n[1], $sym_mig_n[1], $spare_mig_n[1], $asym_mig_n[1]\n"; 
    print $OFS "power   , $sym_n[2], $spare_n[2], $asym_n[2], $sym_mig_n[2], $spare_mig_n[2], $asym_mig_n[2]\n"; 
    print $OFS "\n\n\n\n\n";
}
close($new_env);
close($err_file);
closedir(DIR);


