<?php
include("function.inc.php");
if ($_POST["update"]=="yes") {
include("zugriff.inc.php");
$sql_1="";
foreach ($_POST as $key => $value) {
if ($key!="tbl") {
if ($key!="updateme") {
if ($key!="update") {
$sql_1.="$key='" .magic($value) . "', ";
}
}
}
}
$sql_1=substr($sql_1, 0, strlen($sql_1)-2);
$output="<p>Folgender SQL-Befehl wurde ausgeführt:</p>
<div>UPDATE <strong>$tblname</strong> SET <br>" .
special($sql_1) . "<br>WHERE id='$_POST[updateme]'</div>\n";

$sql_1="UPDATE $tblname SET $sql_1 WHERE id='$_POST[updateme]'"; 

if (mysql_query($sql_1)) {
echo "<p><big><b>Datenupdate erfolgreich!</b></big></p>
<div>[ <a href='manage.php?tbl=$tblname'>Tabelle wieder anzeigen</a> ] -
[ <a href='input.php?tbl=$tblname'>Neuen Eintrag erzeugen</a> ]</div>
$output\n";

}
else {
echo "<p><strong>Datenupdate nicht erfolgreich!</strong></big></p>
<div>[ <a href='input.php?tbl=$tblname'>Neuen Eintrag erzeugen</a> ]</div>
$output\n";
}
// mysql_close($db);
}
else if (empty($_POST["tbl"])) {
include("zugriff.inc.php");
$sql="SELECT * FROM $tblname WHERE id='$_REQUEST[id]'";
$result=mysql_query($sql);
$felder=mysql_num_fields($result);
$row=mysql_fetch_assoc($result);
echo "<form action='$_SERVER[PHP_SELF]' method='post'>\n";
echo "<input type='hidden' name='tbl' value='$tblname'>\n";
echo "<input type='hidden' name='updateme' value='$_REQUEST[id]'>\n";
echo "<input type='hidden' name='update' value='yes'>\n";
echo "<table>";
for ($i=0;$i<$felder;$i++) {
$fn=mysql_field_name($result,$i);
$fl=mysql_field_len($result,$i);
if ($fl<150) {
echo "<tr><td><strong>$fn</strong></td><td><input type='text' name='$fn' " .
"size='$fl' maxlength='$fl' value='" . demagic($row[$fn]). "'></td></tr>";
}
else {
echo "<tr><td><strong>$fn</strong></td><td><textarea name='$fn' " .
"rows='15' cols='100'>" . demagic($row[$fn]) .
"</textarea></td></tr>";
}
}
echo "</table>\n<p>\n" .
"<input type='button' value='Abbrechen' onclick='javascript:history.back()'>\n" . 
"<input type='submit' value='Datensatz updaten'>\n" .
"</p></form>";
}
?>