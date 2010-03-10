#!/usr/bin/perl
@zeilen = `perldoc -u -f atan2`;
foreach (@zeilen) {
      s/\w<([^>]+)/\U$1/g;
      print;
    }
