#!/usr/bin/perl

use strict;
use warnings;

our(@lines, $file);

$file = "/etc/passwd";

open(INFO, $file); # file �ffnen
@lines = <INFO>;
close(INFO);
print @lines;
