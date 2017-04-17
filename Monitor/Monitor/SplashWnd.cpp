// SplashWnd.cpp : ʵ���ļ�
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



// CSplashWnd ��Ϣ�������


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
	// TODO: �ڴ˴������Ϣ����������

	CDC dcimage;
	if(!dcimage.CreateCompatibleDC(&dc)) 
		return ;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	CBitmap* pOldBitmap = dcimage.SelectObject(&m_bitmap);  
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcimage, 0, 0, SRCCOPY);  
	dcimage.SelectObject(pOldBitmap);  

	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
}
