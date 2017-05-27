// SpecialCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SpecialCodeDlg.h"
#include "ProtocolPkg.h"

// CSpecialCodeDlg �Ի���

IMPLEMENT_DYNAMIC(CSpecialCodeDlg, CDialog)

CSpecialCodeDlg::CSpecialCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecialCodeDlg::IDD, pParent)
	, m_strQueryResult(_T(""))
	, m_strSpecialCode(_T(""))
	, m_strSpecialCodeRepeat(_T(""))
{

}

CSpecialCodeDlg::~CSpecialCodeDlg()
{
}

void CSpecialCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESULT_EDIT, m_strQueryResult);
	DDX_Text(pDX, IDC_NUMBER_EDIT, m_strSpecialCode);
	DDV_MaxChars(pDX, m_strSpecialCode, 3);
	DDX_Text(pDX, IDC_NUMBER_REPEAT_EDIT, m_strSpecialCodeRepeat);
	DDV_MaxChars(pDX, m_strSpecialCodeRepeat, 3);
}


BEGIN_MESSAGE_MAP(CSpecialCodeDlg, CDialog)
	ON_WM_TIMER()

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CSpecialCodeDlg::OnBnClickedQueryButton)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CSpecialCodeDlg::OnBnClickedSetButton)
	ON_EN_CHANGE(IDC_NUMBER_EDIT, &CSpecialCodeDlg::OnEnChangeNumberEdit)
	ON_EN_SETFOCUS(IDC_NUMBER_EDIT, &CSpecialCodeDlg::OnEnSetfocusNumberEdit)
	ON_EN_KILLFOCUS(IDC_NUMBER_EDIT, &CSpecialCodeDlg::OnEnKillfocusNumberEdit)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_NUMBER_REPEAT_EDIT, &CSpecialCodeDlg::OnEnChangeNumberRepeatEdit)
	ON_EN_SETFOCUS(IDC_NUMBER_REPEAT_EDIT, &CSpecialCodeDlg::OnEnSetfocusNumberRepeatEdit)
	ON_EN_KILLFOCUS(IDC_NUMBER_REPEAT_EDIT, &CSpecialCodeDlg::OnEnKillfocusNumberRepeatEdit)
END_MESSAGE_MAP()


// CSpecialCodeDlg ��Ϣ�������

//��ʾ��������״̬
void CSpecialCodeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"��������:����");
	else
		str = str = (L"��������:δ����");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CSpecialCodeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CSpecialCodeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//������ʾ��Ϣ
void CSpecialCodeDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}


//��ʼ��
void CSpecialCodeDlg::Init(){
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

	GetDlgItem(IDC_SET_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_TIP_STATIC)->SetFont(f2);

	GetDlgItem(IDCANCEL)->SetFont(f2);

	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
}



BOOL CSpecialCodeDlg::OnInitDialog()
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

void CSpecialCodeDlg::OnTimer(UINT_PTR nIDEvent)
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

void CSpecialCodeDlg::OnBnClickedQueryButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD len = CProtocolPkg::SendSNCFGPacket(SNCFG, SNCFG_CfgID_QUERY);
	if (len > 0)
	{
		CString tip = L"��ѯ����������ͳɹ�!";
		SetTipInfo(tip);
	}
	else{
		CString tip = L"��ѯ�����������ʧ��!";
		SetTipInfo(tip);
	}
}

void CSpecialCodeDlg::OnBnClickedSetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);

	if (m_strSpecialCode.Trim().GetLength() > 0)
	{
		if(m_strSpecialCode.Trim() == m_strSpecialCodeRepeat.Trim())
		{

			DWORD len = CProtocolPkg::SendSNCFGPacket(SNCFG, SNCFG_CfgID_SET, m_strSpecialCode.Trim());

			if (len > 0)
			{
				CString tip = L"��������������ͳɹ�!";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"���������������ʧ��!";
				SetTipInfo(tip);
			}
		}
		else{
			MessageBox(L"��������������Ų�һ��,����!");
			return;
		}
		
	}
	else{
		MessageBox(L"�����ź��벻��Ϊ��!");
	}


}

void CSpecialCodeDlg::OnEnChangeNumberEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strSpecialCode.Trim().GetLength() > 0)
	{
		m_strSpecialCode = CProtocolPkg::eliminateNonNumber(m_strSpecialCode);
		UpdateData(FALSE);

		CString strInfo;
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->GetWindowText(strInfo);
		int nLength = strInfo.GetLength();
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_NUMBER_EDIT))->SetFocus();
	}
}


LRESULT CSpecialCodeDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	vector<CString> v = CProtocolPkg::SplitString(tip, L":");
	if(v.size() > 0){
		if(v[0] == L"�ϱ���վ") //�ϱ���վ
		{
			m_strQueryResult = tip;
			UpdateData(FALSE);
		}
		else{
			SetTipInfo(tip);
		}
	}

	return 1;
}
void CSpecialCodeDlg::OnEnSetfocusNumberEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CSpecialCodeDlg::OnEnKillfocusNumberEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

HBRUSH CSpecialCodeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSpecialCodeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CSpecialCodeDlg::OnEnChangeNumberRepeatEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(m_strSpecialCodeRepeat.Trim().GetLength() > 0)
	{
		m_strSpecialCodeRepeat = CProtocolPkg::eliminateNonNumber(m_strSpecialCodeRepeat);
		UpdateData(FALSE);

		CString strInfo;
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->GetWindowText(strInfo);
		int nLength = strInfo.GetLength();
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_NUMBER_REPEAT_EDIT))->SetFocus();
	}
}

void CSpecialCodeDlg::OnEnSetfocusNumberRepeatEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CSpecialCodeDlg::OnEnKillfocusNumberRepeatEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}
