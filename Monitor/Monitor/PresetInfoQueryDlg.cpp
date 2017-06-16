// PresetInfoQueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoQueryDlg.h"
#include "ProtocolPkg.h"


// CPresetInfoQueryDlg 对话框

IMPLEMENT_DYNAMIC(CPresetInfoQueryDlg, CDialog)

CPresetInfoQueryDlg::CPresetInfoQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoQueryDlg::IDD, pParent)
{

}

CPresetInfoQueryDlg::~CPresetInfoQueryDlg()
{
}

void CPresetInfoQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUERY_LIST, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CPresetInfoQueryDlg, CDialog)
	ON_WM_TIMER()

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPresetInfoQueryDlg 消息处理程序

//显示串口连接状态
void CPresetInfoQueryDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"串口连接:连接");
	else
		str = str = (L"串口连接:未连接");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//显示系统时间
void CPresetInfoQueryDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//显示电量
void CPresetInfoQueryDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";

	if(dwLen != 0){
		if(spsCurrent.ACLineStatus == AC_LINE_ONLINE)
		{
			if(spsCurrent.BatteryLifePercent < 100)
			{

				// 正在充电
				//SetPowerStepBmp(200);
				//MessageBox(_T("充电..."));
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"充电:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"充电:%d%%", 100);
				}

				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_CHARING_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}
			else
			{
				// 充电结束
				//SetPowerStepBmp(300);
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"电源:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"电源:%d%%", 100);
				}

				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_POWER_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 

			}
		}
		else
		{
			//MessageBox(_T("直流电"));

			if (spsCurrent.BatteryLifePercent <= 100)
			{
				str.Format(L"电池:%d%%",spsCurrent.BatteryLifePercent);
			}
			else
			{
				str.Format(L"电池:%d%%",100);
			}

			((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

			if (spsCurrent.BatteryLifePercent >= 100)
			{
				//Full
				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_FULL_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 100 && spsCurrent.BatteryLifePercent >= 70){
				//More
				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_MORE_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}

			else if(spsCurrent.BatteryLifePercent < 70 && spsCurrent.BatteryLifePercent >= 40){
				//Media
				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_MEDIA_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 40 && spsCurrent.BatteryLifePercent >= 10){
				//Less
				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_LESS_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}
			else{
				//Empty
				//从资源中加载图片
				CBitmap bitmap;
				// 保存CBitmap加载的位图的句柄
				HBITMAP hBmp;   
				//加载指定位图资源 Bmp图片ID
				bitmap.LoadBitmap(IDB_EMPTY_BITMAP);
				// 获取bitmap加载位图的句柄
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//获取对话框上的句柄 图片控件ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//设置静态控件窗口风格为位图居中显示
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//将图片设置到Picture控件上
				p->SetBitmap(hBmp); 
			}
		}
	}
	//str.Format(L"电量:%d%%",spsCurrent.BatteryLifePercent);
	//((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}


void CPresetInfoQueryDlg::OnTimer(UINT_PTR nIDEvent)
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

void CPresetInfoQueryDlg::InitListCtrl(){
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listCtrl.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listCtrl.InsertColumn( 0, L"序号", LVCFMT_LEFT, 80 );//插入列
	m_listCtrl.InsertColumn( 1, L"信息", LVCFMT_CENTER, 375);

	//for (int i = 0; i < 30; ++i)
	//{
	//	int nRow = m_listCtrl.InsertItem(i, L"1");//插入行
	//	m_listCtrl.SetItemText(nRow, 1, L"jacky");//设置数据
	//}
	
}


BOOL CPresetInfoQueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);
	InitListCtrl();

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

	GetDlgItem(IDC_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
	GetDlgItem(IDC_QUERY_LIST)->SetFont(f2);
	
	DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_QUERY);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CPresetInfoQueryDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
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

	map<CString, CString> dic = CProtocolPkg::ParsePresetInfo(str);

	m_listCtrl.DeleteAllItems();
	int i = 0;
	for(map<CString,CString>::iterator iter = dic.begin(); iter != dic.end(); ++iter)
	{

		int nRow = m_listCtrl.InsertItem(i, iter->first);//插入行
		m_listCtrl.SetItemText(nRow, 1, iter->second);//设置数据
		++i;
	}

	return 1;
}
HBRUSH CPresetInfoQueryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPresetInfoQueryDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}
