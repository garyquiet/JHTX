// PresetInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PresetInfoDlg.h"


// CPresetInfoDlg 对话框

IMPLEMENT_DYNAMIC(CPresetInfoDlg, CDialog)

CPresetInfoDlg::CPresetInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPresetInfoDlg::IDD, pParent)
{

}

CPresetInfoDlg::~CPresetInfoDlg()
{
}

void CPresetInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPresetInfoDlg, CDialog)
END_MESSAGE_MAP()


// CPresetInfoDlg 消息处理程序
