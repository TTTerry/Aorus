#ifndef _UI_CSLIDERFIX_H
#define _UI_CSLIDERFIX_H

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiSliderFixCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件
 *                控件可对滑动杆的channel和bar显示位图进行设定。
 *                      
 *****************************************************************************************************************/

#define UISCSX_VERTICAL            0x0001L        //垂直slider控件
#define UISCSX_DRAWFOCUSRECT       0x0002L        //显示控件处于FOCUS状态



class UI_SLIDERFIXCTRL   //填充该结构体，创建Slider控件
{
public:
	CWnd*       pParent;
	UINT        uId;
	CRect       rect;
	DWORD       dwStyle;
	UINT        uThumb;
	UINT        uThumbActive;
	UINT        uThumbDisable;
	UINT        uChannel[100];
	UINT        uChannelActive[100];
	UINT        uChannelDisable[100];
	COLORREF    clrMask;
	int			nRange;

	UI_SLIDERFIXCTRL();
	~UI_SLIDERFIXCTRL();
	UI_SLIDERFIXCTRL(CWnd* parent, UINT id, CRect rcWin, UINT thumb, UINT thumbActive, UINT thumbDisable, 
		          UINT* channel, UINT* channelActive, UINT* channelDisable, int nRange, COLORREF mask=CLR_NONE, DWORD style=WS_CHILD|WS_VISIBLE);
	UI_SLIDERFIXCTRL& operator = (const UI_SLIDERFIXCTRL* pSliderCtrl);
};

class CUiSliderFixCtrl : public CUiBase
{
	DECLARE_DYNAMIC(CUiSliderFixCtrl)

public:
	CUiSliderFixCtrl();
	virtual ~CUiSliderFixCtrl();

public:
	void     CreateSliderCtrl(UI_SLIDERFIXCTRL sliderCtrl); //该函数相当于 CUiBase::Create() + CUiSliderFixCtrl::SetSliderBitmap()

	int      GetPos();                                 //获取当前滑动杆的位置
	void     SetPos(int nPos);                         //设置当前滑动杆的位置
	void     OffsetPos(int nIncrement);                //偏移当前滑动杆nIncrement个位置
	void     GetRange(int &nMin, int &nMax);					   //获取滑动杆的最大/小值范围
	void     SetRange(int  nMin);					   //设定滑动杆的最大/小值范围
	void     SetMargin(int l, int t, int r, int b);    //设定滑动杆在控件的那个范围内滑动
	
	bool     IsEnable();
	void     Enable(bool bEnable=true);
	void     SetToolTip(bool bAddToolTip=true);
	void     SetSliderBitmap(UINT* uChannel, UINT* uChannelActive, UINT* uChannelDisable, 
		                     UINT uThumb, UINT uThumbActive, UINT uThumbDisable, COLORREF clrMask=CLR_NONE, int nRange = 10);

protected:
	void     DrawThumb  (CDC* pDC);
	void     DrawChannel(CDC* pDC);
	virtual  void Draw(CDC* pDC, CRect rcCli);

	int      Pos2Pixel(int nPos);
	int      Pixel2Pos(int nPixel);

protected:
	int          m_nMax;
	int          m_nMin;
	int          m_nRange;
	int          m_nPos;
	int          m_nWidth;
	int          m_nHeight;
	int          m_nThumbWidth;
	int          m_nThumbHeight;
	CRect        m_rcMargin;
	int          m_nMouseOffset;
	bool         m_bFocus;
	bool         m_bEnable;
	bool         m_bLButtonDown;
	UINT         m_uChannel[100];
	UINT         m_uChannelActive[100];
	UINT         m_uChannelDisable[100];
	UINT         m_uThumb;
	UINT         m_uThumbActive;
	UINT         m_uThumbDisable;
	COLORREF     m_clrMask;
	CToolTipCtrl m_toolTip;

protected:
	//{{AFX_MSG(CUiSliderFixCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif 
