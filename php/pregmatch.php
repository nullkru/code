<?php

$str = "adf {blah} asdfsadf asdfasdf {bleh} asdasdf";
$str1 = "adsf [[blah]] asdlöfajsd lkajdsöflk asd [[bleh]] miau";
//preg_match('/\{.+\}/',$str,$hits);
preg_match_all('/{[^}]+}/',$str,$hits);

print_r($hits); 

?>
