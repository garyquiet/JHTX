#pragma once
#include "afxwin.h"

#include "const.h"

// CWorkingModeDlg 对话框

class CWorkingModeDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkingModeDlg)

public:
	CWorkingModeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkingModeDlg();

// 对话框数据
	enum { IDD = IDD_L1_GZMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	// 当前工作模式查询结果
	CString m_strQueryResult;
	// 工作模式下拉框对象
	CComboBox m_comboWorkingMode;

private:
	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();

	//设置提示信息
	void SetTipInfo(CString tip);

	//初始化
	void Init();


public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
