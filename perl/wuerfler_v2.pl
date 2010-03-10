#!/usr/bin/perl

use strict;
use warnings;
use Term::ANSIColor;

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


printf "Wuerfler!!!! (Beenden mit ctrl + c) $0 <zahl> fuer mehrere wuerfel. \n";

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
