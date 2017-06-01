// Monitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "CnComm.h"
#include "oled/P36GPIO.h"


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

	CP36GPIO		m_GPIO;	//��ʾ��

	DECLARE_MESSAGE_MAP()

private:
	//ϵͳ�Լ��
	BOOL SelfCheck();
public:
	virtual int ExitInstance();
};

extern CMonitorApp theApp;
