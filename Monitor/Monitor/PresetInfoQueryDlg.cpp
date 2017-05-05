// PresetInfoQueryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoQueryDlg.h"
#include "ProtocolPkg.h"


// CPresetInfoQueryDlg �Ի���

IMPLEMENT_DYNAMIC(CPresetInfoQueryDlg, CDialog)

CPresetInfoQueryDlg::CPresetInfoQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoQueryDlg::IDD, pParent)
{

}

CPresetInfoQueryDlg::~CPresetInfoQueryDlg()
{
}

void CPresetInfoQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUERY_LIST, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CPresetInfoQueryDlg, CDialog)
	ON_WM_TIMER()

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPresetInfoQueryDlg ��Ϣ�������

//��ʾ��������״̬
void CPresetInfoQueryDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CPresetInfoQueryDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CPresetInfoQueryDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


void CPresetInfoQueryDlg::OnTimer(UINT_PTR nIDEvent)
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

void CPresetInfoQueryDlg::InitListCtrl(){
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listCtrl.SetExtendedStyle(dwStyle); //������չ���

	m_listCtrl.InsertColumn( 0, L"���", LVCFMT_LEFT, 40 );//������
	m_listCtrl.InsertColumn( 1, L"��Ϣ", LVCFMT_LEFT, 200 );

	//for (int i = 0; i < 30; ++i)
	//{
	//	int nRow = m_listCtrl.InsertItem(i, L"1");//������
	//	m_listCtrl.SetItemText(nRow, 1, L"jacky");//��������
	//}
	
}


BOOL CPresetInfoQueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);
	InitListCtrl();

	DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_QUERY);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

LRESULT CPresetInfoQueryDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	map<CString, CString> dic = CProtocolPkg::ParsePresetInfo(str);

	m_listCtrl.DeleteAllItems();
	int i = 0;
	for(map<CString,CString>::iterator iter = dic.begin(); iter != dic.end(); ++iter)
	{

		int nRow = m_listCtrl.InsertItem(i, iter->first);//������
		m_listCtrl.SetItemText(nRow, 1, iter->second);//��������
		++i;
	}

	return 1;
}
HBRUSH CPresetInfoQueryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPresetInfoQueryDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
