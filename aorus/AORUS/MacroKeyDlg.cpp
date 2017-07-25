// MacroKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AORUS.h"
#include "MacroKeyDlg.h"
#include "AORUSDlg.h"
#include "./inc/mouse/AM300Ctrl.h"

#define LANG_INSERT_ACTION				0
#define LANG_INSERT_DELAY_TIME		1
#define LANG_DELETE_ONE					2
#define LANG_DELETE_ALL					3
#define LANG_RECORD						    4
#define LANG_DELAY_TIME					5
#define LANG_AUTO_DETECT				6
#define LANG_FIXED_TIME					7
#define LANG_MS									8
#define LANG_NO_DELAY						9
#define LANG_EXECUTE_MORE				10
#define LANG_ONE_TIME						11
#define LANG_LOOP_MORE					12
#define LANG_FIRE_MODE					13
#define LANG_HOTKEY							14
#define LANG_HOTKEY_START				15
#define LANG_HOTKEY_STOP				16
#define LANG_SET								17
#define LKEY_QTY									18
int CMacroKeyDlg::s_nWords = LKEY_QTY;
LANG_WORD CMacroKeyDlg::s_Words[48] = 
{
	LANG_WORD(LANG_INSERT_ACTION,		_T("插入动作"), _T("插入動作"), _T("INSERT ACTION")),
	LANG_WORD(LANG_INSERT_DELAY_TIME,		_T("插入延迟时间"), _T("插入延遲時間"), _T("INSERT DELAY TIME")),
	LANG_WORD(LANG_DELETE_ONE,		_T("删除单行"), _T("刪除單行"), _T("DELETE ONE")),
	LANG_WORD(LANG_DELETE_ALL,			_T("删除全部"), _T("刪除全部"), _T("DELETE ALL")),
	LANG_WORD(LANG_RECORD,		_T("录制"), _T("錄製"), _T("RECORD")),
	LANG_WORD(LANG_DELAY_TIME,		_T("延迟时间"), _T("延遲時間"), _T("Delay TIME")),
	LANG_WORD(LANG_AUTO_DETECT,		_T("自动侦测"), _T("自動偵測"), _T("Auto Detect")),
	LANG_WORD(LANG_FIXED_TIME,			_T("固定延迟"), _T("固定延遲"), _T("Fixed")),
	LANG_WORD(LANG_MS,		_T("毫秒"), _T("毫秒"), _T("ms")),
	LANG_WORD(LANG_NO_DELAY,		_T("无延迟"), _T("無延遲"), _T("No Delay")),
	LANG_WORD(LANG_EXECUTE_MORE,		_T("执行模式"), _T("執行模式"), _T("Excute Mode")),
	LANG_WORD(LANG_ONE_TIME,			_T("仅执行一次"), _T("僅執行一次"), _T("One Time")),
	LANG_WORD(LANG_LOOP_MORE,		_T("循环执行"), _T("循環執行"), _T("Fire Mode")),
	LANG_WORD(LANG_FIRE_MODE,		_T("连发模式"), _T("連發模式"), _T("Press to Start/Stop")),
	LANG_WORD(LANG_HOTKEY,		_T("热键"), _T("熱鍵"), _T("HotKey")),
	LANG_WORD(LANG_HOTKEY_START,			_T("开始："), _T("開始："), _T("Start :")),
	LANG_WORD(LANG_HOTKEY_STOP,			_T("停止："), _T("停止："), _T("Stop :")),
	LANG_WORD(LANG_SET,		_T("设置"), _T("設置"), _T("SET")),
};

IMPLEMENT_DYNAMIC(CMacroKeyDlg, CUiDlg)

CMacroKeyDlg::CMacroKeyDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CMacroKeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	ZeroMemory(&m_curmarco, sizeof(GVORDER_MACROS));
	ZeroMemory(&m_marcos, sizeof(GVORDER_MACROS) * KB_MARCO_COUNT);
	m_dwLastTime = 0;
	m_bRecord = false;
	m_dwLastItem = -1;
}

CMacroKeyDlg::~CMacroKeyDlg()
{
}

void CMacroKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMacroKeyDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_PANEL_SELCHANGE, OnUiPanelSelChanged)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
	ON_WM_INPUT()
END_MESSAGE_MAP()


// CMacroKeyDlg message handlers

BOOL CMacroKeyDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	CUiDlg::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: Add extra initialization here

	Ui();

	SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////////////////
//
// system message.
//
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CMacroKeyDlg::OnNcHitTest(CPoint point)
{
	UINT uRes = (UINT)CUiDlg::OnNcHitTest(point);
	if(uRes == HTCLIENT) 
	{
		uRes = HTCAPTION;
	}
	return uRes;
}

void CMacroKeyDlg::OnPaint()
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

HCURSOR CMacroKeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMacroKeyDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	pParent->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	CUiDlg::OnActivate(nState, pWndOther, bMinimized);
}

void CMacroKeyDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CUiDlg::OnMoving(fwSide, pRect);

	CRect rcCli;
	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	pParent->GetClientRect(rcCli);
	int nWidth = rcCli.Width();
	GetClientRect(rcCli);
	ClientToScreen(&rcCli);

	pParent->OnFollowMove(2, pParent->OnFit(rcCli, 0 - nWidth, -79));
}

void CMacroKeyDlg::OnMinimize()
{
	ShowWindow(SW_HIDE);
	//::PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void CMacroKeyDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CMacroKeyDlg::Ui(void)
{
	UiMain();
}

void CMacroKeyDlg::UiMain(void)
{
	SetBkBitmap(IDB_MONITORING_BG, 0xff, CLR_TRPT);

	UI_BTN btn[] = 
	{
		UI_BTN(this, BTN_KBMACRO_PROADD,  CRect(199,  60, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILEOFF)),
		UI_BTN(this, BTN_KBMACRO_PROEDIT, CRect(220,  60, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITOFF, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILEOFF, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(this, BTN_KBMACRO_PRODEL,  CRect(241,  60, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_DELETEFILE, IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILEOFF)),
		UI_BTN(this, BTN_KBMACRO_IMPORT,	CRect(300, 50, 0, 0),  &UIBTN_IMAGE(IDB_MACRO_IMPORT, IDB_MACRO_IMPORT, IDB_MACRO_IMPORT, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(_T(""), CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(9))),
		UI_BTN(this, BTN_KBMACRO_EXPORT,	CRect(350, 50, 0, 0), &UIBTN_IMAGE(IDB_MACRO_EXPORT, IDB_MACRO_EXPORT, IDB_MACRO_EXPORT, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(_T(""), CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(9))),
		
		UI_BTN(this, BTN_KBMACRO_APPLY,	CRect(265, 398-5, 0, 0), &UIBTN_IMAGE(IDB_MACRO_BTN, IDB_MACRO_BTN, IDB_MACRO_BTN, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_SET), CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),

		UI_BTN(this, BTN_KBMACRO_INSFUN,	CRect(265, 278-5, 0, 0), &UIBTN_IMAGE(IDB_MACRO_BTN, IDB_MACRO_BTN, IDB_MACRO_BTN, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_INSERT_ACTION),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_KBMACRO_INSTIME, CRect(265, 308-5, 0, 0), &UIBTN_IMAGE(IDB_MACRO_BTN, IDB_MACRO_BTN, IDB_MACRO_BTN, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_INSERT_DELAY_TIME),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_KBMACRO_DELONE,	CRect(265, 338-5, 0, 0), &UIBTN_IMAGE(IDB_MACRO_BTN, IDB_MACRO_BTN, IDB_MACRO_BTN, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_DELETE_ONE),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_KBMACRO_DELALL,	CRect(265, 368-5, 0, 0), &UIBTN_IMAGE(IDB_MACRO_BTN, IDB_MACRO_BTN, IDB_MACRO_BTN, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_DELETE_ALL),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		
		UI_BTN(this, BTN_KBMACRO_KB, CRect(220, 205, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(this, BTN_KBMACRO_MOUSE, CRect(220, 224, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(this, BTN_KBMACRO_LOCATION, CRect(220, 245, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, IDB_RADIO_CHECK, CLR_TRPT), NULL, BTN_CHECK),
		
		UI_BTN(this, BTN_KBMACRO_ONCLOSE, CRect(379, 9, 0,  0), &UIBTN_IMAGE(IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, 0, 0, 0, 0, CLR_TRPT)),
//		UI_BTN(this, BTN_KBMACRO_MINIMIZE, CRect(347, 21, 0, 0), &UIBTN_IMAGE(IDB_HOME_MINON, IDB_HOME_MINON, IDB_HOME_MINON, IDB_HOME_MINON, 0, 0, 0, 0, CLR_TRPT)),
		UI_BTN(this, BTN_KBMACRO_RECORD,	CRect(23, 183, 0, 0), &UIBTN_IMAGE(IDB_MACRO_RECORD_ENABLE, IDB_MACRO_RECORD_ENABLE, IDB_MACRO_RECORD_ENABLE, IDB_MACRO_RECORD_ENABLE, IDB_MACRO_RECORD, IDB_MACRO_RECORD, IDB_MACRO_RECORD, IDB_MACRO_RECORD, CLR_TRPT),&UIBTN_STRING(CLangX::Get(s_Words, s_nWords, LANG_RECORD),	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_WHITE,CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_WHITE,Font(11)),BTN_CHECK),
	};

	for (int i = BTN_KBMACRO_PROADD; i < BTN_KBMACRO_NUM; i++)
	{
		m_btn[i].CreateButton(btn[i]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	m_btn[BTN_KBMACRO_KB].SetCheck(true);


	m_combobox[COMBOX_KBMACRO_PROFILE].Create(CRect(22, 60, 0, 0), this, COMBOX_KBMACRO_PROFILE);//23,25,0,0
	m_combobox[COMBOX_KBMACRO_PROFILE].SetComboBoxBitmap(IDB_MACRO_COMBOX, IDB_MACRO_COMBOX, IDB_MACRO_COMBOX, IDB_MACRO_COMBOX, CLR_NONE);//
	m_combobox[COMBOX_KBMACRO_PROFILE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KBMACRO_PROFILE].SetCursor(IDC_CUR_HAND);
	m_combobox[COMBOX_KBMACRO_PROFILE].SetArrowWidth(20);//20
	m_combobox[COMBOX_KBMACRO_PROFILE].GetDropList()->SetFont(Font(11),CLR_WHITE);
	m_combobox[COMBOX_KBMACRO_PROFILE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KBMACRO_PROFILE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KBMACRO_PROFILE].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);

	UI_STATIC sta[] =
	{
		UI_STATIC(this, STC_KBMACRO_DELAY_TIME, CRect(27, 90, 127, 105), CLangX::Get(s_Words, s_nWords, LANG_DELAY_TIME), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_AUTO_DETECT,	 CRect(46, 110, 146, 120), CLangX::Get(s_Words, s_nWords, LANG_AUTO_DETECT), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_FIXED_TIME,	 CRect(46, 128, 101, 138), CLangX::Get(s_Words, s_nWords, LANG_FIXED_TIME), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMARCO_MS, CRect(115, 128, 140, 138), CLangX::Get(s_Words, s_nWords, LANG_MS), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMARCO_NO_DELAY, CRect(46, 146, 146, 156), CLangX::Get(s_Words, s_nWords, LANG_NO_DELAY), NULL, CLR_TRPT),

		UI_STATIC(this, STC_KBMARCO_EXEC_MODE, CRect(217, 90, 317, 105), CLangX::Get(s_Words, s_nWords, LANG_EXECUTE_MORE), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMARCO_ONE_TIME, CRect(236, 110, 317, 120), CLangX::Get(s_Words, s_nWords, LANG_ONE_TIME), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMARCO_LOOP_MODE, CRect(236, 128, 317, 138), CLangX::Get(s_Words, s_nWords, LANG_LOOP_MORE), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMARCO_FIRE_MODE, CRect(236, 146, 363, 156),CLangX::Get(s_Words, s_nWords, LANG_FIRE_MODE), NULL, CLR_TRPT),

		UI_STATIC(this, STC_KBMACRO_KB,					CRect(236, 202, 346, 222), _T("KEYBOARD"), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_MOUSE,					CRect(236, 223, 346, 241), _T("MOUSE"), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_LOCATION,				CRect(236 , 243, 346, 262), _T("LOCATION"), NULL, CLR_TRPT),

		UI_STATIC(this, STC_KBMACRO_HOTKEY, CRect(23, 245, 83, 260), CLangX::Get(s_Words, s_nWords, LANG_HOTKEY), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_HOTKEY_START, CRect(23, 265, 60, 280),  CLangX::Get(s_Words, s_nWords, LANG_HOTKEY_START), NULL, CLR_TRPT),
		UI_STATIC(this, STC_KBMACRO_HOTKEY_STOP,	 CRect(23, 285, 60, 300),  CLangX::Get(s_Words, s_nWords, LANG_HOTKEY_STOP), NULL, CLR_TRPT),
	};
	for (int i = STC_KBMACRO_DELAY_TIME;i <= STC_KBMACRO_HOTKEY_STOP;i++)
	{
		m_stc[i].CreateStatic(sta[i - (int)STC_KBMACRO_DELAY_TIME]);
		m_stc[i].ModifyCtrlStyle(ST_VCENTER,ST_LEFT);
		m_stc[i].SetFont(Font(11), CLR_WHITE);
		m_stc[i].ShowWindow(SW_HIDE);//隱藏，使用背景上的名稱
	}
 	m_stc[STC_KBMACRO_KB].ShowWindow(SW_SHOW);
 	m_stc[STC_KBMACRO_MOUSE].ShowWindow(SW_SHOW);
 	m_stc[STC_KBMACRO_LOCATION].ShowWindow(SW_SHOW);


	//繪製DELAY TIME列表
	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].Create(this, PANEL_KBMACRO_DELAYTIME_NAV, CRect(30, 112, 45, 165));//23, 97, 50, 191
	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].AddItem(&UIPC_ITEM(0, CRect(0, 0, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));//IDB_RADIO_UNCHECK
	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].AddItem(&UIPC_ITEM(1, CRect(0, 19, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));
	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].AddItem(&UIPC_ITEM(2, CRect(0, 37, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));
	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].SetCursor(IDC_CUR_HAND);

	//繪製EXEC MODE列表
 	m_panel[PANEL_KBMACRO_EXECMODE_NAV].Create(this, PANEL_KBMACRO_EXECMODE_NAV, CRect(220, 112, 235, 165));
 	m_panel[PANEL_KBMACRO_EXECMODE_NAV].AddItem(&UIPC_ITEM(0, CRect(0, 0, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));
 	m_panel[PANEL_KBMACRO_EXECMODE_NAV].AddItem(&UIPC_ITEM(1, CRect(0, 19, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));
 	m_panel[PANEL_KBMACRO_EXECMODE_NAV].AddItem(&UIPC_ITEM(2, CRect(0, 37, 0, 0), &UIPC_IMAGE(0, 0, IDB_RADIO_CHECK, CLR_NONE), NULL));
 	m_panel[PANEL_KBMACRO_EXECMODE_NAV].SetCursor(IDC_CUR_HAND);

	m_edit[EDIT_KBMACRO_MACRO].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(22, 60, 186, 76), this, EDIT_KBMACRO_MACRO);//22, 60, 186, 76
	m_edit[EDIT_KBMACRO_MACRO].SetFont(Font(11), CLR_WHITE);
	m_edit[EDIT_KBMACRO_MACRO].SetBkColor(CLR_DARK);
	m_edit[EDIT_KBMACRO_MACRO].ShowWindow(SW_HIDE);

	m_edit[EDIT_KBMACRO_MS].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(82, 129, 112, 139), this, EDIT_KBMACRO_MS);
	m_edit[EDIT_KBMACRO_MS].SetFont(Font(10), CLR_WHITE);
	m_edit[EDIT_KBMACRO_MS].SetBkColor(CLR_DARK);
	m_edit[EDIT_KBMACRO_MS].SetAsIntNumberEdit(5);

// 	m_HotKeyStart.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(65,  260, 127,  280), this, 0);
// 	m_HotKeyStart.SetBkColor(CLR_DARK);
// 	m_HotKeyStart.SetFont(Font(11), CLR_WHITE);
// 	m_HotKeyStop.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(65, 285, 127, 305), this, 0);
// 	m_HotKeyStop.SetBkColor(CLR_DARK);
// 	m_HotKeyStop.SetFont(Font(11), CLR_WHITE);

 	m_list.CreateList(LST_KBMACRO, CRect(23, 274, 239, 399), this, 1, 30, true);//305265673424 140, 216, 410, 460
 	m_list.SetScrollSliCtrl(
 		UI_SLIDERCTRL(&m_list, 1, CRect(208,  11, 0, 0), IDB_MARCO_SCR_BAR, IDB_MARCO_SCR_BAR, 0, IDB_MARCO_SCR_SLI, IDB_MARCO_SCR_SLI, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE)
 		, UI_BTN(&m_list, 2, CRect(208,   0, 0, 0), &UIBTN_IMAGE(IDB_MARCO_SCR_UP,   IDB_MARCO_SCR_UP,   IDB_MARCO_SCR_UP,   0))
 		, UI_BTN(&m_list, 3, CRect(208, 114, 0, 0), &UIBTN_IMAGE(IDB_MARCO_SCR_DOWN, IDB_MARCO_SCR_DOWN, IDB_MARCO_SCR_DOWN, 0)));
 	m_list.InsertColumn(0, _T("ICON"), LVCFMT_CENTER);
 	m_list.InsertColumn(1, _T("NAME"), LVCFMT_CENTER);
 	m_list.SetColumnWidth(0,  0); // 設置列寬度
 	m_list.SetColumnWidth(1, 216);
	m_list.SetItemText(m_list.InsertImgItem(0, IDB_MARCO_DELAY), 1, _T("")); 
 	m_list.RemoveImgItem(0);

	m_stc[STC_KBMACRO_HOTKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KBMACRO_HOTKEY_START].ShowWindow(SW_HIDE);
	m_stc[STC_KBMACRO_HOTKEY_STOP].ShowWindow(SW_HIDE);



}

LRESULT CMacroKeyDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_KBMACRO_INSFUN:  
		{
			CInsertActionDlg insert;
			if(IDOK == insert.DoModal())
			{
				switch (insert.m_nType)
				{
				case 0:
					{
						m_dwLastTime = -1; // 防止記錄delay時間
						insert.m_input.data.keyboard.Flags = (m_list.GetCurSel() < 0 ? 0:1); // 改爲彈起
						ShowInputKey(insert.m_input.data.keyboard, true);
						insert.m_input.data.keyboard.Flags = (m_list.GetCurSel() < 0 ? 1:0);
					//	insert.m_input.data.keyboard.Flags = 0; // 改爲彈起
						m_dwLastTime = -1;
						ShowInputKey(insert.m_input.data.keyboard, true);
						break;
					}
				case 1:
					{
						m_dwLastTime = -1;
						insert.m_input.data.mouse.usButtonFlags = (m_list.GetCurSel() < 0 ?(insert.m_input.data.mouse.usButtonFlags ):(insert.m_input.data.mouse.usButtonFlags << 1));
						ShowInputKey(insert.m_input.data.mouse, false, true);
						insert.m_input.data.mouse.usButtonFlags = (m_list.GetCurSel() < 0 ?(insert.m_input.data.mouse.usButtonFlags << 1):(insert.m_input.data.mouse.usButtonFlags >>1));
						m_dwLastTime = -1;
						ShowInputKey(insert.m_input.data.mouse, false, true);
						break;
					}
				case 2:
					{
						ShowLocation(insert.m_pt, true);
						break;
					}
				default: break;
				}
				ApplyEnable(true);
			}
			break;
		}

	case BTN_KBMACRO_INSTIME:
		{
			
			try{
				CInsertActionDlg insert;
				insert.m_nType = 4;
				if(IDOK == insert.DoModal())
				{
					ShowRealTime(insert.m_nDelay, true);
					ApplyEnable(true);
				}
			}
		catch(...)
		{
		
		}

			break;
		}

	case BTN_KBMACRO_DELONE: 
		{
			int index = m_list.GetCurSel();
			if (index == -1) break;

			m_list.RemoveImgItem(index);

			for (int i = index; i < m_curmarco.nCount - 1; i++)
			{
				m_curmarco.macros[i] = m_curmarco.macros[i + 1];
			}
			m_curmarco.nCount --;
			ApplyEnable(true);
			break;
		}
	
	case BTN_KBMACRO_DELALL: OnClear(); break;
	case BTN_KBMACRO_RECORD: RecodeMarcoKey(); break;
	case BTN_KBMACRO_PROADD: AddMarcoKey(); break;
	case BTN_KBMACRO_PROEDIT: EditMarcoName(); break;
	case BTN_KBMACRO_PRODEL: RemoveMarcoKey(); break;
	case BTN_KBMACRO_IMPORT: ImportMarcoKey(); break;
	case BTN_KBMACRO_EXPORT: 	
		{
			int a = m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel();
			if (m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel() == -1)
			{
				AfxMessageBox(_T("Not selected macro"));
				return 1;
			}
			ExportMarcoKey();
		}
		break;	// 導出導入按钮，也就是import和export

	case BTN_KBMACRO_APPLY: 
		AfxBeginThread(ApplyThread, this);
		break;
	case BTN_KBMACRO_ONCLOSE:
		OnClose();
		break;
// 	case BTN_KBMACRO_MINIMIZE:
// 		OnMinimize();
// 		break;

	default: return 0;	
	}
	return 1;
}

LRESULT CMacroKeyDlg::OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nPanelId = (int)wParam;
	int nPanelItem = (int)lParam;
 	switch(nPanelId)
 	{
 	case PANEL_KBMACRO_DELAYTIME_NAV:
 		if(1 == nPanelItem) m_edit[EDIT_KBMACRO_MS].SetFocus();
 		break;
 	case PANEL_KBMACRO_EXECMODE_NAV:
 		break;
 	}
	ApplyEnable(true);
	return 1;
}

LRESULT CMacroKeyDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nId = (int)wParam;
	int nItem = (int)lParam;
	switch(nId)
	{
	case COMBOX_KBMACRO_PROFILE:
		LoadMarcoKey(nItem);
		break;
	}
	return 1;
}

void CMacroKeyDlg::InitMacroState()
{
	m_Resolution.x = GetSystemMetrics(SM_CXSCREEN); 
	m_Resolution.y = GetSystemMetrics(SM_CYSCREEN); 
	LoadMacrosList();
}


void CMacroKeyDlg::OnFit(CRect rcParentCli)
{
	int nX = rcParentCli.left + rcParentCli.Width();
	int nY = rcParentCli.top + 78;
	SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
	SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
}


void CMacroKeyDlg::InitState()
{
	//CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	//CRect rcCli;
	//pParent->GetClientRect(rcCli);
	//pParent->ClientToScreen(&rcCli);
	//OnFit(rcCli);

	// Initialize monitoring curves.

	//ShowWindow(SW_SHOW);
	//SetTimer(2, 10, NULL);

	//m_EditDlg.InitState();
}

 void CMacroKeyDlg::OnRawInput(UINT nInputcode, HRAWINPUT hRawInput)
{
 	if(!m_bRecord) return;
 	bool bPause = false;// m_btn[BTN_MARCO_RECORD_STOP].IsCheck(); // 是否可以用pause鍵停止錄製
 
 	UINT dwSize;
 	BYTE lpb[1000];
 	BYTE lpb2[1000];
 	RAWINPUT* raw;
 
 	GetRawInputData(hRawInput, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
 	if (dwSize < sizeof (lpb))
 	{
 		if (GetRawInputData(hRawInput, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize)
 		{
 			raw = (RAWINPUT*)lpb;
 			if (raw->header.dwType == RIM_TYPEMOUSE) // 鼠標
 			{
 				RAWMOUSE mouse = raw->data.mouse;
 				ShowInputKey(mouse, true, false);
 			}
 			if (raw->header.dwType == RIM_TYPEKEYBOARD) // 鍵盤
 			{
 				RAWKEYBOARD keyboard = raw->data.keyboard;
 				if(bPause && keyboard.VKey == VK_PAUSE)
 				{
 					OnUiButtonClicked(BTN_KBMACRO_RECORD, NULL);
 				}
 				else
 				{
 					ShowInputKey(keyboard, false);
 				}
 			}
 		}
 	}
 
 	CUiDlg::OnRawInput(nInputcode, hRawInput);
}




bool CMacroKeyDlg::ShowInputKey(RAWMOUSE mouse, bool bLocation, bool bInsert)
{
	if(m_curmarco.nCount >= GVORDER_MACROS_MAX - 3) return false; // 不能超過MARCO最大個數

	int icon = 0;
	CString sValue = _T("");

	GVORDER_MACROS_UNIT unit;
	switch(mouse.usButtonFlags)
	{
	case RI_MOUSE_LEFT_BUTTON_DOWN: // 鼠標左鍵按下或者放開
		sValue += _T("Press & hold mouse button[Left]");
//		icon = IDB_MARCO_MS_DOWN;
		unit.dwValue = GVORDER_MOUSE_LEFT;
		unit.nType = GVORDER_MACROS_MOUSEDOWN;
		break;
	case RI_MOUSE_LEFT_BUTTON_UP:
		sValue += _T("Release mouse button[Left]");
//		icon = IDB_MARCO_MS_UP;
		unit.dwValue = GVORDER_MOUSE_LEFT;
		unit.nType = GVORDER_MACROS_MOUSEUP;
		break;

	case RI_MOUSE_RIGHT_BUTTON_DOWN:  // 鼠標右鍵按下或者放開
		sValue += _T("Press & hold mouse button[Right]");
//		icon = IDB_MARCO_MS_DOWN;
		unit.dwValue = GVORDER_MOUSE_RIGHT;
		unit.nType = GVORDER_MACROS_MOUSEDOWN;
		break;
	case RI_MOUSE_RIGHT_BUTTON_UP:		
		sValue += _T("Release mouse button[Right]");
//		icon = IDB_MARCO_MS_UP;
		unit.dwValue = GVORDER_MOUSE_RIGHT;
		unit.nType = GVORDER_MACROS_MOUSEUP;
		break;

	case RI_MOUSE_MIDDLE_BUTTON_DOWN:	 // 鼠標中鍵按下或者放開
		sValue += _T("Press & hold mouse button[Middle]");
//		icon = IDB_MARCO_MS_DOWN;
		unit.dwValue = GVORDER_MOUSE_MIDDLE;
		unit.nType = GVORDER_MACROS_MOUSEDOWN;
		break;
	case RI_MOUSE_MIDDLE_BUTTON_UP:		
		sValue += _T("Release mouse button[Middle]");
//		icon = IDB_MARCO_MS_UP;
		unit.dwValue = GVORDER_MOUSE_MIDDLE;
		unit.nType = GVORDER_MACROS_MOUSEUP;
		break;
	case RI_MOUSE_WHEEL:				 // 鼠標滾輪
		{
			if (0x0078 == mouse.usButtonData)
			{
				sValue += _T("Mouse Scroll Up ");
				unit.nType = GVORDER_MACROS_SCROLLUP;
			}
			else if ( 0xff88 == mouse.usButtonData)
			{
				sValue += _T("Mouse Scroll Down ");
				unit.nType = GVORDER_MACROS_SCROLLDOWN;
			}
//			icon = IDB_MARCO_WHEEL;
			break;
		}
	default: return false;
	}

	ShowInputTime();

	if(bLocation)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ShowLocation(pt, true);
	}

	//Terry 2017/07/06
// 	m_curmarco.macros[m_curmarco.nCount++] = unit;
// 	m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue);
// // 
	int curSel;
	curSel = m_list.GetCurSel();
	if (curSel < 0)
	{
		curSel = m_list.GetItemCount() - 1;

	}
	if (bInsert)
	{

		m_list.SetItemText(m_list.InsertImgItem(curSel+1, icon), 1, sValue);
		m_curmarco.Append(unit, curSel);
	}
	else
	{
		m_curmarco.macros[m_curmarco.nCount++] = unit;	
		m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue);
	}





	return true;
}


bool CMacroKeyDlg::ShowInputKey(RAWKEYBOARD keyboard, bool bInsert)
{

	if(0xff == keyboard.VKey) return false;

	int icon = 0;
	CString sValue = _T("");

	static RAWKEYBOARD keyOld = {0}; // 用來防止用戶按住不放

	if((keyboard.Flags == keyOld.Flags 
		&& keyboard.VKey == keyOld.VKey 
		|| m_curmarco.nCount >= GVORDER_MACROS_MAX)) // 防止用戶按住不放
		return false;

	keyOld = keyboard;

	ShowInputTime();

	TranslateKey(keyboard);

	GVORDER_MACROS_UNIT unit; // 表示一條記錄
	unit.dwValue = keyboard.VKey;

	CString sKey = GetKeyName(keyboard.VKey);

	if ((keyboard.Flags & RI_KEY_BREAK) == RI_KEY_BREAK)
	{
		sValue += _T("Release key ");
		sValue += sKey;
//		icon = IDB_MARCO_KB_UP;
		unit.nType = GVORDER_MACROS_KEYBOARDUP;
	}
	else if ((keyboard.Flags & RI_KEY_MAKE) == RI_KEY_MAKE)
	{
		sValue += _T("Press & hold key ");
		sValue += sKey;

//		icon = IDB_MARCO_KB_DOWN;
		unit.nType = GVORDER_MACROS_KEYBOARDOWN;
	}
	else{
		return false;
	}

// 	m_curmarco.macros[m_curmarco.nCount++] = unit;	
// 	m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue);
// 	int curSel;
// 	curSel = m_list.GetCurSel();
// 	if (curSel < 0 )
// 	{
// 		m_curmarco.macros[m_curmarco.nCount++] = unit;	
// 		m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue);
// 		return true;
// 	}

	int curSel;
		curSel = m_list.GetCurSel();
		if (curSel < 0)
		{
			curSel = m_list.GetItemCount() - 1;

		}
	if (bInsert)
	{

		m_list.SetItemText(m_list.InsertImgItem(curSel+1, icon), 1, sValue);
		m_curmarco.Append(unit, curSel);
	}
	else
	{
		m_curmarco.macros[m_curmarco.nCount++] = unit;	
		m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue);
	}


	return true;
}

void CMacroKeyDlg::ShowRealTime(int nDelay, bool bInsert)
{
	CString sTime;
	sTime.Format(_T("Delay %d ms"), nDelay);

	GVORDER_MACROS_UNIT unit;
	unit.dwValue = nDelay;
	unit.nType = GVORDER_MACROS_DELAY;
	//Terry 2017/07/06
//	m_curmarco.macros[m_curmarco.nCount++] = unit;
//	m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), IDB_MARCO_DELAY),1, sTime); 

	int curSel;
	curSel = m_list.GetCurSel();
	if (curSel < 0)
	{
		curSel = m_list.GetItemCount() - 1;

	}
	if (bInsert)
	{

		m_list.SetItemText(m_list.InsertImgItem(curSel+1, 0), 1, sTime);
		m_curmarco.Append(unit, curSel);
	}
	else
	{
		m_curmarco.macros[m_curmarco.nCount++] = unit;	
		m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), 0), 1, sTime);
	}
}

bool CMacroKeyDlg::ShowLocation(CPoint pt, bool bInsert)
{
	GVORDER_MACROS_UNIT unitMove;
	CString sMousePt;
	unitMove.nType = GVORDER_MACROS_MOUSEX;
	unitMove.dwValue = MouseCoorToData(pt.x, m_Resolution.x);
	m_curmarco.macros[m_curmarco.nCount++] = unitMove;
	unitMove.nType = GVORDER_MACROS_MOUSEY;
	unitMove.dwValue = MouseCoorToData(pt.y, m_Resolution.y);
//	m_curmarco.macros[m_curmarco.nCount++] = unitMove;
	sMousePt.Format(_T("X:%d, Y:%d"), pt.x, pt.y);
//	m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), 0), 1, sMousePt);
 

	//Terry 2017/07/06
	int curSel;
	curSel = m_list.GetCurSel();
	if (curSel < 0)
	{
		curSel = m_list.GetItemCount() - 1;

	}
	if (bInsert)
	{

		m_list.SetItemText(m_list.InsertImgItem(curSel+1, 0), 1, sMousePt);
		m_curmarco.Append(unitMove, curSel);
	}
	else
	{
		m_curmarco.macros[m_curmarco.nCount++] = unitMove;	
		m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), 0), 1, sMousePt);
	}

	return true;
}

void CMacroKeyDlg::OnClear()
{
	// 清空當前顯示Marco
	m_list.RemoveAllItem();
	m_curmarco.nCount = 0;
	ApplyEnable(true);
}

void CMacroKeyDlg::RecodeMarcoKey()
{

	if(m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel() < 0)
	{
		m_btn[BTN_KBMACRO_RECORD].SetCheck(false);
		AfxMessageBox(_T("Please select at least one macro."));
		return;
	}

	int nType = 0;

	// 生成需要監聽的設備消息
	if (m_btn[BTN_KBMACRO_KB].IsCheck())		nType |= RAW_DEV_KB;
	if (m_btn[BTN_KBMACRO_MOUSE].IsCheck())	nType |= RAW_DEV_MS;
	if (m_btn[BTN_KBMACRO_LOCATION].IsCheck()) nType |= RAW_DEV_MS;

	if (0 == nType)
	{
		m_btn[BTN_KBMACRO_RECORD].SetCheck(false);
		AfxMessageBox(_T("You must select at least one action type."));
		return;
	}

	int iMs = 0;
	iMs = m_edit[EDIT_KBMACRO_MS].GetWindowsValue();
	if (iMs >= 60000)
	{
		iMs = 60000;
		m_edit[EDIT_KBMACRO_MS].SetWindowsValue(iMs);
	}
	m_bRecord = !m_bRecord; // 更改當前Recode狀態
	m_dwLastTime = -1;
	
// 	nType |= RAW_DEV_KB;
// 	nType |= RAW_DEV_MS; 
// 	nType |= RAW_DEV_MS; 


	RawInputDevices(m_hWnd, nType, m_bRecord);
// 
// 	if (!m_bRecord)
// 	{
// 		if(m_list.GetItemCount() > 0){ m_list.RemoveImgItem(m_list.GetItemCount() - 1); m_curmarco.nCount--; }
// 		if(m_list.GetItemCount() > 0){ m_list.RemoveImgItem(m_list.GetItemCount() - 1); m_curmarco.nCount--; }
// 		if(m_list.GetItemCount() > 0){ m_list.RemoveImgItem(m_list.GetItemCount() - 1); m_curmarco.nCount--; }
// 		if(m_list.GetItemCount() > 0){ m_list.RemoveImgItem(m_list.GetItemCount() - 1); m_curmarco.nCount--; }
// 	}

	ApplyEnable(true);
	// 禁用/啓用界面控件
	EnableRecodeUi(!m_bRecord);


}

void CMacroKeyDlg::AddMarcoKey()
{
	CString sName;
	int nMacroNum = 0;


	int nIcon = GetEmptyMarcoIndex();		// 獲取可以存放的Marco Key Index
	nMacroNum = nIcon + 1;
	sName.Format(_T("Macro%d"), nMacroNum);
	if (nIcon < 0)
	{
		AfxMessageBox(_T("The Marco Key was full!"));
		return;
	}

	m_edit[EDIT_KBMACRO_MACRO].ShowWindow(SW_HIDE);
	m_combobox[COMBOX_KBMACRO_PROFILE].ShowWindow(SW_SHOW);

	// 加入新增列表
	GVORDER_MACROS* pNew = new GVORDER_MACROS;
	ZeroMemory(pNew, sizeof(GVORDER_MACROS));
	pNew->attr.nIcon = nIcon + 1;
	pNew->nIndex = nIcon;
	_tcscpy(pNew->attr.szName, sName);
	m_newmarco.SetAtGrow(m_newmarco.GetCount(), pNew);
	m_curmarco = *pNew;

	// 保存下拉框與創建Marco對應關係
	int nCmbIndex = m_combobox[COMBOX_KBMACRO_PROFILE].GetCount();
	m_cmbMarco[nCmbIndex].nIndex = m_curmarco.nIndex;
	m_cmbMarco[nCmbIndex].nType = MARCO_NEW;

	// 加入下拉框并選中
	m_combobox[COMBOX_KBMACRO_PROFILE].AddString(sName, 0, CLR_WHITE);
	m_combobox[COMBOX_KBMACRO_PROFILE].SetCurSel(nCmbIndex);

	m_dwLastItem = nCmbIndex;
	// 重置Marco界面
	OnDefault();

	ApplyEnable(true);
//	OnApply();//解決新增MACRO燈滅的問題
}

int CMacroKeyDlg::GetEmptyMarcoIndex()
{
	for (int i = 0; i < KB_MARCO_COUNT; i++)
	{
		if (m_marcos[i].attr.nIcon <= 0 || m_marcos[i].attr.nIcon > KB_MARCO_COUNT)
		{
			return i;
		}
	}
	return -1;
}

void CMacroKeyDlg::OnDefault()
{
	m_edit[EDIT_KBMACRO_MACRO].SetWindowText(_T(""));
	OnClear();
}

void CMacroKeyDlg::EditMarcoName()
{

	int nIndex = m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel();
	if (nIndex < 0)
	{
		m_btn[BTN_KBMACRO_PROEDIT].SetCheck(false);
		AfxMessageBox(_T("Please select one Macro!"));
		return;
	}

	CBB_MARCO cmb = m_cmbMarco[nIndex];

	bool bCheck = m_btn[BTN_KBMACRO_PROEDIT].IsCheck();
 	m_btn[BTN_KBMACRO_PROADD].Enable(!bCheck);
 	m_btn[BTN_KBMACRO_PRODEL].Enable(!bCheck);
 	m_edit[EDIT_KBMACRO_MACRO].ShowWindow(bCheck ? SW_SHOW : SW_HIDE);
 	m_combobox[COMBOX_KBMACRO_PROFILE].ShowWindow(bCheck ? SW_HIDE : SW_SHOW);

	if(bCheck)
	{
		m_edit[EDIT_KBMACRO_MACRO].EnableWindow(TRUE);
		m_edit[EDIT_KBMACRO_MACRO].SetWindowText(m_curmarco.attr.szName);
		m_edit[EDIT_KBMACRO_MACRO].SetFocus();
	}
	
	else{
 		CString sName = _T("");
 		m_edit[EDIT_KBMACRO_MACRO].GetWindowText(sName);
 		sName.Trim();
		if(sName.GetLength() > 14) sName.Mid(0, 14); // 若名稱過長，則截斷
 		if (_T("") == sName)
 		{
 			sName = m_curmarco.attr.szName; // set it back
 			m_edit[EDIT_KBMACRO_MACRO].SetWindowText(sName);
 		}

		m_combobox[COMBOX_KBMACRO_PROFILE].SetString(nIndex, sName);
		m_combobox[COMBOX_KBMACRO_PROFILE].SetCurSel(nIndex);

		if (cmb.nType == MARCO_NEW)
		{
			_tcscpy(((GVORDER_MACROS*)m_newmarco.GetAt(cmb.nIndex))->attr.szName, sName);
		}
		else if(cmb.nType == MARCO_LOAD)
		{
			_tcscpy(((GVORDER_MACROS*)m_lstMarco.GetAt(cmb.nIndex))->attr.szName, sName);
		}
		ApplyEnable(true);
	}

}

void CMacroKeyDlg::RemoveMarcoKey()
{
	int nIndex = m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel();
	CBB_MARCO cmb = m_cmbMarco[nIndex];
	int i = nIndex;

	for (int j = i; i < KB_MARCO_COUNT - 1; i++)
		m_cmbMarco[j] = m_cmbMarco[j + 1];

	if (cmb.nType == MARCO_NEW)
	{
		m_newmarco.RemoveAt(0);
		ApplyEnable(false);
	}
	else if(cmb.nType == MARCO_LOAD)
	{
		GVORDER_MACROS* pDel = new GVORDER_MACROS;
		*pDel = *(GVORDER_MACROS*)m_lstMarco.GetAt(cmb.nIndex);
		m_delmarco.SetAtGrow(m_delmarco.GetCount(), pDel);
		((GVORDER_MACROS*)m_lstMarco.GetAt(cmb.nIndex))->attr.nIcon = 0;
	}

	m_combobox[COMBOX_KBMACRO_PROFILE].DeleteString(nIndex);

	OnDefault();

	ApplyEnable(cmb.nType == MARCO_LOAD);
	m_bUpdate = cmb.nType == MARCO_LOAD;
	m_dwLastItem = -1;
}

void CMacroKeyDlg::ImportMarcoKey()
{
	CString sPath = Browse(_T("Marco Files (*.dat)|*.dat;||"), _T("dat"), TRUE);
	if(!sPath.IsEmpty())
	{
		GVORDER_MACROS macros;
		if(GVAPI_OK == GvOrderImportMarco(macros, sPath))
		{
			m_list.RemoveAllItem();

			//設置運行模式
			m_panel[PANEL_KBMACRO_EXECMODE_NAV].SetCurItem((int)macros.attr.RunType);

			for (int i = 0; i < macros.nCount; i++)
			{
				m_curmarco.macros[i] = macros.macros[i];
				ShowMarcoUnit(macros.macros[i]);
			}
			m_curmarco.nCount = macros.nCount;
			MessageBox(_T("Import Success!"), _T("Import Marco"), MB_OK | MB_ICONINFORMATION);
		}
		ApplyEnable(true);
	}
}

void CMacroKeyDlg::ExportMarcoKey()
{
	CString sPath = Browse(_T("Marco Files (*.dat)|*.dat;||"), _T("dat"), FALSE);
	if(!sPath.IsEmpty())
	{
		GVORDER_MACROS macros;
		for (int i =0; i < m_curmarco.nCount; i++)
		{
			macros.macros[i] = m_curmarco.macros[i];
		}
		macros.nCount = m_curmarco.nCount;
		macros.attr.RunType = (GVORDER_MACROS_RUN)m_panel[PANEL_KBMACRO_EXECMODE_NAV].GetCurItem();

		if(GVAPI_OK == GvOrderExportMarco(macros, sPath))
		{
			MessageBox(_T("Export Success!"), _T("Export Marco"), MB_OK | MB_ICONINFORMATION);
		}
	}
}

void CMacroKeyDlg::TranslateKey(RAWKEYBOARD& key)
{
	switch(key.VKey)
	{
	case VK_SHIFT:
		{
			if(key.MakeCode == 0x2A) key.VKey = VK_LSHIFT;
			else if(key.MakeCode == 0x36) key.VKey = VK_RSHIFT;
		} 
		break;
	case VK_CONTROL:
		{
			if(key.Flags < 2) key.VKey = VK_LCONTROL;
			else if(key.Flags > 1) key.VKey = VK_RCONTROL;
		} 
		break;
	case VK_MENU:
		{
			if(key.Flags < 2) key.VKey = VK_LMENU;
			else if(key.Flags > 1) key.VKey = VK_RMENU;
		} 
		break;
	}
}

bool CMacroKeyDlg::IsSpecialKey(USHORT vKey)
{
	int count = 11;
	USHORT special_Key[] = {
		//19,// Pause

		46,// Delete

		36,// Home
		33,// PgUp
		34,// PgDn
		35,// End

		144,// NumLk
		45,// Insert

		37,// Left
		38,// Up
		39,// Right
		40,// Down

		//17, //Right Ctrl
		//16, //Right Shift
		//18, //Right Alt
	};
	for (int i = 0; i < count; i++)
	{
		if (vKey == special_Key[i])
		{
			return true;
		}
	}
	return false;
}

void CMacroKeyDlg::EnableRecodeUi(bool bEnable, bool bRecord)
{
	for(int i=BTN_KBMACRO_PROADD; i <= BTN_KBMACRO_RECORD; i++) 
	{
		m_btn[i].Enable(bEnable);
	}
	m_btn[BTN_KBMACRO_RECORD].Enable(bRecord);

	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].Enable(bEnable);
	m_panel[PANEL_KBMACRO_EXECMODE_NAV].Enable(bEnable);

	m_combobox[COMBOX_KBMACRO_PROFILE].Enable(bEnable);

	m_edit[EDIT_KBMACRO_MS].EnableWindow(bEnable);

}

int CMacroKeyDlg::MouseCoorToData(int nValue, int nResolu)
{
	return nValue * 32767 / nResolu;

}

int CMacroKeyDlg::DataToMouseCoor(int nValue, int nResolu)
{
	return nValue * nResolu / 32767;
}

CString CMacroKeyDlg::GetKeyName(DWORD dwKeyCode)
{
	CString sKey = CHotKeyCtrl::GetKeyName(dwKeyCode, FALSE);

	if (dwKeyCode == 19) // Pause
	{
		sKey = _T("Pause");
	}
	else if (IsSpecialKey(dwKeyCode))
	{
		sKey = CHotKeyCtrl::GetKeyName(dwKeyCode, TRUE);
	}

	//CString sKey1 = CHotKeyCtrl::GetKeyName(keyboard.VKey, TRUE);
	if(_T(" ") == sKey) 
	{
		sKey = _T("Space");
	}
	else if(sKey.IsEmpty()) // 如果是空字符串，則可能是擴展鍵
	{
		sKey = CHotKeyCtrl::GetKeyName(dwKeyCode, TRUE);
	}

	switch(dwKeyCode)
	{
	case VK_LCONTROL:	return _T("Left Ctrl");		// Left Ctrl
	case VK_LSHIFT:		return _T("Left Shift");	// Left Shift
	case VK_LMENU:		return _T("Left Alt");		// Left Alt
	case VK_LWIN:		return _T("Left Win");		// Left Win
	case VK_RCONTROL:	return _T("Right Ctrl");	// Right Ctrl
	case VK_RSHIFT:		return _T("Right Shift");	// Right Shift
	case VK_RMENU :		return _T("Right Alt");		// Right Alt
	case VK_RWIN:		return _T("Right Win");		// Right Win
	}
	return sKey;
}

void CMacroKeyDlg::ShowMarcoKey(GVORDER_MACROS marco)
{
	m_curmarco = marco;
	m_list.RemoveAllItem();

	m_panel[PANEL_KBMACRO_DELAYTIME_NAV].SetCurItem(marco.attr.TimeMode);
	m_panel[PANEL_KBMACRO_EXECMODE_NAV].SetCurItem(marco.attr.RunType);

	if (GVORDER_MACROS_FIXEDTIME == marco.attr.TimeMode)
	{
		for (int i = 0; i < marco.nCount; i++)
		{
			if (GVORDER_MACROS_DELAY == marco.macros[i].nType)
			{
				int nDelay = marco.macros[i].dwValue;
				m_edit[EDIT_KBMACRO_MS].SetWindowsValue(nDelay);
				break;
			}
		}
	}

	if (marco.attr.nIcon < 1 || marco.attr.nIcon > KB_MARCO_COUNT)
	{
		return;
	}

	for (int i =0; i < marco.nCount; i++)
	{
		ShowMarcoUnit(marco.macros[i]);
	}
}

void CMacroKeyDlg::ShowMarcoUnit(GVORDER_MACROS_UNIT unit)
{
	int icon = 0; // 
	CString sValue = _T(""); // 

	switch(unit.nType)
	{
	case GVORDER_MACROS_KEYBOARDUP: // 鍵盤彈起
		{ 
			sValue += _T("Release key ") + GetKeyName(unit.dwValue);
	//		icon = IDB_MARCO_KB_UP;
			break; 
		}
	case GVORDER_MACROS_KEYBOARDOWN: // 鍵盤按下
		{ 
			sValue += _T("Press & hold key ") + GetKeyName(unit.dwValue);
	//		icon = IDB_MARCO_KB_DOWN;
			break; 
		} 
	case GVORDER_MACROS_MOUSEUP: // 鼠標彈起
		{ 
			CString sMouse[] = {_T(""), _T("Release mouse button[Left]"), _T("Release mouse button[Right]"), _T(""), _T("Release mouse button[Middle]")};
			sValue = sMouse[unit.dwValue];
	//		icon = IDB_MARCO_MS_UP;
			break; 
		}
	case GVORDER_MACROS_MOUSEDOWN: // 鼠標按下
		{ 
			CString sMouse[] = {_T(""), _T("Press & hold mouse button[Left]"), _T("Press & hold mouse button[Right]"), _T(""), _T("Press & hold mouse button[Middle]")};
			sValue = sMouse[unit.dwValue];
	//		icon = IDB_MARCO_MS_DOWN;
			break; 
		}
	case GVORDER_MACROS_SCROLLUP:
		{ 
			sValue += _T("Mouse Scroll Up ");
//			icon = IDB_MARCO_WHEEL;
			break; 
		}
	case GVORDER_MACROS_SCROLLDOWN:
		{ 
			sValue += _T("Mouse Scroll Down ");
//			icon = IDB_MARCO_WHEEL;
			break; 
		}
	case GVORDER_MACROS_DELAY:
		{ 
			sValue.Format(_T("Delay %d ms"), (long)unit.dwValue);
//			icon = IDB_MARCO_DELAY;
			break; 
		}
	case GVORDER_MACROS_MOUSEX:
	case GVORDER_MACROS_MOUSEY:
		{ 
			static GVORDER_MACROS_UNIT lastUnit;
			if(GVORDER_MACROS_MOUSEX == unit.nType)
			{
				lastUnit = unit;
				return;
			}
			else if(GVORDER_MACROS_MOUSEX == lastUnit.nType 
				&& GVORDER_MACROS_MOUSEY == unit.nType)
			{
				int nX = DataToMouseCoor(lastUnit.dwValue, m_Resolution.x);
				int nY = DataToMouseCoor(unit.dwValue, m_Resolution.y);
				sValue.Format(_T("Move Mouse to X:%d, Y:%d"), nX, nY);
	//			icon = IDB_MARCO_LOCATION;
			}
			break; 
		}
	default: return;
	}

	m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), icon), 1, sValue); 
}

void CMacroKeyDlg::ApplyEnable(bool bEnable)
{
	m_bUpdate = bEnable;
// 	m_btn[BTN_KB_MARCO_RESET].Enable(bEnable);
// 	m_btn[BTN_KB_MARCO_DEFAULT].Enable(bEnable);
//	m_btn[BTN_KBMACRO_APPLY].Enable(bEnable);
 	m_edit[EDIT_KBMACRO_MACRO].EnableWindow(!bEnable);
}

void CMacroKeyDlg::LoadMarcoKey(int nItem)
{
	// 加載下拉列表選中的Marco Key
	CBB_MARCO cmb = m_cmbMarco[m_dwLastItem];
	GVORDER_MACROS* pCur = NULL;

	if (m_bUpdate && IDNO == MessageBox(_T("You have some settings were not saved, confirm to continue ?"), _T("Confirm"), MB_YESNO | MB_ICONWARNING))
	{
		m_combobox[COMBOX_KBMACRO_PROFILE].SetCurSel(m_dwLastItem);
		//pCur = cmb.nType == MARCO_NEW ? (GVORDER_MACROS*)m_newmarco.GetAt(cmb.nIndex) : (GVORDER_MACROS*)m_lstMarco.GetAt(cmb.nIndex);
		//*pCur = m_curmarco;
		return;
	}
	else if (m_bUpdate)
	{
		LoadMacrosList();
		m_combobox[COMBOX_KBMACRO_PROFILE].Invalidate(TRUE);
		m_combobox[COMBOX_KBMACRO_PROFILE].UpdateWindow();
	}

	cmb = m_cmbMarco[nItem];

	if (cmb.nType == MARCO_NEW) // 新增未保存
	{
		pCur = (GVORDER_MACROS*)m_newmarco.GetAt(cmb.nIndex);
	}
	else if(cmb.nType == MARCO_LOAD) // 已保存 
	{
		pCur = (GVORDER_MACROS*)m_lstMarco.GetAt(cmb.nIndex);
		
		switch (m_DeviceType)
		{
		case DEVICE_AK700:
			CKbLedCtrl::GetMacrosKey(*pCur); // 從FW加載Marco Key
			break;
		case DEVICE_AM300:
			CAM300Ctrl::GetMacrosKey(*pCur); // 從FW加載Marco Key
			break;
		}
	}

	ShowMarcoKey(*pCur);

	ApplyEnable(false);
	m_dwLastItem = nItem;
}

CString CMacroKeyDlg::Browse(LPCTSTR lpszFilter, LPCTSTR lpszDefExt, BOOL bOpen)
{
	CString sPathName = _T("");
	CFileDialog dlg(bOpen, 
		lpszDefExt,
		NULL, 
		OFN_HIDEREADONLY | OFN_EXPLORER,
		lpszFilter, 
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		sPathName = dlg.GetPathName();
	}
	return sPathName;
}

CString CMacroKeyDlg::ShowInputTime()
{
	CString sTime = _T("");
	if(m_dwLastTime < 0)
	{
		m_dwLastTime = ::GetTickCount();
		return sTime;
	}

	DWORD dwTick = GetTimeElapse(m_dwLastTime);
	switch((GVORDER_MACROS_TIME)m_panel[PANEL_KBMACRO_DELAYTIME_NAV].GetCurItem())
	{
	case GVORDER_MACROS_AUTO: // auto
		{
			sTime.Format(_T("Delay %d ms"), dwTick);

			GVORDER_MACROS_UNIT unit;
			unit.dwValue = dwTick;
			unit.nType = GVORDER_MACROS_DELAY;
			m_curmarco.macros[m_curmarco.nCount++] = unit;
			m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), IDB_MARCO_DELAY), 1, sTime);
			break;
		}
	case GVORDER_MACROS_FIXEDTIME: // fixed
		{
			dwTick = m_edit[EDIT_KBMACRO_MS].GetWindowsValue();
			sTime.Format(_T("Delay %d ms"), dwTick);

			GVORDER_MACROS_UNIT unit;
			unit.dwValue = dwTick;
			unit.nType = GVORDER_MACROS_DELAY;
			m_curmarco.macros[m_curmarco.nCount++] = unit;
			m_list.SetItemText(m_list.InsertImgItem(m_list.GetItemCount(), IDB_MARCO_DELAY), 1, sTime);
			break;
		}
	case GVORDER_MACROS_NONE: // no Delay
		break;
	}
	m_dwLastTime = ::GetTickCount();
	return sTime;
}

void CMacroKeyDlg::LoadMacrosList()
{
	int nCurSel = -1;
	if (m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel() >= 0)
	{
		int nIndex = m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel();
		if(MARCO_LOAD == m_cmbMarco[nIndex].nType)
		{
			nCurSel = m_cmbMarco[nIndex].nIndex; // 獲取原本設定Index
		}
	}

	m_combobox[COMBOX_KBMACRO_PROFILE].ResetContent();
	m_lstMarco.RemoveAll();
	m_delmarco.RemoveAll();
	m_newmarco.RemoveAll();
	GVORDER_MACROS_ATTR lstmacros[KB_MARCO_COUNT];
	// Peter Lee 2017/7/3
	switch (m_DeviceType) 
	{
	case DEVICE_AK700:
		CKbLedCtrl::GetMarcoList(lstmacros, KB_MARCO_COUNT); // 取得內存中的marco
		break;
	case DEVICE_AM300:
		CAM300Ctrl::GetMacrosList(lstmacros, KB_MARCO_COUNT);
		break;
	}
	int index = 0;
	for (int i = 0; i < KB_MARCO_COUNT; i++)
	{
		GVORDER_MACROS_ATTR marco = lstmacros[i];
		m_marcos[i].attr = marco;
		m_marcos[i].nIndex = i;
		GVORDER_MACROS* pMacro = new GVORDER_MACROS;
		*pMacro = m_marcos[i];
		m_lstMarco.SetAtGrow(m_lstMarco.GetCount(), pMacro);

		if (MacroIsValid(marco))
		{
			m_cmbMarco[index].nType = MARCO_LOAD;
			m_cmbMarco[index].nIndex = i;
			m_combobox[COMBOX_KBMACRO_PROFILE].AddString(marco.szName, 0, CLR_MAIN);
			if(i == nCurSel) m_combobox[COMBOX_KBMACRO_PROFILE].SetCurSel(index);
			index++;
		}
	}
	if(nCurSel < 0) OnClear(); // 保留之前選擇内容
	m_edit[EDIT_KBMACRO_MACRO].ShowWindow(SW_HIDE);
	m_combobox[COMBOX_KBMACRO_PROFILE].ShowWindow(SW_SHOW);
	ApplyEnable(false);
}

bool CMacroKeyDlg::MacroIsValid(GVORDER_MACROS_ATTR macro)
{
	return macro.nIcon >= 1 && macro.nIcon <= KB_MARCO_COUNT && ( 0 <= macro.RunType && macro.RunType <= 2);
}

UINT CMacroKeyDlg::ApplyThread(LPVOID lpParam)
{
	CMacroKeyDlg* pMain = (CMacroKeyDlg*)lpParam;
	pMain->OnApply();
	return 0;
}

void CMacroKeyDlg::OnApply()
{
	ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
	CmdLock();
	int nIndex = m_combobox[COMBOX_KBMACRO_PROFILE].GetCurSel();

	CBB_MARCO cmb = m_cmbMarco[nIndex];

	if (m_dwLastItem < 0) // 刪除MarocKey
	{
		for(int i = 0; i < m_delmarco.GetCount(); i++)
		{
			GVORDER_MACROS macros = *((GVORDER_MACROS*)m_delmarco.GetAt(i));
			macros.attr.nIcon = 0;
			switch (m_DeviceType)
			{
			case DEVICE_AK700:
				CKbLedCtrl::SetMacrosKey(macros);
				break;
			case DEVICE_AM300:
				CAM300Ctrl::SetMacrosKey(macros);
				break;
			}
		}
		m_delmarco.RemoveAll();
		LoadMacrosList();
		ApplyEnable(false);
		ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		return;
	}

	GVORDER_MACROS macros = m_curmarco;
	macros.attr.RunType = (GVORDER_MACROS_RUN) m_panel[PANEL_KBMACRO_EXECMODE_NAV].GetCurItem();
	CString sValue;
	m_combobox[COMBOX_KBMACRO_PROFILE].GetWindowText(sValue);
	_tcscpy(macros.attr.szName, sValue);
	macros.attr.TimeMode = (GVORDER_MACROS_TIME) m_panel[PANEL_KBMACRO_DELAYTIME_NAV].GetCurItem();

	switch (m_DeviceType)
	{
	case DEVICE_AK700:
		CKbLedCtrl::SetMacrosKey(macros);
		break;
	case DEVICE_AM300:
		CAM300Ctrl::SetMacrosKey(macros); // 保存。設備index
		break;
	}

	GVORDER_MACROS* pCur = new GVORDER_MACROS;
	*pCur = macros;
	m_lstMarco.InsertAt(nIndex, pCur);
	m_marcos[cmb.nIndex] = macros;
	m_cmbMarco[nIndex].nType = MARCO_LOAD;

	ApplyEnable(false);
	m_edit[EDIT_KBMACRO_MACRO].EnableWindow(TRUE);
	m_newmarco.RemoveAll();
	LoadMacrosList();
	CmdUnLock();
	ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
	// why this ?
	if (m_DeviceType == DEVICE_AK700)
		CXK700Cmd::SwitchProfile(CXK700Cmd::GetProfileIdx());
}

BOOL CMacroKeyDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)    
	{    
		return TRUE;
	}

	else if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE)) //攔截enter和esc按鍵
	{
		return TRUE; // 攔截消息
	}

	return CUiDlg::PreTranslateMessage(pMsg);

}