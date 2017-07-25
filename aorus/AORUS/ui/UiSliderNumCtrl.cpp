#include "stdafx.h"
#include "UiSliderNumCtrl.h"
#include "UiCommon.h"

//--------------------------------------------------------------------------------------------------------
CUiSliderNumCtrl::CUiSliderNumCtrl()
{
	m_bLButtonDown = false;
	m_hCursor   = NULL;
	m_nMoveSpeed = 0;
	m_nBmpCnt   = 0;
	m_pBmpIds   = NULL;
	m_pBmpLocs  = NULL;
	m_nTop	    = 0;
	m_nCenter   = 50;
	m_clrMask	= CLR_NONE;
	m_rcCli		= CRect(0, 0, 0, 0);
	m_nBmpH		= 0;
}

CUiSliderNumCtrl::~CUiSliderNumCtrl()
{
	m_MemDC.DeleteDC();
	if(NULL != m_pBmpIds) 
	{ 
		delete []m_pBmpIds; 
	}
	if(NULL != m_pBmpLocs) 
	{ 
		delete []m_pBmpLocs; 
	}
}

BEGIN_MESSAGE_MAP(CUiSliderNumCtrl, CUiBase)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::SetBitmap(UINT* pBmpIds, int nBmpCount, COLORREF mask)
{
	ASSERT(nBmpCount > 0);
	ASSERT(NULL != pBmpIds);

	BITMAP  bmp;
	CBitmap bitmap;
	bitmap.LoadBitmap(pBmpIds[0]);
	bitmap.GetBitmap(&bmp);
	bitmap.DeleteObject();

	m_rcBmps.left	= 0;
	m_rcBmps.right	= bmp.bmWidth;
	m_rcBmps.top	= 0;
	m_rcBmps.bottom	= bmp.bmHeight * nBmpCount;
	
	m_MemDC.DeleteDC();
	if(NULL != m_pBmpIds)  
	{ 
		delete []m_pBmpIds;  
		m_pBmpIds  = NULL; 
	}
	if(NULL != m_pBmpLocs) 
	{ 
		delete []m_pBmpLocs; 
		m_pBmpLocs = NULL;
	}

	m_nTop	   = 0;
	m_ptOffset = CPoint(0, 0);
	m_nBmpCnt  = nBmpCount;
	m_clrMask  = mask;
	m_nBmpH    = bmp.bmHeight;
	m_pBmpIds  = new UINT[m_nBmpCnt];
	m_pBmpLocs = new CRect[m_nBmpCnt]; 

	CDC* pDC = GetDC();
	m_MemDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, m_rcBmps.Width(), m_rcBmps.Height());
	m_MemDC.SelectObject(&bitmap);

	for(int i=0; i<m_nBmpCnt; i++)
	{
		m_pBmpIds[i]  = pBmpIds[i];
		m_pBmpLocs[i] = CRect(0, 0, bmp.bmWidth, 0);

		CBitmap	bmpTmp;
		bmpTmp.LoadBitmap(pBmpIds[i]);

		CDC  MemDC;
		MemDC.CreateCompatibleDC(pDC);
		MemDC.SelectObject(&bmpTmp);

		m_MemDC.BitBlt(0, bmp.bmHeight * i, bmp.bmWidth, bmp.bmHeight, &MemDC, 0, 0, SRCCOPY);

		bmpTmp.DeleteObject();
		MemDC.DeleteDC();
	}

	ReleaseDC(pDC);

	GetClientRect(m_rcCli);
	//m_rcCli.bottom = m_rcCli.top + m_rcCli.Height() * 3;  //tmp
	m_rcCli.right = m_rcCli.left + m_rcBmps.Width();
	SetWindowPos(NULL, 0, 0, m_rcCli.Width(), m_rcCli.Height(), SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawGraphs(pDC, rcCli);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::DrawGraphs(CDC* pDC, CRect rcCli)
{
	pDC->MoveTo(rcCli.left,  rcCli.top);
	pDC->LineTo(rcCli.left,  rcCli.bottom);
	pDC->MoveTo(rcCli.right - 1, rcCli.top);
	pDC->LineTo(rcCli.right - 1, rcCli.bottom);

	if(CLR_NONE == m_clrMask)
	{
		pDC->BitBlt(0, m_nTop, m_rcBmps.Width(), m_rcBmps.Height(), &m_MemDC, 0, 0, SRCCOPY);
	}
	else
	{
		pDC->TransparentBlt(0, m_nTop, m_rcBmps.Width(), m_rcBmps.Height(), &m_MemDC, 0, 0, m_rcBmps.Width(), m_rcBmps.Height(), m_clrMask);
	}

	// space in the top.

	int nTopCliLeft = m_nTop - rcCli.top;
	if(nTopCliLeft > 0)
	{
		int nBmpPad  = 0;
		int nBmpUsed = rcCli.bottom - m_nTop;
		nBmpUsed = (nBmpUsed <= m_rcBmps.Height()) ? nBmpUsed : m_rcBmps.Height();
		int nBmpLeft = m_rcBmps.Height() - nBmpUsed;

		if(nBmpLeft > 0)
		{
			nBmpPad = nTopCliLeft;
			nBmpPad = (nTopCliLeft <= nBmpLeft) ? nBmpPad : nBmpLeft;
			if(CLR_NONE == m_clrMask)
			{
				pDC->BitBlt(0, 0, m_rcBmps.Width(), nBmpPad, &m_MemDC, 0, m_rcBmps.Height() - nBmpPad, SRCCOPY);
			}
			else
			{
				pDC->TransparentBlt(0, 0, m_rcBmps.Width(), nBmpPad, &m_MemDC, 0, m_rcBmps.Height() - nBmpPad, m_rcBmps.Width(), nBmpPad, m_clrMask);
			}
		}	
	}

	// space in the bottom.

	int nBomCliLeft = rcCli.bottom - (m_nTop + m_rcBmps.Height());
	if(nBomCliLeft > 0)
	{
		int nBmpPad  = 0;
		int nBmpUsed = m_nTop + m_rcBmps.Height() - ((m_nTop >= rcCli.top) ? m_nTop : rcCli.top);
		int nBmpLeft = m_rcBmps.Height() - nBmpUsed;

		if(nBmpLeft > 0)
		{
			nBmpPad = nBomCliLeft;
			nBmpPad = (nBomCliLeft <= nBmpLeft) ? nBmpPad : nBmpLeft;
			if(CLR_NONE == m_clrMask)
			{
				pDC->BitBlt(0, rcCli.Height() - nBmpPad, m_rcBmps.Width(), nBmpPad, &m_MemDC, 0, 0, SRCCOPY);
			}
			else
			{
				pDC->TransparentBlt(0, rcCli.Height() - nBmpPad, m_rcBmps.Width(), nBmpPad, &m_MemDC, 0, 0, m_rcBmps.Width(), nBmpPad, m_clrMask);
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------
//Dragging is started
void CUiSliderNumCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_rcCli.PtInRect(point))
	{
		SetCapture();

		m_ptOffset = point;
		m_bLButtonDown = true;
		OnMouseMove(nFlags, point);
		Invalidate(FALSE);
	}

	CUiBase::OnLButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
// During dragging
void CUiSliderNumCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_rcCli.PtInRect(point))
	{
		OnLButtonUp(nFlags, point);
	}

	if(NULL != m_hCursor)
	{
		::SetCursor(m_hCursor);
	}

	static int s_nDisY = 0;

	if(m_bLButtonDown)
	{
		m_nMoveSpeed = point.y - s_nDisY;		// Distance between two WM_MOUSEMOVE events. Consider it as mouse's moving speed.
		m_nTop += point.y - m_ptOffset.y;
		m_ptOffset = point;
		RecalPosition(m_rcCli);
		Invalidate(FALSE);
	}

	s_nDisY = point.y;

	CUiBase::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is finished
void CUiSliderNumCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bLButtonDown)
	{
		ReleaseCapture();
		m_bLButtonDown = false;
		m_ptOffset = CPoint(0, 0);

		if(0 == m_nMoveSpeed)
		{
			GetPadding(m_rcCli);
		}
		else
		{
			HANDLE hHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ThreadProc), this, 0, NULL);
			if(NULL != hHandle)
			{
				CloseHandle(hHandle);
			}
		}
	}

	Invalidate(FALSE);

	CUiBase::OnLButtonUp(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::SetCursor(UINT nCursorId)
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
//--------------------------------------------------------------------------------------------------------
DWORD CUiSliderNumCtrl::ThreadProc(LPVOID lpParameter)
{
	CUiSliderNumCtrl* pCtrl = (CUiSliderNumCtrl*)lpParameter;
	pCtrl->Slide();

	return 0;
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::Slide()
{
	//1.计算滑动的总距离:
	//for(i=0; i<nTimes; i++)
	//{
	//	Total += bMoveDown ? 1 * (nTimes - i) : 1 * (i - nTimes);
	//}

	//2.总距离加Padding距离: Total += Padding;

	//3.计算滑动时的最大速度: V_Max = 2 * Total / nTimes; 最小速度: V_Min = 1;

	//4.按V_Max 至 V_Min的速度递减滑动;

	int i = 0;
	BOOL bMoveDown = (BOOL)(m_nMoveSpeed >= 0);
	int nTimes = bMoveDown ? m_nMoveSpeed : -m_nMoveSpeed;
	for(i=0; i<nTimes; i++)
	{
		if(m_bLButtonDown) { break; }

		Sleep(10);

		int nDistanceY = bMoveDown ? 1 * (nTimes - i) : 1 * (i - nTimes);
		m_nTop += nDistanceY;
		RecalPosition(m_rcCli);
		Invalidate(FALSE);
		UpdateWindow();   
	}

	if(i == nTimes)
	{
		int nPadding = GetPadding(m_rcCli); 
		//if(nPadding < 0)
		//{
		//	nPadding += m_nBmpH;
		//}

		//for(int k=0; k<nPadding; k++)
		//{
		//	Sleep(10);

		//	m_nTop += 1;
		//	RecalPosition(m_rcCli);
		//	Invalidate(FALSE);
		//	UpdateWindow();
		//}
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiSliderNumCtrl::RecalPosition(CRect rcRollZone)
{
	if(m_nTop >= rcRollZone.bottom)
	{
		m_nTop = (rcRollZone.Height() >= m_rcBmps.Height()) ? rcRollZone.top : rcRollZone.bottom - m_rcBmps.Height();
	}

	if(m_nTop + m_rcBmps.Height() < rcRollZone.top)
	{
		m_nTop = (rcRollZone.Height() < m_rcBmps.Height()) ? rcRollZone.top : rcRollZone.bottom - m_rcBmps.Height();
	}
}
//--------------------------------------------------------------------------------------------------------
int CUiSliderNumCtrl::GetPadding(CRect rcCli, int nSlideDirection)
{
	for(int i=0; i<m_nBmpCnt; i++)
	{
		m_pBmpLocs[i].top = 0;
		m_pBmpLocs[i].bottom = 0;
	}

	// calculate all Bmps's location. 

	int nTopCliLeft = m_nTop - rcCli.top;  // space in the top.
	int nBomCliLeft = rcCli.bottom - (m_nTop + m_rcBmps.Height()); // space in the bottom.
	if(nTopCliLeft > 0)
	{
		int nBmpPad  = 0;
		int nBmpUsed = rcCli.bottom - m_nTop;
		nBmpUsed = (nBmpUsed <= m_rcBmps.Height()) ? nBmpUsed : m_rcBmps.Height();
		int nBmpLeft = m_rcBmps.Height() - nBmpUsed;
		if(nBmpLeft > 0)
		{
			nBmpPad = nTopCliLeft;
			nBmpPad = (nTopCliLeft <= nBmpLeft) ? nBmpPad : nBmpLeft;
		}

		int nCount = nBmpUsed / m_nBmpH;
		if(0 != (nBmpUsed % m_nBmpH))
		{
			nCount += 1;
		}

		for(int i=0; i<nCount; i++)
		{
			m_pBmpLocs[i].top = m_nTop + m_nBmpH * i;
			m_pBmpLocs[i].bottom = m_nTop + m_nBmpH * (i + 1);
		}

		nCount = nBmpPad / m_nBmpH;
		if(0 != (nBmpPad % m_nBmpH))
		{
			nCount += 1;
		}

		for(int i=0; i<nCount; i++)
		{
			if(0 == m_pBmpLocs[m_nBmpCnt - 1 - i].top && 0 == m_pBmpLocs[m_nBmpCnt - 1 - i].bottom)
			{
				m_pBmpLocs[m_nBmpCnt - 1 - i].top = nBmpPad - m_nBmpH * (i + 1);
				m_pBmpLocs[m_nBmpCnt - 1 - i].bottom = nBmpPad - m_nBmpH * i;
			}
		}
	}
	else if(nBomCliLeft > 0)
	{
		int nBmpPad  = 0;
		int nBmpUsed = m_nTop + m_rcBmps.Height() - ((m_nTop >= rcCli.top) ? m_nTop : rcCli.top);
		int nBmpLeft = m_rcBmps.Height() - nBmpUsed;
		if(nBmpLeft > 0)
		{
			nBmpPad = nBomCliLeft;
			nBmpPad = (nBomCliLeft <= nBmpLeft) ? nBmpPad : nBmpLeft;
		}

		int nCount = nBmpUsed / m_nBmpH;
		if(0 != (nBmpUsed % m_nBmpH))
		{
			nCount += 1;
		}

		for(int i=0; i<nCount; i++)
		{
			m_pBmpLocs[m_nBmpCnt - 1 - i].top = nBmpUsed - m_nBmpH * (i + 1);
			m_pBmpLocs[m_nBmpCnt - 1 - i].bottom = m_pBmpLocs[m_nBmpCnt - 1 - i].top + m_nBmpH;
		}

		nCount = nBmpPad / m_nBmpH;
		if(0 != (nBmpPad % m_nBmpH))
		{
			nCount += 1;
		}

		for(int i=0; i<nCount; i++)
		{
			m_pBmpLocs[i].top = rcCli.bottom - nBmpPad - m_nBmpH * i;
			m_pBmpLocs[i].bottom = m_pBmpLocs[i].top + m_nBmpH;
		}
	}

	// Get padding.

	int nRcCount = m_rcCli.Height() / m_nBmpH + 2;
	CRect* pRc = new CRect[nRcCount];
	for(int i=0; i<nRcCount; i++)
	{
		pRc[i] = CRect(m_pBmpLocs[0].left, 0, m_pBmpLocs[0].right, 0);
	}

	nRcCount = 1;
	pRc[0].top = m_nCenter - m_nBmpH/2;
	pRc[0].bottom = pRc[0].top + m_nBmpH;

	int nTmp = pRc[0].top - m_nBmpH;
	while(nTmp >= m_rcCli.top)
	{
		pRc[nRcCount].top = nTmp;
		pRc[nRcCount].bottom = pRc[nRcCount].top + m_nBmpH;
		nTmp = pRc[nRcCount].top - m_nBmpH;
		nRcCount++;
	}

	nTmp = pRc[0].bottom + m_nBmpH;
	while(nTmp <= m_rcCli.bottom)
	{
		pRc[nRcCount].bottom = nTmp;
		pRc[nRcCount].top = pRc[nRcCount].bottom - m_nBmpH;
		nTmp = pRc[nRcCount].bottom + m_nBmpH;
		nRcCount++;
	}

	CRect rcBmp = CRect(0, 0, 0, 0);
	for(int i=0; i<m_nBmpCnt; i++)
	{
		if(m_pBmpLocs[i].top >= m_rcCli.top && m_pBmpLocs[i].bottom <= m_rcCli.bottom)
		{
			rcBmp = m_pBmpLocs[i];
			break;
		}
	}

	int nPadUp = 0;
	int nPadDn = 0;
	bool bUpFound = false;
	bool bDnFound = false;

	while(1)
	{
		bool bBreak = false;
		for(int i=0; i<nRcCount; i++)
		{
			if(nPadUp >= m_nBmpH || pRc[i] == CRect(rcBmp.left, rcBmp.top - nPadUp, rcBmp.right, rcBmp.bottom - nPadUp))
			{
				bBreak = true;
				if(nPadUp < m_nBmpH)
				{
					bUpFound = true;
				}
				break;
			}
		}

		if(bBreak) break;
		nPadUp++;
	}

	while(1)
	{
		bool bBreak = false;
		for(int i=0; i<nRcCount; i++)
		{
			if(nPadDn >= m_nBmpH || pRc[i] == CRect(rcBmp.left, rcBmp.top + nPadDn, rcBmp.right, rcBmp.bottom + nPadDn))
			{
				bBreak = true;
				if(nPadDn < m_nBmpH)
				{
					bDnFound = true;
				}
				break;
			}
		}

		if(bBreak) break;
		nPadDn++;
	}

	if(!bUpFound || !bDnFound)
	{
		return 0; // unreasonable.
	}

	int nPadding = 0;
	if(nSlideDirection > 0) // Up
	{
		nPadding = nPadUp;
	}
	else if(nSlideDirection < 0) // Down
	{
		nPadding = nPadDn; 
	}
	else // None
	{
	}

	delete []pRc;

	return nPadding;
}
//--------------------------------------------------------------------------------------------------------