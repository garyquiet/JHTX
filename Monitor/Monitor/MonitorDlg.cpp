// MonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"

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
	DDX_Control(pDX, IDC_STATUS_STATIC, m_statusPic);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
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
	Init();
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
	if (!_Com.IsOpen())
	{
		//if (!Com_.Open(m_uPort+1))
		if (!_Com.Open(COM_PORT, BAUD_RATE))
		{
			TCHAR szBuf[1024];
			wsprintf(szBuf, _T("打开 COM%d 失败, 代码:%d"), COM_PORT, GetLastError());
			MessageBox(szBuf);
			/*((CButton*)GetDlgItem(IDC_OPEN_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CLOSE_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_SEND_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_CHILD_BUTTON))->EnableWindow(FALSE);
			((CEdit*)GetDlgItem(IDC_SEND_EDIT))->EnableWindow(FALSE);*/
			return FALSE;
		}
		else
		{
			//SendDlgItemMessage(IDC_BUTTON_OPEN, WM_SETTEXT, 0, (LPARAM)_T("关闭"));
			//m_Lamp.SetIcon(hIcons[1], FALSE);
			//AfxMessageBox(L"打开成功");
			/*((CButton*)GetDlgItem(IDC_OPEN_BUTTON))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_CLOSE_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_SEND_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CHILD_BUTTON))->EnableWindow(TRUE);
			((CEdit*)GetDlgItem(IDC_SEND_EDIT))->EnableWindow(TRUE);*/
			
			HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CONNECT_BITMAP));  // 将位图IDB_BITMAP1加载到bitmap   
			m_statusPic.SetBitmap(hBmp);

			_Com.SetWnd(this->m_hWnd);
			SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
			SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
			
			return TRUE;
		}
	}
			
	return TRUE;
}



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

void CMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == TIMER_EVENT_DATETIME)
	{
		CTime tm; 
		tm=CTime::GetCurrentTime();
		CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
		((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
	}
	else if(nIDEvent == TIMER_EVENT_POWER){
		SYSTEM_POWER_STATUS_EX2 spsCurrent; 
		DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);
		
	}

	CDialog::OnTimer(nIDEvent);
}
