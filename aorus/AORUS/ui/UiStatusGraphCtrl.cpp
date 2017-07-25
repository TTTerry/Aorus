#include "stdafx.h"
#include "UiStatusGraphCtrl.h"
#include "UiCommon.h"

DATA::DATA()
{
	Value = 0;
	Next  = NULL;
}
//--------------------------------------------------------------------------------------------------------
CGraphData::CGraphData() { Init(); }
CGraphData::CGraphData(int size) { Init(); Alloc(size); }
CGraphData::~CGraphData() { Release(); }

void CGraphData::Init()
{
	m_nMin   = 0;
	m_nMax   = 0;
	m_nSize  = 0;
	m_pLeft  = NULL; 
	m_pRight = NULL;
	m_nNumOfValid = 0;
}

void CGraphData::Alloc(int size)
{
	if(NULL == m_pLeft && NULL == m_pRight)
	{
		for(int i=0; i<size; i++)
		{
			DATA* pData = new DATA; 
			if(0 == i) 
			{
				m_pLeft  = pData;
				m_pRight = pData;
			}
			else
			{
				m_pRight->Next = pData;
				m_pRight = pData;
			}
		}
		
		m_nSize = size;
		m_nNumOfValid = 0;
	}
}

void CGraphData::Release()
{
	while(NULL != m_pLeft)
	{
		DATA *pData = m_pLeft->Next;
		delete m_pLeft;
		m_pLeft = pData;
	}

	Init();
}

void CGraphData::InsertValue(long value, int realValue)
{
	if(NULL != m_pLeft && NULL != m_pRight)
	{
		DATA* pData  = new DATA;
		pData->Next  = NULL;
		pData->Value = value;
		pData->realValue = realValue;

		if(m_nMin > value) { m_nMin = value; }
		if(m_nMax < value) { m_nMax = value; }

		//insert note at right
		m_pRight->Next = pData;
		m_pRight = pData;

		//delete note at left
		pData = m_pLeft;
		m_pLeft = m_pLeft->Next;
		delete pData;

		if(m_nNumOfValid < m_nSize)
		{
			m_nNumOfValid++;
		}
	}
}
LONG  CGraphData::GetMinValue()   { return m_nMin; }
LONG  CGraphData::GetMaxValue()   { return m_nMax; }
int   CGraphData::GetSize()       { return m_nSize; }
int   CGraphData::GetNumOfValid() { return m_nNumOfValid; }
DATA* CGraphData::GetLeft()       { return m_pLeft; }
DATA* CGraphData::GetRight()      { return m_pRight; }
	
//--------------------------------------------------------------------------------------------------------
UISGC_GRAPH::UISGC_GRAPH()
{
	nIndex     = -1;
	nLineWidth =  0;
	clrLine    = CLR_NONE;
	pGraphData = NULL;
}
UISGC_GRAPH::UISGC_GRAPH(int index, int width, COLORREF line, CGraphData* pData)
{
	nIndex     = index;
	nLineWidth = width;
	clrLine    = line;
	pGraphData = pData;
}
UISGC_GRAPH::~UISGC_GRAPH()
{
	if(pGraphData != NULL)
	{
		pGraphData->Release();
		delete pGraphData;
	}
}

//--------------------------------------------------------------------------------------------------------
CUiStatusGraphCtrl::CUiStatusGraphCtrl()
{
	m_bEnable         = true;
	m_nMax            = 100;
	m_nMin            = 0;
	m_nSampleInterval = 2;
	m_rcValuePos      = CRect(0, 0, 0, 0);
	m_rcMargin        = CRect(0, 0, 0, 0);
	m_nNumOfGraph     = 0;
	m_pArray.RemoveAll(); 
}

CUiStatusGraphCtrl::~CUiStatusGraphCtrl()
{
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH* pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			delete pGraph;   
		}
    }

	m_pArray.RemoveAll();
}


BEGIN_MESSAGE_MAP(CUiStatusGraphCtrl, CUiBase)
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------------------
int CUiStatusGraphCtrl::GetSampleInterval()
{
	return m_nSampleInterval;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::SetSampleInterval(int nInterval)
{
	if(nInterval != m_nSampleInterval && nInterval > 0)
	{
		m_nSampleInterval = nInterval;
		ReAllocGraphData();
	}
}
//--------------------------------------------------------------------------------------------------------
bool CUiStatusGraphCtrl::IsEnable()
{
	return m_bEnable;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::Enable(bool bEnable)
{
	m_bEnable = bEnable;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::SetMargin(int l, int t, int r, int b) 
{
	if(m_rcMargin != CRect(l, t, r, b))
	{
		m_rcMargin = CRect(l, t, r, b);
		ReAllocGraphData();
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::GetRange(int &nMin, int &nMax)        
{
	nMin = m_nMin; 
	nMax = m_nMax;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::SetRange(int nMin, int nMax)         
{
	if(m_nMin != nMin || m_nMax != nMax)
	{
		m_nMin = nMin; 
		m_nMax = nMax; 
		m_nMin = (nMin > nMax) ? nMax : m_nMin;
		m_nMax = (nMin > nMax) ? nMin : m_nMax;	

		ReAllocGraphData();
	}
}
//--------------------------------------------------------------------------------------------------------
bool CUiStatusGraphCtrl::IsGraphExisted(int nIndex)
{
	ASSERT(GetSafeHwnd() != NULL);
	ASSERT(nIndex >= 0);
	
	bool bExisted = false;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			bExisted = true;
			break;
		}
    }

	return bExisted;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::CreateGraph(int nIndex, int nLineWidth, COLORREF clrLine)
{
	ASSERT(GetSafeHwnd() != NULL);
	ASSERT(nIndex >= 0 && nLineWidth > 0);
	
	BOOL bExisted = FALSE;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			bExisted = TRUE;
			break;
		}
    }

	if(bExisted) { return; }

	CRect rcCli;
	GetClientRect(&rcCli);
	rcCli.DeflateRect(m_rcMargin);
	CGraphData* pData = new CGraphData(rcCli.Width() / m_nSampleInterval + 1);

	m_pArray.SetAtGrow(m_nNumOfGraph, new UISGC_GRAPH(nIndex, nLineWidth, clrLine, pData));
	m_nNumOfGraph++;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::DeleteGraph(int nIndex)
{
	int nExisted = -1;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			nExisted = i;
			break;
		}
    }

	if(-1 == nExisted) { return; }

	UISGC_GRAPH* pGraph = (UISGC_GRAPH*)m_pArray.GetAt(nExisted);
	if(NULL != pGraph)
	{
		delete pGraph;
	}

	m_nNumOfGraph--;
	m_pArray.RemoveAt(nExisted, 1);

	InvalidateRect(NULL, FALSE); 
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::SetValue(int nIndex, int nValue) 
{
	ASSERT(GetSafeHwnd() != NULL);

	UISGC_GRAPH *pCurGraph = NULL;
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph && pGraph->nIndex == nIndex)
		{
			pCurGraph = pGraph;
			break;
		}
    }

	if(NULL == pCurGraph) { return; }

	int nDrawValue = 0;

	nDrawValue = (nValue > m_nMax) ? m_nMax : nValue; 
	nDrawValue = (nValue < m_nMin) ? m_nMin : nValue;
	int nLoc = Val2Pixel(nDrawValue);
	pCurGraph->pGraphData->InsertValue(nLoc, nValue);

	CRect rcCli;
	GetClientRect(&rcCli);
	rcCli.top    = pCurGraph->pGraphData->GetMinValue() - 1;
	rcCli.bottom = pCurGraph->pGraphData->GetMaxValue() + 1;

	InvalidateRect(&rcCli, FALSE);  
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::GetMaxMinValue(int &nmin, int &nmax)
{
	UISGC_GRAPH *pCurGraph = NULL;
	nmin=0;
	nmax=0;

	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			CGraphData* pGraphData = pGraph->pGraphData;

			int nNumOfPoints = 0;
			//rcCli.DeflateRect(m_rcMargin);
			if(NULL != pGraphData)
			{
				nNumOfPoints = pGraphData->GetNumOfValid();
			}

			if(nNumOfPoints <= 0) { continue; }

			DATA* pData = pGraphData->GetLeft();
			int nLoop = pGraphData->GetSize() - nNumOfPoints;
			while(nLoop > 0)
			{
				pData = pData->Next;
				nLoop--;
			}

			nmin=pData->realValue;
			nmax=pData->realValue;
			int value=0;

			for(int i = nNumOfPoints - 1; i >= 0; i--)
			{
				value = pData->realValue;
				nmax = nmax > value ? nmax : value;
				nmin = nmin < value ? nmin : value;
				pData = pData->Next;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::SetFont(CFont* pFont, COLORREF clrFont)
{
	m_pFont   = pFont;
	m_clrText = clrFont;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::ShowValue(CRect rc)
{
	m_rcValuePos = rc;
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawGraphs(pDC, rcCli);
}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::DrawGraphs(CDC* pDC, CRect rcCli)
{
	pDC->SetBkMode(TRANSPARENT);
    for(int i=0; i<m_nNumOfGraph; i++)
    {
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			CGraphData* pGraphData = pGraph->pGraphData;

			int nNumOfPoints = 0;
			rcCli.DeflateRect(m_rcMargin);
			if(NULL != pGraphData)
			{
				nNumOfPoints = pGraphData->GetNumOfValid();
			}

			if(nNumOfPoints <= 0) { continue; }
			
			DATA* pData = pGraphData->GetLeft();
			int nLoop = pGraphData->GetSize() - nNumOfPoints;
			while(nLoop > 0)
			{
				pData = pData->Next;
				nLoop--;
			}

			CPoint* pt = new CPoint[nNumOfPoints];
			
			int nLastData = 0, nLastPos = 0;
			for(int i = nNumOfPoints - 1; i >= 0; i--)
			{
				pt[i].x = rcCli.Width() - i * m_nSampleInterval + rcCli.left;
				nLastPos = pt[i].y = pData->Value;
				nLastData = pData->realValue;
				pData = pData->Next;
			}

			CPen pen, *pOldPen = NULL;
			if(pGraph->clrLine != CLR_NONE || pGraph->nLineWidth > 1)
			{
				pen.CreatePen(PS_SOLID, pGraph->nLineWidth, (CLR_NONE == pGraph->clrLine) ? RGB(0, 0, 0) : pGraph->clrLine);
				pOldPen = pDC->SelectObject(&pen);
			}
			pDC->Polyline(pt, nNumOfPoints);
			if(pOldPen != NULL)
			{
				pDC->SelectObject(pOldPen);
				pen.DeleteObject();
			}

			delete []pt;

			if(m_rcValuePos.Width() > 0)
			{
				CString sCaption;
				sCaption.Format(_T("%d"), nLastData);
				CFont* pOldFont = NULL; 
				if(NULL != m_pFont)
				{
					pOldFont = pDC->SelectObject(m_pFont);
				}
				if(m_clrText != CLR_NONE)
				{
					pDC->SetTextColor(m_clrText);
				}

				CRect rcText = CRect(m_rcValuePos.left, nLastPos - m_rcValuePos.Height(), m_rcValuePos.right, nLastPos);
				if((nLastPos - rcCli.top) <= 0) 
					rcText = CRect(m_rcValuePos.left, nLastPos, m_rcValuePos.right, nLastPos + m_rcValuePos.Height());

				pDC->FillSolidRect(CRect(m_rcValuePos.left, 0, m_rcValuePos.right, rcCli.Height()), RGB(0, 0, 0));

				pDC->DrawText(sCaption, &rcText, DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS);


				if(NULL != pOldFont)
				{
					pDC->SelectObject(pOldFont);
				}
			}
		}
    }
}
//--------------------------------------------------------------------------------------------------------
int CUiStatusGraphCtrl::Val2Pixel(int nValue)
{
	CRect rcCli; 
	GetClientRect(&rcCli);
	rcCli.DeflateRect(m_rcMargin);

	double fRatio = (m_nMax != m_nMin) ? ((double)(nValue - m_nMin) / (m_nMax - m_nMin)) : 0.0;

	return (int)(rcCli.bottom - rcCli.Height() * fRatio);
}
int CUiStatusGraphCtrl::Pixel2Val(int pixel)
{
	CRect rcCli; 
	GetClientRect(&rcCli);
	rcCli.DeflateRect(m_rcMargin);
    double fRatio=(rcCli.top != rcCli.bottom) ? ((double)(rcCli.bottom-pixel) / rcCli.Height()) : 0.0;
	return (int)(m_nMin+(m_nMax-m_nMin)*fRatio);

}
//--------------------------------------------------------------------------------------------------------
void CUiStatusGraphCtrl::ReAllocGraphData()
{
	ASSERT(GetSafeHwnd());

	CRect rcCli;
	GetClientRect(&rcCli);
	rcCli.DeflateRect(m_rcMargin);

	for(int i=0; i<m_nNumOfGraph; i++)
	{
		UISGC_GRAPH *pGraph = (UISGC_GRAPH*)m_pArray.GetAt(i);
		if(NULL != pGraph)
		{
			pGraph->pGraphData->Release();
			pGraph->pGraphData->Alloc(rcCli.Width() / m_nSampleInterval + 1);
		}
	}
}
//--------------------------------------------------------------------------------------------------------
