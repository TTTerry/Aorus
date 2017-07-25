#include "stdafx.h"
#include "UiTabCtrl.h"
#include "UiCommon.h"

UITC_ARROW::UITC_ARROW()
{
	uNormal  = 0;
	uMouseIn = 0;
	uSelect  = 0;
	uDisable = 0;
	clrMask  = CLR_NONE;
}
UITC_ARROW::UITC_ARROW(UINT normal, UINT mouseIn, UINT select, UINT disable, COLORREF mask)
{
	uNormal  = normal;
	uMouseIn = mouseIn;
	uSelect  = select;
	uDisable = disable;
	clrMask  = mask;
}
UITC_ARROW& UITC_ARROW::operator = (const UITC_ARROW* pArrow)
{
	uNormal  = pArrow->uNormal;
	uMouseIn = pArrow->uMouseIn;
	uSelect  = pArrow->uSelect;
	uDisable = pArrow->uDisable;
	clrMask  = pArrow->clrMask;

	return *this;
}


UITC_TAB::UITC_TAB()
{
	pParent  = NULL;
	uNormal  = 0;
	uMouseIn = 0;
	uSelect  = 0;
	clrMask  = CLR_NONE;
}
UITC_TAB::UITC_TAB(CWnd* parent, UINT normal, UINT mouseIn, UINT select, COLORREF mask)
{
	pParent  = parent;
	uNormal  = normal;
	uMouseIn = mouseIn;
	uSelect  = select;
	clrMask  = mask;
}
UITC_TAB& UITC_TAB::operator = (const UITC_TAB* pTab)
{
	pParent  = pTab->pParent;
	uNormal  = pTab->uNormal;
	uMouseIn = pTab->uMouseIn;
	uSelect  = pTab->uSelect;
	clrMask  = pTab->clrMask;

	return *this;
}

UITC_CONTAINER::UITC_CONTAINER()
{
	nIndexTab = -1;
	rcTab = CRect(0, 0, 0, 0);
}


CUiTabCtrl::CUiTabCtrl()
{
	m_nPadding          = 0;
	m_szTab.cx          = 0; 
	m_szTab.cy          = 0;
	m_szArrow.cx        = 0;
	m_szArrow.cy        = 0;
	m_rcArrow[0]        = CRect(0, 0, 0, 0);
	m_rcArrow[1]        = CRect(0, 0, 0, 0);
	m_nContainerSel     = 0;
	m_nContainerMouseIn = -1;
	m_nNumOfContainer   = 0;
	m_nNumOfTabs        =  0;

	m_hCursor    = NULL; 
	m_pLArrow    = NULL;
	m_pRArrow    = NULL;
	m_pContainer = NULL;	
	m_pArray.RemoveAll(); 
}

CUiTabCtrl::~CUiTabCtrl()
{
	m_pArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CUiTabCtrl, CUiBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------
void CUiTabCtrl::SetArrow(UITC_ARROW* pLArrow, UITC_ARROW* pRArrow)
{
	ASSERT(GetSafeHwnd() && pLArrow && pRArrow);

	if(NULL == m_pLArrow && NULL == m_pRArrow)
	{
		m_pLArrow  = new UITC_ARROW;
		m_pRArrow  = new UITC_ARROW;
		*m_pLArrow = *pLArrow;
		*m_pRArrow = *pRArrow;

		UINT uId = m_pLArrow->uNormal;
		uId = (0 == uId) ? m_pLArrow->uMouseIn : uId;
		uId = (0 == uId) ? m_pLArrow->uSelect  : uId;
		uId = (0 == uId) ? m_pLArrow->uDisable : uId;
		ASSERT(uId != 0);

		BITMAP  bmp; 
		CBitmap bitmap;
		bitmap.LoadBitmap(uId);
		bitmap.GetBitmap(&bmp);
		m_szArrow.cx = bmp.bmWidth;
		m_szArrow.cy = bmp.bmHeight;
		bitmap.DeleteObject();
#ifdef _DEBUG
		uId = m_pRArrow->uNormal;
		uId = (0 == uId) ? m_pRArrow->uMouseIn : uId;
		uId = (0 == uId) ? m_pRArrow->uSelect  : uId;
		uId = (0 == uId) ? m_pRArrow->uDisable : uId;
		ASSERT(uId != 0);
		bitmap.LoadBitmap(uId);
		bitmap.GetBitmap(&bmp);
		ASSERT(m_szArrow == CSize(bmp.bmWidth, bmp.bmHeight));
		bitmap.DeleteObject();
		ASSERT(0 == m_szTab.cy || (0 != m_szTab.cy && m_szTab.cy >= m_szArrow.cy));
#endif

		RecalLayout();
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::AddTab(UITC_TAB* pTab)
{
	ASSERT(pTab && pTab->pParent && ::IsWindow(pTab->pParent->GetSafeHwnd()));
	ASSERT(pTab->uNormal != 0 || pTab->uMouseIn != 0 || pTab->uSelect != 0);

	if(0 == m_szTab.cx || 0 == m_szTab.cy)
	{
		UINT uId = pTab->uNormal;
		uId = (0 == uId) ? pTab->uMouseIn : uId;
		uId = (0 == uId) ? pTab->uSelect  : uId;
		ASSERT(uId != 0);

		BITMAP  bmp; 
		CBitmap bitmap;
		bitmap.LoadBitmap(uId);
		bitmap.GetBitmap(&bmp);
		m_szTab.cx = bmp.bmWidth;
		m_szTab.cy = bmp.bmHeight;
		bitmap.DeleteObject();
		ASSERT(m_szTab.cy >= m_szArrow.cy);
	}
	else
	{
#ifdef _DEBUG
		UINT uId = pTab->uNormal;
		uId = (0 == uId) ? pTab->uMouseIn : uId;
		uId = (0 == uId) ? pTab->uSelect  : uId;
		ASSERT(uId != 0);

		BITMAP  bmp; 
		CBitmap bitmap;
		bitmap.LoadBitmap(uId);
		bitmap.GetBitmap(&bmp);
		ASSERT(m_szTab.cx == bmp.bmWidth && m_szTab.cy == bmp.bmHeight);
		bitmap.DeleteObject();
		ASSERT(m_szTab.cy >= m_szArrow.cy);
#endif
	}

	pTab->pParent->ShowWindow(SW_HIDE);
	m_pArray.SetAtGrow(m_nNumOfTabs, new UITC_TAB(pTab->pParent, pTab->uNormal, pTab->uMouseIn, pTab->uSelect, pTab->clrMask));
	m_nNumOfTabs++;

	UITC_TAB* pCurTab = (UITC_TAB*)m_pArray[0]; 
	if(NULL != pCurTab)
	{
		pCurTab->pParent->ShowWindow(SW_SHOW);
	}

	RecalLayout();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::DeleteTab(int nTabIndex)
{
	if(nTabIndex >= m_nNumOfTabs) { return; }

	UITC_TAB* pTab = (UITC_TAB*)m_pArray.GetAt(nTabIndex);
	if(NULL != pTab)
	{
		delete pTab;
	}

	m_nNumOfTabs--;
	m_pArray.RemoveAt(nTabIndex, 1);

	//Existed in container
	int nIndexContainer = -1;
	for(int i=0; i<m_nNumOfContainer; i++)
	{
		if(m_pContainer[i].nIndexTab == nTabIndex)
		{
			nIndexContainer = i;
			m_pContainer[i].nIndexTab = -1;
			break;
		}
	}

	if(m_nContainerSel == nIndexContainer)
	{
		m_nContainerSel = (m_nContainerSel < 1) ? 0 : (m_nContainerSel - 1);
	}
	else
	{
		m_nContainerSel = (m_nContainerSel > nIndexContainer) ? (m_nContainerSel - 1) : m_nContainerSel;
	}

	if(m_nNumOfTabs > 0)
	{
		UITC_TAB* pTab = (UITC_TAB*)m_pArray[m_pContainer[m_nContainerSel].nIndexTab];
		CWnd* pParent = pTab->pParent;
		pParent->ShowWindow(SW_SHOW);
	}

	RecalLayout();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::SetCurTab(int nNewTabSel)
{
	ASSERT(nNewTabSel >= m_nNumOfTabs);

	int nIndexContainer = -1;
	int nOldContainerSel = m_nContainerSel;
	for(int i=0; i<m_nNumOfContainer; i++)
	{
		if(m_pContainer[i].nIndexTab == nNewTabSel)
		{
			nIndexContainer = i; break;
		}
	}

	//Exist in container
	if(nIndexContainer != -1)
	{
		if(m_nContainerSel == nIndexContainer)
		{
			return;
		}

		m_nContainerSel = nIndexContainer;
		if(nIndexContainer == m_nContainerMouseIn)
		{
			m_nContainerMouseIn = -1;
		}
	}
	else
	{
	}

	CWnd* pWndNew = ((UITC_TAB*)m_pArray[nNewTabSel])->pParent;
	CWnd* pWndCur = ((UITC_TAB*)m_pArray[m_pContainer[nOldContainerSel].nIndexTab])->pParent;
	pWndCur->ShowWindow(SW_HIDE);
	pWndNew->ShowWindow(SW_SHOW);

	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_TABCTRL_SELCHANGE, GetDlgCtrlID(), nNewTabSel)) break;
		pParent = pParent->GetParent();
	}

	InvalidateRect(&m_pContainer[m_nContainerSel].rcTab);
	InvalidateRect(&m_pContainer[nOldContainerSel].rcTab);
}
//---------------------------------------------------------------------------------
int CUiTabCtrl::GetCurTab()                       
{ 
	if(NULL != m_pContainer)
	{
		return m_pContainer[m_nContainerSel].nIndexTab;
	}

	return -1; 
}
//---------------------------------------------------------------------------------
int CUiTabCtrl::GetTabCount()                      
{ 
	return m_nNumOfTabs;
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::SetPadding(int nPad)               
{ 
	if(m_nPadding != nPad && nPad >= 0)
	{
		m_nPadding = nPad; 
		RecalLayout();
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::SetCursor(UINT nCursorId)
{
	if(m_hCursor != NULL) 
	{ 
		::DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}
	
	if(nCursorId != -1)
	{
		HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR);
		m_hCursor = (HCURSOR)::LoadImage(hInstResource, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CUiBase::OnLButtonDown(nFlags, point);

	for(int i=0; i<m_nNumOfContainer; i++)
	{
		if(m_pContainer[i].rcTab.PtInRect(point))
		{
			SetCurTab(m_pContainer[i].nIndexTab); 
			break; 
		}
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CUiBase::OnMouseMove(nFlags, point);

	int nContainerMouseIn = -1;
	for(int i=0; i<m_nNumOfContainer; i++)
	{
		if(m_pContainer[i].rcTab.PtInRect(point))
		{
			nContainerMouseIn = i;
			break; 
		}
	}

	if(nContainerMouseIn != m_nContainerSel && nContainerMouseIn != m_nContainerMouseIn)
	{
		int nOld = m_nContainerMouseIn;
		m_nContainerMouseIn = nContainerMouseIn;
		InvalidateRect(&m_pContainer[nOld].rcTab);
		InvalidateRect(&m_pContainer[m_nContainerMouseIn].rcTab);

		//Active WM_MOUSELEAVE message
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE ;
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&trackmouseevent);
	}
}
//---------------------------------------------------------------------------------
LRESULT CUiTabCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_nContainerMouseIn >= 0)
	{
		int nOld = m_nContainerMouseIn;
		m_nContainerMouseIn = -1;
		InvalidateRect(&m_pContainer[nOld].rcTab);
	}

	return 0;
}
//---------------------------------------------------------------------------------
BOOL CUiTabCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_hCursor != NULL)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		for(int i=0; i<m_nNumOfContainer; i++)
		{
			if(m_pContainer[i].rcTab.PtInRect(point))
			{
				::SetCursor(m_hCursor); 
				return TRUE;
			}
		}
	}

	return CUiBase::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnDestroy()
{
    for(int i=0; i<m_nNumOfTabs; i++)
    {
		UITC_TAB *pTab = (UITC_TAB*)m_pArray.GetAt(i);
		if(NULL != pTab)
		{
			delete pTab;
		}
    }

	CUiBase::OnDestroy();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::RecalLayout()
{
	int nTab0 = 0;
	if(m_pContainer != NULL)
	{
		for(int i=0; i<m_nNumOfContainer; i++)
		{
			if(m_pContainer[i].nIndexTab != - 1)
			{
				nTab0 = m_pContainer[i].nIndexTab;
				break;
			}
		}
		delete []m_pContainer;
		m_pContainer = NULL; 
		m_nNumOfContainer = 0;
	}

	if(m_nNumOfTabs <= 0) { return; }

	UITC_TAB* pTab = (UITC_TAB*)m_pArray[0];
	if(NULL == pTab)
	{
		return;
	}

	CRect rcWin;
	pTab->pParent->GetWindowRect(&rcWin);
	ScreenToClient(&rcWin);
	rcWin.bottom = rcWin.bottom + m_szTab.cy;
	SetWindowPos(NULL, 0, 0, rcWin.Width(), rcWin.Height(), SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	CRect rcCli;
	GetClientRect(&rcCli);
	m_nNumOfContainer = (rcCli.Width() - m_szArrow.cx * 2) / (m_szTab.cx + m_nPadding);
	if(m_nNumOfContainer > m_nNumOfTabs)
	{
		m_nNumOfContainer = m_nNumOfTabs;
	}

	if(m_nNumOfContainer > 0)
	{
		m_pContainer = new UITC_CONTAINER[m_nNumOfContainer];
	}
	else
	{
		m_nNumOfContainer = 0;
		return;
	}

	m_nContainerSel = 0;
	for(int i=0; i<m_nNumOfContainer; i++)
	{
		m_pContainer[i].rcTab = CRect((m_szTab.cx + m_nPadding) * i, 0, (m_szTab.cx + m_nPadding) * i + m_szTab.cx, m_szTab.cy);
		m_pContainer[i].nIndexTab = nTab0 + i;
	}

	m_rcArrow[0] = CRect(0, 0, 0, 0);
	m_rcArrow[1] = CRect(0, 0, 0, 0);
	if(m_pLArrow != NULL)
	{
		m_rcArrow[0] = CRect(rcCli.right - m_szArrow.cx * 2, 0, rcCli.right - m_szArrow.cx, m_szArrow.cy);
		m_rcArrow[1] = CRect(rcCli.right - m_szArrow.cx, 0, rcCli.right, m_szArrow.cy);
	}

	for(int i=0; i<m_nNumOfTabs; i++)
	{
		pTab = (UITC_TAB*)m_pArray[i];
		if(NULL != pTab)
		{
			pTab->pParent->SetWindowPos(NULL, 0, m_szTab.cy, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
		}
	}

	Invalidate(FALSE);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawTabs(pDC, rcCli);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::DrawTabs(CDC* pDC, CRect rcCli)
{
	for(int i=0; i<m_nNumOfContainer; i++)
	{
		UINT  uId = 0;
		CRect rcTab = m_pContainer[i].rcTab;
		UITC_TAB* pTab = (UITC_TAB*)m_pArray[m_pContainer[i].nIndexTab];
		if(NULL == pTab)
		{
			continue;
		}

		if(i == m_nContainerSel) { uId = pTab->uSelect; }
		else if( i == m_nContainerMouseIn) { uId = pTab->uMouseIn; }
		else { uId = pTab->uNormal; }

		if(0 == uId) { continue; }

		CDC MemDC; 
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(pDC);
		bitmap.LoadBitmap(uId);
		CBitmap* pOld = MemDC.SelectObject(&bitmap);
		pDC->BitBlt(rcTab.left, rcTab.top, rcTab.Width(), rcTab.Height(), &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOld);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}
}
//---------------------------------------------------------------------------------














/*
TAB_COLOR::TAB_COLOR()
{
	COLORREF clr = ::GetSysColor(COLOR_BTNFACE);

	clrNormal [0] = clr;
	clrNormal [1] = clr;
	clrSelect [0] = clr;
	clrSelect [1] = clr;
	clrMouseIn[0] = clr;
	clrMouseIn[1] = clr;
}

TAB_COLOR& TAB_COLOR::operator = (const TAB_COLOR* pColor)
{
	clrNormal [0] = pColor->clrNormal [0];
	clrNormal [1] = pColor->clrNormal [1];
	clrSelect [0] = pColor->clrSelect [0];
	clrSelect [1] = pColor->clrSelect [1];
	clrMouseIn[0] = pColor->clrMouseIn[0];
	clrMouseIn[1] = pColor->clrMouseIn[1];

	return *this;
}

class CUiTab 
{
public:
	CUiTab(CWnd* pParent, CString strCaption, UINT uIcon = -1)
	{
		Parent	= pParent;
		Caption	= strCaption;
		Icon	= uIcon;
		rect    = CRect(0, 0, 0, 0);
	}

public:
	CWnd*	 Parent;
	CString	 Caption;
	UINT	 Icon;
	CRect	 rect;
};

CUiTabCtrl::CUiTabCtrl()
{
	m_nPadding    =  4;
	m_szTab.cx    = 60; 
	m_szTab.cy    = 20;
	m_nTabSel     =  0;
	m_nNumOfTabs  =  0;
	m_nTabMouseIn = -1;
	m_pFont       = NULL; 
	m_hCursor     = NULL; 
	m_clrBorder   = ::GetSysColor(COLOR_BTNSHADOW);

	m_pArray.RemoveAll(); 
	m_rcAllTabs.SetRectEmpty();

	ModifyCtrlStyle(0, UIBS_BKGND_TRANSPARENT);
}

CUiTabCtrl::~CUiTabCtrl()
{
	m_pArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CUiTabCtrl, CUiBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------
void CUiTabCtrl::AddTab(CWnd *pParent, CString lpMsg, UINT uIcon)
{
	ASSERT_VALID(pParent);
	pParent->ShowWindow(SW_HIDE);
	m_pArray.SetAtGrow(m_nNumOfTabs, new CUiTab(pParent, lpMsg, uIcon));

	m_nTabSel = 0;
	m_nNumOfTabs++;

	CUiTab* pTab = (CUiTab*)m_pArray[m_nTabSel]; 
	if(NULL != pTab)
	{
		pTab->Parent->ShowWindow(SW_SHOW);
	}

	RecalLayout();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::DeleteTab(int nIndex)
{
	if(nIndex >= m_nNumOfTabs) { return; }

	CUiTab* pTab = (CUiTab*)m_pArray.GetAt(nIndex);
	if(NULL != pTab)
	{
		delete pTab;
	}

	m_nNumOfTabs--;
	m_pArray.RemoveAt(nIndex, 1);
	if(m_nNumOfTabs > 0)
	{
		if(m_nTabSel == nIndex)
		{
			m_nTabSel = (m_nTabSel < 1) ? 0 : (m_nTabSel - 1);

			CUiTab* pTab = (CUiTab*)m_pArray[m_nTabSel];
			CWnd* pParent = pTab->Parent;
			ASSERT_VALID(pParent);
			pParent->ShowWindow(SW_SHOW);
		}
		else
		{
			m_nTabSel = (m_nTabSel > nIndex) ? (m_nTabSel - 1) : m_nTabSel;
		}

		RecalLayout();
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::SetCurTab(int nIndex)
{
	if(nIndex >= m_nNumOfTabs || nIndex == m_nTabSel)
	{
		return;
	}

	CWnd* pWndNew = ((CUiTab*)m_pArray[nIndex])->Parent;
	CWnd* pWndCur = ((CUiTab*)m_pArray[m_nTabSel])->Parent;
	ASSERT_VALID(pWndNew);
	ASSERT_VALID(pWndCur);
	pWndCur->ShowWindow(SW_HIDE);
	pWndNew->ShowWindow(SW_SHOW);

	m_nTabSel = nIndex;
	if(nIndex == m_nTabMouseIn)
	{
		m_nTabMouseIn = -1;
	}

	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		pParent->PostMessage(WM_UI_TABCTRL_SELCHANGE, GetDlgCtrlID(), m_nTabSel);
		pParent = pParent->GetParent();
	}

	Invalidate(FALSE);
	UpdateWindow();
}
//---------------------------------------------------------------------------------
int    CUiTabCtrl::GetCurTab()                        { return m_nTabSel; }
int    CUiTabCtrl::GetTabCount()                      { return m_nNumOfTabs; }
void   CUiTabCtrl::SetPadding(int nPad)               { m_nPadding = nPad; RecalLayout(); }
void   CUiTabCtrl::SetTabSize(CSize szTab)            { m_szTab = szTab;RecalLayout(); }
void   CUiTabCtrl::SetBorderColor(COLORREF clrBorder) { m_clrBorder = clrBorder; }
void   CUiTabCtrl::GetTabColor(TAB_COLOR& clrTab)     { clrTab = m_clrTab; }
void   CUiTabCtrl::SetTabColor(TAB_COLOR  clrTab)     { m_clrTab = clrTab; }
void   CUiTabCtrl::SetFont(CFont* pFont)              { m_pFont = pFont; }
CFont* CUiTabCtrl::GetFont()                          { return m_pFont; }
//---------------------------------------------------------------------------------
void CUiTabCtrl::SetCursor(UINT nCursorId)
{
	if(m_hCursor != NULL) 
	{ 
		::DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}
	
	if(nCursorId != -1)
	{
		HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR);
		m_hCursor = (HCURSOR)::LoadImage(hInstResource, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CUiBase::OnLButtonDown(nFlags, point);

	for(int i=0; i<m_nNumOfTabs; i++)
	{
		CUiTab* pTab = (CUiTab*)m_pArray[i];
		if(pTab->rect.PtInRect(point))
		{
            SetCurTab(i); break; 
		}	
	}
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CUiBase::OnMouseMove(nFlags, point);

	int nTabMouseIn = -1;
	for(int i=0; i<m_nNumOfTabs; i++)
	{
		CUiTab* pTab = (CUiTab*)m_pArray[i];
		if(pTab->rect.PtInRect(point))
		{
			nTabMouseIn = i; break; 
		}	
	}

	if(nTabMouseIn != m_nTabSel && nTabMouseIn != m_nTabMouseIn)
	{
		m_nTabMouseIn = nTabMouseIn;
		InvalidateRect(&m_rcAllTabs);

		//Active WM_MOUSELEAVE message
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE ;
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&trackmouseevent);
	}
}
//---------------------------------------------------------------------------------
LRESULT CUiTabCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_nTabMouseIn >= 0)
	{
		m_nTabMouseIn = -1;
		InvalidateRect(&m_rcAllTabs);
	}

	return 0;
}
//---------------------------------------------------------------------------------
BOOL CUiTabCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_hCursor != NULL)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		for(int i=0; i<m_nNumOfTabs; i++)
		{
			CUiTab* pTab = (CUiTab*)m_pArray[i];
			if(pTab->rect.PtInRect(point))
			{
				::SetCursor(m_hCursor); 
				return TRUE;
			}	
		}
	}

	return CUiBase::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::OnDestroy()
{
    for(int i=0; i<m_nNumOfTabs; i++)
    {
		CUiTab *pTab = (CUiTab*)m_pArray.GetAt(i);
		if(NULL != pTab)
		{
			delete pTab;
		}
    }

	CUiBase::OnDestroy();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::RecalLayout()
{
	if(m_nNumOfTabs <= 0) { return; }

	CRect rcCli;
	GetClientRect(&rcCli);

	m_rcAllTabs = rcCli;
	m_rcAllTabs.bottom = m_rcAllTabs.top + m_szTab.cy;

	CRect rcWnd;
	rcWnd = rcCli;
	rcWnd.top = m_rcAllTabs.bottom + 1;
	rcWnd.DeflateRect(1, 1);
	
	for(int i=0; i<m_nNumOfTabs; i++)
	{
		CUiTab* pTab = (CUiTab*)m_pArray[i];
		CWnd* pParent = pTab->Parent;
		ASSERT_VALID(pParent);

		pParent->SetWindowPos(NULL, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

		CRect rcTab = m_rcAllTabs;
		rcTab.left = (m_szTab.cx + m_nPadding) * i;
		rcTab.right = rcTab.left + m_szTab.cx;
		pTab->rect = rcTab;
	}

	Invalidate(FALSE);
	UpdateWindow();
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawBorder(pDC, rcCli);
	DrawTabs  (pDC, rcCli);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::DrawBorder(CDC* pDC, CRect rcCli)
{
	if(m_nNumOfTabs <= 0) { return; }

	for(int i=0; i<m_nNumOfTabs; i++)
	{
		CUiTab* pTab  = (CUiTab*)m_pArray[i];
		CRect rcTab = pTab->rect;
		rcTab.bottom += 2;

		pDC->Draw3dRect(rcTab, m_clrBorder, m_clrBorder);
	}

	CRect rcBorder;
	rcBorder = rcCli;
	rcBorder.top = m_rcAllTabs.bottom + 1;
	pDC->Draw3dRect(rcBorder, m_clrBorder, m_clrBorder);
}
//---------------------------------------------------------------------------------
void CUiTabCtrl::DrawTabs(CDC* pDC, CRect rcCli)
{
	for(int i=0; i<m_nNumOfTabs; i++)
	{	
		CUiTab* pTab = (CUiTab*)m_pArray[i];
		CRect rcTab = pTab->rect;

		rcTab.DeflateRect(1, 1);     //For border
		CRect rcGrad = rcTab;
		rcGrad.bottom += (i == m_nTabSel) ? 3 : 2;

		COLORREF clrL, clrH;
		if(i == m_nTabSel)
		{
			clrL = m_clrTab.clrSelect[0];
			clrH = m_clrTab.clrSelect[1];
		}
		else if(i == m_nTabMouseIn)
		{
			clrL = m_clrTab.clrMouseIn[0];
			clrH = m_clrTab.clrMouseIn[1];
		}
		else
		{
			clrL = m_clrTab.clrNormal[0];
			clrH = m_clrTab.clrNormal[1];
		}

		if(clrL == clrH)
		{
			pDC->FillSolidRect(&rcGrad, clrL);
		}
		else
		{
			CUiGradient M(CSize(rcGrad.Width(), rcGrad.Height()));
			M.PrepareVertical(pDC, clrL, clrH);
			M.Draw(pDC, rcGrad.left, rcGrad.top, 0, 0, rcGrad.Width(), rcGrad.Height(), SRCCOPY);
		}

		//Draw Text
		CFont* pOldFont = NULL; 
		if(NULL != m_pFont && i == m_nTabSel)
		{
			pOldFont = pDC->SelectObject(m_pFont);
		}
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(pTab->Caption, rcTab, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if(NULL != pOldFont)
		{
			pDC->SelectObject(pOldFont);
		}
		pDC->SetBkMode(nOldMode);
	}
}
//---------------------------------------------------------------------------------
*/
