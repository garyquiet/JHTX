// SaveSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SaveSettingDlg.h"
#include "ProtocolPkg.h"

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
END_MESSAGE_MAP()


// CSaveSettingDlg ��Ϣ�������

//��ʾ��������״̬
void CSaveSettingDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CSaveSettingDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CSaveSettingDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
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
				MessageBox(L"��������!");
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
		MessageBox(L"��ѡ��һ�����淽ʽ!");

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