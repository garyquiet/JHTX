#pragma once

#include "const.h"

// CPresetInfoDlg �Ի���

class CPresetInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoDlg)

public:
	CPresetInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPresetInfoDlg();

// �Ի�������
	enum { IDD = IDD_L1_YZXX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	//��ʼ��
	void Init();

	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryPresetInfoButton();
	afx_msg void OnBnClickedMaintainPresetInfoButton();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
