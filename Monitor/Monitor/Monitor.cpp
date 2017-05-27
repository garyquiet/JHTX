// Monitor.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"
#include "MessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinApp)
END_MESSAGE_MAP()


// CMonitorApp 构造
CMonitorApp::CMonitorApp()
	: CWinApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_IsComConnected = FALSE;
}


// 唯一的一个 CMonitorApp 对象
CMonitorApp theApp;

// CMonitorApp 初始化


BOOL CMonitorApp::SelfCheck(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	//SYSTEM_POWER_STATUS_EX spsCurrent; 
	//DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);
	
	if( BATTERY_FLAG_LOW == spsCurrent.BatteryFlag){
		//AfxMessageBox(L"电池电量过低!");
		CMessageDlg dlg;
		dlg.m_info = L"电池电量过低!";
		dlg.DoModal();
	}

	if (!m_Com.IsOpen())
	{
		if (!m_Com.Open(COM_PORT, BAUD_RATE))
		{
			TCHAR szBuf[1024];
			wsprintf(szBuf, _T("打开 COM%d 失败, 错误代码:%d"), COM_PORT, GetLastError());
			//AfxMessageBox(szBuf);
			CMessageDlg dlg;
			dlg.m_info = szBuf;
			dlg.DoModal();
			return FALSE;
		}
		else
		{	
			return TRUE;
		}
	}
	return TRUE;
}

BOOL CMonitorApp::InitInstance()
{

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	if(TRUE == SelfCheck()) //系统自检成功
	{
		CMonitorDlg dlg;
		m_pMainWnd = &dlg;

		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: 在此处放置处理何时用“确定”来关闭
			//  对话框的代码
		}
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
