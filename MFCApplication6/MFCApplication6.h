
// MFCApplication6.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplication6App: 
// �йش����ʵ�֣������ MFCApplication6.cpp
//

class CMFCApplication6App : public CWinApp
{
public:
	CMFCApplication6App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication6App theApp;