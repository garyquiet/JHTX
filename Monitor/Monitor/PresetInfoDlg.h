#pragma once

#include "const.h"

// CPresetInfoDlg 对话框

class CPresetInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoDlg)

public:
	CPresetInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPresetInfoDlg();

// 对话框数据
	enum { IDD = IDD_L1_YZXX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryPresetInfoButton();
	afx_msg void OnBnClickedMaintainPresetInfoButton();
};
