<?php
	$filename = "Data.txt";
	$fp = fopen($filename,"r"); //Data.txt를 열음
	$origin_content = fread($fp,filesize($filename));
	fclose($fp);
	//Data.txt의 내용을 fread로 읽어오고 Data.txtf를 close
	
	echo("<h1>게시판 읽기</h1>");
	//페이지 제목을 출력
	echo("<textarea readonly rows='10' cols='50'>$origin_content</textarea>");
	//읽기전용인 textarea에 읽어온 origin_content를 출력
	echo("<br/><br/><a href='Board_main.php'>메인으로 되돌아 가기</a>");
	echo("<br/><a href='Board_write.php'>게시판 글쓰러 가기</a>");
	//메인화면과 글쓰기로 이동하는 하이퍼링크를 만든다.

?>
