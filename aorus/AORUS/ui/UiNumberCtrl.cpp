#include "stdafx.h"
#include "UiNumberCtrl.h"

#define COUNT_NUM  10

UINC_NUMBER::UINC_NUMBER()
{
	clrMask = CLR_NONE;
	Sign[0] = 0;
	Sign[1] = 0;
	for(int i=0; i<COUNT_NUM; i++)
	{
		Num[i] = 0;
	}
}
UINC_NUMBER::UINC_NUMBER(UINT number[], int count, UINT nSign[], int signCount, COLORREF mask)
{
	ASSERT(2 == signCount);
	ASSERT(COUNT_NUM == count);
	
	Sign[0] = nSign[0];
	Sign[1] = nSign[1];
	clrMask = mask;
	for(int i=0; i<COUNT_NUM; i++)
	{
		Num[i] = number[i];
	}
}
UINC_NUMBER::UINC_NUMBER(UINT n0, UINT n1, UINT n2, UINT n3, UINT n4, UINT n5, UINT n6, UINT n7, UINT n8, UINT n9, UINT sP, UINT sN, COLORREF mask)
{
	Sign[0] = sP;
	Sign[1] = sN;
	clrMask = mask;
	Num[0] = n0; Num[1] = n1; Num[2] = n2; Num[3] = n3; Num[4] = n4; 
	Num[5] = n5; Num[6] = n6; Num[7] = n7; Num[8] = n8; Num[9] = n9;
}
UINC_NUMBER& UINC_NUMBER::operator = (const UINC_NUMBER* pNum)
{
	Sign[0] = pNum->Sign[0];
	Sign[1] = pNum->Sign[1];
	clrMask = pNum->clrMask;
	for(int i=0; i<COUNT_NUM; i++)
	{
		Num[i] = pNum->Num[i];
	}
	return *this;
}


UI_NUMBERCTRL::UI_NUMBERCTRL()
{
	pParent = NULL;
	uId     = 0;
	rect    = CRect(0, 0, 0, 0);
	dwStyle = 0;
	pNumLoc = NULL;
	nCount  = 0;
	rcSign  = CRect(-1, -1, -1, -1);
}
UI_NUMBERCTRL::UI_NUMBERCTRL(CWnd* parent, UINT id, CRect rcWin, UINC_NUMBER num, CRect* pLoc, int count, CRect* pS, DWORD style)
{
	pParent = parent;
	uId     = id;
	rect    = rcWin;
	dwStyle = style;
	number  = num;
	pNumLoc = pLoc;
	nCount  = count;
	rcSign  = CRect(-1, -1, -1, -1);
	if(NULL != pS)
	{
		rcSign = *pS;
	}
}
UI_NUMBERCTRL& UI_NUMBERCTRL::operator = (const UI_NUMBERCTRL* pNumCtrl)
{
	pParent = pNumCtrl->pParent;
	uId     = pNumCtrl->uId;
	rect    = pNumCtrl->rect;
	dwStyle = pNumCtrl->dwStyle;
	number  = pNumCtrl->number;
	pNumLoc = pNumCtrl->pNumLoc;
	nCount  = pNumCtrl->nCount;
	rcSign  = pNumCtrl->rcSign;

	return *this;
}



CUiNumberCtrl::CUiNumberCtrl()
{
	m_nValue      = 0;
	m_nNumOfItems = 0;
	m_pArray.RemoveAll();
	m_pSign = NULL;
}

CUiNumberCtrl::~CUiNumberCtrl()
{
	m_pArray.RemoveAll();
	if(NULL != m_pSign)
	{
		delete m_pSign;
	}
}

BEGIN_MESSAGE_MAP(CUiNumberCtrl, CUiBase)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


//------------------------------------------------------------------------------------
void CUiNumberCtrl::CreateNumberCtrl(UI_NUMBERCTRL numCtrl)
{
	Create(numCtrl.pParent, numCtrl.uId, numCtrl.rect, numCtrl.dwStyle);
	SetNumberBitmap(numCtrl.number);
	SetNumberLocation(numCtrl.pNumLoc, numCtrl.nCount, (numCtrl.rcSign == CRect(-1, -1, -1, -1)) ? NULL : &numCtrl.rcSign);
}
//------------------------------------------------------------------------------------
LONG CUiNumberCtrl::GetValue()                        
{ 
	return m_nValue;
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::SetValue(LONG nValue)             
{ 
	m_nValue = nValue; Invalidate(FALSE); 
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::SetNumberBitmap(UINC_NUMBER num)  
{ 
	m_number = num;

	if(0 == m_nNumOfItems) { return; }

	int nW = 0, nH = 0;
	for(int i=0; i<COUNT_NUM; i++)
	{
		if(m_number.Num[i] !=0)
		{
			BITMAP  bmp;
			CBitmap bitmap;
			bitmap.LoadBitmap(m_number.Num[i]);
			bitmap.GetBitmap(&bmp);
			nW = bmp.bmWidth;
			nH = bmp.bmHeight;
			bitmap.DeleteObject();
			break;
		}
	}

	if(0 == nH || 0 == nW) { return; }

	CSize szMax(0, 0);
	if(NULL != m_pSign && m_number.Sign[0] != 0)
	{
		BITMAP  bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(m_number.Sign[0]);
		bitmap.GetBitmap(&bmp);
		m_pSign->right  = m_pSign->left + bmp.bmWidth;
		m_pSign->bottom = m_pSign->top + bmp.bmHeight;
		bitmap.DeleteObject();

		szMax.cx = m_pSign->Width();
		szMax.cy = m_pSign->Height();
	}

	for(int i=0; i<m_nNumOfItems; i++)
	{
		CRect *pItem  = (CRect*)m_pArray.GetAt(i);
		pItem->right  = pItem->left + nW;
		pItem->bottom = pItem->top  + nH;

		if(szMax.cx < pItem->right)  { szMax.cx = pItem->right;  }
		if(szMax.cy < pItem->bottom) { szMax.cy = pItem->bottom; }
	}

	SetWindowPos(NULL, 0, 0, szMax.cx, szMax.cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::SetNumberLocation(CRect numLoc[], int nCount, CRect* pSign)
{
	ASSERT(numLoc != NULL);

	//remove first
	for(int i=0; i<m_nNumOfItems; i++)
	{
		CRect *pItem = (CRect*)m_pArray.GetAt(i);
		if(NULL != pItem)
		{
			delete pItem;
		}
	}
	m_pArray.RemoveAll();

	if(NULL != m_pSign)
	{
		delete m_pSign;
		m_pSign = NULL; 
	}

	int nW = 0, nH = 0;
	for(int i=0; i<COUNT_NUM; i++)
	{
		if(m_number.Num[i] !=0)
		{
			BITMAP  bmp;
			CBitmap bitmap;
			bitmap.LoadBitmap(m_number.Num[i]);
			bitmap.GetBitmap(&bmp);
			nW = bmp.bmWidth;
			nH = bmp.bmHeight;
			bitmap.DeleteObject();
			break;
		}
	}

	CSize szMax(0, 0);
	if(NULL != pSign && m_number.Sign[0] != 0)
	{
		m_pSign = new CRect(0, 0, 0, 0);
		*m_pSign = *pSign;

		BITMAP  bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(m_number.Sign[0]);
		bitmap.GetBitmap(&bmp);
		m_pSign->right  = m_pSign->left + bmp.bmWidth;
		m_pSign->bottom = m_pSign->top + bmp.bmHeight;
		bitmap.DeleteObject();

		szMax.cx = m_pSign->Width();
		szMax.cy = m_pSign->Height();
	}

	for(int i=0; i<nCount; i++)
	{
		CRect* pNew = new CRect(numLoc[i]);
		if(nW != 0 && nH != 0)
		{
			pNew->right  = pNew->left + nW;
			pNew->bottom = pNew->top  + nH;
		}

		if(szMax.cx < pNew->right)  { szMax.cx = pNew->right;  }
		if(szMax.cy < pNew->bottom) { szMax.cy = pNew->bottom; }

		m_pArray.SetAtGrow(m_nNumOfItems, pNew);
		m_nNumOfItems++;
	}

	SetWindowPos(NULL, 0, 0, szMax.cx, szMax.cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	Invalidate(FALSE);
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::OnDestroy()
{
    for(int i=0; i<m_nNumOfItems; i++)
    {
		CRect *pItem = (CRect*)m_pArray.GetAt(i);
		if(NULL != pItem)
		{
			delete pItem;
		}
    }

	CUiBase::OnDestroy();
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::Draw(CDC* pDC, CRect rcCli) 
{
	DrawNumber(pDC, rcCli);
}
//------------------------------------------------------------------------------------
void CUiNumberCtrl::DrawNumber(CDC* pDC, CRect rcCli)
{
	int  nBase = 10;
	LONG nValue = (m_nValue >= 0) ? m_nValue : -m_nValue;

	if(NULL != m_pSign)
	{
		UINT uId = (m_nValue >= 0) ? m_number.Sign[0] : m_number.Sign[1];
		if(uId != 0)
		{
			int nPosX = rcCli.left + m_pSign->left;
			int nPosY = rcCli.top  + m_pSign->top;

			CBitmap bitmap;
			CBitmap *pOldBitmap = NULL;
			bitmap.LoadBitmap(uId);
			BITMAP bmp;
			bitmap.GetBitmap(&bmp);

			CDC MemDC;
			MemDC.CreateCompatibleDC(pDC);
			if(m_number.clrMask != CLR_NONE)
			{
				MemDC.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, pDC, nPosX, nPosY, SRCCOPY);
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->TransparentBlt(nPosX, nPosY, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, m_number.clrMask);
			}
			else
			{
				pOldBitmap = MemDC.SelectObject(&bitmap);
				pDC->BitBlt(nPosX, nPosY, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, SRCCOPY);
			}
			MemDC.SelectObject(pOldBitmap);
			bitmap.DeleteObject();
			MemDC.DeleteDC();
		}
	}
	

	for(int i = m_nNumOfItems - 1; i >= 0; i--)
	{
		CRect* pItem = (CRect*)m_pArray[i];
		CRect rect = *pItem;

		int nIconPosX = rcCli.left + rect.left;
		int nIconPosY = rcCli.top  + rect.top;

		UINT uId = m_number.Num[nValue % nBase];

		if(0 == uId) { nValue /= nBase; continue; }

		CBitmap bitmap;
		CBitmap *pOldBitmap = NULL;
		bitmap.LoadBitmap(uId);
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);

		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		if(m_number.clrMask != CLR_NONE)
		{
			MemDC.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, pDC, nIconPosX, nIconPosY, SRCCOPY);
			pOldBitmap = MemDC.SelectObject(&bitmap);
			pDC->TransparentBlt(nIconPosX, nIconPosY, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, m_number.clrMask);
		}
		else
		{
			pOldBitmap = MemDC.SelectObject(&bitmap);
			pDC->BitBlt(nIconPosX, nIconPosY, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, SRCCOPY);
		}
		MemDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		MemDC.DeleteDC();

		nValue /= nBase;
	}
}
//------------------------------------------------------------------------------------
