#!/usr/bin/perl

use strict;
use warnings;

my @task_list = (1..20);
my $len = 20;

my @big_task = (1,5,7,8,9,11,15,17,18,19);
my @lit_task = (2,3,4,6,10,12,13,14,16,20);

my $n;
my @cursor1;
my @cursor2;
my @c_task;
my @nc_task;

my @ct_rate = (0.2, 0.4, 0.6);
# my @ct_rate = (0.2);

open (FILE, ">test_env");

sub checkDiff {
    @nc_task = ();
    my %count;
    foreach my $e (@c_task, @task_list) {
        $count{$e}++;
    }
    foreach my $e (keys %count) {
        if ($count{$e} < 2) {
            push @nc_task, $e;
        }
    }
}

sub inc1 {
    # for (my $i=0; $i<$n; $i++) {
    for (my $i=0; $i<$n/2; $i++) {
        my $current_cur_idx = $n/2 - $i - 1;
        my $current_cur = $cursor1[$current_cur_idx];

        # if ($current_cur < $len - $i - 1) {
        if ($current_cur < 10 - $i - 1) {
            $cursor1[$current_cur_idx] = $cursor1[$current_cur_idx] + 2;
            for (my $j=1; ($current_cur_idx + $j)<$n; $j++) {
                $cursor1[$current_cur_idx + $j] = $cursor1[$current_cur_idx] + $j;
            }
            return 1;
        }
    }
    return 0;
}
sub inc2 {
    # for (my $i=0; $i<$n; $i++) {
    for (my $i=0; $i<$n/2; $i++) {
        my $current_cur_idx = $n/2 - $i - 1;
        my $current_cur = $cursor2[$current_cur_idx];

        # if ($current_cur < $len - $i - 1) {
        if ($current_cur < 10 - $i - 1) {
            $cursor2[$current_cur_idx] = $cursor2[$current_cur_idx] + 2;
            for (my $j=1; ($current_cur_idx + $j)<$n; $j++) {
                $cursor2[$current_cur_idx + $j] = $cursor2[$current_cur_idx] + $j;
            }
            return 1;
        }
    }
    return 0;
}

sub randpick {
    my $max = shift;
    my $need = shift;
    return @{[sort{rand()>0.5}(0..$max)]}[1..$need];
}

sub getResult {
    my @data;
    my @tmp1;
    my @tmp2;
    my @idx1;
    my @idx2;
    # for (my $i=0; $i<$n; $i++) {
    #     $data[$i] = $task_list[ $cursor[$i] ];
    # }

    # half from big 
    @idx1 = &randpick(9,$n/2);
    for (my $i=0; $i<$n/2; $i++) {
        $tmp1[$i] = $big_task[ $idx1[$i] ];
    }

    @idx2 = &randpick(9,$n/2);
    for (my $i=0; $i<$n/2; $i++) {
        $tmp2[$i] = $lit_task[ $idx2[$i] ];
    }

    @data = (@tmp1, @tmp2);
    return @data;
}

foreach my $rate (@ct_rate) {
    print FILE "\n\n";
    print FILE "# $rate\n";
    my $round = 0;
    $n = $len * $rate;
    @cursor1 = (0..($n/2-1));
    @cursor2 = (0..($n/2-1));
    my @c1 = ();
    my @c2 = ();
    @c_task = ();
    @nc_task = ();

    do {
        @c_task = &getResult();
        # @c1 = &getResult();
        # @c2 = &getResult();
        # @c_task = (@c1, @c2);

        &checkDiff(); 
        @c_task  = sort { $a <=> $b } @c_task;
        @nc_task = sort { $a <=> $b } @nc_task;
        print FILE "round $round\n";
        print FILE join(',', @c_task), "\n";
        print FILE join(',', @nc_task), "\n";
        print FILE "\n";

        if ($round == 1000) {
            next;
        }
        # &inc();
        $round++;
    # } while ((&inc1() && &inc2()));
    } while (1);
}

close(FILE);









