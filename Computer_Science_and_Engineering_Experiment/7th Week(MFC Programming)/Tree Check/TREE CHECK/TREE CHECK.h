
// TREE CHECK.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTREECHECKApp:
// �� Ŭ������ ������ ���ؼ��� TREE CHECK.cpp�� �����Ͻʽÿ�.
//

class CTREECHECKApp : public CWinApp
{
public:
	CTREECHECKApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTREECHECKApp theApp;