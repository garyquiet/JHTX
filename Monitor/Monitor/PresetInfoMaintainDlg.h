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

	//设置操作结果提示信息
	void SetTipInfo(CString tip);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAddButton();
	
	CString m_strPresetInfoForAdd;
	afx_msg void OnEnChangeInfoContentEditForAdd();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	afx_msg void OnBnClickedCancel();
};
