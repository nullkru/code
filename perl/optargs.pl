#!/usr/bin/perl 

use strict;
use warnings;

# parse the command line

my ($help);
my ($func);
my ($blah);

&GetArgs(\@ARGV,  \$help, \$func, \$blah);


sub GetArgs {
    my ($args) = shift;    # command line args
    my  ($help) = shift;    # help
    my ($func) = shift;    # function
    my ($blah) = shift;    # blah function
    
    # Defaults
    $$func = 0;
    
    # parse the command line arguments
    my $done = 0;
    while( ! $done ) {
        SWITCH: {
              if ($$args[0] eq "-h") {
                  printf "help \n";
                  exit(0);
                  }
            
            $$func = 1, last SWITCH
              if ($$args[0] eq "-f");
            
            if ($$args[0] eq "-b") {
                printf "blahfunction\n";
                }
            }
        $done = 1;
        }
    shift @$args if (! $done);
    }


