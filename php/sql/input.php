<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Neuen Datensatz einrichten</title>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
<link rel="stylesheet" type="text/css" href="admin.css">
</head>
<body>

<?php

include("function.inc.php");
$tblname=$_REQUEST["tbl"];

echo "<div>[ <a href='index.php'>Tabellenauswahl</a> ] - [ <a href='index.php?logoff=now'>" .
"Ausloggen</a> ] - [ <a href='manage.php?tbl=$tblname'>Tabelle anzeigen</a> ]</div>";
echo "<h3>Neuen Datensatz in Tabelle &raquo;$tblname&laquo; einfügen</h3>\n";

if (isset($_POST["tbl"])) {
include("zugriff.inc.php");
$sql_1="";
$sql_2="";
foreach ($_POST as $key => $value) {
if ($key!="tbl") {
$sql_1.="$key, ";
$sql_2.="'" . magic($value) . "', ";
}
}
$sql_1=substr($sql_1, 0, strlen($sql_1)-2);
$sql_2=substr($sql_2, 0, strlen($sql_2)-2);

$output="<p>Folgender SQL-Befehl wurde ausgeführt: </p>
<div>INSERT INTO <b>$tblname</b> <br>($sql_1) <br>VALUES <br>(" .
special($sql_2) . ")\n</div>";

$sql="INSERT INTO $tblname ($sql_1) VALUES ($sql_2)";
if (mysql_query($sql)) {

if ($tblname=="products") {
include("prodwrite.inc.php");
}

echo "<p><big><b>Dateneingabe erfolgreich!</b></big></p>
<div>[ <a href='manage.php?tbl=$tblname'>Tabelle anzeigen</a> ] -
[ <a href='input.php?tbl=$tblname'>Neuen Eintrag erzeugen</a> ]</div>
$output";
}
else {
echo "<p><big><strong>Dateneingabe nicht erfolgreich!</strong></big></p>
<div>[ <a href='manage.php?tbl=$tblname'>Tabelle anzeigen</a> ] -
[ <a href='input.php?tbl=$tblname'>Neuen Eintrag erzeugen</a> ]</div>
$output\n";
}
mysql_close($db);
}
else if (empty($_POST["tbl"])) {

include("zugriff.inc.php");
$sql="SELECT * FROM $tblname";
$result=mysql_query($sql);
$felder=mysql_num_fields($result);

echo "<form action='$_SERVER[PHP_SELF]' method='post'>\n";
echo "<input type='hidden' name='tbl' value='$tblname'>";
echo "<table>";
for ($i=0;$i<$felder;$i++) {
$fn=mysql_field_name($result,$i);
$fl=mysql_field_len($result,$i);
if ($fl<150) {
echo "<tr><td><strong>$fn</strong></td><td><input type='text' name='$fn' " .
"size='$fl' maxlength='$fl'></td></tr>";
}
else {
echo "<tr><td><strong>$fn</strong></td><td><textarea name='$fn' " .
"rows='15' cols='100'></textarea></td></tr>";

}
}
?>

<tr><td colspan="2">
<input type="submit" value="Daten eintragen">
</td></tr>
</form>
</table>

<?php

}

?>
</body>
</html>