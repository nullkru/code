#!/usr/bin/perl -w

use strict;

my @array = ("a", "b", "c", "d", "e");

# first with a foreach...

foreach (1..@array) {
	print "$_ $array[$_ - 1]\n";
}

# next with a C-like for loop

my $i;
my $count;

for ($i = 0; $i <= $#array; $i++) {
	$count = $i + 1;
	print "$count $array[$i]\n";
}

# now a hash

my %colours = (
	"red"		=>	"fire",
	"yellow"	=>	"daffodils",
	"green"		=>	"leaves",
	"blue"		=>	"ocean",
);

foreach (keys %colours) {
	print "$_ $colours{$_}\n";
}
