#ifndef _UI_CTABCTRL_H
#define _UI_CTABCTRL_H

#include "UiBase.h"

struct UITC_ARROW
{
	UINT     uNormal;
	UINT     uMouseIn;
	UINT     uSelect;
	UINT     uDisable;
	COLORREF clrMask;

	UITC_ARROW();
	UITC_ARROW(UINT normal, UINT mouseIn, UINT select, UINT disable, COLORREF mask=CLR_NONE);
	UITC_ARROW& operator = (const UITC_ARROW* pArrow);
};

struct UITC_TAB
{
	CWnd*    pParent;
	UINT     uNormal;
	UINT     uMouseIn;
	UINT     uSelect;
	COLORREF clrMask;

	UITC_TAB();
	UITC_TAB(CWnd* parent, UINT normal, UINT mouseIn, UINT select, COLORREF mask=CLR_NONE);
	UITC_TAB& operator = (const UITC_TAB* pTab);
};

struct UITC_CONTAINER    //tab container
{
	int  nIndexTab;
	CRect rcTab;

	UITC_CONTAINER();
};


class CUiTabCtrl : public CUiBase
{
public:
	CUiTabCtrl();
	virtual ~CUiTabCtrl();

public:
	void     AddTab(UITC_TAB* pTab);
	void     SetArrow(UITC_ARROW* pLArrow, UITC_ARROW* pRArrow);
	void     DeleteTab(int nIndex);
	int      GetCurTab();
	void     SetCurTab(int nTabIndex);
	int      GetTabCount();
	void     SetPadding(int nPad);

	void     SetCursor(UINT nCursorId);


protected:
	void	DrawTabs(CDC* pDC, CRect rcCli);
	virtual void Draw(CDC* pDC, CRect rcCli);	
	virtual void RecalLayout();

protected:
	int         m_nPadding;
	int		    m_nContainerSel;
	int         m_nContainerMouseIn;
	int         m_nNumOfContainer;
	int		    m_nNumOfTabs;
	UITC_CONTAINER* m_pContainer;
	UITC_ARROW* m_pLArrow;
	UITC_ARROW* m_pRArrow;
	
	CSize       m_szTab;
	CSize       m_szArrow;
	CRect       m_rcArrow[2];
	CPtrArray   m_pArray;
	HCURSOR     m_hCursor;
	
protected:
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void    OnDestroy();
DECLARE_MESSAGE_MAP()





/*

struct TAB_COLOR 
{
	COLORREF clrNormal [2];     //High AND Low
	COLORREF clrSelect [2];
	COLORREF clrMouseIn[2];

	TAB_COLOR();
	TAB_COLOR& operator = (const TAB_COLOR* pColor);
};

class CUiTabCtrl : public CUiBase
{
public:
	CUiTabCtrl();
	virtual ~CUiTabCtrl();

public:
	void	 AddTab(CWnd* pParent, CString strCaption, UINT uIcon);
	void     DeleteTab(int nIndex);
	int      GetCurTab();
	void     SetCurTab(int nIndex);
	int      GetTabCount();
	void     SetPadding(int nPad);
	void     SetTabSize(CSize szTab);

	void     SetBorderColor(COLORREF clrBorder);
	void     GetTabColor(TAB_COLOR &clrTab);
	void     SetTabColor(TAB_COLOR  clrTab);
	CFont*   GetFont();
	void     SetFont(CFont* pFont);
	void     SetCursor(UINT nCursorId);


protected:
	void    DrawBorder(CDC* pDC, CRect rcCli);
	void	DrawTabs  (CDC* pDC, CRect rcCli);
	virtual void RecalLayout();
	virtual void Draw(CDC* pDC, CRect rcCli);	

protected:
	int		   m_nTabSel;
	int		   m_nNumOfTabs;
	int        m_nPadding;
	int        m_nTabMouseIn;
	CSize      m_szTab;
	CRect      m_rcAllTabs;
	CPtrArray  m_pArray;
	COLORREF   m_clrBorder;
	TAB_COLOR  m_clrTab;
	HCURSOR    m_hCursor;
	CFont*     m_pFont;
	
protected:
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void    OnDestroy();
DECLARE_MESSAGE_MAP()
*/
};

#endif 
