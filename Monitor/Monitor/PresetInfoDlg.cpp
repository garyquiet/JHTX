// PresetInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"

#include "PresetInfoQueryDlg.h"

// CPresetInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CPresetInfoDlg, CDialog)

CPresetInfoDlg::CPresetInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoDlg::IDD, pParent)
{

}

CPresetInfoDlg::~CPresetInfoDlg()
{
}

void CPresetInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPresetInfoDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_QUERY_PRESET_INFO_BUTTON, &CPresetInfoDlg::OnBnClickedQueryPresetInfoButton)
END_MESSAGE_MAP()


// CPresetInfoDlg ��Ϣ�������

//��ʾ��������״̬
void CPresetInfoDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CPresetInfoDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CPresetInfoDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


BOOL CPresetInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPresetInfoDlg::OnTimer(UINT_PTR nIDEvent)
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

void CPresetInfoDlg::OnBnClickedQueryPresetInfoButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPresetInfoQueryDlg dlg;

	int ret = dlg.DoModal();

	if(ret == IDCANCEL || ret == IDOK){
		theApp.m_Com.SetWnd(this->m_hWnd);
	}
}
