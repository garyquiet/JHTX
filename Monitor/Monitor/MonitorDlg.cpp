// MonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"

#include "PresetInfoDlg.h"


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
	ON_BN_CLICKED(IDC_PRESET_INFO_BUTTON, &CMonitorDlg::OnBnClickedPresetInfoButton)
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

	ShowSplashWindow();
	
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
	ShowConnectionStatus();
	ShowSystemTime();
	ShowBatteryPower();
	if (!theApp.m_Com.IsOpen())
	{
		//if (!Com_.Open(m_uPort+1))
		if (!theApp.m_Com.Open(COM_PORT, BAUD_RATE))
		{
			TCHAR szBuf[1024];
			wsprintf(szBuf, _T("�� COM%d ʧ��, ����:%d"), COM_PORT, GetLastError());
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
			//SendDlgItemMessage(IDC_BUTTON_OPEN, WM_SETTEXT, 0, (LPARAM)_T("�ر�"));
			//m_Lamp.SetIcon(hIcons[1], FALSE);
			//AfxMessageBox(L"�򿪳ɹ�");
			((CButton*)GetDlgItem(IDC_PRESET_INFO_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_WORKING_MODE_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_BASE_STATION_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_SPECIAL_CODE_BUTTON))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_SAVE_SETTING_BUTTON))->EnableWindow(TRUE);
			
			//HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CONNECT_BITMAP));  // ��λͼIDB_BITMAP1���ص�bitmap   
			//m_statusPic.SetBitmap(hBmp);

			theApp.m_Com.SetWnd(this->m_hWnd);
			SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
			SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);
			
			return TRUE;
		}
	}
			
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


//��ʾ��������״̬
void CMonitorDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
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


void CMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPresetInfoDlg dlg;

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);
	}
}
