#include "stdafx.h"
#include "UiScrollStringCtrl.h"



CUiScrollStringCtrl::CUiScrollStringCtrl()
{
	m_nScrollSpeed  = 100;
	m_bEnabled      = true;
	m_MouseHover    = false;
	m_strScroll     = _T("");
	m_rcString      = CRect(0, 0, 0, 0);
	m_pFont         = NULL;
	m_szContent     = CSize(0, 0);
	m_nDirection    = SCROLL_R2L;
	m_nScrollOffset = 0;
	m_rcMargin      = CRect(0, 0, 0, 0);
	m_clrText       = CLR_NONE;
}

CUiScrollStringCtrl::~CUiScrollStringCtrl()
{
}

BEGIN_MESSAGE_MAP(CUiScrollStringCtrl, CUiBase)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::AddString(CString strScroll) 
{
	m_strScroll = strScroll;
	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::SetScrollSpeed(int nMillisecond) 
{ 
	ASSERT(nMillisecond > 0);

	if(m_nScrollSpeed != nMillisecond) 
	{
		if(m_bEnabled)
		{
			KillTimer(1);
			SetTimer(1, nMillisecond, 0);
		}

		m_nScrollSpeed = nMillisecond;
	}
}
//------------------------------------------------------------------------------------
int CUiScrollStringCtrl::GetDirection()
{
	return m_nDirection;
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::SetDirection(int nDirection)
{
	if(nDirection == SCROLL_L2R || nDirection == SCROLL_R2L ||
	   nDirection == SCROLL_T2B || nDirection == SCROLL_B2T)
	{
		m_nDirection = nDirection;
	}
}
//------------------------------------------------------------------------------------
bool CUiScrollStringCtrl::IsEnable()
{
	return m_bEnabled;
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::Enable(bool bEnabled)
{
	if(m_bEnabled != bEnabled) 
	{
		if(m_bEnabled)
		{
			KillTimer(1);
		}
		else
		{
			SetTimer(1, m_nScrollSpeed, 0);
		}

		m_bEnabled = bEnabled;
	}
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::SetMargin(int left, int top, int right, int bottom)
{
	m_rcMargin.left   = left;
	m_rcMargin.top    = top;
	m_rcMargin.right  = right;
	m_rcMargin.bottom = bottom;
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::SetFont(CFont* pFont, COLORREF clrText)
{
	m_pFont   = pFont;
	m_clrText = clrText;
}
//------------------------------------------------------------------------------------
int CUiScrollStringCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetTimer(1, m_nScrollSpeed, NULL);

	return CWnd::OnCreate(lpCreateStruct);
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_MouseHover && m_bEnabled)
	{
		m_MouseHover = true;
		Enable(false);

		//Active WM_MOUSELEAVE message
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize      = sizeof(trackmouseevent);
		trackmouseevent.dwFlags     = TME_LEAVE;
		trackmouseevent.hwndTrack   = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&trackmouseevent);
	}

	return CUiBase::OnMouseMove(nFlags, point);
}
//------------------------------------------------------------------------------------
LRESULT CUiScrollStringCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_MouseHover && !m_bEnabled)
	{
		m_MouseHover = false;
		Enable(true);
	}

	return 0; 
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if(1 != nIDEvent) { return; }

	switch(m_nDirection)
	{
	case SCROLL_L2R: m_nScrollOffset++; if(m_nScrollOffset > m_rcString.right)  { m_nScrollOffset = m_rcString.left - m_szContent.cx;  } break;
	case SCROLL_R2L: m_nScrollOffset--; if(m_nScrollOffset < m_rcString.left - m_szContent.cx)  { m_nScrollOffset = m_rcString.right;  } break;
	case SCROLL_T2B: m_nScrollOffset++; if(m_nScrollOffset > m_rcString.bottom) { m_nScrollOffset = m_rcString.top  - m_szContent.cy;  } break;
	case SCROLL_B2T: m_nScrollOffset--; if(m_nScrollOffset < m_rcString.top  - m_szContent.cy)  { m_nScrollOffset = m_rcString.bottom; } break;
	}

	Invalidate(FALSE);

	CUiBase::OnTimer(nIDEvent);
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::OnDestroy()
{
	if(m_bEnabled)
	{
		KillTimer(1);
	}
	CUiBase::OnDestroy();
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::Draw(CDC* pDC, CRect rcCli) 
{
	DrawString(pDC, rcCli);
}
//------------------------------------------------------------------------------------
void CUiScrollStringCtrl::DrawString(CDC* pDC, CRect rcCli)
{
	rcCli.DeflateRect(m_rcMargin);

	if(m_strScroll != _T(""))
	{
		CRgn clipRgn;
		clipRgn.CreateRectRgnIndirect(&rcCli);
		pDC->SelectClipRgn(&clipRgn);

		CFont* pOldFont = NULL; 
		if(NULL != m_pFont)
		{
			pOldFont = pDC->SelectObject(m_pFont);
		}
		if(m_clrText != CLR_NONE)
		{
			pDC->SetTextColor(m_clrText);
		}
		pDC->SetBkMode(TRANSPARENT);

		CRect rc;
		if(m_rcString != rcCli)
		{
			m_rcString = rcCli;
	
			rc = m_rcString;
			m_szContent.cx = (pDC->GetTextExtent(m_strScroll)).cx;
			m_szContent.cy = pDC->DrawText(m_strScroll, &rc, DT_EXPANDTABS | DT_NOCLIP | DT_CALCRECT | DT_NOPREFIX | DT_WORDBREAK);

			switch(m_nDirection)
			{
			case SCROLL_L2R: m_nScrollOffset = m_rcString.left - m_szContent.cx; break;
			case SCROLL_R2L: m_nScrollOffset = m_rcString.right;                 break;
			case SCROLL_T2B: m_nScrollOffset = m_rcString.top  - m_szContent.cy; break;
			case SCROLL_B2T: m_nScrollOffset = m_rcString.bottom;                break;
			}
		} 

		UINT uFlag = 0;
		rc = m_rcString;
		if(m_nDirection == SCROLL_L2R || m_nDirection == SCROLL_R2L)
		{
			rc.left = m_nScrollOffset; 
			uFlag = DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK | DT_SINGLELINE;
		}
		if(m_nDirection == SCROLL_T2B || m_nDirection == SCROLL_B2T) 
		{
			rc.top = m_nScrollOffset;
			uFlag = DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK;
		}

		pDC->DrawText(m_strScroll, &rc, uFlag);

		if(NULL != pOldFont)
		{
			pDC->SelectObject(pOldFont);
		}

		clipRgn.DeleteObject();
	}
}
//------------------------------------------------------------------------------------
