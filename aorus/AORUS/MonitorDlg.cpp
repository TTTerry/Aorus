// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AORUS.h"
#include "MonitorDlg.h"
#include "AORUSDlg.h"



IMPLEMENT_DYNAMIC(CMonitorDlg, CUiDlg)

CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CMonitorDlg::IDD, pParent)
{
	m_nScrollPos = 0;
	m_pParent = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for(int i=0;i<MONI_GPH_NUM;i++)
	{
		 nMaxValue[i]=0;
		 nMinValue[i]=0;
	}
	m_bLOG = FALSE;
	m_nMonitorCount = 0;
	m_bMove = false;
}

CMonitorDlg::~CMonitorDlg()
{
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitorDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_SLIDER_MOVING, OnUiSliderMoving)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMonitorDlg message handlers

BOOL CMonitorDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	CUiDlg::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: Add extra initialization here

	SetWindowText(_T("GIGABYTE OC GURU Monitor"));

	Ui();
	//InitState();

	SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////////////////
//
// system message.
//
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CMonitorDlg::OnNcHitTest(CPoint point)
{
	UINT uRes = (UINT)CUiDlg::OnNcHitTest(point);
	if(uRes == HTCLIENT) 
	{
		uRes = HTCAPTION;
	}

	if(!m_bMove)
	{
		CAORUSDlg* pParent = (CAORUSDlg*)m_pParent;
		CRect rcCli;
		GetClientRect(rcCli);
		ClientToScreen(&rcCli);

		pParent->OnFit(rcCli, rcCli.Width(), -79);
	}

	return uRes;
}

void CMonitorDlg::OnPaint()
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

HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	CAORUSDlg* pParent = (CAORUSDlg*)m_pParent;
	CRect rcParentCli;
	pParent->GetClientRect(rcParentCli);
	pParent->ClientToScreen(&rcParentCli);
	if (nIDEvent == 0)
	{
		CRect rcMoniCli;
		GetClientRect(&rcMoniCli);
		ClientToScreen(&rcMoniCli);

		int nOffset = rcMoniCli.left - rcParentCli.right + 37;
		if(IsWindowVisible() && (nOffset < 5 && abs(nOffset) < 20))
		{
			OnDepart();
		}
	}
	if(TIMER_PERF_MONITOR == nIDEvent)
	{
		Monitoring();
	}
	if(2 == nIDEvent)
	{
		OnFit(rcParentCli);
		//ShowWindow(SW_SHOW);
		bool bShow = ((CAORUSDlg*)m_pParent)->IsMonitorShow();
		ResetScroll(MoveMoniotr(TRUE));
		ShowWindow(bShow ? SW_SHOW : SW_HIDE);
		KillTimer(2);
		SetTimer(3, 1, NULL);
	}
	CUiDlg::OnTimer(nIDEvent);
}

void CMonitorDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if(m_pParent != NULL)
	{
		m_pParent->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if (NULL != m_EditDlg.GetSafeHwnd() && m_EditDlg.IsWindowVisible())
	{
		m_EditDlg.SetForegroundWindow();
	}
	CUiDlg::OnActivate(nState, pWndOther, bMinimized);
}

void CMonitorDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CUiDlg::OnMoving(fwSide, pRect);

	if(!m_bMove)
	{
		CAORUSDlg* pParent = (CAORUSDlg*)m_pParent;
		CRect rcCli;
		GetClientRect(rcCli);
		ClientToScreen(&rcCli);

		pParent->OnFollowMove(1, pParent->OnFit(rcCli, rcCli.Width(), -79));
	}
}

void CMonitorDlg::OnMinimize()
{
	::PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void CMonitorDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// UI operate.
//
/////////////////////////////////////////////////////////////////////////////////////////
void CMonitorDlg::Ui(void)
{
	UiMain();
}

void CMonitorDlg::UiMain(void)
{
	SetBkBitmap(IDB_MONITORING_BG, 0xff, CLR_TRPT);
	m_stc[MONI_STC_SCROLL].CreateStatic(UI_STATIC(this, MONI_STC_SCROLL, CRect(414, 13, 426, 281), _T(""), 0, CLR_TRPT, WS_CHILD | WS_VISIBLE));

	UI_BTN btn[] = 
	{
		UI_BTN(&m_stc[MONI_STC_SCROLL], BTN_MON_UP,		CRect(0, 0,  0, 0),   &UIBTN_IMAGE(IDB_MONITOR_BTNUP_ON,   IDB_MONITOR_BTNUP_ON,   IDB_MONITOR_BTNUP_ON,   IDB_MONITOR_BTNUP_ON,   0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(&m_stc[MONI_STC_SCROLL], BTN_MON_DOWN,	CRect(0, 257,  0, 0), &UIBTN_IMAGE(IDB_MONITOR_BTNDOWN_ON, IDB_MONITOR_BTNDOWN_ON, IDB_MONITOR_BTNDOWN_ON, IDB_MONITOR_BTNDOWN_ON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_MON_EDIT,	CRect(289, 15,  0, 0), &UIBTN_IMAGE(IDB_BTN_ON, IDB_BTN_ON, IDB_BTN_ON, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_MONI_EDIT),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
	};
	for(int i=BTN_MON_UP; i<=BTN_MON_EDIT; i++)
	{
		m_btn[i].CreateButton(btn[i - (int)BTN_MON_UP]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	m_btn[BTN_MON_UP].EnableConsecutiveHits();
	m_btn[BTN_MON_DOWN].EnableConsecutiveHits();

	m_slider.CreateSliderCtrl(UI_SLIDERCTRL(&m_stc[MONI_STC_SCROLL], SLD_MON_SCROLL,	CRect(0, 11,  0,  0), IDB_MONI_SCROLL_BAR, IDB_MONI_SCROLL_BAR, IDB_MONI_SCROLL_BAR, IDB_MONI_SCROLL_BG, 0, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE));
	m_slider.ModifyCtrlStyle(0, UISCS_VERTICAL);

	// Monitoring panel

	CRect rcMoni;
	m_MonDlg.Create(IDD_MONI_CHILD, this);
	m_MonDlg.SetBkBitmap(IDB_MONI2, CLR_TRPT);
	m_MonDlg.GetClientRect(rcMoni);
	//rcMoni.MoveToXY(40, 50);
	//m_MonDlg.MoveWindow(17, 38, 400, 470);
	m_MonDlg.MoveWindow(7, 38, 407, 425);
	m_MonDlg.ShowWindow(SW_SHOW);
	

	m_stc[MONI_STC_BLKGPUCLK    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKGPUCLK,    CRect(0,   0, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKMEMCLK    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKMEMCLK,    CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKGPUVOL    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKGPUVOL,    CRect(0, 288, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKMEMVOL    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKMEMVOL,    CRect(0, 432, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKFANSPD    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKFANSPD,    CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKFANSPD_RPM].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKFANSPD_RPM,CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKTEMPER    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKTEMPER,    CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKPOWER     ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKPOWER,     CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKGPUSAGE   ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKGPUSAGE,   CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKCPUSAGE   ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKCPUSAGE,   CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKCPUCLK    ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKCPUCLK,    CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKMEMUSAGE  ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKMEMUSAGE,  CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKPAGEUSAGE ].CreateStatic(UI_STATIC(&m_MonDlg, MONI_STC_BLKPAGEUSAGE, CRect(0, 144, 0, 0), _T(""), IDB_MONI_BLK, CLR_TRPT));
	m_stc[MONI_STC_BLKGPUCLK].ShowWindow(SW_HIDE);
	m_stc[MONI_STC_BLKMEMCLK].ShowWindow(SW_HIDE);
	m_stc[MONI_STC_BLKGPUVOL].ShowWindow(SW_HIDE);
	m_stc[MONI_STC_BLKMEMVOL].ShowWindow(SW_HIDE);

	for(int i=MONI_GPH_GPUCLK; i<=MONI_GPH_PAGEUSAGE; i++)
	{
		m_statusGraph[i].Create(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_GPH_GPUCLK], 0, CRect(35,  20, 408, 131));
		m_statusGraph[i].SetSampleInterval(9);
		m_statusGraph[i].CreateGraph(0, 1, CLR_WHITE);
		m_statusGraph[i].Enable(true);
		m_statusGraph[i].SetMargin(0, 0, 35, 0);
		m_statusGraph[i].SetFont(Font(9), CLR_MAIN);
		m_statusGraph[i].ShowValue(CRect(342, 0, 373, 10));
	}

	m_statusGraph[MONI_GPH_GPUCLK].SetRange(0, 2000);		// 0 ~ 2000 MHz
	m_statusGraph[MONI_GPH_MEMCLK].SetRange(0, 15000);		// 0 ~ 8000 MHz
	m_statusGraph[MONI_GPH_GPUVOL].SetRange(0, 2 * 1000);	// 0 ~ 2V  // float to integer. So -> * 100 ...
	m_statusGraph[MONI_GPH_MEMVOL].SetRange(0, 2 * 1000);	// 0 ~ 2V  // float to integer. So -> * 100 ...
	m_statusGraph[MONI_GPH_FANSPD].SetRange(0, 100);		// 0 ~ 100% or 0 ~8000 RPM
	m_statusGraph[MONI_GPH_FANSPD_RPM].SetRange(0, 8000);		// 0 ~ 100% or 0 ~8000 RPM
	m_statusGraph[MONI_GPH_TEMPER].SetRange(0, 100);		// 0 ~ 100 C
	m_statusGraph[MONI_GPH_POWER ].SetRange(0, 100);		// 0 ~ 100 W
	m_statusGraph[MONI_GPH_GPUSAGE  ].SetRange(0, 100);		// 0 ~ 100 W
	m_statusGraph[MONI_GPH_CPUSAGE  ].SetRange(0, 100);		// 0 ~ 100 W
	m_statusGraph[MONI_GPH_CPUCLK   ].SetRange(0, 100);		// 0 ~ 100 W
	m_statusGraph[MONI_GPH_MEMUSAGE ].SetRange(0, 100);		// 0 ~ 100 W
	m_statusGraph[MONI_GPH_PAGEUSAGE].SetRange(0, 100);		// 0 ~ 100 W

	for(int i=MONI_STC_MINGPUCLK; i<=MONI_STC_MINPAGEUSAGE; i++)
	{
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_MINGPUCLK], i, CRect(235, 0, 290, 14), _T("Min: 0"), 0));
		m_stc[i].SetFont(Font(8), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_BOTTOM | ST_LEFT | ST_SINGLELINE);
		//m_stc[i].ShowWindow(SW_HIDE);
	}

	// Max Value
	int nMaxValue[] = {
		2000, 15000, 2000, 2000, 100, 8000, 100, 100, 100, 100, 100, 100
	};
	for(int i=MONI_STC_MAXGPUCLK; i<=MONI_STC_MAXPAGEUSAGE; i++)
	{
		CString sValue;
		sValue.Format(_T("MAX:%d"), nMaxValue[i - MONI_STC_MAXGPUCLK]);
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_MAXGPUCLK], i, CRect( 175, 0, 226, 14), sValue, 0));
		m_stc[i].SetFont(Font(8), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_BOTTOM | ST_LEFT | ST_SINGLELINE);
		//m_stc[i].ShowWindow(SW_HIDE);
	}

	for(int i=MONI_STC_RMINGCLK; i<=MONI_STC_RMINPUSAGE; i++)
	{
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_RMINGCLK], i, CRect(15, 125, 32, 135), _T("0"), 0));
		m_stc[i].SetFont(Font(8), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_BOTTOM | ST_RIGHT | ST_SINGLELINE);
	}

	for(int i=MONI_STC_RMAXGCLK; i<=MONI_STC_RMAXPUSAGE; i++)
	{
		CString sValue;
		sValue.Format(_T("%d"), nMaxValue[i - MONI_STC_RMAXGCLK]);
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_RMAXGCLK], i, CRect( 0, 17, 32, 26), sValue, 0));
		m_stc[i].SetFont(Font(8), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_RIGHT | ST_SINGLELINE);
	}

	// Title
	CString sTitle[] = { 
		CLangX::Get(LANG_MONI_GPUCLK),
		CLangX::Get(LANG_MONI_MEMCLK),
		CLangX::Get(LANG_MONI_GPUVOL),
		CLangX::Get(LANG_MONI_MEMVOL),
		CLangX::Get(LANG_MONI_FANSPD),
		CLangX::Get(LANG_MONI_FANSPD),
		CLangX::Get(LANG_MONI_GPUTEMP),
		CLangX::Get(LANG_MONI_PWRCONS),
		CLangX::Get(LANG_MONI_GPUUSG),
		CLangX::Get(LANG_MONI_CPUUSG),
		CLangX::Get(LANG_MONI_CPUCLK),
		CLangX::Get(LANG_MONI_MEMUSG),
		CLangX::Get(LANG_MONI_PGFILEUSG),
	};

	for(int i=MONI_STC_TITGPUCLK; i<=MONI_STC_TITPAGEUSAGE; i++)
	{
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_TITGPUCLK], i, CRect( 35, 0, 135, 15), sTitle[i - MONI_STC_TITGPUCLK], 0));
		m_stc[i].SetFont(Font(11), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
		//m_stc[i].ShowWindow(SW_HIDE);
	}

	// Unit
	CString sUnit[] = { _T("[MHz]"), _T("[MHz]"), _T("[mV]"), _T("[mV]"), _T("[%]"), _T("[RPM]"), _T("[°C]"), _T("[%]"), _T("[%]"), _T("[%]"), _T("[GHz]"), _T("[%]"), _T("[%]"), };

	for(int i=MONI_STC_UNITGPUCLK; i<=MONI_STC_UNITPAGEUSAGE; i++)
	{
		m_stc[i].CreateStatic(UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK + i - MONI_STC_TITGPUCLK], i, CRect( 70, 0, 100, 14), sUnit[i - MONI_STC_UNITGPUCLK], 0));
		m_stc[i].SetFont(Font(9), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
		//m_stc[i].ShowWindow(SW_HIDE);
	}
	UI_STATIC stc[] = 
	{
		UI_STATIC(&m_stc[MONI_STC_BLKGPUCLK   ],		MONI_STC_GPUCLK,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKMEMCLK   ],		MONI_STC_MEMCLK,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKGPUVOL   ],		MONI_STC_GPUVOL,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKMEMVOL   ],		MONI_STC_MEMVOL,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKFANSPD   ],		MONI_STC_FANSPD,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKFANSPD_RPM ],		MONI_STC_FANSPD_RPM,	CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKTEMPER   ],		MONI_STC_TEMPER,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKPOWER    ],		MONI_STC_POWER,			CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKGPUSAGE  ], 	    MONI_STC_GPUSAGE,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKCPUSAGE  ], 	    MONI_STC_CPUSAGE,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKCPUCLK   ],		MONI_STC_CPUCLK,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKMEMUSAGE ],	    MONI_STC_MEMUSAGE,		CRect(135,  0, 165, 14), _T(""), 0),
		UI_STATIC(&m_stc[MONI_STC_BLKPAGEUSAGE],	    MONI_STC_PAGEUSAGE,		CRect(135,  0, 165, 14), _T(""), 0),
	};

	for(int i=MONI_STC_GPUCLK; i<=MONI_STC_PAGEUSAGE; i++)
	{
		m_stc[i].CreateStatic(stc[i - (int)MONI_STC_GPUCLK]);
		m_stc[i].SetFont(Font(9), CLR_WHITE);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
	}

	//m_statusGraph[MONI_GPH_MEMVOL].Enable(false);

	CRect rcEdit;
	m_EditDlg.SetParent(this);
	m_EditDlg.Create(IDD_MONI_EDIT_DIALOG, GetDesktopWindow());
	m_EditDlg.GetClientRect(&rcEdit);
	rcEdit.MoveToXY(CPoint(800, 400));
	m_EditDlg.MoveWindow(rcEdit);
	m_EditDlg.ShowWindow(SW_HIDE);
}

void CMonitorDlg::SetParent(CUiDlg* pParent)
{
	if(NULL != pParent)
	{
		m_pParent = pParent;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
//
// UI message.
//
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CMonitorDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{

	case BTN_MON_UP:		
	case BTN_MON_DOWN:		m_slider.SetPos(m_slider.GetPos() + (wParam == BTN_MON_UP ? -10 : 10));	
							PostMessage(WM_UI_SLIDER_MOVING, SLD_MON_SCROLL, m_slider.GetPos());
							break;
	case BTN_MON_EDIT:    
		{
			CRect rcRect,rcMainClient,rcdesk;
			//::GetWindowRect(m_hWnd,rcMainClient);
			
			GetDesktopWindow()->GetClientRect(rcdesk);
			m_EditDlg.InitState();
			m_EditDlg.GetClientRect(&rcRect);
			rcRect.MoveToXY(CPoint(rcdesk.right/2-150, rcdesk.bottom/2-158));
			m_EditDlg.MoveWindow(rcRect);
			m_EditDlg.ShowWindow(SW_SHOW);
			m_EditDlg.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			((CAORUSDlg*)AfxGetMainWnd())->Enable(FALSE);
		}
		
		break;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------
LRESULT CMonitorDlg::OnUiSliderMoving(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case SLD_MON_SCROLL:{
			int nMax = 0, nMin = 0;    
			m_slider.GetRange(nMin, nMax);  
			const int nMaxPos = nMax; 

			int nNewPos = lParam;

			if (nNewPos < 0)
				nNewPos = 0;
			else if (nNewPos > nMaxPos)
				nNewPos = nMaxPos;

			int nDelta = nNewPos - m_nScrollPos;
			m_nScrollPos = nNewPos;

			m_MonDlg.ScrollWindow(0,-nDelta);
			break;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
// UI ctrl.
//
/////////////////////////////////////////////////////////////////////////////////////////
void CMonitorDlg::OnDepart()
{
}

void CMonitorDlg::OnFit(CRect rcParentCli)
{
	CAORUSDlg* pParent = (CAORUSDlg*)m_pParent;
	if(NULL != pParent)
	{
		int nX = rcParentCli.left - 426;
		int nY = rcParentCli.top + 79;
		SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
	}
	SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
}

//---------------------------------------------------------------------------------------
BOOL CMonitorDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nMax = 0, nMin = 0;    
	m_slider.GetRange(nMin, nMax);  
	const int nMaxPos = nMax; 

	if(3 >= m_nMonitorCount) return CUiDlg::OnMouseWheel(nFlags, zDelta, pt);

	if (zDelta<0)
	{
		if (m_nScrollPos < nMaxPos)
		{
			zDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);

			m_nScrollPos += zDelta;
			//SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
			m_slider.SetPos(m_nScrollPos);
			m_MonDlg.ScrollWindow(0,-zDelta);
			MoveMoniotr();
		}
	}
	else if(zDelta != 0)
	{
		if (m_nScrollPos > 0)
		{
			zDelta = -min(max(nMaxPos/20,5),m_nScrollPos);

			m_nScrollPos += zDelta;
			//SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
			m_slider.SetPos(m_nScrollPos);
			m_MonDlg.ScrollWindow(0,-zDelta);
			MoveMoniotr();
		}
	}

	return CUiDlg::OnMouseWheel(nFlags, zDelta, pt);
}
/////////////////////////////////////////////////////////////////////////////////////////
//
// main function.
//
/////////////////////////////////////////////////////////////////////////////////////////
void CMonitorDlg::InitPanel(int nIndex, int nPerfLogs[6][64])
{
	m_nIndex = nIndex;
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<64; j++)
		{
			m_nPerfLogs[i][j] = nPerfLogs[i][j];
		}
	}
}

void CMonitorDlg::InitState()
{
	SetTimer(TIMER_PERF_MONITOR, 3000, NULL);

	if (NULL != m_pParent)
	{
		CRect rcCli;
		m_pParent->GetClientRect(rcCli);
		m_pParent->ClientToScreen(&rcCli);
		OnFit(rcCli);
	}

	// Initialize monitoring curves.
	Monitoring();
	ShowWindow(SW_SHOW);
	SetTimer(2, 10, NULL);

	m_EditDlg.InitState();
}

void CMonitorDlg::Monitoring()
{
	CAORUSDlg* pMain = ((CAORUSDlg*)m_pParent);
    pMain->SyncMobile(1,0);
	static int nTimeInterval = 3000;

	CString sValue = _T("");
	VGA_PERFORMANCE perf;
	DWORD dwPerfs = 0;
	static DWORD dwLastPerfs = 0;
	VGA_PARAM_MONISETTING moniSetting;
	VGA_MB_INFO MBInfo;

	Aorus()->GetCfg()->GetMoniSetting(moniSetting);

	if(moniSetting.bGpuClk)		{ dwPerfs |= VGA_PERF_GPUCLK; }
	if(moniSetting.bMemClk)		{ dwPerfs |= VGA_PERF_MEMCLK; }
	if(moniSetting.bGpuVol)		{ dwPerfs |= VGA_PERF_GPUVOL; }
	//if(moniSetting.bMemVol)		{ dwPerfs |= GURU_PERF_MEMVOL; }
	if(moniSetting.bFanSpd)		{ dwPerfs |= VGA_PERF_FANSPD; }
    if(moniSetting.bFanRpm)		{ dwPerfs |= VGA_PERF_FANRPM; }
	if(moniSetting.bPower)		{ dwPerfs |= VGA_PERF_POWER;  }
	if(moniSetting.bGPUsage)	{ dwPerfs |= VGA_PERF_GPUSAGE;}
	if(moniSetting.bCPUsage)	{ dwPerfs |= VGA_PERF_CPUSAGE;}
	if(moniSetting.bCPUClock)	{ dwPerfs |= VGA_PERF_CPUCLK; }
	if(moniSetting.bMemUsage)	{ dwPerfs |= VGA_PERF_MEMUSAGE;}
	//if(moniSetting.bPageUsage)	{ dwPerfs |= VGA_PERF_PAGEFILE;}
	dwPerfs |= VGA_PERF_TEMPER; // 用于风扇调节

	static bool bfirstEnter=true;
	if (bfirstEnter)
	{
		bfirstEnter=false;
		nMinValue[MONI_GPH_GPUCLK]=perf.nGpuClk;
		nMinValue[MONI_GPH_MEMCLK]=perf.nGpuClk;
		nMinValue[MONI_GPH_GPUVOL]=perf.nGpuClk;
		nMinValue[MONI_GPH_MEMVOL]=perf.nGpuClk;
		nMinValue[MONI_GPH_FANSPD]=perf.nGpuClk;
		nMinValue[MONI_GPH_TEMPER]=perf.nGpuClk;
		nMinValue[MONI_GPH_POWER]=perf.nGpuClk;
		nMinValue[MONI_GPH_GPUSAGE]=perf.nGpuClk;
		nMinValue[MONI_GPH_CPUSAGE]=perf.nGpuClk;
		nMinValue[MONI_GPH_CPUCLK]=perf.nGpuClk;
		nMinValue[MONI_GPH_MEMUSAGE]=perf.nGpuClk;
		nMinValue[MONI_GPH_PAGEUSAGE]=perf.nGpuClk;
	}


	dwLastPerfs = dwPerfs;

	if(moniSetting.nTimeInterval != nTimeInterval)
	{
		nTimeInterval = moniSetting.nTimeInterval;
		KillTimer(TIMER_PERF_MONITOR);
		SetTimer(TIMER_PERF_MONITOR, nTimeInterval, NULL);
	}

	Aorus()->GetVGA()->Ctrl()->GetCurrentPerformances(dwPerfs,Aorus()->GetVGASel(),perf);
	Aorus()->GetVGA()->Ctrl()->GetCurrentMBInfo(dwPerfs, MBInfo);

	int nGpuCount=Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	FAN_SETTING *pfansettting;
	int *ptemp;
	pfansettting=new FAN_SETTING[nGpuCount];
	ptemp=new int[nGpuCount];
	for (int i=0;i<nGpuCount;i++)
	{
		VGA_PERFORMANCE temPerf;
		Aorus()->GetVGA()->Ctrl()->GetCurrentPerformances(VGA_PERF_TEMPER,i,temPerf);
		*(ptemp+i)=temPerf.nTemperature;
		FAN_SETTING fansettting;
		Aorus()->GetCfg()->GetCurFanSetting(*(pfansettting+i),i);
		//(pfansettting+i)->bFanStop =Aorus()->GetFanStopState();
	}
	Aorus()->GetVGA()->Ctrl()->FanSpeedMintoring(pfansettting,ptemp);
    delete [nGpuCount]pfansettting;
	delete [nGpuCount]ptemp;


	/*if(!IsWindowVisible() && !moniSetting.bLogRecord)  // 无显示或没有在Log.
	{
		return;
	}*/

	if(moniSetting.bGpuClk)
	{
		sValue.Format(_T("%d"), perf.nGpuClk);
		m_statusGraph[MONI_GPH_GPUCLK].SetValue(0, perf.nGpuClk);
		int nmax,nmin;
		m_stc[MONI_STC_GPUCLK].SetCaption(sValue);
		m_statusGraph[MONI_GPH_GPUCLK].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXGPUCLK].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINGPUCLK].SetCaption(sValue);
	}

	if(moniSetting.bMemClk)
	{
		sValue.Format(_T("%d"), perf.nMemClk);
		m_statusGraph[MONI_GPH_MEMCLK].SetValue(0, perf.nMemClk);
		m_stc[MONI_STC_MEMCLK].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_MEMCLK].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXMEMCLK].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINMEMCLK].SetCaption(sValue);
	}

	if(moniSetting.bGpuVol)
	{
		sValue.Format(_T("%.0f"), perf.nGpuVol / 1000.0);	// uV -> mV
		m_statusGraph[MONI_GPH_GPUVOL].SetValue(0, (int)( perf.nGpuVol / 1000.0));	// float to integer. So -> x 100 ...
		m_stc[MONI_STC_GPUVOL].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_GPUVOL].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXGPUVOL].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINGPUVOL].SetCaption(sValue);
	}

	if(moniSetting.bMemVol)
	{
		sValue.Format(_T("%0.3f"), perf.nMemVol / 1000.0);	// uV -> V
		m_statusGraph[MONI_GPH_MEMVOL].SetValue(0, (int)( perf.nMemVol / 1000.0));	// float to integer. So -> x 100 ...
		m_stc[MONI_STC_MEMVOL].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_MEMVOL].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXMEMVOL].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINMEMVOL].SetCaption(sValue);
	}

	if(moniSetting.bFanSpd)
	{
		sValue.Format(_T("%d"), perf.nFanSpd);
		m_statusGraph[MONI_GPH_FANSPD].SetValue(0, perf.nFanSpd);
		m_stc[MONI_STC_FANSPD].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_FANSPD].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXFANSPD].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINFANSPD].SetCaption(sValue);
	}
	if (moniSetting.bFanRpm)
	{
		sValue.Format(_T("%d"), perf.nFanRPM);
		m_statusGraph[MONI_GPH_FANSPD_RPM].SetValue(0, perf.nFanRPM);
		m_stc[MONI_STC_FANSPD_RPM].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_FANSPD_RPM].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXFANSPD_RPM].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINFANSPD_RPM].SetCaption(sValue);
	}
	if(moniSetting.bTemperature)
	{
		sValue.Format(_T("%d"), perf.nTemperature);
		m_statusGraph[MONI_GPH_TEMPER].SetValue(0, perf.nTemperature);
		m_stc[MONI_STC_TEMPER].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_TEMPER].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXTEMPER].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINTEMPER].SetCaption(sValue);
	}

	if(moniSetting.bPower)
	{
		sValue.Format(_T("%d"), perf.nPower);
		m_statusGraph[MONI_GPH_POWER].SetValue(0, perf.nPower);	// float to integer. So -> x 100 ...
		m_stc[MONI_STC_POWER].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_POWER].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXPOWER].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINPOWER].SetCaption(sValue);
	}

	if(moniSetting.bGPUsage)
	{
		sValue.Format(_T("%d"), perf.nGPUsage);
		m_statusGraph[MONI_GPH_GPUSAGE].SetValue(0, perf.nGPUsage);	
		m_stc[MONI_STC_GPUSAGE].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_GPUSAGE].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXGPUSAGE].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINGPUSAGE].SetCaption(sValue);
	}

	if(moniSetting.bCPUsage)
	{
		sValue.Format(_T("%d"), MBInfo.nCPUsage);
		m_statusGraph[MONI_GPH_CPUSAGE].SetValue(0, MBInfo.nCPUsage);	
		m_stc[MONI_STC_CPUSAGE].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_CPUSAGE].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXCPUSAGE].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINCPUSAGE].SetCaption(sValue);
	}

	if(moniSetting.bCPUClock)
	{
		sValue.Format(_T("%.2f"), MBInfo.fCPUClk / 1000.0);
		m_statusGraph[MONI_GPH_CPUCLK].SetValue(0, (int)(MBInfo.fCPUClk / 50.0));	
		m_stc[MONI_STC_CPUCLK].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_CPUCLK].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXCPUCLK].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINCPUCLK].SetCaption(sValue);
	}

	if(moniSetting.bMemUsage)
	{
		sValue.Format(_T("%d"), MBInfo.nMemUsage);
		m_statusGraph[MONI_GPH_MEMUSAGE].SetValue(0, MBInfo.nMemUsage);
		m_stc[MONI_STC_MEMUSAGE].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_MEMUSAGE].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXMEMUSAGE].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_MINMEMUSAGE].SetCaption(sValue);
	}
	if(moniSetting.bPageUsage)
	{
		sValue.Format(_T("%.2f"), MBInfo.fPageUsage);
		m_statusGraph[MONI_GPH_PAGEUSAGE].SetValue(0, (int)(MBInfo.fPageUsage));
		m_stc[MONI_STC_PAGEUSAGE].SetCaption(sValue);
		int nmax,nmin;
		m_statusGraph[MONI_GPH_PAGEUSAGE].GetMaxMinValue(nmin,nmax);
		sValue.Format(_T("MAX:%d"),nmax);
		m_stc[MONI_STC_MAXPAGEUSAGE].SetCaption(sValue);
		sValue.Format(_T("MIN:%d"),nmin);
		m_stc[MONI_STC_PAGEUSAGE].SetCaption(sValue);
	}

	if (moniSetting.bLogRecord)
	{
		Aorus()->GetVGA()->Ctrl()->LogOutToTxt(perf, MBInfo, dwPerfs, moniSetting.sLogFile);
	}
}


void CMonitorDlg::ResetScroll(int cy)
{
	CRect rc;
	m_MonDlg.GetClientRect(&rc);    

	m_szDialog.cx = rc.right  - rc.left;
	m_szDialog.cy = rc.bottom - rc.top ; 

	if (cy < m_szDialog.cy)
	{
		m_slider.ShowWindow(SW_HIDE);
		return;
	}
	m_slider.SetRange(0, cy - m_szDialog.cy);
	m_slider.SetPos(0);
	m_slider.ShowWindow(SW_SHOW);
	m_nScrollPos = 0;
	return;
}

int CMonitorDlg::MoveMoniotr(BOOL bMove)
{
	VGA_PARAM_MONISETTING moniSetting;

	CPoint pt = m_bMove ? CPoint(40, 50) : CPoint(40, 50);
	Aorus()->GetCfg()->GetMoniSetting(moniSetting);

	pt = CPoint(0, 0);
	CPoint ptXY[] = {
		CPoint(0,   0), 
		CPoint(0, 144),
		CPoint(0, 288),
		CPoint(0, 432),
		CPoint(0, 576),
		CPoint(0, 720),
		CPoint(0, 864),
		CPoint(0, 1008),
		CPoint(0, 1152),
		CPoint(0, 1296),
		CPoint(0, 1440),
		CPoint(0, 1584),
		CPoint(0, 1728),
		CPoint(0, 1872),
		CPoint(0, 2016),
	};
	int i = 0;
	if(bMove){
		if(moniSetting.bGpuClk && m_statusGraph[MONI_GPH_GPUCLK].IsEnable())		
			m_stc[MONI_STC_BLKGPUCLK].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKGPUCLK].ShowWindow(SW_HIDE);

		if(moniSetting.bMemClk && m_statusGraph[MONI_GPH_MEMCLK].IsEnable())		
			m_stc[MONI_STC_BLKMEMCLK].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKMEMCLK].ShowWindow(SW_HIDE);

		if(moniSetting.bGpuVol && m_statusGraph[MONI_GPH_GPUVOL].IsEnable())	
			m_stc[MONI_STC_BLKGPUVOL].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKGPUVOL].ShowWindow(SW_HIDE);

		if(moniSetting.bMemVol && m_statusGraph[MONI_GPH_MEMVOL].IsEnable())	
			m_stc[MONI_STC_BLKMEMVOL].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKMEMVOL].ShowWindow(SW_HIDE);

		if(moniSetting.bFanSpd && m_statusGraph[MONI_GPH_FANSPD].IsEnable())	
			m_stc[MONI_STC_BLKFANSPD].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKFANSPD].ShowWindow(SW_HIDE);

		if(moniSetting.bFanRpm && m_statusGraph[MONI_GPH_FANSPD_RPM].IsEnable())	
			m_stc[MONI_STC_BLKFANSPD_RPM].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKFANSPD_RPM].ShowWindow(SW_HIDE);

		if(moniSetting.bTemperature && m_statusGraph[MONI_GPH_TEMPER].IsEnable())
			m_stc[MONI_STC_BLKTEMPER].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKTEMPER].ShowWindow(SW_HIDE);

		if(moniSetting.bPower && m_statusGraph[MONI_GPH_POWER].IsEnable())	
			m_stc[MONI_STC_BLKPOWER].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKPOWER].ShowWindow(SW_HIDE);

		if(moniSetting.bGPUsage && m_statusGraph[MONI_GPH_GPUSAGE].IsEnable())	
			m_stc[MONI_STC_BLKGPUSAGE].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKGPUSAGE].ShowWindow(SW_HIDE);

		if(moniSetting.bCPUsage && m_statusGraph[MONI_GPH_CPUSAGE].IsEnable())	
			m_stc[MONI_STC_BLKCPUSAGE].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKCPUSAGE].ShowWindow(SW_HIDE);

		if(moniSetting.bCPUClock && m_statusGraph[MONI_GPH_CPUCLK].IsEnable())	
			m_stc[MONI_STC_BLKCPUCLK].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKCPUCLK].ShowWindow(SW_HIDE);

		if(moniSetting.bMemUsage && m_statusGraph[MONI_GPH_MEMUSAGE].IsEnable())	
			m_stc[MONI_STC_BLKMEMUSAGE].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKMEMUSAGE].ShowWindow(SW_HIDE);

		/*if(moniSetting.bPageUsage && m_statusGraph[MONI_GPH_PAGEUSAGE].IsEnable())	
			m_stc[MONI_STC_BLKPAGEUSAGE].SetWindowPos(NULL, ptXY[i].x + pt.x, ptXY[i++].y + pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else m_stc[MONI_STC_BLKPAGEUSAGE].ShowWindow(SW_HIDE);*/
		m_stc[MONI_STC_BLKPAGEUSAGE].ShowWindow(SW_HIDE);

		m_nMonitorCount = i;

		if(moniSetting.bGpuClk		&& m_statusGraph[MONI_GPH_GPUCLK].IsEnable())			m_stc[MONI_STC_BLKGPUCLK].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bMemClk		&& m_statusGraph[MONI_GPH_MEMCLK].IsEnable())			m_stc[MONI_STC_BLKMEMCLK].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bGpuVol		&& m_statusGraph[MONI_GPH_GPUVOL].IsEnable())			m_stc[MONI_STC_BLKGPUVOL].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bMemVol		&& m_statusGraph[MONI_GPH_MEMVOL].IsEnable())			m_stc[MONI_STC_BLKMEMVOL].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bFanSpd		&& m_statusGraph[MONI_GPH_FANSPD].IsEnable())			m_stc[MONI_STC_BLKFANSPD].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bTemperature && m_statusGraph[MONI_GPH_TEMPER].IsEnable())			m_stc[MONI_STC_BLKTEMPER].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bPower		&& m_statusGraph[MONI_GPH_POWER ].IsEnable())			m_stc[MONI_STC_BLKPOWER ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bGPUsage		&& m_statusGraph[MONI_GPH_GPUSAGE].IsEnable())			m_stc[MONI_STC_BLKGPUSAGE ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bCPUsage		&& m_statusGraph[MONI_GPH_CPUSAGE].IsEnable())			m_stc[MONI_STC_BLKCPUSAGE ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bCPUClock	&& m_statusGraph[MONI_GPH_CPUCLK ].IsEnable())			m_stc[MONI_STC_BLKCPUCLK ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bMemUsage	&& m_statusGraph[MONI_GPH_MEMUSAGE ].IsEnable())		m_stc[MONI_STC_BLKMEMUSAGE ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);
		if(moniSetting.bPageUsage	&& m_statusGraph[MONI_GPH_PAGEUSAGE].IsEnable())		m_stc[MONI_STC_BLKPAGEUSAGE ].SetStaticBitmap(IDB_MONI_BLK, CLR_TRPT);

		for(int i=MONI_STC_TITGPUCLK; i<=MONI_STC_TITPAGEUSAGE; i++)
		{
			m_stc[i].ShowWindow(SW_SHOW);
		}
		for(int i=MONI_STC_MINGPUCLK; i<=MONI_STC_MINPAGEUSAGE; i++)
		{
			m_stc[i].ShowWindow(SW_SHOW);
		}
		for(int i=MONI_STC_MAXGPUCLK; i<=MONI_STC_MAXPAGEUSAGE; i++)
		{
			m_stc[i].ShowWindow(SW_SHOW);
		}
		for(int i=MONI_STC_UNITGPUCLK; i<=MONI_STC_UNITPAGEUSAGE; i++)
		{
			m_stc[i].ShowWindow(SW_SHOW);
		}
	}

	if(bMove) 
	{
		m_MonDlg.Invalidate(TRUE);
		m_MonDlg.UpdateWindow();
	}

	OnPaint();

	m_slider.ShowWindow(m_nMonitorCount <= 3 ? SW_HIDE : SW_SHOW);

	return m_nMonitorCount <= 3 ? 0 : ptXY[i].y;
}

void CMonitorDlg::ResetPowerBtn()
{
	//m_btn[BTN_MON_POWER].Enable(false);
}


void CMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CUiDlg::OnSize(nType, cx, cy);

}
