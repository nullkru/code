#!/usr/bin/perl

use strict;
use warnings;

our(@lines, $file);

$file = "/etc/passwd";

open(INFO, $file); # file öffnen
@lines = <INFO>;
close(INFO);
print @lines;
