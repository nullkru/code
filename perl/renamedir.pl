#!/usr/bin/perl -w

#
# SCRIPT TO RENAME MP3'S INTO PROPER FORMAT
#
# based on filename, not ID3!
# 
# 02-sept-2003: addition to substitute common
#        non-ascii chars (öäüÖÄÜßéèêÉÈÊ...)
#


foreach $xold (`ls`){
  chomp $xold;
    $xnew = $xold;
    $xn = $xold;
    $xnew = lc($xn);          ## lowercase it
    $xnew =~ s/\%20/_/g;      ## Converts netscape screwup to a _
    $xnew =~ s/\ /_/g;        ## Converts space to a _
    $xnew =~ s/\(/-/g;        ## Removes ( and subs -
    $xnew =~ s/\)//g;         ## Removes )
    $xnew =~ s/\[/-/g;        ## Removes [ and subs -
    $xnew =~ s/\]//g;         ## Removes ]
    $xnew =~ s/\{/-/g;        ## Removes { and subs -
    $xnew =~ s/\}//g;         ## Removes }
    $xnew =~ s/\#//g;         ## Removes #
    $xnew =~ s/\!//g;         ## Removes !
    $xnew =~ s/\~//g;         ## Removes ~
    $xnew =~ s/\'//g;         ## Hickey remover
    ##$xnew =~ s/_-_/-/g;       ## Shorten _-_ to -
    $xnew =~ s/-*-/-/g;       ## Shorten 2 or more -- to 1 -
    $xnew =~ s/_*_/_/g;       ## Shorten 2 or more __ to 1 _
    ##$xnew =~ s/-_/-/g;        ## Clean up -_ to -
    $xnew =~ s/\&/\+/g;       ## Clean up & for eaiser use in unix
    $xnew =~ s/\,_/\+/g;      ## Set up for format artist1+artist2
    $xnew =~ s/_\+_/\+/g;     ## Shorten _+_ to +
    ##$xnew =~ s/_-/-/g;        ## Clean up _- to -
    $xnew =~ s/-\./\./g;      ## Remove extra -'s infront of .mp3
    $xnew =~ s/\.-/\./g;      ## Remove extra -'s behind a  dot
    $xnew =~ s/\._/\./g;      ## Remove extra _'s behind a  dot
    $xnew =~ s/^-//g;         ## Remove - at beginning of filename
    $xnew =~ s/^_//g;         ## Remove _ at beginning of filename
    $xnew =~ s/^\.//g;        ## Unhide files

    ## addition to substitute the following chars:
    ## äöüÄÖÜáàâÁÀÂéèêÉÈÊíìîÍÌÎóòôÓÒÔúùûÚÙÛñçßïõã
    $xnew =~ s/\ä|\Ä/ae/g;
    $xnew =~ s/\ö|\Ö/oe/g;
    $xnew =~ s/\ü|\Ü/ue/g;
    $xnew =~ s/\á|\Á/a/g;
    $xnew =~ s/\à|\À/a/g;
    $xnew =~ s/\â|\Â/a/g;
    $xnew =~ s/\é|\É/e/g;
    $xnew =~ s/\è|\È/e/g;
    $xnew =~ s/\ê|\Ê/e/g;
    $xnew =~ s/\í|\Í/i/g;
    $xnew =~ s/\ì|\Ì/i/g;
    $xnew =~ s/\î|\Î/i/g;
    $xnew =~ s/\ó|\Ó/o/g;
    $xnew =~ s/\ò|\Ò/o/g;
    $xnew =~ s/\ô|\Ô/o/g;
    $xnew =~ s/\ú|\Ú/u/g;
    $xnew =~ s/\ù|\Ù/u/g;
    $xnew =~ s/\û|\Û/u/g;
    $xnew =~ s/\ñ/n/g;
    $xnew =~ s/\ç/c/g;
    $xnew =~ s/\ß/ss/g;
    $xnew =~ s/\ï/i/g;
    $xnew =~ s/\õ/o/g;
    $xnew =~ s/\ã/a/g;

    if($xnew ne $xold){
        print "Renaming $xold to $xnew\n";
        rename $xold, $xnew or die "Failed renaming $xold\n";
    }
}
