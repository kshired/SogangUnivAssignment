#ifndef __WATERFALLSOLVER_H__
#define __WATERFALLSOLVER_H__

#include "stdafx.h"
#include "define.h"

void F1(void);							//F1
void F2(LPCTSTR fname);					//F2 : data 초기화 반환 수는 점의 갯수
void F3(void);							//F3 : 문제를 푸는 함수 입력은 해당

void F4(CDC* pDC);						//F4 : 백그라운드를 그린다.
void F5(CDC* pDC);						//F5 : 현재 시작점을 나타낸다.
void F6(CDC* pDC);						//F6 : 현재 시작점에서 물의 흐름을 그린다.

void F7(void);			//start point를 바꾸는 함수

#endif