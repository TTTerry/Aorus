#ifndef _UI_CPROGRESSCTRL_H
#define _UI_CPROGRESSCTRL_H

#include "UiBase.h"



/*****************************************************************************************************************
 *
 * CUiProgressCtrl: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。该控件
 *                  可自定义进度条的channel位图和bar位图。以及在进度条上显示当前的进度百分比值。注意bar位图的大小必
 *                  须小于等于channel的大小。控件会根据设置channel和bar大小自动调整控件窗口的大小位置。
 *                      
 *****************************************************************************************************************/

//Vertical
#define UIPBS_VERTICAL             0x0001L    //设定进度条为垂直方向，默认为水平方向

//Text Alignment Styles
#define UIPBS_LEFT                 0x0010L    //在进度条上左边显示当前进度百分比
#define UIPBS_RIGHT                0x0020L    //在进度条上右边显示当前进度百分比
#define UIPBS_CENTER               0x0030L    //在进度条上中间显示当前进度百分比
#define UIPBS_TOP                  0x0040L    //在进度条上顶端显示当前进度百分比
#define UIPBS_BOTTOM               0x0080L    //在进度条上底部显示当前进度百分比
#define UIPBS_VCENTER              0x00C0L    //在进度条上中间显示当前进度百分比

//Text format
#define UIPBS_SHOW_NOTEXT          0x0100L    //不显示进度百分比
#define UIPBS_SHOW_PERCENT         0x0200L    //显示百分比
#define UIPBS_SHOW_TIEDTEXT        0x0400L    //显示百分比，同时该百分比显示位置随进度变化而变化


class UI_PROCTRL     //填充该结构体，创建控件
{
public:
	CWnd*       pParent;
	UINT        uId;
	CRect       rect;
	DWORD       dwStyle;
	UINT        uBar;
	UINT        uChannel;
	COLORREF    clrMask;

	UI_PROCTRL();
	UI_PROCTRL(CWnd* parent, UINT id, CRect rcWin, UINT bar, UINT channel, COLORREF mask=CLR_NONE, DWORD style=WS_CHILD|WS_VISIBLE);
	UI_PROCTRL& operator = (const UI_PROCTRL* pProCtrl);
};

class CUiProgressCtrl : public CUiBase
{
public:
	CUiProgressCtrl();
	virtual ~CUiProgressCtrl();

public: 
	void     CreateProgressCtrl(UI_PROCTRL proCtrl);  //该函数相当于CUiBase::Create() + CUiProgressCtrl::SetProgressBitmap()

	int      GetPos();                              //获取当前进度条位置
	void     SetPos(int nPos);                      //设定当前进度条位置
	void     OffsetPos(int nIncrement);             //偏移当前进度条位置n个单位
	int      GetStep();                             //获取每次进度条移动的step值
	void     SetStep(int nStep);                    //设定每次进度条移动的step值
	void     SetRange(int  nMin, int  nMax);        //设定进度条最大/小范围值
	void     GetRange(int& nMin, int& nMax);        //获取进度条最大/小范围值
	void     SetMargin(int left, int  top);         //设定bar在偏移channel左上角的哪个位置开始显示，默认为(0, 0)即不偏移

	void     SetFont(CFont* pFont, COLORREF clrFont);  //设定显示百分比的字体类型和颜色
	void     SetProgressBitmap(UINT uChannel, UINT uBar, COLORREF clrMask=CLR_NONE);  //设定进度条的channel、bar位图和透明色
	
	virtual  DWORD GetCtrlStyle();                               //获取进度条属性
	virtual  void  ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd); //设定进度条属性

protected:
	void     DrawBar  (CDC* pDC, CRect rcCli);
	void     DrawText (CDC* pDC, CRect rcCli);
	virtual  void Draw(CDC* pDC, CRect rcCli);

	int      Pos2Pixel(int nPos);
	void     DrawClippedText(CDC* pDC, const CRect& rcClip, CString& sText, const CPoint& ptWndOrg);
	
protected:
	int          m_nPos;
	int          m_nMin;
	int          m_nMax;
	int          m_nStep;
	int          m_nBarPosX;
	int          m_nBarPosY;
	UINT         m_uChannel;
	UINT         m_uBar;
	SIZE         m_szBar;
	COLORREF     m_clrMask;
	CFont*       m_pFont;
	COLORREF     m_clrText;

	DECLARE_MESSAGE_MAP()
};

#endif 
