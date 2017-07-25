#ifndef _UI_ANGLE_H
#define _UI_ANGLE_H

#include "UiBase.h"

struct UI_ANGLE
{
	CWnd*		pParent;
	UINT		uId;
	CRect		rect;
	COLORREF    clrLine;
	COLORREF	clrLineDisable;
	UINT		uBkNormal;
	UINT		uBkDisable;
	COLORREF	clrMask;

	 UI_ANGLE();
	 UI_ANGLE(CWnd* parent, UINT id, CRect rcWin, COLORREF clrLine, COLORREF clrLineDisable, UINT nNormal, UINT nDisable, COLORREF clrMask=CLR_NONE);
};

class CUiAngleCtrl : public CUiBase
{
public:
	CUiAngleCtrl();
	virtual ~CUiAngleCtrl();

public:   
	void     CreateAngle(UI_ANGLE angle);
	void     SetValue(int nAngle);// Set line's coords according to X-Coord & Y-Coord's range. (X: left to right, Y: top to bottom).
	int		 GetValue();
	void	 SetLineWidth(int nWidth);
	void     SetCursor(UINT nCursorId);
	
	bool     IsEnable();
	void     Enable(bool bEnable=true);

protected:
	void     DrawGraphs(CDC* pDC, CRect rcCli);
	virtual  void  Draw(CDC* pDC, CRect rcCli);

	bool     PtInMovePoint(const CPoint& point);
	bool	 PtInLine(const CPoint& point);

protected:
	bool         m_bEnable;
	CPoint		 m_Center;
	CPoint		 m_Move;
	int			 m_nLineWidth;
	int			 m_nLength;
	COLORREF     m_clrLine;
	COLORREF	 m_clrLineDisable;
	HCURSOR      m_hCursor;
	bool		 m_bLButtonDown;
	UICGC_ADJUST_DIR m_adjustDir;

protected:
	//{{AFX_MSG(CUiCurveGraphCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
