<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Adresseliste ausgeben</title>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
</head>
<body>
<h3>Adressen anzeigen</h3>
<p>
<?php
mysql_connect("localhost","root","");
mysql_select_db("kunden");
$sql="SELECT * FROM adressen";
$result=mysql_query($sql);
while ($row=mysql_fetch_assoc($result)) {
echo "$row[Vorname] $row[Name], $row[Ort] <br>\n";  
}
mysql_close();
?>
</body>
</html>