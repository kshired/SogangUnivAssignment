#include "stdafx.h"
#include "Waterfallsolver.h"
 
#include "stdio.h"
#include "stdlib.h"
 
#define mm (waterpath* )malloc(sizeof(waterpath))
#define gradient (float)(mline[i].yl-mline[i].yr)/(float)(mline[i].xl-mline[i].xr)
 
Line *mline;
Point *mpoint;
int mLine_num;
int mPoint_num;
int first_flag=0;
int Data_flag=0;
 
typedef struct waterpath
	{
		float x;
		float y;
		waterpath* node;
	} waterpath;
 
int pathnumber=0;
int i;
waterpath* path=NULL;
 
void F1()
{
	waterpath* prevptr,*ptr;
	if(path!=NULL)
	{
		prevptr=path;
		ptr=prevptr->node;
		while(prevptr!=NULL)
		{
			free(prevptr);
			prevptr=ptr;
			if(ptr!=NULL)
				ptr=ptr->node;
		}
	}
	if(mline!=NULL) free(mline);
	if(mpoint!=NULL) free(mpoint);
	mLine_num=0;
	mPoint_num=0;
	first_flag=0;
	Data_flag=0;
 
	pathnumber=0;
	
}
void F2(LPCTSTR fname)
{
	FILE* fp;
	fp = fopen(fname,"r");
	fscanf(fp,"%d",&(mLine_num));
	mline = (Line *)malloc((mLine_num)*sizeof(Line));
	for(i=0;i<mLine_num;i++)
	{
		fscanf(fp,"%d %d %d %d",&(mline[i].xl),&(mline[i].yl),&(mline[i].xr),&(mline[i].yr));
	}
	fscanf(fp,"%d",&(mPoint_num));
	mpoint = (Point *)malloc((mPoint_num)*sizeof(Point));
	for(i=0;i<mPoint_num;i++)
	{
		fscanf(fp,"%f %f",&(mpoint[i].x),&(mpoint[i].y));
	}
	Data_flag = 1;
	fclose(fp);
}
void F3()
{
	waterpath * current;
	float least;
	int leasti;
	float heek,left,right;
	if(!Data_flag)
		return;
	current = path = mm;
	current->x = mpoint[pathnumber].x;
	current->y = mpoint[pathnumber].y;
	current->node = NULL;
	while(current->y!=0)
	{
		for(first_flag=0,leasti=-1,i=0;i<mLine_num;i++)
		{
			left = mline[i].xl < mline[i].xr ? (float)mline[i].xl : (float)mline[i].xr;
			right = mline[i].xl < mline[i].xr ? (float)mline[i].xr : (float)mline[i].xl;
			if((left<current->x)&&(right>current->x))
			{
				heek = (gradient) * ( current->x - (float)mline[i].xl ) + (float)mline[i].yl;
				if(((current->y) - heek)>0)
				{
					if(!first_flag)
					{
						first_flag = 1;
						least = current->y - heek;
						leasti = i;
					}
					if(least > (current->y - heek))
					{
						least = current->y - heek;
						leasti = i;
					}
				}
			}
		}
		if(leasti==-1)
		{
			current->node = mm;
			current->node->x = current->x;
			current->node->y = 0;
			current->node->node = NULL;
			current = current->node;
		}
		else
		{
			current->node = mm;
			current->node->x = current->x;
			current->node->y = current->y - least;
			current->node->node = mm;
			current = current->node;
			current->node->x = mline[leasti].yl < mline[leasti].yr ? mline[leasti].xl : mline[leasti].xr; 
			current->node->y = mline[leasti].yl < mline[leasti].yr ? mline[leasti].yl : mline[leasti].yr;
			current->node->node = NULL;
			current = current->node;
		}
 
	}
 
}
void F4(CDC* pDC)
{
	if(!Data_flag)
		return;
	CPen MyPen;
	MyPen.CreatePen(PS_SOLID,10,RGB(0,0,0));
	pDC->SelectObject(MyPen);
	pDC->MoveTo(gXmin,gYmin); pDC->LineTo(gXmax,gYmin);
	pDC->MoveTo(gXmin,gYmax); pDC->LineTo(gXmax,gYmax);
	for(i=0;i<mLine_num;i++)
	{
		pDC->MoveTo(lineSize*mline[i].xl+gXmin,gYmax-lineSize*mline[i].yl);
		pDC->LineTo(lineSize*mline[i].xr+gXmin,gYmax-lineSize*mline[i].yr);
	}
	MyPen.DeleteObject();
	MyPen.CreatePen(PS_SOLID,10,RGB(0,0,0));
	pDC->SelectObject(MyPen);
	for(i=0;i<mPoint_num;i++)
	{
		if(i!=pathnumber)
		{
			pDC->MoveTo(lineSize*mpoint[i].x+gXmin,gYmax-lineSize*mpoint[i].y);
			pDC->LineTo(lineSize*mpoint[i].x+gXmin,gYmax-lineSize*mpoint[i].y);
		}
	}
	MyPen.DeleteObject();
}
void F5(CDC* pDC)
{
	if(!Data_flag)
		return;
	CPen MyPen;
	MyPen.CreatePen(PS_SOLID,10,RGB(255,0,0));
	pDC->SelectObject(MyPen);
		pDC->MoveTo(lineSize*mpoint[pathnumber].x+gXmin,gYmax-lineSize*mpoint[pathnumber].y);
		pDC->LineTo(lineSize*mpoint[pathnumber].x+gXmin,gYmax-lineSize*mpoint[pathnumber].y);
	MyPen.DeleteObject();
}
void F6(CDC* pDC)
{
	waterpath* prevptr, *ptr;
	if(!Data_flag)
		return;
	prevptr = path;
	ptr = path->node;
	CPen MyPen;
	MyPen.CreatePen(PS_SOLID,10,RGB(0,0,255));
	pDC->SelectObject(MyPen);
	while(ptr!=NULL)
	{
		pDC->MoveTo(lineSize*(prevptr->x)+gXmin,gYmax-lineSize*(prevptr->y));
		pDC->LineTo(lineSize*(ptr->x)+gXmin,gYmax-lineSize*(ptr->y));
		prevptr = ptr;
		ptr = ptr->node;
	}
	MyPen.DeleteObject();
}
void F7(void)
{
	if(!Data_flag)
		return;
	if(pathnumber<mPoint_num-1)
		pathnumber++;
	else
		pathnumber=0;
}