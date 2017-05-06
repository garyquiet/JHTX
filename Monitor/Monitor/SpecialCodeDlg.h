#pragma once

#include "const.h"

// CSpecialCodeDlg �Ի���

class CSpecialCodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpecialCodeDlg)

public:
	CSpecialCodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpecialCodeDlg();

// �Ի�������
	enum { IDD = IDD_L1_TSBH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ǰ�����ź����ѯ���
	CString m_strQueryResult;
	// �����ź���
	CString m_strSpecialCode;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
	afx_msg void OnEnChangeNumberEdit();

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

private:
	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

	//���ò��������ʾ��Ϣ
	void SetTipInfo(CString tip);
public:
	afx_msg void OnEnSetfocusNumberEdit();
	afx_msg void OnEnKillfocusNumberEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	// �ظ������������
	CString m_strSpecialCodeRepeat;
	afx_msg void OnEnChangeNumberRepeatEdit();
	afx_msg void OnEnSetfocusNumberRepeatEdit();
	afx_msg void OnEnKillfocusNumberRepeatEdit();
};
