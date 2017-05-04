// SaveSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "SaveSettingDlg.h"
#include "ProtocolPkg.h"

// CSaveSettingDlg 对话框

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


// CSaveSettingDlg 消息处理程序

//显示串口连接状态
void CSaveSettingDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CSaveSettingDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CSaveSettingDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//设置提示信息
void CSaveSettingDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

//初始化
void CSaveSettingDlg::Init(){
	m_combeSaveMethod.ResetContent();

	CString arr[CONST_TOTAL_SAVE_METHOD] = {L"恢复所有设置", L"保留当前所有设置并保存", L"初始化电量显示", L"初始化通信设置"};

	for (int i = 0; i < CONST_TOTAL_SAVE_METHOD; ++i)
	{
		m_combeSaveMethod.AddString(arr[i]);
	}
}



BOOL CSaveSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSaveSettingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加控件通知处理程序代码
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
				MessageBox(L"参数错误!");
			}
			break;
		}
		
		if (len > 0)
		{
			CString tip = L"存储命令发送成功!";
			SetTipInfo(tip);
		}else{
			CString tip = L"存储命令发送失败!";
			SetTipInfo(tip);
		}
	}
	else{
		MessageBox(L"请选择一个保存方式!");

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