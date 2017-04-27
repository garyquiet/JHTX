#pragma once

#include "const.h"

// CPresetInfoMaintainDlg 对话框

class CPresetInfoMaintainDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoMaintainDlg)

public:
	CPresetInfoMaintainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPresetInfoMaintainDlg();

// 对话框数据
	enum { IDD = IDD_L2_YZXX_WH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:

	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
