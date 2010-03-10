use strict;
use warnings;

use Digest::MD5 qw(md5_hex);

my $blah = "bleh";

print md5_hex($blah)."\n";


