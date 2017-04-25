// MonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"

#include "PresetInfoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMonitorDlg 对话框

CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATUS_STATIC, m_statusPic);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PRESET_INFO_BUTTON, &CMonitorDlg::OnBnClickedPresetInfoButton)
END_MESSAGE_MAP()


// CMonitorDlg 消息处理程序

BOOL CMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(FALSE == Init())
		return FALSE;

	ShowSplashWindow();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CMonitorDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_HOME_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_HOME_DIALOG));
	}
}
#endif


BOOL CMonitorDlg::Init(){
	ShowConnectionStatus();
	ShowSystemTime();
	ShowBatteryPower();
	if (!theApp.m_Com.IsOpen())
	{
		//if (!Com_.Open(m_uPort+1))
		if (!theApp.m_Com.Open(COM_PORT, BAUD_RATE))
		{
			TCHAR szBuf[1024];
			wsprintf(szBuf, _T("打开 COM%d 失败, 代码:%d"), COM_PORT, GetLastError());
			MessageBox(szBuf);
			((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(FALSE);
			return FALSE;
		}
		else
		{
			//SendDlgItemMessage(IDC_BUTTON_OPEN, WM_SETTEXT, 0, (LPARAM)_T("关闭"));
			//m_Lamp.SetIcon(hIcons[1], FALSE);
			//AfxMessageBox(L"打开成功");
			((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(TRUE);
			
			//HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CONNECT_BITMAP));  // 将位图IDB_BITMAP1加载到bitmap   
			//m_statusPic.SetBitmap(hBmp);

			theApp.m_Com.SetWnd(this->m_hWnd);
			SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
			SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
			
			return TRUE;
		}
	}
			
	return TRUE;
}


//显示启动画面
void CMonitorDlg::ShowSplashWindow(){
	CSplashWnd *pSplashWindow = new CSplashWnd;//创建对象
	pSplashWindow->CreateSplashWnd();
	pSplashWindow->CenterWindow();
	pSplashWindow->ShowWindow(SW_SHOW);  //显示窗口
	pSplashWindow->UpdateWindow();
	Sleep(2000);  //表示启动画面持续时间
	pSplashWindow->DestroyWindow(); //销毁启动画面
	delete pSplashWindow; //删除
}


//显示串口连接状态
void CMonitorDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CMonitorDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CMonitorDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


void CMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == TIMER_EVENT_DATETIME)
	{
		ShowConnectionStatus();
		ShowSystemTime();
	}
	else if(nIDEvent == TIMER_EVENT_POWER){
		ShowBatteryPower();		
	}

	CDialog::OnTimer(nIDEvent);
}

void CMonitorDlg::OnBnClickedPresetInfoButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CPresetInfoDlg dlg;

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);
	}
}
