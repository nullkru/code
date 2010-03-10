#!/usr/bin/perl

use strict;
use warnings;

use LWP;


my $url = "http://cp.chao.ch/paster.php?file=true";

my $ua = LWP::UserAgent->new;

my $post = $ua->post(
	$url,
	[
		'ufile' => ["/home/kru/rip.jpg"],
		'pasted' => 'true',
	],
	
	'content_type' => 'multipart/form-data'
);

print $post->content;
