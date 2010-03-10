#!/usr/bin/perl

# global config
$eth = "eth1";
$iwlist = "/usr/sbin/iwlist $eth scan";
$iwconfig ="/usr/sbin/iwconfig $eth";
$dhcp = "/sbin/dhclient";

our($iwlist, @list, $eth, $iwconfig, $dhcp, );

use strict;
use warnings;
use Getopt::Long;

my $help = 0;
my $essid = " ";
my $autoget = "0";

GetOptions ('scan' => sub { scan(); },
            'help' => \$help,
            'essid=s' => \$essid,
            'autoget' => \$autoget,
            'conf' => sub { conf_eth(); },
           );



sub scan
{
    @list = `$iwlist`;
    my $line;
    foreach $line (@list) {
        if($line =~ m/ESSID/) {
            printf "$line";
            }
        if($line =~ m/Quality/) {
            printf "$line\n";
        }
        }
}

sub conf_eth
{
      if($essid eq " ") {
          printf 'please set a valid essid with -e <essid>'."\n";
          exit(0);
          } 
      else {
      `$iwconfig essid $essid`;
      `$dhcp $eth`;
      printf "done!\n";
      }
}

sub autoconf
{
	
}


if ($help == "1") {
printf " Usage: kwlanutil <option> [moreoptions]
        scan | s     scans for networks
        essid | e    set the ESSID variable and try to get an ip via dhcp 
        autoget | a  try automatical to get a network connection
        conf | c     use it with -e to get auto ip from a dhcp server( kwlanutil -e essid -c ) 
";
}

