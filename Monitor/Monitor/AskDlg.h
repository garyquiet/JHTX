#pragma once


// CAskDlg �Ի���

class CAskDlg : public CDialog
{
	DECLARE_DYNAMIC(CAskDlg)

public:
	CAskDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAskDlg();

// �Ի�������
	enum { IDD = IDD_QUESTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_info;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
