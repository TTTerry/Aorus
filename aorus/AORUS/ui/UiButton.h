#ifndef _UI_CBUTTON_H
#define _UI_CBUTTON_H

#include "UiBase.h"


/*****************************************************************************************************************
 *
 * CUiButton: 由CUiBase继承而来。通过继承父类的virtual void Draw(CDC* pDC, CRect rcCli)，实现控件绘制。CUiButton分
 *            普通Button、Check Button、Radio Button三种。
 *
 *****************************************************************************************************************/

#define BTN_COMMON 0     // common button
#define BTN_CHECK  1     // check  button
#define BTN_RADIO  2     // radio  button




class UIBTN_IMAGE	// using bitmap mode to display button
{
public:
	COLORREF clrMask;
	union
	{
		struct Check  { UINT uUncheckNormal; UINT uUncheckMouseIn; UINT uUncheckSelect; UINT uUncheckDisable;
		                UINT uCheckNormal;   UINT uCheckMouseIn;   UINT uCheckSelect;   UINT uCheckDisable;   } c;
		struct Radio  { UINT uUncheckNormal; UINT uUncheckMouseIn; UINT uUncheckSelect; UINT uUncheckDisable;
			            UINT uCheckNormal;   UINT uCheckMouseIn;   UINT uCheckSelect;   UINT uCheckDisable;   } r;
		struct Common { UINT uNormal;        UINT uMouseIn;        UINT uSelect;        UINT uDisable;        } b;
	};

	UIBTN_IMAGE();
	// 未选中，鼠标进入，选中，不选中
	UIBTN_IMAGE(UINT normal, UINT mouseIn, UINT select, UINT disable, COLORREF clrMask=CLR_NONE);
	// CheckBox或RadioButton，前面四个是unchecked的状态，后面4个check的状态
	UIBTN_IMAGE(UINT ucNormal, UINT ucMouseIn, UINT ucSel, UINT ucDisable, UINT ckNormal, UINT ckMouseIn, UINT ckSel, UINT ckDisable, COLORREF clrMask=CLR_NONE);
	UIBTN_IMAGE& operator = (const UIBTN_IMAGE* pImg);
};

class UIBTN_STRING	// using string mode to display button
{
public:
	CFont* pFont;
	CString sCaption;
	union
	{
		struct Check  { COLORREF clrUncheckNormal; COLORREF clrUncheckMouseIn; COLORREF clrUncheckSelect; COLORREF clrUncheckDisable;
		                COLORREF clrCheckNormal;   COLORREF clrCheckMouseIn;   COLORREF clrCheckSelect;   COLORREF clrCheckDisable;   } c;
		struct Radio  { COLORREF clrUncheckNormal; COLORREF clrUncheckMouseIn; COLORREF clrUncheckSelect; COLORREF clrUncheckDisable;
			            COLORREF clrCheckNormal;   COLORREF clrCheckMouseIn;   COLORREF clrCheckSelect;   COLORREF clrCheckDisable;   } r;
		struct Common { COLORREF clrNormal;        COLORREF clrMouseIn;        COLORREF clrSelect;        COLORREF clrDisable;        } b;
	};

	UIBTN_STRING();
	// 字符串，未选中的颜色，鼠标进入的颜色，选择的颜色，不可点击时的颜色，字体
	UIBTN_STRING(CString sCaption, COLORREF normal, COLORREF mouseIn, COLORREF select, COLORREF disable, CFont* pFont);
	UIBTN_STRING(CString sCaption, COLORREF ucNormal, COLORREF ucMouseIn, COLORREF ucSel, COLORREF ucDisable, COLORREF ckNormal, COLORREF ckMouseIn, COLORREF ckSel, COLORREF ckDisable, CFont* pFont);
	UIBTN_STRING& operator = (const UIBTN_STRING* pString);
};


class UI_BTN     //	set attributes of button
{
public:
	CWnd*			pParent;
	UINT			uId;
	CRect			rect;
	int				nType;
	COLORREF		clrMask;
	UIBTN_IMAGE		bmpMode;		// bitmap mode
	UIBTN_STRING	strMode;		// string mode
	DWORD			dwStyle;

	UI_BTN();
	// 新建按钮，作为CreateButton的参数，父指针，按钮的id，按钮的位置，按钮图片，按钮文字，按钮类型（普通按钮，CheckBox，radioButton），样式
	UI_BTN(CWnd* parent, UINT id, CRect rcWin, UIBTN_IMAGE* pBmpMode, UIBTN_STRING* pStrMode=NULL, int btnType=BTN_COMMON, DWORD style=WS_CHILD|WS_VISIBLE);
	UI_BTN& operator = (const UI_BTN* pBtn);
};

class CUiButton : public CUiBase
{
public:
	CUiButton();
	virtual ~CUiButton();

public:
	void    CreateButton(UI_BTN btn);     
	void    SetToolTip(CString sTip, int nMaxTipWidth=0);	// set nMaxTipWidth to show mutilline text.
	void    SetCursor(UINT nCursorId); 
	void    SetBkColor(COLORREF clrBackground); 
	COLORREF GetBkColor() { return m_clrBackground; }; 
	void    Enable(bool bEnable=true);    
	bool    IsEnable();      
	void	GetWindowText(CString& rString);
	bool    IsCheck();								  // only works for BTN_CHECK & BTN_RADIO button.
	bool    SetCheck(bool bCheck=true);				  // only works for BTN_CHECK & BTN_RADIO button.
	void	EnableConsecutiveHits(bool bEnable=true); // Only works for BTN_COMMON button. 
													  // If true, the button will send mutil click messages when it is pressed for a while. 
	void    SetButtonBitmap(UIBTN_IMAGE bmpMode, UIBTN_STRING strMode, int nBtnType=BTN_COMMON);  
	void    SetButtonImage(UIBTN_IMAGE bmpMode);  
	void    SetButtonTextStyle(UIBTN_STRING strMode);  
	void    SetCapture(CString sText, bool bTip = false);  
	CString GetCapture();  
	CToolTipCtrl* GetToolTipCtrl();

	void	SetHoverZoom(double fRatio, bool bZoom = true);
    void	SetPlayBtimap(UIBTN_IMAGE *bitmapArr,int num);
	void    Play(bool bAutoStop=true);
	void    Stop();

	virtual void  ModifyCtrlStyle(DWORD dwRemove, DWORD dwAdd); // see DT_***

protected:
	void    DrawButton(CDC* pDC, CRect rcCli);
	virtual void  Draw(CDC* pDC, CRect rcCli); 

	static void CALLBACK UiTimerProc(UINT uTimerId, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	void   OnTimerSlide();
	BOOL   QueryAniTimer();
	void   SetAniTimer(UINT nMillisecond);
	void   KillAniTimer();

protected:
	int          m_nBtnType;
	UIBTN_IMAGE  m_BmpMode;
	UIBTN_STRING m_strMode;
	COLORREF	 m_clrBackground;
	int          m_nState;
	bool         m_bEnabled;
	bool         m_bChecked;
	bool		 m_bConHits;
	int			 m_nTimer1;
	int			 m_nTimer2;
	HCURSOR      m_hCursor;
	CToolTipCtrl m_toolTip;
	UIBTN_IMAGE  m_PlayBitMap[20];
	int m_PlayBitMapNum;
	bool m_bAutoStop;
	bool		 m_bZoom;
	double	     m_fRatio;
	double	     m_fMinRatio;
	int	         m_nZoom;
	UINT		 m_uTimer; // 縮放動畫Timer
	bool		 m_bPlaying;
	DWORD		 m_dwFlags;
protected:
	afx_msg BOOL    OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void    OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif 
