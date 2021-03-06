// SystemSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "SystemSettingDlg.h"


// CSystemSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSystemSettingDlg, CDialog)

CSystemSettingDlg::CSystemSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemSettingDlg::IDD, pParent)
{

}

CSystemSettingDlg::~CSystemSettingDlg()
{
}

void CSystemSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dateTimePicker);
	DDX_Control(pDX, IDC_HOUR_COMBO, m_comboHour);
	DDX_Control(pDX, IDC_MINUTE_COMBO, m_comboMinute);
	DDX_Control(pDX, IDC_SECOND_COMBO, m_comboSecond);
}


BEGIN_MESSAGE_MAP(CSystemSettingDlg, CDialog)
	ON_BN_CLICKED(IDC_SET_BUTTON, &CSystemSettingDlg::OnBnClickedSetButton)
	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSystemSettingDlg 消息处理程序

//显示串口连接状态
void CSystemSettingDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:断开");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CSystemSettingDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CSystemSettingDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"电量:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//对话框初始化（下拉框、日期选择）
void CSystemSettingDlg::Init(){

	m_comboHour.ResetContent();
	m_comboMinute.ResetContent();
	m_comboSecond.ResetContent();

	for (int i = 0; i < CONST_TOTAL_HOUR; i++)
	{
		CString str = L"";
		str.Format(L"%02d", i);
		m_comboHour.AddString(str);
	}

	for (int i = 0; i < CONST_TOTAL_MINUTE; i++)
	{
		CString str = L"";
		str.Format(L"%02d", i);
		m_comboMinute.AddString(str);
		m_comboSecond.AddString(str);
	}

	CTime curTime; 
	curTime = CTime::GetCurrentTime();
	
	m_dateTimePicker.SetTime(&curTime);

	CString strHour;
	strHour.Format(L"%02d",curTime.GetHour());
	CString strMinute;
	strMinute.Format(L"%02d",curTime.GetMinute());
	CString strSecond;
	strSecond.Format(L"%2d",curTime.GetSecond());

	int ret = m_comboHour.FindStringExact(0, strHour);
	if (ret != CB_ERR)
	{
		m_comboHour.SetCurSel(ret);
	}

	ret = m_comboMinute.FindStringExact(0, strMinute);
	if (ret != CB_ERR)
	{
		m_comboMinute.SetCurSel(ret);
	}

	ret = m_comboSecond.FindStringExact(0, strSecond);
	if (ret != CB_ERR)
	{
		m_comboSecond.SetCurSel(ret);
	}

}


BOOL CSystemSettingDlg::OnInitDialog()
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


//确认保存按钮
void CSystemSettingDlg::OnBnClickedSetButton()
{
	// TODO: 在此添加控件通知处理程序代码

	CTime curTime;
	m_dateTimePicker.GetTime(curTime);

	
	/*curTime.GetHour();
	curTime.GetMinute();
	curTime.GetSecond();*/

	CString strHour;
	CString strMinute;
	CString strSecond;
	
	int ret = m_comboHour.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboHour.GetLBText(ret, strHour);
	}

	ret = m_comboMinute.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboMinute.GetLBText(ret, strMinute);
	}

	ret = m_comboSecond.GetCurSel();
	if (ret != CB_ERR)
	{
		m_comboSecond.GetLBText(ret, strSecond);
	}
	

	SYSTEMTIME st;
	st.wYear = curTime.GetYear();
	st.wMonth = curTime.GetMonth();
	st.wDay = curTime.GetDay();
	st.wHour = _ttoi(strHour);
	st.wMinute = _ttoi(strMinute);
	st.wSecond = _ttoi(strSecond);

	if(FALSE == SetLocalTime(&st)){
		MessageBox(L"设置失败!");
	}
	else{
		MessageBox(L"设置成功!");
	}
}


void CSystemSettingDlg::OnTimer(UINT_PTR nIDEvent)
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

LRESULT CSystemSettingDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	return 1;
}
HBRUSH CSystemSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSystemSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0));
}
