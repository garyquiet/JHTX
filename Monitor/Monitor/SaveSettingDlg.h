#pragma once
#include "afxwin.h"

#include "const.h"

// CSaveSettingDlg �Ի���

class CSaveSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveSettingDlg)

public:
	CSaveSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveSettingDlg();

// �Ի�������
	enum { IDD = IDD_L1_BCSZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSetButton();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	// ���淽ʽ���������
	CComboBox m_combeSaveMethod;


private:
	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

	//���ò��������ʾ��Ϣ
	void SetTipInfo(CString tip);

	//��ʼ��
	void Init();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
