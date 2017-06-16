// WorkingModeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "WorkingModeDlg.h"
#include "ProtocolPkg.h"
#include "MessageDlg.h"

// CWorkingModeDlg �Ի���

IMPLEMENT_DYNAMIC(CWorkingModeDlg, CDialog)

CWorkingModeDlg::CWorkingModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkingModeDlg::IDD, pParent)
	, m_strQueryResult(_T(""))
{

}

CWorkingModeDlg::~CWorkingModeDlg()
{
}

void CWorkingModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESULT_EDIT, m_strQueryResult);
	DDX_Control(pDX, IDC_MODE_COMBO, m_comboWorkingMode);
}


BEGIN_MESSAGE_MAP(CWorkingModeDlg, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CWorkingModeDlg::OnBnClickedQueryButton)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CWorkingModeDlg::OnBnClickedSetButton)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWorkingModeDlg ��Ϣ�������

//��ʾ��������״̬
void CWorkingModeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"��������:����");
	else
		str = str = (L"��������:δ����");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CWorkingModeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CWorkingModeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";

	if(dwLen != 0){
		if(spsCurrent.ACLineStatus == AC_LINE_ONLINE)
		{
			if(spsCurrent.BatteryLifePercent < 100)
			{

				// ���ڳ��
				//SetPowerStepBmp(200);
				//MessageBox(_T("���..."));
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"���:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"���:%d%%", 100);
				}

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
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"��Դ:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"��Դ:%d%%", 100);
				}

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

			if (spsCurrent.BatteryLifePercent <= 100)
			{
				str.Format(L"���:%d%%",spsCurrent.BatteryLifePercent);
			}
			else
			{
				str.Format(L"���:%d%%",100);
			}

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

//������ʾ��Ϣ
void CWorkingModeDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

//��ʼ��
void CWorkingModeDlg::Init(){
	m_comboWorkingMode.ResetContent();

	CString arr[CONST_TOTAL_WORK_MODE] = {L"�л�ģʽ����Ъ����ģʽ", L"�л�ģʽ����������ģ", L"�л�ģʽ���ͺĹ���ģʽ",
		L"�л�ģʽ����עģʽ", L"�л�ģʽ������ģʽ"};

	for (int i = 0; i < CONST_TOTAL_WORK_MODE; ++i)
	{
		m_comboWorkingMode.AddString(arr[i]);
	}

	CFont * f2 = new CFont; 
	f2->CreateFont(15, // nHeight 
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

	GetDlgItem(IDC_SETTING_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_QUERY_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_QUERY_RESULT_STATIC)->SetFont(f2);
	GetDlgItem(IDC_RESULT_EDIT)->SetFont(f2);


	GetDlgItem(IDC_QUERY_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_SWITCH_MODE_STATIC)->SetFont(f2);
	GetDlgItem(IDC_MODE_COMBO)->SetFont(f2);
	GetDlgItem(IDC_SET_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_TIP_STATIC)->SetFont(f2);

	GetDlgItem(IDCANCEL)->SetFont(f2);

	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
	
}


BOOL CWorkingModeDlg::OnInitDialog()
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

void CWorkingModeDlg::OnTimer(UINT_PTR nIDEvent)
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

void CWorkingModeDlg::OnBnClickedQueryButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

void CWorkingModeDlg::OnBnClickedSetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_comboWorkingMode.GetCurSel();
	if (index != CB_ERR)
	{
		int method = index + 1;
		DWORD len = 0;
		switch(method)
		{
		case 1:
			{
				len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_MODE1);
			}
			break;;
		case 2:
			{
				len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_MODE2);
			}
			break;;
		case 3:
			{
				len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_MODE3);
			}
			break;;
		case 4:
			{
				len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_MODE4);
			}
			break;
		case 5:
			{
				len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_MODE5);
			}
			break;
		default:
			{
				//MessageBox(L"��������!");
				CMessageDlg dlg;
				dlg.m_info = L"��������!";
				dlg.DoModal();
			}
			break;
		}

		if (len > 0)
		{
			CString tip = L"����ģʽ�л�����ͳɹ�!";
			SetTipInfo(tip);
		}else{
			CString tip = L"����ģʽ�л������ʧ��!";
			SetTipInfo(tip);
		}
	}
	else{
		//MessageBox(L"��ѡ��һ������ģʽ!");
		CMessageDlg dlg;
		dlg.m_info = L"��ѡ��һ������ģʽ!";
		dlg.DoModal();

	}

}


LRESULT CWorkingModeDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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
	

	vector<CString> v = CProtocolPkg::SplitString(tip, L":");
	if(v.size() > 0)
	{
		if(v[0] == L"��ǰģʽ") //��ǰģʽ
		{
			m_strQueryResult = tip;
			UpdateData(FALSE);
		}
		else{

			vector<CString> v2 = CProtocolPkg::SplitString(tip, L"��");
			if(v2.size() > 0){
				if(v2[0] == L"��ǰģʽ") //��ǰģʽ
				{
					m_strQueryResult = tip;
					UpdateData(FALSE);
				}
				else{
					SetTipInfo(tip);
				}
			}

		}
	}

	return 1;
}
HBRUSH CWorkingModeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CWorkingModeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
