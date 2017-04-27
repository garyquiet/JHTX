// PresetInfoMaintainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoMaintainDlg.h"
#include "ProtocolPkg.h"


// CPresetInfoMaintainDlg 对话框

IMPLEMENT_DYNAMIC(CPresetInfoMaintainDlg, CDialog)

CPresetInfoMaintainDlg::CPresetInfoMaintainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoMaintainDlg::IDD, pParent)
	
	, m_strPresetInfoForAdd(_T(""))
{

}

CPresetInfoMaintainDlg::~CPresetInfoMaintainDlg()
{
}

void CPresetInfoMaintainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_ADD, m_strPresetInfoForAdd);
	DDV_MaxChars(pDX, m_strPresetInfoForAdd, 8);
}


BEGIN_MESSAGE_MAP(CPresetInfoMaintainDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedAddButton)
	ON_EN_CHANGE(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd)
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

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
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
	UpdateData(TRUE);

}

void CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if(m_strPresetInfoForAdd.Trim().GetLength() > 0)
	{
		/*BOOL ret = CProtocolPkg::isHanZi(m_strPresetInfoForAdd.GetAt(m_strPresetInfoForAdd.GetLength() - 1));
		if (ret == FALSE)
		{
			m_strPresetInfoForAdd.Delete(m_strPresetInfoForAdd.GetLength() - 1, 1);
		}*/
		m_strPresetInfoForAdd = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForAdd);
		UpdateData(FALSE);

		int nLength = m_strPresetInfoForAdd.GetLength();
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetFocus();
	}
}