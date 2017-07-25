#ifndef _UI_CCOMBOBOX_H
#define _UI_CCOMBOBOX_H

/*****************************************************************************************************************
 *
 * CUiComboBox: 整合了MFC中的CButton和CListBox类，构建了自定义组合框类。
 *
 *****************************************************************************************************************/
#define ST_TOP          0x00000001
#define ST_LEFT         0x00000002
#define ST_CENTER       0x00000004
#define ST_RIGHT        0x00000008
#define ST_VCENTER      0x00000010
#define ST_BOTTOM       0x00000020
#define ST_SINGLELINE   0x00000040

class CListWnd;
class CDropList;
class CUiComboBox : public CButton
{
public:
	CUiComboBox();
	virtual ~CUiComboBox();

public:
	BOOL    Create(CRect Rect, CWnd* pParent, UINT uID, DWORD dwStyle = NULL);
	void    SetComboBoxBitmap(UINT nNormal, UINT nMouseIn, UINT nSelect, UINT uDisable=0, COLORREF clrMask=CLR_NONE); //设置控件在不同状态下的位图和位图透明色
	void    SetArrowWidth(int nWidth);                        //设置组合框右边下拉三角的长度，从而避免可能文字太长而在显示时覆盖下拉三角图案的情况发生
	void    SetCursor(UINT nCursorId);                        //设置mouse移入组合框时的mouse的形状。
	void    SetFont(CFont* pFont, COLORREF clrFont=CLR_NONE); //设置组合框中显示文字时的文字字体类型大小和颜色
	void    Enable(bool bEnable);                             //使能/禁用组合框
	bool    IsEnable();                                       //询问组合框是否禁用

	// List box Settings
	int     GetCurSel();                                      //获取组合框中ListBox中当前的选中项
	void    SetCurSel(int nSel);                              //设置组合框中ListBox中当前的选中项
	int     GetCount();                                       //获取组合框中ListBox中一共添加了多少项
	int		AddString(LPCTSTR lpszItem);                      //往组合框中ListBox添加项
	int		AddString(LPCTSTR lpszItem, int GroupPos, COLORREF crTextColor = RGB(0,0,0), COLORREF crTextHighlightColor = RGB(0,0,0));//往组合框中ListBox添加项，同时设定添加项的前/背景颜色，以及是否将该项归入某个Group中(按颜色区分)
	void	SetString(int nIndex, CString sText);
	int		DeleteString(UINT nIndex);                        //删除组合框中ListBox中指定的项
	void	ResetContent();                                   //清除组合框中ListBox中的所有项
	void    ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd);
	// Set DropList directly
	CDropList* GetDropList();                                 //获取Drop List，从而可直接对Drop List操作

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 

private:
	void	DisplayList();

private:
	bool      m_bOver;
	bool      m_bEnabled;
	int       m_nState;
	int       m_nArrowWidth;
	UINT      m_uNormal;
	UINT      m_uMouseIn;
	UINT      m_uSelect;
	UINT      m_uDisable;
	COLORREF  m_clrMask;
	HCURSOR   m_hCursor;
	CListWnd* m_pDropWnd;
	CFont*    m_pFont;
	COLORREF  m_clrText;
	DWORD     m_dwFlags;

protected:
	afx_msg void    OnPaint();
	afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
	afx_msg void    OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LONG    OnSelectionChanged(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};


typedef struct tagLISTITEM
{	
	BYTE		btHeader;
	COLORREF	crTextColor;
	COLORREF	crTextHighlightColor;
	 
} LISTITEM;


//*******************************************************************************
// CDropList window
//*******************************************************************************
class CDropList : public CListBox
{
public:
	CDropList();
	virtual ~CDropList();

public:
	void	SetFont(CFont* pFont, BOOL bRedraw = TRUE);
	void	SetBkColor(COLORREF crColor);
	void	SetHighlightBkColor(COLORREF crColor);

	inline	int GetGroupCount()        { return m_nGroupCount;    };
	inline	LISTITEM* GetCurListItem() { return m_pCurListItem;   };
	inline	int GetPreviousSelection() { return m_nPrevSelection; };
	void	SetPreviousSelection(int nPrevSelection);
	void	SetItemText(int nIndex, CString sText);

	// Overrides
	int		AddString(LPCTSTR lpszItem);
	int		AddString(LPCTSTR lpszItem, int GroupPos, COLORREF crTextColor = RGB(0,0,0), COLORREF crTextHighlightColor = RGB(0,0,0));
	int		DeleteString(UINT nIndex);
	void	ResetContent();


protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

private:
	void	DrawItem(CDC* pDC, CRect ItemRect, BOOL bSelected);
	int		AddToList(int nGroup, CString csText);
	void	ClearItems();

private:
	int			m_nGroupCount;
	int      	m_nPrevSelection;
	CPtrList	m_ItemList;
	CRect		m_WindowRect;
	CFont*		m_pTextFont;
	CFont*		m_pHeaderFont;
	CString		m_csText;
	CPen*		m_pBkPen;
	CBrush*		m_pBkBrush;
	CBrush*		m_pBkHighlightBrush;
	LISTITEM*	m_pCurListItem;	

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};


//*******************************************************************************
// CListWnd window
//*******************************************************************************
class CListWnd : public CWnd
{
public:
	CListWnd();
	virtual ~CListWnd();
	
	BOOL Create(CWnd* pParentWnd);

public:
	CWnd*	   m_pParent;
	CDropList* m_pDropList;
	
protected:
	afx_msg void OnSelectionChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
};


#endif 
