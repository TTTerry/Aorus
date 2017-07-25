#include "stdafx.h"
#include "UiCurveGraphCtrl.h"
#include "UiCommon.h"
#include <math.h>
	
//--------------------------------------------------------------------------------------------------------
UICGC_GRAPH::UICGC_GRAPH()
{
	nIndex     = -1;
	nOrder     = -1;
	nLineWidth =  0;
	clrLine    = CLR_NONE;
	clrLineDisable = CLR_NONE;
	pGraphData = NULL;
	nPtsCount  = 0;
	bLine = true;
	bEnable	= true;
	bShowPoint	= true;
}

UICGC_GRAPH::UICGC_GRAPH(int index, int order, int width, COLORREF line, COLORREF lineDisable, CPoint* pData, int nPtsCnt)
{
	nIndex     = index;
	nOrder     = order;
	nLineWidth = width;
	clrLine    = line;
	clrLineDisable = lineDisable;
	pGraphData = pData;
	nPtsCount  = nPtsCnt;
	bLine = true;
	bEnable	= true;
	bShowPoint	= true;
}

UICGC_GRAPH::~UICGC_GRAPH()
{
	if(pGraphData != NULL)
	{
		delete []pGraphData;
		pGraphData = NULL;
		nPtsCount  = 0;
	}
}

//--------------------------------------------------------------------------------------------------------
CUiCurveGraphCtrl::CUiCurveGraphCtrl()
{
	m_CoordShow = CPoint(-1, -1);
	m_bFreeMove = false;
	m_bEnable = true;
	m_bShowPoint = true;
	m_bAddPoint = true;
	m_nMaxX = 100;
	m_nMinX = 0;
	m_nMaxY = 100;
	m_nMinY = 0;
	m_nAdjustMinX = m_nMinX;
	m_nAdjustMaxX = m_nMaxX;
	m_nAdjustMinY = m_nMinY;
	m_nAdjustMaxY = m_nMaxY;
	m_rcMargin = CRect(0, 0, 0, 0);
	m_nNumOfGraph = 0;
	m_bLButtonDown = false;
	m_pCurSel = NULL;
	m_pPreCur = NULL;
	m_pNextCur = NULL;
	m_pOrders = NULL;
	m_hCursor = NULL;
	m_pFont  = NULL;
	m_clrText = CLR_NONE;
	m_pArray.RemoveAll(); 
	m_adjustDir = UICGC_ADJUST_XYDIR;
	m_sXUnit = _T("");
	m_sYUnit = _T("");
	m_fXRatio = 1;
	m_fYRatio = 1;
}

CUiCurveGraphCtrl::~CUiCurveGraphCtrl()
{
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UICGC_GRAPH* pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			delete pGraph;   
		}
    }

	if(NULL != m_pOrders)
	{
		delete []m_pOrders;
		m_pOrders = NULL;
	}

	m_pArray.RemoveAll();
}


BEGIN_MESSAGE_MAP(CUiCurveGraphCtrl, CUiBase)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------------------
bool CUiCurveGraphCtrl::IsEnable()
{
	return m_bEnable;
}
//--------------------------------------------------------------------------------------------------------
bool CUiCurveGraphCtrl::IsEnable(int nIndex)
{
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			return pGraph->bEnable && m_bEnable;
		}
	}

	return false;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::Enable(bool bEnable)
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
void CUiCurveGraphCtrl::Enable(int nIndex, bool bEnable)
{
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			pGraph->bEnable = bEnable;;
			break;
		}
	}

	//If control is disabled during dragging
	if(!bEnable && m_bLButtonDown) 
	{
		ReleaseCapture();
		m_bLButtonDown = false;
	}

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::EnableLine(int nIndex, bool bLine)
{
	UICGC_GRAPH *pCurGraph = NULL;
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			pCurGraph = pGraph;
			break;
		}
	}
	pCurGraph->bLine = bLine;

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::ShowPoint(int nIndex, bool bShow) 
{ 
	UICGC_GRAPH* pGraph = (UICGC_GRAPH*)m_pArray.GetAt(nIndex);
	pGraph->bShowPoint = bShow; 
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetCursor(UINT nCursorId)
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
void CUiCurveGraphCtrl::SetAdjustDirection(UICGC_ADJUST_DIR dir)
{
	m_adjustDir = dir;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetMargin(int l, int t, int r, int b) 
{
	if(m_rcMargin != CRect(l, t, r, b))
	{
		CRect rcMn = m_rcMargin;
		m_rcMargin = CRect(l, t, r, b);

		ReAllocGraphData(rcMn, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::GetCoordXRange(int &nMin, int &nMax)        
{
	nMin = m_nMinX; 
	nMax = m_nMaxX;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetCoordXRange(int nMin, int nMax)         
{
	if(m_nMinX != nMin || m_nMaxX != nMax)
	{
		int nOldMin = m_nMinX;
		int nOldMax = m_nMaxX;

		m_nMinX = nMin; 
		m_nMaxX = nMax; 
		m_nMinX = (nMin > nMax) ? nMax : m_nMinX;
		m_nMaxX = (nMin > nMax) ? nMin : m_nMaxX;	

		ReAllocGraphData(m_rcMargin, nOldMin, nOldMax, m_nMinY, m_nMaxY, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::GetCoordYRange(int &nMin, int &nMax)        
{
	nMin = m_nMinY; 
	nMax = m_nMaxY;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetCoordYRange(int nMin, int nMax)         
{
	if(m_nMinY != nMin || m_nMaxY != nMax)
	{
		int nOldMin = m_nMinY;
		int nOldMax = m_nMaxY;

		m_nMinY = nMin; 
		m_nMaxY = nMax; 
		m_nMinY = (nMin > nMax) ? nMax : m_nMinY;
		m_nMaxY = (nMin > nMax) ? nMin : m_nMaxY;	

		ReAllocGraphData(m_rcMargin, m_nMinX, m_nMaxX, nOldMin, nOldMax, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetAdjustXRange(int nAdjustMin, int nAdjustMax)
{
	int nMin = (nAdjustMin < nAdjustMax) ? nAdjustMin : nAdjustMax;
	int nMax = (nAdjustMin < nAdjustMax) ? nAdjustMax : nAdjustMin;

	nMin = (nMin >= m_nMinX) ? nMin : m_nMinX;
	nMin = (nMin <= m_nMaxX) ? nMin : m_nMaxX;
	nMax = (nMax >= m_nMinX) ? nMax : m_nMinX;
	nMax = (nMax <= m_nMaxX) ? nMax : m_nMaxX;

	m_nAdjustMinX = nMin;
	m_nAdjustMaxX = nMax;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetAdjustYRange(int nAdjustMin, int nAdjustMax)
{
	int nMin = (nAdjustMin < nAdjustMax) ? nAdjustMin : nAdjustMax;
	int nMax = (nAdjustMin < nAdjustMax) ? nAdjustMax : nAdjustMin;

	nMin = (nMin >= m_nMinY) ? nMin : m_nMinY;
	nMin = (nMin <= m_nMaxY) ? nMin : m_nMaxY;
	nMax = (nMax >= m_nMinY) ? nMax : m_nMinY;
	nMax = (nMax <= m_nMaxY) ? nMax : m_nMaxY;

	m_nAdjustMinY = nMin;
	m_nAdjustMaxY = nMax;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::CreateGraph(int nIndex, int nLineWidth, COLORREF clrLine, COLORREF clrLineDisable)
{
	ASSERT(GetSafeHwnd() != NULL);
	ASSERT(nIndex >= 0 && nLineWidth > 0);
	
	BOOL bExisted = FALSE;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			bExisted = TRUE;
			break;
		}
    }

	if(bExisted) { return; }

	m_pArray.SetAtGrow(m_nNumOfGraph, new UICGC_GRAPH(nIndex, m_nNumOfGraph, nLineWidth, clrLine, clrLineDisable, NULL, 0)); // Set points to NULL first.
	m_nNumOfGraph++;

	if(NULL != m_pOrders)
	{
		delete []m_pOrders;
		m_pOrders = NULL;
	}

	m_pOrders = new int[m_nNumOfGraph];
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		m_pOrders[i] = ((UICGC_GRAPH*)m_pArray.GetAt(i))->nOrder;
	}

	Sort(m_pOrders, m_nNumOfGraph);
	SortGraph();
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::DeleteGraph(int nIndex)
{
	int nExisted = -1;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			nExisted = i;
			break;
		}
    }

	if(-1 == nExisted) { return; }

	UICGC_GRAPH* pGraph = (UICGC_GRAPH*)m_pArray.GetAt(nExisted);
	if(NULL != pGraph)
	{
		delete pGraph;
	}

	m_nNumOfGraph--;
	m_pArray.RemoveAt(nExisted, 1);

	m_pOrders = new int[m_nNumOfGraph];
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		m_pOrders[i] = ((UICGC_GRAPH*)m_pArray.GetAt(i))->nOrder;
	}

	Sort(m_pOrders, m_nNumOfGraph);
	SortGraph();

	InvalidateRect(NULL, FALSE); 
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetFont(CFont* pFont, COLORREF clrFont)
{
	m_pFont   = pFont;
	m_clrText = clrFont;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetValue(int nIndex, CPoint* pValues, int nCount)
{
	ASSERT(nCount  > 0);
	ASSERT(pValues != NULL);
	ASSERT(GetSafeHwnd() != NULL);

	// Peter Lee 2017/4/13 
	if (nCount > 0xffff)
		return;

	UICGC_GRAPH *pCurGraph = NULL;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			pCurGraph = pGraph;
			break;
		}
    }

	if(NULL == pCurGraph) { return; }

	if(NULL != pCurGraph->pGraphData)
	{
		delete[] pCurGraph->pGraphData;
		pCurGraph->nPtsCount  = 0;
		pCurGraph->pGraphData = NULL;
	}

	pCurGraph->pGraphData = new CPoint[80];
	if(NULL == pCurGraph->pGraphData)
	{
		return;
	}

	pCurGraph->nPtsCount = nCount;
	for(int i=0; i<nCount; ++i)
	{
		int nX = pValues[i].x;
		int nY = pValues[i].y;
		if(nX < m_nAdjustMinX) nX = m_nAdjustMinX;
		if(nX > m_nAdjustMaxX) nX = m_nAdjustMaxX;
		if(nY < m_nAdjustMinY) nY = m_nAdjustMinY;
		if(nY > m_nAdjustMaxY) nY = m_nAdjustMaxY;
		pCurGraph->pGraphData[i].x = nX;
		pCurGraph->pGraphData[i].y = nY;

		//pCurGraph->pGraphData[i].x = pValues[i].x;
		//pCurGraph->pGraphData[i].y = pValues[i].y;
		Val2Pixel(pCurGraph->pGraphData[i].x, pCurGraph->pGraphData[i].y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
	}

	CRect rcCli;
	GetClientRect(&rcCli);
	InvalidateRect(&rcCli, FALSE);  
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::GetValue(int nIndex, CPoint* pValues, int& nCount)
{
	ASSERT(nCount  > 0);
	ASSERT(pValues != NULL);
	ASSERT(GetSafeHwnd() != NULL);
	
	UICGC_GRAPH *pCurGraph = NULL;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			pCurGraph = pGraph;
			break;
		}
    }

	if(NULL == pCurGraph) { return; }

	if(NULL != pCurGraph->pGraphData)
	{
		int nNumOfPts = (nCount >= pCurGraph->nPtsCount) ? pCurGraph->nPtsCount : nCount;
		nCount = nNumOfPts;

		for(int i=0; i<nNumOfPts; ++i)
		{
			pValues[i].x = pCurGraph->pGraphData[i].x;
			pValues[i].y = pCurGraph->pGraphData[i].y;
			Pixel2Val(pValues[i].x, pValues[i].y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
		}
	}
	else
	{
		nCount = 0;
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetValueUnit(CString sXUnit, CString sYUnit)
{
	m_sXUnit = sXUnit;
	m_sYUnit = sYUnit;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SetValueRatio(float fXRatio, float fYRatio)
{
	m_fXRatio = fXRatio;
	m_fYRatio = fYRatio;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawGraphs(pDC, rcCli);

	if (m_CoordShow.x >= 0)
	{
		int nleft = m_CoordShow.x, ntop = m_CoordShow.y, nright = m_CoordShow.x + 90, nbottom = m_CoordShow.y + 50;
		CPoint realCoord = m_CoordShow;
		CString sCaption = _T("");
		CRect rcVaild, rcTxt; 
		GetClientRect(&rcVaild);
		rcVaild.DeflateRect(m_rcMargin);
		DWORD dwStyle = DT_LEFT;

		if(nright > rcVaild.right)
		{
			nleft = m_CoordShow.x - 90;
			nright = m_CoordShow.x;
			dwStyle = DT_RIGHT;
		}
		if(nbottom > rcVaild.bottom)
		{
			ntop = m_CoordShow.y - 50;
			nbottom = m_CoordShow.y;
		}
		rcTxt = CRect(nleft, ntop, nright, nbottom);

		Pixel2Val(realCoord.x, realCoord.y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
		sCaption.Format(_T("[%g%s,%g%s]"), realCoord.x * m_fXRatio, m_sXUnit, realCoord.y * m_fYRatio, m_sYUnit);

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

		pDC->DrawText(sCaption, &rcTxt, DT_SINGLELINE | DT_VCENTER | dwStyle);

		if(NULL != pOldFont)
		{
			pDC->SelectObject(pOldFont);
		}

	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::DrawGraphs(CDC* pDC, CRect rcCli)
{
	if(m_nNumOfGraph <= 0)
		return;

	for(int i = m_nNumOfGraph - 1; i>=0; i--)
    {
		BOOL bFound = FALSE;
		UICGC_GRAPH *pGraph = NULL;

		for(int j=0; j<m_nNumOfGraph; j++)
		{
			pGraph = (UICGC_GRAPH*)m_pArray.GetAt(j);
			if(m_pOrders[i] == pGraph->nOrder)
			{
				bFound = TRUE;
				break;
			}
		}

		if(bFound)
		{
			COLORREF clrLine = RGB(0, 0, 0);
			clrLine = ((m_bEnable && pGraph->bEnable)  && CLR_NONE != pGraph->clrLine) ? pGraph->clrLine : clrLine;
			clrLine = ((!m_bEnable || !pGraph->bEnable) && CLR_NONE != pGraph->clrLineDisable) ? pGraph->clrLineDisable : clrLine;
			clrLine = (!((UICGC_GRAPH*)m_pArray.GetAt(i))->bEnable && CLR_NONE != pGraph->clrLineDisable) ? pGraph->clrLineDisable : clrLine;

			//pDC->Polyline(pGraph->pGraphData, pGraph->nPtsCount);

			for(int j=0; j<pGraph->nPtsCount; j++)
			{
				CPen pen, *pOldPen = NULL;
				if(pGraph->clrLine != CLR_NONE || pGraph->nLineWidth > 1)
				{
					pen.CreatePen(PS_SOLID, pGraph->nLineWidth, clrLine);
					pOldPen = pDC->SelectObject(&pen);
				}

				if(j < pGraph->nPtsCount - 1 && pGraph->bLine)		
				{
					pDC->MoveTo(pGraph->pGraphData[j]);
					pDC->LineTo(pGraph->pGraphData[j + 1]);
				}

				int  w = pGraph->nLineWidth + 1;
				long x = pGraph->pGraphData[j].x;
				long y = pGraph->pGraphData[j].y;
				if(m_bShowPoint && pGraph->bShowPoint) pDC->Ellipse(CRect(x - w, y - w, x + w, y + w));

				if(pOldPen != NULL)
				{
					pDC->SelectObject(pOldPen);
					pen.DeleteObject();
				}
			}

		}
    }
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::Val2Pixel(long& x, long& y, CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY)  // x: [in, out], y: [in, out]
{
	CRect rcCli; 
	GetClientRect(&rcCli);
	rcCli.DeflateRect(rcMargin);

	x = (x > nMaxX) ? nMaxX : x; 
	x = (x < nMinX) ? nMinX : x;
	y = (y > nMaxY) ? nMaxY : y; 
	y = (y < nMinY) ? nMinY : y;

	double fRatioX = (nMaxX != nMinX) ? ((double)(x - nMinX) / (nMaxX - nMinX)) : 0.0;
	double fRatioY = (nMaxY != nMinY) ? ((double)(y - nMinY) / (nMaxY - nMinY)) : 0.0;

	x = (long)(rcCli.left   + rcCli.Width()  * fRatioX);
	y = (long)(rcCli.bottom - rcCli.Height() * fRatioY);
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::Pixel2Val(long& x, long& y, CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY)  // x: [in, out], y: [in, out]
{
	CRect rcCli; 
	GetClientRect(&rcCli);
	rcCli.DeflateRect(rcMargin);

	x = (long)(((double)(x  -  rcCli.left) / rcCli.Width())  * (nMaxX - nMinX) + nMinX + 0.5);
	y = (long)(((double)(rcCli.bottom - y) / rcCli.Height()) * (nMaxY - nMinY) + nMinY + 0.5);
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::ReAllocGraphData(CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY, 
										 CRect rcMarginNew, int nMinXNew, int nMaxXNew, int nMinYNew, int nMaxYNew)
{
	ASSERT(GetSafeHwnd());

	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			for(int j=0; j<pGraph->nPtsCount; ++j)
			{
				Pixel2Val(pGraph->pGraphData[j].x, pGraph->pGraphData[j].y, rcMargin, nMinX, nMaxX, nMinY, nMaxY);
				Val2Pixel(pGraph->pGraphData[j].x, pGraph->pGraphData[j].y, rcMarginNew, nMinXNew, nMaxXNew, nMinYNew, nMaxYNew);
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------
//Dragging is started
void CUiCurveGraphCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	m_pCurSel  = NULL;
	m_pPreCur  = NULL;
	m_pNextCur = NULL;
	m_bLButtonDown = false;   
	int nCurSel = PtInGraph(point, m_pCurSel, m_pPreCur, m_pNextCur);
	if(nCurSel < 0 || m_bMoveTotal)
	{
		m_LastDownPt = point;
		if (PtInLine(point))
		{
			if (nCurSel = PtInGraph(point, m_pCurSel, m_pPreCur, m_pNextCur) < 0)
			{
				return;
			}
		}
		else
			return;
	}

	if (!IsEnable(nCurSel))
	{
		m_pPreCur = m_pNextCur = m_pCurSel = NULL;
		return;
	}

	ActiveGraph(nCurSel);
	SetCapture();
	m_bLButtonDown = true;
	OnMouseMove(nFlags, point);
	Invalidate(FALSE);

	CUiBase::OnLButtonDown(nFlags, point);
}

void CUiCurveGraphCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	m_pCurSel  = NULL;
	m_pPreCur  = NULL;
	m_pNextCur = NULL;
	m_bLButtonDown = false;   
	int nCurSel = PtInGraph(point, m_pCurSel, m_pPreCur, m_pNextCur);
	if(nCurSel < 0)
	{
		return;
	}

	UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(nCurSel);
	ActiveGraph(nCurSel);

	if (pGraph->nPtsCount < 3)
	{
		return;
	}

	for (CPoint* pPt = m_pCurSel; pPt != &(pGraph->pGraphData[pGraph->nPtsCount - 1]); pPt++)
	{
		*pPt = *(pPt + 1);
	}
	pGraph->nPtsCount--;

	CWnd* pParent = GetParent();
	while(NULL != pParent)
	{
		if(pParent->SendMessage(WM_UI_GRAPHCTRL_REMOVE, GetDlgCtrlID(), NULL)) break;
		pParent = pParent->GetParent();
	}

	Invalidate(FALSE);

	CUiBase::OnRButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
// During dragging
void CUiCurveGraphCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) return;
	
	if(m_bLButtonDown)
	{
		if(NULL != m_pCurSel)
		{
			int nOffsetY = point.y - m_LastDownPt.y;
			int nOffsetX = point.x - m_LastDownPt.x;
			m_LastDownPt = point;

			CRect rcCli; 
			GetClientRect(&rcCli);
			rcCli.DeflateRect(m_rcMargin);
			if(!rcCli.PtInRect(point))
			{
				point.x = (point.x < rcCli.left)   ? rcCli.left   : point.x;
				point.x = (point.x > rcCli.right)  ? rcCli.right  : point.x;
				point.y = (point.y < rcCli.top)    ? rcCli.top    : point.y;
				point.y = (point.y > rcCli.bottom) ? rcCli.bottom : point.y;
			}

			// 限制当前点的移动范围. 即:
			// 1)当前点的X & Y坐标值必须大于等于同一线中前一个点的X & Y坐标值;
			// 2)当前点的X & Y坐标值必须小于等于同一线中后一个点的X & Y坐标值;
			// 3)当前点的X & Y坐标值必须在User指定的可调节的范围内. 默认情况下, 可调节范围为X OR Y轴的坐标范围.

			if(NULL != m_pPreCur)
			{
				point.x = (point.x >= m_pPreCur->x) ? point.x : m_pPreCur->x;
				if(!m_bFreeMove && !m_bMoveTotal) point.y = (point.y <= m_pPreCur->y) ? point.y : m_pPreCur->y;
			}

			if(NULL != m_pNextCur)
			{
				point.x = (point.x <= m_pNextCur->x) ? point.x : m_pNextCur->x;
				if(!m_bFreeMove && !m_bMoveTotal) point.y = (point.y >= m_pNextCur->y) ? point.y : m_pNextCur->y;
			}

			// 限制点可调节范围
			LONG nAdjustMinX = m_nAdjustMinX;
			LONG nAdjustMaxX = m_nAdjustMaxX;
			LONG nAdjustMinY = m_nAdjustMinY;
			LONG nAdjustMaxY = m_nAdjustMaxY;
			Val2Pixel(nAdjustMinX, nAdjustMinY, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
			Val2Pixel(nAdjustMaxX, nAdjustMaxY, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);

			LONG nTemp = nAdjustMinY;
			nAdjustMinY = nAdjustMaxY;
			nAdjustMaxY = nTemp;

			point.x = (point.x >= nAdjustMinX) ? point.x : nAdjustMinX;
			point.x = (point.x <= nAdjustMaxX) ? point.x : nAdjustMaxX;
			point.y = (point.y >= nAdjustMinY) ? point.y : nAdjustMinY;
			point.y = (point.y <= nAdjustMaxY) ? point.y : nAdjustMaxY;

			if (m_bMoveTotal)
			{
				int nCurSel = PtInGraph(*m_pCurSel, m_pCurSel, m_pPreCur, m_pNextCur);
				UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(nCurSel);

				if(pGraph->pGraphData[pGraph->nPtsCount - 1].y + nOffsetY <= nAdjustMaxY
				&& pGraph->pGraphData[pGraph->nPtsCount - 1].y + nOffsetY >= nAdjustMinY
				&& pGraph->pGraphData[0].y + nOffsetY >= nAdjustMinY
				&& pGraph->pGraphData[0].y + nOffsetY <= nAdjustMaxY
				&& (UICGC_ADJUST_YDIR == m_adjustDir || UICGC_ADJUST_XYDIR == m_adjustDir)) 
				{
					for (int m = 0; m < pGraph->nPtsCount; m++)
					{
						switch(m_adjustDir)
						{
						case UICGC_ADJUST_XDIR:		pGraph->pGraphData[m].x += nOffsetX; break;
						case UICGC_ADJUST_YDIR:		pGraph->pGraphData[m].y += nOffsetY; break;
						case UICGC_ADJUST_XYDIR:	pGraph->pGraphData[m].y += nOffsetY; break;
						}
					}
				}
			}
			else
			{
				// 限制点可调节方向
				switch(m_adjustDir)
				{
				case UICGC_ADJUST_XYDIR:	*m_pCurSel = point; break;
				case UICGC_ADJUST_XDIR:		m_pCurSel->x = point.x; break;
				case UICGC_ADJUST_YDIR:		m_pCurSel->y = point.y; break;
				}
			}

			CPoint CurPt = *m_pCurSel;

			Pixel2Val(CurPt.x, CurPt.y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);

			CWnd* pParent = GetParent();
			while(NULL != pParent)
			{
				if(pParent->SendMessage(WM_UI_GRAPHCTRL_MOVING, GetDlgCtrlID(), LPARAM(&CurPt))) break;
				pParent = pParent->GetParent();
			}

			Val2Pixel(CurPt.x, CurPt.y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);

			if (!m_bMoveTotal)
			{
				*m_pCurSel = CurPt;
			}

			::SetCursor(m_hCursor);
			Invalidate(FALSE);
		}
	}
	else  // Change cursor when mouse move to the point.
	{
		CPoint* pPtSel  = NULL;
		CPoint* pPtPre  = NULL;
		CPoint* pPtNext = NULL;
		if(PtInGraph(point, pPtSel, pPtPre, pPtNext) >= 0)
		{
			::SetCursor(m_hCursor);
			m_CoordShow = *pPtSel;
			Invalidate(FALSE);
		}
		else
		{
			m_CoordShow = CPoint(-1, -1);
			Invalidate(FALSE);
		}
	}

	CUiBase::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is finished
void CUiCurveGraphCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	ReleaseCapture();
	if(m_bLButtonDown)
	{
		CPoint CurPt = *m_pCurSel;
		Pixel2Val(CurPt.x, CurPt.y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);

		CWnd* pParent = GetParent();
		while(NULL != pParent)
		{
			if(pParent->SendMessage(WM_UI_GRAPHCTRL_MOVED, GetDlgCtrlID(), LPARAM(&CurPt))) break;
			pParent = pParent->GetParent();
		}

		Val2Pixel(CurPt.x, CurPt.y, m_rcMargin, m_nMinX, m_nMaxX, m_nMinY, m_nMaxY);
		if(!m_bMoveTotal) *m_pCurSel = CurPt;
	}
	m_bLButtonDown = false;
	m_pCurSel  = NULL;
	m_pPreCur  = NULL;
	m_pNextCur = NULL;
	Invalidate(FALSE);

	CUiBase::OnLButtonUp(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiCurveGraphCtrl::PtInLine(CPoint& point)
{
	int nIndex = -1;
	int nOrder = -1;
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			//for(int j=0; j<pGraph->nPtsCount; j++)
			for(int j=pGraph->nPtsCount - 1; j > 0; j--)
			{
				if(m_bMoveTotal || PtInLine(point, pGraph->pGraphData[j], pGraph->pGraphData[j - 1], pGraph->nLineWidth) && pGraph->nPtsCount < 80)
				{
					if(!m_bMoveTotal && m_bAddPoint && pGraph->bEnable)
					{
						for (int m = pGraph->nPtsCount; m >= j; m--)
						{
							pGraph->pGraphData[m] = pGraph->pGraphData[m - 1];
						}
						pGraph->nPtsCount ++;
						pGraph->pGraphData[j] = point;
					}
					else if(m_bMoveTotal)
					{
						point = pGraph->pGraphData[pGraph->nPtsCount - 1];
					}
					else
					{
						point = pGraph->pGraphData[j];
					}
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
//--------------------------------------------------------------------------------------------------------
BOOL CUiCurveGraphCtrl::PtInLine(const CPoint& point, CPoint PtBefore, CPoint PtAfter, int nLineWidth)
{
	double fPointY = PtAfter.y + (PtAfter.y - PtBefore.y) * (point.x - PtAfter.x) * 1.0 / (PtAfter.x - PtBefore.x);
	return point.x < PtBefore.x && 
		   point.x > PtAfter.x  && 
		   fabs(fPointY - point.y) < nLineWidth;
}
//--------------------------------------------------------------------------------------------------------
int CUiCurveGraphCtrl::PtInGraph(const CPoint& point, CPoint*& pPtCurIn, CPoint*& pPtPre, CPoint*& pPtNext)
{
	int nIndex = -1;
	int nOrder = -1;
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->bEnable)
		{
			//for(int j=0; j<pGraph->nPtsCount; j++)
			for(int j=pGraph->nPtsCount - 1; j >= 0; j--)
			{
				CRect rc(CPoint(pGraph->pGraphData[j].x - pGraph->nLineWidth - 1, pGraph->pGraphData[j].y - pGraph->nLineWidth - 1), 
						 CPoint(pGraph->pGraphData[j].x + pGraph->nLineWidth + 1, pGraph->pGraphData[j].y + pGraph->nLineWidth + 1));
				if(rc.PtInRect(point))
				{
					if(-1 == nIndex || nOrder > pGraph->nOrder)
					{
						nIndex = pGraph->nIndex;
						nOrder = pGraph->nOrder;
						pPtCurIn = &pGraph->pGraphData[j];
						pPtPre = (0 == j) ? NULL : &pGraph->pGraphData[j - 1];
						pPtNext = (pGraph->nPtsCount - 1 == j) ? NULL : &pGraph->pGraphData[j + 1];
					}
				}
			}
		}
	}

	return nIndex;
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::ActiveGraph(int nTopIndex)
{
	int nOrder = 0;
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		if(i == nTopIndex)
		{
			pGraph->nOrder = 0;
		}
		else
		{
			nOrder++;
			for(int j=0; j<m_nNumOfGraph; j++)
			{
				if(pGraph->nOrder == m_pOrders[j])
				{
					pGraph->nOrder = nOrder;
					break;
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::Sort(int* pData, int nCount)
{
	int nTemp = 0;
	for (int i=1; i<nCount; i++)
	{
		for (int j=0; j <nCount - i; j++)
		{
			if (pData[j] > pData[j + 1])
			{
				nTemp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = nTemp;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiCurveGraphCtrl::SortGraph()
{
	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UICGC_GRAPH *pGraph = (UICGC_GRAPH*)m_pArray.GetAt(i);
		for(int j=0; j<m_nNumOfGraph; j++)
		{
			if(pGraph->nOrder == m_pOrders[j])
			{
				pGraph->nOrder = i;
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------