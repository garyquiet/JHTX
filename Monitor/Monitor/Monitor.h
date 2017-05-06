// Monitor.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "CnComm.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CMonitorApp:
// 有关此类的实现，请参阅 Monitor.cpp
//

class CMonitorApp : public CWinApp
{
public:
	CMonitorApp();
	
	BOOL m_IsComConnected;
// 重写
public:
	virtual BOOL InitInstance();

// 实现
public:
	CnComm m_Com;	//串口

	DECLARE_MESSAGE_MAP()

private:
	//系统自检测
	BOOL SelfCheck();
};

extern CMonitorApp theApp;
