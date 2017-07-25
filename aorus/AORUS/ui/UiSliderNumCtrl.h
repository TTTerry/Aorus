#ifndef _UI_SLIDERNUM_H
#define _UI_SLIDERNUM_H

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiSliderNumCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。
 *                   CUiSliderNumCtrl模拟类似Iphone手机的日期调整功能. 通过鼠标控制诸如日期、数字等等的选择与控制。
 *
 *****************************************************************************************************************/

class CUiSliderNumCtrl : public CUiBase
{
public:
	CUiSliderNumCtrl();
	virtual ~CUiSliderNumCtrl();

public:   
	void    SetCursor(UINT nCursorId);
	void	SetBitmap(UINT* pBmpIds, int nBmpCount, COLORREF mask=CLR_NONE);

protected:
	void     DrawGraphs(CDC* pDC, CRect rcCli);
	virtual  void  Draw(CDC* pDC, CRect rcCli);

	void	 Slide();
	static	 DWORD ThreadProc(LPVOID lpParameter);
	void	RecalPosition(CRect rcRollZone);
	int 	GetPadding(CRect rcCli, int nSlideDirection=0);
	
protected:
	bool	 m_bLButtonDown;
	HCURSOR  m_hCursor;
	int		 m_nMoveSpeed;

	int		 m_nBmpCnt;
	UINT*	 m_pBmpIds;		
	int		 m_nTop;		//Bmps的起始位置
	int		 m_nCenter;	    //Bmps最后的停靠位置(Y轴)
	CDC		 m_MemDC;		//存储Bmps的DC
	CRect	 m_rcBmps;		//存储Bmps的总体位置
	CRect    m_rcCli;		
	CPoint   m_ptOffset;	//记录鼠标点击后每次的移动距离 
	COLORREF m_clrMask;
	CRect*	 m_pBmpLocs;	//Bmps最后各自的显示位置
	int		 m_nBmpH;		//Bmp的图片高度
	
protected:
	//{{AFX_MSG(CUiSliderNumCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
