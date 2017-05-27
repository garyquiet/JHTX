#pragma once

#include "const.h"

// CBaseStationDlg �Ի���

class CBaseStationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseStationDlg)

public:
	CBaseStationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseStationDlg();

// �Ի�������
	enum { IDD = IDD_L1_ZHJZ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedQueryButton();
	afx_msg void OnBnClickedSetButton();
	// ָ�ӻ�վ�����ѯ���
	CString m_strQueryResult;
	// ָ�ӻ�վ���ĺ���
	CString m_strBaseCenterNo;
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

	//��ʼ��
	void Init();
public:
	afx_msg void OnEnSetfocusNumberEdit();
	afx_msg void OnEnKillfocusNumberEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	// �ظ������ָ�ӻ�վ���ĺ���
	CString m_strBaseCenterNoRepeat;
	afx_msg void OnEnChangeNumberRepeatEdit();
	afx_msg void OnEnSetfocusNumberRepeatEdit();
	afx_msg void OnEnKillfocusNumberRepeatEdit();
};
