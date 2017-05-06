#pragma once

#include "const.h"

// CSpecialCodeDlg 对话框

class CSpecialCodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpecialCodeDlg)

public:
	CSpecialCodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSpecialCodeDlg();

// 对话框数据
	enum { IDD = IDD_L1_TSBH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 当前特殊编号号码查询结果
	CString m_strQueryResult;
	// 特殊编号号码
	CString m_strSpecialCode;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
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
public:
	afx_msg void OnEnSetfocusNumberEdit();
	afx_msg void OnEnKillfocusNumberEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	// 重复输入的特殊编号
	CString m_strSpecialCodeRepeat;
	afx_msg void OnEnChangeNumberRepeatEdit();
	afx_msg void OnEnSetfocusNumberRepeatEdit();
	afx_msg void OnEnKillfocusNumberRepeatEdit();
};
