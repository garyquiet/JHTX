// SystemSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SystemSettingDlg.h"


// CSystemSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSystemSettingDlg, CDialog)

CSystemSettingDlg::CSystemSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemSettingDlg::IDD, pParent)
{

}

CSystemSettingDlg::~CSystemSettingDlg()
{
}

void CSystemSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dateTimePicker);
	DDX_Control(pDX, IDC_HOUR_COMBO, m_comboHour);
	DDX_Control(pDX, IDC_MINUTE_COMBO, m_comboMinute);
	DDX_Control(pDX, IDC_SECOND_COMBO, m_comboSecond);
}


BEGIN_MESSAGE_MAP(CSystemSettingDlg, CDialog)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CSystemSettingDlg::OnBnClickedSetButton)
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSystemSettingDlg ��Ϣ�������

//��ʾ��������״̬
void CSystemSettingDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CSystemSettingDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CSystemSettingDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//�Ի����ʼ��������������ѡ��
void CSystemSettingDlg::Init(){

	m_comboHour.ResetContent();
	m_comboMinute.ResetContent();
	m_comboSecond.ResetContent();

	for (int i = 0; i < CONST_TOTAL_HOUR; i++)
	{
		CString str = L"";
		str.Format(L"%02d", i);
		m_comboHour.AddString(str);
	}

	for (int i = 0; i < CONST_TOTAL_MINUTE; i++)
	{
		CString str = L"";
		str.Format(L"%02d", i);
		m_comboMinute.AddString(str);
		m_comboSecond.AddString(str);
	}

	CTime curTime; 
	curTime = CTime::GetCurrentTime();
	
	m_dateTimePicker.SetTime(&curTime);

	CString strHour;
	strHour.Format(L"%02d",curTime.GetHour());
	CString strMinute;
	strMinute.Format(L"%02d",curTime.GetMinute());
	CString strSecond;
	strSecond.Format(L"%2d",curTime.GetSecond());

	int ret = m_comboHour.FindStringExact(0, strHour);
	if (ret != CB_ERR)
	{
		m_comboHour.SetCurSel(ret);
	}

	ret = m_comboMinute.FindStringExact(0, strMinute);
	if (ret != CB_ERR)
	{
		m_comboMinute.SetCurSel(ret);
	}

	ret = m_comboSecond.FindStringExact(0, strSecond);
	if (ret != CB_ERR)
	{
		m_comboSecond.SetCurSel(ret);
	}

}


BOOL CSystemSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//ȷ�ϱ��水ť
void CSystemSettingDlg::OnBnClickedSetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CTime curTime;
	m_dateTimePicker.GetTime(curTime);

	
	/*curTime.GetHour();
	curTime.GetMinute();
	curTime.GetSecond();*/

	CString strHour;
	CString strMinute;
	CString strSecond;
	
	int ret = m_comboHour.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboHour.GetLBText(ret, strHour);
	}

	ret = m_comboMinute.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboMinute.GetLBText(ret, strMinute);
	}

	ret = m_comboSecond.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboSecond.GetLBText(ret, strSecond);
	}
	

	SYSTEMTIME st;
	st.wYear = curTime.GetYear();
	st.wMonth = curTime.GetMonth();
	st.wDay = curTime.GetDay();
	st.wHour = _ttoi(strHour);
	st.wMinute = _ttoi(strMinute);
	st.wSecond = _ttoi(strSecond);

	if(FALSE == SetLocalTime(&st)){
		MessageBox(L"����ʧ��!");
	}
	else{
		MessageBox(L"���óɹ�!");
	}
}


void CSystemSettingDlg::OnTimer(UINT_PTR nIDEvent)
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

LRESULT CSystemSettingDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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
HBRUSH CSystemSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSystemSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0));
}
