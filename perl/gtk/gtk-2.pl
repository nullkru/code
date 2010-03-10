#!/usr/bin/perl

use Gtk2 '-init';

my $window = Gtk2::Window->new;
$window->set_title ("Hello world");
$window->signal_connect (destroy => sub { Gtk2->main_quit; });

my $vbox = Gtk2::VBox->new();
$vbox->set("border_width"=> 10);
$window->add($vbox);

my $label = Gtk2::Label->new("Hello world");
$vbox->pack_start($label,0,0,5); # expand?, fill?, padding

my $button = Gtk2::Widget->new("Gtk2::Button",
			       label=>"Quit");
$button->signal_connect(clicked=>\&my_quit);

$vbox->pack_start($button, 0,0,5);

$window->show_all();

Gtk2->main;

sub my_quit {
    print "Good bye!\n";
    exit;
}
