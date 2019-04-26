#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MALLOC(x, y) x=(struct node *)malloc(y)
#define IS_FULL(ptr) (!(ptr))

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} Node;

void push(nodePointer* top, int value) {
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));
	if(IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->data = value;
	temp->link = *top;
	*top = temp;
}

int pop(nodePointer* top) {
	nodePointer temp = *top;
	int item;
	if(temp == NULL) {
		fprintf(stderr, "The stack is empty\n");
		exit(1);
	}
	item = temp->data;
	*top = temp->link;
	free(temp);
	return item;
}

int main(void) {
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, top;
	int i, j, n;

	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &n);

	for(i = 0; i < n; i++) {
		out[i] = TRUE; seq[i] = NULL;
	}

	fscanf(fp, "%d %d", &i, &j);

	while(i >= 0) {
		push(&seq[i], j);
		push(&seq[j], i);
		fscanf(fp, "%d %d", &i, &j);
	}
	for(i = 0; i < n; i++) {
		if(out[i]) {
			printf("\nNew Class : % 5d", i);
			out[i] = FALSE;
			x = seq[i];
			top = NULL;
			for(; ; ) {
				while(x) {
					j = x->data;
					if(out[j]) {
						printf("%5d", j); out[j] = FALSE;
						pop(&x);
						push(&top, j);
					}
					else
						pop(&x);
				}
				if(!top) break;
				
				x = seq[top->data];
				pop(&top);
			}
		}
	}
	printf("\n");

	return 0;
}
