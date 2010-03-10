#!/usr/bin/perl

# array ohne qw
@arr = (1, 2, 3, 4, 5);
printf "ohne qw:".$arr[1]."\n";

# array mit qw(); operator
@array = qw(1 2 3 4 5 6);

printf "mit qw:".$array[1]."\n";;
