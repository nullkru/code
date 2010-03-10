#!/usr/bin/perl

printf "ohne standart var benutze \$i \n";
foreach $i (2, 6, 7, 1) {
    printf $i."\n";
    }

printf "mit standart var \$_ \n";
foreach (2, 4, 6, 7, 8) {
    printf $_."\n";
    }
