#!/usr/bin/perl 

use strict;
use warnings;

my $menu = <<HERE_MENUE;

Adresse eingeben     <1>
Adresse suchen       <2>
Adressliste ausgeben <3>
Beenden		     <4>

HERE_MENUE


my $eingabe = 0;

do {
	print $menu;
	chomp ($eingabe = <STDIN>);

	SWITCH: 
	{
		$eingabe == 1 && do { print "Adresse eingeben \n ";
					last SWITCH; };

		$eingabe == 2 && do { print "Adresse suchen \n ";
					last SWITCH; };
		
		$eingabe == 3 && do { print "Adressliste ausgeben \n";
					last SWITCH; };

		$eingabe == 4 && do { print "Beenden \n"; 
					last SWITCH; };
	}

}

while ($eingabe != 4);
