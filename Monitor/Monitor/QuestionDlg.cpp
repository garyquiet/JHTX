// QuestionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg �Ի���

IMPLEMENT_DYNAMIC(CQuestionDlg, CDialog)

CQuestionDlg::CQuestionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestionDlg::IDD, pParent)
	, m_info(_T(""))
{

}

CQuestionDlg::~CQuestionDlg()
{
}

void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO_STATIC, m_info);
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
END_MESSAGE_MAP()


// CQuestionDlg ��Ϣ�������
// QuestionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg �Ի���

IMPLEMENT_DYNAMIC(CQuestionDlg, CDialog)

CQuestionDlg::CQuestionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestionDlg::IDD, pParent)
{

}

CQuestionDlg::~CQuestionDlg()
{
}

void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CQuestionDlg ��Ϣ�������

HBRUSH CQuestionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CQuestionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

BOOL CQuestionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
// QuestionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg �Ի���

IMPLEMENT_DYNAMIC(CQuestionDlg, CDialog)

CQuestionDlg::CQuestionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestionDlg::IDD, pParent)
{

}

CQuestionDlg::~CQuestionDlg()
{
}

void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
END_MESSAGE_MAP()


// CQuestionDlg ��Ϣ�������
