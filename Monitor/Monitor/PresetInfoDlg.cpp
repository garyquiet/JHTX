// PresetInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"

#include "PresetInfoQueryDlg.h"
#include "PresetInfoMaintainDlg.h"

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
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)

	ON_BN_CLICKED(IDC_QUERY_PRESET_INFO_BUTTON, &CPresetInfoDlg::OnBnClickedQueryPresetInfoButton)
	ON_BN_CLICKED(IDC_MAINTAIN_PRESET_INFO_BUTTON, &CPresetInfoDlg::OnBnClickedMaintainPresetInfoButton)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPresetInfoDlg ��Ϣ�������

//��ʼ��
void CPresetInfoDlg::Init(){
	CFont * f; 
	f = new CFont; 
	f->CreateFont(18, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		TRUE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 
	GetDlgItem(IDC_QUERY_PRESET_INFO_BUTTON)->SetFont(f);
	GetDlgItem(IDC_MAINTAIN_PRESET_INFO_BUTTON)->SetFont(f);
	//GetDlgItem(IDCANCEL)->SetFont(f);

}

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
	Init();

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

void CPresetInfoDlg::OnBnClickedMaintainPresetInfoButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPresetInfoMaintainDlg dlg;

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

LRESULT CPresetInfoDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	return 1;
}
HBRUSH CPresetInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPresetInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
