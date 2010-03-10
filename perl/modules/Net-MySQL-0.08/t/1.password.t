use Test;
BEGIN { plan tests => 4 };
use Net::MySQL;

ok(Net::MySQL::Password->scramble('', 'nextsalt', 0) eq '');
ok(Net::MySQL::Password->scramble('', 'newsalt',  1) eq '');
ok(Net::MySQL::Password->scramble('password', 'saltcode', 0) eq '\\WBDNZ\\@');
ok(Net::MySQL::Password->scramble('yourpassword', 'nextsalt', 1) eq 'ZKBTUFLS');