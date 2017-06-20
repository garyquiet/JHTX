#pragma once

#include "const.h"
#include "afxcmn.h"

// CPresetInfoQueryDlg 对话框

class CPresetInfoQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoQueryDlg)

public:
	CPresetInfoQueryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPresetInfoQueryDlg();

// 对话框数据
	enum { IDD = IDD_L2_YZXX_CX_DIALOG };

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

	//初始化列表控件
	void InitListCtrl();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	CListCtrl m_listCtrl;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRequeryButton();
};
