#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

#include "const.h"


// CSystemSettingDlg �Ի���

class CSystemSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemSettingDlg)

public:
	CSystemSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemSettingDlg();

// �Ի�������
	enum { IDD = IDD_L1_XTSZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ʱ��ѡ��ؼ�����
	CDateTimeCtrl m_dateTimePicker;
	// Сʱѡ�����������
	CComboBox m_comboHour;
	// ����ѡ�����������
	CComboBox m_comboMinute;
	// ��ѡ�����������
	CComboBox m_comboSecond;
	virtual BOOL OnInitDialog();


	afx_msg void OnBnClickedSetButton();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);


private:

	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

	//��ʼ��
	void Init();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedVersionButton();
};
