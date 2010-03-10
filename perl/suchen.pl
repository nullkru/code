#!/usr/bin/perl

my $list = `which`;

$list =~ m/skip/s;

printf $&;



