#!/usr/bin/perl
use strict;
use warnings;
use Net::FTP;


# guest username and password for /tmp
# feel free to use
my $user = "web497f5";
my $passwd = "guests";


if(!defined($ARGV[0])) {
  die "usage: paster <filetopaste>";
  exit(0);
  }

my $ftp = Net::FTP->new("chao.ch", Debug => 0)
or die "Cannot connect to host: $@";

$ftp->login("$user","$passwd");
$ftp->put("$ARGV[0]")
  or die "Cannot put file", $ftp->message;

printf "url: http://chao.ch/tmp/".$ARGV[0]."\n";