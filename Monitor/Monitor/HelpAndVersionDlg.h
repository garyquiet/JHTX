#pragma once

#include "const.h"
// CHelpAndVersionDlg �Ի���

class CHelpAndVersionDlg : public CDialog
{
	DECLARE_DYNAMIC(CHelpAndVersionDlg)

public:
	CHelpAndVersionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelpAndVersionDlg();

// �Ի�������
	enum { IDD = IDD_L2_XTSZ_HELP_VERSION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

private:
	//��ʼ��
	void Init();

	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();
};
