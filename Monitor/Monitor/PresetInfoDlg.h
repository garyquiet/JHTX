#pragma once


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
};
