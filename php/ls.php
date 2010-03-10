<?php

/* config */

$cfg['dir'] = '';
$cfg['ignore'] = array('.htaccess');

class ls {

	var $dir;
	var $ignore;

	function getconf() {
		$this->dir = $cfg['dir'];
		$this->ignore = $cfg['ignore'];
		return true;
	}

	function getcontent() {
	}

	function listcontent() {
	}

	function cat() {
	}

}

?>
