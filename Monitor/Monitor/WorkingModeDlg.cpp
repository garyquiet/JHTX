// WorkingModeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "WorkingModeDlg.h"
#include "ProtocolPkg.h"


// CWorkingModeDlg 对话框

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


// CWorkingModeDlg 消息处理程序

//显示串口连接状态
void CWorkingModeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CWorkingModeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CWorkingModeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//设置提示信息
void CWorkingModeDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

//初始化
void CWorkingModeDlg::Init(){
	m_comboWorkingMode.ResetContent();

	CString arr[CONST_TOTAL_WORK_MODE] = {L"切换模式至间歇工作模式", L"切换模式至持续工作模", L"切换模式至低耗工作模式",
		L"切换模式至加注模式", L"切换模式至测试模式"};

	for (int i = 0; i < CONST_TOTAL_WORK_MODE; ++i)
	{
		m_comboWorkingMode.AddString(arr[i]);
	}
}


BOOL CWorkingModeDlg::OnInitDialog()
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

void CWorkingModeDlg::OnTimer(UINT_PTR nIDEvent)
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

void CWorkingModeDlg::OnBnClickedQueryButton()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD len;

	len = CProtocolPkg::SendMDCFGPacket(MDCFG,MDCFG_CfgID_QUERY);

	if (len > 0)
	{
		CString tip = L"查询工作模式命令发送成功!";
		SetTipInfo(tip);
	}else{
		CString tip = L"查询工作模式命令发送失败!";
		SetTipInfo(tip);
	}
}

void CWorkingModeDlg::OnBnClickedSetButton()
{
	// TODO: 在此添加控件通知处理程序代码
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
				MessageBox(L"参数错误!");
			}
			break;
		}

		if (len > 0)
		{
			CString tip = L"工作模式切换命令发送成功!";
			SetTipInfo(tip);
		}else{
			CString tip = L"工作模式切换命令发送失败!";
			SetTipInfo(tip);
		}
	}
	else{
		MessageBox(L"请选择一个工作模式!");

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
		if(v[0] == L"当前模式") //当前模式
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