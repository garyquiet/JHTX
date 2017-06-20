// QuestionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg 对话框

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


// CQuestionDlg 消息处理程序
// QuestionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg 对话框

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


// CQuestionDlg 消息处理程序

HBRUSH CQuestionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CQuestionDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}

BOOL CQuestionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
// QuestionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "QuestionDlg.h"


// CQuestionDlg 对话框

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


// CQuestionDlg 消息处理程序
