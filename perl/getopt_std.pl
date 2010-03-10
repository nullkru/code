#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Std;


my %opts;



getopts('hb:', \%opts);

help() = $opts{h};
my $blah = $opts{b};

sub help
  {
      printf "help";
  }


printf $blah;
