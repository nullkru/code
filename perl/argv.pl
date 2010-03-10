 @ARGV = qw# larry moe curly #;  # drei Dateien zum Lesen hartcodieren
 while (<>) {
        chomp;
        print "Ich habe $_ in einer Handlangerdatei gesehen!\n";
      }
