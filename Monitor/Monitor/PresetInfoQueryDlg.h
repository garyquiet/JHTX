#pragma once

#include "const.h"
#include "afxcmn.h"

// CPresetInfoQueryDlg �Ի���

class CPresetInfoQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoQueryDlg)

public:
	CPresetInfoQueryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPresetInfoQueryDlg();

// �Ի�������
	enum { IDD = IDD_L2_YZXX_CX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

	//��ʼ���б�ؼ�
	void InitListCtrl();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	CListCtrl m_listCtrl;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRequeryButton();
};
