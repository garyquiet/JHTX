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
	
	//CString m_strPresetInfoForAdd;
	afx_msg void OnEnChangeInfoContentEditForAdd();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	afx_msg void OnBnClickedCancel();
	// 输入修改的预置信息
	CString m_strPresetInfoForModify;
	afx_msg void OnEnChangeInfoContentEditForModify();
	afx_msg void OnBnClickedModifyButton();
	// 预置信息编号
	UINT m_iPresetInfoNoForModify;
	//UINT m_iPresetInfoNoForDelete;
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnEnSetfocusInfoContentEditForAdd();
	afx_msg void OnEnKillfocusInfoContentEditForAdd();
	afx_msg void OnEnSetfocusInforNoEditForModify();
	afx_msg void OnEnKillfocusInforNoEditForModify();
	afx_msg void OnEnSetfocusInfoContentEditForModify();
	afx_msg void OnEnKillfocusInfoContentEditForModify();
	afx_msg void OnEnSetfocusInfoNoEditForDelete();
	afx_msg void OnEnKillfocusInfoNoEditForDelete();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnEnChangeInforNoEditForModify();
};
