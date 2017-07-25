#ifndef _UI_TRAYICON_H
#define _UI_TRAYICON_H

#include <afxtempl.h>

#define WM_TRAYICON_MESSAGE	WM_APP + 1

#define WM_BALLOON_CLICKED	WM_APP + 2
#define WM_BALLOON_TIMEOUT	WM_APP + 3
#define WM_TRAY_LBTNDBLCLK	WM_APP + 4
#define WM_TRAY_RBTNDOWN	WM_APP + 5
#define WM_TRAY_MINIMIZE    WM_APP + 6
#define WM_TRAY_RESTORE		WM_APP + 7

#define TIMER_EVENT_ANIMATION 0
#define TIMER_EVENT_CLOSETIP  1

typedef enum _ICON_FLAG {
	
	ICON_NONE = 0x00,// No icon.
	ICON_INFO,		 // An information icon.
	ICON_WARNING,	 // A warning icon.
	ICON_ERROR,		 // An error icon.
	ICON_USER,		 // Use the icon identified in hIcon as the notification balloon's title icon.

} ICON_FLAG;

class CUiTrayIcon : public CWnd
{
	DECLARE_DYNAMIC(CUiTrayIcon)

public:
	CUiTrayIcon();
	CUiTrayIcon(HWND hUserWnd, UINT uTrayIconId, HICON hIcon, UINT uMenuResId);
	virtual ~CUiTrayIcon();
	
	//
	// hUserWnd    : The window handle that receives notification messages.
	// uTrayIconId : The identifier of the trayicon, will be send as WPARAM.
	// hIcon       : The trayicon handle.
	// uMenuResId  : The menu resource id that created in the window (whose handle is pWnd above). 
	//
	BOOL Create(HWND hUserWnd, UINT uTrayIconId, HICON hIcon, UINT uMenuResId);
	BOOL Destroy();

	BOOL SetToolTipText(TCHAR* szToolTip);
	BOOL ShowBalloon(TCHAR* szInfo, TCHAR* szTitle, UINT uTimeout, ICON_FLAG emIconFlag, BOOL bNoSound);
	BOOL ShowTrayIcon();
	BOOL HideTrayIcon();
	
	BOOL Minimize();
	BOOL Restore();
	
	BOOL SetIconList(HICON* pHIcon, int iNumIcons);
	//
	// iDelayMilliSeconds : Indicates the interval of replacing an icon. You must call SetIconList() to set icons first.
	// iNumSeconds        : Indicates animation continued time, if set it to -1, it will animate all the time until you call StopAnimation().
	// 
	BOOL StartAnimation(int iDelayMilliSeconds, int iNumSeconds = -1);
	BOOL StopAnimation();

private:
	BOOL SetIcon(HICON hIcon);
	BOOL AddTrayIcon();
	BOOL ModifyTrayIcon();
	BOOL DeleteTrayIcon();
	BOOL ShowPopMenu(int iSubMenuPos);
	BOOL StepAnimation();
	
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnTrayIconMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);

	HWND  m_hUserWnd;
	UINT  m_uMenuResId;
	HMENU m_hMenu;
	BOOL  m_bTrayHide;

	CArray<HICON, HICON&> m_IconList;
	COleDateTime m_oleStartTime;
	UINT_PTR m_uTimer;
	HICON    m_hSavedIcon;
	int	  m_iCurrentIcon;
	int   m_iNumSeconds;
	BOOL  m_bIsAnimation;
	
	NOTIFYICONDATA m_stNd;
};

#endif