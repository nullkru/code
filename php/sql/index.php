<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Datenverwaltung</title>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
<link rel="stylesheet" type="text/css" href="admin.css">
</head>
<body>

<?php

echo "<h2>Hauptseite: Tabellenauswahl</h2>\n" .
"<div>Welche Tabelle möchten Sie bearbeiten?</div>";

include("zugriff.inc.php");
include("dbname.inc.php");
$result=mysql_list_tables($dbname,$db);
$i=0;
echo "<ol>\n";
while ($i<mysql_num_rows($result)) {
$tb_name[$i]=mysql_tablename($result, $i);
echo "<li>[ <a href='manage.php?tbl=$tb_name[$i]'>$tb_name[$i]</a> ]</li>\n";
$i++;
}
echo "</ol>\n";
mysql_close($db);

?>

<br>
<div>Direkte Befehle senden<br><br>
[ <a href="sql_query.php" target="query">SQL-Queries</a> ]
</div>





</body>
</html>