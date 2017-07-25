#ifndef _UI_CHOTKEYCTRL_H
#define _UI_CHOTKEYCTRL_H

#define WM_NEW_PAINT	0xabcd

/*****************************************************************************************************************
 *
 * CUiHotKeyCtrl: 由CHotKeyCtrl继承而来，实现控件背景颜色、背景位图的设定，以及显示字体的设定。使用该控件有两种方式：
 *                第一种，在MFC的ToolBox中添加CEdit模板资源, 通过DDX_Control将模板资源和CUiEdit对象关联；第二种，利
 *                用CEidt::Create()动态创建。
 *
 *****************************************************************************************************************/

class CUiHotKeyCtrl : public CHotKeyCtrl
{
public:
	CUiHotKeyCtrl();
	virtual ~CUiHotKeyCtrl();

	void  SetBkColor(COLORREF clrBk);                      //设置控件的背景颜色
	void  SetBkBitmap(UINT uBitmap, BOOL bAutoMove=FALSE); //设置控件的背景位图，以及是否根据位图的大小调整控件的大小
	void  SetFont(CFont* pFont, COLORREF clrFont);         //设置控件的字体类型和颜色

private:
	CBrush    m_Brush;
	CFont*    m_pFont;
	COLORREF  m_clrText;

protected:
	afx_msg void  OnPaint();
	afx_msg void  OnNcPaint();
	afx_msg BOOL  OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

#endif 
