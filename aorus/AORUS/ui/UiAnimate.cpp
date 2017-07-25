#include "stdafx.h"
#include "Hook.h"
#include "UiBase.h"
#include "UiDlg.h"
#include "UiAnimate.h"
#include "UiCommon.h"
#include "Mmsystem.h"

#pragma comment(lib, "Winmm.lib")

#define CLS_UINONE    0
#define CLS_UIBASE    1
#define CLS_UIDLG     2

#define UI_WND_PROP	  _T("UI_ANIMATE_PROP")

struct CHILD_INFO 
{
	HWND hWnd; 
	BOOL bVisable; 

	CHILD_INFO() { hWnd = NULL; bVisable = 0; }
	CHILD_INFO(HWND h, BOOL b) { hWnd = h; bVisable = b; } 
};

SLIDE_PARAM::SLIDE_PARAM()
{
	uSlideStep   = 10;
	uSlideSpeed  = 20;
	hSlideRgn    = NULL;
	nWinState    = SLIDE_WIN_NA;
	rcSlide      = CRect(0, 0, 0, 0);
	rcUpdate     = CRect(0, 0, 0, 0);
	Direction    = SLIDE_NONE;
}

void SLIDE_PARAM::Clear()
{
	uSlideStep   = 10;
	uSlideSpeed  = 20;
	nWinState    = SLIDE_WIN_NA;
	rcSlide      = CRect(0, 0, 0, 0);
	rcUpdate     = CRect(0, 0, 0, 0);
	Direction    = SLIDE_NONE;
	if(NULL != hSlideRgn)
	{
		::DeleteObject(hSlideRgn);
		hSlideRgn = NULL;
	}
}

//---------------------------------------------------------------------------------
CUiAnimate::CUiAnimate()
{
	m_uTimer       = 0;
	m_hWnd         = NULL;
	m_hBkDC        = NULL;
	m_hMemDc       = NULL;
	m_hDstMemDc    = NULL;
	m_hWinRgn      = NULL;
	m_pOldWndProc  = NULL;
	m_bStoredBkDc  = false;
	m_bPrintWindow = false;
	m_bUnupdateWin = false;
	m_clrMask      = CLR_NONE;
	m_pArray.RemoveAll(); 
}

CUiAnimate::~CUiAnimate()
{
	Detach(m_hWnd);
	Clear();
}

//-------------------------------------------------------------------------------
BOOL CUiAnimate::Attach(HWND hWnd)
{
	if(!IsWindow(hWnd))
	{
		return FALSE;
	}

	Detach(hWnd);
	
	m_pOldWndProc = (WNDPROC)(LONG_PTR)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)(LONG_PTR)UiAnimateWndProc);
	if(NULL == m_pOldWndProc)
	{
		return FALSE;
	}

	SetProp(hWnd, UI_WND_PROP, (HANDLE)this);  

	return TRUE; 
}
//-------------------------------------------------------------------------------
void CUiAnimate::Detach(HWND hWnd)
{
	if(NULL != m_pOldWndProc) 
	{ 
		RemoveProp(hWnd, UI_WND_PROP); 
		SetWindowLong(hWnd, GWL_WNDPROC, (LONG)(LONG_PTR)m_pOldWndProc);
		m_pOldWndProc = NULL;
	}
}
//-------------------------------------------------------------------------------
void CUiAnimate::Clear()
{
	m_Slide.Clear();
	KillAniTimer();

	if(NULL != m_hMemDc)
	{
		::DeleteDC(m_hMemDc);
		m_hMemDc = NULL;
	}

	if(NULL != m_hDstMemDc)
	{
		::DeleteDC(m_hDstMemDc);
		m_hDstMemDc = NULL;
	}

	if(NULL != m_hBkDC)
	{
		::DeleteDC(m_hBkDC);
		m_hBkDC = NULL;
		m_bStoredBkDc = false;
	}

	int nChild = (int)m_pArray.GetSize();
	for(int i=0; i<nChild; i++)
	{
		CHILD_INFO *pChild = (CHILD_INFO*)m_pArray.GetAt(i);
		if(NULL != pChild)
		{
			delete pChild;
		}
	}
	m_pArray.RemoveAll();	

	m_hWnd    = NULL;
	m_clrMask = CLR_NONE;
	m_bUnupdateWin = false;
}
//-------------------------------------------------------------------------------
BOOL CUiAnimate::IsAnimate()
{
	return QueryAniTimer();
}
//-------------------------------------------------------------------------------
void CUiAnimate::Slide(CWnd* pWnd, COLORREF clrMask, SLIDE_DIRECTION direction, int nWinState, HRGN hSlideRgn, UINT nSlideStep, UINT nSlideSpeed)
{
	ASSERT(direction != SLIDE_NONE && nSlideStep != 0);
	ASSERT(pWnd != NULL && ::IsWindow(pWnd->GetSafeHwnd()));
	ASSERT((::GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE) & WS_CHILD) && pWnd->GetParent());

	if(IsAnimate()) { return; }

	Clear();
	CHook::HookFunction();

	m_hWnd    = pWnd->GetSafeHwnd();
	m_clrMask = clrMask;

	Attach(m_hWnd);

	CRect rcCli;
	::GetClientRect(m_hWnd, &rcCli);

	//copy bk dc. the bk dc is used to erase bk when the window is sliding.
	HDC hBkDc = GetUiClassBkDC(m_hWnd, IsUiClass(m_hWnd));
	if(hBkDc != NULL)
	{
		m_hBkDC = ::CreateCompatibleDC(hBkDc);
		ASSERT(m_hBkDC != NULL);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hBkDc, rcCli.Width(), rcCli.Height());
		::SelectObject(m_hBkDC, (HGDIOBJ)hBitmap);
		::BitBlt(m_hBkDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), hBkDc, rcCli.left, rcCli.top, SRCCOPY);

		m_bStoredBkDc = true; 
	}

	HDC hdc = ::GetDC(m_hWnd);
	m_hDstMemDc = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, rcCli.Width(), rcCli.Height());
	::SelectObject(m_hDstMemDc, hBitmap);
	::ReleaseDC(m_hWnd, hdc);

	//Init slide structure.
	m_Slide.uSlideStep  = nSlideStep;
	m_Slide.uSlideSpeed = nSlideSpeed;
	m_Slide.Direction   = direction;
	m_Slide.nWinState   = nWinState;
	BOOL bWinVisable = ::IsWindowVisible(m_hWnd);
	if(!bWinVisable)
	{
		::ShowWindow(m_hWnd, SW_SHOW);
		if(m_Slide.nWinState == SLIDE_WIN_NA)
		{
			m_Slide.nWinState = SLIDE_WIN_HIDE;
		}
	}

	EnumChildWindows(m_hWnd, (WNDENUMPROC)UiAnimateEnumChildProc, (LPARAM)this);
	PrintWindow();
	HideChildWindow();

	bool bHide = true;
	m_Slide.rcSlide = rcCli;
	switch(m_Slide.Direction)
	{
	case SLIDE_SHOW_L2R: bHide = false; m_Slide.rcSlide.right = m_Slide.rcSlide.left; break;
	case SLIDE_SHOW_R2L: bHide = false; m_Slide.rcSlide.left = m_Slide.rcSlide.right; break;
	case SLIDE_SHOW_T2B: bHide = false; m_Slide.rcSlide.bottom = m_Slide.rcSlide.top; break;
	case SLIDE_SHOW_B2T: bHide = false; m_Slide.rcSlide.top = m_Slide.rcSlide.bottom; break;
	}

	if(NULL != hSlideRgn)
	{
		m_Slide.hSlideRgn = ::CreateRectRgn(0, 0, 0, 0);
		if(ERROR == ::CombineRgn(m_Slide.hSlideRgn, hSlideRgn, NULL, RGN_COPY))
		{
			::DeleteObject(m_Slide.hSlideRgn);
			m_Slide.hSlideRgn = NULL;
		}
	}

	//if slide rgn is not null, we should remove window rgn first.
	if(NULL != m_Slide.hSlideRgn)
	{
		RemoveWinRgn();
	}

	SetAniTimer(m_Slide.uSlideSpeed);
}
//-------------------------------------------------------------------------------
void CUiAnimate::OnTimerSlide()
{
	CRect rcCli; 
	::GetClientRect(m_hWnd, &rcCli);

	bool bKillTimer = false;

	CRect rc = m_Slide.rcSlide;
	UINT  nStep = m_Slide.uSlideStep;
	m_Slide.rcUpdate = rc;

	switch(m_Slide.Direction)
	{
	case SLIDE_HIDE_L2R: rc.left   += nStep; if(rc.left   >= rcCli.right)  { rc.left   = rcCli.right;  bKillTimer = true; } break;
	case SLIDE_HIDE_R2L: rc.right  -= nStep; if(rc.right  <= rcCli.left)   { rc.right  = rcCli.left;   bKillTimer = true; } break;
	case SLIDE_HIDE_T2B: rc.top    += nStep; if(rc.top    >= rcCli.bottom) { rc.top    = rcCli.bottom; bKillTimer = true; } break;
	case SLIDE_HIDE_B2T: rc.bottom -= nStep; if(rc.bottom <= rcCli.top)    { rc.bottom = rcCli.top;    bKillTimer = true; } break;
	case SLIDE_SHOW_L2R: rc.right  += nStep; if(rc.right  >= rcCli.right)  { rc.right  = rcCli.right;  bKillTimer = true; } m_Slide.rcUpdate = rc; break;
	case SLIDE_SHOW_R2L: rc.left   -= nStep; if(rc.left   <= rcCli.left)   { rc.left   = rcCli.left;   bKillTimer = true; } m_Slide.rcUpdate = rc; break;
	case SLIDE_SHOW_T2B: rc.bottom += nStep; if(rc.bottom >= rcCli.bottom) { rc.bottom = rcCli.bottom; bKillTimer = true; } m_Slide.rcUpdate = rc; break;
	case SLIDE_SHOW_B2T: rc.top    -= nStep; if(rc.top    <= rcCli.top)    { rc.top    = rcCli.top;    bKillTimer = true; } m_Slide.rcUpdate = rc; break;
	}

	m_Slide.rcSlide = rc;
	::InvalidateRect(m_hWnd, &m_Slide.rcUpdate, TRUE);
	::UpdateWindow(m_hWnd);       
	
	if(bKillTimer)
	{
		HWND hWnd = m_hWnd;
		int  nWinState = m_Slide.nWinState;
		SLIDE_DIRECTION eDirection = m_Slide.Direction;

		//we have removed window rgn at the beginning, so set it back.
		if(NULL != m_Slide.hSlideRgn)
		{
			ResetWinRgn();
		}

		m_Slide.Direction = SLIDE_NONE;
		
		switch(nWinState)
		{
		case SLIDE_WIN_NA:   RestoreChildWindow(); ::InvalidateRect(m_hWnd, NULL, FALSE); break;  //show real window again
		case SLIDE_WIN_HIDE: ::ShowWindow(m_hWnd, SW_HIDE); RestoreChildWindow(); break;
		case SLIDE_WIN_SHOW: m_bUnupdateWin = TRUE; ::ShowWindow(m_hWnd, SW_SHOW); RestoreChildWindow(); break;
		}

		Detach(m_hWnd); //Detach window after showing child windows to avoid flickering
		Clear();

		HWND hParent = GetParent(hWnd);
		while(NULL != hParent)
		{
			if(::SendMessage(hParent, WM_UI_ANIMATE_SLIDEFINISHED, (WPARAM)hWnd, (LPARAM)eDirection)) break;
			hParent = ::GetParent(hParent);
		}
		::PostMessage(hWnd, WM_UI_ANIMATE_SLIDEFINISHED, (WPARAM)hWnd, (LPARAM)eDirection);
	}
}
//-------------------------------------------------------------------------------
BOOL CUiAnimate::OnSlidePaint()
{
	if(m_bUnupdateWin)
	{
		CRect rcUpdate(0, 0, 0, 0);
		::GetUpdateRect(m_hWnd, rcUpdate, FALSE);
		::ValidateRect(m_hWnd, rcUpdate);

		return TRUE;
	}

	if(m_Slide.Direction != SLIDE_NONE)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(m_hWnd, &ps);

		CRect rcCli;
		::GetClientRect(m_hWnd, &rcCli);

		bool bHide = false;
		int xSrc = 0, ySrc = 0;
		int xDst = 0, yDst = 0;

		CRect rcSlide  = m_Slide.rcSlide;
		CRect rcUpdate = m_Slide.rcUpdate;

		switch(m_Slide.Direction)
		{
		case SLIDE_HIDE_L2R: bHide = 1; xDst = rcSlide.left; yDst = rcSlide.top; xSrc = rcCli.left; ySrc = rcCli.top;                         break;
		case SLIDE_HIDE_R2L: bHide = 1; xDst = rcCli.left;   yDst = rcCli.top;   xSrc = rcCli.right - rcSlide.Width(); ySrc = rcCli.top;      break;
		case SLIDE_HIDE_T2B: bHide = 1; xDst = rcCli.left;   yDst = rcSlide.top; xSrc = rcCli.left; ySrc = rcCli.top;                         break;
		case SLIDE_HIDE_B2T: bHide = 1; xDst = rcCli.left;   yDst = rcCli.top;   xSrc = rcCli.left; ySrc = rcCli.bottom - rcSlide.Height();   break;
		case SLIDE_SHOW_L2R: bHide = 0; xDst = rcSlide.left; yDst = rcSlide.top; xSrc = rcCli.right - rcSlide.Width(); ySrc = rcSlide.top;    break;
		case SLIDE_SHOW_R2L: bHide = 0; xDst = rcSlide.left; yDst = rcSlide.top; xSrc = rcCli.left; ySrc = rcCli.top;                         break;
		case SLIDE_SHOW_T2B: bHide = 0; xDst = rcSlide.left; yDst = rcCli.top;   xSrc = rcSlide.top;  ySrc = rcCli.bottom - rcSlide.Height(); break;
		case SLIDE_SHOW_B2T: bHide = 0; xDst = rcSlide.left; yDst = rcSlide.top; xSrc = rcCli.left; ySrc = rcCli.top;                         break;
		}

		{
			::BitBlt(m_hDstMemDc, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), hdc, rcCli.left, rcCli.top, SRCCOPY);

			//when foreground sliding, background must be unchanged!
			if(m_hBkDC != NULL)
			{
				if(bHide)
				{
					::BitBlt(m_hDstMemDc, rcUpdate.left, rcUpdate.top, rcUpdate.Width(), rcUpdate.Height(), m_hBkDC, rcUpdate.left, rcUpdate.top, SRCCOPY);
				}
				else
				{
					::BitBlt(m_hDstMemDc, xDst, yDst, rcSlide.Width(), rcSlide.Height(), m_hBkDC, xDst, yDst, SRCCOPY);
				}
			}

			if(m_Slide.hSlideRgn != NULL)
			{
				::SelectClipRgn(m_hDstMemDc, m_Slide.hSlideRgn);
				if(CLR_NONE == m_clrMask)
				{
					::BitBlt(m_hDstMemDc, xDst, yDst, rcSlide.Width(), rcSlide.Height(), m_hMemDc, xSrc, ySrc, SRCCOPY);
				}
				else
				{
					::TransparentBlt(m_hDstMemDc, xDst, yDst, rcSlide.Width(), rcSlide.Height(), m_hMemDc, xSrc, ySrc, rcSlide.Width(), rcSlide.Height(), m_clrMask);
				}
				::SelectClipRgn(m_hDstMemDc, NULL);
			}
			else
			{
				if(CLR_NONE == m_clrMask)
				{
					::BitBlt(m_hDstMemDc, xDst, yDst, rcSlide.Width(), rcSlide.Height(), m_hMemDc, xSrc, ySrc, SRCCOPY);
				}
				else
				{
					::TransparentBlt(m_hDstMemDc, xDst, yDst, rcSlide.Width(), rcSlide.Height(), m_hMemDc, xSrc, ySrc, rcSlide.Width(), rcSlide.Height(), m_clrMask);
				}
			}

			::BitBlt(hdc, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), m_hDstMemDc, rcCli.left, rcCli.top, SRCCOPY);
		}

		::EndPaint(m_hWnd, &ps);

		return TRUE;
	}
	
	return FALSE;
}
//-------------------------------------------------------------------------------
BOOL CUiAnimate::OnEraseBkgnd(HDC hdc)
{
	if(m_bPrintWindow)
	{
		return TRUE;
	}

	if(!m_bStoredBkDc)
	{
		m_bStoredBkDc = true; 

		CRect rcCli;
		::GetClientRect(m_hWnd, &rcCli);
		::DeleteDC(m_hBkDC);
		m_hBkDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, rcCli.Width(), rcCli.Height());
		::SelectObject(m_hBkDC, (HGDIOBJ)hBitmap);
		::BitBlt(m_hBkDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), hdc, rcCli.left, rcCli.top, SRCCOPY);
	}

	return FALSE; //Must return fasle. the old window proc can store the bk dc when return false.
}
//-------------------------------------------------------------------------------
BOOL CUiAnimate::OnPaint()
{
	if(m_bPrintWindow)
	{
		return FALSE;
	}

	return OnSlidePaint();
}
//-------------------------------------------------------------------------------
LRESULT CUiAnimate::UiAnimateWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CUiAnimate* pThis = (CUiAnimate*)GetProp(hWnd, UI_WND_PROP);

	if(NULL == pThis)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	BOOL bReturn = FALSE;
	switch(message)
	{
	case WM_PAINT:      bReturn = pThis->OnPaint(); break;
	case WM_ERASEBKGND: bReturn = pThis->OnEraseBkgnd((HDC)wParam); break;
	}

	if(bReturn) 
	{
		return TRUE; 
	}

	return CallWindowProc(pThis->m_pOldWndProc, hWnd, message, wParam, lParam);
}
//---------------------------------------------------------------------------------
BOOL CUiAnimate::QueryAniTimer()
{
	return m_uTimer != 0;
}
//---------------------------------------------------------------------------------
void CUiAnimate::SetAniTimer(UINT nMillisecond)
{
	if(m_uTimer != 0)
	{
		::timeKillEvent(m_uTimer);
		m_uTimer = 0;
	}

	m_uTimer = ::timeSetEvent(nMillisecond, 10, UiAnimateTimerProc, (DWORD_PTR)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
}
//---------------------------------------------------------------------------------
void CUiAnimate::KillAniTimer()
{
	if(m_uTimer != 0)
	{
		::timeKillEvent(m_uTimer);
		m_uTimer = 0;
	}
}
//---------------------------------------------------------------------------------
void CALLBACK CUiAnimate::UiAnimateTimerProc(UINT uTimerId, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CUiAnimate* pThis = (CUiAnimate*)dwUser;

	pThis->OnTimerSlide();
}
//---------------------------------------------------------------------------------
BOOL CALLBACK CUiAnimate::UiAnimateEnumChildProc(HWND hWnd, LPARAM lParam)
{
	CUiAnimate* pThis = (CUiAnimate*)lParam;
	pThis->m_pArray.Add(new CHILD_INFO(hWnd, ::IsWindowVisible(hWnd)));
	return TRUE;
}
//-------------------------------------------------------------------------------
void CUiAnimate::PrintWindow()
{
	m_bPrintWindow = true;

	CRect rcCli;
	::GetClientRect(m_hWnd, &rcCli);

	if(m_hMemDc != NULL)
	{
		::DeleteDC(m_hMemDc);
	}

	//print all the child windows into memory dc.
	HDC hdc  = ::GetDC(m_hWnd);
	m_hMemDc = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, rcCli.Width(), rcCli.Height());
	::SelectObject(m_hMemDc, (HGDIOBJ)hBitmap);

	HDC   hMemDc = ::CreateCompatibleDC(hdc);
	HBITMAP hBmp = ::CreateCompatibleBitmap(hdc, rcCli.Width(), rcCli.Height());
	HBITMAP hOld = (HBITMAP)::SelectObject(hMemDc, (HGDIOBJ)hBmp);
	::ReleaseDC(m_hWnd, hdc);

	if(m_clrMask != CLR_NONE)
	{
		//fill mem dc with m_clrMask to make part of the window transparent.
		HBRUSH hBrush = ::CreateSolidBrush(m_clrMask);
		::FillRect(m_hMemDc, &rcCli, hBrush);
		::FillRect(hMemDc,   &rcCli, hBrush);
		::DeleteObject(hBrush);
	}

	CHook::SetPaintDC(hMemDc);
	::SendMessage(m_hWnd, WM_PAINT, 0, 0);

	HRGN hWinRgn = CreateRectRgn(0, 0, 0, 0); 
	int nHaveRgn = ::GetWindowRgn(m_hWnd, hWinRgn);
	if(nHaveRgn != ERROR)
	{
		::SelectClipRgn(m_hMemDc, hWinRgn);
		::BitBlt(m_hMemDc, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), hMemDc, rcCli.left, rcCli.top, SRCCOPY);
		::SelectClipRgn(m_hMemDc, NULL);
	}
	else
	{
		::BitBlt(m_hMemDc, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), hMemDc, rcCli.left, rcCli.top, SRCCOPY);
	}
	
	::SelectObject(hMemDc, hOld);
	::DeleteObject(hBmp);
	::DeleteObject(hWinRgn);
	::DeleteDC(hMemDc);

	
	int nChild = (int)m_pArray.GetSize();
	for(int i=0; i<nChild; i++)
	{
		CHILD_INFO* pChild = (CHILD_INFO*)m_pArray.GetAt(i);
		if(NULL != pChild && pChild->bVisable)
		{
			PrintChildWindow(m_hMemDc, pChild->hWnd);
		}
	}

	m_bPrintWindow = false;
}
//-------------------------------------------------------------------------------
void CUiAnimate::PrintChildWindow(HDC hDstDc, HWND hChildWin)
{
	CRect rcWin, rcCliChild, rcWinChild;

	::GetWindowRect(m_hWnd, &rcWin);
	::GetClientRect(hChildWin, &rcCliChild);
	::GetWindowRect(hChildWin, &rcWinChild);

	int nPosX = rcWinChild.left - rcWin.left;
	int nPosY = rcWinChild.top  - rcWin.top;

	HDC hSrcDc = ::GetDC(hChildWin);
	HDC hMemDc = ::CreateCompatibleDC(hSrcDc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hSrcDc, rcCliChild.Width(), rcCliChild.Height());
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDc, (HGDIOBJ)hBitmap);
	::ReleaseDC(hChildWin, hSrcDc);

	int nUiClass = IsUiClass(hChildWin);
	if(nUiClass != CLS_UINONE && NULL == GetUiClassBkDC(hChildWin, nUiClass))
	{
		::BitBlt(hMemDc, 0, 0, rcCliChild.Width(), rcCliChild.Height(), hDstDc, nPosX, nPosY, SRCCOPY);
		::SendMessage(hChildWin, WM_ERASEBKGND, (WPARAM)hMemDc, 0);
	}

	CHook::SetPaintDC(hMemDc);
	::SendMessage(hChildWin, WM_PAINT, 0, 0);

	HRGN hChildRgn = CreateRectRgn(0, 0, 0, 0); 
	int nHaveRgn = ::GetWindowRgn(hChildWin, hChildRgn);
	if(nHaveRgn != ERROR)
	{
		::OffsetRgn(hChildRgn, nPosX, nPosY);
		::SelectClipRgn(hDstDc, hChildRgn);
		::BitBlt(hDstDc, nPosX, nPosY, rcCliChild.Width(), rcCliChild.Height(), hMemDc, 0, 0, SRCCOPY);
		::SelectClipRgn(hDstDc, NULL);
	}
	else
	{
		::BitBlt(hDstDc, nPosX, nPosY, rcCliChild.Width(), rcCliChild.Height(), hMemDc, 0, 0, SRCCOPY);
	}
	
	::SelectObject(hMemDc, hOldBmp);
	::DeleteObject(hBitmap);
	::DeleteObject(hChildRgn);
	::DeleteDC(hMemDc);
}
//-------------------------------------------------------------------------------
void CUiAnimate::HideChildWindow()
{
	int nChild = (int)m_pArray.GetSize();
	for(int i=0; i<nChild; i++)
	{
		CHILD_INFO* pChild = (CHILD_INFO*)m_pArray.GetAt(i);
		if(NULL != pChild && pChild->bVisable)
		{
			::ShowWindow(pChild->hWnd, SW_HIDE);
		}
	}
}
//-------------------------------------------------------------------------------
void CUiAnimate::RestoreChildWindow()
{
	int nChild = (int)m_pArray.GetSize();
	for(int i=0; i<nChild; i++)
	{
		CHILD_INFO* pChild = (CHILD_INFO*)m_pArray.GetAt(i);
		if(NULL != pChild && pChild->bVisable)
		{
			::ShowWindow(pChild->hWnd, SW_SHOW);
		}
	}
}
//-------------------------------------------------------------------------------
void CUiAnimate::ResetWinRgn()
{
	if(m_hWinRgn != NULL)
	{
		::SetWindowRgn(m_hWnd, m_hWinRgn, FALSE/*free flicker*/);
		m_hWinRgn = NULL;
	}
}
//-------------------------------------------------------------------------------
void CUiAnimate::RemoveWinRgn()
{
	if(m_hWinRgn != NULL)
	{
		::DeleteObject(m_hWinRgn);
	}

	m_hWinRgn = ::CreateRectRgn(0, 0, 0, 0);
	int nHaveRgn = ::GetWindowRgn(m_hWnd, m_hWinRgn);
	if(ERROR != nHaveRgn && NULLREGION != nHaveRgn)
	{
		::SetWindowRgn(m_hWnd, NULL, FALSE);
	}
	else
	{
		::DeleteObject(m_hWinRgn);
		m_hWinRgn = NULL;
	}
}
//-------------------------------------------------------------------------------
int CUiAnimate::IsUiClass(HWND hWnd)
{
	int nUiClass = CLS_UINONE;

	CWnd* pWnd = CWnd::FromHandle(hWnd);
	if(pWnd != NULL)
	{
		if(pWnd->IsKindOf(RUNTIME_CLASS(CUiBase)))
		{
			nUiClass = CLS_UIBASE;
		}
		else if(pWnd->IsKindOf(RUNTIME_CLASS(CUiDlg)))
		{
			nUiClass = CLS_UIDLG;
		}
	}

	return nUiClass;
}
//-------------------------------------------------------------------------------
HDC CUiAnimate::GetUiClassBkDC(HWND hWnd, int nUiClass)
{
	HDC hBkDc = NULL;

	switch(nUiClass)
	{
	case CLS_UINONE: break;
	case CLS_UIBASE: hBkDc = ((CUiBase*)CWnd::FromHandle(hWnd))->GetBkDC()->GetSafeHdc(); break;
	case CLS_UIDLG:  hBkDc = ((CUiDlg *)CWnd::FromHandle(hWnd))->GetBkDC()->GetSafeHdc(); break;
	}

	return hBkDc;
}
//-------------------------------------------------------------------------------