// PresetInfoMaintainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"
#include "PresetInfoMaintainDlg.h"
#include "ProtocolPkg.h"
#include "AskDlg.h"
#include "MessageDlg.h"

// CPresetInfoMaintainDlg �Ի���

IMPLEMENT_DYNAMIC(CPresetInfoMaintainDlg, CDialog)

CPresetInfoMaintainDlg::CPresetInfoMaintainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoMaintainDlg::IDD, pParent)
	
	//, m_strPresetInfoForAdd(_T(""))
	, m_strPresetInfoForModify(_T(""))
	, m_iPresetInfoNoForModify(1)
	//, m_iPresetInfoNoForDelete(1)
{

}

CPresetInfoMaintainDlg::~CPresetInfoMaintainDlg()
{
}

void CPresetInfoMaintainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_ADD, m_strPresetInfoForAdd);
	//DDV_MaxChars(pDX, m_strPresetInfoForAdd, 8);
	DDX_Text(pDX, IDC_INFO_CONTENT_EDIT_FOR_MODIFY, m_strPresetInfoForModify);
	DDV_MaxChars(pDX, m_strPresetInfoForModify, 8);
	DDX_Text(pDX, IDC_INFOR_NO_EDIT_FOR_MODIFY, m_iPresetInfoNoForModify);

	//DDX_Text(pDX, IDC_INFO_NO_EDIT_FOR_DELETE, m_iPresetInfoNoForDelete);
	//DDV_MinMaxUInt(pDX, m_iPresetInfoNoForDelete, 1, 30);
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
	ON_EN_SETFOCUS(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForAdd)
	ON_EN_KILLFOCUS(IDC_INFO_CONTENT_EDIT_FOR_ADD, &CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForAdd)
	ON_EN_SETFOCUS(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnSetfocusInforNoEditForModify)
	ON_EN_KILLFOCUS(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnKillfocusInforNoEditForModify)
	ON_EN_SETFOCUS(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForModify)
	ON_EN_KILLFOCUS(IDC_INFO_CONTENT_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForModify)
	ON_EN_SETFOCUS(IDC_INFO_NO_EDIT_FOR_DELETE, &CPresetInfoMaintainDlg::OnEnSetfocusInfoNoEditForDelete)
	ON_EN_KILLFOCUS(IDC_INFO_NO_EDIT_FOR_DELETE, &CPresetInfoMaintainDlg::OnEnKillfocusInfoNoEditForDelete)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_INFOR_NO_EDIT_FOR_MODIFY, &CPresetInfoMaintainDlg::OnEnChangeInforNoEditForModify)
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

	CFont * f2 = new CFont; 
	f2->CreateFont(15, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_NORMAL, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("����")); // lpszFac 

	GetDlgItem(IDC_INPUT_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_NO_LABEL_STATIC)->SetFont(f2);
	GetDlgItem(IDC_INFOR_NO_EDIT_FOR_MODIFY)->SetFont(f2);
	GetDlgItem(IDC_CONTENT_LABEL_STATIC)->SetFont(f2);
	GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_MODIFY)->SetFont(f2);


	GetDlgItem(IDC_OPERATE_GROUP_STATIC)->SetFont(f2);
	GetDlgItem(IDC_ADD_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_MODIFY_BUTTON)->SetFont(f2);
	GetDlgItem(IDC_DELETE_BUTTON)->SetFont(f2);
	GetDlgItem(IDCANCEL)->SetFont(f2);


	GetDlgItem(IDC_STATIC_COM_STATUS)->SetFont(f2);
	GetDlgItem(IDC_SYSTEM_TIME_STATIC)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POWER)->SetFont(f2);
	GetDlgItem(IDC_COMPLETE_STUTAS_STATIC)->SetFont(f2);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//��ʾ��������״̬
void CPresetInfoMaintainDlg::ShowConnectionStatus(){
	CString str = L"";

	if(theApp.m_IsComConnected)
		str = (L"��������:����");
	else
		str = str = (L"��������:δ����");
	((CStatic*)GetDlgItem(IDC_STATIC_COM_STATUS))->SetWindowText(str);
}

//��ʾϵͳʱ��
void CPresetInfoMaintainDlg::ShowSystemTime(){
	CTime tm; 
	tm=CTime::GetCurrentTime();
	CString str = tm.Format(L"%Y/%m/%d %H:%M:%S");
	//CString str = tm.Format(L"%H:%M:%S");
	((CStatic*)GetDlgItem(IDC_SYSTEM_TIME_STATIC))->SetWindowText(str);
}

//��ʾ����
void CPresetInfoMaintainDlg::ShowBatteryPower(){
	SYSTEM_POWER_STATUS_EX2 spsCurrent; 
	DWORD dwLen = GetSystemPowerStatusEx2(&spsCurrent, sizeof(spsCurrent), TRUE);

	CString str = L"";

	if(dwLen != 0){
		if(spsCurrent.ACLineStatus == AC_LINE_ONLINE)
		{
			if(spsCurrent.BatteryLifePercent < 100)
			{

				// ���ڳ��
				//SetPowerStepBmp(200);
				//MessageBox(_T("���..."));
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"���:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"���:%d%%", 100);
				}

				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_CHARING_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else
			{
				// ������
				//SetPowerStepBmp(300);
				if (spsCurrent.BatteryLifePercent <= 100)
				{
					str.Format(L"��Դ:%d%%", spsCurrent.BatteryLifePercent);
				}
				else
				{
					str.Format(L"��Դ:%d%%", 100);
				}

				((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_POWER_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 

			}
		}
		else
		{
			//MessageBox(_T("ֱ����"));

			if (spsCurrent.BatteryLifePercent <= 100)
			{
				str.Format(L"���:%d%%",spsCurrent.BatteryLifePercent);
			}
			else
			{
				str.Format(L"���:%d%%",100);
			}

			((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);

			if (spsCurrent.BatteryLifePercent >= 100)
			{
				//Full
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_FULL_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 100 && spsCurrent.BatteryLifePercent >= 70){
				//More
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_MORE_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}

			else if(spsCurrent.BatteryLifePercent < 70 && spsCurrent.BatteryLifePercent >= 40){
				//Media
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_MEDIA_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else if(spsCurrent.BatteryLifePercent < 40 && spsCurrent.BatteryLifePercent >= 10){
				//Less
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_LESS_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
			else{
				//Empty
				//����Դ�м���ͼƬ
				CBitmap bitmap;
				// ����CBitmap���ص�λͼ�ľ��
				HBITMAP hBmp;   
				//����ָ��λͼ��Դ BmpͼƬID
				bitmap.LoadBitmap(IDB_EMPTY_BITMAP);
				// ��ȡbitmap����λͼ�ľ��
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
				//��ȡ�Ի����ϵľ�� ͼƬ�ؼ�ID
				CStatic *p=(CStatic *)GetDlgItem(IDC_POWER_PIC_STATIC);  
				//���þ�̬�ؼ����ڷ��Ϊλͼ������ʾ
				//p->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE); 
				//��ͼƬ���õ�Picture�ؼ���
				p->SetBitmap(hBmp); 
			}
		}
	}
	//str.Format(L"����:%d%%",spsCurrent.BatteryLifePercent);
	//((CStatic*)GetDlgItem(IDC_STATIC_POWER))->SetWindowText(str);
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
	
	
	if(TRUE == UpdateData(TRUE))
	{
		if (m_iPresetInfoNoForModify < 1 || m_iPresetInfoNoForModify > 30)
		{
			CMessageDlg dlg;
			dlg.m_info = L"��Ϣ��ű�����1��30֮��!";
			dlg.DoModal();
			return;
		}
		if (m_strPresetInfoForModify.Trim().GetLength() > 0)
		{
			CAskDlg askDlg;
			askDlg.m_info = L"ȷ��Ҫ����Ԥ����Ϣ��";
			if(IDOK == askDlg.DoModal()){

				DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_ADD, ANY, m_strPresetInfoForModify.Trim());

				if (len > 0)
				{
					CString tip = L"Ԥ����Ϣ��������ͳɹ�!";
					SetTipInfo(tip);
				}
				else{
					CString tip = L"Ԥ����Ϣ���������ʧ��!";
					SetTipInfo(tip);
				}
			}
		}
		else{
			//MessageBox(L"Ԥ����Ϣ����Ϊ��!");
			CMessageDlg dlg;
			dlg.m_info = L"Ԥ����Ϣ����Ϊ��!";
			dlg.DoModal();
		}
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
	if(m_strPresetInfoForModify.Trim().GetLength() > 0)
	{
		/*BOOL ret = CProtocolPkg::isHanZi(m_strPresetInfoForAdd.GetAt(m_strPresetInfoForAdd.GetLength() - 1));
		if (ret == FALSE)
		{
			m_strPresetInfoForAdd.Delete(m_strPresetInfoForAdd.GetLength() - 1, 1);
		}*/
		m_strPresetInfoForModify = CProtocolPkg::eliminateNonHanZi(m_strPresetInfoForModify);
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
		CString strInfo;
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_MODIFY))->GetWindowText(strInfo);
		int nLength = strInfo.GetLength();
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_MODIFY))->SetSel(nLength,nLength, FALSE);
		((CEdit*)GetDlgItem(IDC_INFO_CONTENT_EDIT_FOR_MODIFY))->SetFocus();
	}
}

void CPresetInfoMaintainDlg::OnBnClickedModifyButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(TRUE == UpdateData(TRUE)){

		if (m_strPresetInfoForModify.Trim().GetLength() > 0)
		{
			CAskDlg askDlg;
			askDlg.m_info = L"ȷ��Ҫ�޸�Ԥ����Ϣ��";
			if(IDOK == askDlg.DoModal()){

				CString tmp = L"";
				tmp.Format(L"%d", m_iPresetInfoNoForModify);
				DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_MODIFY, tmp, m_strPresetInfoForModify.Trim());

				if (len > 0)
				{
					CString tip = L"Ԥ����Ϣ��������ͳɹ�!";
					SetTipInfo(tip);
				}
				else{
					CString tip = L"Ԥ����Ϣ���������ʧ��!";
					SetTipInfo(tip);
				}
			}
		}
		else{
			//MessageBox(L"Ԥ����Ϣ����Ϊ��!");
			CMessageDlg dlg;
			dlg.m_info = L"Ԥ����Ϣ����Ϊ��!";
			dlg.DoModal();
		}
	}
		
	
}

void CPresetInfoMaintainDlg::OnBnClickedDeleteButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CAskDlg askDlg;
	askDlg.m_info = L"ȷ��Ҫɾ��Ԥ����Ϣ��";
	if(IDOK == askDlg.DoModal()){

		if(TRUE == UpdateData(TRUE)){

			CString tmp = L"";
			tmp.Format(L"%d", m_iPresetInfoNoForModify);
			DWORD len = CProtocolPkg::SendPRCFGPacket(PRCFG, PRCFG_CfgID_DELETE, tmp, ANY);

			if (len > 0)
			{
				CString tip = L"Ԥ����Ϣɾ������ͳɹ�!";
				SetTipInfo(tip);
			}
			else{
				CString tip = L"Ԥ����Ϣɾ�������ʧ��!";
				SetTipInfo(tip);
			}
		}
	}
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInforNoEditForModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInforNoEditForModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoContentEditForModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoContentEditForModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

void CPresetInfoMaintainDlg::OnEnSetfocusInfoNoEditForDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(TRUE);
}

void CPresetInfoMaintainDlg::OnEnKillfocusInfoNoEditForDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SipShowIM(FALSE);
}

HBRUSH CPresetInfoMaintainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if(nCtlColor==CTLCOLOR_BTN) //���İ�ť��ɫ
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));			//��ť���ֺ�ɫ
		pDC->SetBkColor(RGB(186,71,8));		//��ť������ɫ
		HBRUSH b=CreateSolidBrush(RGB(186,71,8));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_SCROLLBAR) //
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(233,233,220));
		HBRUSH b=CreateSolidBrush(RGB(233,233,220));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_EDIT) //���ı༭��
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,255,0));
		HBRUSH b=CreateSolidBrush(RGB(0,255,0));
		return b;
	}
	else if(nCtlColor==CTLCOLOR_STATIC) //���ľ�̬�ı�
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkColor(RGB(0,0,0));			//��̬�����ְ�ɫ
		HBRUSH b=CreateSolidBrush(RGB(0,0,0));	//��̬�򱳾���ɫ
		return b;
	}
	else if(nCtlColor==CTLCOLOR_MSGBOX) //���ĶԻ��򱳾�ɫ
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(166,254,1));
		HBRUSH b=CreateSolidBrush(RGB(166,254,1));
		return b;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CPresetInfoMaintainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect; 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(0,0,0)); 
}

void CPresetInfoMaintainDlg::OnEnChangeInforNoEditForModify()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData(TRUE);
	if(m_iPresetInfoNoForModify.Trim().GetLength() > 0)
	{
		m_iPresetInfoNoForModify = CProtocolPkg::eliminateNonNumber(m_iPresetInfoNoForModify);
		UpdateData(FALSE);
	}*/
}
