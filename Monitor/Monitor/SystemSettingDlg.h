#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

#include "const.h"


// CSystemSettingDlg 对话框

class CSystemSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemSettingDlg)

public:
	CSystemSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemSettingDlg();

// 对话框数据
	enum { IDD = IDD_L1_XTSZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 时期选择控件对象
	CDateTimeCtrl m_dateTimePicker;
	// 小时选择下拉框对象
	CComboBox m_comboHour;
	// 分钟选择下拉框对象
	CComboBox m_comboMinute;
	// 秒选择下拉框对象
	CComboBox m_comboSecond;
	virtual BOOL OnInitDialog();


	afx_msg void OnBnClickedSetButton();


private:

	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();

	//初始化
	void Init();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
