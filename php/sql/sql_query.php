<html>
<head>
<title>mySQL</title>
</head>

<body>
Hier mySQL-Befehl(e) eingeben:
<form name="sql" action="sql_query.php" method="post">
<textarea name="befehl" cols="50" rows="10" wrap="virtual"><?php echo stripslashes($_POST['befehl']); ?></textarea>
<input type="submit" value="Befehl senden">
</form>

<?php

if(isset($_POST['befehl']))
 {
  include( "connect.php" );
  mysql_query(stripslashes($_POST['befehl'])) or die("<font color=red>Fehler: ".mysql_error()."</font>");
  mysql_close();
  echo "Folgender Befehl wurde ausgeführt:<br>\n";
  echo stripslashes($_POST['befehl']);
 }

?>

</body>
</html>