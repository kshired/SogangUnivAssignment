#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50 
#define IS_FULL(X) (!(X))

typedef enum { head, entry }tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer mread(FILE *f, int rrow, int rcol, int rterm);
matrix_pointer new_node(void);
void mwrite(matrix_pointer node);
void merase(matrix_pointer *node);

int main() {
	int r, c, tmp, i, j,check = 0;
	matrix_pointer a, b;
	FILE *fp_A = fopen("A.txt", "r");
	FILE *fp_B = fopen("B.txt", "r");
	FILE *f1 = fopen("tmp1.txt", "w+");
	FILE *f2 = fopen("tmp2.txt", "w+");

// 희소행렬을 변환
	fscanf(fp_A, "%d %d", &r, &c);
	for(i = 0; i < r; i++) {
		for(j=0; j<c; j++) {
			fscanf(fp_A, "%d", &tmp);
			if(tmp!=0) {
				fprintf(f1, "%d %d %d\n", i, j, tmp);
				check++;
			}
		}
	}
	fclose(f1);
	f1 = fopen("tmp1.txt", "r");
	
	a = mread(f1, r, c, check);
	
	check = 0;
	fscanf(fp_B, "%d %d", &r, &c);
	for(i = 0; i < r; i++) {
		for(j = 0; j<c; j++) {
			fscanf(fp_B, "%d", &tmp);
			if(tmp != 0) {
				fprintf(f2, "%d %d %d\n", i, j, tmp);
				check++;
			}
		}
	}
	fclose(f2);
	f2 = fopen("tmp2.txt", "r");

	b = mread(f2, r, c, check);

	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);

	//file close and temp file remove
	fclose(fp_A);
	fclose(fp_B);
	fclose(f1);
	fclose(f2);
	remove("tmp1.txt");
	remove("tmp2.txt");
	return 0;

}

matrix_pointer mread(FILE *f, int rrow, int rcol, int rterm) {
	int num_rows, num_cols, num_terms, num_heads, i;
	int row, col, value, current_row;

	matrix_pointer temp, last, node;

	num_rows = rrow;
	num_cols = rcol;
	num_terms = rterm;
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;

	node = new_node();
	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if(!num_heads)
		node->right = node;
	else {
		for(i = 0; i<num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0];

		for(i = 0; i<num_terms; i++) {
			fscanf(f, "%d %d %d", &row, &col, &value);
			if(row>current_row) {
				last->right = hdnode[current_row];
				current_row = row;
				last = hdnode[row];
			}
			temp = new_node();
			temp->tag = entry;

			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;

			last->right = temp;
			last = temp;

			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[current_row];

		for(i = 0; i<num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];

		for(i = 0; i<num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];

		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}

matrix_pointer new_node(void) {
	matrix_pointer temp;

	temp = (matrix_pointer)malloc(sizeof(matrix_node));

	if(IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	return temp;
}
void mwrite(matrix_pointer node) {
	if(node == NULL) {
		return;
	}
	int i, j;
	matrix_pointer temp, head = node->right;
	int **a = (int**)malloc(sizeof(int*)*node->u.entry.row);
	for(i = 0; i < node->u.entry.row; i++) {
		a[i] = (int*)malloc(sizeof(int)*node->u.entry.col);
	}
	for(i = 0; i < node->u.entry.row; i++) {
		for(j = 0; j < node->u.entry.col; j++) {
			a[i][j] = 0;
		}
	}

	for(i = 0; i<node->u.entry.row; i++) {
		for(temp = head->right; temp != head; temp = temp->right)
			a[temp->u.entry.row][temp->u.entry.col] = temp->u.entry.value;
		head = head->u.next;
	}

	for(i = 0; i < node->u.entry.row; i++) {
		for(j = 0; j < node->u.entry.col; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	for(i = 0; i < node->u.entry.row; i++) {
		free(a[i]);
	}
	free(a);
}


void merase(matrix_pointer *node) {\
	if(*node == NULL) {
		return;
	}
	matrix_pointer x, y, head = (*node)->right;
	int i;
	for(i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while(y != head) {
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}

	y = head;

	while(y != *node) {
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*node);

	*node = NULL;
}
