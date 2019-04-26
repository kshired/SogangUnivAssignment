#include <stdio.h>
#include <stdlib.h>
#define MAX 101
#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
typedef struct _Polynomial {
	int coef; // 계수
	int exp; // 지수
}Poly;
Poly terms[MAX]; // 다항식을 읽어오기 위한 전역변수
int avail = 0; // Index
void readpoly(int *start, int *finish, char *name) {
	FILE *f;
	int a, b;
	int res;
	f = fopen(name, "r"); // char형 str로 fopen
	if (avail != 0) avail += 1; // 예외처리
	*start = avail;
	while(1){  //eof면 while문 break
		res = fscanf(f, "%d %d", &a, &b);
		if (res == EOF) break;
		terms[avail].coef = a;
		terms[avail].exp = b;
		avail++;
	}
	avail -= 1;
	*finish = avail;
	fclose(f); // 꼭! fclose
}
void printpoly(int start, int finish) {
	for (int i = start; i <= finish; i++) {
		printf("(%d,%d), ", terms[i].coef, terms[i].exp);
	}
}
void attach(int coefficient, int exponent) {
	if (avail >= MAX) {
		printf("Too Many terms n the Polynomial!!\n");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].exp = exponent;
}
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
	int coefficient;
	avail += 1;
	*startd = avail;
	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(terms[starta].exp, terms[startb].exp)) {
		case -1: attach(terms[startb].coef, terms[startb].exp);
			startb++;
			break;
		case 0: coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient) attach(coefficient, terms[starta].exp);
			starta++;
			startb++;
			break;
		case 1: attach(terms[starta].coef, terms[starta].exp);
			starta++;
		}
	}
	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].exp);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].exp);
	*finishd = avail-1;

}
int main() {
	char *a = "A.txt"; // A.txt 읽어오기 위한 char형 str
	char *b = "B.txt"; // B.txt 읽어오기 위한 char형 str
	int sA, fA;
	int sB, fB;
	int sD, fD; // start,finish A,B (입력) , D ( 두 입력의 합)

	readpoly(&sA, &fA, a);
	readpoly(&sB, &fB, b);
	padd(sA, fA, sB, fB, &sD, &fD); // 두 다항식 합치기.
	printpoly(sD, fD - 1);
	printf("(%d,%d)\n", terms[fD].coef, terms[fD].exp); // 제출 출력형식.	

	return 0;
}
