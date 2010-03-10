<?php
/* reemoves the directory and all its contents.
 *
 *  * @param string the directory name to remove
 *   * @param boolean whether to just empty the given directory, without deleting the given directory.
 *    * @return boolean True/False whether the directory was deleted.
 *  
 */ 


function deleteDirectory($dirname,$only_empty=false) {
    if (!is_dir($dirname))
        return false;
    $dscan = array(realpath($dirname));
    $darr = array();
    while (!empty($dscan)) {
        $dcur = array_pop($dscan);
        $darr[] = $dcur;
        if ($d=opendir($dcur)) {
            while ($f=readdir($d)) {
                if ($f=='.' || $f=='..')
                    continue;
                $f=$dcur.'/'.$f;
                if (is_dir($f))
                    $dscan[] = $f;
                else
                    unlink($f);
            }
            closedir($d);
        }
    }
    $i_until = ($only_empty)? 1 : 0;
    for ($i=count($darr)-1; $i>=$i_until; $i--) {
        echo "\nDeleting '".$darr[$i]."' ... ";
        if (rmdir($darr[$i]))
            echo "ok";
        else
            echo "FAIL";
    }
    return (($only_empty)? (count(scandir)<=2) : (!is_dir($dirname)));
}

deleteDirectory("templates/holzer_template_-_wuerstli")

?>
