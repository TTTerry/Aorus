#ifndef  _UI_CPANELCTRL_H_
#define  _UI_CPANELCTRL_H_

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiPanelCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件能
 *               将多个Item组合成一个控件，每次只有一个Item处于被选中状态，可以通过鼠标点击选中其他的Item。类似于
 *               CTabCtrl的页签。
 *                      
 *****************************************************************************************************************/
class UIPC_IMAGE		// using bitmap mode to display panel item.
{
public:
	UINT     uNormal;	 
	UINT     uMouseIn;
	UINT     uSelect;
	UINT     uDisable;
	COLORREF clrMask;
	
	UIPC_IMAGE();
	// 没有选择，鼠标进入，选择
	UIPC_IMAGE(UINT normal, UINT mouseIn, UINT select, COLORREF mask=CLR_NONE);
	UIPC_IMAGE(UINT normal, UINT mouseIn, UINT select, UINT disable = 0, COLORREF mask=CLR_NONE);
	UIPC_IMAGE& operator = (const UIPC_IMAGE* pBmpMode);
};

class UIPC_STRING		// using string mode to display panel item.
{
public:
	CString	 sCaption;
	COLORREF clrNormal;
	COLORREF clrMouseIn;
	COLORREF clrSelect;
	COLORREF clrDisable;
	CFont*	 pFtNormal;
	CFont*   pFtMouseIn;
	CFont*   pFtSelect;
	CFont*   pFtDisable;
	CRect	 rect;
	DWORD	 dwAlign;	// text-align. See UiBase.h: ST_****
	
	UIPC_STRING();
	// 内容，颜色，鼠标经过的颜色，按下的颜色，字体，通常的字体，鼠标经过的字体，鼠标按下的字体
	UIPC_STRING(CString caption, COLORREF normal, COLORREF mouseIn, COLORREF select, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL);
	UIPC_STRING(CString caption, CRect rect, COLORREF normal, COLORREF mouseIn, COLORREF select, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL);
	UIPC_STRING(CString caption, DWORD align, CRect rect, COLORREF normal, COLORREF mouseIn, COLORREF select, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL);
	UIPC_STRING(CString caption, COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL, CFont* pDisable=NULL);
	UIPC_STRING(CString caption, CRect rect, COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL, CFont* pDisable=NULL);
	UIPC_STRING(CString caption, DWORD align, CRect rect, COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, CFont* pNormal=NULL, CFont* pMouseIn=NULL, CFont* pSelect=NULL, CFont* pDisable=NULL);
	UIPC_STRING& operator = (const UIPC_STRING* pStrMode);
};

class UIPC_ITEM			// panel item
{
public:
	UINT		uItemId;		
	CRect		rect;			// item location(offset) in the panel ctrl.
	UIPC_IMAGE	bmpMode;		// bitmap mode
	UIPC_STRING	strMode;		// string mode
	bool		bEnable;
	bool		bVisible;		// Show/Hide item
	
	UIPC_ITEM();
	//控件id，位置，图片，文字
	UIPC_ITEM(UINT id, CRect rc, UIPC_IMAGE* pBmpMode, UIPC_STRING* pStrMode=NULL);
	UIPC_ITEM& operator = (const UIPC_ITEM* pItem);
};

class CUiPanelCtrl : public CUiBase
{
public:
	CUiPanelCtrl();
	virtual ~CUiPanelCtrl();
	
public:
	void     AddItem(UIPC_ITEM* pItem);       // The item id is the order when it is adding into the panel.
	void     DeleteItem(int nIndex);          // Delete item by item index
	void	 DeleteItemById(UINT uItemId);	  // Delete item by item id	
	int      GetCurItem();                    // Get item selected. return Item Index.
	void     SetCurItem(int nIndex);          // Set item selected.
	void     SetCurItemById(UINT uItemId);	  // Set item Id selected.
	void	 SetItemVisible(int nIndex, bool bVisible);
	void	 SetItemVisibleById(UINT uItemId, bool bVisible);
	bool	 IsItemVisible(int nIndex);
	bool	 IsItemVisibleById(UINT uItemId);
	void	 EnableItem(int nIndex, bool bEnable=true);
	void     EnableItemById(UINT uItemId, bool bEnable=true); 
	bool	 IsItemEnable(int nIndex);
	bool	 IsItemEnableById(UINT uItemId);
	UIPC_ITEM* GetItem(int nIndex);
	UIPC_ITEM* GetItemById(UINT uItemId);
	int      GetItemCount();                 
	void     SetCursor(UINT nCursorId);      
	void     SetText(UIPC_STRING* pStrMode, int nId);      
	void	 Enable(bool bEnable=true);   
	bool     IsEnable();   
	void     SetToolTip(CString sTip, int nMaxTipWidth=0);	// set nMaxTipWidth to show mutilline text.
	CToolTipCtrl* GetToolTipCtrl();
	

protected:
	void	 DrawItems(CDC* pDC, CRect rcCli);
	virtual  void Draw(CDC* pDC, CRect rcCli);


protected:
	int		   m_nItemSel;
	int		   m_nNumOfItems;
	int        m_nItemMouseIn;
	CPtrArray  m_pArray;
	HCURSOR    m_hCursor;
	bool       m_bEnabled;

	CToolTipCtrl m_toolTip;
	
protected:
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void    OnDestroy();
	 BOOL    OnToolTips(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


#endif 
