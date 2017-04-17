// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "SplashWnd.h"


// CSplashWnd

IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)

CSplashWnd::CSplashWnd()
{

}

CSplashWnd::~CSplashWnd()
{
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSplashWnd 消息处理程序


BOOL CSplashWnd::CreateSplashWnd()
{
	
	if(!m_bitmap.LoadBitmap(IDB_SPLASH_BITMAP))
		return false;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	return CreateEx(0,  AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),  
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, NULL, NULL); 
}


void CSplashWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	CDC dcimage;
	if(!dcimage.CreateCompatibleDC(&dc)) 
		return ;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	CBitmap* pOldBitmap = dcimage.SelectObject(&m_bitmap);  
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcimage, 0, 0, SRCCOPY);  
	dcimage.SelectObject(pOldBitmap);  

	// 不为绘图消息调用 CWnd::OnPaint()
}
