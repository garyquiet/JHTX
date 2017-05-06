// MonitorDlg.cpp : ʵ���ļ�
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

// CMonitorDlg �Ի���

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


// CMonitorDlg ��Ϣ�������

BOOL CMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(FALSE == Init())
		return FALSE;

	//ShowSplashWindow();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		_T("����")); // lpszFac 
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
	//		wsprintf(szBuf, _T("�� COM%d ʧ��, ����:%d"), COM_PORT, GetLastError());
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
	//		//SendDlgItemMessage(IDC_BUTTON_OPEN, WM_SETTEXT, 0, (LPARAM)_T("�ر�"));
	//		//m_Lamp.SetIcon(hIcons[1], FALSE);
	//		//AfxMessageBox(L"�򿪳ɹ�");
	//		((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(TRUE);
	//		((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(TRUE);
	//		
	//		//HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CONNECT_BITMAP));  // ��λͼIDB_BITMAP1���ص�bitmap   
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


//��ʾ��������
void CMonitorDlg::ShowSplashWindow(){
	CSplashWnd *pSplashWindow = new CSplashWnd;//��������
	pSplashWindow->CreateSplashWnd();
	pSplashWindow->CenterWindow();
	pSplashWindow->ShowWindow(SW_SHOW);  //��ʾ����
	pSplashWindow->UpdateWindow();
	Sleep(2000);  //��ʾ�����������ʱ��
	pSplashWindow->DestroyWindow(); //������������
	delete pSplashWindow; //ɾ��
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
	
	if( wcsstr(tip, L"��ǰģʽ") )
	{
		SetDlgItemText(IDC_STATIC_COM_STATUS, L"��������:����");
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

//��ʾ��������״̬
void CMonitorDlg::ShowConnectionStatus(){
	/*CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);*/

	DWORD len;

	len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_QUERY);

	if (len > 0)
	{
		CString tip = L"��ѯ����ģʽ����ͳɹ�!";
		SetTipInfo(tip);
	}else{
		CString tip = L"��ѯ����ģʽ�����ʧ��!";
		SetTipInfo(tip);
	}
}

//��ʾϵͳʱ��
void CMonitorDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CMonitorDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


//������ʾ��Ϣ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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


//����Ԥ����Ϣ�Ի���
void CMonitorDlg::OnBnClickedPresetInfoButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


//����ϵͳ���öԻ���
void CMonitorDlg::OnBnClickedSystemSettingButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


//�����������öԻ���
void CMonitorDlg::OnBnClickedSaveSettingButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


//��������ģʽ�Ի���
void CMonitorDlg::OnBnClickedWorkingModeButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


//����ָ�ӻ�վ�Ի���
void CMonitorDlg::OnBnClickedBaseStationButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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


//���������ŶԻ���
void CMonitorDlg::OnBnClickedSpecialCodeButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ˸��� DC ���κ�����

	if(nCtlColor==CTLCOLOR_BTN) //���İ�ť��ɫ
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));			//��ť���ֺ�ɫ
		pDC->SetBkColor(RGB(186,71,8));		//��ť������ɫ
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
	else if(nCtlColor==CTLCOLOR_EDIT) //���ı༭��
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,255,0));
		HBRUSH b=CreateSolidBrush(RGB(0,255,0));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC) //���ľ�̬�ı�
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(0,0,0));			//��̬�����ְ�ɫ
		HBRUSH b=CreateSolidBrush(RGB(0,0,0));	//��̬�򱳾���ɫ
		return b;
	}
	else if(nCtlColor==CTLCOLOR_MSGBOX) //���ĶԻ��򱳾�ɫ
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(166,254,1));
		HBRUSH b=CreateSolidBrush(RGB(166,254,1));
		return b;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CMonitorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()


	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
