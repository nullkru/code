#!/usr/bin/perl

use strict;
use warnings;

my $blah = "stri strar stringeling <title>blah</title>";

$blah =~ s/<title>(.+?)<\/title>/<blah>$1<\/blah>/gi;

printf "$blah\n"
