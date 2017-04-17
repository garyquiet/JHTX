#pragma once


// CSplashWnd

class CSplashWnd : public CWnd
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd();
	virtual ~CSplashWnd();

	BOOL CreateSplashWnd();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CBitmap m_bitmap;
public:
	afx_msg void OnPaint();
};


