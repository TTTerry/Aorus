#include "stdafx.h"
#include "UiBase.h"
#include "UiCommon.h"

IMPLEMENT_DYNAMIC(CUiBase, CWnd)

CUiBase::CUiBase()
{ 
	m_dwStyle      = 0;
	m_bStoredBkDc  = false;
	m_pBkBrush     = NULL;
	m_uBkBmpId     = 0;
	m_clrBk        = CLR_NONE;
	m_clrBkBmpMask = CLR_NONE;
}

CUiBase::~CUiBase()
{
	m_BkDC.DeleteDC();
}

BEGIN_MESSAGE_MAP(CUiBase, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------------------
BOOL CUiBase::Create(CWnd* pParent, UINT nId, RECT rect, DWORD dwStyle)
{
	return CWnd::Create(NULL, _T(""), dwStyle, rect, pParent, nId);
}
//--------------------------------------------------------------------------------------------------------
CDC* CUiBase::GetBkDC()                  
{ 
	return &m_BkDC; 
}
//--------------------------------------------------------------------------------------------------------
COLORREF CUiBase::GetBkColor()               
{
	return m_clrBk; 
}
//--------------------------------------------------------------------------------------------------------
CBrush* CUiBase::GetBkBrush()             
{
	return m_pBkBrush;
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::SetBkColor(COLORREF clrBk) 
{ 
	ASSERT(NULL == m_pBkBrush && 0 == m_uBkBmpId); 
	m_clrBk = clrBk;
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::SetBkBrush(CBrush* pBrush) 
{ 
	ASSERT(CLR_NONE == m_clrBk && 0 == m_uBkBmpId); 
	m_pBkBrush = pBrush; 
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::SetBkBitmap(UINT uBkBmpId, COLORREF clrMask, int nWinPosX, int nWinPosY, bool bAutoMoveWin) 
{
	ASSERT(NULL == m_pBkBrush && CLR_NONE == m_clrBk);

	m_uBkBmpId    = uBkBmpId;
	m_clrBkBmpMask = clrMask;

	if(bAutoMoveWin && uBkBmpId != 0)
	{
		BITMAP  bmp;
		CBitmap bitmap;
		bitmap.LoadBitmap(m_uBkBmpId);
		bitmap.GetBitmap(&bmp);
		MoveWindow(nWinPosX, nWinPosY, bmp.bmWidth, bmp.bmHeight);
		bitmap.DeleteObject();
	}
}
//--------------------------------------------------------------------------------------------------------
DWORD CUiBase::GetCtrlStyle()
{
	return m_dwStyle;
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd)
{
	m_dwStyle &= ~dwRemove;
	m_dwStyle |= dwAdd;
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::OnSize(UINT nType, int cx, int cy) 
{
	m_bStoredBkDc = false;
	RecalLayout();
	CWnd::OnSize(nType, cx, cy);	
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiBase::OnEraseBkgnd(CDC* pDC) 
{	
	if(!m_bStoredBkDc)
	{
		m_bStoredBkDc = true; 

		CRect rcCli;
		GetClientRect(&rcCli);
		m_BkDC.DeleteDC();
		m_BkDC.CreateCompatibleDC(pDC);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(pDC, rcCli.Width(), rcCli.Height());
		m_BkDC.SelectObject(&bitmap);
		m_BkDC.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), pDC, rcCli.left, rcCli.top, SRCCOPY);

		if(0 != m_uBkBmpId)
		{
			BITMAP  bmp;
			CBitmap	bitmap;
			bitmap.LoadBitmap(m_uBkBmpId);
			bitmap.GetObject(sizeof(BITMAP), &bmp);

			CDC  MemDC;
			MemDC.CreateCompatibleDC(&m_BkDC);
			CBitmap* pOld = MemDC.SelectObject(&bitmap);
			if(m_clrBkBmpMask != CLR_NONE)
			{
				m_BkDC.TransparentBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, m_clrBkBmpMask);
			}
			else
			{
				m_BkDC.BitBlt(rcCli.left, rcCli.top, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, SRCCOPY);
			}

			MemDC.SelectObject(pOld);
			bitmap.DeleteObject();
			MemDC.DeleteDC();
		}
		else if(NULL != m_pBkBrush) 
		{
			m_BkDC.FillRect(&rcCli, m_pBkBrush);
		}
		else if(m_clrBk != CLR_NONE) 
		{
			m_BkDC.FillSolidRect(&rcCli, m_clrBk); 
		}
	}

	return TRUE;
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::OnPaint() 
{
	CPaintDC dc(this);

	CRect rcCli; 
	GetClientRect(&rcCli);

	//Flicker free drawing
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; 
	bitmap.CreateCompatibleBitmap(&dc, rcCli.Width(), rcCli.Height());
	CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);

	Refresh(&MemDC, rcCli);
	Draw(&MemDC, rcCli);

	dc.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	MemDC.DeleteDC();
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::Refresh(CDC* pDC, CRect rcCli)
{
	if(NULL != m_BkDC.GetSafeHdc())
	{
		pDC->BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &m_BkDC, rcCli.left, rcCli.top, SRCCOPY);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiBase::RecalLayout()
{
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiBase::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CWnd* pParent = GetParent();
	if(NULL != pParent->GetSafeHwnd())
	{
		pParent->SendMessage(WM_COMMAND, wParam, lParam);
	}

	return TRUE;
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiBase::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CWnd* pParent = GetParent();
	if(NULL != pParent->GetSafeHwnd())
	{
		pParent->SendMessage(WM_NOTIFY, wParam, lParam);
	}
	
	return TRUE;
}
//--------------------------------------------------------------------------------------------------------
HRGN CUiBase::CreateRgn(UINT uId, COLORREF clrMask)
{
	CBitmap bitmap;
	bitmap.LoadBitmap(uId);

	return CreateRgn(&bitmap, clrMask);
}
//--------------------------------------------------------------------------------------------------------
HRGN CUiBase::CreateRgn(CDC* pDC, COLORREF clrMask)
{
	BITMAP bmp = {0};
	CBitmap* pBitmap = pDC->GetCurrentBitmap();

	return CreateRgn(pBitmap, clrMask);
}
//--------------------------------------------------------------------------------------------------------
HRGN CUiBase::CreateRgn(CBitmap* pBitmap, COLORREF clrMask)
{
	BITMAP bmp = {0};
	pBitmap->GetBitmap(&bmp);

	int nWidth      = bmp.bmWidth;
	int nHeigh      = bmp.bmHeight;
	int nWidthBytes = bmp.bmWidthBytes;
	int nBytesPixel = bmp.bmBitsPixel / 8;

	BYTE* pSrc = new BYTE[nWidthBytes * nHeigh];
	if(NULL == pSrc)
	{
		return NULL;
	}

	pBitmap->GetBitmapBits(nWidthBytes * nHeigh, (void*)pSrc);
	
	bool bBound = false;
	HRGN hAll = CreateRectRgn(0, 0, 0, 0);
	
	for(int i=0; i<nHeigh; i++)
	{
		int nLeftX = 0;
		for(int j=0; j<nWidth; j++)
		{
			DWORD dwColor = *(DWORD*)(pSrc + i * nWidthBytes + j * nBytesPixel);
			if(dwColor != clrMask && !bBound)
			{
				nLeftX = j;
				bBound = true;
			}
			if((dwColor == clrMask || j + 1 == nWidth) && bBound)
			{
				bBound = false;

				if(j + 1 == nWidth && clrMask != dwColor)
				{
					j++;
				}
				HRGN hTemp = CreateRectRgn(nLeftX, i, j, i + 1);
				CombineRgn(hAll, hAll, hTemp, RGN_OR);
				DeleteObject(hTemp);
			}
		}
	}

	delete []pSrc;

	return hAll;
}
//--------------------------------------------------------------------------------------------------------
