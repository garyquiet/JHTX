#pragma once


// CAskDlg 对话框

class CAskDlg : public CDialog
{
	DECLARE_DYNAMIC(CAskDlg)

public:
	CAskDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAskDlg();

// 对话框数据
	enum { IDD = IDD_QUESTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_info;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
