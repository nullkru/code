<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Tabelle verwalten</title>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
<link rel="stylesheet" type="text/css" href="admin.css">
</head>
<body>
<div>
<?php

$tblname=$_REQUEST["tbl"];
$maxlength=20; // steuert Länge

include("zugriff.inc.php");
if ($_GET['kill']=="me") {
$sql="DELETE from $tblname WHERE id='$_GET[id]'";
if (mysql_query($sql)) {
echo "<h3>Löschupdate erfolgreich!</h3>";

if ($tblname=="products") {
include("prodwrite.inc.php");
}

}
else {
echo "<h3>Löschupdate nicht erfolgreich!</h3>";
}
echo "<div>[ <a href='$_SERVER[PHP_SELF]?tbl=$tblname'>Tabelle wieder anzeigen</a> ]</div>";
mysql_close($db);

} else if ($_GET['update']=="7_rukzz69" || $_POST["update"] ) {
if ($_POST['kill']=="yes") {
echo "<div>[ <a href='index.php'>Tabellenauswahl</a> ] - [ <a href='index.php?logoff=now'>" .
"Ausloggen</a> ] - [ <a href='manage.php?tbl=$tblname'>Tabelle anzeigen</a> ]</div>";
echo "<h3>Datensatz &raquo;$_REQUEST[id]&laquo; aus Tabelle &raquo;$tblname&laquo; löschen</h3>\n";
echo "<p>Sind Sie sicher, dass der Eintrag <b>endgültig gelöscht</b> werden soll?</p>" . 
"<div>[ <a href='$_SERVER[PHP_SELF]?kill=me&id=$_POST[id]&tbl=$tblname'>" .
"Ja, Eintrag jetzt löschen</a> ] - " .
"[ <a href='$_SERVER[PHP_SELF]?tbl=$tblname'>Nein, Zurück zur Tabelle!</a> ]</div>";
} else {
echo "<div>[ <a href='index.php'>Tabellenauswahl</a> ] - [ <a href='index.php?logoff=now'>" .
"Ausloggen</a> ] - [ <a href='manage.php?tbl=$tblname'>Tabelle anzeigen</a> ]</div>";
echo "<h3>Datensatz &raquo;$_REQUEST[id]&laquo; aus &raquo;$tblname&laquo; updaten</h3>\n";

include("update.inc.php"); 
mysql_close($db);
}
}

else {
echo "<div>[ <a href='index.php'>Tabellenauswahl</a> ] - [ <a href='index.php?logoff=now'>" .
"Ausloggen</a> ] - [ <a href='input.php?tbl=$tblname'>Neuen Eintrag erzeugen</a> ]</div>";
echo "<h3>Tabelle &raquo;$tblname&laquo; anzeigen und bearbeiten</h3>\n";
if ($_GET["sort"]) {
$sql="SELECT * FROM $tblname $where ORDER BY $_GET[sort] $_GET[dir]";
}
else {
$sql="SELECT * FROM $tblname $where ORDER BY id";
}
$result=mysql_query($sql);
$zeilen=mysql_num_rows($result);
$felder=mysql_num_fields($result);

echo "<p>$zeilen Einträge:</p>\n";
// Tabelle definieren:
echo "<table border='1' cellspacing='0'>\n";

// Kopfzeile der Tabelle anlegen:

echo "<tr><th>&nbsp;</th><th><img src='delete.gif' border='0' 
width='8' height='9' alt='Löschen?'></th>"; // Zeile beginnen 
for ($i=0;$i<$felder;$i++) {
$finame=mysql_field_name($result,$i);
if ($_GET["dir"]=="ASC" && $finame==$_GET['sort']) {
$dir="DESC";
}
else {
$dir="ASC";
}
if ($_GET['sort']==$finame) {
echo "<th class='$_GET[dir]'><img src='$_GET[dir].gif'>";
}
else {
echo "<th>";
}

echo "<a href='$_SERVER[PHP_SELF]?tbl=$tblname&sort=$finame&dir=$dir'  
title='Sortieren' style=
'text-decoration: none; color: black;'>$finame</a></th>";
}
echo "</tr>"; // Zeile schließen
// while-Schleife Anfang
while ($row=mysql_fetch_assoc($result)) {
echo "<tr><form action='$_SERVER[PHP_SELF]?update=7_rukzz69&tbl=$tblname' method='post'>"; // Zeile erzeugen
echo "<td>&nbsp;<input type='image' src='okay.gif' border='0' width='8' height='9' alt='Updaten'></td>";
echo "<td><input type='checkbox' name='kill' value='yes' title='Wirklich löschen?'></td>";
// foreach Anfang:
foreach ($row as $key => $value) {
$value=htmlspecialchars($value); // HTML-Tags entschärfen
if ($key=="id") {
echo "<td>" .
"<input type='hidden' name='$key' value='$value' size='4' " .
"style='border-width: 0px'>$value</td>";
}
else {
if (strlen($value)>$maxlength) {
$value=substr($value, 0, $maxlength);
$value.="... ";
}
echo "<td>$value&nbsp;</td>";
}
} // foreach Ende
echo "</form></tr>\n"; // Zeile schließen
 } // while Ende
echo "</table>\n"; // Tabelle schließen
echo "<p><strong>Updaten</strong> durch Klick auf das " .
"grüne Häkchen (<img src='okay.gif' border='0' width='8' height='9' alt=''>).<br>\n" .
"<b>Löschen</b> durch zusätzliches Abhaken der Checkbox " .
"(<img src='delete.gif' border='0' width='8' height='9' alt='delete.gif'>).<br>\n" .
"<strong>Sortieren</strong> durch Klick auf den Spaltenkopf.</p>\n";

mysql_close($db);
}
?>
</div>
</body>
</html>