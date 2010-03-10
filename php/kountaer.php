<?php
  /*
     Simple PHP/MySQL Text Counter with reload protection by smoln

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.
  
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
    
     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
   
     $Id: kountär.php,v 1.29 2001/12/27 01:19:23 smoln Exp $

     To install, perform these MySQL commands as root:
       use mysql;
       insert into user (host,user,password) values ('localhost','counters','');
       insert into db (host,db,user,select_priv,update_priv,insert_priv,delete_priv)
              values ('localhost','counters','counters','Y','Y','Y','Y');
       flush privileges;
       create database counters;
       use counters;
       create table counters (name varchar(16) not null, visits bigint, primary key(name));
       create table locks (name varchar(16) not null, host varchar(255) not null,
                           expire timestamp not null, primary key(host));
       insert into counters (name, visits) values ('www.wulf.ch.vu', 0);
          ^-- use this for each counter u want
    
     To clean the database:
       use mysql;
       delete from user where user='counters';
       delete from db where user='counters';
       drop database counters;

     To include this file from a PHP script:
       include('kountär.php');
       echo $counter;
    
     How the "reload protection" works:
       If a user hits the page, this script reads the appropriate counter entry
       to the $name variable (multi-counter capability).
       Then it checks wether the client is in the "locks" table. If not, it
       adds him to this table with the current time, increments the counter
       and outputs it, otherwise it updates the clients lock-entry with the
       current time.
       Expired lock-entries are cleaned at every script execution.       
  */ 

  // counter entry name
  $name = "wiki.chao.ch";

  // expire times for locks in seconds
  $expire_time = 1800;

  // database name
  $db = "usr_web497_1"; 

  // open the MySQL connection
  $myhandle = mysql_connect("localhost", "web497", "skalaska")
                  or die (mysql_error());

  // fetch the appropriate counter entry
  $myresult = mysql_db_query($db, "select visits from counters where name='" . $name . "'")
                  or die (mysql_error());
  $myrow = mysql_fetch_row($myresult);
  $counter = $myrow[0];
  
  // check wheter client is locked or not
  $host = getenv("REMOTE_ADDR");
  $myresult = mysql_db_query($db, "select expire from locks where host='" . $host . "' and name='" . $name . "'")
                or die (mysql_error());
  $myrow = mysql_fetch_row($myresult);  

  // if client has not been locked then increment the counter & lock him
  if(!$myrow)
    {
      $counter++;
       
      mysql_db_query($db, "update counters set visits=" . $counter . " where name='" . $name . "'")
             or die (mysql_error());

      mysql_db_query($db, "insert into locks (name,host) values ('" . $name . "','" . $host . "')")
             or die (mysql_error());
    }
  else
    mysql_db_query($db, "update locks set expire=now() where host='" . $host . "'")
           or die (mysql_error());
    
  // kill expired locks
  $expired = time() - $expire_time;
  $myresult = mysql_db_query($db, "select host,unix_timestamp(expire) from locks where name='" . $name . "'")
                or die (mysql_error());

  while($myrow = mysql_fetch_row($myresult))
  {
    $host = $myrow[0];
    $expire = $myrow[1];
   
    if($expire <= $expired)
      mysql_db_query($db, "delete from locks where host='" . $host . "'")
             or die (mysql_error());
  }

  // kill MySQL connection
  mysql_close($myhandle);
?>
