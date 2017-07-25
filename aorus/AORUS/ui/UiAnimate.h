#ifndef _UI_CANIMATE_H
#define _UI_CANIMATE_H

/*****************************************************************************************************************
 *
 * CUiAnimate: 实现对任何窗口的动画操作，目前只实现滑动功能。通过Slider()的参数，可设定窗口滑动方向、滑动速度、滑动
 *             步长、滑动区域、以及滑动后窗口是否隐藏等属性。
 *
 *****************************************************************************************************************/

#define SLIDE_WIN_NA    0        //displays the window in its current state after sliding finished
#define SLIDE_WIN_HIDE  2        //show the window after sliding finished
#define SLIDE_WIN_SHOW  1        //hide the window after sliding finished


typedef enum _SLIDE_DIRECTION 
{ 
	SLIDE_NONE = 0, 
	SLIDE_HIDE_L2R,          //hide from left to right
	SLIDE_HIDE_R2L,          //hide from right to left
	SLIDE_HIDE_T2B,          //hide from bottom to top
	SLIDE_HIDE_B2T,          //hide from top to bottom
	SLIDE_SHOW_L2R,          //show from left to right
	SLIDE_SHOW_R2L,          //show from right to left
	SLIDE_SHOW_T2B,          //show from top to bottom
	SLIDE_SHOW_B2T,          //show from bottom to top 

} SLIDE_DIRECTION, *PSLIDE_DIRECTION;

class SLIDE_PARAM
{
public:
	UINT       uSlideStep;
	UINT       uSlideSpeed;
	CRect      rcSlide;
	CRect      rcUpdate;         
	HRGN       hSlideRgn;       
	int        nWinState;
	SLIDE_DIRECTION Direction;

	void Clear();
	SLIDE_PARAM();
};



class CUiAnimate
{
public:
	 CUiAnimate();
	~CUiAnimate();

	void Slide(CWnd*           pWnd,                             
		       COLORREF        clrMask,              //Used to make part of the window transparent(if it is necessary) when sliding
		       SLIDE_DIRECTION direction,            //sliding direction
		       int             nWinStateAfterSlide,  //show or hide the window, or keep the window in its current state after sliding finished 
			   HRGN            hSlideRgn=NULL,       //the window slide in this region, this parameter is ignored by popup window
			   UINT            nSlideStep=10,        //slide step(in pixel)  
			   UINT            nSlideSpeed=20        //slide speed(in millisecond)
			  );
	BOOL IsAnimate();                                //Is CUiAnimate used now.

private:
	void   Clear();
	BOOL   Attach(HWND hWnd);
	void   Detach(HWND hWnd);

	BOOL   OnPaint();
	BOOL   OnEraseBkgnd(HDC hdc);
	void   OnTimerSlide();
	BOOL   OnSlidePaint();

	BOOL   QueryAniTimer();
	void   SetAniTimer(UINT nMillisecond);
	void   KillAniTimer();

	void   PrintWindow();
	void   PrintChildWindow(HDC hDstDc, HWND hChildWin);
	void   HideChildWindow();
	void   RestoreChildWindow();

	void   ResetWinRgn();
	void   RemoveWinRgn();

	int    IsUiClass(HWND hWnd);
	HDC    GetUiClassBkDC(HWND hWnd, int nUiClass);
	
	static void    CALLBACK UiAnimateTimerProc(UINT uTimerId, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
	static BOOL    CALLBACK UiAnimateEnumChildProc(HWND hwnd, LPARAM lParam);
	static LRESULT CALLBACK UiAnimateWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND        m_hWnd;
	WNDPROC     m_pOldWndProc;
	UINT        m_uTimer;
	CPtrArray   m_pArray;
	HDC         m_hMemDc;
	HDC         m_hDstMemDc;
	HRGN        m_hWinRgn;
	HDC         m_hBkDC;
	bool        m_bStoredBkDc;
	COLORREF    m_clrMask;
	SLIDE_PARAM m_Slide;
	bool        m_bPrintWindow;
	bool        m_bUnupdateWin;
	
};

#endif 
