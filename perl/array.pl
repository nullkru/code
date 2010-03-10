#!/usr/bin/perl

#use strict;
#use warnings;

my @blah = ("miau", "dini", "mer");

my $in = "blah";
my $size = @blah;
printf "size of array:".$size."\n";
printf ${$in}[0]."\n";
printf $blah[0]."\n";
