// Monitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "CnComm.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CMonitorApp:
// �йش����ʵ�֣������ Monitor.cpp
//

class CMonitorApp : public CWinApp
{
public:
	CMonitorApp();
	
	BOOL m_IsComConnected;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
public:
	CnComm m_Com;	//����

	DECLARE_MESSAGE_MAP()

private:
	//ϵͳ�Լ��
	BOOL SelfCheck();
};

extern CMonitorApp theApp;
