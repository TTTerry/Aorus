#include "stdafx.h"
#include "UiSliderCtrl.h"
#include "UiCommon.h"


UI_SLIDERCTRL::UI_SLIDERCTRL()
{
	pParent         = NULL;
	uId             = 0;
	rect            = CRect(0, 0, 0, 0);
	dwStyle         = 0;
	uThumb          = 0;
	uThumbActive    = 0;
	uThumbDisable   = 0;
	uChannel        = 0;
	uChannelActive  = 0;
	uChannelDisable = 0;
	clrMask         = CLR_NONE;
}
UI_SLIDERCTRL::UI_SLIDERCTRL(CWnd* parent, UINT id, CRect rcWin, UINT thumb, UINT thumbA, UINT thumbD, 
							 UINT channel, UINT channelA, UINT channelD, COLORREF mask, DWORD style)
{
	pParent         = parent;
	uId             = id;
	rect            = rcWin;
	dwStyle         = style;
	uThumb          = thumb;
	uThumbActive    = thumbA;
	uThumbDisable   = thumbD;
	uChannel        = channel;
	uChannelActive  = channelA;
	uChannelDisable = channelD;
	clrMask         = mask;
}
UI_SLIDERCTRL& UI_SLIDERCTRL::operator = (const UI_SLIDERCTRL* pSliderCtrl)
{
	pParent         = pSliderCtrl->pParent;
	uId             = pSliderCtrl->uId;
	rect            = pSliderCtrl->rect;
	dwStyle         = pSliderCtrl->dwStyle;
	uThumb          = pSliderCtrl->uThumb;
	uThumbActive    = pSliderCtrl->uThumbActive;
	uThumbDisable   = pSliderCtrl->uThumbDisable;
	uChannel        = pSliderCtrl->uChannel;
	uChannelActive  = pSliderCtrl->uChannelActive;
	uChannelDisable = pSliderCtrl->uChannelDisable;
	clrMask         = pSliderCtrl->clrMask;

	return *this;
}


IMPLEMENT_DYNAMIC(CUiSliderCtrl, CUiBase)

CUiSliderCtrl::CUiSliderCtrl()
{
	m_nPos            = 0;
	m_nMin            = 0;
	m_nMax            = 100;
	m_nWidth          = 0;
	m_nHeight         = 0;
	m_nThumbWidth     = 0;
	m_nThumbHeight    = 0;
	m_nMouseOffset    = 0;
	m_bEnable         = true;
	m_bFocus          = false;
	m_bLButtonDown    = false;
	m_rcMargin        = CRect(0, 0, 0, 0);
	m_uChannel        = 0;
	m_uChannelActive  = 0;
	m_uChannelDisable = 0;
	m_uThumb          = 0;
	m_uThumbActive    = 0;
	m_uThumbDisable   = 0;
	m_clrMask         = CLR_NONE;
}

CUiSliderCtrl::~CUiSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CUiSliderCtrl, CUiBase)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::CreateSliderCtrl(UI_SLIDERCTRL sliderCtrl)
{
	Create(sliderCtrl.pParent, sliderCtrl.uId, sliderCtrl.rect, sliderCtrl.dwStyle);
	SetSliderBitmap(sliderCtrl.uChannel, sliderCtrl.uChannelActive, sliderCtrl.uChannelDisable, sliderCtrl.uThumb, sliderCtrl.uThumbActive, sliderCtrl.uThumbDisable, sliderCtrl.clrMask);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::SetMargin(int l, int t, int r, int b) 
{
	m_rcMargin = CRect(l, t, r, b); 
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::GetRange(int &nMin, int &nMax)        
{
	nMin = m_nMin; 
	nMax = m_nMax;
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::SetRange(int nMin, int nMax)         
{
	m_nMin = nMin; 
	m_nMax = nMax; 
	m_nMin = (nMin > nMax) ? nMax : m_nMin;
	m_nMax = (nMin > nMax) ? nMin : m_nMax;

	SetPos(m_nPos);
}
//--------------------------------------------------------------------------------------------------------
int CUiSliderCtrl::GetPos()                              
{
	return m_nPos;
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::SetPos(int nPos) 
{
	m_nPos = nPos;
	m_nPos = (m_nPos > m_nMax) ? m_nMax : m_nPos; 
	m_nPos = (m_nPos < m_nMin) ? m_nMin : m_nPos;

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::OffsetPos(int nIncrement)
{
	SetPos(m_nPos + nIncrement);
}
//--------------------------------------------------------------------------------------------------------
//Load bitmaps for a channel and thumb
void CUiSliderCtrl::SetSliderBitmap(UINT uChannel, UINT uChannelActive, UINT uChannelDisable, UINT uThumb, UINT uThumbActive, UINT uThumbDisable, COLORREF clrMask)
{
	ASSERT(GetSafeHwnd() != NULL);

	m_uChannel        = uChannel;
	m_uChannelActive  = uChannelActive;
	m_uChannelDisable = uChannelDisable;
	m_uThumb          = uThumb;
	m_uThumbActive    = uThumbActive;
	m_uThumbDisable   = uThumbDisable;
	m_clrMask         = clrMask;

	if(m_uChannel != 0)
	{
		BITMAP bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(m_uChannel);
		bitmap.GetBitmap(&bmp);

		m_nWidth  = bmp.bmWidth;
		m_nHeight = bmp.bmHeight;
		SetWindowPos(NULL, 0, 0, m_nWidth, m_nHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		bitmap.DeleteObject();
	}
	else
	{
		CRect rcCli;
		GetClientRect(&rcCli);
		m_nWidth  = rcCli.Width();
		m_nHeight = rcCli.Height();
	}

	if(m_uThumb != 0)
	{
		BITMAP bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(m_uThumb);
		bitmap.GetBitmap(&bmp);

		m_nThumbWidth  = bmp.bmWidth;
		m_nThumbHeight = bmp.bmHeight;
		ASSERT(m_nThumbWidth <= m_nWidth && m_nThumbHeight <= m_nHeight);

		bitmap.DeleteObject();
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::SetToolTip(bool bAddToolTip)
{
	ASSERT(GetSafeHwnd() != NULL);

	if(bAddToolTip && NULL == m_toolTip.GetSafeHwnd()) 
	{
		CString strTip;
		strTip.Format(_T("%d"), m_nPos);
		m_toolTip.Create(this, TTS_ALWAYSTIP);
		m_toolTip.Activate(TRUE);
		m_toolTip.AddTool(this, strTip);
	}

	if(!bAddToolTip && NULL != m_toolTip.GetSafeHwnd())
	{
		m_toolTip.Activate(FALSE);
		m_toolTip.DelTool(this);
	}
}
//--------------------------------------------------------------------------------------------------------
bool CUiSliderCtrl::IsEnable()
{
	return m_bEnable;
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::Enable(bool bEnable)
{
	m_bEnable = bEnable;

	//If control is disabled during dragging
	if(!m_bEnable && m_bLButtonDown) 
	{
		ReleaseCapture();
		m_bLButtonDown = false;
	}

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiSliderCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEnable && m_toolTip.GetSafeHwnd() != NULL)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		bool bMouseOnThumb = false;
		if(GetCtrlStyle() & UISCS_VERTICAL)
		{
			bMouseOnThumb  = (abs(point.y - Pos2Pixel(m_nPos)) <= m_nThumbHeight/2);
		}
		else
		{
			bMouseOnThumb  = (abs(point.x - Pos2Pixel(m_nPos)) <=  m_nThumbWidth/2);
		}

		if(bMouseOnThumb) 
		{
			m_toolTip.RelayEvent(pMsg);
		}
	}

	return CUiBase::PreTranslateMessage(pMsg);
}
//--------------------------------------------------------------------------------------------------------
UINT CUiSliderCtrl::OnGetDlgCode() 
{
	return (GetKeyState(VK_TAB) >= 0) ? DLGC_WANTALLKEYS : CUiBase::OnGetDlgCode();
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if(!m_bEnable) { return; }

	switch(nChar)
	{
	case VK_UP:    SetPos(m_nPos - 1); break;
	case VK_LEFT:  SetPos(m_nPos - 1); break;
	case VK_DOWN:  SetPos(m_nPos + 1); break;
	case VK_RIGHT: SetPos(m_nPos + 1); break;
	default:
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags); 
		return;
	}
	
	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_SLIDER_MOVED, GetDlgCtrlID(), m_nPos)) break;
		pParent = pParent->GetParent();
	}

	CUiBase::OnKeyDown(nChar, nRepCnt, nFlags);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CUiBase::OnKillFocus(pNewWnd);
	m_bFocus = false;
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CUiBase::OnSetFocus(pOldWnd);
	m_bFocus = true;
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is started
void CUiSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	SetFocus();
	SetCapture();
	
	m_bLButtonDown = true;

	//If mouse button is clicked on the thumb, capture the coordinates of mouse 
	//pointer and center of thumb and calculate distance between them.

	bool bMouseOnThumb = false;
	int  nThumbCurLoc = Pos2Pixel(m_nPos);

	if(GetCtrlStyle() & UISCS_VERTICAL)
	{
		m_nMouseOffset = point.y - nThumbCurLoc;
		bMouseOnThumb  = (abs(m_nMouseOffset) <= m_nThumbHeight/2);
	}
	else
	{
		m_nMouseOffset = point.x - nThumbCurLoc;
		bMouseOnThumb  = (abs(m_nMouseOffset) <=  m_nThumbWidth/2);
	}

	m_nMouseOffset = bMouseOnThumb ? m_nMouseOffset : 0;

	OnMouseMove(nFlags, point);
	Invalidate(FALSE);

	CUiBase::OnLButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
// During dragging
void CUiSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bLButtonDown || !m_bEnable) { return; }

	int nPixel    = 0;
	int nBoundMin = 0;
	int nBoundMax = 0;

	// Boundary check
	if(GetCtrlStyle() & UISCS_VERTICAL)
	{
		nPixel    = point.y - m_nMouseOffset;
		nBoundMin = m_rcMargin.top + m_nThumbHeight/2;
		nBoundMax = m_nHeight - m_rcMargin.bottom - m_nThumbHeight/2;
	} 
	else 
	{
		nPixel    = point.x - m_nMouseOffset;
		nBoundMin = m_rcMargin.left + m_nThumbWidth/2;
		nBoundMax = m_nWidth - m_rcMargin.right - m_nThumbWidth/2;
	}

	nPixel = (nPixel > nBoundMax) ? nBoundMax : nPixel;
	nPixel = (nPixel < nBoundMin) ? nBoundMin : nPixel;

	if(m_nPos != Pixel2Pos(nPixel))
	{
		SetPos(Pixel2Pos(nPixel));

		CWnd* pParent = GetParent();
		while(NULL != pParent)
		{
			if(pParent->SendMessage(WM_UI_SLIDER_MOVING, GetDlgCtrlID(), m_nPos)) break;
			pParent = pParent->GetParent();
		}
	}
	else
	{
#ifdef _DEBUG
		CString sValue;
		sValue.Format(_T("MouseMove:%d,%d\n"), m_nPos, Pos2Pixel(m_nPos));
		TRACE(sValue);
#endif // _DEBUG
	}

	if(NULL != m_toolTip.GetSafeHwnd())
	{
		CString strTip; 
		strTip.Format(_T("%d"), m_nPos);
		m_toolTip.UpdateTipText(strTip, this);
	}

	Invalidate(FALSE);

	CUiBase::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is finished
void CUiSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	ReleaseCapture();
	m_bLButtonDown = false;
	
	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_SLIDER_MOVED, GetDlgCtrlID(), m_nPos)) break;
		pParent = pParent->GetParent();
	}

	Invalidate(FALSE);

	CUiBase::OnLButtonUp(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawChannel(pDC);
	DrawThumb  (pDC);
	
	//draw focus rectangle
	if((GetCtrlStyle() & UISCS_DRAWFOCUSRECT) && m_bFocus) 
	{
		pDC->DrawFocusRect(rcCli); 
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::DrawThumb(CDC* pDC)
{
	if(m_uThumb != 0)
	{
		//bool bNoUsedThumbActive = (0 == m_uThumbActive || !m_bLButtonDown || !m_bEnable);
		UINT uId = m_uThumb;
		if(!m_bEnable)
		{
			if(0 != m_uThumbDisable) 
			{ 
				uId = m_uThumbDisable;
			}
		}
		else
		{
			if(0 != m_uThumbActive && m_bLButtonDown)
			{
				uId = m_uThumbActive;
			}
		}

		CDC MemDC;
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(pDC);
		bitmap.LoadBitmap(uId);
		CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);
		
#ifdef _DEBUG
		CString sValue;
		sValue.Format(_T("DrawThumb:%d,%d\n"), m_nPos, Pos2Pixel(m_nPos));
		TRACE(sValue);
#endif // _DEBUG

		CRect rc;
		int nThumbCurLoc = Pos2Pixel(m_nPos);
		if(GetCtrlStyle() & UISCS_VERTICAL)
		{
			rc = CRect(m_rcMargin.left, nThumbCurLoc - m_nThumbHeight/2, m_nThumbWidth + m_rcMargin.left, nThumbCurLoc + m_nThumbHeight/2);
		}
		else
		{
			rc = CRect(nThumbCurLoc - m_nThumbWidth/2,  m_rcMargin.top,  nThumbCurLoc + m_nThumbWidth/2,  m_nThumbHeight + m_rcMargin.top);
		}

		if(m_clrMask != CLR_NONE)
		{
			pDC->TransparentBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 0, 0, rc.Width(), rc.Height(), m_clrMask);
		}
		else
		{
			pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
		}

		MemDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderCtrl::DrawChannel(CDC* pDC)
{
	if(m_uChannel != 0)
	{
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);

		if(m_uChannelActive != 0 && (m_bEnable || (!m_bEnable && 0 == m_uChannelDisable)))
		{
			CRect rcPart1; 
			CRect rcPart2; 
			int nThumbCurLoc = Pos2Pixel(m_nPos);
			if(GetCtrlStyle() & UISCS_VERTICAL)
			{
				rcPart1 = CRect(0, nThumbCurLoc, m_nWidth, m_nHeight);
				rcPart2 = CRect(0, 0, m_nWidth, nThumbCurLoc);
			}
			else
			{
				rcPart1 = CRect(nThumbCurLoc, 0, m_nWidth, m_nHeight);
				rcPart2 = CRect(0, 0, nThumbCurLoc, m_nHeight);
			}

			//Draw lower/upper part OR left/right side

			CBitmap bitmap1, bitmap2;
			bitmap1.LoadBitmap(m_uChannel);
			bitmap2.LoadBitmap(m_uChannelActive);

			CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap1);
			if(m_clrMask != CLR_NONE)
			{
				pDC->TransparentBlt(rcPart1.left, rcPart1.top, rcPart1.Width(), rcPart1.Height(), &MemDC, 
									rcPart1.left, rcPart1.top, rcPart1.Width(), rcPart1.Height(), m_clrMask);
			}
			else
			{
				pDC->BitBlt(rcPart1.left, rcPart1.top, rcPart1.Width(), rcPart1.Height(), &MemDC, rcPart1.left, rcPart1.top, SRCCOPY);
			}
			
			MemDC.SelectObject(&bitmap2);
			if(m_clrMask != CLR_NONE)
			{
				pDC->TransparentBlt(rcPart2.left, rcPart2.top, rcPart2.Width(), rcPart2.Height(), &MemDC, 
									rcPart2.left, rcPart2.top, rcPart2.Width(), rcPart2.Height(), m_clrMask);
			}
			else
			{
				pDC->BitBlt(rcPart2.left, rcPart2.top, rcPart2.Width(), rcPart2.Height(), &MemDC, rcPart2.left, rcPart2.top, SRCCOPY);
			}
			MemDC.SelectObject(pOldBitmap);
			
			bitmap1.DeleteObject();
			bitmap2.DeleteObject();
		}
		else
		{
			//Only one bitmap for channel
			UINT uId = m_uChannel;
			if(!m_bEnable && 0 != m_uChannelDisable)
			{
				uId = m_uChannelDisable;
			}

			CBitmap bitmap;
			bitmap.LoadBitmap(uId);

			CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);
			if(m_clrMask != CLR_NONE)
			{
				pDC->TransparentBlt(0, 0, m_nWidth, m_nHeight, &MemDC, 0, 0, m_nWidth, m_nHeight, m_clrMask);
			}
			else
			{
				pDC->BitBlt(0, 0, m_nWidth, m_nHeight, &MemDC, 0, 0, SRCCOPY);
			}
			MemDC.SelectObject(pOldBitmap);

			bitmap.DeleteObject();
		}

		MemDC.DeleteDC();
	}
}
//--------------------------------------------------------------------------------------------------------
//Calculate point of thumb from position value
int CUiSliderCtrl::Pos2Pixel(int nPos)
{
	double fRatio = (m_nMax != m_nMin) ? ((double)(nPos - m_nMin) / (m_nMax - m_nMin)) : 0.0;

	if(GetCtrlStyle() & UISCS_VERTICAL) 
	{
		return (int)((m_nHeight - m_rcMargin.top - m_rcMargin.bottom - m_nThumbHeight) * fRatio + m_rcMargin.top + m_nThumbHeight/2);
		
	} 
	else 
	{
		return (int)((m_nWidth - m_rcMargin.left - m_rcMargin.right - m_nThumbWidth) * fRatio + m_rcMargin.left + m_nThumbWidth/2);
	}
}
//--------------------------------------------------------------------------------------------------------
//Calculate position value from point of mouse
int CUiSliderCtrl::Pixel2Pos(int nPixel)
{
	if(GetCtrlStyle() & UISCS_VERTICAL) 
	{
		return (int)(m_nMin + (double)(nPixel - m_rcMargin.top - m_nThumbHeight/2) / 
			        (m_nHeight - m_rcMargin.bottom - m_rcMargin.top - m_nThumbHeight) * (m_nMax - m_nMin));
	} 
	else 
	{
		return (int)(m_nMin + (double)(nPixel - m_rcMargin.left - m_nThumbWidth/2) / 
			        (m_nWidth  - m_rcMargin.left  - m_rcMargin.right - m_nThumbWidth) * (m_nMax - m_nMin));
	}
}
//--------------------------------------------------------------------------------------------------------