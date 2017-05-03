// PresetInfoMaintainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"
#include "PresetInfoMaintainDlg.h"
#include "ProtocolPkg.h"


// CPresetInfoMaintainDlg �Ի���

IMPLEMENT_DYNAMIC(CPresetInfoMaintainDlg, CDialog)

CPresetInfoMaintainDlg::CPresetInfoMaintainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoMaintainDlg::IDD, pParent)
	
	, m_strPresetInfoForAdd(_T(""))
	, m_strPresetInfoForModify(_T(""))
	, m_iPresetInfoNoForModify(1)
	, m_iPresetInfoNoForDelete(1)
{

}

CPresetInfoMaintainDlg::~CPresetInfoMaintainDlg()
{
}

void CPresetInfoMaintainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_ADD, m_strPresetInfoForAdd);
	DDV_MaxChars(pDX, m_strPresetInfoForAdd, 8);
	DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_MODIFY, m_strPresetInfoForModify);
	DDV_MaxChars(pDX, m_strPresetInfoForModify, 8);
	DDX_Text(pDX, IDC_INFOR_NO_EDIT_FOR_MODIFY, m_iPresetInfoNoForModify);
	DDV_MinMaxUInt(pDX, m_iPresetInfoNoForModify, 1, 30);
	DDX_Text(pDX, IDC_INFO_NO_EDIT_FOR_DELETE, m_iPresetInfoNoForDelete);
	DDV_MinMaxUInt(pDX, m_iPresetInfoNoForDelete, 1, 30);
}


BEGIN_MESSAGE_MAP(CPresetInfoMaintainDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedAddButton)
	ON_EN_CHANGE(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd)

	ON_MESSAGE(ON_COM_RECEIVE, OnComRecv)
	ON_BN_CLICKED(IDCANCEL, &CPresetInfoMaintainDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForModify)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedModifyButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CPresetInfoMaintainDlg::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// CPresetInfoMaintainDlg ��Ϣ�������

BOOL CPresetInfoMaintainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ShowBatteryPower();
	ShowConnectionStatus();
	ShowSystemTime();
	SetTimer(TIMER_EVENT_DATETIME,TIME_INTERVAL_SENCOND, NULL);
	SetTimer(TIMER_EVENT_POWER,TIME_INTERVAL_MINUTE, NULL);

	theApp.m_Com.SetWnd(this->m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//��ʾ��������״̬
void CPresetInfoMaintainDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_Com.IsOpen())
		str = (L"��������:����");
	else
		str = str = (L"��������:�Ͽ�");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CPresetInfoMaintainDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CPresetInfoMaintainDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx(&spsCurrent, TRUE);

	CString str = L"";
	str.Format(L"����:%d%%",spsCurrent.BackupBatteryLifePercent);
	((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
}

//������ʾ��Ϣ
void CPresetInfoMaintainDlg::SetTipInfo(CString tip){
	CTime tm = CTime::GetCurrentTime();
	//CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	CString time = tm.Format(L"%H:%M:%S");
	CString info = L"";
	info.Format(L"%s  %s",time, tip);
	SetDlgItemText(IDC_COMPLETE_STUTAS_STATIC, info);
}

void CPresetInfoMaintainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TIMER_EVENT_DATETIME)
	{
		ShowConnectionStatus();
		ShowSystemTime();
	}
	else if(nIDEvent == TIMER_EVENT_POWER){
		ShowBatteryPower();
	}

	CDialog::OnTimer(nIDEvent);
}

//����Ԥ����Ϣ
void CPresetInfoMaintainDlg::OnBnClickedAddButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_strPresetInfoForAdd.Trim().GetLength() > 0)
	{
	
		DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_ADD, ANY, m_strPresetInfoForAdd.Trim());

		if (len > 0)
		{
			CString tip = L"Ԥ����Ϣ��������ͳɹ�!";
			SetTipInfo(tip);
		}
	}
	else{
		MessageBox(L"Ԥ����Ϣ����Ϊ��!");
	}

}

void CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForAdd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(m_strPresetInfoForAdd.Trim().GetLength() > 0)
	{
		/*BOOL ret = CProtocolPkg::isHanZi(m_strPresetInfoForAdd.GetAt(m_strPresetInfoForAdd.GetLength() - 1));
		if (ret == FALSE)
		{
			m_strPresetInfoForAdd.Delete(m_strPresetInfoForAdd.GetLength() - 1, 1);
		}*/
		m_strPresetInfoForAdd = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForAdd);
		UpdateData(FALSE);

		/*int nLength = m_strPresetInfoForAdd.GetLength();
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_ADD))->SetFocus();*/
	}
}

LRESULT CPresetInfoMaintainDlg::OnComRecv(WPARAM wParam, LPARAM lParam)
{
	char buf[RCV_BUFFER_SIZE];
	TCHAR sbuf[RCV_BUFFER_SIZE];
	memset(sbuf, 0, sizeof(sbuf));
	int len;

	len = theApp.m_Com.Read(buf, RCV_BUFFER_SIZE);

	mbstowcs(sbuf, buf, len);

	CString str = L"";
	str += sbuf;
	str += _T("\r\n");

	CString tip = CProtocolPkg::ParseANS(1,str);
	SetTipInfo(tip);

	return 1;
}
void CPresetInfoMaintainDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//((CPresetInfoDlg*)GetParent())->m_hWnd
	theApp.m_Com.SetWnd(((CPresetInfoDlg*)GetParent())->m_hWnd);
	OnCancel();
}

void CPresetInfoMaintainDlg::OnEnChangeInfoContentEditForModify()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strPresetInfoForModify.Trim().GetLength() > 0)
	{
		m_strPresetInfoForModify = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForModify);
		UpdateData(FALSE);
	}
}

void CPresetInfoMaintainDlg::OnBnClickedModifyButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(TRUE == UpdateData(TRUE)){

		if (m_strPresetInfoForModify.Trim().GetLength() > 0)
		{
			CString tmp = L"";
			tmp.Format(L"%d", m_iPresetInfoNoForModify);
			DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_MODIFY, tmp, m_strPresetInfoForModify.Trim());

			if (len > 0)
			{
				CString tip = L"Ԥ����Ϣ��������ͳɹ�!";
				SetTipInfo(tip);
			}
		}
		else{
			MessageBox(L"Ԥ����Ϣ����Ϊ��!");
		}
		
	}
}

void CPresetInfoMaintainDlg::OnBnClickedDeleteButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(TRUE == UpdateData(TRUE)){

		CString tmp = L"";
		tmp.Format(L"%d", m_iPresetInfoNoForDelete);
		DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_DELETE, tmp, ANY);

		if (len > 0)
		{
			CString tip = L"Ԥ����Ϣɾ������ͳɹ�!";
			SetTipInfo(tip);
		}
	}
	
}
