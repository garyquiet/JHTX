// MonitorDlg.h : 头文件
//

#pragma once

#include "CnComm.h"
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
	BOOL Init();
	void ShowSplashWindow();

private:
	CnComm _Com;	//串口

public:
	
	CStatic m_statusPic;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
