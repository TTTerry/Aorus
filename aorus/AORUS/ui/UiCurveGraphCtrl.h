#ifndef _UI_CCURVEGRAPH_H
#define _UI_CCURVEGRAPH_H

#include "UiBase.h"


enum UICGC_ADJUST_DIR
{
	UICGC_ADJUST_XYDIR = 0,	// allow to adjust both x and y direction. default setting. 
	UICGC_ADJUST_XDIR,		// allow to adjust x direction
	UICGC_ADJUST_YDIR,		// allow to adjust y direction
};

struct UICGC_GRAPH
{
	int         nIndex;
	int			nOrder;			// 仅供内部使用
	bool		bLine;			
	int         nLineWidth;
	COLORREF    clrLine;
	COLORREF	clrLineDisable;
	CPoint*		pGraphData;
	int			nPtsCount;
	bool        bEnable;
	bool        bShowPoint;

	 UICGC_GRAPH();
	 UICGC_GRAPH(int index, int nOrder, int width, COLORREF clrLine, COLORREF clrLineDisable, CPoint* pData, int nPtsCnt);
	~UICGC_GRAPH();
};

class CUiCurveGraphCtrl : public CUiBase
{
public:
	CUiCurveGraphCtrl();
	virtual ~CUiCurveGraphCtrl();

public:   
	void     CreateGraph(int nIndex, int nLineWidth=1, COLORREF clrLine=CLR_NONE/*Default color*/, COLORREF clrLineDisable=CLR_NONE/*Default color*/);
	void     DeleteGraph(int nIndex);
	void     SetFont(CFont* pFont, COLORREF clrFont=CLR_NONE);
	void     SetValue(int nIndex, CPoint* pValues, int  nCount);// Set line's coords according to X-Coord & Y-Coord's range. (X: left to right, Y: top to bottom).
	void	 GetValue(int nIndex, CPoint* pValues, int& nCount);
	void	 SetValueUnit(CString sXUnit = _T(""), CString sYUnit = _T(""));
	void	 SetValueRatio(float fXRatio = 1, float fYRatio = 1);
	void     GetCoordXRange(int &nMin, int &nMax);			
	void     SetCoordXRange(int  nMin, int  nMax);				// Set X-Coord's range. 
	void     GetCoordYRange(int &nMin, int &nMax);
	void     SetCoordYRange(int  nMin, int  nMax);				// Set Y-Coord's range. 
	void	 SetAdjustXRange(int nAdjustMin, int nAdjustMax);	// Set X-Coord's adjust range(According to X-Coord's range).
	void	 SetAdjustYRange(int nAdjustMin, int nAdjustMax);	// Set Y-Coord's adjust range(According to Y-Coord's range).
	void     SetMargin(int l, int t, int r, int b);
	void	 SetAdjustDirection(UICGC_ADJUST_DIR dir);
	void     SetCursor(UINT nCursorId);
	void     SetFreeMove(bool bFree) { m_bFreeMove = bFree; };
	void	 ShowPoint(bool bShow) { m_bShowPoint = bShow; };
	void	 ShowPoint(int nIndex, bool bShow);
	void	 MoveTotal(bool bMove) { m_bMoveTotal = bMove; };
	void	 AddPoint(bool bAdd) { m_bAddPoint = bAdd; };
	
	bool     IsEnable();
	bool     IsEnable(int nIndex);
	void     Enable(bool bEnable=true);
	void     Enable(int nIndex, bool bEnable=true);
	void     EnableLine(int nIndex, bool bLine=true);

protected:
	void     DrawGraphs(CDC* pDC, CRect rcCli);
	virtual  void  Draw(CDC* pDC, CRect rcCli);

	void     Val2Pixel(long& x, long& y, CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY);
	void     Pixel2Val(long& x, long& y, CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY);
	void     ReAllocGraphData(CRect rcMargin, int nMinX, int nMaxX, int nMinY, int nMaxY, 
		     CRect rcMarginNew, int nMinXNew, int nMaxXNew, int nMinYNew, int nMaxYNew);

	int      PtInGraph(const CPoint& point, CPoint*& pPtCurIn, CPoint*& pPtPre, CPoint*& pPtNext);
	BOOL	 PtInLine(CPoint& point);
	BOOL	 PtInLine(const CPoint& point, CPoint PtBefore, CPoint PtAfter, int nLineWidth);
	void	 ActiveGraph(int nIndex);
	void	 Sort(int* pOrders, int nCount);
	void     SortGraph();

protected:
	CPoint		 m_CoordShow;
	bool         m_bEnable;
	bool		 m_bShowPoint;
	bool		 m_bMoveTotal;
	bool		 m_bAddPoint;
	int          m_nMaxX;
	int          m_nMinX;
	int          m_nMaxY;
	int          m_nMinY;
	int			 m_nAdjustMinX;
	int			 m_nAdjustMaxX;
	int			 m_nAdjustMinY;
	int			 m_nAdjustMaxY;
	CRect        m_rcMargin;
	CPtrArray    m_pArray;
	int          m_nNumOfGraph;
	bool         m_bLButtonDown;
	CPoint*      m_pCurSel;		// m_pPreCur and m_pCurSel are both in the same line. 
	CPoint*      m_pPreCur;		// But m_pPreCur is the point which locates before m_pCurSel.
	CPoint*      m_pNextCur;
	CPoint       m_LastDownPt;
	int*		 m_pOrders;
	HCURSOR      m_hCursor;
	bool		 m_bFreeMove;
	UICGC_ADJUST_DIR m_adjustDir;
	CFont*		 m_pFont;
	COLORREF	 m_clrText;
	CString		 m_sXUnit;
	CString		 m_sYUnit;
	float		 m_fXRatio;
	float		 m_fYRatio;

protected:
	//{{AFX_MSG(CUiCurveGraphCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
