#include "stdafx.h"
#include "UiMulitSliderCtrl.h"
#include "UiCommon.h"


UI_MULITSLIDERCTRL::UI_MULITSLIDERCTRL()
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

UI_MULITSLIDERCTRL::UI_MULITSLIDERCTRL(CWnd* parent, UINT id, CRect rcWin, UINT thumb, UINT thumbA, UINT thumbD, 
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

UI_MULITSLIDERCTRL& UI_MULITSLIDERCTRL::operator = (const UI_MULITSLIDERCTRL* pSliderCtrl)
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


IMPLEMENT_DYNAMIC(CUiMulitSliderCtrl, CUiBase)

CUiMulitSliderCtrl::CUiMulitSliderCtrl()
{
	m_lstPos.push_back(0);
	m_curPos          = m_lstPos.begin();
	m_nMin            = 0;
	m_nMax            = 100;
	m_nWidth          = 0;
	m_nHeight         = 0;
	m_nThumbWidth     = 0;
	m_nThumbHeight    = 0;
	m_nMouseOffset    = 0;
	m_bEnable         = true;
	m_bFocus          = false;
	m_bClickAdd		  = true;
	m_bLButtonDown    = false;
	m_rcMargin        = CRect(0, 0, 0, 0);
	m_uChannel        = 0;
	m_uChannelActive  = 0;
	m_uChannelDisable = 0;
	m_uThumb          = 0;
	m_uThumbActive    = 0;
	m_uThumbDisable   = 0;
	m_nMaxPos		  = 7;
	m_nMinPos		  = 1;
	m_clrMask         = CLR_NONE;
}

CUiMulitSliderCtrl::~CUiMulitSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CUiMulitSliderCtrl, CUiBase)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::CreateSliderCtrl(UI_MULITSLIDERCTRL sliderCtrl)
{
	Create(sliderCtrl.pParent, sliderCtrl.uId, sliderCtrl.rect, sliderCtrl.dwStyle);
	SetSliderBitmap(sliderCtrl.uChannel, sliderCtrl.uChannelActive, sliderCtrl.uChannelDisable, sliderCtrl.uThumb, sliderCtrl.uThumbActive, sliderCtrl.uThumbDisable, sliderCtrl.clrMask);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::SetMargin(int l, int t, int r, int b) 
{
	m_rcMargin = CRect(l, t, r, b); 
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::GetRange(int &nMin, int &nMax)        
{
	nMin = m_nMin; 
	nMax = m_nMax;
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::SetRange(int nMin, int nMax)         
{
	m_nMin = nMin; 
	m_nMax = nMax; 
	m_nMin = (nMin > nMax) ? nMax : m_nMin;
	m_nMax = (nMin > nMax) ? nMin : m_nMax;

	SetPos(m_curPos, GetPos(m_curPos));
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::AddPos(int nIndex, int nPos)             
{
	if((int)m_lstPos.size() >= m_nMaxPos) return;
	int i = 0;
	ItemInt item;
	for (item = m_lstPos.begin(); item != m_lstPos.end(); ++item,++i)
	{
		if(i == nIndex) 
		{
			m_lstPos.insert(item, nPos);
		}
	}
	if (item == m_lstPos.end())
	{
		m_lstPos.push_back(nPos);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::RemovePos(int nIndex)             
{
	ASSERT(nIndex < (int)m_lstPos.size());
	int i = 0;
	ItemInt item;
	for (item = m_lstPos.begin(); item != m_lstPos.end(); i++)
	{
		if(i == nIndex) 
		{
			item = m_lstPos.erase(item);
			break;
		}
		else
			++item;
	}
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::Reset()             
{
	int i = 0;
	ItemInt item;
	for (item = m_lstPos.begin(); item != m_lstPos.end(); i++)
	{
		if(i >= m_nMinPos) 
		{
			item = RemovePos(item);
		}
		else
			++item;
	}
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
int CUiMulitSliderCtrl::GetPos(int nIndex)                              
{
	ASSERT(nIndex < (int)m_lstPos.size());
	int i = 0;
	for (ItemInt item = m_lstPos.begin(); item != m_lstPos.end(); ++item)
	{
		if(i++ == nIndex) return GetPos(item);
	}
	return 0;
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::SetPos(int nPos) 
{
	SetPos(m_curPos, nPos);

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::SetPos(int nIndex, int nPos) 
{
	ASSERT(nIndex < (int)m_lstPos.size());
	int i = 0;
	for (ItemInt item = m_lstPos.begin(); item != m_lstPos.end(); ++item)
	{
		if(i++ == nIndex) return SetPos(item, nPos);
	}

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OffsetPos(int nIndex, int nIncrement)
{
	ASSERT(nIndex < (int)m_lstPos.size());
	int i = 0;
	for (ItemInt item = m_lstPos.begin(); item != m_lstPos.end(); ++item)
	{
		if(i++ == nIndex) return OffsetPos(item, nIncrement);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OffsetPos(int nIncrement)
{
	return OffsetPos(m_curPos, nIncrement);
}
//--------------------------------------------------------------------------------------------------------
//Load bitmaps for a channel and thumb
void CUiMulitSliderCtrl::SetSliderBitmap(UINT uChannel, UINT uChannelActive, UINT uChannelDisable, UINT uThumb, UINT uThumbActive, UINT uThumbDisable, COLORREF clrMask)
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
void CUiMulitSliderCtrl::SetToolTip(bool bAddToolTip)
{
	ASSERT(GetSafeHwnd() != NULL);

	if(bAddToolTip && NULL == m_toolTip.GetSafeHwnd()) 
	{
		CString strTip;
		strTip.Format(_T("%d"), GetPos(m_curPos));
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
void CUiMulitSliderCtrl::ClickAddEnable(bool bEnable)
{
	m_bClickAdd = bEnable;
}
//--------------------------------------------------------------------------------------------------------
bool CUiMulitSliderCtrl::IsEnable()
{
	return m_bEnable;
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::Enable(bool bEnable)
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
BOOL CUiMulitSliderCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEnable && m_toolTip.GetSafeHwnd() != NULL)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		bool bMouseOnThumb = false;
		if(GetCtrlStyle() & UISCS_VERTICAL)
		{
			bMouseOnThumb  = (abs(point.y - Pos2Pixel(GetPos(m_curPos))) <= m_nThumbHeight/2);
		}
		else
		{
			bMouseOnThumb  = (abs(point.x - Pos2Pixel(GetPos(m_curPos))) <=  m_nThumbWidth/2);
		}

		if(bMouseOnThumb) 
		{
			m_toolTip.RelayEvent(pMsg);
		}
	}

	return CUiBase::PreTranslateMessage(pMsg);
}
//--------------------------------------------------------------------------------------------------------
UINT CUiMulitSliderCtrl::OnGetDlgCode() 
{
	return (GetKeyState(VK_TAB) >= 0) ? DLGC_WANTALLKEYS : CUiBase::OnGetDlgCode();
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if(!m_bEnable || m_lstPos.end() == m_curPos) { return; }

	switch(nChar)
	{
	case VK_UP:    OffsetPos(m_curPos, -1); break;
	case VK_LEFT:  OffsetPos(m_curPos, -1); break;
	case VK_DOWN:  OffsetPos(m_curPos,  1); break;
	case VK_RIGHT: OffsetPos(m_curPos,  1); break;
	default:
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags); 
		return;
	}
	
	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		pParent->PostMessage(WM_UI_MULITSLIDER_MOVED, GetDlgCtrlID(), GetIndex(m_curPos));
		pParent = pParent->GetParent();
	}

	CUiBase::OnKeyDown(nChar, nRepCnt, nFlags);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CUiBase::OnKillFocus(pNewWnd);
	m_bFocus = false;
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CUiBase::OnSetFocus(pOldWnd);
	m_bFocus = true;
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is started
void CUiMulitSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	SetFocus();
	SetCapture();
	
	m_bLButtonDown = true;

	//If mouse button is clicked on the thumb, capture the coordinates of mouse 
	//pointer and center of thumb and calculate distance between them.

	if(GetCtrlStyle() & UISCS_VERTICAL)
	{
		m_curPos = Pixel2Pointer(point.y, m_bClickAdd);
	}
	else
	{
		m_curPos = Pixel2Pointer(point.x, m_bClickAdd);
	}

	m_nMouseOffset = 0;

	OnMouseMove(nFlags, point);
	Invalidate(FALSE);

	CUiBase::OnLButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
// During dragging
void CUiMulitSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bLButtonDown || !m_bEnable || m_lstPos.end() == m_curPos) { return; }

	int nPixel    = 0;
	int nBoundMin = 0;
	int nBoundMax = 0;
	ItemInt prevPos = m_curPos;
	ItemInt nextPos = m_curPos;

	prevPos = m_curPos == m_lstPos.begin() ? m_lstPos.end() : --prevPos;
	nextPos = ++nextPos  == m_lstPos.end() ? m_lstPos.end() : nextPos;

	// Boundary check
	if(GetCtrlStyle() & UISCS_VERTICAL)
	{
		nPixel    = point.y;
		nBoundMin = prevPos == m_lstPos.end() ? m_rcMargin.top + m_nThumbWidth/2 : Pos2Pixel(*prevPos) + m_nThumbHeight;
		nBoundMax = nextPos == m_lstPos.end() ? m_nHeight - m_rcMargin.bottom - m_nThumbHeight/2 : Pos2Pixel(*nextPos) - m_nThumbHeight;
	} 
	else 
	{
		nPixel    = point.x;
		nBoundMin = prevPos == m_lstPos.end() ? m_rcMargin.left + m_nThumbWidth/2 : Pos2Pixel(*prevPos) + m_nThumbWidth;
		nBoundMax = nextPos == m_lstPos.end() ? m_nWidth - m_rcMargin.right - m_nThumbWidth/2 : Pos2Pixel(*nextPos) - m_nThumbWidth;
	}

	nPixel = (nPixel > nBoundMax) ? nBoundMax : nPixel;
	nPixel = (nPixel < nBoundMin) ? nBoundMin : nPixel;

	if(Pos2Pixel(GetPos(m_curPos)) != nPixel)
	{
		SetPos(m_curPos, Pixel2Pos(nPixel));

		CWnd* pParent = GetParent();
		while(NULL != pParent)
		{
			pParent->PostMessage(WM_UI_MULITSLIDER_MOVING, GetDlgCtrlID(), GetIndex(m_curPos));
			pParent = pParent->GetParent();
		}
	}

	if(NULL != m_toolTip.GetSafeHwnd())
	{
		CString strTip; 
		strTip.Format(_T("%d"), GetPos(m_curPos));
		m_toolTip.UpdateTipText(strTip, this);
	}

	CUiBase::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is finished
void CUiMulitSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	ReleaseCapture();
	m_bLButtonDown = false;
	
	CWnd* pParent = GetParent();
	while(NULL != pParent && m_lstPos.end() != m_curPos)
	{
		pParent->PostMessage(WM_UI_MULITSLIDER_MOVED, GetDlgCtrlID(), GetIndex(m_curPos));
		pParent = pParent->GetParent();
	}

	Invalidate(FALSE);

	CUiBase::OnLButtonUp(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	if(GetCtrlStyle() & UISCS_VERTICAL)
	{
		m_curPos = Pixel2Pointer(point.y, false);
	}
	else
	{
		m_curPos = Pixel2Pointer(point.x, false);
	}

	if (m_curPos != m_lstPos.end())
	{
		m_curPos = RemovePos(m_curPos);
		CWnd* pParent = GetParent();
		while(NULL != pParent && m_lstPos.end() != m_curPos)
		{
			pParent->PostMessage(WM_UI_MULITSLIDER_MOVED, GetDlgCtrlID(), GetIndex(m_curPos));
			pParent = pParent->GetParent();
		}
	}

	Invalidate(FALSE);

	CUiBase::OnRButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::Draw(CDC* pDC, CRect rcCli)
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
void CUiMulitSliderCtrl::DrawThumb(CDC* pDC)
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
		//pDC->FillSolidRect(CRect(0, 0, m_nWidth, m_nHeight), RGB(255, 0, 0));

		CDC MemDC;
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(pDC);
		bitmap.LoadBitmap(uId);
		CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);
		for (ItemInt item = m_lstPos.begin(); item != m_lstPos.end(); ++item)
		{
			CRect rc;
			int nThumbCurLoc = Pos2Pixel(GetPos(item));
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
		}

		MemDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::DrawChannel(CDC* pDC)
{
	if(m_uChannel != 0)
	{
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);

		if(m_uChannelActive != 0 && (m_bEnable || (!m_bEnable && 0 == m_uChannelDisable)))
		{
			CRect rcPart1; 
			CRect rcPart2; 
			int nThumbCurLocBegin = Pos2Pixel(GetPos(0));
			int nThumbCurLocEnd = Pos2Pixel(GetPos(GetCount() - 1));
			if(GetCtrlStyle() & UISCS_VERTICAL)
			{
				rcPart1 = CRect(0, 0, m_nWidth, m_nHeight);
				rcPart2 = CRect(0, nThumbCurLocBegin, m_nWidth, nThumbCurLocEnd);
			}
			else
			{
				rcPart1 = CRect(0, 0, m_nWidth, m_nHeight);
				rcPart2 = CRect(nThumbCurLocBegin, 0, nThumbCurLocEnd, m_nHeight);
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
int CUiMulitSliderCtrl::Pos2Pixel(int nPos)
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
int CUiMulitSliderCtrl::Pixel2Pos(int nPixel)
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
lstInt::iterator CUiMulitSliderCtrl::Pixel2Pointer(int nPixel, bool bInsert)
{
	lstInt::iterator item;
	int nOffset = m_nThumbWidth;
	if(GetCtrlStyle() & UISCS_VERTICAL) nOffset = m_nThumbHeight;
	int nPos = Pixel2Pos(nPixel);

	for (item = m_lstPos.begin(); item != m_lstPos.end(); ++item)
	{
		if(Pos2Pixel(abs(nPos - GetPos(item))) <= nOffset) return item;
		if(bInsert && nPos< GetPos(item))
		{
			if(item != m_lstPos.begin() && (int)m_lstPos.size() < m_nMaxPos)
				m_lstPos.insert(item--, nPos);
			else if((int)m_lstPos.size() >= m_nMaxPos)
			{
				return m_lstPos.end();
			}
			else
				m_lstPos.push_front(nPos);

			CWnd* pParent = GetParent();
			while(NULL != pParent)
			{
				pParent->PostMessage(WM_UI_MULITSLIDER_MOVED, GetDlgCtrlID(), 0);
				pParent = pParent->GetParent();
			}
			return ++item;
		}
		else if(nPixel < GetPos(item))
		{
			return m_lstPos.end();
		}
	}
	if (bInsert && item == m_lstPos.end())
	{
		m_lstPos.push_back(nPos);
	}
	return item;
}
//--------------------------------------------------------------------------------------------------------
int CUiMulitSliderCtrl::GetPos(ItemInt item)                              
{
	return *item;
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::SetPos(ItemInt item, int nPos) 
{
	ItemInt prev = item;
	ItemInt next = item;

	int nMax = ++next == m_lstPos.end() ? m_nMax : GetPos(next);
	int nMin = item == m_lstPos.begin() ? m_nMin : GetPos(--prev);
	*item = (GetPos(item) > nMax) ? nMax : nPos; 
	*item = (GetPos(item) < nMin) ? nMin : nPos;

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
ItemInt CUiMulitSliderCtrl::RemovePos(ItemInt it)
{
	if ((int)m_lstPos.size() <= m_nMinPos) return m_lstPos.end();
	if (it == m_lstPos.end()) return m_lstPos.end();
	return m_lstPos.erase(it);
}
//--------------------------------------------------------------------------------------------------------
int	CUiMulitSliderCtrl::GetIndex(ItemInt item)
{
	int nIndex = 0;
	for (ItemInt i = m_lstPos.begin(); i != m_lstPos.end(); ++i, nIndex++)
	{
		if(i == item) return nIndex;
	}
	return -1;
}
//--------------------------------------------------------------------------------------------------------
void CUiMulitSliderCtrl::OffsetPos(ItemInt item, int nIncrement)
{
	SetPos(item, GetPos(item) + nIncrement);
}
