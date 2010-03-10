#!/usr/bin/perl

use strict;
use warnings;

use Net::MySQL; # mysql connector version 0.8.  0.9 funktioniert nicht bug!
use Digest::MD5 qw(md5_hex);


if ( ! $ARGV[0] )
{
	print "usage: $0 <pwfile> \n";
	exit 0;
}

our ($string, $file, @lines, $md5sum);

$file = $ARGV[0];

open(READFILE, $file);

@lines = <READFILE>;

#mysql connection

my $mysql = Net::MySQL->new(
	#hostname => 'localhost',
	database => 'hashtable',
	user => 'root',
	password => ''
);


my $i = 1;
foreach $string (@lines)
{
	
	my $groesse = scalar(@lines);
	chomp($string); #newline bei $string entfernen
	#create md5sum here
	$md5sum = md5_hex($string);
		
	print  $i."\/".$groesse.": ".$string ." " . $md5sum . "\n";
	# write in to database
	$mysql->query("INSERT INTO rainbow (pw, hash) VALUES ('$string', '$md5sum')");
	++$i;
}

$mysql->close;
