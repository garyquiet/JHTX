#pragma once

#include "const.h"

// CPresetInfoMaintainDlg �Ի���

class CPresetInfoMaintainDlg : public CDialog
{
	DECLARE_DYNAMIC(CPresetInfoMaintainDlg)

public:
	CPresetInfoMaintainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPresetInfoMaintainDlg();

// �Ի�������
	enum { IDD = IDD_L2_YZXX_WH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAddButton();
	
	CString m_strPresetInfoForAdd;
	afx_msg void OnEnChangeInfoContentEditForAdd();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	afx_msg void OnBnClickedCancel();
};
