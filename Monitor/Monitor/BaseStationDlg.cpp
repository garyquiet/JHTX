// BaseStationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "BaseStationDlg.h"
#include "MessageDlg.h"
#include "ProtocolPkg.h"

// CBaseStationDlg 对话框

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
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CBaseStationDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";


	if(dwLen != 0){
		if(spsCurrent.ACLineStatus == AC_LINE_ONLINE)
		{
			if(spsCurrent.BatteryLifePercent != 100)
			{

				// 正在充电
				//SetPowerStepBmp(200);
				//MessageBox(_T("充电..."));
				str.Format(L"充电:%d%%", spsCurrent.BatteryLifePercent);
				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
			}
			else
			{
				// 充电结束
				//SetPowerStepBmp(300);
				str.Format(L"电源:%d%%", spsCurrent.BatteryLifePercent);
				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

			}
		}
		else
		{
			//MessageBox(_T("直流电"));
			str.Format(L"电池:%d%%",spsCurrent.BatteryLifePercent);
			((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
		}
	}
	//str.Format(L"电量:%d%%",spsCurrent.BatteryLifePercent);
	//((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
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
		_T("宋体")); // lpszFac 

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
		if (m_strBaseCenterNo.Trim() == m_strBaseCenterNoRepeat.Trim())
		{
			DWORD len = CProtocolPkg::SendIDCFGPacket(IDCFG, IDCFG_CfgID_SET, m_strBaseCenterNo.Trim());

			if (len > 0)
			{
				CString tip = L"设置基站中心号码命令发送成功";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"设置基站中心号码命令发送失败";
				SetTipInfo(tip);
			}
		}
		else{
			//MessageBox(L"两次输入的指挥基站中心号码不一致,请检查!");
			CMessageDlg dlg;
			dlg.m_info = L"两次输入的指挥基站中心号码不一致,请检查!";
			dlg.DoModal();
			return;
		}
		
	}
	else{
		//MessageBox(L"指挥基站中心号码不能为空!");
		CMessageDlg dlg;
		dlg.m_info = L"指挥基站中心号码不能为空!";
		dlg.DoModal();
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
		if(v[0] == L"上报基站") //上报基站
		{
			m_strQueryResult = tip;
			UpdateData(FALSE);
		}
		else{

			vector<CString> v2 = CProtocolPkg::SplitString(tip, L"：");
			if(v2.size() > 0){
				if(v2[0] == L"上报基站") //上报基站
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
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CBaseStationDlg::OnEnKillfocusNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

HBRUSH CBaseStationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	if(nCtlColor==CTLCOLOR_BTN) //更改按钮颜色
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));			//按钮文字黑色
		pDC->SetBkColor(RGB(186,71,8));		//按钮背景黄色
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
	else if(nCtlColor==CTLCOLOR_EDIT) //更改编辑框
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,255,0));
		HBRUSH b=CreateSolidBrush(RGB(0,255,0));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC) //更改静态文本
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(0,0,0));			//静态框文字白色
		HBRUSH b=CreateSolidBrush(RGB(0,0,0));	//静态框背景黑色
		return b;
	}
	else if(nCtlColor==CTLCOLOR_MSGBOX) //更改对话框背景色
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(166,254,1));
		HBRUSH b=CreateSolidBrush(RGB(166,254,1));
		return b;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CBaseStationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CBaseStationDlg::OnEnChangeNumberRepeatEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CBaseStationDlg::OnEnKillfocusNumberRepeatEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}
