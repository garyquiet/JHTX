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
	
	//CString m_strPresetInfoForAdd;
	afx_msg void OnEnChangeInfoContentEditForAdd();
	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);
	afx_msg void OnBnClickedCancel();
	// �����޸ĵ�Ԥ����Ϣ
	CString m_strPresetInfoForModify;
	afx_msg void OnEnChangeInfoContentEditForModify();
	afx_msg void OnBnClickedModifyButton();
	// Ԥ����Ϣ���
	UINT m_iPresetInfoNoForModify;
	//UINT m_iPresetInfoNoForDelete;
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnEnSetfocusInfoContentEditForAdd();
	afx_msg void OnEnKillfocusInfoContentEditForAdd();
	afx_msg void OnEnSetfocusInforNoEditForModify();
	afx_msg void OnEnKillfocusInforNoEditForModify();
	afx_msg void OnEnSetfocusInfoContentEditForModify();
	afx_msg void OnEnKillfocusInfoContentEditForModify();
	afx_msg void OnEnSetfocusInfoNoEditForDelete();
	afx_msg void OnEnKillfocusInfoNoEditForDelete();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnEnChangeInforNoEditForModify();
};
