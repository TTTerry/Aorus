#include "stdafx.h"
#include "UiPanelCtrl.h"
#include "UiCommon.h"

UIPC_IMAGE::UIPC_IMAGE()
{
	uNormal		= 0;	 
	uMouseIn	= 0;
	uSelect		= 0;
	clrMask		= CLR_NONE;

}

UIPC_IMAGE::UIPC_IMAGE(UINT normal, UINT mouseIn, UINT select, COLORREF mask)
{
	uNormal		= normal;	 
	uMouseIn	= mouseIn;
	uSelect		= select;
	uDisable    = 0;
	clrMask		= mask;
}

UIPC_IMAGE::UIPC_IMAGE(UINT normal, UINT mouseIn, UINT select, UINT disable, COLORREF mask)
{
	uNormal		= normal;	 
	uMouseIn	= mouseIn;
	uSelect		= select;
	uDisable    = disable;
	clrMask		= mask;
}

UIPC_IMAGE& UIPC_IMAGE::operator = (const UIPC_IMAGE* pBmpMode)
{
	uNormal		= pBmpMode->uNormal;	 
	uMouseIn	= pBmpMode->uMouseIn;
	uSelect		= pBmpMode->uSelect;
	clrMask		= pBmpMode->clrMask;

	return *this;
}
	
UIPC_STRING::UIPC_STRING()
{
	sCaption	= _T("");
	clrNormal	= CLR_NONE;
	clrMouseIn	= CLR_NONE;
	clrSelect	= CLR_NONE;
	clrDisable  = CLR_NONE;
	pFtNormal	= NULL;
	pFtMouseIn	= NULL;
	pFtSelect	= NULL;
	rect		= CRect(0, 0, 0, 0);
	dwAlign		= 0;
}
UIPC_STRING::UIPC_STRING(CString caption,
						 COLORREF normal, COLORREF mouseIn, COLORREF select, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	clrDisable  = CLR_NONE;
	rect		= CRect(0, 0, 0, 0);
	dwAlign		= 0;
}

UIPC_STRING::UIPC_STRING(CString caption, 
						 CRect rc, COLORREF normal, COLORREF mouseIn, COLORREF select, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	clrDisable  = CLR_NONE;
	rect		= rc;
	dwAlign		= 0;
}

UIPC_STRING::UIPC_STRING(CString caption, DWORD align, CRect rc, 
						 COLORREF normal, COLORREF mouseIn, COLORREF select, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	clrDisable  = CLR_NONE;
	rect		= rc;
	dwAlign		= align;
}

UIPC_STRING::UIPC_STRING(CString caption, 
						 COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect, CFont* pDisable)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	clrDisable	= disable;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	pFtDisable	= pDisable;
	dwAlign		= 0;
}

UIPC_STRING::UIPC_STRING(CString caption, CRect rc, 
						 COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect, CFont* pDisable)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	clrDisable	= disable;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	pFtDisable	= pDisable;
	rect		= rc;
	dwAlign		= 0;
}

UIPC_STRING::UIPC_STRING(CString caption, DWORD align, CRect rc,  
						 COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, 
						 CFont* pNormal, CFont* pMouseIn, CFont* pSelect, CFont* pDisable)
{
	sCaption	= caption;
	clrNormal	= normal;
	clrMouseIn	= mouseIn;
	clrSelect	= select;
	clrDisable	= disable;
	pFtNormal	= pNormal;
	pFtMouseIn	= pMouseIn;
	pFtSelect	= pSelect;
	pFtDisable	= pDisable;
	rect		= rc;
	dwAlign		= align;
}

UIPC_STRING& UIPC_STRING::operator = (const UIPC_STRING* pStrMode)
{
	sCaption	= pStrMode->sCaption;
	clrNormal	= pStrMode->clrNormal;
	clrMouseIn	= pStrMode->clrMouseIn;
	clrSelect	= pStrMode->clrSelect;
	pFtNormal	= pStrMode->pFtNormal;
	pFtMouseIn	= pStrMode->pFtMouseIn;
	pFtSelect	= pStrMode->pFtSelect;
	rect		= pStrMode->rect;
	clrDisable	= pStrMode->clrDisable;
	dwAlign		= pStrMode->dwAlign;
	return *this;
}

UIPC_ITEM::UIPC_ITEM()
{
	uItemId	= 0;
	rect	= CRect(0, 0, 0, 0);
	bEnable = true;
	bVisible = true;
}

UIPC_ITEM::UIPC_ITEM(UINT id, CRect rc, UIPC_IMAGE* pBmpMode, UIPC_STRING* pStrMode)
{
	uItemId	= id;
	rect	= rc;
	if(NULL != pBmpMode) bmpMode = *pBmpMode;
	if(NULL != pStrMode) strMode = *pStrMode;
	bEnable = true;
	bVisible = true;
}

UIPC_ITEM& UIPC_ITEM::operator = (const UIPC_ITEM* pItem)
{
	uItemId = pItem->uItemId;
	rect	= pItem->rect;
	bmpMode	= pItem->bmpMode;
	strMode	= pItem->strMode;
	bEnable = pItem->bEnable;
	bVisible= pItem->bVisible;

	return *this;
}

CUiPanelCtrl::CUiPanelCtrl()
{
	m_bEnabled	   = true;
	m_nItemSel     =  0;
	m_nNumOfItems  =  0;
	m_nItemMouseIn = -1;
	m_pArray.RemoveAll();

	m_hCursor = NULL; 
}

CUiPanelCtrl::~CUiPanelCtrl()
{
	//m_pArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CUiPanelCtrl, CUiBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTips)
END_MESSAGE_MAP()


CToolTipCtrl* CUiPanelCtrl::GetToolTipCtrl()
{
	return &m_toolTip;
}

void CUiPanelCtrl::SetToolTip(CString sTip, int nMaxTipWidth)
{
	if(NULL != GetSafeHwnd() && sTip != _T("")) 
	{
		if(NULL == m_toolTip.GetSafeHwnd()) 
		{
			EnableToolTips(TRUE);
			m_toolTip.Create(this);
			m_toolTip.Activate(TRUE);
			m_toolTip.AddTool(this, LPSTR_TEXTCALLBACK);
		}
	}
}

BOOL CUiPanelCtrl::OnToolTips(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	CString sTip;
    TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	sTip = _T("OnToolTips");
	_tcscpy(pTTT->lpszText, sTip.GetBuffer(sTip.GetLength()));
	sTip.ReleaseBuffer();
    pTTT->hinst = AfxGetResourceHandle();

    return TRUE;
}

BOOL CUiPanelCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_MOUSEMOVE)
	{
		if (m_toolTip.GetSafeHwnd()) { m_toolTip.RelayEvent(pMsg); }
	}

	return CUiBase::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetText(UIPC_STRING* pStrMode, int nId)
{
	if(nId >= 0)
	{
		for(int i=0; i<m_nNumOfItems; i++)
		{
			UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
			if(pItem->uItemId == nId)
			{
				pItem->strMode = *pStrMode;
				Invalidate(FALSE);
				break; 
			}	
		}
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::EnableItem(int nIndex, bool bEnable)
{
	if (0 < nIndex || nIndex >= m_nNumOfItems) 
		return;

	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	if (NULL != pItem && pItem->bEnable != bEnable)
	{
		pItem->bEnable = bEnable;
		Invalidate(FALSE);
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::EnableItemById(UINT uItemId, bool bEnable)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if(pItem->uItemId == uItemId && pItem->bEnable != bEnable)
		{
			pItem->bEnable = bEnable;
			Invalidate(FALSE);
			break; 
		}	
	}
}
//---------------------------------------------------------------------------------
bool CUiPanelCtrl::IsItemEnable(int nIndex)
{
	if (0 < nIndex || nIndex >= m_nNumOfItems) 
		return false;

	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	if (NULL != pItem)
	{
		return pItem->bEnable;
	}
	return false;
}
//---------------------------------------------------------------------------------
bool CUiPanelCtrl::IsItemEnableById(UINT uItemId)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if(pItem->uItemId == uItemId)
		{
			return pItem->bEnable;
		}	
	}
	return false;
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::Enable(bool bEnable)
{
	if (m_bEnabled != bEnable)
	{
		m_bEnabled = bEnable;
		Invalidate(FALSE);
	}
}
//---------------------------------------------------------------------------------
bool CUiPanelCtrl::IsEnable()
{
	return m_bEnabled;
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetCursor(UINT nCursorId)
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
void CUiPanelCtrl::AddItem(UIPC_ITEM* pItem)
{
	ASSERT(pItem != NULL);

	UIPC_ITEM* pNew = new UIPC_ITEM;
	
	*pNew = *pItem;

	UINT uId = pNew->bmpMode.uNormal;
	uId = (0 != uId) ? uId : pNew->bmpMode.uMouseIn;
	uId = (0 != uId) ? uId : pNew->bmpMode.uSelect;

	if(0 != uId)
	{
		BITMAP  bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(uId);
		bitmap.GetBitmap(&bmp);
		pNew->rect.right  = pNew->rect.left + bmp.bmWidth;
		pNew->rect.bottom = pNew->rect.top + bmp.bmHeight;
		bitmap.DeleteObject();
	}

	m_pArray.SetAtGrow(m_nNumOfItems, pNew);

	//m_nItemSel = 0;
	m_nNumOfItems++;

	RecalLayout();
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::DeleteItem(int nIndex)
{
	if (0 < nIndex || nIndex >= m_nNumOfItems) 
		return;

	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	if(NULL != pItem)
	{
		delete pItem;
	}

	m_nNumOfItems--;
	m_pArray.RemoveAt(nIndex, 1);
	if (m_nNumOfItems > 0)
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
void CUiPanelCtrl::DeleteItemById(UINT uItemId)
{
	int nIndex = -1;
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (pItem->uItemId == uItemId)
		{
			nIndex = i; break;
		}
	}
	if (nIndex >= 0)
	{
		DeleteItem(nIndex);
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetCurItem(int nIndex)
{
	m_nItemSel = nIndex;
	if(nIndex == m_nItemMouseIn)
	{
		m_nItemMouseIn = -1;
	}

	Invalidate(FALSE);
	UpdateWindow();
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetCurItemById(UINT uItemId)
{
	int nIndex = -1;
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (pItem->uItemId == uItemId)
		{
			nIndex = i; break;
		}
	}
	if (nIndex >= 0)
	{
		SetCurItem(nIndex);
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetItemVisible(int nIndex, bool bVisible)
{
	if(nIndex < 0 || nIndex >= m_nNumOfItems) 
		return;
	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	if(NULL != pItem && pItem->bVisible != bVisible)
	{
		pItem->bVisible = bVisible;
		Invalidate(FALSE);
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::SetItemVisibleById(UINT uItemId, bool bVisible)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (pItem->uItemId != uItemId)
			continue;
		if (pItem->bVisible != bVisible)
		{
			pItem->bVisible = bVisible;
			Invalidate(FALSE);
		}
		break;
	}
}
//---------------------------------------------------------------------------------
bool CUiPanelCtrl::IsItemVisible(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_nNumOfItems) 
		return false;
	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	if(NULL != pItem)
	{
		return pItem->bVisible;
	}
	return false;
}
//---------------------------------------------------------------------------------
bool CUiPanelCtrl::IsItemVisibleById(UINT uItemId)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (pItem->uItemId == uItemId)
		{
			return pItem->bVisible;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
int  CUiPanelCtrl::GetCurItem()             
{ 
	return m_nItemSel; 
}
//---------------------------------------------------------------------------------
UIPC_ITEM* CUiPanelCtrl::GetItem(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_nNumOfItems) 
		return NULL;
	UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray.GetAt(nIndex);
	return pItem;
}
//---------------------------------------------------------------------------------
UIPC_ITEM* CUiPanelCtrl::GetItemById(UINT uItemId)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (pItem->uItemId == uItemId)
		{
			return pItem;
		}
	}

	return NULL;
}
//---------------------------------------------------------------------------------
int  CUiPanelCtrl::GetItemCount()            
{ 
	return m_nNumOfItems; 
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	CWnd::OnLButtonDown(nFlags, point);

	Invalidate(TRUE);
	UpdateWindow();

	for(int i=0; i<m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if(pItem->rect.PtInRect(point) && pItem->bEnable && pItem->bVisible)
		{
            SetCurItem(i);
			CWnd* pParent = GetParent();
			while(NULL != pParent)
			{
				if(pParent->SendMessage(WM_UI_PANEL_SELCHANGE, GetDlgCtrlID(), pItem->uItemId)) break;
				pParent = pParent->GetParent();
			}
			break; 
		}	
	}
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bEnabled) { return; }

	CUiBase::OnMouseMove(nFlags, point);

	int nItemMouseIn = -1;
	for(int i=0; i<m_nNumOfItems; i++)
	{
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if(pItem->rect.PtInRect(point) && pItem->bEnable && pItem->bVisible)
		{
			nItemMouseIn = i; break; 
		}	
	}

	if(nItemMouseIn != m_nItemSel && nItemMouseIn != m_nItemMouseIn)
	{
		m_nItemMouseIn = nItemMouseIn;
		Invalidate(FALSE);

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
LRESULT CUiPanelCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_nItemMouseIn >= 0 && m_bEnabled)
	{
		m_nItemMouseIn = -1;
		Invalidate(FALSE);
	}

	return 0;
}
//---------------------------------------------------------------------------------
BOOL CUiPanelCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_hCursor != NULL && m_bEnabled)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		for(int i=0; i<m_nNumOfItems; i++)
		{
			UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
			if(m_hCursor != NULL && pItem->rect.PtInRect(point) && pItem->bEnable && pItem->bVisible)
			{
				::SetCursor(m_hCursor); 
				return TRUE;
			}	
		}
	}

	return CUiBase::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::OnDestroy()
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
void CUiPanelCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawItems(pDC, rcCli);
}
//---------------------------------------------------------------------------------
void CUiPanelCtrl::DrawItems(CDC* pDC, CRect rcCli)
{
	for (int i = 0; i < m_nNumOfItems; i++)
	{	
		UIPC_ITEM* pItem = (UIPC_ITEM*)m_pArray[i];
		if (!pItem->bVisible)
		{
			continue; // Hide 
		}

		//Draw Bitmap
		UINT uItemId	 = pItem->uItemId;
		UINT uId		 = pItem->bmpMode.uNormal; 
		CFont* pFont	 = pItem->strMode.pFtNormal;
		COLORREF clrText = pItem->strMode.clrNormal;
		CRect rcText	 = pItem->strMode.rect;
		
		if(i == m_nItemSel)    
		{ 
			uId     = pItem->bmpMode.uSelect;
			pFont   = pItem->strMode.pFtSelect;
			clrText = pItem->strMode.clrSelect;
		}

		if(i == m_nItemMouseIn) 
		{ 
			uId     = pItem->bmpMode.uMouseIn; 
			pFont   = pItem->strMode.pFtMouseIn;
			clrText = pItem->strMode.clrMouseIn;
		}

		if (!pItem->bEnable || !m_bEnabled)
		{
			uId = pItem->bmpMode.uDisable;
			pFont = pItem->strMode.pFtDisable;
			if(CLR_NONE != pItem->strMode.clrDisable) clrText = pItem->strMode.clrDisable;
		}

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
			if(pItem->bmpMode.clrMask != CLR_NONE)
			{
				MemDC.BitBlt(0, 0, nW, nH, pDC, nPosX, nPosY, SRCCOPY);
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->TransparentBlt(nPosX, nPosY, nW, nH, &MemDC, 0, 0, nW, nH, pItem->bmpMode.clrMask);
			}
			else
			{
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->BitBlt(nPosX, nPosY, nW, nH, &MemDC, 0, 0, SRCCOPY);
			}
			MemDC.SelectObject(pOldBitmap);
			bitmap.DeleteObject();
			MemDC.DeleteDC();
		}

		if(_T("") != pItem->strMode.sCaption)
		{
			CFont* pOldFont = NULL; 
			if(NULL != pFont)
			{
				pOldFont = pDC->SelectObject(pFont);
			}
			if(clrText != CLR_NONE)
			{
				pDC->SetTextColor(clrText);
			}
			pDC->SetBkMode(TRANSPARENT);
			//if(rcText.Width() > 0) pDC->DrawText(pItem->strMode.sCaption, &rcText, DT_VCENTER | DT_CENTER); 
			if(rcText.Width() > 0) 
			{
				DWORD dwFlags = 0;
				if (pItem->strMode.dwAlign & ST_LEFT) dwFlags |= DT_LEFT;
				else if (pItem->strMode.dwAlign & ST_RIGHT) dwFlags |= DT_RIGHT;
				else dwFlags |= DT_CENTER;
				if (pItem->strMode.dwAlign & ST_TOP) dwFlags |= DT_TOP;
				else if (pItem->strMode.dwAlign & ST_BOTTOM) dwFlags |= DT_BOTTOM;
				else dwFlags |= DT_VCENTER;
				pDC->DrawText(pItem->strMode.sCaption, &rcText, dwFlags); 
			}
			else pDC->DrawText(pItem->strMode.sCaption, &CRect(nPosX, nPosY, nPosX + nW, nPosY + nH), DT_SINGLELINE | DT_VCENTER | DT_CENTER);

			if(NULL != pOldFont)
			{
				pDC->SelectObject(pOldFont);
			}
		}
	}
}
//---------------------------------------------------------------------------------

