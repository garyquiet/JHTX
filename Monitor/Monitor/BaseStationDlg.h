#pragma once

#include "const.h"

// CBaseStationDlg 对话框

class CBaseStationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseStationDlg)

public:
	CBaseStationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseStationDlg();

// 对话框数据
	enum { IDD = IDD_L1_ZHJZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
	// 指挥基站号码查询结果
	CString m_strQueryResult;
	// 指挥基站中心号码
	CString m_strBaseCenterNo;
	afx_msg void OnEnChangeNumberEdit();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

private:
	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();

	//设置操作结果提示信息
	void SetTipInfo(CString tip);

	//初始化
	void Init();
public:
	afx_msg void OnEnSetfocusNumberEdit();
	afx_msg void OnEnKillfocusNumberEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	// 重复输入的指挥基站中心号码
	CString m_strBaseCenterNoRepeat;
	afx_msg void OnEnChangeNumberRepeatEdit();
	afx_msg void OnEnSetfocusNumberRepeatEdit();
	afx_msg void OnEnKillfocusNumberRepeatEdit();
};
