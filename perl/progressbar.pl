#!/usr/bin/perl

use Term::ProgressBar 2.00;

use constant MAX => 100_000;

my $progress = Term::ProgressBar->new(MAX);

for (0..MAX) {
	my $is_power = 0;
		for(my $i = 0; 2**$i <= $_; $i++) {
			$is_power = 1
				if 2**$i == $_;
}

if ( $is_power ) {
	$progress->update($_);
	}
}
