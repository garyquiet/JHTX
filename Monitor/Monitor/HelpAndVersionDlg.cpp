// HelpAndVersionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "HelpAndVersionDlg.h"


// CHelpAndVersionDlg �Ի���

IMPLEMENT_DYNAMIC(CHelpAndVersionDlg, CDialog)

CHelpAndVersionDlg::CHelpAndVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpAndVersionDlg::IDD, pParent)
{

}

CHelpAndVersionDlg::~CHelpAndVersionDlg()
{
}

void CHelpAndVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpAndVersionDlg, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHelpAndVersionDlg ��Ϣ�������

//��ʼ��
void CHelpAndVersionDlg::Init(){
	CFont * f; 
	f = new CFont; 
	f->CreateFont(15, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 

	GetDlgItem(IDC_HELP_STATIC)->SetFont(f);
	GetDlgItem(IDC_VERSION)->SetFont(f);
	GetDlgItem(IDCANCEL)->SetFont(f);
	GetDlgItem(IDC_GROUP_STATIC)->SetFont(f);
	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f);
}

//��ʾ��������״̬
void CHelpAndVersionDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"��������:����");
	else
		str = str = (L"��������:δ����");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CHelpAndVersionDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CHelpAndVersionDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";

	if(dwLen != 0){
		if(spsCurrent.ACLineStatus == AC_LINE_ONLINE)
		{
			if(spsCurrent.BatteryLifePercent != 100)
			{

				// ���ڳ��
				//SetPowerStepBmp(200);
				//MessageBox(_T("���..."));
				str.Format(L"���:%d%%", spsCurrent.BatteryLifePercent);
				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_CHARING_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else
			{
				// ������
				//SetPowerStepBmp(300);
				str.Format(L"��Դ:%d%%", spsCurrent.BatteryLifePercent);
				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_POWER_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 

			}
		}
		else
		{
			//MessageBox(_T("ֱ����"));
			str.Format(L"���:%d%%",spsCurrent.BatteryLifePercent);
			((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

			if (spsCurrent.BatteryLifePercent >= 100)
			{
				//Full
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_FULL_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 100 && spsCurrent.BatteryLifePercent >= 70){
				//More
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_MORE_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}

			else if(spsCurrent.BatteryLifePercent < 70 && spsCurrent.BatteryLifePercent >= 40){
				//Media
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_MEDIA_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 40 && spsCurrent.BatteryLifePercent >= 10){
				//Less
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_LESS_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else{
				//Empty
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_EMPTY_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
		}
	}
	//str.Format(L"����:%d%%",spsCurrent.BatteryLifePercent);
	//((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


BOOL CHelpAndVersionDlg::OnInitDialog()
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

void CHelpAndVersionDlg::OnTimer(UINT_PTR nIDEvent)
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

HBRUSH CHelpAndVersionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CHelpAndVersionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

LRESULT CHelpAndVersionDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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