#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long;


my $comment;
my $bleh;

GetOptions ('comment=s' => \$comment,
            'bleh' => \$bleh,
            );


printf "comment:" . "\t$comment\n";
