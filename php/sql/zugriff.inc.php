<?php
$db=@mysql_connect('localhost','web497','skalaska')
or die("Datenbankverbindung gescheitert!");
@mysql_select_db("usr_web497_1",$db) or die("Datenbankzugriff gescheitert!");
?>

