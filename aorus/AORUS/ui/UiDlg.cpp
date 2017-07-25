#include "stdafx.h"
#include "UiDlg.h"
#include "UiCommon.h"


IMPLEMENT_DYNAMIC(CUiDlg, CDialog)

CUiDlg::CUiDlg() : CDialog()
{
	Init();
}
CUiDlg::CUiDlg(UINT nIDTemplate, CWnd* pParent) : CDialog(nIDTemplate, pParent)
{
	Init();
}
CUiDlg::CUiDlg(LPCTSTR lpszTemplate, CWnd* pParent) : CDialog(lpszTemplate, pParent)
{
	Init();
}

CUiDlg::~CUiDlg()
{
	m_BkDC.DeleteDC();
}

BEGIN_MESSAGE_MAP(CUiDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//-------------------------------------------------------------------------------
void CUiDlg::Init()
{
	m_uBk         = 0;
	m_uAlpha      = 0xFF;
	m_clrMask     = RGB(255, 0, 255);

	m_bPopup	  = false;
	m_bPopupWin   = true;
	m_bStoredBkDc = false;
	m_hWinRgn     = NULL;
}
//-------------------------------------------------------------------------------
void CUiDlg::SetWinRgn(HRGN hWinRgn/*if null, set window region to null*/)
{
	ASSERT(m_uBk != 0 && GetSafeHwnd());

	//Ignored for have-no-parent window.
	if(!m_bPopupWin)
	{
		if(NULL == hWinRgn)
		{
			::SetWindowRgn(m_hWnd, NULL, FALSE);
			m_hWinRgn = NULL;
			return;
		}

		m_hWinRgn = ::CreateRectRgn(0, 0, 0, 0);
		if(ERROR != ::CombineRgn(m_hWinRgn, hWinRgn, NULL, RGN_COPY))
		{
			::SetWindowRgn(m_hWnd, m_hWinRgn, TRUE);
		}
		else
		{
			::DeleteObject(m_hWinRgn);
			m_hWinRgn = NULL;
		}
	}
}
//-------------------------------------------------------------------------------
CDC* CUiDlg::GetBkDC()
{
	return &m_BkDC;
}
//-------------------------------------------------------------------------------
void CUiDlg::SetBkBitmap(UINT uId, UINT uAlpha, COLORREF clrMask)
{
	ASSERT(GetSafeHwnd());

	if(0 != uId)
	{
		m_uBk    = uId;
		m_uAlpha = uAlpha;
		if(clrMask != CLR_NONE)
		{
			m_clrMask = clrMask;
		}

		m_bPopup = (::GetWindowLong(m_hWnd, GWL_STYLE) & WS_POPUP) > 0 ? true : false;
		m_bPopupWin = (bool)(::GetWindowLong(m_hWnd, GWL_STYLE) & WS_POPUP && NULL == GetParent());

		CBitmap bitmap;
		bitmap.LoadBitmap(m_uBk);
		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		bitmap.DeleteObject();

		if(m_bPopupWin)
		{
			::SetWindowLong(m_hWnd, GWL_STYLE,   ::GetWindowLong(m_hWnd, GWL_STYLE)   & ~WS_CAPTION);
			::SetWindowLong(m_hWnd, GWL_STYLE,   ::GetWindowLong(m_hWnd, GWL_STYLE)   | WS_MINIMIZEBOX);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_WINDOWEDGE);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_DLGMODALFRAME);

			//for popup window, use SetLayeredWindowAttributes() to clip bk bitmap.
			SetLayeredWindowAttributes(m_clrMask, m_uAlpha, LWA_COLORKEY | LWA_ALPHA);
		}

		Invalidate();
	}
}
//-------------------------------------------------------------------------------
void CUiDlg::OnPaint()
{
	if(0 == m_uBk)
	{
		return CDialog::OnPaint();
	}
	else
	{
		CPaintDC dc(this);

		CRect rcCli;
		GetClientRect(&rcCli);
		
		CDC MemDC;
		CBitmap bitmap;

		MemDC.CreateCompatibleDC(&dc);
		bitmap.LoadBitmap(m_uBk);
		CBitmap* pOldBitmap = MemDC.SelectObject(&bitmap);

		if(NULL != m_BkDC.GetSafeHdc())
		{
			dc.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &m_BkDC, rcCli.left, rcCli.top, SRCCOPY);
		}

		if(m_bPopupWin || (!m_bPopupWin && m_clrMask == CLR_NONE))
		{
			dc.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, SRCCOPY);
		}
		else
		{
			dc.TransparentBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), &MemDC, rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), m_clrMask);
		}

		MemDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
		MemDC.DeleteDC();
	}
}
//-------------------------------------------------------------------------------
BOOL CUiDlg::OnEraseBkgnd(CDC* pDC)
{
	if(0 != m_uBk)
	{
		if(!m_bPopupWin && !m_bStoredBkDc)
		{
			m_bStoredBkDc = true; 

			CRect rcCli;
			GetClientRect(&rcCli);
			m_BkDC.DeleteDC();
			m_BkDC.CreateCompatibleDC(pDC);
			CBitmap bitmap;
			bitmap.CreateCompatibleBitmap(pDC, rcCli.Width(), rcCli.Height());
			m_BkDC.SelectObject(&bitmap);
			m_BkDC.BitBlt(rcCli.left, rcCli.top, rcCli.Width(), rcCli.Height(), pDC, rcCli.left, rcCli.top, SRCCOPY);
		}

		return TRUE;
	}

	return CDialog::OnEraseBkgnd(pDC);
}
//-------------------------------------------------------------------------------
LRESULT CUiDlg::OnNcHitTest(CPoint point)
{
	UINT uRes = (UINT)CDialog::OnNcHitTest(point);
	if(0 != m_uBk && m_bPopupWin && uRes == HTCLIENT) 
	{
		uRes = HTCAPTION;
	}
	else if(m_bPopup)	// allow pop-up dialog to move window.
	{
		uRes = HTCAPTION;
	}
	else if(NULL != GetParent())
	{
		uRes = HTTRANSPARENT;
	}

	return uRes;
}
//-------------------------------------------------------------------------------
BOOL CUiDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CWnd* pParent = GetParent();
	if(NULL != pParent)
	{
		pParent->PostMessage(WM_COMMAND, wParam, lParam);
		return TRUE;
	}

	return CDialog::OnCommand(wParam, lParam);
}
//-------------------------------------------------------------------------------
/*BOOL CUiDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CWnd* pParent = GetParent();
	if(NULL != pParent)
	{
		pParent->PostMessage(WM_NOTIFY, wParam, lParam);
		return TRUE;
	}

	NMHDR* pNMHDR = (NMHDR*)lParam;
	HWND hWndCtrl = pNMHDR->hwndFrom;

	if(hWndCtrl == NULL || !::IsWindow(hWndCtrl)) 
		return TRUE;

	return CDialog::OnNotify(wParam, lParam, pResult);
}*/
//-------------------------------------------------------------------------------