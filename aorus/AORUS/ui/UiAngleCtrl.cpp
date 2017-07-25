#include "stdafx.h"
#include "UiAngleCtrl.h"
#include "UiCommon.h"
#include <math.h>
	
//--------------------------------------------------------------------------------------------------------
UI_ANGLE::UI_ANGLE()
{
	pParent = NULL;
	uId = 0;
	rect = CRect(0, 0, 0, 0);
	clrLine = CLR_NONE;
	clrLineDisable = CLR_NONE;
	uBkNormal = 0;
	uBkDisable = 0;
	clrMask = CLR_NONE;
}

UI_ANGLE::UI_ANGLE(CWnd* parent, UINT id, CRect rcWin, COLORREF line, COLORREF linedisable, UINT nNormal, UINT nDisable, COLORREF mask)
{
	pParent = parent;
	uId = id;
	rect = rcWin;
	clrLine = line;
	clrLineDisable = linedisable;
	uBkNormal = nNormal;
	uBkDisable = nDisable;
	clrMask = mask;
}

//--------------------------------------------------------------------------------------------------------
CUiAngleCtrl::CUiAngleCtrl()
{
	m_bEnable = true;
	m_Center = CPoint(0, 0);
	m_Move = CPoint(0, 0);
	m_nLineWidth = 2;
	m_nLength = 0;
	m_clrLine = CLR_NONE;
	m_clrLineDisable = CLR_NONE;
	m_bLButtonDown = false;
}

CUiAngleCtrl::~CUiAngleCtrl()
{
}


BEGIN_MESSAGE_MAP(CUiAngleCtrl, CUiBase)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------------------
bool CUiAngleCtrl::IsEnable()
{
	return m_bEnable;
}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::Enable(bool bEnable)
{
	m_bEnable = bEnable;

	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::SetCursor(UINT nCursorId)
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
void CUiAngleCtrl::CreateAngle(UI_ANGLE angle)
{
	Create(angle.pParent, angle.uId, angle.rect);

	m_Center = CPoint(angle.rect.Width() / 2, angle.rect.Height() / 2);
	m_Move = CPoint(angle.rect.Width() - 5, angle.rect.Height() / 2);
	m_nLength = angle.rect.Width() / 2 - 5;
	m_clrLine = angle.clrLine;
	m_clrLineDisable = angle.clrLineDisable;

}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::SetValue(int nAngle)
{
	nAngle = (nAngle + 90) % 360;
	int x = (int)(sin(nAngle / 180.0 * 3.14159265358979323846) * m_nLength);
	int y = (int)(cos(nAngle / 180.0 * 3.14159265358979323846) * m_nLength);

	x += m_Center.x;
	y += m_Center.y;

	m_Move = CPoint(x, y);
	Invalidate(FALSE);
}
//--------------------------------------------------------------------------------------------------------
int CUiAngleCtrl::GetValue()
{
	int x0 = m_Move.x - m_Center.x;
	int y0 = m_Move.y - m_Center.y;
	int nAngle = (int)(-atan2((double)y0, (double)x0) / 3.14159265358979323846 * 180);
	if(y0 >= 0) nAngle += 360;
	if(360 == nAngle) nAngle = 0;
	return nAngle;
}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::SetLineWidth(int nWidth)
{
	m_nLineWidth = nWidth;
}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::Draw(CDC* pDC, CRect rcCli)
{
	DrawGraphs(pDC, rcCli);
}
//--------------------------------------------------------------------------------------------------------
void CUiAngleCtrl::DrawGraphs(CDC* pDC, CRect rcCli)
{
	COLORREF clrLine = RGB(0, 0, 0);
	clrLine = (m_bEnable  && CLR_NONE != m_clrLine) ? m_clrLine : clrLine;
	clrLine = (!m_bEnable && CLR_NONE != m_clrLineDisable) ? m_clrLineDisable : clrLine;

	CPen pen, *pOldPen = NULL;
	if(m_clrLine != CLR_NONE || m_nLineWidth > 1)
	{
		pen.CreatePen(PS_SOLID, m_nLineWidth, clrLine);
		pOldPen = pDC->SelectObject(&pen);
	}

	CBrush BkBrush(RGB(0, 0, 0));
	CBrush *pOldBrush = pDC->SelectObject(&BkBrush);  
	pDC->Ellipse(CRect(m_Center.x - m_nLength, m_Center.y - m_nLength, m_Center.x + m_nLength, m_Center.y + m_nLength));

	if(pOldBrush != NULL)
	{
		pDC->SelectObject(pOldBrush);
		BkBrush.DeleteObject();
	}

	CBrush cenBrush(clrLine);
	pOldBrush = pDC->SelectObject(&cenBrush);  

	pDC->Ellipse(CRect(m_Center.x - 3, m_Center.y - 3, m_Center.x + 3, m_Center.y + 3));

	if(pOldBrush != NULL)
	{
		pDC->SelectObject(pOldBrush);
		cenBrush.DeleteObject();
	}

	pDC->MoveTo(m_Center);
	pDC->LineTo(m_Move);

	if(pOldPen != NULL)
	{
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}

	int  w = m_nLineWidth + 1;
	long x = m_Move.x;
	long y = m_Move.y;
	pDC->Ellipse(CRect(x - w, y - w, x + w, y + w));

}
//--------------------------------------------------------------------------------------------------------
//Dragging is started
void CUiAngleCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	m_bLButtonDown = false;   
	if(!PtInLine(point))
	{
		return;
	}

	SetCapture();
	m_bLButtonDown = true;
	OnMouseMove(nFlags, point);
	Invalidate(FALSE);

	CUiBase::OnLButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
// During dragging
void CUiAngleCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) return;
	
	if(m_bLButtonDown)
	{
		int y0 = point.y - m_Center.y;
		int x0 = point.x - m_Center.x;
		int y = (int)(sqrt(double(m_nLength * m_nLength * y0 * y0 * 1.0) / (y0 * y0 + x0 * x0)));
		int x = (int)(sqrt(double(m_nLength * m_nLength * x0 * x0 * 1.0) / (y0 * y0 + x0 * x0)));

		if (point.x < m_Center.x) x = -x;
		if (point.y < m_Center.y) y = -y;

		x += m_Center.x;
		y += m_Center.y;

		m_Move = CPoint(x, y);


		CWnd* pParent = GetParent();
		while(NULL != pParent)
		{
			if(pParent->SendMessage(WM_UI_ANGLE_CHANGE, GetDlgCtrlID(), GetValue())) break;
			pParent = pParent->GetParent();
		}

		Invalidate(FALSE);
	}
	else  // Change cursor when mouse move to the point.
	{
		if(PtInMovePoint(point) && m_hCursor != NULL)
		{
			::SetCursor(m_hCursor);
		}
	}

	CUiBase::OnMouseMove(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
//Dragging is finished
void CUiAngleCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(!m_bEnable) { return; }

	ReleaseCapture();
	OnMouseMove(nFlags, point);
	m_bLButtonDown = false;
	Invalidate(FALSE);

	CUiBase::OnLButtonUp(nFlags, point);
}
//--------------------------------------------------------------------------------------------------------
bool CUiAngleCtrl::PtInLine(const CPoint& point)
{
	float nY = (float)sqrt((double)m_nLength * m_nLength - (point.x - m_Center.x) * (point.x - m_Center.x));
	float nX = (float)sqrt((double)m_nLength * m_nLength - (point.y - m_Center.y) * (point.y - m_Center.y));

	if (point.x < m_Center.x) nX = -nX;
	if (point.y < m_Center.y) nY = -nY;

	nX += m_Center.x;
	nY += m_Center.y;

	return (fabs(nY - point.y) < m_nLineWidth + 5) || (fabs(nX - point.x) < m_nLineWidth + 5);
}
//--------------------------------------------------------------------------------------------------------
bool CUiAngleCtrl::PtInMovePoint(const CPoint& point)
{
	float nY = (float)sqrt((double)m_nLength * m_nLength - (point.x - m_Center.x) * (point.x - m_Center.x)) + m_Center.y;

	if (point.y < m_Center.y) nY = -nY;

	CRect rc(m_Move.x - (m_nLineWidth + 1) / 2, 
			 m_Move.y - (m_nLineWidth + 1) / 2, 
			 m_Move.x + (m_nLineWidth + 1) / 2, 
			 m_Move.y + (m_nLineWidth + 1) / 2);

	return (rc.PtInRect(point) == TRUE) ? true : false;
}
//--------------------------------------------------------------------------------------------------------