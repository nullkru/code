#!/usr/bin/perl

use Gtk2 '-init';

my $window = Gtk2::Window->new;
$window->set_title ("Hello world");
$window->signal_connect (destroy => sub { Gtk2->main_quit; });

my $button = Gtk2::Button->new("Hello world!");
$button->signal_connect(clicked=> sub { Gtk2->main_quit; });

$window->add($button);
$window->show_all();

Gtk2->main;
