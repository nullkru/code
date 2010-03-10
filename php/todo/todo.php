<?php
//startsession
session_start();

class todo {

	var $todoNode;	# todo list name
	var $todoItem;	# the todo note
	var $timestamp;

	function init($dbname) {

		$this->dbName = $dbname;

		print_r($_SESSION);
	}

	function parseRequest($value) {
		echo $value;

		$this->timestamp = time();
		if(preg_match("/^(.*)(?=\/)/", $value, $m))
			$this->todoNode = $m[0];

		if(preg_match("/(?<=\/)(.*)$/", $value, $m))
			$this->todoItem = urldecode($m[0]);
	}


	/* db functions */
	var $dbName;

	function dbLoad($dbname) {
		$this->dbName = $dbname;
	}


	function dbInsert() {
		printf("<br />node: %s", $this->todoNode);
		printf("<br />note: %s", $this->todoItem);
	}
	
	function itemAdd() {
		true;
		$sql = "INSERT INTO %s VALUES ()";
	}

	function itemDone() {
		true;
	}

	function itemUpdate() {
		true;
	}

	function itemRemove() {
		true;
	}
	
	function dbOpen() {
		try {
			$this->db = sqlite_open($this->dbName, 0666, $error);
		}
		catch (Exception $e) {
			die($error);
		}
	}
}

$t = new todo();

$t->init('todoer.sqlite');
$t->parseRequest($_SERVER["QUERY_STRING"]);
$t->dbInsert();
?>
