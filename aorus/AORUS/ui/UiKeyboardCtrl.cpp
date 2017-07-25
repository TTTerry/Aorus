#include "stdafx.h"
#include "UiKeyboardCtrl.h"
#include "UiCommon.h"

UIKB_RECT::UIKB_RECT()
{
	uItemId = 0;	 
	rect = CRect(0, 0, 0, 0);
	bSel = false;
}

UIKB_RECT::UIKB_RECT(DWORD id, CRect rc, bool sel)
{
	uItemId = id;	 
	rect = rc;
	bSel = false;
}

UIKB_RECT& UIKB_RECT::operator = (const UIKB_RECT* pKbRect)
{
	uItemId = pKbRect->uItemId;	 
	rect = pKbRect->rect;
	bSel = pKbRect->bSel;;

	return *this;
}

UI_KEYBOARD::UI_KEYBOARD()
{
	pParent    = NULL;
	uId        = 0;
	rect       = CRect(0, 0, 0, 0);
	uBkBitmap  = 0;
	uHlBitmap  = 0;
	clrMask    = CLR_NONE;
	clrRect    = CLR_NONE;
}
UI_KEYBOARD::UI_KEYBOARD(CWnd* parent, UINT id, CRect rcWin, UINT bkbmp, UINT hlbmp, COLORREF clrc, COLORREF mask)
{
	pParent    = parent;
	uId        = id;
	rect       = rcWin;
	uBkBitmap  = bkbmp;
	uHlBitmap  = hlbmp;
	clrMask    = mask;
	clrRect    = clrc;
}
UI_KEYBOARD& UI_KEYBOARD::operator = (const UI_KEYBOARD* pStatic)
{
	pParent    = pStatic->pParent;
	uId        = pStatic->uId;
	rect       = pStatic->rect;
	uBkBitmap  = pStatic->uBkBitmap;
	uHlBitmap  = pStatic->uHlBitmap;
	clrMask    = pStatic->clrMask;
	clrRect    = pStatic->clrRect;

	return *this;
}

CUiKeyboardCtrl::CUiKeyboardCtrl()
{
	m_bEnabled     = true;
	m_bDrop		   = false;
	m_bSingle	   = false;
	m_nItemSel     =  0;
	m_nNumOfItems  =  0;
	m_nItemMouseIn = -1;
	m_uHlBmpId	   =  0;
	m_uNormal	   =  0;
	m_startPt	   = CPoint(0, 0);
	m_curPt		   = CPoint(0, 0);
	m_clrRect	   = CLR_NONE;
	m_clrMask	   = CLR_NONE;

	m_pArray.RemoveAll();

	m_hCursor = NULL; 
}

CUiKeyboardCtrl::~CUiKeyboardCtrl()
{
	//m_pArray.RemoveAll();
	//m_pLastArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CUiKeyboardCtrl, CUiBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


BOOL CUiKeyboardCtrl::PreTranslateMessage(MSG* pMsg)
{

	return CUiBase::PreTranslateMessage(pMsg);
}

//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::Enable(bool bEnable)
{
	if(m_bEnabled != bEnable)
	{
		m_bEnabled = bEnable;
		Invalidate(FALSE);
	}
}
//---------------------------------------------------------------------------------
bool CUiKeyboardCtrl::IsEnable()
{
	return m_bEnabled;
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::SetCursor(UINT nCursorId)
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
void CUiKeyboardCtrl::CreateKeyboard(UI_KEYBOARD uiKeyboard)
{
	Create(uiKeyboard.pParent, uiKeyboard.uId, uiKeyboard.rect, WS_CHILD|WS_VISIBLE); 
	if(uiKeyboard.uBkBitmap != 0)
	{
		SetKeyboardBitmap(uiKeyboard.uBkBitmap, uiKeyboard.clrMask); 
	}
	m_uHlBmpId = uiKeyboard.uHlBitmap;
	m_clrRect = uiKeyboard.clrRect;
}


void CUiKeyboardCtrl::ResetKeyboard(UI_KEYBOARD uiKeyboard)
{
	if(uiKeyboard.uBkBitmap != 0)
	{
		SetKeyboardBitmap(uiKeyboard.uBkBitmap, uiKeyboard.clrMask); 
	}
	m_uHlBmpId = uiKeyboard.uHlBitmap;
	m_clrRect = uiKeyboard.clrRect;
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::SetKeyboardBitmap(UINT nNormal, COLORREF clrMask)
{
	m_uNormal = nNormal;
	m_clrMask = clrMask;
	ASSERT(m_uNormal != 0);

	BITMAP  bmp;
	CBitmap bitmap;
	bitmap.LoadBitmap(m_uNormal);
	bitmap.GetBitmap(&bmp);

	SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	bitmap.DeleteObject();

	Invalidate(FALSE);
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::AddItem(UIKB_RECT* pItem)
{
	ASSERT(pItem != NULL);

	UIKB_RECT* pNew = new UIKB_RECT;
	
	*pNew = *pItem;

	m_pArray.SetAtGrow(m_nNumOfItems, pNew);

	m_nItemSel = 0;
	m_nNumOfItems++;

	RecalLayout();
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::DeleteItem(int nIndex)
{
	if(nIndex >= m_nNumOfItems) { return; }

	UIKB_RECT* pItem = (UIKB_RECT*)m_pArray.GetAt(nIndex);
	if(NULL != pItem)
	{
		delete pItem;
	}

	m_nNumOfItems--;
	m_pArray.RemoveAt(nIndex, 1);
	if(m_nNumOfItems > 0)
	{
		if(m_nItemSel != nIndex && m_nItemSel > nIndex)
		{
			m_nItemSel -= 1;
		}
		else if(m_nItemSel == nIndex && m_nItemSel > 0)
		{
			m_nItemSel -= 1;
		}

		RecalLayout();
	}
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::ResetAllItemStatus()
{
	for(int i=0; i<m_nNumOfItems; i++)
	{
		UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];
		pItem->bSel = false;
	}
	Invalidate(FALSE);
}
//---------------------------------------------------------------------------------
int CUiKeyboardCtrl::GetAllItemStatus(bool nStatus[], int nCount)
{
	for(int i=0; i<m_nNumOfItems && nCount > 0; i++)
	{
		UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];
		nStatus[i] = pItem->bSel;
	}
	return m_nNumOfItems;
}
//---------------------------------------------------------------------------------
int CUiKeyboardCtrl::GetAllSelectItem(int nStatus[], int& nCount)
{
	int n = 0;
	for(int i=0; i<m_nNumOfItems && nCount > n; i++)
	{
		UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];
		if(pItem->bSel) nStatus[n++] = pItem->uItemId;
	}
	return nCount = n;
}
//---------------------------------------------------------------------------------
bool CUiKeyboardCtrl::GetItemStatus(int nIndex)
{
	if(nIndex >= m_nNumOfItems) return false;
	UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[nIndex];
	return pItem->bSel;
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::SetItemStatus(int nIndex, bool bStatus)
{
	if(nIndex >= m_nNumOfItems) return;
	UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[nIndex];
	pItem->bSel = bStatus;
	Invalidate(FALSE);
}
//---------------------------------------------------------------------------------
int  CUiKeyboardCtrl::GetItemCount()            
{ 
	return m_nNumOfItems; 
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	m_startPt = point; //记录开始点
	m_curPt   = point; 
	m_bDrop	  = !m_bSingle;
	if(m_bDrop) SetCapture();

	m_pLastArray.RemoveAll();
	bool bDoubleSel = GetAsyncKeyState(VK_CONTROL);
	for(int i=0; i<m_nNumOfItems; i++)
	{
		UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];
		UIKB_RECT* pNewItem = new UIKB_RECT;
		if(!bDoubleSel) pItem->bSel = false;
		*pNewItem = *pItem;
		m_pLastArray.SetAtGrow(i, pNewItem);
		if(pItem->rect.PtInRect(point))
		{
			pItem->bSel = m_bSingle || !pNewItem->bSel;
			CWnd* pParent = GetParent();
			while(NULL != pParent)
			{
				if(pParent->SendMessage(WM_UI_KEYBOARD_SELCHANGE, GetDlgCtrlID(), pItem->uItemId)) break;
				pParent = pParent->GetParent();
			}
		}	
		else
		{
			if(m_bSingle) pItem->bSel = false;
		}
	}
	Invalidate(FALSE);

	if(!m_bSingle) OnMouseMove(nFlags, point);

	CWnd::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	if(m_bDrop)
	{
		m_bDrop = false;
		ReleaseCapture();
		Invalidate(FALSE);
	}

	CWnd::OnLButtonUp(nFlags, point);
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	if (m_bDrop)
	{
		m_curPt = point;
		int nLeft   = m_startPt.x < m_curPt.x ? m_startPt.x : m_curPt.x;
		int nRight  = m_startPt.x > m_curPt.x ? m_startPt.x : m_curPt.x;
		int nTop    = m_startPt.y < m_curPt.y ? m_startPt.y : m_curPt.y;
		int nBottom = m_startPt.y > m_curPt.y ? m_startPt.y : m_curPt.y;

		for(int i=0; i<m_nNumOfItems; i++)
		{
			UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];
			UIKB_RECT* pLast = (UIKB_RECT*)m_pLastArray[i];
			if(RectInRect(CRect(nLeft, nTop, nRight, nBottom), pItem->rect))
			{
				pItem->bSel = !pLast->bSel;
			}
			else
				pItem->bSel = pLast->bSel;

		}
		Invalidate(FALSE);
	}

	CUiBase::OnMouseMove(nFlags, point);

}
//---------------------------------------------------------------------------------
BOOL CUiKeyboardCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_hCursor != NULL && m_bEnabled)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		for(int i=0; i<m_nNumOfItems; i++)
		{
			UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
			if(m_hCursor != NULL && pItem->rect.PtInRect(point))
			{
				::SetCursor(m_hCursor); 
				return TRUE;
			}	
		}
	}

	return CUiBase::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::OnDestroy()
{
  //  for(int i=0; i<m_nNumOfItems; i++)
  //  {
		//UIPC_ITEM *pItem = (UIPC_ITEM*)m_pArray.GetAt(i);
		//if(NULL != pItem)
		//{
		//	delete pItem;
		//}
  //  }

	CUiBase::OnDestroy();
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::Draw(CDC* pDC, CRect rcCli)
{
	if(m_uNormal != 0)
	{
		CDC MemDC;
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(pDC);
		bitmap.LoadBitmap(m_uNormal);
		CBitmap* pOld = MemDC.SelectObject(&bitmap);
		if(m_clrMask != CLR_NONE)
		{
			pDC->TransparentBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), m_clrMask);
		}
		else
		{
			pDC->BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, SRCCOPY);
		}
		MemDC.SelectObject(pOld);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}


	DrawItems(pDC, rcCli);

	if (m_bDrop && !m_bSingle && CLR_NONE != m_clrRect)
	{
		int nLeft   = m_startPt.x < m_curPt.x ? m_startPt.x : m_curPt.x;
		int nRight  = m_startPt.x > m_curPt.x ? m_startPt.x : m_curPt.x;
		int nTop    = m_startPt.y < m_curPt.y ? m_startPt.y : m_curPt.y;
		int nBottom = m_startPt.y > m_curPt.y ? m_startPt.y : m_curPt.y;

		CPen pen;
		pen.CreatePen(PS_SOLID, 3, m_clrRect);
		pDC->SelectStockObject(NULL_BRUSH);;
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(nLeft, nTop, nRight, nBottom);
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}
}
//---------------------------------------------------------------------------------
void CUiKeyboardCtrl::DrawItems(CDC* pDC, CRect rcCli)
{
	for(int i=0; i<m_nNumOfItems; i++)
	{	
		UIKB_RECT* pItem = (UIKB_RECT*)m_pArray[i];

		if (!pItem->bSel) continue;

		//Draw Bitmap
		UINT uId		 = m_uHlBmpId; 
		
		int nPosX = rcCli.left  + pItem->rect.left;
		int nPosY = rcCli.top   + pItem->rect.top;
		int nW = pItem->rect.Width();
		int nH = pItem->rect.Height();
		
		if(uId != 0)
		{
			CBitmap bitmap;
			CBitmap* pOldBitmap = NULL;
			bitmap.LoadBitmap(uId);

			CDC MemDC;
			MemDC.CreateCompatibleDC(pDC);
			if(m_clrMask != CLR_NONE)
			{
				MemDC.BitBlt(0, 0, nW, nH, pDC, nPosX, nPosY, SRCCOPY);
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->TransparentBlt(nPosX, nPosY, nW, nH, &MemDC, nPosX, nPosY, nW, nH, m_clrMask);
			}
			else
			{
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->BitBlt(nPosX, nPosY, nW, nH, &MemDC, nPosX, nPosY, SRCCOPY);
			}
			MemDC.SelectObject(pOldBitmap);
			bitmap.DeleteObject();
			MemDC.DeleteDC();
		}
	}
}
//---------------------------------------------------------------------------------
bool CUiKeyboardCtrl::RectInRect(CRect rcSrc, CRect rcInc)
{
	int minx   =   max(rcSrc.left,   rcInc.left);
	int miny   =   max(rcSrc.top,    rcInc.top);
	int maxx   =   min(rcSrc.right,  rcInc.right);
	int maxy   =   min(rcSrc.bottom, rcInc.bottom);

	return !((minx > maxx) || ( miny > maxy));
}

