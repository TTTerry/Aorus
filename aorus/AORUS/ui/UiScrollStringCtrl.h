#ifndef _UI_CSCROLLSTRINGCTRL_H
#define _UI_CSCROLLSTRINGCTRL_H

#include "UiBase.h"

/*****************************************************************************************************************
 *
 * CUiScrollStringCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该
 *                      控件可实现字符串滚动。同时设定字符串的字体类型和颜色。
 *                      
 *****************************************************************************************************************/

//scroll direction
#define SCROLL_L2R  1        //由左向右滚动
#define SCROLL_R2L  2        //由右向左滚动
#define SCROLL_T2B  3        //由上向下滚动
#define SCROLL_B2T  4        //由下向上滚动


class CUiScrollStringCtrl : public CUiBase
{
public:
	CUiScrollStringCtrl();
	virtual ~CUiScrollStringCtrl();

public:
	void     SetFont(CFont* pFont, COLORREF clrFont=CLR_NONE);  //设置滚动字体类型和颜色
	void     SetMargin(int l, int t, int r, int b);             //设置字符串在控件内的滚动范围
	void     AddString(CString strScroll);	                    //设置字符串

	bool     IsEnable();                                        //询问控件是否禁用
	void     Enable(bool bEnabled);                             //禁用/使能控件

	int      GetDirection();                                    //获取字符串的滚动方向
	void     SetDirection(int nDirection);                      //设置字符串的滚动方向
	void     SetScrollSpeed(int nMillisecond);                  //设置字符串的滚动速度

protected:
	void     DrawString(CDC* pDC, CRect rcCli);
	virtual  void Draw(CDC* pDC, CRect rcCli);
	
protected:
	bool         m_bEnabled;
	bool         m_MouseHover;
	int          m_nDirection;
	int          m_nScrollSpeed;
	CString      m_strScroll;
	CRect        m_rcString;
	CFont*       m_pFont;
	CSize        m_szContent;
	int          m_nScrollOffset;
	CRect        m_rcMargin;  
	COLORREF     m_clrText;
	
protected:
	afx_msg void    OnTimer(UINT_PTR nIDEvent);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void    OnDestroy();
	afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

#endif 
