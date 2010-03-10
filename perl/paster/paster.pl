#!/usr/bin/perl

use strict;
use warnings;

our(@paste,);

while( ! $ARGV[0] )
{
	printf "usage: paster <filetopaste>\n";
	printf "or eg: cat filetopaste | paster\n";
	exit(0);
}

@paste = <>;

print @paste;
