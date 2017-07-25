#ifndef  _UI_CKBCTRL_H_
#define  _UI_CKBCTRL_H_

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiKeyboardCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件能
 *               将多个Item组合成一个控件，每次只有一个Item处于被选中状态，可以通过鼠标点击选中其他的Item。类似于
 *               CTabCtrl的页签。
 *                      
 *****************************************************************************************************************/
class UIKB_RECT		// using bitmap mode to display panel item.
{
public:
	DWORD uItemId;	 
	CRect rect;
	bool  bSel;
	
	UIKB_RECT();
	UIKB_RECT(DWORD id, CRect rect, bool sel = false);
	UIKB_RECT& operator = (const UIKB_RECT* pKbRect);
};

struct UI_KEYBOARD
{
	CWnd*       pParent;
	UINT        uId;
	CRect       rect;
	UINT        uBkBitmap;
	UINT        uHlBitmap;
	COLORREF    clrRect;
	COLORREF    clrMask;

	UI_KEYBOARD();
	UI_KEYBOARD(CWnd* parent, UINT id, CRect rcWin, UINT bkbmp=0, UINT hlbmp=0, COLORREF clrc = CLR_NONE, COLORREF mask=CLR_NONE);
	UI_KEYBOARD& operator = (const UI_KEYBOARD* pStatic);
};

class CUiKeyboardCtrl : public CUiBase
{
public:
	CUiKeyboardCtrl();
	virtual ~CUiKeyboardCtrl();
	
public:
	void     CreateKeyboard(UI_KEYBOARD uiStatic);
	void     ResetKeyboard(UI_KEYBOARD uiKeyboard);
	void     SetKeyboardBitmap(UINT nNormal, COLORREF clrMask);
	void     AddItem(UIKB_RECT* pItem);       // The item id is the order when it is adding into the panel.
	void     DeleteItem(int nIndex);          // 
	void     ResetAllItemStatus(); 
	int      GetAllItemStatus(bool nStatus[], int nCount);   // Get all item selected or not.
	int      GetAllSelectItem(int nStatus[], int& nCount);  // Get all selected item id.
	bool     GetItemStatus(int nIndex);						// Get item selected or not.
	void     SetItemStatus(int nIndex, bool bStatus);       // Set item selected.
	int      GetItemCount(); 
	void	 SetSingle(bool bSingle) { m_bSingle = bSingle; }
	void     SetCursor(UINT nCursorId);      
	void     Enable(bool bEnable=true);      
	bool     IsEnable();   	

protected:
	void	 DrawItems(CDC* pDC, CRect rcCli);
	virtual  void Draw(CDC* pDC, CRect rcCli);
	bool	 RectInRect(CRect rcSrc, CRect rcInc);


protected:
	int		   m_nItemSel;
	int		   m_nNumOfItems;
	int        m_nItemMouseIn;
	CPtrArray  m_pArray;
	CPtrArray  m_pLastArray;
	HCURSOR    m_hCursor;
	bool       m_bEnabled;
	bool       m_bDrop;
	bool       m_bSingle;
	UINT       m_uHlBmpId;
	UINT       m_uNormal;
	COLORREF   m_clrRect;
	COLORREF   m_clrMask;
	CPoint	   m_startPt;
	CPoint	   m_curPt;

	CToolTipCtrl m_toolTip;
	
protected:
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void    OnDestroy();
	 BOOL    OnToolTips(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


#endif 
