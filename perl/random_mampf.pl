#!/usr/bin/perl

use strict;
use warnings;
use Term::ANSIColor;

my @essen = ("pavette", "fondue", "reis", "kuchen", "salz fl��ten",);
printf "Soll ich etwas zu essen f�r dich ausw�hlen [y/n]\n";

our($answer, );
printf "answer: ";
$answer = <stdin>;

if($answer =~ m/y|Y/) {
    printf "ok ich waehle fuer dich\n"; 
    sleep 3;

    my $bleh = $essen[rand($#essen + 1)];

    printf "und sage mach:" .  colored (" $bleh ", 'red bold') ."du st�ck\n";

    }
else {
    exit(0);
}
