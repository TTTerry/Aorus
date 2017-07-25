// AORUSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AORUS.h"
#include "AORUSDlg.h"
#include "MousePointerDlg.h"
//2017/07/23 Terry
#include "tlhelp32.h"

extern "C" {  
#include "setupapi.h" 
#include "lib/hidsdi.h" 
}

#include "afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int m_nProfileSel;

static CMutex s_Mutex = CMutex(FALSE, _T("LOCK_THREAD_AORUS_REGULATE_GIGABYTE"), NULL);

static void Lock()   { s_Mutex.Lock();   }
static void Unlock() { s_Mutex.Unlock(); }


CAORUSDlg* g_AorusDlg = NULL;
CAORUSDlg* Aorus() { return g_AorusDlg; }

CCfg CAORUSDlg::m_Cfg;
CCfg* CAORUSDlg::GetCfg() { return &m_Cfg; }

SYNCLED_CONFIG s_SyncLedConfig; 

//Terry 2017/07/04
GVORDER_PROFILE s_nCurProfile; // ?前profile
GVORDER_PROFILE s_LastApplyProfile; // 最後apply的profile

CAORUSDlg::CAORUSDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CAORUSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nVGASel = 0;
	m_nDeviceSel = DEVICE_VGA;
	m_nVGAProSel = 0;
	m_nDevShiftL = 0;
	m_bWinClose = false;
	
	Gv::Shell shell;
	if (!m_DevMB.IsSupportLed()) 
	{
		//shell.Execute(Gv::OS::GetCurDirectory() + _T("MBLed.exe"));
	}
}

void CAORUSDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAORUSDlg, CUiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_INPUT()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
	ON_MESSAGE(WM_TRAYICON_MESSAGE, OnTrayIcon)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_PANEL_SELCHANGE, OnUiPanelSelChanged)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
	ON_COMMAND(IDR_MENU_CLOSE, OnClose)
	ON_COMMAND(IDR_MENU_OPEN, OnOpen)
	ON_WM_DEVICECHANGE()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CAORUSDlg message handlers

BOOL CAORUSDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();

    g_AorusDlg = this;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//// Check AORUS is running or not.

	m_hInstance = CreateMutex(NULL, TRUE, _T("GRAPHICS ENGINE_INSTANCE"));
	if (ERROR_ALREADY_EXISTS == GetLastError()) // running
	{
		CloseHandle(m_hInstance);
		m_hInstance = NULL;
		::PostQuitMessage(0);
		return TRUE;
	}

	CSyncLed::RefreshMemory();
	
//------------------------------------------------terry 2017/06/26-----------------------------------------------
	RAWINPUTDEVICE rid[4];
	memset (rid, 0, sizeof (rid));
	// For XM300
	rid[0].usUsagePage = 0xFF00;
	rid[0].usUsage = 0x01;
	rid[0].dwFlags = RIDEV_INPUTSINK;
	rid[0].hwndTarget = m_hWnd;

	rid[1].usUsagePage = 0xFF02;
	rid[1].usUsage = 0x01;
	rid[1].dwFlags = RIDEV_INPUTSINK;
	rid[1].hwndTarget = m_hWnd;
	if(RegisterRawInputDevices(rid, 2, sizeof (RAWINPUTDEVICE)) == FALSE); // 註冊監?hid設備
//-----------------------------------------------------------------------------------------------------------------
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME1);
	m_trayIcon.Create(m_hWnd, TRAYICON_UID, hIcon, IDR_MENU_MAIN);
	CString sCaption = _T("AORUS GRAPHICS ENGINE");
	::SetWindowText(m_hWnd, sCaption);
	m_trayIcon.SetToolTipText((LPTSTR)(LPCTSTR)sCaption);

	// Register to receive notification when a USB device is plugged in.  


	DEV_BROADCAST_DEVICEINTERFACE broadcastInterface;
	broadcastInterface.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	broadcastInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	HidD_GetHidGuid(&broadcastInterface.dbcc_classguid);
	m_deviceNotifyHandle = RegisterDeviceNotification(m_hWnd, &broadcastInterface, DEVICE_NOTIFY_WINDOW_HANDLE);


	CAudioVolume::Init();
	m_DevVGA.OnConnect(m_hWnd);  // Initialize
	m_Cfg.Initialize();

	
	VGA_PARAM_BASESETTING base;
	m_Cfg.GetBaseSetting(base);
//	m_Cfg.Initialize();
	if(base.bCheckUpdate && m_DevVGA.Ctrl()->IsSwUpdate())
	{
		m_trayIcon.ShowBalloon(_T("New version tool is available."), _T("AORUS GRAPHICS ENGINE"), 5000, ICON_WARNING, TRUE);
	}
	if (base.bMinimize)
	{
		CString sCmd = GetCommandLine();
		if(sCmd.MakeLower().Find(_T("/h")) >= 0) OnMinimize();
	}

	m_nVGAProSel = m_Cfg.GetProfileSel(m_nVGASel);

	CSyncLed::RefreshMemory();



   Ui();
	Initstate();
	// Peter Lee 2017/6/18
//#ifndef _DEBUG
	SwitchDevice(m_nDeviceSel);
//#endif
	AfxBeginThread(OnScanDevice, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAORUSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CUiDlg::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAORUSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CAORUSDlg::PreTranslateMessage(MSG* pMsg)
{
	// Enter & ESC key: return directly, do nothing.

	if (pMsg->message == WM_KEYDOWN && 
	   (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}
	return CUiDlg::PreTranslateMessage(pMsg);
}

void CAORUSDlg::Ui()
{
	UiMain();
}

void CAORUSDlg::UiMain()
{
	// Background 
	SetBkBitmap(IDB_MAIN_BG, 0xff, CLR_TRPT); 

	UI_BTN btn[] = 
	{
		UI_BTN(this, BTN_HOME_REMOTE,	 CRect(506,  25, 0,  0), &UIBTN_IMAGE(IDB_HOME_REMOTEON, IDB_HOME_REMOTEON, IDB_HOME_REMOTEON, IDB_HOME_REMOTEON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_SETTING,	 CRect(540,  25, 0,  0), &UIBTN_IMAGE(IDB_HOME_SETTINGON, IDB_HOME_SETTINGON, IDB_HOME_SETTINGON, IDB_HOME_SETTINGON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_MIN,	 CRect(572,  26, 0,  0), &UIBTN_IMAGE(IDB_HOME_MINON, IDB_HOME_MINON, IDB_HOME_MINON, IDB_HOME_MINON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_CLOSE,	 CRect(602,  26, 0,  0), &UIBTN_IMAGE(IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_MENULEFT,	 CRect(540,  25, 0,  0), &UIBTN_IMAGE(0, 0, 0, 0, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_MENURIGHT,	 CRect(572,  33, 0,  0), &UIBTN_IMAGE(0, 0, 0, 0, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_LED,	 CRect(494,  501, 0,  0), &UIBTN_IMAGE(IDB_QUICKMENU_LED, IDB_QUICKMENU_LED, IDB_QUICKMENU_LED, 0, 0, 0, 0, 0, CLR_TRPT)),
		
		UI_BTN(this, BTN_HOME_MONIT,	CRect(518, 456, 0, 0),  &UIBTN_IMAGE(IDB_HOME_MONIT_OFF, IDB_HOME_MONIT_OFF, IDB_HOME_MONIT_OFF, 0, IDB_HOME_MONIT_ON, IDB_HOME_MONIT_ON, IDB_HOME_MONIT_ON, 0, CLR_TRPT),NULL, BTN_CHECK),
		UI_BTN(this, BTN_HOME_SEMIPASS,	CRect(569, 424, 0, 0),  &UIBTN_IMAGE(IDB_HOME_FANSTOP_OFF, IDB_HOME_FANSTOP_OFF, IDB_HOME_FANSTOP_OFF, 0, IDB_HOME_FANSTOP_ON, IDB_HOME_FANSTOP_ON, IDB_HOME_FANSTOP_ON, 0, CLR_TRPT),NULL, BTN_CHECK),

		UI_BTN(this, BTN_HOME_ENTERPRO,	 CRect(400, 110, 630, 130), &UIBTN_IMAGE(0, 0, 0, 0, CLR_TRPT), &UIBTN_STRING(CLangX::Get(LANG_AORUS_PROFTIP) + _T(" >>"), CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, Font(14))), 
		UI_BTN(this, BTN_HOME_BACKHOME,	 CRect(579,  501, 0,  0), &UIBTN_IMAGE(IDB_HOME_BACKHOME_ON, IDB_HOME_BACKHOME_ON, IDB_HOME_BACKHOME_ON, IDB_HOME_BACKHOME_ON, 0, 0, 0, 0, CLR_TRPT)),
	
		UI_BTN(this, BTN_HOME_DEVARROWL, CRect( 10, 500, 0,  0), &UIBTN_IMAGE(IDB_DEVICE_LARROW_ON, IDB_DEVICE_LARROW_ON, IDB_DEVICE_LARROW_ON, IDB_DEVICE_LARROW_ON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_DEVARROWR, CRect(440, 500, 0,  0), &UIBTN_IMAGE(IDB_DEVICE_RARROW_ON, IDB_DEVICE_RARROW_ON, IDB_DEVICE_RARROW_ON, IDB_DEVICE_RARROW_ON, 0, 0, 0, 0, CLR_TRPT)),
		
		UI_BTN(this, BTN_HOME_MACRO, CRect(553, 110-10, 640-10, 130), &UIBTN_IMAGE(IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_AORUS_MACRO), CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, Font(12)), BTN_CHECK),

	//	UI_BTN(this, BTN_HOME_MACRO, CRect(563, 87, 0, 0), &UIBTN_IMAGE(IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, 0, IDB_HOME_MACRO, IDB_HOME_MACRO, IDB_HOME_MACRO, 0, CLR_TRPT),NULL, BTN_CHECK),
		UI_BTN(this, BTN_HOME_POINTER, CRect(494,  501, 0,  0), &UIBTN_IMAGE(IDB_HOME_POINTER, IDB_HOME_POINTER, IDB_HOME_POINTER, 0, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_MOUSEBUTTON, CRect(494,  501, 0,  0), &UIBTN_IMAGE(IDB_HOME_MOUSEBUTTON, IDB_HOME_MOUSEBUTTON, IDB_HOME_MOUSEBUTTON, 0, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_HOME_KEYASSIGN, CRect(494,  501, 0,  0), &UIBTN_IMAGE(IDB_HOME_KEYASSIGN, IDB_HOME_KEYASSIGN, IDB_HOME_KEYASSIGN, 0, 0, 0, 0, 0, CLR_TRPT)),
	};

	for (int i = BTN_HOME_REMOTE; i < BTN_HOME_NUM; i++)
	{
		m_btn[i].CreateButton(btn[i]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	m_btn[BTN_HOME_REMOTE].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_LED].SetBkColor(CLR_DARK);
	m_btn[BTN_HOME_ENTERPRO].ModifyCtrlStyle(ST_CENTER, ST_RIGHT);


	m_btn[BTN_HOME_MACRO].ModifyCtrlStyle(ST_CENTER, ST_RIGHT);
	m_btn[BTN_HOME_MACRO].SetToolTip(CLangX::Get(LANG_AORUS_MACRO));
	m_btn[BTN_HOME_MACRO].ShowWindow(SW_HIDE);

	m_btn[BTN_HOME_POINTER].SetToolTip(CLangX::Get(LANG_AORUS_POINTER));
	m_btn[BTN_HOME_MOUSEBUTTON].SetToolTip(CLangX::Get(LANG_AORUS_BUTTONS));


	m_btn[BTN_HOME_BACKHOME].SetToolTip(CLangX::Get(LANG_AORUS_HOMETIP));
	m_btn[BTN_HOME_ENTERPRO].SetToolTip(CLangX::Get(LANG_AORUS_PROFTIP));
	m_btn[BTN_HOME_MONIT].SetToolTip(CLangX::Get(LANG_AORUS_MONITIP));
	m_btn[BTN_HOME_SEMIPASS].SetToolTip(CLangX::Get(LANG_AORUS_FANSTOPTIP));
	m_btn[BTN_HOME_LED].SetToolTip(CLangX::Get(LANG_AORUS_LEDTIP));
	m_btn[BTN_HOME_KEYASSIGN].SetToolTip(CLangX::Get(LANG_AORUS_KEYASSIGNTIP));


	//m_btn[BTN_HOME_KEYASSIGN].SetToolTip(CLangX::Get(LANG_AORUS_LEDTIP));

	
	m_btn[BTN_HOME_ENTERPRO].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_DEVARROWL].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_DEVARROWR].ShowWindow(SW_HIDE);

	m_btn[BTN_HOME_MONIT].SetHoverZoom(0.8, true);
	m_btn[BTN_HOME_SEMIPASS].SetHoverZoom(0.8, true);
	m_btn[BTN_HOME_LED].SetHoverZoom(0.8, true);
	m_btn[BTN_HOME_POINTER].SetHoverZoom(0.8, true);
	m_btn[BTN_HOME_MOUSEBUTTON].SetHoverZoom(0.8, true);
	m_btn[BTN_HOME_KEYASSIGN].SetHoverZoom(0.8, true);




	CreateDeivceIcons(); // Create device panel: show different device icons.

	m_stc[STC_HOME_GIGABYTE_LOGO].CreateStatic(UI_STATIC(this, STC_HOME_GIGABYTE_LOGO,  CRect(21, 17, 0, 0), _T(""), IDB_GIGABYTE_LOGO, CLR_TRPT));
	m_stc[STC_HOME_AORUS_LOGO].CreateStatic(UI_STATIC(this, STC_HOME_AORUS_LOGO,  CRect(21, 17, 0, 0), _T(""), IDB_AORUS_LOGO, CLR_TRPT));
	m_stc[STC_HOME_RGB_FUSION].CreateStatic(UI_STATIC(this, STC_HOME_RGB_FUSION,  CRect(563, 87, 0, 0), _T(""), IDB_RGBFUSION, CLR_TRPT));
	m_stc[STC_HOME_RGB_FUSION].ShowWindow(SW_HIDE);
	m_stc[STC_HOME_AORUS_LOGO].ShowWindow(SW_HIDE);

	m_combobox[COMB_HOME_CARDSEL].Create(CRect(20, 104, 0, 0), this, COMB_HOME_CARDSEL);
	m_combobox[COMB_HOME_CARDSEL].SetComboBoxBitmap(IDB_CARDSEL_COMB_BG, IDB_CARDSEL_COMB_BG, IDB_CARDSEL_COMB_BG, IDB_CARDSEL_COMB_BG, CLR_TRPT);
	m_combobox[COMB_HOME_CARDSEL].SetFont(Font(13, true), CLR_WHITE);
	m_combobox[COMB_HOME_CARDSEL].SetCursor(IDC_CUR_HAND); 
	m_combobox[COMB_HOME_CARDSEL].SetArrowWidth(20);
	m_combobox[COMB_HOME_CARDSEL].GetDropList()->SetFont(Font(12));
	m_combobox[COMB_HOME_CARDSEL].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMB_HOME_CARDSEL].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMB_HOME_CARDSEL].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);

	// create all dialogs

	CRect rcWin;
	m_VgaHomeDlg.Create(IDD_VGA_HOME_DIALOG, this);
	m_VgaHomeDlg.GetWindowRect(rcWin);
	m_VgaHomeDlg.MoveWindow(8, 149, rcWin.Width(), rcWin.Height());
	m_VgaHomeDlg.ShowWindow(SW_HIDE);

	m_DispClkDlg.Create(IDD_VGA_DISPLAYCLK_DIALOG, this);
	m_DispClkDlg.GetWindowRect(rcWin);
	m_DispClkDlg.MoveWindow(8, 323, rcWin.Width(), rcWin.Height());
	m_DispClkDlg.ShowWindow(SW_HIDE);

	m_VgaProDlg.Create(IDD_VGA_PROF_DIALOG, this);
	m_VgaProDlg.GetWindowRect(rcWin);
	m_VgaProDlg.MoveWindow(14, 133, rcWin.Width(), rcWin.Height());
	m_VgaProDlg.ShowWindow(SW_HIDE);

	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		bool bHasProfile = (s_DevIds[i] == DEVICE_AM300 || s_DevIds[i] == DEVICE_AK700) ? true : false;
		m_LedDlg[i].Initialize(s_DevIds[i], bHasProfile);

		m_LedDlg[i].Create(IDD_VGA_LED_DIALOG, this);
		m_LedDlg[i].GetWindowRect(rcWin);
		m_LedDlg[i].MoveWindow(19, bHasProfile ? (126 - 33) : 126, rcWin.Width(), rcWin.Height());
		m_LedDlg[i].ShowWindow(SW_HIDE);
	}

	
	m_KeyAssignDlg.Create(IDD_VGA_LED_DIALOG, this);
 	m_KeyAssignDlg.GetWindowRect(rcWin);
 	m_KeyAssignDlg.MoveWindow(1, 80, rcWin.Width(), rcWin.Height());
	m_KeyAssignDlg.ShowWindow(SW_HIDE);

	m_KBLedDlg.Create(IDD_VGA_LED_DIALOG, this);
	m_KBLedDlg.GetWindowRect(rcWin);
	m_KBLedDlg.MoveWindow(1, 80, rcWin.Width(), rcWin.Height());
	m_KBLedDlg.ShowWindow(SW_HIDE);

	m_MousePointerDlg.Create(IDD_VGA_LED_DIALOG, this);
	m_MousePointerDlg.GetWindowRect(rcWin);
	m_MousePointerDlg.MoveWindow(1, 80, rcWin.Width(), rcWin.Height());
	m_MousePointerDlg.ShowWindow(SW_HIDE);

	m_MouseButtonDlg.Create(IDD_VGA_LED_DIALOG, this);
	m_MouseButtonDlg.GetWindowRect(rcWin);
	m_MouseButtonDlg.MoveWindow(1, 80, rcWin.Width(), rcWin.Height());
	m_MouseButtonDlg.ShowWindow(SW_HIDE);

	m_cRemoteSettingDlg.Create(IDD_REMOTECTR_SETTING, GetDesktopWindow());
	m_cRemoteSettingDlg.GetClientRect(&rcWin);
	rcWin.MoveToXY(CPoint(800, 400));
	m_cRemoteSettingDlg.MoveWindow(rcWin);
	m_cRemoteSettingDlg.ShowWindow(SW_HIDE);

	m_settingDlg.Create(IDD_VGA_SETTING, GetDesktopWindow());
	m_settingDlg.GetClientRect(&rcWin);
	rcWin.MoveToXY(CPoint(800, 400));
	m_settingDlg.MoveWindow(rcWin);
	m_settingDlg.ShowWindow(SW_HIDE);

	m_CMonitorDlg.SetParent(this);
	m_CMonitorDlg.Create(IDD_VGA_MONITORING, GetDesktopWindow());
	m_CMonitorDlg.GetClientRect(&rcWin);
	rcWin.MoveToXY(CPoint(1024, 400));
	m_CMonitorDlg.MoveWindow(rcWin);
	m_CMonitorDlg.ShowWindow(SW_HIDE);

	m_MacroKeyDlg.Create(IDD_VGA_MONITORING, GetDesktopWindow());
	m_MacroKeyDlg.ShowWindow(SW_HIDE);
}

CDevice* CAORUSDlg::GetDevice(int nDevice/*should be DEVICE_*** */)
{
	switch(nDevice)
	{
	case DEVICE_VGA:	return &m_DevVGA;
	case DEVICE_SLI:	return &m_DevSLI;
	case DEVICE_MB:		return &m_DevMB;
	case DEVICE_ATC700:	return &m_DevATC700;
	case DEVICE_AC300:	return &m_DevAC300;
	case DEVICE_AH300:	return &m_DevAH300;
	case DEVICE_AM300:	return &m_DevAM300;
	case DEVICE_AK700:	return &m_DevAK700;
	case DEVICE_H5:	return &m_DevH5;
	}

	ASSERT(false);
	return NULL;
}

void CAORUSDlg::ReInitAllDevicesLedState()
{
	for (int i = 0 ; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = GetDevice(s_DevIds[i]); 
		if (!pDevice->IsConnected())
			continue;
		m_LedDlg[i].InitState();
		m_LedDlg[i].UpdateWindow();
		//Terry 2017/07/25 
// 		m_KBLedDlg.InitState();//Terry 2017/07/17
// 		m_KBLedDlg.UpdateWindow();

	}
}

//
// Keep monitoring VGA: GPU usage/temperature...
//
UINT CAORUSDlg::KeepLedMonitor(LPVOID pParam)
{
	// To control NV video graphics cards: 
	// 1st card index: 0; 
	// 2nd card index: 1;
	// SLI devicee index: 2;

	CAORUSDlg* pAorus = (CAORUSDlg*)pParam;
	int nGPUs = pAorus->m_DevVGA.Ctrl()->GetGpuCount();
	if (nGPUs >= 2)
	{
		nGPUs = nGPUs + 1; // +1: to control SLI device.
	}

	while(true) // keep monitoring
	{
		if (pAorus->m_bWinClose) 
			break;
		for(int i = 0; i < nGPUs; i++)
		{
			LED_SETTING led = pAorus->m_LedDlg[DEVICE_VGA - 1].GetLedCfg(i, 0);
			pAorus->m_DevVGA.Ctrl()->LedMintoring(i,led);
		}
		Sleep(10);
	}

	return 1;
}

void CAORUSDlg::Initstate()
{
	FAN_SETTING fan;
	m_LastVgaSel = m_nVGASel;
	m_nVGAProSel = m_Cfg.GetProfileSel(m_nVGASel);
	m_Cfg.GetFanSetting(fan, m_nVGASel, m_nVGAProSel);
	m_btn[BTN_HOME_SEMIPASS].SetCheck(fan.bFanStop ? true : false);

	// Peter Lee 2017/6/18 marked
/*#ifndef _DEBUG*/
	UpdateCardSelCombbox(DEVICE_VGA);

	if (!m_DevVGA.Ctrl()->IsVgaCard())
		return;

	m_MobileCtrl.init();
	m_VgaHomeDlg.InitState();
	m_VgaProDlg.InitState();
	m_DispClkDlg.InitState();

	m_LedDlg[DEVICE_VGA - 1].InitState();              

	m_KBLedDlg.InitState();//Terry 2017/07/12
	m_settingDlg.Initstate();
	m_CMonitorDlg.InitState();
	
	CXK700Cmd::SetLEDStatus(false); 
	CKbLedCtrl::LoadMemory();//update by terry 2017/6/22
	m_MacroKeyDlg.SetDeviceType(DEVICE_AK700);
	m_MacroKeyDlg.InitMacroState();
	m_KeyAssignDlg.InitState();
	if (m_DevVGA.Ctrl()->IsLedCard())
	{
		AfxBeginThread(KeepLedMonitor, this);
	}
	CXK700Cmd::SetLEDStatus(true);
/*#endif*/

// 	CKbLedCtrl::LoadMemory();//update by terry 2017/6/22
// 	m_MacroKeyDlg.SetDeviceType(DEVICE_AK700);
// 	m_MacroKeyDlg.InitMacroState();
// 	m_KeyAssignDlg.InitState();
}

// This function is called by LED dialog 
// to show LED color in LED icon synchronously
void CAORUSDlg::SyncLedBtnClr(COLORREF clr)
{
	m_btn[BTN_HOME_LED].SetBkColor(clr);
}

LRESULT CAORUSDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_HOME_REMOTE: {
		CRect rcRect,rcMainClient;
		::GetWindowRect(m_hWnd,rcMainClient);
		m_cRemoteSettingDlg.GetClientRect(&rcRect);
		rcRect.MoveToXY(CPoint(rcMainClient.left+170, rcMainClient.top+159));
		m_cRemoteSettingDlg.MoveWindow(rcRect);
		m_cRemoteSettingDlg.ShowWindow(SW_SHOW);
		m_cRemoteSettingDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		((CAORUSDlg*)AfxGetMainWnd())->Enable(FALSE);
						  } break;
	case BTN_HOME_SETTING: { // show setting dialog
		CRect rcRect,rcMainClient,rcdesk;
		GetDesktopWindow()->GetClientRect(rcdesk);
		m_settingDlg.GetClientRect(&rcRect);
		rcRect.MoveToXY(CPoint(rcdesk.right/2-150, rcdesk.bottom/2-120));
		m_settingDlg.MoveWindow(rcRect);
		m_settingDlg.ShowWindow(SW_SHOW);
		m_settingDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		((CAORUSDlg*)AfxGetMainWnd())->Enable(FALSE);
						   } break;
	case BTN_HOME_MIN: OnMinimize(); break;
	case BTN_HOME_CLOSE: {
		//退出關閉統一控燈進程
		KillProcessFromName(_T("GvLedService.exe"));

		VGA_PARAM_BASESETTING base;
		m_Cfg.GetBaseSetting(base);
		base.bCloseMin ? OnMinimize() : OnClose();
						 } break;
	case BTN_HOME_MENULEFT:	break;
	case BTN_HOME_MENURIGHT:break;
	case BTN_HOME_MONIT: { // show monitoring dialog		
		CRect rcCli;
		GetClientRect(rcCli);
		ClientToScreen(&rcCli);
		m_CMonitorDlg.OnFit(rcCli);
		m_CMonitorDlg.ShowWindow(m_btn[BTN_HOME_MONIT].IsCheck()? SW_SHOW : SW_HIDE);
						 } break;
	case BTN_HOME_SEMIPASS: {
		FAN_SETTING fansetting;

		int nMode=m_Cfg.GetVgaMode(m_nVGASel);
		if (nMode!=VGA_MODE_USER)
			m_Cfg.GetCurFanSetting(fansetting,m_nVGASel);
		else
			m_Cfg.GetFanSetting(fansetting,m_nVGASel,m_nVGAProSel);
		fansetting.bFanStop=m_btn[BTN_HOME_SEMIPASS].IsCheck();
		m_DevVGA.Ctrl()->SetFanSetting(m_nVGASel,fansetting);
		if (nMode!=VGA_MODE_USER)
			m_Cfg.SetCurFanSetting(fansetting,m_nVGASel);
		else
			m_Cfg.SetFanSetting(fansetting,m_nVGASel,m_nVGAProSel);
		m_VgaProDlg.PostMessage(WM_FANTOP_BTN_CHANGE,fansetting.bFanStop);
							} break;
	case BTN_HOME_BACKHOME: 
		m_panel[PAN_HOME_DEVICE].SetCurItemById(DEVICE_VGA); 
		SwitchDevice(DEVICE_VGA); break;
	case BTN_HOME_LED: SwitchUI(BTN_HOME_LED); break;
	case BTN_HOME_ENTERPRO: SwitchUI(BTN_HOME_ENTERPRO); break;
	case BTN_HOME_DEVARROWL: m_nDevShiftL--; UpdateDeivceIcons(); break;
	case BTN_HOME_DEVARROWR: m_nDevShiftL++; UpdateDeivceIcons(); break;
	case BTN_HOME_MACRO: { // show MacroKey dialog		
		CRect rcCli;
		GetClientRect(rcCli);
		ClientToScreen(&rcCli);
		m_MacroKeyDlg.OnFit(rcCli);

		m_MacroKeyDlg.SetDeviceType(m_nDeviceSel);
		m_MacroKeyDlg.InitMacroState();

		m_MacroKeyDlg.IsWindowVisible() ? m_MacroKeyDlg.ShowWindow(SW_HIDE) : m_MacroKeyDlg.ShowWindow(SW_SHOW);

		//Terry 2017/07/05
		m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_HIDE);
		m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_HIDE);
//		m_MacroKeyDlg.ShowWindow(m_btn[BTN_HOME_MACRO].IsCheck()? SW_SHOW : SW_HIDE);
						 } break;
	case BTN_HOME_POINTER: 
		SwitchUI(BTN_HOME_POINTER); 
		m_MousePointerDlg.InitState();
		break;
	case BTN_HOME_MOUSEBUTTON:
		SwitchUI(BTN_HOME_MOUSEBUTTON);
		m_MouseButtonDlg.InitBtnState(); 
		m_MouseButtonDlg.GetMacrosList();
		break;
	case BTN_HOME_KEYASSIGN: 
		SwitchUI(BTN_HOME_KEYASSIGN); 
	//	m_KeyAssignDlg.m_StyleDlg.SetMultiKeyFocus();
		m_KeyAssignDlg.InitState();
		break;
	default:break;
	}
	return 1;
}

LRESULT CAORUSDlg::OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nPanelSel = (int)wParam;
	int nItemSel  = (int)lParam;
	switch(nPanelSel)
	{
	case PAN_HOME_DEVICE: SwitchDevice(nItemSel); break;
	}
	return 0;
}

LRESULT CAORUSDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case COMB_HOME_CARDSEL:
		if (m_nDeviceSel != DEVICE_VGA)
			break;  
		if(lParam == m_DevVGA.Ctrl()->GetGpuCount()) lParam = -1; // 选择All Card，仅LED
		m_nVGASel = lParam;
		m_LastVgaSel = lParam;
		FAN_SETTING fansetting;
		m_Cfg.GetCurFanSetting(fansetting , m_nVGASel);
		m_btn[BTN_HOME_SEMIPASS].SetCheck(fansetting.bFanStop? true : false);
		m_nVGAProSel=m_Cfg.GetProfileSel(m_nVGASel);
		m_VgaProDlg.OnUpdateUI();
		m_VgaHomeDlg.UpdateUI();
		m_LedDlg[DEVICE_VGA - 1].InitializeUI();
		break;
	}
	return 1;	
}

int CAORUSDlg::GetDeviceSel()
{
	return m_nDeviceSel;
}

void CAORUSDlg::SwitchUI(int nBtnClick)
{
	m_VgaHomeDlg.ShowWindow(SW_HIDE);
	m_DispClkDlg.ShowWindow(SW_HIDE);
	m_VgaProDlg.ShowWindow(SW_HIDE);
	m_KeyAssignDlg.ShowWindow(SW_HIDE);
	m_KBLedDlg.ShowWindow(SW_HIDE);
	m_MousePointerDlg.ShowWindow(SW_HIDE);
	m_MouseButtonDlg.ShowWindow(SW_HIDE);

	//Terry 2017/07/05
	m_MacroKeyDlg.ShowWindow(SW_HIDE);


	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		m_LedDlg[i].ShowWindow(SW_HIDE);
	}
	m_stc[STC_HOME_RGB_FUSION].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_ENTERPRO].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_MACRO].ShowWindow(SW_HIDE);

	if (nBtnClick == BTN_HOME_BACKHOME) // Go back home dialog
	{
		m_VgaHomeDlg.UpdateUI();
		m_VgaProDlg.UIShowCustomized(false);
		bool bIsOneStepCard = m_DevVGA.Ctrl()->IsOneStepCard();
		m_VgaHomeDlg.ShowWindow(bIsOneStepCard ? SW_SHOW : SW_HIDE);
		m_DispClkDlg.ShowWindow(bIsOneStepCard ? SW_SHOW : SW_HIDE);
		m_btn[BTN_HOME_ENTERPRO].ShowWindow(bIsOneStepCard ? SW_SHOW : SW_HIDE);
		m_VgaProDlg.ShowWindow(bIsOneStepCard ? SW_HIDE : SW_SHOW);
		UpdateCardSelCombbox(DEVICE_VGA);
	}
	else if(nBtnClick == BTN_HOME_ENTERPRO) // Enter VGA pro mode
	{
		m_VgaProDlg.OnUpdateUI();
		m_VgaHomeDlg.ShowWindow(SW_HIDE);
		m_DispClkDlg.ShowWindow(SW_HIDE);
		m_btn[BTN_HOME_ENTERPRO].ShowWindow(SW_HIDE);
		m_VgaProDlg.ShowWindow(SW_SHOW);
	}
	else if(nBtnClick == BTN_HOME_LED)
	{
		switch(m_nDeviceSel)
		{
		case DEVICE_VGA: {
			m_LedDlg[DEVICE_VGA - 1].ShowWindow(SW_SHOW);
			m_LedDlg[DEVICE_VGA - 1].InitializeUI();
			m_stc[STC_HOME_RGB_FUSION].ShowWindow(SW_SHOW);
			UpdateCardSelCombbox(DEVICE_VGA);
						 } break;
		case DEVICE_SLI:
		case DEVICE_MB:
		case DEVICE_ATC700:
		case DEVICE_AC300:
		case DEVICE_AH300:
		case DEVICE_H5:
		case DEVICE_AM300:
			m_LedDlg[m_nDeviceSel - 1].ShowWindow(SW_SHOW);
			m_LedDlg[m_nDeviceSel - 1].InitializeUI();
			m_btn[BTN_HOME_MACRO].ShowWindow(SW_SHOW);
		//	m_stc[STC_HOME_RGB_FUSION].ShowWindow(SW_SHOW);
			break;
		case DEVICE_AK700:
			m_KBLedDlg.ShowWindow(SW_SHOW);
			CRect rcCli;
			GetClientRect(rcCli);
			ClientToScreen(&rcCli);
			m_KBLedDlg.m_LedStyleDlg.OnFit(rcCli);
			//	m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_MACRO].ShowWindow(SW_SHOW);
			//update by Terry 2017/6/23
			if (!m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
			{
				m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_SHOW);
				m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_HIDE);
			}
			else{
				m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_HIDE);
			}

			break;
		} 
		m_VgaProDlg.UIShowCustomized(false);
	}
	else if (nBtnClick == BTN_HOME_POINTER)
	{
		m_MousePointerDlg.ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_MACRO].ShowWindow(SW_SHOW);
	}
	else if (nBtnClick == BTN_HOME_MOUSEBUTTON)
	{
		m_MouseButtonDlg.ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_MACRO].ShowWindow(SW_SHOW);
	}
	else if (nBtnClick == BTN_HOME_KEYASSIGN)
	{
		m_KeyAssignDlg.ShowWindow(SW_SHOW); 
		m_btn[BTN_HOME_MACRO].ShowWindow(SW_SHOW);

		//Terry 2017/6/23
		CRect rcCli;
		GetClientRect(rcCli);
		ClientToScreen(&rcCli);
		m_KeyAssignDlg.m_StyleDlg.OnFit(rcCli);
		if (!m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
		{
			m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_SHOW);
			m_KeyAssignDlg.m_StyleDlg.SetMultiKeyFocus();
		}
		else{
			m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_HIDE);
		}
	}

	if(DEVICE_VGA != m_nDeviceSel && m_CMonitorDlg.IsWindowVisible()) 
	{
		m_btn[BTN_HOME_MONIT].SetCheck(false); m_CMonitorDlg.ShowWindow(SW_HIDE); 
	}
	if(DEVICE_AK700 != m_nDeviceSel && 
		DEVICE_AM300 != m_nDeviceSel && m_MacroKeyDlg.IsWindowVisible()) 
	{
		m_btn[BTN_HOME_MACRO].SetCheck(false); m_MacroKeyDlg.ShowWindow(SW_HIDE); 
	}
	if(!m_KBLedDlg.IsWindowVisible()) 
	{
		m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_HIDE); 
	}
}

// According to the device selected, 
// change items in COMB_HOME_CARDSEL combbox, 
// and show or hide the combbox
void CAORUSDlg::UpdateCardSelCombbox(int nDeviceId)
{
	m_combobox[COMB_HOME_CARDSEL].ResetContent();
	if (nDeviceId != DEVICE_VGA && nDeviceId != DEVICE_MB)		
	{
		m_combobox[COMB_HOME_CARDSEL].ShowWindow(SW_HIDE);
		return;
	}

	m_combobox[COMB_HOME_CARDSEL].ShowWindow(SW_SHOW);
	if (nDeviceId == DEVICE_VGA)
	{
		// show VGA name
		int nGpuCount = m_DevVGA.Ctrl()->GetGpuCount();
		for (int i = 0;i < nGpuCount; i++)
		{
			// switch GBT/Aorus logo 
			bool bIsAorus = m_DevVGA.Ctrl()->IsAorus();
			m_stc[STC_HOME_AORUS_LOGO].ShowWindow(bIsAorus ? SW_SHOW : SW_HIDE);
			m_stc[STC_HOME_GIGABYTE_LOGO].ShowWindow(bIsAorus ? SW_HIDE : SW_SHOW);

			// show card's model name
			CString sCardName = _T("");
			VGA_CARD_INFO const* pCardInfo = m_DevVGA.Ctrl()->GetCardInfo();
			sCardName.Format(L"Card %d",i + 1);
			if (_T("") != pCardInfo->sModelName)
			{
				sCardName = pCardInfo->sModelName;
				if (nGpuCount > 1)
				{
					CString sIdx = _T("");
					sIdx.Format(_T("(%d)"), i + 1);
					sCardName += sIdx;
				}
			}
			m_combobox[COMB_HOME_CARDSEL].AddString(sCardName, 0, CLR_WHITE);
		}

		if(m_LedDlg[DEVICE_VGA - 1].IsWindowVisible()) 
		{
			//m_combobox[COMB_HOME_CARDSEL].AddString(CLangX::Get(LANG_AORUS_ALLCARD), 0, CLR_WHITE);
			m_combobox[COMB_HOME_CARDSEL].SetCurSel((m_nVGASel + m_combobox[COMB_HOME_CARDSEL].GetCount()) % m_combobox[COMB_HOME_CARDSEL].GetCount());
		}
		else
		{
			m_combobox[COMB_HOME_CARDSEL].SetCurSel(m_nVGASel >= 0 ? m_nVGASel % m_combobox[COMB_HOME_CARDSEL].GetCount() : 0);
		}
	}
	else if(DEVICE_MB == nDeviceId)
	{
		// show MB name
		CString sMBName  = _T("");
		m_DevMB.Ctrl()->GetModuleName(sMBName);
		if (_T("") == sMBName)
		{
			sMBName = CLangX::Get(LANG_AORUS_MOTHERBOARD);
		}
		m_combobox[COMB_HOME_CARDSEL].AddString(sMBName, 0, CLR_WHITE);
		m_combobox[COMB_HOME_CARDSEL].SetCurSel(0);
	}
}

void CAORUSDlg::SyncMobile(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0:m_MobileCtrl.syncLedState();break;
	case 1:m_MobileCtrl.monitor();break;
	}
}

void CAORUSDlg::Enable(bool bEnable)
{
	m_CMonitorDlg.EnableWindow(bEnable);
	m_MacroKeyDlg.EnableWindow(bEnable);
	EnableWindow(bEnable);
}

bool CAORUSDlg::IsMonitorShow()
{
	return NULL != m_btn[BTN_HOME_MONIT].GetSafeHwnd() && m_btn[BTN_HOME_MONIT].IsCheck();
}

void CAORUSDlg::MobileUpdateUI(int nWhatToUpdate)
{
	switch(nWhatToUpdate)
	{
	case 0: m_VgaHomeDlg.UpdateUI(); m_DispClkDlg.UpdateUI(); break;
	case 1: m_LedDlg[DEVICE_VGA - 1].InitializeUI(); break;
	}
}

void CAORUSDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if(m_CMonitorDlg.GetSafeHwnd() != NULL && 
		m_CMonitorDlg.IsWindowVisible())
	{
		m_CMonitorDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if(m_MacroKeyDlg.GetSafeHwnd() != NULL && 
		m_MacroKeyDlg.IsWindowVisible())
	{
		m_MacroKeyDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if (m_VgaProDlg.GetSafeHwnd() != NULL && 
		m_VgaProDlg.m_CustomizedDlg.GetSafeHwnd() != NULL && 
		m_VgaProDlg.m_CustomizedDlg.IsWindowVisible())
	{
		m_VgaProDlg.m_CustomizedDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if (NULL != m_KBLedDlg.GetSafeHwnd() && m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
	{
		m_KBLedDlg.m_LedStyleDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if (m_KeyAssignDlg.GetSafeHwnd() != NULL && 
		m_KeyAssignDlg.m_StyleDlg.GetSafeHwnd() != NULL && 
		m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
	{
		m_KeyAssignDlg.m_StyleDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	CUiDlg::OnActivate(nState, pWndOther, bMinimized);
}

void CAORUSDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	OnFollowMove(0, *pRect);  // User-Defined Fan Curve
	OnFollowMove(1, *pRect);  // VGA Monitor Dialog
	OnFollowMove(2, *pRect);  // MacroKey Dialog
	OnFollowMove(3, *pRect);  // KB Led Style Dialog
	OnFollowMove(4, *pRect);  // KB Key Assign Style Dialog
	CUiDlg::OnMoving(fwSide, pRect);
}

CRect CAORUSDlg::OnFit(CRect rcCli, int nLeft, int nTop)
{
	int nX = rcCli.left + nLeft;
	int nY = rcCli.top  + nTop;
	SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
	SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	GetClientRect(rcCli);
	rcCli.MoveToXY(nX, nY);
	return rcCli;
}

void CAORUSDlg::OnFollowMove(int nType, CRect rc)
{
	switch(nType)
	{
	case 0:  // Notify from: User-Defined Fan Curve 
		if (m_CMonitorDlg.IsWindowVisible())
		{
			m_CMonitorDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_CMonitorDlg.OnFit(rc);
		}
		if (m_MacroKeyDlg.IsWindowVisible())
		{
			m_MacroKeyDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_MacroKeyDlg.OnFit(rc);
		}
		if (m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
		{
			m_KBLedDlg.m_LedStyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KBLedDlg.m_LedStyleDlg.OnFit(rc);
		}
		if (m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
		{
			m_KeyAssignDlg.m_StyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KeyAssignDlg.m_StyleDlg.OnFit(rc);
		}
		break;
	case 1:  // Notify from: VGA Monitor Dialog
		if (m_VgaProDlg.m_CustomizedDlg.IsWindowVisible())
		{
			m_VgaProDlg.m_CustomizedDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_VgaProDlg.m_CustomizedDlg.OnFit(rc);
		}
		if (m_MacroKeyDlg.IsWindowVisible())
		{
			m_MacroKeyDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_MacroKeyDlg.OnFit(rc);
		}
		if (m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
		{
			m_KBLedDlg.m_LedStyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KBLedDlg.m_LedStyleDlg.OnFit(rc);
		}
		if (m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
		{
			m_KeyAssignDlg.m_StyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KeyAssignDlg.m_StyleDlg.OnFit(rc);
		}
		break;
	case 2: // Notify from: MacroKey Dialog
		if (m_CMonitorDlg.IsWindowVisible())
		{
			m_CMonitorDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_CMonitorDlg.OnFit(rc);
		}
		if (m_VgaProDlg.m_CustomizedDlg.IsWindowVisible())
		{
			m_VgaProDlg.m_CustomizedDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_VgaProDlg.m_CustomizedDlg.OnFit(rc);
		}
		if (m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
		{
			m_KBLedDlg.m_LedStyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KBLedDlg.m_LedStyleDlg.OnFit(rc);
		}
		if (m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
		{
			m_KeyAssignDlg.m_StyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KeyAssignDlg.m_StyleDlg.OnFit(rc);
		}
		break;
	case 3: // Notify from: KB Led Style Dialog
		if (m_CMonitorDlg.IsWindowVisible())
		{
			m_CMonitorDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_CMonitorDlg.OnFit(rc);
		}
		if (m_VgaProDlg.m_CustomizedDlg.IsWindowVisible())
		{
			m_VgaProDlg.m_CustomizedDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_VgaProDlg.m_CustomizedDlg.OnFit(rc);
		}
		if (m_MacroKeyDlg.IsWindowVisible())
		{
			m_MacroKeyDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_MacroKeyDlg.OnFit(rc);
		}
		if (m_KeyAssignDlg.m_StyleDlg.IsWindowVisible())
		{
			m_KeyAssignDlg.m_StyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KeyAssignDlg.m_StyleDlg.OnFit(rc);
		}
	case 4: // Notify from: KB Key Assign Style Dialog
		if (m_CMonitorDlg.IsWindowVisible())
		{
			m_CMonitorDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_CMonitorDlg.OnFit(rc);
		}
		if (m_VgaProDlg.m_CustomizedDlg.IsWindowVisible())
		{
			m_VgaProDlg.m_CustomizedDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_VgaProDlg.m_CustomizedDlg.OnFit(rc);
		}
		if (m_MacroKeyDlg.IsWindowVisible())
		{
			m_MacroKeyDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_MacroKeyDlg.OnFit(rc);
		}
		if (m_KBLedDlg.m_LedStyleDlg.IsWindowVisible())
		{
			m_KBLedDlg.m_LedStyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			m_KBLedDlg.m_LedStyleDlg.OnFit(rc);
		}
		break;
	}
}

void CAORUSDlg::OnMinimize()
{
	m_trayIcon.Minimize();
	if (NULL != m_CMonitorDlg.GetSafeHwnd()) 
	{
		m_CMonitorDlg.ShowWindow(SW_HIDE);
	}
	if (NULL != m_MacroKeyDlg.GetSafeHwnd()) 
	{
		m_MacroKeyDlg.ShowWindow(SW_HIDE);
	}
	if (NULL != m_VgaProDlg.GetSafeHwnd())  
	{
		m_VgaProDlg.m_CustomizedDlg.ShowWindow(SW_HIDE);
	}
	if (NULL != m_KBLedDlg.GetSafeHwnd())
	{
		m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_HIDE);
	}
	if (NULL != m_KeyAssignDlg.GetSafeHwnd())  
	{
		m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_HIDE);
	}
}

void CAORUSDlg::OnClose()
{
	m_bWinClose = true; 
	Sleep(10); // notify another thread to stop led monitoring
	ShowWindow(SW_HIDE);
	m_CMonitorDlg.ShowWindow(SW_HIDE);
	m_MacroKeyDlg.ShowWindow(SW_HIDE);
	m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_HIDE);
	::SendMessage(m_hWnd, WM_DESTROY, 0, 0);
	::PostQuitMessage(0);
}

void CAORUSDlg::OnOpen()
{
	m_trayIcon.Restore();
	m_CMonitorDlg.ShowWindow(IsMonitorShow() ? SW_HIDE : SW_SHOW);
	bool bWinShow = (NULL != m_btn[BTN_HOME_MACRO].GetSafeHwnd() && m_btn[BTN_HOME_MACRO].IsCheck());
	m_MacroKeyDlg.ShowWindow(bWinShow ? SW_HIDE : SW_SHOW);
	bWinShow = m_KBLedDlg.IsWindowVisible() ? true : false;
	m_KBLedDlg.m_LedStyleDlg.ShowWindow(bWinShow ? SW_HIDE : SW_SHOW);
}

LRESULT CAORUSDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case WM_BALLOON_CLICKED: m_DevVGA.Ctrl()->SoftwareUpdate(); break;	// Load as default state.
	case WM_BALLOON_TIMEOUT: m_trayIcon.ShowTrayIcon();  break;	
	}
	return 0;
}

void CAORUSDlg::OnSize(UINT nType, int cx, int cy)
{
	CUiDlg::OnSize(nType, cx, cy);

	switch(nType)
	{
	case SIZE_MINIMIZED: break;
	case SIZE_RESTORED:	
		if (NULL != m_CMonitorDlg.GetSafeHwnd() && m_btn[BTN_HOME_MONIT].IsCheck())
		{
			m_CMonitorDlg.ShowWindow(SW_SHOW);
			m_CMonitorDlg.SetForegroundWindow();
		}
		if (NULL != m_MacroKeyDlg.GetSafeHwnd() && m_btn[BTN_HOME_MACRO].IsCheck())
		{
			m_MacroKeyDlg.ShowWindow(SW_SHOW);
			m_MacroKeyDlg.SetForegroundWindow();
		}
		if (NULL != m_KBLedDlg.GetSafeHwnd() && m_KBLedDlg.IsWindowVisible())
		{
			m_KBLedDlg.m_LedStyleDlg.ShowWindow(SW_SHOW);
			m_KBLedDlg.m_LedStyleDlg.SetForegroundWindow();
		}

// 		if (NULL != m_KeyAssignDlg.GetSafeHwnd() && m_KeyAssignDlg.IsWindowVisible())
// 		{
// 			m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_SHOW);
// 			m_KeyAssignDlg.m_StyleDlg.SetForegroundWindow();
// 		}
		break;
	case SIZE_MAXSHOW:	break;
	}
}

void CAORUSDlg::SwitchDevice(int nDeviceId)
{
	// if show 1 icons, the location of icons:
	// CRect(494, 501, 0, 0)
	// if show 2 icons, the location of icons:
	// CRect(557, 431, 0, 0), CRect(501, 483, 0, 0) 
	// if show 3 icons, the location of icons:
	// CRect(494, 501, 0, 0), CRect(518, 456, 0, 0), CRect(569, 424, 0, 0)

	m_btn[BTN_HOME_LED].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_MONIT].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_SEMIPASS].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_POINTER].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_MOUSEBUTTON].ShowWindow(SW_HIDE);
	m_btn[BTN_HOME_KEYASSIGN].ShowWindow(SW_HIDE);

	//Terry 2017/06/28 
	m_KBLedDlg.ShowWindow(SW_HIDE);
	m_KeyAssignDlg.m_StyleDlg.ShowWindow(SW_HIDE);
	m_MacroKeyDlg.ShowWindow(SW_HIDE);
	
	m_nDeviceSel = nDeviceId;
	switch(nDeviceId)
	{
	case DEVICE_VGA: {
		m_nVGASel = m_LastVgaSel;  
		SwitchUI(BTN_HOME_BACKHOME);
		UpdateCardSelCombbox(m_nDeviceSel);
		// Icons location
		bool bShowLed = m_DevVGA.Ctrl()->IsLedCard();
		bool bShowFan = m_DevVGA.Ctrl()->IsSupportFanStop();
		if (bShowLed && bShowFan)
		{
			m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_MONIT].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_SEMIPASS].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_LED].MoveWindow(494, 501, 48,  48);
			m_btn[BTN_HOME_MONIT].MoveWindow(518, 456, 48,  48);
			m_btn[BTN_HOME_SEMIPASS].MoveWindow(569, 424, 55, 33);
		}
		else if(bShowLed)
		{
			m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_MONIT].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_LED].MoveWindow(501, 483, 48, 48);
			m_btn[BTN_HOME_MONIT].MoveWindow(557, 431, 48, 48);
		}
		else if (bShowFan)
		{
			m_btn[BTN_HOME_MONIT].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_SEMIPASS].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_MONIT].MoveWindow(501, 483, 48, 48);
			m_btn[BTN_HOME_SEMIPASS].MoveWindow(557, 431, 55, 33);
		}
		else if (!bShowLed && !bShowFan)
		{
			m_btn[BTN_HOME_MONIT].ShowWindow(SW_SHOW);
			m_btn[BTN_HOME_MONIT].MoveWindow(494, 501, 48,  48);
		}
		break; }
	case DEVICE_SLI:
		m_nVGASel = m_DevVGA.Ctrl()->GetGpuCount();  
		SwitchUI(BTN_HOME_LED);
		UpdateCardSelCombbox(m_nDeviceSel);
		m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_LED].MoveWindow(494, 501, 48,  48);
		break;
	case DEVICE_MB:
	case DEVICE_ATC700:
	case DEVICE_AC300:
	case DEVICE_H5:
	case DEVICE_AH300:
		SwitchUI(BTN_HOME_LED);
		UpdateCardSelCombbox(m_nDeviceSel);	
		m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_LED].MoveWindow(494, 501, 48,  48);
		break;
	case DEVICE_AM300:
		SwitchUI(BTN_HOME_LED);
		UpdateCardSelCombbox(m_nDeviceSel);	
		m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_MOUSEBUTTON].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_POINTER].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_LED].MoveWindow(494, 501, 48,  48);
		m_btn[BTN_HOME_MOUSEBUTTON].MoveWindow(518, 456, 45,  45);
		m_btn[BTN_HOME_POINTER].MoveWindow(569, 424, 45, 45);
		break;
	case DEVICE_AK700:
		SwitchUI(BTN_HOME_LED);
		UpdateCardSelCombbox(m_nDeviceSel);	
		m_btn[BTN_HOME_LED].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_KEYASSIGN].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_LED].MoveWindow(501, 483, 48,  48);
		m_btn[BTN_HOME_KEYASSIGN].MoveWindow(552, 426, 50,  50);//557 431 55 33
		break;
	}
}
bool CAORUSDlg::GetFanStopState()
{
	return m_btn[BTN_HOME_SEMIPASS].IsCheck();
}

#pragma region Monitor USB deivce: plug in or remove. Show or remove device icon.

// receive WM_DEIVCE_CHANGE message & handle it.

BOOL CAORUSDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	CString HID_list_string;
	DEV_BROADCAST_DEVICEINTERFACE* dev = (DEV_BROADCAST_DEVICEINTERFACE*)dwData;

	if (NULL == dev)
		return FALSE;

	CString sDevice(dev->dbcc_name); // Device ID desc: such as: USB\VID_1044&PID_7A15&REV_0200&MI_01

	// Checks if the deviceType is correct

	if (dev->dbcc_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
		return FALSE;

	switch(nEventType)
	{
		// Device been plugged in and useful
	case DBT_DEVICEARRIVAL: ScanDevice(sDevice); break; 
		// Device been removed
	case DBT_DEVICEREMOVECOMPLETE: FreeDevice(sDevice); break;
	case DBT_DEVICEQUERYREMOVE: break;
	case DBT_DEVICEQUERYREMOVEFAILED: break;
	case DBT_DEVICEREMOVEPENDING: break;
	case DBT_DEVICETYPESPECIFIC: break;
	case DBT_CONFIGCHANGED: break;
	case DBT_DEVNODES_CHANGED: break;
	default: break;
	}
	return FALSE;
}

// scan new device 
void CAORUSDlg::ScanDevice(CString sDevice)
{
	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = GetDevice(s_DevIds[i]);
		if (pDevice->IsThisDevice(sDevice) && !pDevice->IsConnected())
		{
			AfxBeginThread(OnScanDevice, this); // Load new device
			break;
		}
	}
}

// remove device
void CAORUSDlg::FreeDevice(CString sDevice)
{
	// Upate the AORUS's device pannel UI

	CArray<UINT> devicesToNoShow;
	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = GetDevice(s_DevIds[i]);
		if (pDevice->IsThisDevice(sDevice) && pDevice->IsConnected())
		{
			pDevice->Unconnect();
			devicesToNoShow.Add(s_DevIds[i]);
		}
	}

	if(devicesToNoShow.GetSize() > 0)
	{
		ShowDeviceIcons(devicesToNoShow, false);

		// device removed, to make sure led dialog's sync led button show/hide.
		for (int i = 0; i < DEVICE_COUNT; i++)
		{
			CDevice* pDevice = GetDevice(s_DevIds[i]);
			if (pDevice->IsConnected())
			{
				m_LedDlg[pDevice->GetDeviceId() - 1].InitState();
			}
		}
	}
}

void CAORUSDlg::ScanDevices()
{
	Lock();
	CArray<UINT> devicesToShow;
	AfxGetMainWnd()->EnableWindow(FALSE);
	ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW); 
	if(IsWindowVisible()) 
	{
		SetForegroundWindow();
	}

	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = GetDevice(s_DevIds[i]);
		if (!pDevice->IsConnected() && pDevice->OnConnect())
		{
			devicesToShow.Add(s_DevIds[i]);
		}
	}

	// Initialize led dialog after checking device connection:
	// then we can know how many devices are connected exactly,
	// and make sure Led dialog's sync led button show/hide. 

	if (devicesToShow.GetSize() > 0)
	{
		ShowDeviceIcons(devicesToShow, true);
		for (int i = 0; i < DEVICE_COUNT; i++)
		{
			CDevice* pDevice = GetDevice(s_DevIds[i]);
			if (pDevice->IsConnected())
			{
				m_LedDlg[pDevice->GetDeviceId() - 1].InitState();
				m_KBLedDlg.InitState();//Terry 2017/07/13
			}
		}
	}

	ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
	AfxGetMainWnd()->EnableWindow(TRUE);

	Unlock();
}

// Callback function: 
UINT CAORUSDlg::OnScanDevice(LPVOID pParam)
{
	((CAORUSDlg*)pParam)->ScanDevices(); return 0;
}

// create device icons in AORUS's main UI
void CAORUSDlg::CreateDeivceIcons()
{
	if (NULL != m_panel[PAN_HOME_DEVICE].GetSafeHwnd())
		return; // has created yet.

	m_panel[PAN_HOME_DEVICE].Create(this, PAN_HOME_DEVICE, CRect(34, 468, 431, 561));  

	// create separation lines

	UINT lineIds[] = {
		DEVICE_LINE1,
		DEVICE_LINE2,
		DEVICE_LINE3,
	};
	CRect rcLine[] = { // separation line
		CRect( 85, 14, 0, 0), 
		CRect(195, 14, 0, 0), 
		CRect(310, 14, 0, 0),
	};	

	for (int i = 0; i < 3; i++)
	{
		m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(lineIds[i], rcLine[i], &UIPC_IMAGE(IDB_DEVICE_LINE, IDB_DEVICE_LINE, IDB_DEVICE_LINE, IDB_DEVICE_LINE, CLR_TRPT)));
		m_panel[PAN_HOME_DEVICE].EnableItemById(lineIds[i], false);
	}

	// create deivce icons.

	bool bIXEB = m_DevVGA.Ctrl()->IsIXEBCard();

	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM( 
		DEVICE_VGA, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_HOME_VGAOFF, IDB_HOME_VGAON, IDB_HOME_VGAON, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(!bIXEB ? LANG_AORUS_VGA : LANG_AORUS_IXEB), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_SLI, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_2WAYSLI_OFF, IDB_2WAYSLI_ON, IDB_2WAYSLI_ON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_SLI), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM( 
		DEVICE_MB, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_MBOARD_OFF, IDB_MBOARD_ON, IDB_MBOARD_ON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_MOTHRBOARD), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_ATC700, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_HOME_CPUCOOLEROFF, IDB_HOME_CPUCOOLERON, IDB_HOME_CPUCOOLERON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_CPU_COOLER), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_AC300, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_HOME_CASEOFF, IDB_HOME_CASEON, IDB_HOME_CASEON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_CASE), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_AH300, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_HOME_HEADSETOFF, IDB_HOME_HEADSETON, IDB_HOME_HEADSETON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_HEADSET), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_AM300, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_MOUSE_OFF, IDB_MOUSE_ON, IDB_MOUSE_ON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_MOUSE), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_AK700, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_KEYBOARD_OFF, IDB_KEYBOARD_ON, IDB_KEYBOARD_ON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_KB), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	m_panel[PAN_HOME_DEVICE].AddItem(&UIPC_ITEM(
		DEVICE_H5, 
		CRect( 10, 13, 0, 0),
		&UIPC_IMAGE(IDB_HOME_HEADSETOFF, IDB_HOME_HEADSETON, IDB_HOME_HEADSETON, 0, CLR_TRPT), 
		&UIPC_STRING(CLangX::Get(LANG_AORUS_HEADSET), CRect(0, 66, 75, 85), CLR_GRAY, CLR_MAIN, CLR_MAIN, CLR_BLACK, Font(11), Font(11), Font(11), Font(11))));
	// Set all device icons invisible, except the VGA icon

	int nItems = m_panel[PAN_HOME_DEVICE].GetItemCount();
	for (int i = 0; i < nItems; i++)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisible(i, false);
	}

	m_panel[PAN_HOME_DEVICE].SetCursor(IDC_CUR_HAND);
	m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_VGA, true);
	m_panel[PAN_HOME_DEVICE].SetCurItemById(DEVICE_VGA);
}

// Show or hide device icons
void CAORUSDlg::ShowDeviceIcons(CArray<UINT>& deviceIds, bool bShow)
{
	int nDevices = (int)deviceIds.GetSize();
	for (int i = 0; i < nDevices; i++)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(deviceIds.GetAt(i), bShow);
	}
	UpdateDeivceIcons();
}

// Update device icons in AORUS's main UI, 
// when different devices plugged in or removed
void CAORUSDlg::UpdateDeivceIcons()
{
	// Locaiton of icons
	CRect rcIcon[] = { // icon
		CRect( 10, 13, 0, 0), 
		CRect(113, 11, 0, 0), 
		CRect(225, 11, 0, 0), 
		CRect(337, 11, 0, 0),
	};
	CRect rcText[] = { // text below icon
		CRect(  0, 66,  75, 85), 
		CRect( 91, 66, 186, 85), 
		CRect(206, 66, 301, 85), 
		CRect(321, 66, 416, 85),
	};

	bool devicesExisted[DEVICE_COUNT] = { false };

	// How many devices existed.

	int nDevicesExisted = 0;
	CArray<UINT> devicesHere;
	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = GetDevice(s_DevIds[i]);
		if (pDevice->IsConnected())
		{
			nDevicesExisted++; devicesHere.Add(s_DevIds[i]); 
		}
	}

	if (nDevicesExisted <= 4) // less than 4 devices
	{
		m_btn[BTN_HOME_DEVARROWL].ShowWindow(SW_HIDE);
		m_btn[BTN_HOME_DEVARROWR].ShowWindow(SW_HIDE);
	}
	else if (m_nDevShiftL <= 0) // more than 4 devices
	{
		m_btn[BTN_HOME_DEVARROWL].ShowWindow(SW_HIDE);
		m_btn[BTN_HOME_DEVARROWR].ShowWindow(SW_SHOW);
	}
	else if (m_nDevShiftL + 4 >= nDevicesExisted)
	{
		m_btn[BTN_HOME_DEVARROWL].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_DEVARROWR].ShowWindow(SW_HIDE);
	}
	else 
	{
		m_btn[BTN_HOME_DEVARROWL].ShowWindow(SW_SHOW);
		m_btn[BTN_HOME_DEVARROWR].ShowWindow(SW_SHOW);
	}

	// How many separation lines to show.

	if (nDevicesExisted <= 1)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE1, false);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE2, false);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE3, false);
	}
	else if (2 == nDevicesExisted)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE1, true);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE2, false);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE3, false);
	}
	else if (3 == nDevicesExisted)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE1, true);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE2, true);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE3, false);
	}
	else if (nDevicesExisted >= 4)
	{
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE1, true);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE2, true);
		m_panel[PAN_HOME_DEVICE].SetItemVisibleById(DEVICE_LINE3, true);
	}

	// out of range

	if (m_nDevShiftL > nDevicesExisted - 4) { m_nDevShiftL = nDevicesExisted - 4; }
	if (m_nDevShiftL < 0) m_nDevShiftL = 0;

	bool bCurDevRemove = true;
	for (int k = 0; k < (int)devicesHere.GetSize(); k++)
	{
		if (m_nDeviceSel == devicesHere.GetAt(k)) { bCurDevRemove = false; break; }
	}
	if (bCurDevRemove)
	{
		m_nDeviceSel = devicesHere.GetAt(0);
	}

	// check how many devices to show

	int nDevicesShow = 0;
	int nShowFrom = m_nDevShiftL;
	int nShowTo = (m_nDevShiftL + 4 <= nDevicesExisted) ? (m_nDevShiftL + 4) : nDevicesExisted;
	for (int i = nShowFrom; i < nShowTo; i++)
	{
		UINT nDeviceId = devicesHere.GetAt(i);

		// Update deivce icon location
		UIPC_ITEM* pItem = m_panel[PAN_HOME_DEVICE].GetItemById(nDeviceId);
		int w = pItem->rect.Width();
		int h = pItem->rect.Height();
		pItem->rect.left = rcIcon[nDevicesShow].left;
		pItem->rect.right = pItem->rect.left + w;
		pItem->rect.top  = rcIcon[nDevicesShow].top;
		pItem->rect.bottom = pItem->rect.top + h;
		// Update device desc string location 
		pItem->strMode.rect = rcText[nDevicesShow];
		nDevicesShow++;
	}

	// Show/Hide devices

	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		bool bShow = false;
		UIPC_ITEM* pItem = m_panel[PAN_HOME_DEVICE].GetItemById(s_DevIds[i]);
		for (int k = nShowFrom; k < nShowTo; k++)
		{
			if (devicesHere.GetAt(k) == s_DevIds[i])
			{
				bShow = true; break;
			}
		}
		pItem->bVisible = bShow;
	}

	m_panel[PAN_HOME_DEVICE].SetCurItemById(m_nDeviceSel);
	if (bCurDevRemove)
	{
		SwitchDevice(m_nDeviceSel);
	}
}

void CAORUSDlg::OnRawInput(UINT nInputcode, HRAWINPUT hRawInput)
{
	UINT dwSize;
	BYTE lpb[1000];
	TCHAR lpb2[1000];
	RAWINPUT* raw;
	GetRawInputData(hRawInput, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
	if (dwSize < sizeof (lpb))
	{
		if (GetRawInputData(hRawInput, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize)
		{
			raw = (RAWINPUT*)lpb;
			if (raw->header.dwType == RIM_TYPEMOUSE)
			{
			}
			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
			}
			else if (raw->header.dwType == RIM_TYPEHID) // HID設備
			{
				UINT dwSize2;
				BYTE* byData = &raw->data.hid.bRawData[1];
				GetRawInputDeviceInfo(raw->header.hDevice,RIDI_DEVICENAME, NULL, &dwSize2); // 取得設備名稱的大小
				GetRawInputDeviceInfo(raw->header.hDevice,RIDI_DEVICENAME, lpb2, &dwSize2); // 取得設備名稱
				CString device;
				device.Format(_T("%s"), lpb2);
				if(device.Find(_T("7A2C")) > 0 || device.Find(_T("7A1A")) > 0) // xk700 104  105
				{
					m_DevAK700.OnHIDInput(raw);
				}
				//AM300
				else if (device.Find(_T("7A28")) > 0) // AM300
				{
					m_MousePointerDlg.OnHIDInput(byData);
				} 
			}
		}
	}
	CUiDlg::OnRawInput(nInputcode, hRawInput);
}


void CAORUSDlg::SwitchM3LedDlProfile(int iProfile)
{
	//m_LedDlg[DEVICE_AM300 - 1].SendMessage(WM_UI_COMBOBOX_SELCHANGED, 2, iProfile);
	m_LedDlg[DEVICE_AM300 - 1].ChangeCurProfile(iProfile);
}

void CAORUSDlg::SwitchM3ButtonProfile(int iProfile)
{
	m_MouseButtonDlg.ChangeCurProfile(iProfile);

}

void CAORUSDlg::SwitchAK700KeyProfile(int iProfile)
{
	m_KeyAssignDlg.ChangeCurProfile(iProfile);

}

void CAORUSDlg::SwitchAK700LedProfile(int iProfile)
{
	m_KBLedDlg.ChangeCurProfile(iProfile);

}


BOOL CAORUSDlg::KillProcessFromName(CString strProcessName)  
{  
	//创建进程快照(TH32CS_SNAPPROCESS表示创建所有进程的快照)  
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  

	//PROCESSENTRY32进程快照的结构体  
	PROCESSENTRY32 pe;  

	//实例化后使用Process32First获取第一个快照的进程前必做的初始化操作  
	pe.dwSize = sizeof(PROCESSENTRY32);  

	//下面的IF效果同:  
	//if(hProcessSnap == INVALID_HANDLE_VALUE)   无效的句柄  
	if(!Process32First(hSnapShot,&pe))  
	{  
		return FALSE;  
	}  

	//将字符串转换为小写  
	strProcessName.MakeLower();  

	//如果句柄有效  则一直获取下一个句柄循环下去  
	while (Process32Next(hSnapShot,&pe))  
	{  
		//pe.szExeFile获取当前进程的可执行文件名称  
		CString scTmp = pe.szExeFile;  

		//将可执行文件名称所有英文字母修改为小写  
		scTmp.MakeLower();  

		//比较当前进程的可执行文件名称和传递进来的文件名称是否相同  
		//相同的话Compare返回0  
		if(!scTmp.Compare(strProcessName))  
		{  
			//从快照进程中获取该进程的PID(即任务管理器中的PID)  
			DWORD dwProcessID = pe.th32ProcessID;  
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);  
			::TerminateProcess(hProcess,0);  
			CloseHandle(hProcess);  
			return TRUE;  
		}  
		scTmp.ReleaseBuffer();  
	}  
	strProcessName.ReleaseBuffer();  
	return FALSE;  
} 

#pragma endregion