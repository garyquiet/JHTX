// MonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"

#include "ProtocolPkg.h"
#include "PresetInfoDlg.h"
#include "SystemSettingDlg.h"
#include "SaveSettingDlg.h"
#include "WorkingModeDlg.h"
#include "BaseStationDlg.h"
#include "SpecialCodeDlg.h"


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
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_BN_CLICKED(IDC_PRESET_INFO_BUTTON, &CMonitorDlg::OnBnClickedPresetInfoButton)
	ON_BN_CLICKED(IDC_SYSTEM_SETTING_BUTTON, &CMonitorDlg::OnBnClickedSystemSettingButton)
	ON_BN_CLICKED(IDC_SAVE_SETTING_BUTTON, &CMonitorDlg::OnBnClickedSaveSettingButton)
	ON_BN_CLICKED(IDC_WORKING_MODE_BUTTON, &CMonitorDlg::OnBnClickedWorkingModeButton)
	ON_BN_CLICKED(IDC_BASE_STATION_BUTTON, &CMonitorDlg::OnBnClickedBaseStationButton)
	ON_BN_CLICKED(IDC_SPECIAL_CODE_BUTTON, &CMonitorDlg::OnBnClickedSpecialCodeButton)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
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

	//ShowSplashWindow();
	
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
	CFont * f; 
	f = new CFont; 
	f->CreateFont(19, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体")); // lpszFac 
	GetDlgItem(IDC_PRESET_INFO_BUTTON)->SetFont(f);
	GetDlgItem(IDC_WORKING_MODE_BUTTON)->SetFont(f);
	GetDlgItem(IDC_BASE_STATION_BUTTON)->SetFont(f);
	GetDlgItem(IDC_SPECIAL_CODE_BUTTON)->SetFont(f);
	GetDlgItem(IDC_SAVE_SETTING_BUTTON)->SetFont(f);
	GetDlgItem(IDC_SYSTEM_SETTING_BUTTON)->SetFont(f);

	theApp.m_Com.SetWnd(this->m_hWnd);

	ShowSystemTime();
	ShowBatteryPower();
	ShowConnectionStatus();

	//if (!theApp.m_Com.IsOpen())
	//{
	//	//if (!Com_.Open(m_uPort+1))
	//	if (!theApp.m_Com.Open(COM_PORT, BAUD_RATE))
	//	{
	//		TCHAR szBuf[1024];
	//		wsprintf(szBuf, _T("打开 COM%d 失败, 代码:%d"), COM_PORT, GetLastError());
	//		MessageBox(szBuf);
	//		((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(FALSE);
	//		((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(FALSE);
	//		((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(FALSE);
	//		((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(FALSE);
	//		((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(FALSE);
	//		return FALSE;
	//	}
	//	else
	//	{
	//		//SendDlgItemMessage(IDC_BUTTON_OPEN, WM_SETTEXT, 0, (LPARAM)_T("关闭"));
	//		//m_Lamp.SetIcon(hIcons[1], FALSE);
	//		//AfxMessageBox(L"打开成功");
	//		((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(TRUE);
	//		
	//		//HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CONNECT_BITMAP));  // 将位图IDB_BITMAP1加载到bitmap   
	//		//m_statusPic.SetBitmap(hBmp);

	//		theApp.m_Com.SetWnd(this->m_hWnd);
	//		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	//		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
	//		
	//		return TRUE;
	//	}
	//}
			
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
	SetTimer(TIMER_EVENT_COM_STATUS, TIME_INTERVAL_TEN_SECONDS, NULL);

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

LRESULT CMonitorDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
{
	char buf[RCV_BUFFER_SIZE];
	TCHAR sbuf[RCV_BUFFER_SIZE];
	memset(sbuf, 0, sizeof(sbuf));
	int len;

	len = theApp.m_Com.Read(buf, RCV_BUFFER_SIZE);

	mbstowcs(sbuf, buf, len);

	CString str = L"";
	str += sbuf;
	str += _T("\r\n");

	CString tip = CProtocolPkg::ParseMOD(str);
	
	if( wcsstr(tip, L"当前模式") )
	{
		SetDlgItemText(IDC_STATIC_COM_STATUS, L"串口连接:连接");
		theApp.m_IsComConnected = TRUE;

		KillTimer(TIMER_EVENT_COM_STATUS);
		((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(TRUE);
	}

	return 1;
}

//显示串口连接状态
void CMonitorDlg::ShowConnectionStatus(){
	/*CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);*/

	DWORD len;

	len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_QUERY);

	if (len > 0)
	{
		CString tip = L"查询工作模式命令发送成功!";
		SetTipInfo(tip);
	}else{
		CString tip = L"查询工作模式命令发送失败!";
		SetTipInfo(tip);
	}
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


//设置提示信息
void CMonitorDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}


void CMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == TIMER_EVENT_DATETIME)
	{
		ShowSystemTime();
	}
	else if(nIDEvent == TIMER_EVENT_POWER){
		ShowBatteryPower();		
	}
	else if (nIDEvent == TIMER_EVENT_COM_STATUS)
	{
		ShowConnectionStatus();
	}

	CDialog::OnTimer(nIDEvent);
}


//弹出预置信息对话框
void CMonitorDlg::OnBnClickedPresetInfoButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CPresetInfoDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif
	}
}


//弹出系统设置对话框
void CMonitorDlg::OnBnClickedSystemSettingButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CSystemSettingDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif
	}
}


//弹出保存设置对话框
void CMonitorDlg::OnBnClickedSaveSettingButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CSaveSettingDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif
	}
}


//弹出工作模式对话框
void CMonitorDlg::OnBnClickedWorkingModeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CWorkingModeDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif
		
	}
}


//弹出指挥基站对话框
void CMonitorDlg::OnBnClickedBaseStationButton()
{
	// TODO: 在此添加控件通知处理程序代码

	CBaseStationDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif

	}
}


//弹出特殊编号对话框
void CMonitorDlg::OnBnClickedSpecialCodeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CSpecialCodeDlg dlg;

#if defined(OPTIMIZATION)
	KillTimer(TIMER_EVENT_DATETIME);
	KillTimer(TIMER_EVENT_POWER);
#endif

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);

#if defined(OPTIMIZATION)
		SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
		SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
#endif

	}
}

HBRUSH CMonitorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	if(nCtlColor==CTLCOLOR_BTN) //更改按钮颜色
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));			//按钮文字黑色
		pDC->SetBkColor(RGB(186,71,8));		//按钮背景黄色
		HBRUSH b=CreateSolidBrush(RGB(186,71,8));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_SCROLLBAR) //
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(233,233,220));
		HBRUSH b=CreateSolidBrush(RGB(233,233,220));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_EDIT) //更改编辑框
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,255,0));
		HBRUSH b=CreateSolidBrush(RGB(0,255,0));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC) //更改静态文本
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(0,0,0));			//静态框文字白色
		HBRUSH b=CreateSolidBrush(RGB(0,0,0));	//静态框背景黑色
		return b;
	}
	else if(nCtlColor==CTLCOLOR_MSGBOX) //更改对话框背景色
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(166,254,1));
		HBRUSH b=CreateSolidBrush(RGB(166,254,1));
		return b;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CMonitorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()


	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
