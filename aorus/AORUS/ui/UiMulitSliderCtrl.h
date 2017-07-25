#ifndef _UI_CMULITSLIDER_H
#define _UI_CMULITSLIDER_H

#include "UiBase.h"
#include "list"

/*****************************************************************************************************************
 *
 * CUiMulitSliderCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件
 *                控件可对滑动杆的channel和bar显示位图进行设定。
 *                      
 *****************************************************************************************************************/

#define UISCS_VERTICAL            0x0001L        //垂直slider控件
#define UISCS_DRAWFOCUSRECT       0x0002L        //显示控件处于FOCUS状态

typedef std::list<int> lstInt;
typedef lstInt::iterator ItemInt;

class UI_MULITSLIDERCTRL   //填充该结构体，创建Slider控件
{
public:
	CWnd*       pParent;
	UINT        uId;
	CRect       rect;
	DWORD       dwStyle;
	UINT        uThumb;
	UINT        uThumbActive;
	UINT        uThumbDisable;
	UINT        uChannel;
	UINT        uChannelActive;
	UINT        uChannelDisable;
	COLORREF    clrMask;

	UI_MULITSLIDERCTRL();
	UI_MULITSLIDERCTRL(CWnd* parent, UINT id, CRect rcWin, UINT thumb, UINT thumbActive, UINT thumbDisable, 
		          UINT channel, UINT channelActive, UINT channelDisable, COLORREF mask=CLR_NONE, DWORD style=WS_CHILD|WS_VISIBLE);
	UI_MULITSLIDERCTRL& operator = (const UI_MULITSLIDERCTRL* pSliderCtrl);
};

class CUiMulitSliderCtrl : public CUiBase
{
	DECLARE_DYNAMIC(CUiMulitSliderCtrl)

public:
	CUiMulitSliderCtrl();
	virtual ~CUiMulitSliderCtrl();

public:
	void     CreateSliderCtrl(UI_MULITSLIDERCTRL sliderCtrl); //该函数相当于 CUiBase::Create() + CUiMulitSliderCtrl::SetSliderBitmap()

	int		 GetCount() { return m_lstPos.size(); }
	int      GetPos(int nIndex);                       //获取当前滑动杆的位置
	void     SetPos(int nPos);						   //设置当前滑动杆的位置
	void     SetPos(int nIndex, int nPos);             //设置当前滑动杆的位置
	void     AddPos(int nIndex, int nPos);             //新增滑塊
	void     RemovePos(int nIndex);					   //移除滑塊
	void     Reset();								   //移除滑塊
	void     OffsetPos(int nIncrement);				   //偏移当前滑动杆nIncrement个位置
	void     OffsetPos(int nIndex, int nIncrement);    //偏移指定Index滑动杆nIncrement个位置
	void     GetRange(int &nMin, int &nMax);           //获取滑动杆的最大/小值范围
	void     SetRange(int  nMin, int  nMax);           //设定滑动杆的最大/小值范围
	void     SetMargin(int l, int t, int r, int b);    //设定滑动杆在控件的那个范围内滑动
	
	void	 ClickAddEnable(bool bEnable);
	bool     IsEnable();
	void     Enable(bool bEnable=true);
	void     SetToolTip(bool bAddToolTip=true);
	void     SetSliderBitmap(UINT uChannel, UINT uChannelActive, UINT uChannelDisable, 
		                     UINT uThumb, UINT uThumbActive, UINT uThumbDisable, COLORREF clrMask=CLR_NONE);

protected:
	void     DrawThumb  (CDC* pDC);
	void     DrawChannel(CDC* pDC);
	virtual  void Draw(CDC* pDC, CRect rcCli);

	int      Pos2Pixel(int nPos);
	int      Pixel2Pos(int nPixel);
	ItemInt  Pixel2Pointer(int nPixel, bool bInsert = false);

	void     OffsetPos(ItemInt item, int nIncrement);    //偏移当前滑动杆nIncrement个位置
	int      GetPos(ItemInt item);                       //获取当前滑动杆的位置
	void     SetPos(ItemInt item, int nPos);             //设置当前滑动杆的位置
	ItemInt  RemovePos(ItemInt item);					 //移除滑塊
	int		 GetIndex(ItemInt item);

protected:
	int          m_nMax;
	int          m_nMin;
	lstInt		 m_lstPos;
	ItemInt		 m_curPos;
	int          m_nWidth;
	int          m_nHeight;
	int          m_nThumbWidth;
	int          m_nThumbHeight;
	CRect        m_rcMargin;
	int          m_nMouseOffset;
	bool         m_bFocus;
	bool         m_bEnable;
	bool		 m_bClickAdd;
	bool         m_bLButtonDown;
	UINT         m_uChannel;
	UINT         m_uChannelActive;
	UINT         m_uChannelDisable;
	UINT         m_uThumb;
	UINT         m_uThumbActive;
	UINT         m_uThumbDisable;
	COLORREF     m_clrMask;
	CToolTipCtrl m_toolTip;
	int			 m_nMinPos;
	int			 m_nMaxPos;

protected:
	//{{AFX_MSG(CUiMulitSliderCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif 
