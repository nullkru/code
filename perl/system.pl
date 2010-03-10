#!/usr/bin/perl
#

use strict;
use warnings;

my $var = "blah";
my $blah = exec("echo -n $var  | md5sum | awk '{ print \$1 }'");

print "blah $blah \n";



#print "md5sum from the var $var is: $ENV{'md5sum'} \n";
