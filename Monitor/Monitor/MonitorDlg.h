// MonitorDlg.h : ͷ�ļ�
//

#pragma once


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
	//��ʼ��
	BOOL Init();

	//��ʾ��������
	void ShowSplashWindow();

	//��ʾ��������״̬
	void ShowConnectionStatus();

	//��ʾϵͳʱ��
	void ShowSystemTime();

	//��ʾ����
	void ShowBatteryPower();

private:
	//CnComm _Com;	//����

public:

	afx_msg LRESULT OnComRecv(WPARAM, LPARAM);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPresetInfoButton();
	afx_msg void OnBnClickedSystemSettingButton();
	afx_msg void OnBnClickedSaveSettingButton();
	afx_msg void OnBnClickedWorkingModeButton();
	afx_msg void OnBnClickedBaseStationButton();
	afx_msg void OnBnClickedSpecialCodeButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
