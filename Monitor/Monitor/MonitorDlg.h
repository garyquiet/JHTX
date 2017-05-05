// MonitorDlg.h : 头文件
//

#pragma once


#include "const.h"
#include "afxwin.h"

// CMonitorDlg 对话框
class CMonitorDlg : public CDialog
{
// 构造
public:
	CMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HOME_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()


private:
	//初始化
	BOOL Init();

	//显示启动画面
	void ShowSplashWindow();

	//显示串口连接状态
	void ShowConnectionStatus();

	//显示系统时间
	void ShowSystemTime();

	//显示电量
	void ShowBatteryPower();

private:
	//CnComm _Com;	//串口

public:

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPresetInfoButton();
	afx_msg void OnBnClickedSystemSettingButton();
	afx_msg void OnBnClickedSaveSettingButton();
	afx_msg void OnBnClickedWorkingModeButton();
	afx_msg void OnBnClickedBaseStationButton();
	afx_msg void OnBnClickedSpecialCodeButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
