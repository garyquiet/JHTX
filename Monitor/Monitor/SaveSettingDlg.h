#pragma once
#include "afxwin.h"

#include "const.h"

// CSaveSettingDlg 对话框

class CSaveSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveSettingDlg)

public:
	CSaveSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaveSettingDlg();

// 对话框数据
	enum { IDD = IDD_L1_BCSZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSetButton();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	// 保存方式下拉框对象
	CComboBox m_combeSaveMethod;


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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
