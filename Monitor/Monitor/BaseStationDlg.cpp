// BaseStationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "BaseStationDlg.h"

#include "ProtocolPkg.h"

// CBaseStationDlg 对话框

IMPLEMENT_DYNAMIC(CBaseStationDlg, CDialog)

CBaseStationDlg::CBaseStationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseStationDlg::IDD, pParent)
	, m_strQueryResult(_T(""))
	, m_strBaseCenterNo(_T(""))
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
}


BEGIN_MESSAGE_MAP(CBaseStationDlg, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)

	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CBaseStationDlg::OnBnClickedQueryButton)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CBaseStationDlg::OnBnClickedSetButton)
	ON_EN_CHANGE(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnChangeNumberEdit)
	ON_EN_SETFOCUS(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnSetfocusNumberEdit)
	ON_EN_KILLFOCUS(IDC_NUMBER_EDIT, &CBaseStationDlg::OnEnKillfocusNumberEdit)
END_MESSAGE_MAP()


// CBaseStationDlg 消息处理程序

//显示串口连接状态
void CBaseStationDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CBaseStationDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CBaseStationDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//设置提示信息
void CBaseStationDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}


BOOL CBaseStationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBaseStationDlg::OnTimer(UINT_PTR nIDEvent)
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

void CBaseStationDlg::OnBnClickedQueryButton()
{
	// TODO: 在此添加控件通知处理程序代码

	DWORD len = CProtocolPkg::SendIDCFGPacket(IDCFG, IDCFG_CfgID_QUERY);
	if (len > 0)
	{
		CString tip = L"查询基站中心号码命令发送成功";
		SetTipInfo(tip);
	}
	else{
		CString tip = L"查询基站中心号码命令发送失败";
		SetTipInfo(tip);
	}
}


void CBaseStationDlg::OnBnClickedSetButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_strBaseCenterNo.Trim().GetLength() > 0)
	{

		DWORD len = CProtocolPkg::SendIDCFGPacket(IDCFG, IDCFG_CfgID_SET, m_strBaseCenterNo.Trim());

		if (len > 0)
		{
			CString tip = L"设置基站中心号码命令发送成功!";
			SetTipInfo(tip);
		}
		else{
			CString tip = L"设置基站中心号码命令发送失败!";
			SetTipInfo(tip);
		}
	}
	else{
		MessageBox(L"指挥基站中心号码不能为空!");
	}

}


void CBaseStationDlg::OnEnChangeNumberEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if(m_strBaseCenterNo.Trim().GetLength() > 0)
	{
		m_strBaseCenterNo = CProtocolPkg::eliminateNonNumber(m_strBaseCenterNo);
		UpdateData(FALSE);
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
		if(v[0] == L"上报基站") //上报基站
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
void CBaseStationDlg::OnEnSetfocusNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CBaseStationDlg::OnEnKillfocusNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}
