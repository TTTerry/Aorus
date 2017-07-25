#include "stdafx.h"
#include "UiHotKeyCtrl.h"



CUiHotKeyCtrl::CUiHotKeyCtrl()
{
	m_pFont   = NULL;
	m_clrText = CLR_NONE;
}

CUiHotKeyCtrl::~CUiHotKeyCtrl()
{
	m_Brush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CUiHotKeyCtrl, CHotKeyCtrl)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//-------------------------------------------------------------------------------
void CUiHotKeyCtrl::SetFont(CFont* pFont, COLORREF clrFont)
{
	m_pFont   = pFont;
	m_clrText = clrFont;
}
//-------------------------------------------------------------------------------
void CUiHotKeyCtrl::SetBkColor(COLORREF clrBk)
{
	ASSERT(clrBk != CLR_NONE);

	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(clrBk);
}
//-------------------------------------------------------------------------------
void CUiHotKeyCtrl::SetBkBitmap(UINT uBitmap, BOOL bAutoMove)
{
	ASSERT(uBitmap != 0);
	
	CBitmap bitmap;
	bitmap.LoadBitmap(uBitmap);
	m_Brush.DeleteObject();
	m_Brush.CreatePatternBrush(&bitmap); 
	if(bAutoMove)
	{
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	bitmap.DeleteObject();
}
//-------------------------------------------------------------------------------
void CUiHotKeyCtrl::OnPaint() 
{

	CPaintDC dc(this);

	CRect rcCli;
	GetClientRect(&rcCli);

	if(NULL != m_Brush.GetSafeHandle())
	{
		dc.FillRect(&rcCli, &m_Brush);
	}
	if(m_pFont != NULL)
	{
		dc.SelectObject(m_pFont);
	}
	if(m_clrText != CLR_NONE)
	{
		dc.SetTextColor(m_clrText);
	}
	dc.SetBkMode(TRANSPARENT);
	CString str = GetHotKeyName();
	CSize sz = dc.GetTextExtent(str);
	dc.DrawText(str, &rcCli, DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK | DT_SINGLELINE);
	//::SetCaretPos(sz.cx, rcCli.top);

	CWnd* pParent = GetParent();
	while(pParent != NULL)
	{
		if(pParent->SendMessage(WM_NEW_PAINT, GetDlgCtrlID(), 0)) break;
		pParent = pParent->GetParent();
	}
}
//-------------------------------------------------------------------------------
void CUiHotKeyCtrl::OnNcPaint() 
{
	if(NULL == m_Brush.GetSafeHandle())
	{
		CHotKeyCtrl::OnNcPaint();
	}
}
//-------------------------------------------------------------------------------
BOOL CUiHotKeyCtrl::OnEraseBkgnd(CDC* pDC)
{
	if(NULL != m_Brush.GetSafeHandle())
	{
		return TRUE;
	}
	else
	{
		return CHotKeyCtrl::OnEraseBkgnd(pDC);
	}
}
//-------------------------------------------------------------------------------