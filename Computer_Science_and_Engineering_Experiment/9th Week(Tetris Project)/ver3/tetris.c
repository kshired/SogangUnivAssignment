﻿#include "tetris.h"
int holdingNum = -1;
static struct sigaction act, oact;
int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	
    start_color();
	for(int i = 0; i < 7; i++) {
		init_pair(blockColor[i], blockColor[i], COLOR_BLACK);
	}
	srand((unsigned int)time(NULL));
    createRankList();
	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
        case MENU_RANK: rank();break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
    writeRankFile();
	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=NO_BLOCK;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	//DrawNextBlock2(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(0,WIDTH+8);
	printw("NEXT BLOCK");
	DrawBox(1,WIDTH+8,4,7);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(7,WIDTH+8);
	printw("SCORE");
	DrawBox(8,WIDTH+8,1,8);

	move(12,WIDTH+8);
	printw("NEXT2 BLOCK");
	DrawBox(13,WIDTH+8,4,7);
/*
    move(19,WIDTH+8);
	printw("HOLD BLOCK");
	DrawBox(20,WIDTH+8,3,8);*/
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int tmpY;
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	case ' ':
		tmpY = blockY;
		while(CheckToMove(field,nextBlock[0],blockRotate,tmpY+1,blockX)){
			tmpY++;
		}
		blockY = tmpY;
		drawFlag = 1;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]!=NO_BLOCK){
				attron(A_REVERSE|COLOR_PAIR(field[j][i]));
				printw(" ");
				attroff(A_REVERSE|COLOR_PAIR(field[j][i]));
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(9,WIDTH+9);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for(int k=1;k<3;k++){
		for( i = 0; i < 4; i++ ){
			move(2+i+(k-1)*12,WIDTH+11);
			for( j = 0; j < 4; j++ ){
				if( block[nextBlock[k]][0][i][j] == 1 ){
					attron(A_REVERSE|COLOR_PAIR(blockColor[nextBlock[k]]));
					printw(" ");
					attroff(A_REVERSE|COLOR_PAIR(blockColor[nextBlock[k]]));
				}
				else printw(" ");
			}
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE|COLOR_PAIR(blockColor[blockID]));
				printw("%c",tile);
				attroff(A_REVERSE|COLOR_PAIR(blockColor[blockID]));
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out = 1;
		}
		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
		
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				if(f[blockY+i][blockX+j]!=NO_BLOCK) return 0;
				if(blockY+i>=HEIGHT) return 0;
				if(blockX+j<0) return 0;
				if(blockX+j>=WIDTH) return 0;
			}
		}
	}
	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
    int dropY;
	
    switch(command) {
		case KEY_UP:
            dropY = DropCheck(blockY, blockX, currentBlock, (blockRotate+3)%4);
			Erase(dropY, blockX, currentBlock, (blockRotate+3)%4);
			Erase(blockY, blockX, currentBlock, (blockRotate+3)%4);
			break;
		case KEY_DOWN:
            Erase(blockY-1, blockX, currentBlock, blockRotate);
			break;
		case KEY_LEFT:
            dropY = DropCheck(blockY, blockX+1, currentBlock, blockRotate);
			Erase(dropY, blockX+1, currentBlock, blockRotate);
			Erase(blockY, blockX+1, currentBlock, blockRotate);
			break;
		case KEY_RIGHT:
            dropY = DropCheck(blockY, blockX-1, currentBlock, blockRotate);
			Erase(dropY, blockX-1, currentBlock, blockRotate);
			Erase(blockY, blockX-1, currentBlock, blockRotate);
	}
	// draw the new image
	DrawBlockWithFeatures(blockY,blockX,currentBlock,blockRotate);
    move(HEIGHT,WIDTH+10);
}

void BlockDown(int sig){
	// user code
    if(CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)){
        blockY++;
        DrawChange(field,KEY_DOWN,nextBlock[0],blockRotate,blockY,blockX);
    }else{
        if(blockY==-1)
            gameOver = TRUE;
        score+=AddBlockToField(field,nextBlock[0],blockRotate,blockY,blockX);
		score+=DeleteLine(field);
        blockY=-1;blockX=(WIDTH/2)-2;blockRotate=0;
        nextBlock[0] = nextBlock[1];
        nextBlock[1] = nextBlock[2];
        nextBlock[2] = rand()%7;
        DrawNextBlock(nextBlock);
        PrintScore(score);
		DrawField();
    }
    timed_out = 0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
    int scr = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(block[currentBlock][blockRotate][i][j]==1){
				f[blockY+i][blockX+j] = blockColor[currentBlock];
                if((blockY+i == HEIGHT-1) || (f[blockY+i+1][blockX+j] != NO_BLOCK)){
					scr++;
                }
			}
        }
    }
    return scr*10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
    int count = 0;
	int fullFlag;
	for(int i = 0; i < HEIGHT; i++) { 
		fullFlag = 1;
		for(int j = 0; j < WIDTH; j++) {
			if(f[i][j] == NO_BLOCK) {
				fullFlag = 0;
				break;
			}
		}
		if(fullFlag) {
			count++;
			for(int k = i-1; k >= 0; k--) {
				for(int j = WIDTH; j > 0; j--) {
					f[k+1][j] = f[k][j];
				}
			}
		}
	}
	return count*count*100;
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	int dropY;
	dropY = blockY;
	while(CheckToMove(field,nextBlock[0],blockRotate,dropY+1,blockX)){
		dropY++;
	}
	DrawBlock(dropY, x, blockID, blockRotate, '/');
}
void createRankList(){
	FILE* fp;
	int number_of_rank;
	int score;
	char name[NAMELEN];
	
	int buffer_int;
	int i, temp;
	
	// open "rank.txt"
	fp = fopen(RANK_FILE_NAME, "rt");

	// if file does not exist, create and initialize
	if(fp == NULL) {
		fp = fopen(RANK_FILE_NAME, "wt");
		fprintf(fp, "0\n");
		// create an empty red-black tree
		tree = rbNewTree();
	}

	// read ranking from file "rank.txt"
	else {
		tree = rbNewTree();
		fscanf(fp, "%d", &number_of_rank);
		
		for(i = 0; i < number_of_rank; i++) {
			fscanf(fp, "%s%d", name, &score);
			rbInsert(tree, rbNewNode(score, name));
		}
	}

	// close "rank.txt"
	fclose(fp);

	rank_change_flag = 0;
}
void rank(){
	int command;
	int x, y;
	int i;
	char name[NAMELEN];
	rbnode ** nodes = NULL;

	do {
		clear();
		printw("1. list ranks from X to Y\n");
		printw("2. list ranks by a specific name\n");
		printw("3. delete a specific rank\n");
		command = wgetch(stdscr);
	} while(!('1' <= command && command <= '3'));
	echo();
	switch(command) {
		case RANK_BY_RANGE: // list ranks from X to Y
			printw("X: ");
			scanw("%d", &x);
			printw("Y: ");
			scanw("%d", &y);
			
			// check for parameter sanity
			if(x < 1 || x > tree->size) {
				x = 1;
			}
			if(y < 1 || y > tree->size) {
				y = tree->size;
			}

			printw(" rank |       name       |   score   \n");
			printw("-------------------------------------\n");
			// case: search fail
			if(x > y) {
				printw("\nsearch failure: no rank in the list\n");
			}
			// case: query and print
			else {
				nodes = rbSelectByRange(tree, x, y);
				for(i = 0; i < y-x+1; i++) {
					printw(" %4d | %-17s| %-10d\n", i+x, nodes[i]->name, nodes[i]->score);
				}
				if(nodes) {
					free(nodes);
				}
			}
			break;
		case RANK_BY_NAME: // search rank by name
			printw("input the name: ");
			scanw("%s", name);
			
			// get list of all ranks and search for matching name
			printw(" rank |       name       |   score   \n");
			printw("-------------------------------------\n");
			x = 0;
			nodes = rbSelectByRange(tree, 1, tree->size);
			for(i = 0; i < tree->size; i++) {
				if(strcmp(name, nodes[i]->name) == 0) {
					printw(" %4d | %-17s| %-10d\n", i+1, nodes[i]->name, nodes[i]->score);
					x = 1;
				}
			}
			// case: search fail
			if(!x) {
				printw("\nsearch failure: no name in the list\n");
			}
			if(nodes) {
				free(nodes);
			}
			break;
		case RANK_DELETE_BY_NO: // delete data of given rank number
			printw("input the rank: ");
			scanw("%d", &x);

			if(rbDelete(tree, x) == 0) {
				printw("result: the rank deleted\n");
				rank_change_flag = 1;
			}
			else {
				printw("search failure: the rank is not in the list\n");
			}
			break;
	}
	noecho();
	getch();
}

void writeRankFile(){
	FILE *fp;
	rbnode ** nodes;
	int i;

	if(!rank_change_flag) {
		return;
	}

	fp = fopen(RANK_FILE_NAME, "wt");

	// get list of all ranks
	nodes = rbSelectByRange(tree, 1, tree->size);

	// write it to file
	fprintf(fp, "%d\n", tree->size);
	for(i = 0; i < tree->size; i++) {
		fprintf(fp, "%s %d\n", nodes[i]->name, nodes[i]->score);
	}

	// free memory and close file
	if(nodes) {
		free(nodes);
	}
	rbDestroyTree(tree);
	fclose(fp);
}

void newRank(int score){
	char name[NAMELEN];
	int y;
	int i;
	int rank;
	rbnode * new_node;
	rbnode ** nodes;
	
	// input a user name
	clear(); echo();
	printw("your name: ");
	scanw("%s", name);
	noecho();
	
	// create a new node and insert it to the tree
	new_node = rbNewNode(score, name);
	rbInsert(tree, new_node);
	rank = rbRankByNode(tree, new_node);
	rank_change_flag = 1;


	// print rank of the new score
	if(tree->size < 5) {
		y = tree->size;
	}
	else {
		y = 5;
	}
	printw(" rank |       name       |   score   \n");
	printw("-------------------------------------\n");
	nodes = rbSelectByRange(tree, 1, y);
	for(i = 0; i < y; i++) {
		if(i == rank-1) {
			attron(A_REVERSE);
		}
			printw(" %4d | %-17s| %-10d\n", i+1, nodes[i]->name, nodes[i]->score);
		if(i == rank-1) {
			attroff(A_REVERSE);
		}
	}

	if(rank > y) {
		attron(A_REVERSE);
		printw(" %4d | %-17s| %-10d\n", rank, name, score);
		attroff(A_REVERSE);
	}

	if(nodes) {
		free(nodes);
	}
	getch();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}
int DropCheck(int y, int x, int blockID, int blockRotate){
	int dropY = y;
	while(CheckToMove(field, nextBlock[0], blockRotate, dropY+1, x))
		dropY++;
	return dropY;
}
void Erase(int y, int x, int blockID, int blockRotate) {
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				printw(".");
			}
		}

	move(HEIGHT,WIDTH+10);
}
void DrawBlockWithFeatures(int y, int x,int blockID, int blockRotate){
    DrawBlock(y, x, blockID, blockRotate, ' ');
    DrawShadow(y, x, blockID, blockRotate);
}
