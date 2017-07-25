#include "stdafx.h"
#include "UiProgressCtrl.h"

UI_PROCTRL::UI_PROCTRL()
{
	pParent  = NULL;
	uId      = 0;
	rect     = CRect(0, 0, 0, 0);
	dwStyle  = 0;
	uBar     = 0;
	uChannel = 0;
	clrMask  = CLR_NONE;
}
UI_PROCTRL::UI_PROCTRL(CWnd* parent, UINT id, CRect rcWin, UINT bar, UINT channel, COLORREF mask, DWORD style)
{
	pParent  = parent;
	uId      = id;
	rect     = rcWin;
	dwStyle  = style;
	uBar     = bar;
	uChannel = channel;
	clrMask  = mask;
}
UI_PROCTRL& UI_PROCTRL::operator = (const UI_PROCTRL* pProCtrl)
{
	pParent  = pProCtrl->pParent;
	uId      = pProCtrl->uId;
	rect     = pProCtrl->rect;
	dwStyle  = pProCtrl->dwStyle;
	uBar     = pProCtrl->uBar;
	uChannel = pProCtrl->uChannel;
	clrMask  = pProCtrl->clrMask;

	return *this;
}


CUiProgressCtrl::CUiProgressCtrl()
{
	m_nPos         = 0;
	m_nMin         = 0;
	m_nMax         = 100;
	m_nStep        = 1;
	m_nBarPosX     = 0;
	m_nBarPosY     = 0;
	m_uBar         = 0;
	m_uChannel     = 0;
	m_szBar.cx     = 0;
	m_szBar.cy     = 0;
	m_pFont        = NULL;
	m_clrMask      = CLR_NONE;
	m_clrText      = CLR_NONE;
	
	CUiBase::ModifyCtrlStyle(0, UIPBS_CENTER | UIPBS_VCENTER | UIPBS_SHOW_NOTEXT);
}

CUiProgressCtrl::~CUiProgressCtrl()
{
}

BEGIN_MESSAGE_MAP(CUiProgressCtrl, CUiBase)
END_MESSAGE_MAP()


//------------------------------------------------------------------------------------
void CUiProgressCtrl::CreateProgressCtrl(UI_PROCTRL proCtrl)
{
	Create(proCtrl.pParent, proCtrl.uId, proCtrl.rect, proCtrl.dwStyle);
	SetProgressBitmap(proCtrl.uChannel, proCtrl.uBar, proCtrl.clrMask);
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetFont(CFont* pFont, COLORREF clrFont)  
{ 
	m_pFont   = pFont; 
	m_clrText = clrFont;

	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
int  CUiProgressCtrl::GetPos()                           
{ 
	return m_nPos; 
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetPos(int nPos)                   
{ 
	m_nPos = nPos;
	m_nPos = (m_nPos > m_nMax) ? m_nMax : m_nPos;
	m_nPos = (m_nPos < m_nMin) ? m_nMin : m_nPos;	

	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
int  CUiProgressCtrl::GetStep()                          
{ 
	return m_nStep; 
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetStep(int nStep)                 
{ 
	if(m_nStep != nStep)
	{
		m_nStep = nStep; 
		Invalidate(FALSE);
	}
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::OffsetPos(int nIncrement)          
{ 
	SetPos(m_nPos + nIncrement); 
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::GetRange(int& nMin, int& nMax) 
{ 
	nMin = m_nMin; 
	nMax = m_nMax; 
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetRange(int nMin, int nMax)  
{ 
	m_nMin = nMin; 
	m_nMax = nMax; 
	m_nMin = (nMin > nMax) ? nMax : m_nMin;
	m_nMax = (nMin > nMax) ? nMin : m_nMax;

	SetPos(m_nPos); 
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetMargin(int left, int top)
{
	m_nBarPosX = left;
	m_nBarPosY = top;
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::SetProgressBitmap(UINT uChannel, UINT uBar, COLORREF clrMask)
{
	ASSERT(uChannel != 0 && uBar != 0);

	m_uBar     = uBar;
	m_uChannel = uChannel;
	m_clrMask  = clrMask;

	BITMAP  bmp;
	CBitmap bitmap;
	bitmap.LoadBitmap(m_uBar);
	bitmap.GetBitmap(&bmp);
	m_szBar.cx = bmp.bmWidth;
	m_szBar.cy = bmp.bmHeight;
	bitmap.DeleteObject();

	bitmap.LoadBitmap(m_uChannel);
	bitmap.GetBitmap(&bmp);
	ASSERT(m_szBar.cx <= bmp.bmWidth);
	ASSERT(m_szBar.cy <= bmp.bmHeight);
	SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	bitmap.DeleteObject();
}
//------------------------------------------------------------------------------------
DWORD CUiProgressCtrl::GetCtrlStyle()
{
	return CUiBase::GetCtrlStyle();
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd) 
{
	if((dwAdd & UIPBS_SHOW_NOTEXT) || (dwAdd & UIPBS_SHOW_PERCENT) || (dwAdd & UIPBS_SHOW_TIEDTEXT))
	{
		dwRemove |= UIPBS_SHOW_NOTEXT;
		dwRemove |= UIPBS_SHOW_PERCENT;
		dwRemove |= UIPBS_SHOW_TIEDTEXT;
	}
	if((dwAdd & UIPBS_LEFT) || (dwAdd & UIPBS_RIGHT) || (dwAdd & UIPBS_TOP) || (dwAdd & UIPBS_BOTTOM))
	{
		dwRemove |= UIPBS_CENTER;
		dwRemove |= UIPBS_VCENTER;
	}

	CUiBase::ModifyCtrlStyle(dwRemove, dwAdd);
	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::Draw(CDC* pDC, CRect rcCli) 
{
	DrawBar (pDC, rcCli);
	DrawText(pDC, rcCli);
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::DrawBar(CDC* pDC, CRect rcCli)
{
	//Calculate bar location
	CRect rcActive;
	if(GetCtrlStyle() & UIPBS_VERTICAL)
	{
		rcActive = CRect(m_nBarPosX, m_nBarPosY, m_nBarPosX + m_szBar.cx, Pos2Pixel(m_nPos));
	}
	else
	{
		rcActive = CRect(m_nBarPosX, m_nBarPosY, Pos2Pixel(m_nPos), m_nBarPosY + m_szBar.cy);
	}

	CDC MemDC;
	CBitmap bitmap;
	MemDC.CreateCompatibleDC(pDC);

	//draw channel
	bitmap.LoadBitmap(m_uChannel);
	CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);
	if(m_clrMask != CLR_NONE)
	{
		pDC->TransparentBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), m_clrMask);
	}
	else
	{
		pDC->BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, SRCCOPY);
	}
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();

	//draw bar
	bitmap.LoadBitmap(m_uBar);
	pOldBitmap = MemDC.SelectObject(&bitmap);
	if(m_clrMask != CLR_NONE)
	{
		pDC->TransparentBlt(rcActive.left, rcActive.top, rcActive.Width(), rcActive.Height(), &MemDC, 0, 0, rcActive.Width(), rcActive.Height(), m_clrMask);
	}
	else
	{
		pDC->BitBlt(rcActive.left, rcActive.top, rcActive.Width(), rcActive.Height(), &MemDC, 0, 0, SRCCOPY);
	}
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();

	MemDC.DeleteDC();
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::DrawText(CDC* pDC, CRect rcCli)
{
	DWORD dwStyle = GetCtrlStyle();
	if(dwStyle & UIPBS_SHOW_NOTEXT)
	{
		return;
	}

	CString sText = _T("0%%");
	if(m_nMax != m_nMin)
	{
		sText.Format(_T("%d%%"), (int)(100.0 * (m_nPos - m_nMin) / (m_nMax - m_nMin)));
	}

	LONG nGrad = 0; 
	if(NULL != m_pFont)
	{
		LOGFONT lf;
		m_pFont->GetLogFont(&lf);
		nGrad = lf.lfEscapement / 10;
	}

	int cx = 0, cy = 0;
	int dx = 0, dy = 0;
	CSize sizText = pDC->GetTextExtent(sText);
	if(nGrad == 0)         { cx = sizText.cx; cy = sizText.cy; dx = 0;           dy = sizText.cy; }
	else if(nGrad == 90)   { cx = sizText.cy; cy = sizText.cx; dx = sizText.cy;  dy = 0; }
	else if(nGrad == 180)  { cx = sizText.cx; cy = sizText.cy; dx = 0;           dy = -sizText.cy; }
	else if(nGrad == 270)  { cx = sizText.cy; cy = sizText.cx; dx = -sizText.cy; dy = 0; }
	else ASSERT(0); // angle not supported

	CPoint ptWOrg        = pDC->GetWindowOrg();
	CPoint ptVpOrgOld    = pDC->GetViewportOrg();
	int  nOldBkMode      = pDC->SetBkMode(TRANSPARENT);
	UINT uOldTextAlign   = pDC->SetTextAlign(TA_BOTTOM | TA_CENTER);
	if(CLR_NONE != m_clrText)
	{
		pDC->SetTextColor(m_clrText);
	}
	if(NULL != m_pFont)
	{
		pDC->SelectObject(m_pFont);
	}

	if(dwStyle & UIPBS_SHOW_TIEDTEXT)
	{
		//Calculate bar location
		CRect rcActive;
		if(dwStyle & UIPBS_VERTICAL)
		{
			rcActive = CRect(m_nBarPosX, m_nBarPosY, m_nBarPosX + m_szBar.cx, Pos2Pixel(m_nPos));
		}
		else
		{
			rcActive = CRect(m_nBarPosX, m_nBarPosY, Pos2Pixel(m_nPos), m_nBarPosY + m_szBar.cy);
		}

		if(((dwStyle & UIPBS_VERTICAL) ? cy : cx) <= rcActive.Width())
		{
			// align text
			dx += ((dwStyle & UIPBS_LEFT)   ? -(rcActive.Width()  - cx) : 0); 
			dx += ((dwStyle & UIPBS_RIGHT)  ?  (rcActive.Width()  - cx) : 0); 
			dy += ((dwStyle & UIPBS_TOP)    ? -(rcActive.Height() - cy) : 0);
			dy += ((dwStyle & UIPBS_BOTTOM) ?  (rcActive.Height() - cy) : 0); 

			pDC->SetViewportOrg(rcActive.left + (rcActive.Width() + dx)/2, rcActive.top + (rcActive.Height() + dy)/2);
			DrawClippedText(pDC, rcActive, sText, ptWOrg);
		}
	}
	else
	{
		CRect rc = CRect(m_nBarPosX, m_nBarPosY, m_nBarPosX + m_szBar.cx, m_nBarPosY + m_szBar.cy);

		// align text
		dx += ((dwStyle & UIPBS_LEFT)   ? -(rc.Width()  - cx) : 0); 
		dx += ((dwStyle & UIPBS_RIGHT)  ?  (rc.Width()  - cx) : 0); 
		dy += ((dwStyle & UIPBS_TOP)    ? -(rc.Height() - cy) : 0); 
		dy += ((dwStyle & UIPBS_BOTTOM) ?  (rc.Height() - cy) : 0); 

		pDC->SetViewportOrg(rc.left + (rc.Width() + dx)/2, rc.top + (rc.Height() + dy)/2);
		
		// draw text on background
		if(m_clrText != CLR_NONE)
		{
			pDC->SetTextColor(m_clrText);
		}
		DrawClippedText(pDC, rc, sText, ptWOrg);
	}

	//Restore
	pDC->SetViewportOrg(ptVpOrgOld);
	pDC->SetBkMode(nOldBkMode);
	pDC->SetTextAlign(uOldTextAlign);
}
//------------------------------------------------------------------------------------
void CUiProgressCtrl::DrawClippedText(CDC* pDC, const CRect& rcClip, CString& sText, const CPoint& ptWndOrg)
{
	CRgn rgn;
	CRect rc(rcClip);
	if(rc.IsRectEmpty())
	{
		return;
	}

	rc.OffsetRect(-ptWndOrg);
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	pDC->SelectClipRgn(&rgn);
	pDC->TextOut(0, 0, sText);
	rgn.DeleteObject();
}
//------------------------------------------------------------------------------------
int CUiProgressCtrl::Pos2Pixel(int nPos)
{
	double fRatio = (m_nMax != m_nMin) ? ((double)(nPos - m_nMin) / (m_nMax - m_nMin)) : 0.0;

	if(GetCtrlStyle() & UIPBS_VERTICAL) 
	{
		return (int)((m_szBar.cy - m_nBarPosY) * fRatio + m_nBarPosY);
	} 
	else 
	{
		return (int)((m_szBar.cx - m_nBarPosX) * fRatio + m_nBarPosX);
	}
}
//--------------------------------------------------------------------------------------------------------