<?php
ini_set('magic_quotes', 'off');
/* simple paste script without any special stuff or functions...
* just creates a plain textfile or upload images or whatever 
*  + create a .htaccess file or set in php.ini: magic_quotes to off!
*  example .htaccess
*  php_flag register_globals off
*  php_flag magic_quotes_gpc off   
*/



## Configuration
#directory where the pastes  gone be saved (chmod 777 this dir)
$path = "p/";
#Fully Qualified Domain Name ex: http://chao.ch/tmp is  chao.ch ist the fqdn
$fqdn = "http://cp.figg.ch/";

## End config
?>

<html>
	<head>
	<title><?= $fqdn ?> - cp /dev/local /dev/www </title>
	</head>
	<style type="text/css">
	body,html  {font-family:sans-serif; padding:23px; background-color:#EFEFEF;}
	h1 { font-size:14px; font-weight: bold; margin:0; padding:0; }
	h2 { font-size:12px; font-weight: bold; }
	a:link, a:visited, a:hover, a:active { color: #4B8F35; font-weight: bold; }	
	textarea { border:1px #000 solid; width: 80%; }
	.button { border:1px #000 solid; background-color:#BFDFB5; font-weight:bold; color: #000; }
	.field { border:1px #000 solid; }	
	.checkbox { border:1px #000 solid; }
	#selector { border:1px #000 dashed; width:20%; padding:5px; margin:20px 0 20px 0; text-align:center;}
	</style>
<body>	
<?php



if(! $_POST['pasted'])
{
	echo "<div id=\"holder\">\n<h1>Simple code/text or file paster for $fqdn$path</h1>\n";
	echo "Simple means without highlighting or any other crap!!!<br />";
	
	echo "<div id=\"selector\"><a href=\"".basename(__FILE__)."?file=true\">Upload a File</a> &nbsp;<a href=\"".basename(__FILE__)."\">Paste some Code/Text</a></div>\n";
	
	echo "<form name=\"paster\" enctype=\"multipart/form-data\" action=\"".basename(__FILE__)."\" method=\"post\">\n";
	
	if($_GET['file'])
	{
		echo "File Upload(max size:8MB):<br />\n";
		echo "<input type=\"file\" name=\"ufile\" /><br /><br />\n";
	}
	else
	{	
		echo "paste name(enter something or let it blank):<input class=\"field\" type=\"text\" name=\"pastename\" /><br />\n";
		echo "Description:<br />\n";
		echo "<textarea name=\"description\" rows=\"4\"></textarea><br />\n";
		echo "Text to paste:	<br />\n";
		echo "<textarea name=\"content\" rows=\"30\"></textarea><br />\n";
	}
	echo "<input class=\"checkbox\" type=\"checkbox\" name=\"pasted\" value=\"true\" /> Yes, i'm no fucking Spamer\n"; 
	echo "<input class=\"button\" type=\"submit\" value=\"Paste/Upload\" />\n";
	echo "</form>\n";
}

else
{
	//call functions
	if($_FILES["ufile"])
		$fileupload = true;
	
	if($_POST['content'])
		$textpaste = true;
	
}

if($fileupload) 
{
	$file=$_FILES["ufile"]["name"];

	while(file_exists($path.$file))
	{
		$file = rand(1, 23425)."_".$file;
	}
	
	if(move_uploaded_file($_FILES['ufile']['tmp_name'], $path.$file))
	{
		echo "File Uploaded!<br />";
		echo "URL: <a href=\"$fqdn$path$file\">$fqdn$path$file</a>";
		echo "<form>copy me:<input type=\"text\" name=\"url\" size=\"30\" value=\"$fqdn$path$file\"></form><br />";
	}
	else 
	{
		echo "<p><br />error: konnte datei nich uploaden<br />";
		print_r($_FILES);
		echo "</p>";
	}
	echo "\n</div>";
}


/* Text paste */
if($textpaste)
{

	$description = $_POST['description'];
	$content = $_POST['content'];

	if(! $_POST['pastename'] )
	{
		$id = rand(1, 23425);
		while(file_exists("$path/".$id))
	       	{
			$id = rand(1, 23425);
		}
	}
	else
	{
		$id = $_POST['pastename'];
		while(file_exists("$path/".$id))
		{
			$id = rand(1, 23425)."_".$_POST['pastename'];
			$exists = true;
		}
	}

	if($fh=fopen("$path/".$id,w)) 
	{
		if($description) 
		{
			fwrite($fh, "Description/Notes:\n\n");
			fwrite($fh, "$description\n");
			fwrite($fh, "----------------------8<--------------------\n\n");
		}
		fwrite($fh, $content);
		fclose($fh);
	}
	if($exists == true)
	{
		echo "<br /><strong>Sorry file $_POST[pastename] allready exists.So I added some numbers...</strong><br />";
	}

	echo "URL: <a href=\"$fqdn$path$id\"> $fqdn$path$id</a>";
	echo "<form>copy me:<input type=\"text\" name=\"url\" size=\30\" value=\"$fqdn$path$id\"></form><br />";

}
	
	//$files_pasted inhalte von $path auslesen und zahl ausgeben
	echo "<div id=\"meta\">";
	echo "<br /><br />//Meta stuff<br />\n";
	$countarr = glob($path.'/*');
	$pastes = is_array($countarr) ? count($countarr) : 0;
	echo "$pastes  pasted files<br />\n";
	echo "<b>To paste stuff you can use <a href=\"http://chao.ch/code/perl/kcp.pl\">paster.pl</a></b><br />\n";
	echo "Search older pastes? Browse <a href=\"$fqdn$path\"> $fqdn$path</a>.";
	echo "<br /> last modified: ".date(r,filemtime(basename(__FILE__)));
	echo "</div>";
	
	
	/*DEBUG*/
	//phpinfo(INFO_VARIABLES);
?>
<pre>
TODO:
- such funktion
</pre>
</body>
</html>		
