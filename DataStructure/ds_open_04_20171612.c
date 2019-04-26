#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE true
#define FALSE false
#define M 103
#define P 103
#define MAX_DIRECTION_SIZE 8
#define MAX_STACK_SIZE M * P

#define _MDH_DEBUG_

/* Structure definition  */
typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

typedef struct {
	short int vert;
	short int horiz;
}offsets;

/* Global Variables Region */

int maze[M][P];
int mark[M][P];
offsets move[MAX_DIRECTION_SIZE] = { { -1,0 },{ -1,1 },{ 0,1 },{ 1,1 }, { 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };
int EXIT_ROW, EXIT_COL;

/* Stack */
element stack[MAX_STACK_SIZE];
int top;

/* Functions to be implemented */
void push(int *top, element position) {

	(*top)++;
	stack[*top].row = position.row;
	stack[*top].col = position.col;
	stack[*top].dir = position.dir;

}


element pop(int *top) {
	element tmp;

	tmp = stack[*top];
	(*top)--;

	return tmp;
}

void path() {
	int i, row, col, next_row, next_col, dir, found = FALSE;
	element position;
	mark[1][1] = 1;
	top = 0;
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;
	
	if (maze[EXIT_ROW - 1][EXIT_COL] + maze[EXIT_ROW][EXIT_COL - 1] + maze[EXIT_ROW - 1][EXIT_COL - 1] == 3) {
		printf("The maze dose not have a path\n");
		return;
	}

	if (maze[EXIT_ROW][EXIT_COL] == 1) {
		printf("The maze dose not have a path\n");
		return;
	}

	while (top > -1 && !found) {
		position = pop(&top);
		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROW && next_col == EXIT_COL) {
				found = TRUE;
			}
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = 3;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(&top, position);
				row = next_row;
				col = next_col;
				dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path\n");
		printf("row col\n");

		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}

	else printf("The maze dose not have a path\n");
}

/* Functions already implemented by MDH*/

void PrintMaze();
void ReadMaze();

/* main Function */
int main() {
	ReadMaze();
	path();
	return 0;
}
void ReadMaze(){

	FILE* _read_fp = fopen("maze.txt", "r");
	int i;

	/* File Validation Check */
	if (!_read_fp) {
		fprintf(stderr, "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á\n");
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be Shutdown\n");
		fprintf(stderr, "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á\n");
		exit(0);
	}

	/* Scanning Input */
	fscanf(_read_fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	for (i = 1; i <= EXIT_ROW; i++) {
		char tmp[M][P];
		fscanf(_read_fp, "%s", &tmp[i][1]);

		for (int j = 1; j <= EXIT_COL; j++) {
			maze[i][j] = (int)(tmp[i][j] - '0');
		}

	}
		/* Enveloping maze in '1' which indicates artificial wall */
	for (i = 0; i <= EXIT_COL + 1; i++) {
		maze[0][i] = 1;
		maze[EXIT_ROW + 1][i] = 1;
	}
	for (i = 0; i <= EXIT_ROW + 1; i++) {
		maze[i][0] = 1;
		maze[i][EXIT_COL + 1] = 1;
	}
	fclose(_read_fp);
}

void PrintMaze() {
	int i, j;
#ifdef _MDH_DEBUG_
	printf("Input Checking\n");
	printf("%d %d\n", EXIT_ROW, EXIT_COL);
#endif
	for (i = 0; i <= EXIT_ROW + 1; i++) {
		for (j = 0; j <= EXIT_COL + 1; j++) {
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}
}