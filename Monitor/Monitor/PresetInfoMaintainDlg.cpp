// PresetInfoMaintainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"
#include "PresetInfoMaintainDlg.h"
#include "ProtocolPkg.h"


// CPresetInfoMaintainDlg 对话框

IMPLEMENT_DYNAMIC(CPresetInfoMaintainDlg, CDialog)

CPresetInfoMaintainDlg::CPresetInfoMaintainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoMaintainDlg::IDD, pParent)
	
	//, m_strPresetInfoForAdd(_T(""))
	, m_strPresetInfoForModify(_T(""))
	, m_iPresetInfoNoForModify(1)
	//, m_iPresetInfoNoForDelete(1)
{

}

CPresetInfoMaintainDlg::~CPresetInfoMaintainDlg()
{
}

void CPresetInfoMaintainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_ADD, m_strPresetInfoForAdd);
	//DDV_MaxChars(pDX, m_strPresetInfoForAdd, 8);
	DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_MODIFY, m_strPresetInfoForModify);
	DDV_MaxChars(pDX, m_strPresetInfoForModify, 8);
	DDX_Text(pDX, IDC_INFOR_NO_EDIT_FOR_MODIFY, m_iPresetInfoNoForModify);
	DDV_MinMaxUInt(pDX, m_iPresetInfoNoForModify, 1, 30);
	//DDX_Text(pDX, IDC_INFO_NO_EDIT_FOR_DELETE, m_iPresetInfoNoForDelete);
	//DDV_MinMaxUInt(pDX, m_iPresetInfoNoForDelete, 1, 30);
}


BEGIN_MESSAGE_MAP(CPresetInfoMaintainDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedAddButton)
	ON_EN_CHANGE(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd)

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_BN_CLICKED(IDCANCEL, &CPresetInfoMaintainDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForModify)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedModifyButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedDeleteButton)
	ON_EN_SETFOCUS(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForAdd)
	ON_EN_KILLFOCUS(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForAdd)
	ON_EN_SETFOCUS(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnSetfocusInforNoEditForModify)
	ON_EN_KILLFOCUS(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnKillfocusInforNoEditForModify)
	ON_EN_SETFOCUS(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForModify)
	ON_EN_KILLFOCUS(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForModify)
	ON_EN_SETFOCUS(IDC_INFO_NO_EDIT_FOR_DELETE, &CPresetInfoMaintainDlg::OnEnSetfocusInfoNoEditForDelete)
	ON_EN_KILLFOCUS(IDC_INFO_NO_EDIT_FOR_DELETE, &CPresetInfoMaintainDlg::OnEnKillfocusInfoNoEditForDelete)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnChangeInforNoEditForModify)
END_MESSAGE_MAP()


// CPresetInfoMaintainDlg 消息处理程序

BOOL CPresetInfoMaintainDlg::OnInitDialog()
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


//显示串口连接状态
void CPresetInfoMaintainDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:未连接");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CPresetInfoMaintainDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CPresetInfoMaintainDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//设置提示信息
void CPresetInfoMaintainDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

void CPresetInfoMaintainDlg::OnTimer(UINT_PTR nIDEvent)
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

//增加预置信息
void CPresetInfoMaintainDlg::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if(TRUE == UpdateData(TRUE))
	{
		if (m_strPresetInfoForModify.Trim().GetLength() > 0)
		{

			DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_ADD, ANY, m_strPresetInfoForModify.Trim());

			if (len > 0)
			{
				CString tip = L"预置信息增加命令发送成功!";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"预置信息增加命令发送失败!";
				SetTipInfo(tip);
			}
		}
		else{
			MessageBox(L"预置信息不能为空!");
		}
	}
}

void CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if(m_strPresetInfoForModify.Trim().GetLength() > 0)
	{
		/*BOOL ret = CProtocolPkg::isHanZi(m_strPresetInfoForAdd.GetAt(m_strPresetInfoForAdd.GetLength() - 1));
		if (ret == FALSE)
		{
			m_strPresetInfoForAdd.Delete(m_strPresetInfoForAdd.GetLength() - 1, 1);
		}*/
		m_strPresetInfoForModify = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForModify);
		UpdateData(FALSE);

		/*int nLength = m_strPresetInfoForAdd.GetLength();
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetFocus();*/
	}
}

LRESULT CPresetInfoMaintainDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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


void CPresetInfoMaintainDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//((CPresetInfoDlg*)GetParent())->m_hWnd
	theApp.m_Com.SetWnd(((CPresetInfoDlg*)GetParent())->m_hWnd);
	OnCancel();
}

void CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForModify()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strPresetInfoForModify.Trim().GetLength() > 0)
	{
		m_strPresetInfoForModify = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForModify);
		UpdateData(FALSE);
	}
}

void CPresetInfoMaintainDlg::OnBnClickedModifyButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if(TRUE == UpdateData(TRUE)){

		if (m_strPresetInfoForModify.Trim().GetLength() > 0)
		{
			CString tmp = L"";
			tmp.Format(L"%d", m_iPresetInfoNoForModify);
			DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_MODIFY, tmp, m_strPresetInfoForModify.Trim());

			if (len > 0)
			{
				CString tip = L"预置信息覆盖命令发送成功!";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"预置信息覆盖命令发送失败!";
				SetTipInfo(tip);
			}
		}
		else{
			MessageBox(L"预置信息不能为空!");
		}
		
	}
}

void CPresetInfoMaintainDlg::OnBnClickedDeleteButton()
{
	// TODO: 在此添加控件通知处理程序代码

	if(TRUE == UpdateData(TRUE)){

		CString tmp = L"";
		tmp.Format(L"%d", m_iPresetInfoNoForModify);
		DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_DELETE, tmp, ANY);

		if (len > 0)
		{
			CString tip = L"预置信息删除命令发送成功!";
			SetTipInfo(tip);
		}
		else{
			CString tip = L"预置信息删除命令发送失败!";
			SetTipInfo(tip);
		}
	}
	
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInforNoEditForModify()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInforNoEditForModify()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForModify()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForModify()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoNoEditForDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoNoEditForDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	SipShowIM(FALSE);
}

HBRUSH CPresetInfoMaintainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPresetInfoMaintainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CPresetInfoMaintainDlg::OnEnChangeInforNoEditForModify()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	if(m_iPresetInfoNoForModify.Trim().GetLength() > 0)
	{
		m_iPresetInfoNoForModify = CProtocolPkg::eliminateNonNumber(m_iPresetInfoNoForModify);
		UpdateData(FALSE);
	}*/
}
