// SaveSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SaveSettingDlg.h"
#include "ProtocolPkg.h"
#include "MessageDlg.h"

// CSaveSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSaveSettingDlg, CDialog)

CSaveSettingDlg::CSaveSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveSettingDlg::IDD, pParent)
{

}

CSaveSettingDlg::~CSaveSettingDlg()
{
}

void CSaveSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODE_COMBO, m_combeSaveMethod);
}


BEGIN_MESSAGE_MAP(CSaveSettingDlg, CDialog)
	ON_WM_TIMER()

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)

	ON_BN_CLICKED(IDC_SET_BUTTON, &CSaveSettingDlg::OnBnClickedSetButton)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSaveSettingDlg ��Ϣ�������

//��ʾ��������״̬
void CSaveSettingDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"��������:����");
	else
		str = str = (L"��������:δ����");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CSaveSettingDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CSaveSettingDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

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
			}
			else
			{
				// ������
				//SetPowerStepBmp(300);
				str.Format(L"��Դ:%d%%", spsCurrent.BatteryLifePercent);
				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

			}
		}
		else
		{
			//MessageBox(_T("ֱ����"));
			str.Format(L"���:%d%%",spsCurrent.BatteryLifePercent);
			((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
		}
	}
	//str.Format(L"����:%d%%",spsCurrent.BatteryLifePercent);
	//((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//������ʾ��Ϣ
void CSaveSettingDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

//��ʼ��
void CSaveSettingDlg::Init(){
	m_combeSaveMethod.ResetContent();

	CString arr[CONST_TOTAL_SAVE_METHOD] = {L"�ָ���������", L"������ǰ�������ò�����", L"��ʼ��������ʾ", L"��ʼ��ͨ������"};

	for (int i = 0; i < CONST_TOTAL_SAVE_METHOD; ++i)
	{
		m_combeSaveMethod.AddString(arr[i]);
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

	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
	GetDlgItem(IDC_GROUP_STATIC)->SetFont(f2);

	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);

	GetDlgItem(IDC_SELECT_METHOD_STATIC)->SetFont(f2);
	GetDlgItem(IDC_SET_BUTTON)->SetFont(f2);
	GetDlgItem(IDCANCEL)->SetFont(f2);
	GetDlgItem(IDC_TIP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_MODE_COMBO)->SetFont(f2);
	
}



BOOL CSaveSettingDlg::OnInitDialog()
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

void CSaveSettingDlg::OnTimer(UINT_PTR nIDEvent)
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

void CSaveSettingDlg::OnBnClickedSetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_combeSaveMethod.GetCurSel();
	if (index != CB_ERR)
	{
		int method = index + 1;
		DWORD len = 0;
		switch(method)
		{
		case 1:
			{
				len = CProtocolPkg::SendSAVEPacket(SAVE,SAVE_CfgID_1);
			}
			break;;
		case 2:
			{
				len = CProtocolPkg::SendSAVEPacket(SAVE,SAVE_CfgID_2);
			}
			break;;
		case 3:
			{
				len = CProtocolPkg::SendSAVEPacket(SAVE,SAVE_CfgID_3);
			}
			break;;
		case 4:
			{
				len = CProtocolPkg::SendSAVEPacket(SAVE,SAVE_CfgID_4);
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
			CString tip = L"�洢����ͳɹ�!";
			SetTipInfo(tip);
		}else{
			CString tip = L"�洢�����ʧ��!";
			SetTipInfo(tip);
		}
	}
	else{
		//MessageBox(L"��ѡ��һ�����淽ʽ!");
		CMessageDlg dlg;
		dlg.m_info = L"��ѡ��һ�����淽ʽ!";
		dlg.DoModal();

	}
	
}


LRESULT CSaveSettingDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	CString tip = CProtocolPkg::ParseANS(1,str);
	SetTipInfo(tip);

	return 1;
}
HBRUSH CSaveSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSaveSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
