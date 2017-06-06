// BaseStationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "BaseStationDlg.h"
#include "MessageDlg.h"
#include "ProtocolPkg.h"

// CBaseStationDlg �Ի���

IMPLEMENT_DYNAMIC(CBaseStationDlg, CDialog)

CBaseStationDlg::CBaseStationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseStationDlg::IDD, pParent)
	, m_strQueryResult(_T(""))
	, m_strBaseCenterNo(_T(""))
	, m_strBaseCenterNoRepeat(_T(""))
{

}

CBaseStationDlg::~CBaseStationDlg()
{
}

void CBaseStationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESULT_EDIT, m_strQueryResult);
	DDX_Text(pDX, IDC_NUMBER_EDIT, m_strBaseCenterNo);
	DDV_MaxChars(pDX, m_strBaseCenterNo, 7);
	DDX_Text(pDX, IDC_NUMBER_REPEAT_EDIT, m_strBaseCenterNoRepeat);
	DDV_MaxChars(pDX, m_strBaseCenterNoRepeat, 7);
}


BEGIN_MESSAGE_MAP(CBaseStationDlg, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)

	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CBaseStationDlg::OnBnClickedQueryButton)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CBaseStationDlg::OnBnClickedSetButton)
	ON_EN_CHANGE(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnChangeNumberEdit)
	ON_EN_SETFOCUS(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnSetfocusNumberEdit)
	ON_EN_KILLFOCUS(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnKillfocusNumberEdit)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_NUMBER_REPEAT_EDIT, &CBaseStationDlg::OnEnChangeNumberRepeatEdit)
	ON_EN_SETFOCUS(IDC_NUMBER_REPEAT_EDIT, &CBaseStationDlg::OnEnSetfocusNumberRepeatEdit)
	ON_EN_KILLFOCUS(IDC_NUMBER_REPEAT_EDIT, &CBaseStationDlg::OnEnKillfocusNumberRepeatEdit)
END_MESSAGE_MAP()


// CBaseStationDlg ��Ϣ�������

//��ʾ��������״̬
void CBaseStationDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CBaseStationDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CBaseStationDlg::ShowBatteryPower(){
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
void CBaseStationDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}


void CBaseStationDlg::Init(){
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

	GetDlgItem(IDC_QUERY_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_QUERY_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_QUERY_RESULT_STATIC)->SetFont(f2);
	GetDlgItem(IDC_RESULT_EDIT)->SetFont(f2);


	GetDlgItem(IDC_SETTING_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_LABEL_STATIC)->SetFont(f2);
	GetDlgItem(IDC_NUMBER_EDIT)->SetFont(f2);
	GetDlgItem(IDC_LABEL2_STATIC)->SetFont(f2);
	GetDlgItem(IDC_NUMBER_REPEAT_EDIT)->SetFont(f2);
	
	GetDlgItem(IDC_TIP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_SET_BUTTON)->SetFont(f2);
	
	GetDlgItem(IDCANCEL)->SetFont(f2);

	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
}


BOOL CBaseStationDlg::OnInitDialog()
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

void CBaseStationDlg::OnTimer(UINT_PTR nIDEvent)
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

void CBaseStationDlg::OnBnClickedQueryButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DWORD len = CProtocolPkg::SendIDCFGPacket(IDCFG, IDCFG_CfgID_QUERY);
	if (len > 0)
	{
		CString tip = L"��ѯ��վ���ĺ�������ͳɹ�";
		SetTipInfo(tip);
	}
	else{
		CString tip = L"��ѯ��վ���ĺ��������ʧ��";
		SetTipInfo(tip);
	}
}


void CBaseStationDlg::OnBnClickedSetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);

	if (m_strBaseCenterNo.Trim().GetLength() > 0)
	{
		if (m_strBaseCenterNo.Trim() == m_strBaseCenterNoRepeat.Trim())
		{
			DWORD len = CProtocolPkg::SendIDCFGPacket(IDCFG, IDCFG_CfgID_SET, m_strBaseCenterNo.Trim());

			if (len > 0)
			{
				CString tip = L"���û�վ���ĺ�������ͳɹ�";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"���û�վ���ĺ��������ʧ��";
				SetTipInfo(tip);
			}
		}
		else{
			//MessageBox(L"���������ָ�ӻ�վ���ĺ��벻һ��,����!");
			CMessageDlg dlg;
			dlg.m_info = L"���������ָ�ӻ�վ���ĺ��벻һ��,����!";
			dlg.DoModal();
			return;
		}
		
	}
	else{
		//MessageBox(L"ָ�ӻ�վ���ĺ��벻��Ϊ��!");
		CMessageDlg dlg;
		dlg.m_info = L"ָ�ӻ�վ���ĺ��벻��Ϊ��!";
		dlg.DoModal();
	}

}


void CBaseStationDlg::OnEnChangeNumberEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(m_strBaseCenterNo.Trim().GetLength() > 0)
	{
		m_strBaseCenterNo = CProtocolPkg::eliminateNonNumber(m_strBaseCenterNo);
		UpdateData(FALSE);
		CString strInfo;
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->GetWindowText(strInfo);
		int nLength = strInfo.GetLength();
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->SetFocus();
	}
}


LRESULT CBaseStationDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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
	//SetTipInfo(tip);

	vector<CString> v = CProtocolPkg::SplitString(tip, L":");
	if(v.size() > 0){
		if(v[0] == L"�ϱ���վ") //�ϱ���վ
		{
			m_strQueryResult = tip;
			UpdateData(FALSE);
		}
		else{

			vector<CString> v2 = CProtocolPkg::SplitString(tip, L"��");
			if(v2.size() > 0){
				if(v2[0] == L"�ϱ���վ") //�ϱ���վ
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
void CBaseStationDlg::OnEnSetfocusNumberEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CBaseStationDlg::OnEnKillfocusNumberEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

HBRUSH CBaseStationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CBaseStationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CBaseStationDlg::OnEnChangeNumberRepeatEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strBaseCenterNoRepeat.Trim().GetLength() > 0)
	{
		m_strBaseCenterNoRepeat = CProtocolPkg::eliminateNonNumber(m_strBaseCenterNoRepeat);
		UpdateData(FALSE);

		CString strInfo;
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->GetWindowText(strInfo);
		int nLength = strInfo.GetLength();
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->SetFocus();
	}
}

void CBaseStationDlg::OnEnSetfocusNumberRepeatEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CBaseStationDlg::OnEnKillfocusNumberRepeatEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}
