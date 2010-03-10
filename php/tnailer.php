<?php

$path = array('images/maturfiir06');


	
$tnails="images/mfiir06";       
#$tnail_width="640";
$tnail_height="480";
    
foreach($path as $act_path) {
     $handle=opendir($act_path);
     while($files = readdir($handle)) {
	    if($files != "." && $files != "..") {
	        $imgsize = @getimagesize($act_path."/".$files);
	        if($imgsize !== false) {
	            if(!file_exists($tnails.$files)) {
        	        $size=getimagesize($act_path."/".$files);
			$orig_width=$size[0];
			$orig_height=$size[1];
                        $tnail_width=round($tnail_height * $orig_width / $orig_height);
			#$new_size=intval($height+$tnail_width/$width);
			
			$picture = ImageCreateFromJPEG($act_path."/".$files);
			if($picture = "") {
                            $picture=ImageCreateFromGif($act_path."/".$files);
                        }
                        if($picture = "") {
                            $picture=ImageCreateFromPng($act_path."/".$files);
                        }
                        if($picture = "") {
                            $picture=ImageCreateFromWbmp($act_path."/".$files);
                        }
                        
                        
                        $new_picture=ImageCreateTrueColor($tnail_width,$tnail_height);
			ImageCopyResized($new_picture,$picture,0,0,0,0,$tnail_width,$tnail_height,$orig_width,$orig_height);
	                $pwd=getcwd();
			$goto=chdir($tnails);
			ImageJPEG($new_picture,$files);
			chdir($pwd);
                    }	
	         }
            }
	}
}
?>
