<?php

	$filename = "counter.txt";
	$fp = fopen($filename,"r");
	$count=fread($fp,filesize($filename));
	fclose($fp);
	if(!$_COOKIE['set']){
		setcookie('set','visited');
		$count++;
	}	
	
	$string = (string) $count;
	
	echo("<b style='font-size:40px;'>방문자수 : </b>");
	
	for($i=0;$i<strlen($string);$i++){
		$ch = substr($string,$i,1);
		switch($ch){
		case 0:echo("<IMG SRC='img/0.JPG'>"); break;
		case 1:echo("<IMG SRC='img/1.JPG'>"); break;
		case 2:echo("<IMG SRC='img/2.JPG'>"); break;
		case 3:echo("<IMG SRC='img/3.JPG'>"); break;
		case 4:echo("<IMG SRC='img/4.JPG'>"); break;
		case 5:echo("<IMG SRC='img/5.JPG'>"); break;
		case 6:echo("<IMG SRC='img/6.JPG'>"); break;
		case 7:echo("<IMG SRC='img/7.JPG'>"); break;
		case 8:echo("<IMG SRC='img/8.JPG'>"); break;
		case 9:echo("<IMG SRC='img/9.JPG'>"); break;
		}
	}

	$fp = fopen($filename,"w");
	fwrite($fp,"$count",strlen($count));
	fclose($fp);

?>
