
// WebBrowser_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWebBrowser_MFCApp:
// �йش����ʵ�֣������ WebBrowser_MFC.cpp
//

class CWebBrowser_MFCApp : public CWinApp
{
public:
	CWebBrowser_MFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWebBrowser_MFCApp theApp;