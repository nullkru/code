<?php

$link=mysql_connect('localhost','web497','skalaska')
   or die("Keine Verbindung möglich: " . mysql_error());

mysql_select_db('usr_web497_1')
   or die("Auswahl der Datenbank fehlgeschlagen");

?>
