<?php
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */



if(isset($_GET['p']))
{
    header("Location: " .file_get_contents("s/".$_GET['p']));
    echo file_get_contents("s/".$_GET['p']);
}

?>
	
<html>
	<head>
	    <title>snipsler</title>
	    <style type="text/css">
	    body { font-family:	sans-serif; background: #709413; }
	    #efeld {color: #000; border: 2px #444 solid}
            #button {border: 2px #444 solid; background-color: #fff; color:#444;}
	    #ausgabe {color: #000;}
	    a:link { color: #000; text-decoration: underline; }
	    a:visited { color: #000; text-decoration: underline; }
	    a:hover { color: #000; text-decoration: none; }
	    a:active { color: #000; text-decoration: none; }
	    </style>
	</head>
	<body>
	<h1>Snipsler</h1>
<form name="urladd" enctype="multipart/form-data" action="index.php" method="post">
	Long URL: <input type="text" id="efeld" name="url" size="100" maxlength="1000"> <br /><br />
	<input type="submit" id="button" value="5n1p teh URL ;) ">
</form>
	
	
<?php
                

/* add the entry */
                
$id = rand(1, 23425);
while(file_exists('s/'.$id))
{
    rand(1, 23425);
}

if( $_POST['url'] != "") 
{
    $url = $_POST['url'];
    
    if(!preg_match("/^.+\:\/\/.*$/",$url))
    {   
       $url = "http://".$_POST['url'];
    }
    
    if($fh=fopen("s/".$id,w))
    {
        $add = "$url";
        fwrite($fh,$add);
	fclose($fh);
	$snipedurl='http://'.$_SERVER['HTTP_HOST']."/".$id.'.r';
        echo "<div id=\"ausgabe\">";
        echo "<b>short url: <a name=\"url\" href=\"$snipedurl\"> $snipedurl </a></b>" ;
        echo "<form>copy me:(ctrl+c)<input type=\"text\" id=\"efeld\" size=\"30\" maxlength=\"30\" value=\"$snipedurl\"></form>";
	echo "Long Url:".$_POST['url']."<br /><br />";
        echo "</div>";

    }
}
	echo "//meta<br />";
	system("expr `ls s/ | wc -l` - 2"); echo  "pasted url's<br />";
	echo " last modified: ".date(r,filemtime(basename(__FILE__)));  
?>
	
	
	
	
	</body>
</html>	
