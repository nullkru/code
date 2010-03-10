#!/usr/bin/perl
# scripted by : kru_
# last modified: 4.3.06
use strict;
use warnings;
use Net::FTP;
use File::Basename;

# guest username and password for /tmp
# feel free to use
my $user = "web497f5";
my $passwd = "guests";

while ( ! $ARGV[0] ) {
    printf "usage: paster <filetopaste>\n";
    exit();
    }

our($ftp);

$ftp = Net::FTP->new("chao.ch", Debug => 0, )
  or die "Cannot connect to host: $@";

$ftp->login("$user","$passwd");
$ftp->binary;


$ftp->put("$ARGV[0]")
  or die "Cannot put file", $ftp->message;

my $file =  basename($ARGV[0]);
printf "url: http://chao.ch/tmp/".$file."\n";

