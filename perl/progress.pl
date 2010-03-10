#!/usr/bin/perl

use strict;
use warnings;


use Term::ProgressBar;

my $max = 10000;

my $progress = Term::ProgressBar->new($max);

for (0..$max)
{
	my $is_power = 0;
	for(my $i = 0; 2**$i <= $_; $i++)
	{
		$is_power = 1
		if 2**$i == $_;
	}
	$progress->update($_)
}
