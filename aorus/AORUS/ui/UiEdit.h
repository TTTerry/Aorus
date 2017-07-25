#ifndef _UI_CEDIT_H
#define _UI_CEDIT_H


/*****************************************************************************************************************
 *
 * CUiEdit: 由CEdit继承而来，实现CEdit背景颜色、位图的设置，以及CEdit中显示文字的字体设定，使用CEdit有两种方式：
 *          第一种，在MFC的ToolBox中添加CEdit模板资源, 通过DDX_Control将模板资源和CUiEdit对象关联；第二种，利用
 *          CEidt::Create()动态创建。
 *
 *****************************************************************************************************************/


class CUiEdit : public CEdit
{
public:
	CUiEdit();
	virtual ~CUiEdit();

	BOOL  Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void  SetBkColor(COLORREF clrBk);                      
	void  SetBkBitmap(UINT uBitmap, BOOL bAutoMove=FALSE);	// If bAutoMove is TRUE, set ctrl's window size as bitmap's size.
	void  SetFont(CFont* pFont, COLORREF clrFont);  
	void  SetToolTip(CString sTip, int nMaxTipWidth=0);		// set nMaxTipWidth to show mutilline text.
	void  SetAsIntNumberEdit(int nLen=20);
	void  SetAsHexNumberEdit(int nLen=20);
	void  SetAsFloatNumberEdit(int nLen=20, int nPrecision=2);	// Set as number eidt ctrl(allow [0 ~ 9], '+', '-', '.')
	void  SetWindowsValue(double fValue);
	double  GetWindowsValue();
	void  AutoAdjustCaret(bool bAutoAdjust) {m_bAdjustCaret = bAutoAdjust; }
	CToolTipCtrl* GetToolTipCtrl();

private:
	CBrush    m_Brush;
	CFont*    m_pFont;
	COLORREF  m_clrText;

protected:
	afx_msg void    OnChange();
	afx_msg void    OnSetFocus();
	afx_msg void    OnChanged();
	afx_msg void    OnNcPaint();
	afx_msg HBRUSH  CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	int  m_nNumType;
	int	 m_nDec;		// precision of number
	int  m_nLength;	// Len of number
	int  m_Height;
	CToolTipCtrl m_toolTip;
	bool m_bAdjustCaret;
};

#endif 
