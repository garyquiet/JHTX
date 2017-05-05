#pragma once
#include "afxwin.h"

#include "const.h"

// CWorkingModeDlg �Ի���

class CWorkingModeDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkingModeDlg)

public:
	CWorkingModeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkingModeDlg();

// �Ի�������
	enum { IDD = IDD_L1_GZMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	// ��ǰ����ģʽ��ѯ���
	CString m_strQueryResult;
	// ����ģʽ���������
	CComboBox m_comboWorkingMode;

private:
	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

	//������ʾ��Ϣ
	void SetTipInfo(CString tip);

	//��ʼ��
	void Init();


public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
