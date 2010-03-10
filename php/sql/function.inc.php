<?php
function datemaker($datum) {
$datum=explode("-",$datum);
$datum="$datum[2].$datum[1].$datum[0]";
return $datum; 
}

function magic($wert) {
// $wert=addslashes($wert); // KW-Server
$wert=$wert; // normaler Server
return $wert;
}

function demagic($wert) {
// $wert=stripslashes($wert); // normaler Server
$wert=$wert; // KW-Server
$wert=htmlspecialchars($wert);
return $wert;
}

function special($wert) {
// $wert=stripslashes($wert); // normaler Server
$wert=htmlspecialchars($wert);
$wert=nl2br($wert);
return $wert;
}

// Reload-Killer
function no_reload() {
$gleichheit=false;
if (isset($_POST["uw"])) {
$datei="bestellen/unique.txt";
$fp=fopen($datei,"r+");
$aw=fgets($fp,30);
if ($aw==$_POST["uw"]) {
$gleichheit=true;
}
rewind($fp);
fputs($fp,$_POST["uw"]);
fclose($fp);
}
return $gleichheit;
}

function hidemail($txt) {
// $txt=str_replace("@", "<img src='help/affe.gif' title='E-Mail-Adresse'>", $txt);
$txt=str_replace(".", "<img src='help/dot.gif' title=''>", $txt);
$txt=str_replace("@", "<img src='help/affe.gif' title=''>", $txt);
$txt=str_replace("de", "<img src='help/de.gif' title=''>", $txt);
$txt=str_replace("net", "<img src='help/net.gif' title=''>", $txt);
return $txt;
}

?>