#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 1000

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
typedef struct _node {
	precedence pr;
	struct _node *next;
}Node;
typedef struct _stack {
	Node * head;
}Stack;
Stack stack;
/* Global Variables */

/* expression */
char expr[MAX_EXPR_SIZE];
/* isp, icp */
static int isp[] ={ 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] ={ 20, 19, 12, 12, 13, 13, 13, 0 };



/* Functions already implemented by MDH */
void readExpr(FILE* _fp, char* _expr);

/* Functions to be implemented by you */
precedence getToken(char*, int*);
void postfix();
void printToken(precedence);
/* Functions relavant to stack also will be implemented by you. */
precedence pop();
void push(precedence);

int main()
{
	/* Local variables */
	FILE* readfp = fopen("infix.txt", "r");

	readExpr(readfp, expr);
	expr[strlen(expr)] = ' ';
	postfix();
	return 0;
}
void readExpr(FILE* _fp, char* _expr)
{

	/* File Existence Check */
	if(!_fp) {
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be shutdown\n");
		exit(0);
	}

	/* Scanning Input */
	fscanf(_fp, "%s", _expr);

	fclose(_fp);
}
precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch(*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return eos;
	default: return operand;
	}
}
void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	int top = 0;
	push(eos);
	for(token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if(token == operand) printf("%c", symbol);
		else if(token == rparen) {
			while(stack.head->pr != lparen)
				printToken(pop());
			pop();
		}
		else {
			while(isp[stack.head->pr] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
void printToken(precedence pr) {
	switch(pr) {
	case lparen: printf("("); break;
	case rparen: printf(")"); break;
	case plus: printf("+"); break;
	case minus: printf("-"); break;
	case divide: printf("/"); break;
	case times: printf("*"); break;
	case mod: printf("%%"); break;
	case eos: printf(" "); break;
	default: return;
	}
}
/* Functions relavant to stack also will be implemented by you. */
precedence pop() {
	precedence rp;
	Node *rnode;

	rp = stack.head->pr;
	rnode = stack.head;

	stack.head = stack.head->next;
	free(rnode);
	return rp;

}
void push(precedence pr) {
	Node * newNode = (Node*)malloc(sizeof(Node));

	newNode->pr = pr;
	newNode->next = stack.head;

	stack.head = newNode;
}