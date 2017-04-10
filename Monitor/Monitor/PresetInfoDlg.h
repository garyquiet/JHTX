#pragma once


// CPresetInfoDlg 对话框

class CPresetInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoDlg)

public:
	CPresetInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPresetInfoDlg();

// 对话框数据
	enum { IDD = IDD_L1_YZXX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
