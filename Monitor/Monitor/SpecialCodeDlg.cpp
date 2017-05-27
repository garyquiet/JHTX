// SpecialCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "SpecialCodeDlg.h"
#include "ProtocolPkg.h"

// CSpecialCodeDlg 对话框

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


// CSpecialCodeDlg 消息处理程序

//显示串口连接状态
void CSpecialCodeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:未连接");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CSpecialCodeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CSpecialCodeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//设置提示信息
void CSpecialCodeDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}


//初始化
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

void CSpecialCodeDlg::OnTimer(UINT_PTR nIDEvent)
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

void CSpecialCodeDlg::OnBnClickedQueryButton()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD len = CProtocolPkg::SendSNCFGPacket(SNCFG, SNCFG_CfgID_QUERY);
	if (len > 0)
	{
		CString tip = L"查询特殊编号命令发送成功!";
		SetTipInfo(tip);
	}
	else{
		CString tip = L"查询特殊编号命令发送失败!";
		SetTipInfo(tip);
	}
}

void CSpecialCodeDlg::OnBnClickedSetButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_strSpecialCode.Trim().GetLength() > 0)
	{
		if(m_strSpecialCode.Trim() == m_strSpecialCodeRepeat.Trim())
		{

			DWORD len = CProtocolPkg::SendSNCFGPacket(SNCFG, SNCFG_CfgID_SET, m_strSpecialCode.Trim());

			if (len > 0)
			{
				CString tip = L"设置特殊编号命令发送成功!";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"设置特殊编号命令发送失败!";
				SetTipInfo(tip);
			}
		}
		else{
			MessageBox(L"两次输入的特殊编号不一致,请检查!");
			return;
		}
		
	}
	else{
		MessageBox(L"特殊编号号码不能为空!");
	}


}

void CSpecialCodeDlg::OnEnChangeNumberEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
void CSpecialCodeDlg::OnEnSetfocusNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CSpecialCodeDlg::OnEnKillfocusNumberEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

HBRUSH CSpecialCodeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSpecialCodeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CSpecialCodeDlg::OnEnChangeNumberRepeatEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CSpecialCodeDlg::OnEnKillfocusNumberRepeatEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}
