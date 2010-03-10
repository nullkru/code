#!/usr/bin/perl
 $wass = "dini mer";
 $was = "Brontosaurier-Steak";
 $n = 3;
 print "Fred aﬂ $n $wass.\n";       # Keine Steaks, sondern der
                                    #  Wert von $wass
 print "Fred aﬂ $n ${was}s.\n";     # Jetzt wird $was benutzt
 print "Fred aﬂ $n $was" . "s.\n";  # eine andere Art, das gleiche
                                    #  zu tun
 print 'Fred aﬂ ' . $n . ' ' . $was . "s.\n"; # eine besonders
                                              # aufwendige Methode

