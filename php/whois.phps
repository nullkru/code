<?php

/* by gichty paranoya.homelinux.org */
$GLOBALS['whois_servers'] = array(
		    'de' => 'whois.denic.de',
   		    'com' => 'whois.crsnic.net',
		    'net' => 'whois.crsnic.net',
		    'org' => 'whois.pir.org',
		    'ac' => 'whois.nic.ac',
		    "ac.uk" => "whois.ja.net",
		    "ad.jp" => "whois.nic.ad.jp",
		    "aero" => "whois.information.aero",
		    "ag" => "whois.nic.ag",
		    "al" => "whois.ripe.net",
		    "at" => "whois.nic.at",
		    "au" => "whois.aunic.net",
		    "as" => "whois.nic.as",
		    "asn.au" => "whois.aunic.net",
		    "be" => "whois.dns.be",
		    "bg" => "whois.digsys.bg",
		    "biz" => "whois.biz",
		    "br" => "whois.registro.br",
		    "ca" => "whois.cira.ca",
		    "cc" => "whois.nic.cc",
		    "cd" => "whois.cd",
		    "ch" => "whois.nic.ch",
		    "cl" => "whois.nic.cl",
		    "com" => "whois.verisign-grs.net",
		    "com.au" => "whois.aunic.net",
		    "com.eg" => "whois.ripe.net",
		    "com.mx" => "whois.nic.mx",
		    "com.tw" => "whois.twnic.net",
		    "conf.au" => "whois.aunic.net",
		    "co.jp" => "whois.nic.ad.jp",
		    "co.uk" => "whois.nic.uk",
		    "csiro.au" => "whois.aunic.net",
		    "cx" => "whois.nic.cx",
		    "cz" => "whois.nic.cz",
		    "de" => "whois.denic.de",
		    "dk" => "whois.dk-hostmaster.dk",
		    "ee" => "whois.eenet.ee",
		    "edu" => "whois.verisign-grs.net",
		    "edu.au" => "whois.aunic.net",
		    "eg" => "whois.ripe.net",
		    "es" => "whois.ripe.net",
		    "eun.eg" => "whois.ripe.net",
		    "emu.id.au" => "whois.aunic.net",
		    "fi" => "whois.ripe.net",
		    "fo" => "whois.ripe.net",
		    "fr" => "whois.nic.fr",
		    "ge" => "whois.ripe.net",
		    "gl" => "whois.ripe.net",
		    "gr" => "whois.ripe.net",
		    "gr.jp" => "whois.nic.ad.jp",
		    "gov.au" => "whois.aunic.net",
	            "gob.mx" => "whois.nic.mx",
		    "gs" => "whois.adamsnames.tc",
		    "hm" => "whois.registry.hm",
		    "mc" => "whois.ripe.net",
		    "mil" => "whois.nic.mil",
		    "ms" => "whois.adamsnames.tc",
		    "mx" => "whois.nic.mx",
   		    "name" => "whois.nic.name",
		    "ne.jp" => "whois.nic.ad.jp",
		    "net" => "whois.verisign-grs.net",
		    "net.au" => "whois.aunic.net",
		    "net.eg" => "whois.ripe.net",
		    "net.lu" => "whois.dns.lu",
		    "net.mx" => "whois.nic.mx",
		    "net.uk" => "whois.nic.uk",
		    "net.tw" => "whois.twnic.net",
		    "nl" => "whois.domain-registry.nl",
		    "id.au" => "whois.aunic.net",
		    "ie" => "whois.domainregistry.ie",
		    "info" => "whois.afilias.info",
		    "info.au" => "whois.aunic.net",
		    "it" => "whois.nic.it",
		    "idv.tw" => "whois.twnic.net",
		    "int" => "whois.iana.org",
		    "is" => "whois.isnic.is",
		    "jp" => "whois.nic.ad.jp",
		    "la" => "whois.nic.la",
		    "li" => "whois.nic.ch",
		    "lk" => "whois.nic.lk",
		    "lt" => "ns.litnet.lt",
		    "lu" => "whois.dns.lu",
		    "ltd.uk" => "whois.nic.uk",
		    "plc.uk" => "whois.nic.uk",
		    "or.jp" => "whois.nic.ad.jp",
		    "org" => "whois.verisign-grs.net",
		    "org.au" => "whois.aunic.net",
	      	    "org.lu" => "whois.dns.lu",
		    "org.tw" => "whois.twnic.net",
		    "org.uk" => "whois.nic.uk",
		    "pl" => "nazgul.nask.waw.pl",
		    "pt" => "whois.ripe.net",
		    "ru" => "whois.ripn.ru",
		    "th" => "whois.nic.uk",
		    "to" => "whois.tonic.to",
		    "tw" => "whois.twnic.net",
		    "uk" => "whois.thnic.net",
		    "wattle.id.au" => "whois.aunic.net"
		   );
				  
						
function get_whois_server_by_tld($tld)
{
    foreach($GLOBALS['whois_servers'] as $a_tld => $a_whois)
    {
	if("$tld" == "$a_tld")
	  return $a_whois;
    }
    return "";
}

function domain_whois($domain, $tld)
{
	global $whois_servers;

	if (!isset($whois_servers[$tld]))
		return NULL;

	$fd = fsockopen($whois_servers[$tld], 43);

	if (!$fd)
		return NULL;

	set_socket_blocking($fd, 0);

	if ($tld == 'de')
		$domain = '-C ISO-8859-1 -T ace,dn '.$domain;

	fputs($fd, $domain.'.'.$tld."\r\n");

	$result = '';
	while (!feof($fd))
	{
		$result .= fgets($fd, 512);
	}

	fclose($fd);

	return $result;
}

function domain_checkfree($domain, $tld)
{
	$result = domain_whois($domain, $tld);

	if ($result == NULL)
		return false;

	if (ereg('Object "'.$domain.'.'.$tld.'" not found in database|No match for|NOT FOUND|"'.$domain.$tld.'" is not a valid domain name', $result))
		return true;
	else
		return false;
}
?>
<form name="whois_form" method="post" action="whois.php">
<input type="text" name="domain" value="<?php
if(isset($_POST['domain']) && strlen($_POST['domain']))
  echo $_POST['domain'];
else
  echo "meinedomain";
?>" />
<select name="tld">
<?php
foreach($GLOBALS['whois_servers'] as $tld => $whois)
{
    echo "<option value=\"$tld\" ";
    if(isset($_POST['tld']) && strlen($_POST['tld']))
    {
      if($_POST['tld'] == $tld)
	  echo "selected";
    }
    echo ">$tld</option>";
}
?>
</select>
<input type="submit" name="submit" value="check" />
</form>
<?php
if(isset($_POST['domain']) && strlen($_POST['domain']))
	$domain = $_POST['domain'];
else
	{ echo "Bitte geben Sie den Domainnamen an!"; die(); }
if (isset($_POST['tld']) && strlen($_POST['tld']))
	$tld = $_POST['tld'];
else
	{ echo "Bitte geben Sie die TLD an!"; die(); }
if(domain_checkfree($domain, $tld))
    echo "Domain ist noch frei";
else
    echo "Domain ist bereits vergeben";
$whois_server = get_whois_server_by_tld($tld);
if(strlen($whois_server))
  echo "<br />Verwendeter Whois-Server: $whois_server";
?>
