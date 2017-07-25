// KeyAssignStyleDlg.cpp : implementation file

#include "stdafx.h"
#include "AORUS.h"
#include "KeyAssignStyleDlg.h"
#include "AORUSDlg.h"


int CKeyAssignStyleDlg::s_nWords = LKEY_QTY;
LANG_WORD CKeyAssignStyleDlg::s_Words[48] = 
{
	LANG_WORD(LKEY_DEFAULT, _T("默认"), __T("默認"), _T("DEFAULT")),
	LANG_WORD(LKEY_MUTILKEY,		_T("組合键"), _T("組合鍵"), _T("MUTIL-KEY RECORD")),
	LANG_WORD(LKEY_TXTINPUT,		_T("文本"), _T("文本"), _T("TEXT INPUT")),
	LANG_WORD(LKEY_MOUSEACTION,		_T("鼠标"), _T("滑鼠"), _T("MOUSE ACTION")),
	LANG_WORD(LKEY_FNKEY,			_T("功能键"), _T("功能鍵"), _T("FUNCTION KEY")),
	LANG_WORD(LKEY_MEDIAPLAYER,		_T("多媒体"), _T("多媒體"), _T("MEDIA PLAYER")),
	LANG_WORD(LKEY_HOTKEY,			_T("快捷方式"), _T("熱鍵"), _T("HOT KEY")),
	LANG_WORD(LKEY_MACRO, _T("聚集"), _T("聚集"), _T("MACRO")),

	LANG_WORD(LKEY_ALT_F4,			_T("关闭窗口"), _T("關閉窗口"), _T("Close the Window")),
// 	LANG_WORD(LKEY_ALT_SPACE_X,		_T("最大化窗口"), _T("最大化窗口"), _T("Maximize the Window")),
// 	LANG_WORD(LKEY_ALT_SPACE_N,		_T("最小化窗口"), _T("最小化窗口"), _T("Minimize the Window")),
	LANG_WORD(LKEY_WIN_D,			_T("显示桌面"), _T("顯示桌面"), _T("Return to Desktop")),
	LANG_WORD(LKEY_CTRL_TAB,		_T("切换下个窗口"), _T("切換下?窗口"), _T("Next Tab")),
	LANG_WORD(LKEY_CTRL_SHIFT_TAB,	_T("切换上个窗口"), _T("切換上?窗口"), _T("Previous Tab")),
// 	LANG_WORD(LKEY_CTRL_WHEEL_UP,	_T("放大"), _T("放大"), _T("Zoom In")),
// 	LANG_WORD(LKEY_CTRL_WHEEL_DOWN, _T("缩小"), _T("縮小"), _T("Zoom Out")),
	LANG_WORD(LKEY_CTRL_0,			_T("缩放恢复"), _T("縮放恢復"), _T("Restore Default Zoom")),
	LANG_WORD(LKEY_CTRL_C,			_T("拷贝"), _T("拷?"), _T("Copy")),
	LANG_WORD(LKEY_CTRL_V,			_T("粘贴"), _T("粘貼"), _T("Paste")),
	LANG_WORD(LKEY_CTRL_X,			_T("剪切"), _T("剪切"), _T("Cut")),
	LANG_WORD(LKEY_CTRL_Z,			_T("取消操作"), _T("取消操作"), _T("Undo")),
	LANG_WORD(LKEY_CTRL_Y,			_T("重复操作"), _T("重複操作"), _T("Redo")),

	LANG_WORD(LKEY_MOUSE_LFET,		_T("左键"), _T("左鍵"), _T("LEFT BUTTON")),
	LANG_WORD(LKEY_MOUSE_RIGHT,		_T("右键"), _T("右鍵"), _T("RIGHT BUTTON")),
	LANG_WORD(LKEY_MOUSE_MIDDLE,	_T("滚轮中键"), _T("滾?中鍵"), _T("MIDDLE BUTTON")),
	LANG_WORD(LKEY_MOUSE_PREPAGE,	_T("往前一页"), _T("往前一?"), _T("PREVIOUS PAGE")),
	LANG_WORD(LKEY_MOUSE_NEXTPAGE,	_T("往后一页"), _T("往後一?"), _T("NEXT PAGE")),
	LANG_WORD(LKEY_MOUSE_WHEELUP,	_T("向上滚动"), _T("向上滾動"), _T("WHEEL UP")),
	LANG_WORD(LKEY_MOUSE_WHEELDOWN, _T("向下滚动"), _T("向下滾動"), _T("WHEEL DOWN")),
};

int CKeyAssignStyleDlg::s_nHotKeys  = 10;
CString CKeyAssignStyleDlg::s_HotKeysName[24] = 
{
	_T("Alt + F4"),
// 	_T("Alt + Space + X"),
// 	_T("Alt + Space + N"),
	_T("Win + D"),
	_T("Ctrl + Tab"),
	_T("Ctrl + Shift + Tab"),
// 	_T("Ctrl + Wheel Up"),
// 	_T("Ctrl + Wheel Down"),
	_T("Ctrl + 0"),
	_T("Ctrl + C"),
	_T("Ctrl + V"),
	_T("Ctrl + X"),
	_T("Ctrl + Z"),
	_T("Ctrl + Y"),
};
int CKeyAssignStyleDlg::s_HotKeys[24] = 
{
	LKEY_ALT_F4,
	LKEY_WIN_D,
	LKEY_CTRL_TAB,
	LKEY_CTRL_SHIFT_TAB,
	LKEY_CTRL_0,
	LKEY_CTRL_C,
	LKEY_CTRL_V,
	LKEY_CTRL_X,
	LKEY_CTRL_Z,
	LKEY_CTRL_Y,
};

int CKeyAssignStyleDlg::s_nMouses = 7;
int CKeyAssignStyleDlg::s_Mouses[12] = 
{
	LKEY_MOUSE_LFET,
	LKEY_MOUSE_RIGHT,
	LKEY_MOUSE_MIDDLE,
	LKEY_MOUSE_PREPAGE,
	LKEY_MOUSE_NEXTPAGE,
	LKEY_MOUSE_WHEELUP,
	LKEY_MOUSE_WHEELDOWN,
};


// CKeyAssignStyleDlg dialog

IMPLEMENT_DYNAMIC(CKeyAssignStyleDlg, CUiDlg)

CKeyAssignStyleDlg::CKeyAssignStyleDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CKeyAssignStyleDlg::IDD, pParent)
{
}

CKeyAssignStyleDlg::~CKeyAssignStyleDlg()
{
}

void CKeyAssignStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BOOL CKeyAssignStyleDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	CUiDlg::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	Ui();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CKeyAssignStyleDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
	ON_MESSAGE(WM_UI_PANEL_SELCHANGE, OnUiPanelSelChanged)
	ON_MESSAGE(WM_NEW_PAINT, OnNewPaint)
//	ON_MESSAGE(WM_SHOWWINDOW, OnShowWindow)
	ON_WM_NCHITTEST()
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
	ON_WM_SHOWWINDOW()
	
	
END_MESSAGE_MAP()


// CKeyAssignStyleDlg message handlers

void CKeyAssignStyleDlg::Ui()
{
	UiMain();
}

void CKeyAssignStyleDlg::UiMain()
{
	SetBkBitmap(IDB_KBLEDSTYLE_BG, 0xff, CLR_TRPT); 

	UI_STATIC stc[] =
	{
		UI_STATIC(this, STC_KEYASSIGN_DEFAULT, CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_MOUSEANDMACRO, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_MUTILKEY,		CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_MULTIKEY, CLR_TRPT),
		UI_STATIC(this, STC_KEYASSIGN_TXTINPUT,		CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_INPUTTEXT, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_MOUSEACTION,	CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_MOUSEANDMACRO, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_FNKEY,		CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_FNKEY, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_MEDIAPLAYER,	CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_MIDIAPLAYER, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_HOTKEY,		CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_INPUTTEXT, CLR_NONE),
		UI_STATIC(this, STC_KEYASSIGN_MACRO, CRect(4, 76, 0, 0), _T(""), IDB_KEYASSIGN_MOUSEANDMACRO, CLR_NONE),
		UI_STATIC(&m_stc[STC_KEYASSIGN_TXTINPUT], STC_KEYASSIGN_TXTINPUTDESC, CRect(39, 53, 254, 198), _T(""), NULL, CLR_NONE),
		UI_STATIC(&m_stc[STC_KEYASSIGN_MOUSEACTION], STC_KEYASSIGN_MOUSEACTIONDESC, CRect(39, 53, 254, 198), _T(""), NULL, CLR_NONE),
		UI_STATIC(&m_stc[STC_KEYASSIGN_HOTKEY], STC_KEYASSIGN_HOTKEYDESC, CRect(39, 53, 254, 198), _T(""), NULL, CLR_NONE),
		UI_STATIC(&m_stc[STC_KEYASSIGN_MACRO], STC_KEYASSIGN_MACRODESC, CRect(39, 53, 254, 198), _T(""), NULL, CLR_NONE),
  		UI_STATIC(&m_stc[STC_KEYASSIGN_MUTILKEY], STC_KEYASSIGN_MUTILKEYONE,		CRect(89,  37, 205,  56), _T(""), NULL, CLR_TRPT),
  		UI_STATIC(&m_stc[STC_KEYASSIGN_MUTILKEY], STC_KEYASSIGN_MUTILKEYTWO,		CRect(89,  95, 205, 114), _T(""), NULL, CLR_TRPT),
  		UI_STATIC(&m_stc[STC_KEYASSIGN_MUTILKEY], STC_KEYASSIGN_MUTILKEYTHREE,		CRect(89, 153, 205, 172), _T(""), NULL, CLR_TRPT),
	};
	for (int i = STC_KEYASSIGN_DEFAULT;i < STC_KEYASSIGN_NUM; i++)
	{
		m_stc[i].CreateStatic(stc[i - (int)STC_KEYASSIGN_DEFAULT]);
		m_stc[i].ModifyCtrlStyle(ST_VCENTER, ST_LEFT);
		m_stc[i].SetFont(Font(11), CLR_WHITE);
	}

//  	m_stc[STC_KEYASSIGN_MUTILKEYONE].ShowWindow(SW_SHOW);
//  	m_stc[STC_KEYASSIGN_MUTILKEYTWO].ShowWindow(SW_SHOW);
//  	m_stc[STC_KEYASSIGN_MUTILKEYTHREE].ShowWindow(SW_SHOW);
	m_stc[STC_KEYASSIGN_MUTILKEYONE].SetBkColor(CLR_MAIN);
 	m_stc[STC_KEYASSIGN_MUTILKEYTWO].SetBkColor(CLR_MAIN);
 	m_stc[STC_KEYASSIGN_MUTILKEYTHREE].SetBkColor(CLR_MAIN);

	m_stc[STC_KEYASSIGN_DEFAULT].ShowWindow(SW_SHOW);
	m_stc[STC_KEYASSIGN_MUTILKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_TXTINPUT].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MOUSEACTION].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_FNKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MEDIAPLAYER].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_HOTKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MACRO].ShowWindow(SW_HIDE);

	UI_BTN btn[] = 
	{
		UI_BTN(this, BTN_KEYASSIGN_CLOSE, CRect(270, 10, 0,  0), &UIBTN_IMAGE(IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, 0, 0, 0, 0, CLR_TRPT)),
	};

	for(int i = BTN_KEYASSIGN_CLOSE; i < BTN_KEYASSIGN_NUM; i++)
	{
		m_btn[i].CreateButton(btn[i - (int)BTN_KEYASSIGN_CLOSE]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	m_panel[PANEL_KEYASSIGN_FNKEY].Create(&m_stc[STC_KEYASSIGN_FNKEY], PANEL_KEYASSIGN_FNKEY, CRect(30, 40, 265, 180));  
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(1, CRect(  5,  5, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_MAIL_OFF, IDB_FUNKEY_MAIL_OFF, IDB_FUNKEY_MAIL_ON, IDB_FUNKEY_MAIL_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(2, CRect( 87,  5, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_WEB_OFF, IDB_FUNKEY_WEB_OFF, IDB_FUNKEY_WEB_ON, IDB_FUNKEY_WEB_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(3, CRect(169,  5, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_MEDIAPLAY_OFF, IDB_FUNKEY_MEDIAPLAY_OFF, IDB_FUNKEY_MEDIAPLAY_ON, IDB_FUNKEY_MEDIAPLAY_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(4, CRect(  5, 87, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_SOUND_OFF, IDB_FUNKEY_SOUND_OFF, IDB_FUNKEY_SOUND_ON, IDB_FUNKEY_SOUND_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(5, CRect( 87, 87, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_MYPC_OFF, IDB_FUNKEY_MYPC_OFF, IDB_FUNKEY_MYPC_ON, IDB_FUNKEY_MYPC_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].AddItem(&UIPC_ITEM(6, CRect(169, 87, 0, 0), &UIPC_IMAGE(IDB_FUNKEY_CACULATOR_OFF, IDB_FUNKEY_CACULATOR_OFF, IDB_FUNKEY_CACULATOR_ON, IDB_FUNKEY_CACULATOR_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_FNKEY].SetCursor(IDC_CUR_HAND);
	m_panel[PANEL_KEYASSIGN_MEDIA].Create(&m_stc[STC_KEYASSIGN_MEDIAPLAYER], PANEL_KEYASSIGN_MEDIA, CRect(30, 40, 265, 180));  
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(1, CRect(  5,  5, 0, 0), &UIPC_IMAGE(IDB_MEDIA_STOP_OFF, IDB_MEDIA_STOP_OFF, IDB_MEDIA_STOP_ON, IDB_MEDIA_STOP_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(2, CRect( 87,  5, 0, 0), &UIPC_IMAGE(IDB_MEDIA_PLAY_OFF, IDB_MEDIA_PLAY_OFF, IDB_MEDIA_PLAY_ON, IDB_MEDIA_PLAY_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(3, CRect(169,  5, 0, 0), &UIPC_IMAGE(IDB_MEDIA_PREVIOUS_OFF, IDB_MEDIA_PREVIOUS_OFF, IDB_MEDIA_PREVIOUS_ON, IDB_MEDIA_PREVIOUS_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(4, CRect(  5, 87, 0, 0), &UIPC_IMAGE(IDB_MEDIA_NEXT_OFF, IDB_MEDIA_NEXT_OFF, IDB_MEDIA_NEXT_ON, IDB_MEDIA_NEXT_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(5, CRect( 87, 87, 0, 0), &UIPC_IMAGE(IDB_MEDIA_VOLUP_OFF, IDB_MEDIA_VOLUP_OFF, IDB_MEDIA_VOLUP_ON, IDB_MEDIA_VOLUP_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].AddItem(&UIPC_ITEM(6, CRect(169, 87, 0, 0), &UIPC_IMAGE(IDB_MEDIA_VOLDOWN_OFF, IDB_MEDIA_VOLDOWN_OFF, IDB_MEDIA_VOLDOWN_ON, IDB_MEDIA_VOLDOWN_OFF, CLR_TRPT)));
	m_panel[PANEL_KEYASSIGN_MEDIA].SetCursor(IDC_CUR_HAND);


	
	m_combobox[COMBOX_KEYASSIGN_STYLE].Create(CRect(7, 55, 0, 0), this, COMBOX_KEYASSIGN_STYLE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].SetCursor(IDC_CUR_HAND); 
	m_combobox[COMBOX_KEYASSIGN_STYLE].SetArrowWidth(20);
	m_combobox[COMBOX_KEYASSIGN_STYLE].GetDropList()->SetFont(Font(11));
	m_combobox[COMBOX_KEYASSIGN_STYLE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KEYASSIGN_STYLE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KEYASSIGN_STYLE].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_DEFAULT), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_MUTILKEY), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_TXTINPUT), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_MOUSEACTION), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_FNKEY), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_MEDIAPLAYER), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_HOTKEY), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_MACRO), 0, CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_STYLE].SetCurSel(0);

	m_combobox[COMBOX_KEYASSIGN_MACRO].Create(CRect(3, 15, 0, 0), &m_stc[STC_KEYASSIGN_MACRO], COMBOX_KEYASSIGN_MACRO);
	m_combobox[COMBOX_KEYASSIGN_MACRO].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
	m_combobox[COMBOX_KEYASSIGN_MACRO].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_MACRO].SetCursor(IDC_CUR_HAND); 
	m_combobox[COMBOX_KEYASSIGN_MACRO].SetArrowWidth(20);
	m_combobox[COMBOX_KEYASSIGN_MACRO].GetDropList()->SetFont(Font(11));
	m_combobox[COMBOX_KEYASSIGN_MACRO].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KEYASSIGN_MACRO].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KEYASSIGN_MACRO].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);

	
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].Create(CRect(3, 15, 0, 0), &m_stc[STC_KEYASSIGN_HOTKEY], COMBOX_KEYASSIGN_HOTKEY);
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetCursor(IDC_CUR_HAND); 
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetArrowWidth(20);
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].GetDropList()->SetFont(Font(11));
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);
	for (int i = 0; i < s_nHotKeys; i++)
	{
		m_combobox[COMBOX_KEYASSIGN_HOTKEY].AddString(s_HotKeysName[i], 0, CLR_WHITE);
	}
	m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetCurSel(0);
	m_stc[STC_KEYASSIGN_HOTKEYDESC].SetCaption(CLangX::Get(s_Words, s_nWords, s_HotKeys[0]));

	m_combobox[COMBOX_KEYASSIGN_MOUSE].Create(CRect(3, 15, 0, 0), &m_stc[STC_KEYASSIGN_MOUSEACTION], COMBOX_KEYASSIGN_MOUSE);
	m_combobox[COMBOX_KEYASSIGN_MOUSE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
	m_combobox[COMBOX_KEYASSIGN_MOUSE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KEYASSIGN_MOUSE].SetCursor(IDC_CUR_HAND); 
	m_combobox[COMBOX_KEYASSIGN_MOUSE].SetArrowWidth(20);
	m_combobox[COMBOX_KEYASSIGN_MOUSE].GetDropList()->SetFont(Font(11));
	m_combobox[COMBOX_KEYASSIGN_MOUSE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KEYASSIGN_MOUSE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KEYASSIGN_MOUSE].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);
	for (int i = 0; i < s_nMouses; i++)
	{
		m_combobox[COMBOX_KEYASSIGN_MOUSE].AddString(CLangX::Get(s_Words, s_nWords, s_Mouses[i]), 0, CLR_WHITE);
	}
	m_combobox[COMBOX_KEYASSIGN_MOUSE].SetCurSel(0);
//	m_stc[STC_KEYASSIGN_MOUSEACTIONDESC].SetCaption(CLangX::Get(s_Words, s_nWords, s_Mouses[0]));

// 	m_HKey1.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(89,  37, 205,  56), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);
// 	m_HKey1.SetBkColor(CLR_DARK);
// 	m_HKey1.SetFont(Font(11), CLR_WHITE);
// 	m_HKey2.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(89,  95, 205, 114), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);
// 	m_HKey2.SetBkColor(CLR_DARK);
// 	m_HKey2.SetFont(Font(11), CLR_WHITE);
// 	m_HKey3.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(89, 153, 205, 172), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);
// 	m_HKey3.SetBkColor(CLR_DARK);
// 	m_HKey3.SetFont(Font(11), CLR_WHITE);
//	m_HKey1.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(89+198-150,  37-10, 205+198-250,  56-17-10), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);
	m_HKey1.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(89,  27, 90,  28), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);
	m_HKey1.SetBkColor(CLR_DARK);
	m_HKey1.SetFont(Font(5), CLR_DARK);
	




	//m_HKey1.ShowWindow(SW_HIDE);

	
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYONE].Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY, CRect(89,  37+30, 205,  56+30), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);//ES_WANTRETURN
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYONE].SetFont(Font(11), CLR_WHITE);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYONE].SetBkColor(CLR_DARK);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYONE].AutoAdjustCaret(false);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTWO].Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY, CRect(89,  95+25, 205, 114+25), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);//ES_WANTRETURN
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTWO].SetFont(Font(11), CLR_WHITE);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTWO].SetBkColor(CLR_DARK);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTWO].AutoAdjustCaret(false);
// 		m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTHREE].Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY, CRect(89, 153+20, 205, 172+20), &m_stc[STC_KEYASSIGN_MUTILKEY], 0);//ES_WANTRETURN
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTHREE].SetFont(Font(11), CLR_WHITE);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTHREE].SetBkColor(CLR_DARK);
// 	m_EditTxtInput[EDIT_KEYASSIGN_MUTILKEYTHREE].AutoAdjustCaret(false);




	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE, CRect(38, 52, 254, 199), &m_stc[STC_KEYASSIGN_TXTINPUT], 0);//ES_WANTRETURN
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].SetFont(Font(11), CLR_WHITE);
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].SetBkColor(CLR_DARK);
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].AutoAdjustCaret(false);


}




LRESULT CKeyAssignStyleDlg::OnNcHitTest(CPoint point)
{
	UINT uRes = (UINT)CUiDlg::OnNcHitTest(point);
	if(uRes == HTCLIENT) 
	{
		uRes = HTCAPTION;
	}

	return uRes;
}

void CKeyAssignStyleDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	pParent->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	CUiDlg::OnActivate(nState, pWndOther, bMinimized);
}

void CKeyAssignStyleDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CUiDlg::OnMoving(fwSide, pRect);

	CRect rcCli;
	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	pParent->GetClientRect(rcCli);
	int nWidth = rcCli.Width();
	GetClientRect(rcCli);
	ClientToScreen(&rcCli);

	pParent->OnFollowMove(4, pParent->OnFit(rcCli, 0 - nWidth, -79));
}

void CKeyAssignStyleDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CKeyAssignStyleDlg::OnFit(CRect rcParentCli)
{
 	int nX = rcParentCli.left + rcParentCli.Width();
 	int nY = rcParentCli.top + 78;
 
 	SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
 	SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);

}


LRESULT CKeyAssignStyleDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_KEYASSIGN_CLOSE: OnClose(); break;
	}

	return 1;
}

LRESULT CKeyAssignStyleDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nCurSel = (int)lParam; 
	switch(wParam)
	{
	case COMBOX_KEYASSIGN_STYLE:
	SwitchAssignStyle(nCurSel);
// 		m_stc[STC_KEYASSIGN_MUTILKEY].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_TXTINPUT].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_MOUSEACTION].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_FNKEY].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_MEDIAPLAYER].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_HOTKEY].ShowWindow(SW_HIDE);
// 		m_stc[STC_KEYASSIGN_MACRO].ShowWindow(SW_HIDE);
// 		switch(nCurSel)
// 		{
// 		case 0: m_stc[STC_KEYASSIGN_MUTILKEY].ShowWindow(SW_SHOW); break;
// 		case 1: m_stc[STC_KEYASSIGN_TXTINPUT].ShowWindow(SW_SHOW); break;
// 		case 2: m_stc[STC_KEYASSIGN_MOUSEACTION].ShowWindow(SW_SHOW); break;
// 		case 3: m_stc[STC_KEYASSIGN_FNKEY].ShowWindow(SW_SHOW); break;
// 		case 4: m_stc[STC_KEYASSIGN_MEDIAPLAYER].ShowWindow(SW_SHOW); break;
// 		case 5: m_stc[STC_KEYASSIGN_HOTKEY].ShowWindow(SW_SHOW); break;
// 		case 6:m_stc[STC_KEYASSIGN_MACRO].ShowWindow(SW_SHOW); break;
// 		}
		break;
	case COMBOX_KEYASSIGN_HOTKEY:
		m_stc[STC_KEYASSIGN_HOTKEYDESC].SetCaption(CLangX::Get(s_Words, s_nWords, s_HotKeys[nCurSel]));
		break;
	case COMBOX_KEYASSIGN_MOUSE: 
		//MOUSE ACTION不顯示DESCRIPTION
	//	m_stc[STC_KEYASSIGN_MOUSEACTIONDESC].SetCaption(CLangX::Get(s_Words, s_nWords, s_Mouses[nCurSel]));
		break;

	case COMBOX_KEYASSIGN_MACRO: 
		
		break;
	}


	return 1;
}

LRESULT CKeyAssignStyleDlg::OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		m_nFunctionKeySel = lParam;
		break;
	case 1:
		m_nMediaPlayerSel = lParam;
		break;
	}
	
	return 0;
}
void CKeyAssignStyleDlg::InitState()
{
	int nCurSel = -1;

	if (m_combobox[COMBOX_KEYASSIGN_MACRO].GetCurSel() >= 0)
	{
		int nIndex = m_combobox[COMBOX_KEYASSIGN_MACRO].GetCurSel();
		nCurSel = m_cmbMarco[nIndex].nIndex; // 獲取原本設定Index
	}

	m_combobox[COMBOX_KEYASSIGN_MACRO].ResetContent(); // 清除掉內容
	GVORDER_MACROS_ATTR lstmacros[KB_MARCO_COUNT];
	CKbLedCtrl::GetMarcoList(lstmacros, KB_MARCO_COUNT); // 取得內存中的marco
	int index = 0;
	for (int i = 0; i < KB_MARCO_COUNT; i++)
	{
		GVORDER_MACROS_ATTR marco = lstmacros[i];
		if (MacroIsValid(marco))
		{
			m_cmbMarco[index].nType = MARCO_LOAD;
			m_cmbMarco[index].nIndex = i;
			m_combobox[COMBOX_KEYASSIGN_MACRO].AddString(marco.szName, 0, CLR_MAIN);
			if(i == nCurSel) m_combobox[COMBOX_KEYASSIGN_MACRO].SetCurSel(index);
			index++;
		}
	}
	m_combobox[COMBOX_KEYASSIGN_MACRO].SetWindowText(_T(""));
	m_combobox[COMBOX_KEYASSIGN_MACRO].Invalidate(FALSE);
//	SetProfile(nProfile);
}


bool CKeyAssignStyleDlg::MacroIsValid(GVORDER_MACROS_ATTR macro)
{
	return macro.nIcon >= 1 && macro.nIcon <= KB_MARCO_COUNT && (0 <= macro.RunType && macro.RunType <= 2);
}

bool CKeyAssignStyleDlg::GetMutilKey(GVORDER_KEYFUN &keyfun)
{
	CString name = m_HKey1.GetHotKeyName();
	WORD vk;
	WORD modifiers;
	m_HKey1.GetHotKey(vk, modifiers);
	if (modifiers == 0)
	{
		CString s;
		s.Format( _T("%s is not a valid multi-key"), name);
		AfxMessageBox(s);
		return false;
	}
	
	keyfun.fnType = GVORDER_FUN_KEYBOARD;
	keyfun.value.keyboard.keyCode = vk;
	keyfun.value.keyboard.keyModifier = modifiers;

	return true;
}

CString CKeyAssignStyleDlg::GetInputStr()
{
	CString sInput = _T("");
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].GetWindowText(sInput);
	return sInput;
}

void CKeyAssignStyleDlg::SetOutputStr(CString str)
{
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].SetWindowText(_T(""));
	m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].SetWindowText(str);
}

void CKeyAssignStyleDlg::SwitchAssignStyle(int Index)
{
	m_stc[STC_KEYASSIGN_DEFAULT].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MUTILKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_TXTINPUT].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MOUSEACTION].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_FNKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MEDIAPLAYER].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_HOTKEY].ShowWindow(SW_HIDE);
	m_stc[STC_KEYASSIGN_MACRO].ShowWindow(SW_HIDE);
	UpdateWindow();

	switch(Index)
	{
		case 0: m_stc[STC_KEYASSIGN_DEFAULT].ShowWindow(SW_SHOW); break;
		case 1: m_stc[STC_KEYASSIGN_MUTILKEY].ShowWindow(SW_SHOW); m_HKey1.SetFocus();break;
		case 2: m_stc[STC_KEYASSIGN_TXTINPUT].ShowWindow(SW_SHOW); break;
		case 3: m_stc[STC_KEYASSIGN_MOUSEACTION].ShowWindow(SW_SHOW); break;
		case 4: m_stc[STC_KEYASSIGN_FNKEY].ShowWindow(SW_SHOW); break;
		case 5: m_stc[STC_KEYASSIGN_MEDIAPLAYER].ShowWindow(SW_SHOW); break;
		case 6: m_stc[STC_KEYASSIGN_HOTKEY].ShowWindow(SW_SHOW); break;
		case 7:m_stc[STC_KEYASSIGN_MACRO].ShowWindow(SW_SHOW); break;
	}
}

LRESULT CKeyAssignStyleDlg::OnNewPaint(WPARAM wParam, LPARAM lParam)
{
	CString name = m_HKey1.GetHotKeyName();
	CString strOne = _T("");
	CString strTwo = _T("");
	CString strThree = _T("");

	if (name.Find(_T("+")) != -1)
	{
		strOne = name.Mid(0, name.Find(_T("+"))-1);
		name = name.Mid( name.Find(_T("+"))+1);
		if (name.Find(_T("+")) != -1)
		{
			strTwo = name.Mid(0, name.Find(_T("+"))-1);
			name = name.Mid( name.Find(_T("+"))+1);
			strThree = name;
		}
		else
		{
			strTwo = name;
		}
	}
	else
	{
		strOne = name;
	}
	m_stc[STC_KEYASSIGN_MUTILKEYONE].SetCaption(strOne);
	m_stc[STC_KEYASSIGN_MUTILKEYTWO].SetCaption(strTwo);
	m_stc[STC_KEYASSIGN_MUTILKEYTHREE].SetCaption(strThree);

	return 1;
}

void CKeyAssignStyleDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if (bShow)
		m_HKey1.SetFocus();
	CWnd::OnShowWindow(bShow, nStatus);
}