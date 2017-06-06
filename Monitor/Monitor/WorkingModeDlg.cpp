// WorkingModeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "WorkingModeDlg.h"
#include "ProtocolPkg.h"
#include "MessageDlg.h"

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
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWorkingModeDlg 消息处理程序

//显示串口连接状态
void CWorkingModeDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:未连接");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CWorkingModeDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CWorkingModeDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BatteryLifePercent);
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

	GetDlgItem(IDC_SETTING_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_QUERY_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_QUERY_RESULT_STATIC)->SetFont(f2);
	GetDlgItem(IDC_RESULT_EDIT)->SetFont(f2);


	GetDlgItem(IDC_QUERY_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_SWITCH_MODE_STATIC)->SetFont(f2);
	GetDlgItem(IDC_MODE_COMBO)->SetFont(f2);
	GetDlgItem(IDC_SET_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_TIP_STATIC)->SetFont(f2);

	GetDlgItem(IDCANCEL)->SetFont(f2);

	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
	
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
				//MessageBox(L"参数错误!");
				CMessageDlg dlg;
				dlg.m_info = L"参数错误!";
				dlg.DoModal();
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
		//MessageBox(L"请选择一个工作模式!");
		CMessageDlg dlg;
		dlg.m_info = L"请选择一个工作模式!";
		dlg.DoModal();

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
HBRUSH CWorkingModeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CWorkingModeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
