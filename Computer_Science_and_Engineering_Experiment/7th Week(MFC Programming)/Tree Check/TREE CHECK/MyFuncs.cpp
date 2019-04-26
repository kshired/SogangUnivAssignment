#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "MyHeader.h"

#define mm1(A) (CASES *)malloc(sizeof(CASES)*(A))
#define mm2(A) (node *)malloc(sizeof(node)*(A))
#define T testCases[number]

CASES *testCases;
int testCaseNum;
int currentCase;
char resultString[1000];

char *ConvertString(int currentCase)
{
	char* a,temp;
	a = (char *)malloc(sizeof(char)*1000);
	int i;
	int length=0;
	int temp_case;
	for(temp_case = currentCase,i=0;temp_case;i++)
	{
		a[i] = '0'+(temp_case%10);
		temp_case = temp_case/10;
	}
	a[i] = '\0';
	for(i=0;i<(strlen(a)/2);i++)
	{
		temp = a[i];
		a[i] = a[strlen(a)-1];
		a[strlen(a)-1] = temp;
	}
	return a;
}

bool Singlefind(int* P,int max)
{
	int i,current,current2,currentnum;
	for(current=-1,i=0;i<=max;i++)
	{
		if(!P[i])
		{
			current = i;
			break;
		}
	}
	if(current==-1)
		return true;
	for(currentnum=0,i=0;i<=max;i++)
	{
		if(P[i]==current)
		{
			current2 = i;
			currentnum++;
		}
	}
	if(currentnum>1)
		return false;
	for(current=-1,i=0;i<=max;i++)
	{
		if(P[i]==current2)
			return false;
	}
	return true;
}

bool Cyclefind(int* P,int max)
{
	int reback;
	int i,current;

	for(reback=-1,i=0;i<=max;i++,reback=-1)
	{
		current = i;
		if(P[current]==-1)
			continue;
		while(P[current]!=0)
		{
			if(reback==-1)
			{
				reback = current;
				current = P[current];
				continue;
			}
			if(reback==current)
				return true;
			current = P[current];
		}
	}
	return false;
}

void F1()
{         
	int i;
	for(i=0;i<testCaseNum;i++)
		free(testCases[i].nodes);
	free(testCases);
	testCaseNum = 0;
	currentCase = 0;
	for(i=0;i<1000;i++)
		resultString[i]=0;
}
void F2(const char *filename)
{
	int i,j;
	FILE *fp;
	fp = fopen(filename,"r");
	fscanf(fp,"%d",&testCaseNum);
	testCases=mm1(testCaseNum);
	for(i=0;i<testCaseNum;i++)
	{
		fscanf(fp,"%d",&(testCases[i].intpair));
		testCases[i].nodes = mm2(testCases[i].intpair);
		for(j=0;j<testCases[i].intpair;j++)
			fscanf(fp,"%d %d",&(testCases[i].nodes[j].pre),&(testCases[i].nodes[j].suc));
	}
}
char* F3(int number)//number == currentCase
{
	char *str2;
	int i;
	int max;
	int *P;
	bool non_tree_flag=0,temp_flag;
	int zero_find_flag;
	for(i=0;i<1000;i++)
		resultString[i] = 0;
	for(max=T.nodes[0].pre,i=1;i<T.intpair;i++)
		if(max<T.nodes[i].pre)
			max = T.nodes[i].pre;
	for(i=0;i<T.intpair;i++)
		if(max<T.nodes[i].suc)
			max = T.nodes[i].suc;
	P = (int *)malloc(sizeof(int)*(max+1));
	for(i=0;i<=max;i++)
		P[i] = -1;

	for(i=0;i<T.intpair;i++)
	{
		if ( P[T.nodes[i].pre] == -1 )
			P[T.nodes[i].pre] = 0;        // membership setting
		if ( P[T.nodes[i].suc] <= 0 )
			P[T.nodes[i].suc] = T.nodes[i].pre;        // predecessor setting
		else
			non_tree_flag=1; // has more than one predecessors
	}

	for(zero_find_flag=0,i=0;i<=max;i++)
	{
		if(!P[i])
			zero_find_flag++;
		if(zero_find_flag>1)
		{
			non_tree_flag=1;
			break;
		}
	}

	temp_flag = Singlefind(P,max);
	if(temp_flag)
		non_tree_flag = temp_flag;

	temp_flag = Cyclefind(P,max);
	if(temp_flag)
		non_tree_flag = temp_flag;
	
	free(P);

	strcpy(resultString,"Case ");
	str2=ConvertString(number+1);
	strcat(resultString,str2);
	if(non_tree_flag)
		strcat(resultString," is not a tree");
	else
		strcat(resultString," is a tree");
	free(str2);
	return resultString;
}

