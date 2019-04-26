<?php
	$content = $_POST[content];
	//write로부터 POST되어온 데이터 읽기
	$filename = "Data.txt";
	//Data.txt에서 읽어오거나 저장.

	if($content){ //content가 존재하면
		$fp = fopen($filename,"w"); //Data.txt를 열고
		fwrite($fp,"$content",strlen($content));
		fclose($fp);
		//content의 내용을 fwrite로 저장후 Data.txt를 close
	}
	echo("<a href='Board_write.php'>게시판 글쓰기</a>");
	echo("<br/><a href='Board_read.php'>게시판 읽기</a>");
	//a href 태그와 echo를 이용하여 게시판 글쓰기와 읽기로 이동하게 연결
?>