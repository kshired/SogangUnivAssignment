#ifndef __WATERFALLSOLVER_H__
#define __WATERFALLSOLVER_H__

#include "stdafx.h"
#include "define.h"

void F1(void);							//F1
void F2(LPCTSTR fname);					//F2 : data �ʱ�ȭ ��ȯ ���� ���� ����
void F3(void);							//F3 : ������ Ǫ�� �Լ� �Է��� �ش�

void F4(CDC* pDC);						//F4 : ��׶��带 �׸���.
void F5(CDC* pDC);						//F5 : ���� �������� ��Ÿ����.
void F6(CDC* pDC);						//F6 : ���� ���������� ���� �帧�� �׸���.

void F7(void);			//start point�� �ٲٴ� �Լ�

#endif