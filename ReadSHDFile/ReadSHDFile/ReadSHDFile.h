
// ReadSHDFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadSHDFileApp:
// �йش����ʵ�֣������ ReadSHDFile.cpp
//

class CReadSHDFileApp : public CWinApp
{
public:
	CReadSHDFileApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadSHDFileApp theApp;