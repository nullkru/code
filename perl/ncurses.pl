#!/usr/bin/perl
#
# Copyright (C) 2003 by Virtusa Corporation
# http://www.virtusa.com
#
# Anuradha Ratnaweera
# http://www.linux.lk/~anuradha/
#

use warnings;
use Curses;
use strict;

initscr();
printw("Hello world!");
refresh();
getch();
endwin();
