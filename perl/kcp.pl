#!/usr/bin/perl

#
# by kru<@choa.ch> [http://chao.ch]
# date: 10.05.2007
#
# paster script for http://cp.chao.ch
#
use strict;
use warnings;

use LWP;
use File::Basename;
use Getopt::Long;

#config vars
my $pasteurl = "http://cp.chao.ch/"; #eg. http://cp.chao.ch/
#my $pasteurl = "http://cp.figg.ch/";
my $filepasteurl = "http://cp.chao.ch/paster.php?file=true"; # blah
#my $filepasteurl = "http://cp.figg.ch/index.php?file=true";
my $pastedir = "p/"; #eg /pastes

#global vars
our ($content, $paste, $post );
my $sname = basename($0); # script name
my $version = "0.1";


printf "$sname: -h for help, ctrl+d to send or ctrl+c to cancel\n";


# for Getopt::Long switchs
GetOptions (
	'help' => sub { help() },
);

sub help
{
printf <<EOT;
$sname info:\n
options:
	-h\t help
usage:
	read from stdin:
	cat <plain text file> | $sname
	tail /var/log/message.log | $sname

	paste a file:
	$sname <file>

more help:
	http://chao.ch
EOT
exit(0);
}

#send to form 
my $ua = LWP::UserAgent->new;
$ua->agent('kcp/'.$version);

# text or code
if( ! $ARGV[0] )
{
	
	# read from stdin
	while( <STDIN> )
	{
		$content .= $_;
	}
	
	if( ! $content ) 
	{ 
		printf "don't paste nothing, noob!!!\n"; # specially for cy_
       		exit(0);
	};	
	
	$post = $ua->post( 
		$pasteurl, 
		[
			'content' => $content,
			'pasted' => 'true',
		],
			'content_type' => 'multipart/form-data'
	);
}
else
{
	my $file =  $ARGV[0];
	$post = $ua->post(
		$filepasteurl,
		[
			'ufile' => [ $file ],
			'pasted' => 'true',
		],
		'content_type' => 'multipart/form-data'
	);
}

# get the url 
my $htmlout =  $post->content;
if( $htmlout )
{
	$htmlout =~ s/URL: <a href=\"(.+?)\">//gmi;
	$paste = $1;
}
print "url: ".$paste."\n";	



