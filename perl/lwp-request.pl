#!/usr/bin/perl

use strict;
use warnings;
use LWP;
my $ua = LWP::UserAgent->new;

my $response = $ua->get('http://cp.chao.ch/paster.php?file=true');

if($response->is_success) {
	print $response->content;
}
