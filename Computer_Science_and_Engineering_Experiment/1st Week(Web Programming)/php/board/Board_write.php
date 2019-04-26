<?php
	//제목 출력
	echo("<h1>게시판 쓰기</h1>");

	//form을 이용하여 Board_read로 POST
	//name = content로 textarea의 내용을 POST
	echo("
		<form action='Board_main.php' method='POST'>
		<textarea name='content' placeholder='입력하세요' rows='10' cols='50'></textarea>
		<br/>
		<button type='submit'>등록하기</button>
		<button type='reset'>다시기입</button>	
		</form>	
	");
	// submit과 reset 타입을 이용해 등록하기와 다시기입 버튼 구현
	
	echo("<br/><br/><a href='Board_main.php'>메인으로 되돌아가기</a>");	
	echo("<br/><a href='Board_read.php'>게시판 내용 읽으러가기</a>");	
	//메인과 게시판 읽기로 가는 하이퍼링크 생성
?>
