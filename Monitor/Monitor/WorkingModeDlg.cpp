// WorkingModeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "WorkingModeDlg.h"
#include "ProtocolPkg.h"


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
END_MESSAGE_MAP()


// CWorkingModeDlg ��Ϣ�������

//��ʾ��������״̬
void CWorkingModeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CWorkingModeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CWorkingModeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
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
				MessageBox(L"��������!");
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
		MessageBox(L"��ѡ��һ������ģʽ!");

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
	if(v.size() > 0){
		if(v[0] == L"��ǰģʽ") //��ǰģʽ
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