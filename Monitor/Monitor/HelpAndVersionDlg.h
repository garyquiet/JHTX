#pragma once

#include "const.h"
// CHelpAndVersionDlg 对话框

class CHelpAndVersionDlg : public CDialog
{
	DECLARE_DYNAMIC(CHelpAndVersionDlg)

public:
	CHelpAndVersionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHelpAndVersionDlg();

// 对话框数据
	enum { IDD = IDD_L2_XTSZ_HELP_VERSION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

private:
	//初始化
	void Init();

	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();
};
