#!/usr/bin/perl
 $wass = "dini mer";
 $was = "Brontosaurier-Steak";
 $n = 3;
 print "Fred a� $n $wass.\n";       # Keine Steaks, sondern der
                                    #  Wert von $wass
 print "Fred a� $n ${was}s.\n";     # Jetzt wird $was benutzt
 print "Fred a� $n $was" . "s.\n";  # eine andere Art, das gleiche
                                    #  zu tun
 print 'Fred a� ' . $n . ' ' . $was . "s.\n"; # eine besonders
                                              # aufwendige Methode

