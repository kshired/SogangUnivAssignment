#ifndef __MYHEADER_H__
#define __MYHEADER_H__

#include "stdafx.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	int pre;//predecessor
	int suc;//successor
} node;
typedef struct
{
	int intpair;
	node* nodes;
} CASES;

void F1();
void F2(const char * filename);
char* F3(int number);

#endif