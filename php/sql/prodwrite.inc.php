<?php
$sql="SELECT id, pnr, title, cat, price FROM products ORDER BY pnr";
$result=mysql_query($sql);
$gist="prod=new Array(\n";
$ct=1;
while ($row=mysql_fetch_assoc($result)) {
if ($ct==1) {
$gist.="'$row[pnr]|$row[title]|$row[id]|$row[cat]||$row[price]|'";
}
else {
$gist.=",\n'$row[pnr]|$row[title]|$row[id]|$row[cat]||$row[price]|'";
}
$ct++;
} // while Ende
$gist.="\n);";
echo "<p>Die JavaScript-Datei <b>products.js</b> wurde geschrieben!</p>";
$fp=fopen("../data/products.js","w");
fputs($fp,$gist);
fclose($fp);
?>