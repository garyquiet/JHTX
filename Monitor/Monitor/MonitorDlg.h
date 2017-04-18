// MonitorDlg.h : ͷ�ļ�
//

#pragma once

#include "CnComm.h"
#include "const.h"
#include "afxwin.h"

// CMonitorDlg �Ի���
class CMonitorDlg : public CDialog
{
// ����
public:
	CMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HOME_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()


private:
	BOOL Init();
	void ShowSplashWindow();

private:
	CnComm _Com;	//����

public:
	
	CStatic m_statusPic;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
