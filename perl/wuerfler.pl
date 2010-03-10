#!/usr/bin/perl

#
# booring "würfel" script for army usage :)
# by kru<@chao.ch> [http://chao.ch]
# date: 26.02.2007
#

use strict;
use warnings;

my @augen = (
	"     
  O  
     \n",

	"O    
     
    O\n",

	"O    
  O  
    O\n",

	"O   O
     
O   O\n",

	"O   O
  O  
O   O\n",

	"O   O
O   O
O   O\n"
);


printf "Wuerfler!!!! (Beenden mit ctrl + c) $0 <n> fuer n wuerfel. \n";

sub wuerfeln 
{
	for (my $i = 1; $i  <= $_[0]; ++$i)
	{
		my $erg = $augen[rand(@augen)];
		printf $erg . "\n-\n";
	}
	
}


my $runde = 1;
while ( <STDIN> =~ "\n")
{
	printf "--- $runde --- \n\n";
	
	if ( ! $ARGV[0] )
	{
		wuerfeln 1
	}
	else
	{
		wuerfeln $ARGV[0]
	}
	++$runde;
}
