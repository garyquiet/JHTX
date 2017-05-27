// Monitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "SplashWnd.h"
#include "MessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinApp)
END_MESSAGE_MAP()


// CMonitorApp ����
CMonitorApp::CMonitorApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_IsComConnected = FALSE;
}


// Ψһ��һ�� CMonitorApp ����
CMonitorApp theApp;

// CMonitorApp ��ʼ��


BOOL CMonitorApp::SelfCheck(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	//SYSTEM_POWER_STATUS_EX spsCurrent; 
	//DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);
	
	if( BATTERY_FLAG_LOW == spsCurrent.BatteryFlag){
		//AfxMessageBox(L"��ص�������!");
		CMessageDlg dlg;
		dlg.m_info = L"��ص�������!";
		dlg.DoModal();
	}

	if (!m_Com.IsOpen())
	{
		if (!m_Com.Open(COM_PORT, BAUD_RATE))
		{
			TCHAR szBuf[1024];
			wsprintf(szBuf, _T("�� COM%d ʧ��, �������:%d"), COM_PORT, GetLastError());
			//AfxMessageBox(szBuf);
			CMessageDlg dlg;
			dlg.m_info = szBuf;
			dlg.DoModal();
			return FALSE;
		}
		else
		{	
			return TRUE;
		}
	}
	return TRUE;
}

BOOL CMonitorApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	if(TRUE == SelfCheck()) //ϵͳ�Լ�ɹ�
	{
		CMonitorDlg dlg;
		m_pMainWnd = &dlg;

		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
			//  �Ի���Ĵ���
		}
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
