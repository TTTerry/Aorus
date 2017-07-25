#include "stdafx.h"
#include "UiTrayIcon.h"

IMPLEMENT_DYNAMIC(CUiTrayIcon, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CSystemTray message handlers

BEGIN_MESSAGE_MAP(CUiTrayIcon, CWnd)
	ON_MESSAGE(WM_TRAYICON_MESSAGE, OnTrayIconMessage)
	ON_WM_TIMER()
END_MESSAGE_MAP()


CUiTrayIcon::CUiTrayIcon()
{
	m_hUserWnd   = NULL;
	m_uMenuResId = 0;
	m_hMenu      = NULL;
	m_bTrayHide  = TRUE;

	m_hSavedIcon   = NULL;
	m_iCurrentIcon = 0;
	m_iNumSeconds  = 0;
	m_uTimer       = NULL;
	m_bIsAnimation = 0;

	memset(&m_stNd, 0, sizeof(NOTIFYICONDATA));
}

CUiTrayIcon::CUiTrayIcon(HWND hUserWnd, UINT uTrayIconId, HICON hIcon, UINT uMenuResId)
{
	Create(hUserWnd, uTrayIconId, hIcon, uMenuResId);
}

CUiTrayIcon::~CUiTrayIcon()
{
	Destroy();
}

BOOL CUiTrayIcon::Create(HWND hUserWnd, UINT uTrayIconId, HICON hIcon, UINT uMenuResId)
{
	if (::IsWindow(m_hWnd))// Have created the trayicon.
	{
		return FALSE;
	}

	m_hUserWnd   = hUserWnd;
	m_uMenuResId = uMenuResId;

	if (!::IsWindow(m_hUserWnd))
	{
		return FALSE;
	}
	
	// Create an invisible window for the trayicon
    if (!CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP, 0,0,0,0, NULL, 0))
	{
		return FALSE;
	}
	
	m_stNd.cbSize = sizeof(NOTIFYICONDATA);
	m_stNd.hWnd = ((CWnd* )this)->GetSafeHwnd();
	m_stNd.uID = uTrayIconId;
	m_stNd.hIcon = hIcon;

	m_stNd.uCallbackMessage = WM_TRAYICON_MESSAGE;
	m_stNd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	return TRUE;
}

BOOL CUiTrayIcon::Destroy()
{
	BOOL bRet1 = 0, bRet2 = 0, bRet3 = 0;
	if (!::IsWindow(m_hWnd))// Have destroyed the trayicon.
	{
		return FALSE;
	}

	if (::IsWindow(m_hWnd))
	{
		bRet1 = ::DestroyWindow(m_hWnd);
	}
	if (NULL != m_hMenu)
	{
		bRet2 = ::DestroyMenu(m_hMenu);
		m_hMenu =  NULL;
	}
	bRet3 = DeleteTrayIcon();
	m_IconList.RemoveAll();

	return (bRet1 && bRet2 && bRet3);
}

BOOL CUiTrayIcon::SetToolTipText(TCHAR* szToolTip)
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}
	
	_tcscpy(m_stNd.szTip, szToolTip);

	return ShowTrayIcon();
}

BOOL CUiTrayIcon::ShowBalloon(TCHAR* szInfo, TCHAR* szTitle, UINT uTimeout, ICON_FLAG emIconFlag, BOOL bNoSound)
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	m_stNd.uTimeout = uTimeout;

	_tcscpy(m_stNd.szInfo, szInfo);
	_tcscpy(m_stNd.szInfoTitle, szTitle);
	
	DWORD dwInfoFlags = 0;
	if (ICON_NONE    == emIconFlag) { dwInfoFlags = NIIF_NONE; }
	if (ICON_INFO    == emIconFlag) { dwInfoFlags = NIIF_INFO; }
	if (ICON_ERROR   == emIconFlag) { dwInfoFlags = NIIF_ERROR; }
	if (ICON_WARNING == emIconFlag) { dwInfoFlags = NIIF_WARNING; }
	if (ICON_USER    == emIconFlag) { dwInfoFlags = NIIF_USER; }
	if (bNoSound) { dwInfoFlags |= NIIF_NOSOUND; }
	m_stNd.dwInfoFlags = dwInfoFlags;
	
	m_stNd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	if (m_bTrayHide)
	{
		AddTrayIcon();
	}
	ModifyTrayIcon();

	SetTimer(TIMER_EVENT_CLOSETIP, uTimeout, NULL);
	
	return TRUE;
}

BOOL CUiTrayIcon::ShowTrayIcon()
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	m_stNd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	if (m_bTrayHide)
	{
		AddTrayIcon();
	}

	return ModifyTrayIcon();
}

BOOL CUiTrayIcon::HideTrayIcon()
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	if (!m_bTrayHide)
	{
		return DeleteTrayIcon();
	}

	return TRUE;
}

BOOL CUiTrayIcon::Minimize()
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	ShowTrayIcon();

	//::ShowWindow(m_hUserWnd, SW_MINIMIZE);
	//::ShowWindow(m_hUserWnd, SW_HIDE);
	::PostMessage(m_hUserWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	::PostMessage(m_hUserWnd, WM_SHOWWINDOW, FALSE, SW_OTHERZOOM);
	
	::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_TRAY_MINIMIZE);

	return TRUE;
}

BOOL CUiTrayIcon::Restore()
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	ShowTrayIcon();

	if (::IsIconic(m_hUserWnd) || !::IsWindowVisible(m_hUserWnd))
	{
		::ShowWindow(m_hUserWnd, SW_RESTORE);
		::SetForegroundWindow(m_hUserWnd);
	}

	::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_TRAY_RESTORE);

	return TRUE;
}

BOOL CUiTrayIcon::SetIconList(HICON* pHIcon, int iNumIcons)
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	m_IconList.RemoveAll();
	try {
		for (int i = 0; i < iNumIcons; ++i)
		{
			m_IconList.Add(pHIcon[i]);
		}
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		m_IconList.RemoveAll();
		return FALSE;
	}
	
    return TRUE;
}

BOOL CUiTrayIcon::StartAnimation(int iDelayMilliSeconds, int iNumSeconds)
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}
	if (m_bIsAnimation)
	{
		return TRUE;
	}

	StopAnimation();
	m_hSavedIcon = m_stNd.hIcon;// Backup the previous trayicon.
	m_iCurrentIcon = 0;
	m_oleStartTime = COleDateTime::GetCurrentTime();
	m_iNumSeconds  = iNumSeconds;
	m_bIsAnimation = TRUE;

	if (NULL == m_uTimer)
	{
		m_uTimer = SetTimer(TIMER_EVENT_ANIMATION, iDelayMilliSeconds, NULL);
	}

	return (NULL != m_uTimer);
}

BOOL CUiTrayIcon::StopAnimation()
{
	if (!::IsWindow(m_hWnd))// Have't created the trayicon yet.
	{
		return FALSE;
	}

	BOOL bResult = 0;
	if (NULL != m_uTimer)
	{
		bResult = KillTimer(TIMER_EVENT_ANIMATION);
		m_uTimer = NULL;
	}
	if (NULL != m_hSavedIcon)
	{
		m_stNd.hIcon = m_hSavedIcon;
		ModifyTrayIcon();
	}
	m_bIsAnimation = FALSE;

	return bResult;
}

BOOL CUiTrayIcon::ShowPopMenu(int iSubMenuPos)
{
	ShowTrayIcon();

	POINT stMenuPos;
	HINSTANCE hInstance = NULL;
	
	::GetCursorPos(&stMenuPos);
	if (NULL != m_hMenu)
	{
		::DestroyMenu(m_hMenu);
		m_hMenu =  NULL;
	}

	hInstance = ::AfxGetInstanceHandle();
	m_hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(m_uMenuResId));
	if (NULL != m_hMenu)
	{
		m_hMenu = ::GetSubMenu(m_hMenu, iSubMenuPos);
	}
	if (NULL == m_hMenu)
	{
		return FALSE;
	}

	::SetForegroundWindow(m_hUserWnd);// To make the menu disappear when click outside the menu.
	::TrackPopupMenu(m_hMenu, TPM_RIGHTALIGN | TPM_RIGHTBUTTON, stMenuPos.x, stMenuPos.y, NULL, m_hUserWnd, NULL);
	::PostMessage(m_hUserWnd, WM_NULL, 0, 0);// To make the menu stays displayed for the next time.

	return TRUE;
}

LRESULT CUiTrayIcon::OnTrayIconMessage(WPARAM wParam, LPARAM lParam)
{
	if (m_stNd.uID != wParam)
	{
		return NULL;
	}

	switch (lParam)
	{
	case NIN_BALLOONUSERCLICK: 
		::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_BALLOON_CLICKED); 
		//DeleteTrayIcon();
		break;
	case NIN_BALLOONTIMEOUT: 
		::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_BALLOON_TIMEOUT); 
		break;
	case NIN_BALLOONHIDE:  DeleteTrayIcon(); break;
	case NIN_BALLOONSHOW:  break;

	case WM_LBUTTONDBLCLK: 
		::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_TRAY_LBTNDBLCLK); 
		Restore();
		break;
	case WM_RBUTTONDOWN:
		::PostMessage(m_hUserWnd, WM_TRAYICON_MESSAGE, (WPARAM)m_stNd.uID, (LPARAM)WM_TRAY_RBTNDOWN); 
		ShowPopMenu(0);
		break;
	}

	return NULL;
}

BOOL CUiTrayIcon::SetIcon(HICON hIcon)
{
	m_stNd.hIcon = hIcon;

	return Shell_NotifyIcon(NIM_MODIFY, &m_stNd);
}

BOOL CUiTrayIcon::AddTrayIcon()
{
	m_bTrayHide = FALSE;

	return Shell_NotifyIcon(NIM_ADD, &m_stNd);
}

BOOL CUiTrayIcon::ModifyTrayIcon()
{
	return Shell_NotifyIcon(NIM_MODIFY, &m_stNd);
}

BOOL CUiTrayIcon::DeleteTrayIcon()
{
	m_bTrayHide = TRUE;

	return Shell_NotifyIcon(NIM_DELETE, &m_stNd);
}

BOOL CUiTrayIcon::StepAnimation()
{
	if (!m_IconList.GetSize())
	{
		return FALSE;
	}

	m_iCurrentIcon++;
	if (m_iCurrentIcon >= m_IconList.GetSize())
	{
		m_iCurrentIcon = 0;
	}

	return SetIcon(m_IconList[m_iCurrentIcon]);
}

void CUiTrayIcon::OnTimer(UINT nIDEvent) 
{
	if (TIMER_EVENT_ANIMATION == nIDEvent)
	{
		COleDateTime CurrentTime = COleDateTime::GetCurrentTime();
		COleDateTimeSpan period  = CurrentTime - m_oleStartTime;
		if (m_iNumSeconds > 0 && m_iNumSeconds < period.GetTotalSeconds())
		{
			StopAnimation();
			return ;
		}

		StepAnimation();
	}
	else if (TIMER_EVENT_CLOSETIP == nIDEvent)
	{
		_tcscpy(m_stNd.szInfo, _T(""));
		if (m_bTrayHide)
		{
			AddTrayIcon();
		}
		ModifyTrayIcon();
		KillTimer(TIMER_EVENT_CLOSETIP);
	}
}