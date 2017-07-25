#include "stdafx.h"
#include "UiComboBox.h"
#include "UiCommon.h"



#define  ST_MOVEIN      0
#define  ST_MOVEOUT     1
#define  ST_MOUSEUP     2
#define  ST_MOUSEDOWN   3


CUiComboBox::CUiComboBox()
{
	m_bOver	   = false;
	m_bEnabled = true;
	m_pDropWnd = NULL;
	m_nState   = ST_MOVEOUT;
	m_uNormal  = 0;
	m_uSelect  = 0;
	m_uMouseIn = 0;
	m_uDisable = 0;
	m_hCursor  = NULL;
	m_clrMask  = CLR_NONE;
	m_clrText  = CLR_NONE;
	m_pFont    = NULL;
	m_nArrowWidth = 0;
	m_dwFlags = DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS;
}

CUiComboBox::~CUiComboBox()
{
	if(NULL != m_pDropWnd)
	{
		delete	m_pDropWnd;
	}
}

BEGIN_MESSAGE_MAP(CUiComboBox, CButton)
	ON_WM_PAINT()
	//ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnSelectionChanged)	
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CUiComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	return; // stop to draw the button style
}
//-------------------------------------------------------------------------------
BOOL CUiComboBox::Create(CRect Rect, CWnd* pParent, UINT uID, DWORD dwStyle)
{
	if(!CButton::Create(_T(""), WS_CHILD | WS_VISIBLE | dwStyle | BS_OWNERDRAW, Rect, pParent, uID))
	{
		return FALSE;
	}

	if(NULL == m_pDropWnd)
	{
		m_pDropWnd = new CListWnd();
		if(!m_pDropWnd->Create(this))
		{
			return FALSE;
		}
	}

	return TRUE;
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetComboBoxBitmap(UINT nNormal, UINT nMouseIn, UINT nSelect, UINT uDisable, COLORREF clrMask)
{
	m_uNormal  = nNormal;
	m_uMouseIn = nMouseIn;
	m_uSelect  = nSelect;
	m_uDisable = uDisable;
	m_clrMask  = clrMask;
	
	UINT uId = nNormal;
	uId = (0 == uId) ? nSelect  : uId;
	uId = (0 == uId) ? nMouseIn : uId;
	uId = (0 == uId) ? uDisable : uId;
	ASSERT(0 != uId);

	BITMAP  bmp;
	CBitmap bitmap;
	bitmap.LoadBitmap(uId);
	bitmap.GetBitmap(&bmp);

	SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	bitmap.DeleteObject();
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetArrowWidth(int nWidth)
{
	if(nWidth >= 0)
	{
		m_nArrowWidth = nWidth;
		Invalidate(FALSE);
	}
}
//-------------------------------------------------------------------------------
void CUiComboBox::Enable(bool bEnable)
{
	if(m_bEnabled != bEnable)
	{
		m_bEnabled = bEnable;
		Invalidate(FALSE);
	}
}
//-------------------------------------------------------------------------------
bool CUiComboBox::IsEnable()
{
	return m_bEnabled;
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetFont(CFont* pFont, COLORREF clrFont)
{
	m_pFont   = pFont;
	m_clrText = clrFont;
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetCursor(UINT nCursorId)
{
	if(m_hCursor != NULL) 
	{ 
		::DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}
	
	if(nCursorId != -1)
	{
		m_hCursor = (HCURSOR)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR), 
			                             MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
	}
}
//-------------------------------------------------------------------------------
BOOL CUiComboBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_hCursor != NULL && m_bEnabled)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}	

	return CButton::OnSetCursor(pWnd, nHitTest, message);
}
//-------------------------------------------------------------------------------
CDropList* CUiComboBox::GetDropList()
{
	return m_pDropWnd->m_pDropList;
}
//-------------------------------------------------------------------------------
int	CUiComboBox::AddString(LPCTSTR lpszItem)
{
	ASSERT(m_pDropWnd);
	return m_pDropWnd->m_pDropList->AddString(lpszItem);
}
//-------------------------------------------------------------------------------
int	CUiComboBox::AddString(LPCTSTR lpszItem, int GroupPos, COLORREF crTextColor, COLORREF crTextHighlightColor)
{
	ASSERT(m_pDropWnd);
	return m_pDropWnd->m_pDropList->AddString(lpszItem, GroupPos, crTextColor, crTextHighlightColor);
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetString(int nIndex, CString sText)
{
	m_pDropWnd->m_pDropList->SetItemText(nIndex, sText);
}
//-------------------------------------------------------------------------------
int	CUiComboBox::DeleteString(UINT nIndex)
{
	ASSERT(m_pDropWnd);
	SetWindowText(_T(""));
	int nRet = m_pDropWnd->m_pDropList->DeleteString(nIndex);
	Invalidate(FALSE);
	return nRet;
}
//-------------------------------------------------------------------------------
void CUiComboBox::ResetContent()
{
	ASSERT(m_pDropWnd);
	m_pDropWnd->m_pDropList->ResetContent();
	SetWindowText(_T(""));
	Invalidate(FALSE);
}
//-------------------------------------------------------------------------------
int CUiComboBox::GetCurSel()
 {
	ASSERT(m_pDropWnd);
	return m_pDropWnd->m_pDropList->GetPreviousSelection();
}
//-------------------------------------------------------------------------------
void CUiComboBox::SetCurSel(int nSel)
{
	ASSERT(m_pDropWnd);
	if(nSel >= 0 && nSel < GetCount())
	{
		CString csText;
		m_pDropWnd->m_pDropList->GetText(nSel, csText);
		SetWindowText(csText);
		m_pDropWnd->m_pDropList->SetPreviousSelection(nSel);
		m_pDropWnd->m_pDropList->Invalidate(FALSE);
		m_pDropWnd->m_pDropList->UpdateWindow();
		m_pDropWnd->m_pDropList->Invalidate(FALSE);
	}
	Invalidate(FALSE);
}
//-------------------------------------------------------------------------------
void CUiComboBox::ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd) 
{
	m_dwFlags = DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS;
	if(dwRemove & ST_TOP)        { m_dwFlags = m_dwFlags & ~DT_TOP; }
	if(dwRemove & ST_LEFT)       { m_dwFlags = m_dwFlags & ~DT_LEFT; }
	if(dwRemove & ST_CENTER)     { m_dwFlags = m_dwFlags & ~DT_CENTER; }
	if(dwRemove & ST_RIGHT)      { m_dwFlags = m_dwFlags & ~DT_RIGHT; }
	if(dwRemove & ST_VCENTER)    { m_dwFlags = m_dwFlags & ~DT_VCENTER; }
	if(dwRemove & ST_BOTTOM)     { m_dwFlags = m_dwFlags & ~DT_BOTTOM; }
	if(dwRemove & ST_SINGLELINE) { m_dwFlags = m_dwFlags & ~DT_SINGLELINE; }

	if(dwAdd & ST_TOP)        { m_dwFlags = m_dwFlags | DT_TOP; }
	if(dwAdd & ST_LEFT)       { m_dwFlags = m_dwFlags | DT_LEFT; }
	if(dwAdd & ST_CENTER)     { m_dwFlags = m_dwFlags | DT_CENTER; }
	if(dwAdd & ST_RIGHT)      { m_dwFlags = m_dwFlags | DT_RIGHT; }
	if(dwAdd & ST_VCENTER)    { m_dwFlags = m_dwFlags | DT_VCENTER; }
	if(dwAdd & ST_BOTTOM)     { m_dwFlags = m_dwFlags | DT_BOTTOM; }
	if(dwAdd & ST_SINGLELINE) { m_dwFlags = m_dwFlags | DT_SINGLELINE; }

	Invalidate(FALSE);
}
//-------------------------------------------------------------------------------
int CUiComboBox::GetCount()
{
	ASSERT(m_pDropWnd);
	return m_pDropWnd->m_pDropList->GetCount();
}
//-------------------------------------------------------------------------------
BOOL CUiComboBox::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnPaint()
{
	CPaintDC dc(this);

	UINT uId = m_uNormal;
	if(!m_bEnabled)
	{
		uId = (0 == m_uDisable) ? uId : m_uDisable;
	}
	else
	{
		switch(m_nState)
		{
		case ST_MOVEOUT:    uId = m_uNormal;  break;
		case ST_MOVEIN:     uId = m_uMouseIn; break;
		case ST_MOUSEUP:    uId = m_uMouseIn; break;
		case ST_MOUSEDOWN:  uId = m_uSelect;  break;
		}
	}

	CString string;
	GetWindowText(string.GetBuffer(MAX_PATH), MAX_PATH);
	string.ReleaseBuffer();

	CRect rcCli;
	GetClientRect(&rcCli);

	CRect rcT(rcCli);
	rcT.left  += 4;
	rcT.right -= m_nArrowWidth;

	CFont* pOldFont = NULL; 

	if(0 != uId)
	{
		CDC MemDC;
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(&dc);
		bitmap.LoadBitmap(uId);
		CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);

		if(_T("") != string)
		{	
			if(NULL != m_pFont)
			{
				pOldFont = MemDC.SelectObject(m_pFont);
			}
			if(m_clrText != CLR_NONE)
			{
				if (m_bEnabled)
				{
					MemDC.SetTextColor(m_clrText);
				}
				else
				{
					MemDC.SetTextColor(RGB(108, 108, 108));
				}
			}
			MemDC.SetBkMode(TRANSPARENT);

			MemDC.DrawText(string, string.GetLength(), rcT, m_dwFlags);
		}

		if(m_clrMask == CLR_NONE)
		{
			dc.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, 0, 0, SRCCOPY);
		}
		else
		{
			dc.TransparentBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), m_clrMask);
		}

		if(NULL != pOldFont)
		{
			MemDC.SelectObject(pOldFont);
		}
		MemDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}
	else
	{
		if(_T("") != string)
		{	
			if(NULL != m_pFont)
			{
				pOldFont = dc.SelectObject(m_pFont);
			}
			if(m_clrText != CLR_NONE)
			{
				dc.SetTextColor(m_clrText);
			}
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(string, string.GetLength(), rcT, m_dwFlags);
			if(NULL != pOldFont)
			{
				dc.SelectObject(pOldFont);
			}
		}
	}
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	m_nState = ST_MOVEIN;

	//Active WM_MOUSELEAVE message
	TRACKMOUSEEVENT trackmouseevent;
	trackmouseevent.cbSize = sizeof(trackmouseevent);
	trackmouseevent.dwFlags     = TME_LEAVE;
	trackmouseevent.hwndTrack   = GetSafeHwnd();
	trackmouseevent.dwHoverTime = HOVER_DEFAULT;
	_TrackMouseEvent(&trackmouseevent);

	if(!m_bOver && !m_pDropWnd->IsWindowVisible())
	{
		SetCapture();
	}

	CRect rcWin;
	GetClientRect(rcWin);
	ClientToScreen(rcWin);
	ClientToScreen(&point);

	if(rcWin.PtInRect(point))
	{
		if(!m_bOver && !m_pDropWnd->IsWindowVisible())
		{
			m_bOver = true;	
			RedrawWindow();
		}
	}
	else
	{
		if(m_pDropWnd->IsWindowVisible())
		{
			m_pDropWnd->GetWindowRect(rcWin);
			if(!rcWin.PtInRect(point))
			{
				m_pDropWnd->ShowWindow(SW_HIDE);
			}
		}
		else
		{
			m_bOver = false;
			RedrawWindow();
			ReleaseCapture();
		}
	}

	CButton::OnMouseMove(nFlags, point);
}
//-------------------------------------------------------------------------------
LRESULT CUiComboBox::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_bEnabled)
	{
		m_nState = ST_MOVEOUT;
		Invalidate(FALSE);
	}

	return 0;
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	m_nState = ST_MOUSEUP;
	Invalidate(FALSE);

	CButton::OnLButtonUp(nFlags, point);
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	m_nState = ST_MOUSEDOWN;

	m_bOver = false;
	if(m_pDropWnd->IsWindowVisible())
	{
		CRect rcWin;
		m_pDropWnd->GetWindowRect(&rcWin);
		MapWindowPoints(GetDesktopWindow(), &point, 2);
		if(!rcWin.PtInRect(point))
		{
			m_pDropWnd->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		DisplayList();
	}

	CButton::OnLButtonDown(nFlags, point);
}
//-------------------------------------------------------------------------------
void CUiComboBox::DisplayList()
{
	CRect rcWin;
	GetClientRect(&rcWin);
	MapWindowPoints(GetDesktopWindow(), rcWin);

	int nHeight    = m_pDropWnd->m_pDropList->GetItemHeight(0);
	int nCount     = m_pDropWnd->m_pDropList->GetCount() > 10 ? 10 : m_pDropWnd->m_pDropList->GetCount();
	int nListHight = (0 == nCount) ? 0 : nCount * nHeight;
	
	CRect rcDropWnd;
	m_pDropWnd->GetWindowRect(&rcDropWnd);

	if(rcDropWnd.Height() != nListHight)
	{
		CRect rcMove(rcWin.left, rcWin.bottom - 1, rcWin.left + rcWin.Width(), rcWin.bottom + nListHight);
		m_pDropWnd->MoveWindow(rcMove, FALSE);

		m_pDropWnd->m_pDropList->GetWindowRect(rcDropWnd);
		if(rcDropWnd.bottom != rcMove.bottom)
		{
			rcDropWnd.bottom = rcMove.bottom;
			rcDropWnd.InflateRect(1, 1);
			m_pDropWnd->MoveWindow(rcDropWnd);
		}
	}

	m_pDropWnd->ShowWindow(SW_SHOWNORMAL);
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	if(m_pDropWnd->IsWindowVisible())
	{
		m_pDropWnd->m_pDropList->SetFocus();
	}	
}
//-------------------------------------------------------------------------------
LONG CUiComboBox::OnSelectionChanged(UINT wParam, LONG lParam)
{
	CString csText;
	m_pDropWnd->m_pDropList->GetText(wParam, csText);
	SetWindowText(csText);
	RedrawWindow();	

	m_pDropWnd->m_pDropList->SetPreviousSelection(wParam);

	CWnd* pParent = GetParent();
	while(pParent != NULL)
	{
		if(pParent->SendMessage(WM_UI_COMBOBOX_SELCHANGED, GetDlgCtrlID(), wParam)) break;
		pParent = pParent->GetParent();
	}

	return 1;
}
//-------------------------------------------------------------------------------
void CUiComboBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CButton::OnLButtonDblClk(nFlags, point);
}
//-------------------------------------------------------------------------------







//***************************************************************************
// CListWnd
//***************************************************************************

CListWnd::CListWnd()
{
	m_pDropList = NULL;
}

CListWnd::~CListWnd()
{
	if(NULL != m_pDropList) delete m_pDropList;
}

BEGIN_MESSAGE_MAP(CListWnd, CWnd)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(WM_UI_COMBOBOX_LIST, OnSelectionChange)
END_MESSAGE_MAP()

//-------------------------------------------------------------------------------
BOOL CListWnd::Create(CWnd* pParentWnd)
{
	ASSERT(pParentWnd);
	CString csWndClassName = AfxRegisterWndClass(CS_SAVEBITS, NULL, NULL, NULL);
	if(!CreateEx(WS_EX_TOPMOST, csWndClassName, NULL, WS_BORDER | WS_POPUP, 0, 0, 1, 1, pParentWnd->GetSafeHwnd(), NULL, NULL))
	{
		return FALSE;
	}

	m_pDropList = new CDropList();
	ASSERT(m_pDropList);
	if(!m_pDropList->Create(WS_CHILD | WS_VSCROLL | WS_VISIBLE | LBS_NOTIFY | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT, CRect(0,0,0,0), this, WM_UI_COMBOBOX_LIST))
	{
		return FALSE;
	}

	m_pParent = pParentWnd;

	return TRUE;
}
//-------------------------------------------------------------------------------
void CListWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if(NULL != m_pDropList)
	{
		CRect rcWin;
		GetClientRect(rcWin);
		m_pDropList->MoveWindow(rcWin);
	}
}
//-------------------------------------------------------------------------------
void CListWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
}
//-------------------------------------------------------------------------------
void CListWnd::OnSelectionChange()
{
	// Did they pick a Header?
	LISTITEM* pItem = m_pDropList->GetCurListItem();
	if(pItem->btHeader)
	{
		return;
	}

	ShowWindow(SW_HIDE);		

	// Is the mouse still over this window
	CRect rcWin;
	POINT pt;
	GetWindowRect(rcWin);
	GetCursorPos(&pt);
	if(!rcWin.PtInRect(pt))
	{
		// Set back to the Selection before this one
		m_pDropList->SetCurSel(m_pDropList->GetPreviousSelection());
		return;
	}
	
	m_pParent->PostMessage(WM_UI_COMBOBOX_SELCHANGED, m_pDropList->GetCurSel(), 0);
}
//-------------------------------------------------------------------------------


//***************************************************************************
// CDropList
//***************************************************************************

CDropList::CDropList()
{
	m_nPrevSelection			= -1;
	m_nGroupCount				= 0;
	m_pHeaderFont				= NULL;
	m_pTextFont					= NULL;
	m_pBkBrush					= NULL;
	m_pBkHighlightBrush			= NULL;
	m_pBkPen					= NULL;
}

CDropList::~CDropList()
{
	if(m_pHeaderFont) delete m_pHeaderFont;
	if(m_pBkBrush) delete m_pBkBrush;
	if(m_pBkHighlightBrush) delete m_pBkHighlightBrush;
	if(m_pBkPen) delete m_pBkPen;

	// Clear out the Items
	ClearItems();
}

void CDropList::ClearItems()
{
	POSITION Pos = m_ItemList.GetHeadPosition();
	while(Pos)
	{
		m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);
		delete m_pCurListItem;
	}
	m_ItemList.RemoveAll();
	m_nGroupCount = 0;
	m_nPrevSelection = -1;
}

BEGIN_MESSAGE_MAP(CDropList, CListBox)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
END_MESSAGE_MAP()

//-------------------------------------------------------------------------------
int CDropList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pBkBrush	= new CBrush(RGB(255,255,255));
	m_pBkPen	= new CPen(PS_SOLID, 1, RGB(255,255,255));

	//m_pBkHighlightBrush = new CBrush(RGB(247,247,239));
	m_pBkHighlightBrush = new CBrush(RGB(200, 200, 200));
	SetItemHeight(-1, 22);
	return 0;
}
//-------------------------------------------------------------------------------
void CDropList::OnSize(UINT nType, int cx, int cy) 
{
	CListBox::OnSize(nType, cx, cy);
	GetClientRect(m_WindowRect);		
}
//-------------------------------------------------------------------------------
void CDropList::OnKillFocus(CWnd* pNewWnd) 
{
	CListBox::OnKillFocus(pNewWnd);
	GetParent()->ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------------------------
void CDropList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Make sure its a valid item
	if(lpDrawItemStruct->itemID == LB_ERR )
		return;
     
  	// Obtain the text for this item
	m_csText.Empty();
	GetText(lpDrawItemStruct->itemID, m_csText);
	
	// Set the current List item
	m_pCurListItem = (LISTITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(lpDrawItemStruct->itemID));

	// Get the drawing DC
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	// Obtain the Item Rect
	CRect ItemRect(lpDrawItemStruct->rcItem);
	ItemRect.InflateRect(1,1);
	
    // Draw This item
	DrawItem(pDC, ItemRect, lpDrawItemStruct->itemState & ODS_SELECTED);
}
//-------------------------------------------------------------------------------
void CDropList::DrawItem(CDC* pDC, CRect ItemRect, BOOL bSelected)
{
	////////////////////////////////////////////////
	// Draw the Background Rectangle
	pDC->SelectObject(m_pBkPen);
	pDC->SelectObject(m_pBkBrush);
	pDC->SetTextColor(m_pCurListItem->crTextColor);
	if(bSelected && !m_pCurListItem->btHeader)
	{
		pDC->SelectObject(m_pBkHighlightBrush);
		pDC->SetTextColor(m_pCurListItem->crTextHighlightColor);
	}
	pDC->Rectangle(ItemRect);

	////////////////////////////////////////////////
	// Draw the Text - Is this a header?
	pDC->SetBkMode(TRANSPARENT);
	ItemRect.left = 4;
	ItemRect.right -= 5;
	if(m_pCurListItem->btHeader)
	{
		pDC->SelectObject(m_pHeaderFont);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_CALCRECT);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);

		// Create a pen based on the text color
		CPen LinePen(PS_SOLID, 1, m_pCurListItem->crTextColor);
		pDC->SelectObject(LinePen);

		// Draw a line
		pDC->MoveTo(ItemRect.right + 2, ItemRect.top + (ItemRect.Height() / 2));
		pDC->LineTo(m_WindowRect.right - 2, ItemRect.top + (ItemRect.Height() / 2));
	}
	else
	{
		pDC->SelectObject(m_pTextFont);
		pDC->DrawText(m_csText, m_csText.GetLength(), ItemRect, DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_END_ELLIPSIS);
	}
}
//-------------------------------------------------------------------------------
void CDropList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
}
//-------------------------------------------------------------------------------
HBRUSH CDropList::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return (HBRUSH)(m_pBkBrush->GetSafeHandle() );
}
//-------------------------------------------------------------------------------
void CDropList::SetPreviousSelection(int nPrevSelection)
{
	m_nPrevSelection = nPrevSelection;
	SetCurSel(m_nPrevSelection);
}
//-------------------------------------------------------------------------------
void CDropList::SetItemText(int nIndex, CString sText)
{
	int nCount = GetCount();
	for (int i = nIndex; i < nCount; i++)
	{
		COLORREF crTextColor = ((LISTITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(nIndex)))->crTextColor;
		COLORREF crTextHighlightColor = ((LISTITEM*)m_ItemList.GetAt(m_ItemList.FindIndex(nIndex)))->crTextHighlightColor;

		DeleteString(nIndex);
		AddString(sText, 0, crTextColor, crTextHighlightColor);
		GetText(nIndex, sText);
	}
}
//-------------------------------------------------------------------------------
// Overrides
int CDropList::AddString(LPCTSTR lpszItem)
{
	// Create a new Item
	m_pCurListItem = new LISTITEM;
	m_pCurListItem->crTextColor = RGB(0,0,0);
	m_pCurListItem->crTextHighlightColor = RGB(0,0,0);
	m_pCurListItem->btHeader = 0;

	// Should we create a Group Item?
	if(!m_ItemList.GetCount())
	{
		m_nGroupCount++;
	}
	else if(m_ItemList.GetCount() == 1) 
	{
		SetCurSel(m_nPrevSelection);
	}

	// Add this item to the list box (always at the top)
	return AddToList(1, lpszItem);
}
//-------------------------------------------------------------------------------
int CDropList::AddString(LPCTSTR lpszItem, int GroupPos, COLORREF crTextColor, COLORREF crTextHighlightColor)
{
	// Is this a valid group
	if(GroupPos > m_nGroupCount + 1)
		return -1;
	
	// Create a new Item
	m_pCurListItem = new LISTITEM;
	m_pCurListItem->crTextColor = crTextColor;
	m_pCurListItem->crTextHighlightColor = crTextHighlightColor;
	m_pCurListItem->btHeader = 0;

	// Is this a new group header
	if(GroupPos == m_nGroupCount + 1)
	{
		m_nGroupCount++;
		m_pCurListItem->btHeader = 1;
	}
	
	// Add this item to the list box (always at the top)
	return AddToList(GroupPos, lpszItem);
}
//-------------------------------------------------------------------------------
int CDropList::AddToList(int nGroup, CString csText)
{
	/////////////////////////////////////////////////////
	// If this item is a header then add it to the end
	if(m_pCurListItem->btHeader)
	{
		m_ItemList.AddTail(m_pCurListItem);
		return CListBox::AddString(csText);
	}
	
	/////////////////////////////////////////////////////
	// Loop through the list items until you find the correct group
	int nListBoxItem = 0, nCurGroup = 1;	
	LISTITEM* pItem;
	POSITION Pos = m_ItemList.GetHeadPosition();
	POSITION OldPos = Pos;
	while(Pos)
	{
		// Get the item and check for a header
		pItem = (LISTITEM*)m_ItemList.GetNext(Pos);
		if(pItem->btHeader)
			nCurGroup++;

		// Is this the group?
		nListBoxItem++;
		if(nCurGroup == nGroup)
			break;
	}

	/////////////////////////////////////////////////////
	// If this was the first group - then force a heading
	if(nGroup == 1)
	{
		Pos = OldPos;
		nListBoxItem = 0;
	}
	else
		OldPos = Pos;

	/////////////////////////////////////////////////////
	// Continue looping from this position look for the correct spot
	CString csCurText;
	while(Pos)
	{
		// Get the Next Item
		OldPos = Pos;
		pItem = (LISTITEM*)m_ItemList.GetNext(Pos);

		// Get the Text For this item
		GetText(nListBoxItem, csCurText);

		// Have we hit a header?
		/*  NOTE: SORTING STRING HERE!!!  
		if(csText.CompareNoCase(csCurText) < 0)
		{
			m_ItemList.InsertBefore(OldPos, m_pCurListItem);
			return InsertString(nListBoxItem, csText);
		}
		*/
		nListBoxItem++;
	}

	/////////////////////////////////////////////////////
	// If we get here then we never found it so add it to the end
	m_ItemList.AddTail(m_pCurListItem);
	return CListBox::AddString(csText);
}
//-------------------------------------------------------------------------------
int CDropList::DeleteString(UINT nIndex)
{
	// Is this a valid item?
	if(nIndex >= (UINT)GetCount())
		return -1;
	
	// Find this item in our list
	POSITION Pos = m_ItemList.FindIndex(nIndex);
	POSITION LastPos = Pos;
	m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);

	// Is this a header?
	if(m_pCurListItem->btHeader)
	{
		// have to remove all items until the end or next header
		m_nGroupCount--; // Reduce the Group Count
		while(Pos)
		{
			// Remove this item
			delete m_pCurListItem;
			m_ItemList.RemoveAt(LastPos);
			CListBox::DeleteString(nIndex);

			// Get the Next Element
			LastPos = Pos;
			m_pCurListItem = (LISTITEM*)m_ItemList.GetNext(Pos);
			if(m_pCurListItem->btHeader)
				break;
		}
	}

	// Deletes a Single item and Last item in the list in a group delete
	if(!m_pCurListItem->btHeader || LastPos && !Pos)
	{
		// Remove only this item
		delete m_pCurListItem;
		m_ItemList.RemoveAt(LastPos);
		return CListBox::DeleteString(nIndex);
	}

	return 1;
}
//-------------------------------------------------------------------------------
void CDropList::ResetContent()
{
	// Clear the list
	ClearItems();

	CListBox::ResetContent();
}
//-------------------------------------------------------------------------------
void CDropList::SetBkColor(COLORREF crColor)
{
	if(m_pBkBrush) delete m_pBkBrush;
	if(m_pBkPen)	delete m_pBkPen;
	m_pBkPen	= new CPen(PS_SOLID, 1, crColor);
	m_pBkBrush	= new CBrush(crColor);	
	RedrawWindow();
}
//-------------------------------------------------------------------------------
void CDropList::SetHighlightBkColor(COLORREF crColor)
{
	if(m_pBkHighlightBrush) delete m_pBkHighlightBrush;
	m_pBkHighlightBrush = new CBrush(crColor);
	RedrawWindow();
}
//-------------------------------------------------------------------------------
void CDropList::SetFont(CFont* pFont, BOOL bRedraw)
{
	// Can only set the font once (sorry - no resize on the fly)
	if(m_pTextFont)
		return;
	m_pTextFont = pFont;
	CWnd::SetFont(pFont);

	// Figure out the text size
	LOGFONT lpLogFont;
	m_pTextFont->GetLogFont(&lpLogFont);

	// Create the heading font with the bold attribute
	lpLogFont.lfWeight = FW_BOLD;
	m_pHeaderFont = new CFont();
	m_pHeaderFont->CreateFontIndirect(&lpLogFont);

	// Set the Row height
	SetItemHeight(-1,lpLogFont.lfHeight);
}
