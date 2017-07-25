// MouseButtonDlg.cpp : implementation file

#include "stdafx.h"
#include "AORUS.h"
#include "MouseButtonDlg.h"
#include "AORUSDlg.h"



#include ".\inc\mouse\AM300Cmd.h"
#include ".\inc\mouse\AM300Ctrl.h"
#include ".\inc\mouse\CmdFormat.h"
#include "LedDlg.h"


CLedDlg m_ledDlg;

//Terry 2017/07/09


#define HOT_KEY_ID 10000

#define LKEY_MOUSE_LFET 0
#define LKEY_MOUSE_MIDDLE 1
#define LKEY_MOUSE_RIGHT 2
#define LKEY_MOUSE_DPIINC 3
#define LKEY_MOUSE_DPIDEC 4
#define LKEY_MOUSE_FORWARD 5
#define LKEY_MOUSE_BACKWARD 6

#define LKEY_MOUSE_LFET_CLICK			7
#define LKEY_MOUSE_RIGHT_CLICK		8
#define LKEY_MOUSE_MIDDLE_CLICK	9
#define LKEY_MOUSE_PREPAGE_CLICK		10
#define LKEY_MOUSE_NEXTPAGE_CLICK		11
#define LKEY_MOUSE_WHEELUP_CLICK		12
#define LKEY_MOUSE_WHEELDOWN_CLICK	13

#define LKEY_ALT_F4				14
#define LKEY_WIN_D				15
#define LKEY_CTRL_TAB			16
#define LKEY_CTRL_SHIFT_TAB		17
#define LKEY_CTRL_0				18
#define LKEY_CTRL_C				19
#define LKEY_CTRL_V				20
#define LKEY_CTRL_X				21
#define LKEY_CTRL_Z				22
#define LKEY_CTRL_Y				23


#define LANG_CALCULATOR		24
#define LANG_DOUBLE_CLICK	25
#define LANG_RESTROE			26
#define LANG_CUT					27
#define LANG_COPY					28
#define LANG_PASTE				29
#define LANG_NEW					30
#define LANG_CLOSE				31
#define LANG_OPEN					32
#define LANG_MINIMIZE			33
#define LANG_MAXIMIZE			34
#define LANG_ZOOM_OUT		35
#define LANG_ZOOM_IN			36
#define LANG_EXIT_PROGRAM	37
#define LANG_VOLUME_UP		38
#define LANG_VOLUME_DOWN	39
#define LANG_MUTE_ON_OFF	40
#define LANG_MAGNIFIER		41
#define LANG_DESKTOP			42
#define LANG_WEB_BROWSER	43
#define LANG_IE_FAVORITES	44
#define LANG_PREVIOUS_WINDOW	45
#define LANG_E_MAIL				46
#define LANG_PLAY_PAUSE		47
#define LANG_PREVIOUS			48
#define LANG_NEXT					49
#define LANG_MEDIA_PLAYER	50
#define LANG_MODE_KEY		51
#define LANG_DPI_LOOP			52

#define LKEY_QTY				   53

int CMouseButtonDlg::s_nWords = LKEY_QTY;
LANG_WORD CMouseButtonDlg::s_Words[48] = 
{
	LANG_WORD(LKEY_MOUSE_LFET,		_T("LEFT BUTTON"), _T("LEFT BUTTON"), _T("LEFT BUTTON")),
	LANG_WORD(LKEY_MOUSE_MIDDLE,	_T("MIDDLE BUTTON"), _T("MIDDLE BUTTON"), _T("MIDDLE BUTTON")),
	LANG_WORD(LKEY_MOUSE_RIGHT,		_T("RIGHT BUTTON"), _T("RIGHT BUTTON"), _T("RIGHT BUTTON")),
	LANG_WORD(LKEY_MOUSE_DPIINC,		_T("DPI+"), _T("DPI+"), _T("DPI+")),
	LANG_WORD(LKEY_MOUSE_DPIDEC,		_T("DPI-"), _T("DPI-"), _T("DPI-")),
	LANG_WORD(LKEY_MOUSE_FORWARD,		_T("FOWARD"), _T("FOWARD"), _T("FOWARD")),
	LANG_WORD(LKEY_MOUSE_BACKWARD,		_T("BACKWARD"), _T("BACKWARD"), _T("BACKWARD")),

	LANG_WORD(LKEY_MOUSE_LFET_CLICK,		_T("左键"), _T("左鍵"), _T("LEFT BUTTON")),
	LANG_WORD(LKEY_MOUSE_RIGHT_CLICK,		_T("右键"), _T("右鍵"), _T("RIGHT BUTTON")),
	LANG_WORD(LKEY_MOUSE_MIDDLE_CLICK,	_T("滚轮中键"), _T("滾輪中鍵"), _T("MIDDLE BUTTON")),
	LANG_WORD(LKEY_MOUSE_PREPAGE_CLICK,	_T("往前一页"), _T("往前一頁"), _T("PREVIOUS PAGE")),
	LANG_WORD(LKEY_MOUSE_NEXTPAGE_CLICK,	_T("往后一页"), _T("往後一頁"), _T("NEXT PAGE")),
	LANG_WORD(LKEY_MOUSE_WHEELUP_CLICK,	_T("向上滚动"), _T("向上滾動"), _T("WHEEL UP")),
	LANG_WORD(LKEY_MOUSE_WHEELDOWN_CLICK, _T("向下滚动"), _T("向下滾動"), _T("WHEEL DOWN")),

	LANG_WORD(LKEY_ALT_F4,			_T("关闭窗口"), _T("關閉窗口"), _T("Close the Window")),
	LANG_WORD(LKEY_WIN_D,			_T("显示桌面"), _T("顯示桌面"), _T("Return to Desktop")),
	LANG_WORD(LKEY_CTRL_TAB,		_T("切换下个窗口"), _T("切換下個窗口"), _T("Next Tab")),
	LANG_WORD(LKEY_CTRL_SHIFT_TAB,	_T("切换上个窗口"), _T("切換上個窗口"), _T("Previous Tab")),
	LANG_WORD(LKEY_CTRL_0,			_T("缩放恢复"), _T("縮放恢復"), _T("Restore Default Zoom")),
	LANG_WORD(LKEY_CTRL_C,			_T("拷贝"), _T("拷貝"), _T("Copy")),
	LANG_WORD(LKEY_CTRL_V,			_T("粘贴"), _T("粘貼"), _T("Paste")),
	LANG_WORD(LKEY_CTRL_X,			_T("剪切"), _T("剪切"), _T("Cut")),
	LANG_WORD(LKEY_CTRL_Z,			_T("取消操作"), _T("取消操作"), _T("Undo")),
	LANG_WORD(LKEY_CTRL_Y,			_T("重复操作"), _T("重複操作"), _T("Redo")),
};

// int CMouseButtonDlg::s_nMouses = 7;
// int CMouseButtonDlg::s_Mouses[12] = 
// {
// 	LKEY_MOUSE_LFET,
// 	LKEY_MOUSE_RIGHT,
// 	LKEY_MOUSE_MIDDLE,
// 	LKEY_MOUSE_PREPAGE,
// 	LKEY_MOUSE_NEXTPAGE,
// 	LKEY_MOUSE_WHEELUP,
// 	LKEY_MOUSE_WHEELDOWN,
// };

int CMouseButtonDlg::s_nMultiMedia  = 29;
CString CMouseButtonDlg::s_sMultiMedia[29] = 
{
	_T("CALCULATOR"),
	_T("DOUBLE CLICK"),
	_T("RESTROE(CTRL+Z)"),
	_T("CUT(CTRL+X)"),
	_T("COPY(CTRL+C)"),
	_T("PASTE(CTRL+V)"),
	_T("NEW(CTRL+N)"),
	_T("CLOSE(CTRL+W)"),
	_T("OPEN(CTRL+O)"),
	_T("MINIMIZE"),
	_T("MAXIMIZE"),
	_T("ZOOM OUT"),
	_T("ZOOM IN"),
	_T("EXIT PROGRAM"),
	_T("VOLUME UP"),
	_T("VOLUME DOWN"),
	_T("MUTE ON/OFF"),
	_T("MAGNIFIER"),
	_T("DESKTOP"),
	_T("WEB BROWSER"),
	_T("IE FAVORITES"),
	_T("PREVIOUS WINDOW"),
	_T("E-MAIL"),
	_T("PLAY/PAUSE"),
	_T("PREVIOUS"),
	_T("NEXT"),
	_T("MEDIA PLAYER"),
	_T("Mode Key"),
	_T("DPI Loop"),
};
int CMouseButtonDlg::s_MultiMedia[29] = 
{
 	LANG_CALCULATOR,
	LANG_DOUBLE_CLICK,
	LANG_RESTROE,
	LANG_CUT,
	LANG_COPY,
	LANG_PASTE,
	LANG_NEW,
	LANG_CLOSE,
	LANG_OPEN,
	LANG_MINIMIZE,
	LANG_MAXIMIZE,
	LANG_ZOOM_OUT,
	LANG_ZOOM_IN,
	LANG_EXIT_PROGRAM,
	LANG_VOLUME_UP,
	LANG_VOLUME_DOWN,
	LANG_MUTE_ON_OFF,
	LANG_MAGNIFIER,
	LANG_DESKTOP,
	LANG_WEB_BROWSER,
	LANG_IE_FAVORITES,
	LANG_PREVIOUS_WINDOW,
	LANG_E_MAIL,
	LANG_PLAY_PAUSE,
	LANG_PREVIOUS,
	LANG_NEXT,
	LANG_MEDIA_PLAYER,
	LANG_MODE_KEY,
	LANG_DPI_LOOP,
};

int CMouseButtonDlg::s_nMouseKey = 9;
CString CMouseButtonDlg::s_MouseKey[20] = {
	_T("LEFT CLICK"),
	_T("RIGHT CLICK"),
	_T("MIDDLE CLICK"),
	_T("Browser Forward"),
	_T("Browser Backward"),
	_T("DPI+"),
	_T("DPI-"),
	_T("FORWARD SCROLL"),
	_T("BACKWARD SCROLL"),
};

int CMouseButtonDlg::s_nKeyMapping  = 66;
CString CMouseButtonDlg::s_KeyMapping[105] = {
	_T("0"), _T("1"),  _T("2"),  _T("3"),  _T("4"),  _T("5"),  _T("6"),  _T("7"),  _T("8"),  _T("9"),  
	_T("A"),  _T("B"),  _T("C"),  _T("D"),  _T("E"),  _T("F"),  _T("G"),  
	_T("H"),  _T("I"),  _T("J"),  _T("K"),  _T("L"),  _T("M"),  _T("N"),  
	_T("O"),  _T("P"),  _T("Q"),  _T("R"),  _T("S"),  _T("T"),  
	_T("U"),  _T("V"),  _T("W"),  _T("X"),  _T("Y"),  _T("Z"), 
	_T("F1"),  _T("F2"),  _T("F3"),  _T("F4"),  _T("F5"),  _T("F6"),  _T("F7"),  _T("F8"),  _T("F9"),  _T("F10"),  _T("F11"),  _T("F12"), 	
	_T("num0"),  _T("num1"),  _T("num2"),  _T("num3"),  _T("num4"),  _T("num5"),  _T("num6"),  _T("num7"),  _T("num8"),  _T("num9"), 
	_T("Left Shift"),  _T("Left Ctrl"),  _T("Left Alt"),  
	_T("Enter"), 
	_T("Right Shift"),  _T("Right Ctrl"),  _T("Right Alt"),  
	_T("Win"), 
};

// static CString s_btnDefault[] = {
// 	CLangX::Get(LKEY_MOUSE_LFET),
// 	CLangX::Get(LKEY_MOUSE_MIDDLE),
// 	CLangX::Get(LKEY_MOUSE_RIGHT),
// 	CLangX::Get(LKEY_MOUSE_DPIINC),
// 	CLangX::Get(LKEY_MOUSE_DPIDEC),
// 	CLangX::Get(LKEY_MOUSE_FORWARD),
// 	CLangX::Get(LKEY_MOUSE_BACKWARD),
// };

static CString s_btnDefault[] = {
	_T("LEFT BUTTON"),
	_T("RIGHT BUTTON"),
	_T("MIDDLE BUTTON"),
	_T("FORWARD"),
	_T("BACKWARD"),
	_T("DPI+"),
	_T("DPI-"),
};


// CMouseButtonDlg dialog

IMPLEMENT_DYNAMIC(CMouseButtonDlg, CUiDlg)

CMouseButtonDlg::CMouseButtonDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CMouseButtonDlg::IDD, pParent)
{
	m_cur_selected = 0;
	m_nValidMacroCount = 0;
}

CMouseButtonDlg::~CMouseButtonDlg()
{
}

void CMouseButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BOOL CMouseButtonDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	return true;
}

BEGIN_MESSAGE_MAP(CMouseButtonDlg, CUiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
//	ON_MESSAGE(WM_UI_PANEL_SELCHANGE, OnUiPanelSelChanged)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_NEW_PAINT, OnNewPaint)


END_MESSAGE_MAP()



// CMouseButtonDlg message handlers

void CMouseButtonDlg::Ui()
{
	UiMain();
}

void CMouseButtonDlg::UiMain()
{
	SetBkBitmap(IDB_LED_BGCOMMON, 0xff, CLR_TRPT);

	UI_STATIC sta[] = 
	{
		UI_STATIC(this, STC_MBTN_STATUS1, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS1, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS2, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS2, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS3, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS3, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS4, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS4, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS5, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS5, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS6, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS6, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS7, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS7, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_STATUS8, CRect(310, 60, 0, 0), _T(""), IDB_MOUSE_STATUS8, CLR_TRPT),

		UI_STATIC(this, STC_MBTN_MOUSE,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_KEYASSIGN, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_KEYMAPPING,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_KEYASSIGN, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_MACRO,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_KEYASSIGN, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_MULTIKEY,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_MULTIKEY_BG, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_MUTILMEDIA,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_KEYASSIGN, CLR_TRPT),
		UI_STATIC(this, STC_MBTN_DEFAULT,		CRect(10, 105, 0, 0), _T(""), IDB_MBTN_KEYASSIGN, CLR_TRPT),

		UI_STATIC(&m_stc[STC_MBTN_MULTIKEY], STC_MBTN_MULTIKEYONE,		CRect(73,  35, 173,  55), _T(""), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_MBTN_MULTIKEY], STC_MBTN_MULTIKEYTWO,		CRect(73,  92, 173, 112), _T(""), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_MBTN_MULTIKEY], STC_MBTN_MULTIKEYTHREE,		CRect(73, 148, 173, 168), _T(""), NULL, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_LEFT, CRect(270-10, 100, 0, 0), _T(""), IDB_MBTN_LEFT, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_RIGHT, CRect(415, 53, 0, 0), _T(""), IDB_MBTN_RIGHT, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_MIDDLE, CRect(405, 86, 0, 0), _T(""), IDB_MBTN_MIDDLE, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_FORWARD, CRect(275, 160, 0, 0), _T(""), IDB_MBTN_FORWARD, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_BACKWARD, CRect(315, 195, 0, 0), _T(""), IDB_MBTN_BACKWARD, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_DPIINC, CRect(420, 108, 0, 0), _T(""), IDB_MBTN_DPIINC, CLR_TRPT),
// 		UI_STATIC(this, STC_MBTN_BUTTON_DPIDEC, CRect(430, 130, 0, 0), _T(""), IDB_MBTN_DPIDEC, CLR_TRPT),
		
	};

	for (int i = STC_MBTN_STATUS1; i < STC_MBTN_NUM; i++)
	{
		m_stc[i].CreateStatic(sta[i]);
	}

	m_stc[STC_MBTN_MULTIKEYONE].ModifyCtrlStyle(ST_VCENTER, ST_LEFT);
	m_stc[STC_MBTN_MULTIKEYONE].SetFont(Font(11), CLR_WHITE);
	m_stc[STC_MBTN_MULTIKEYONE].SetBkColor(CLR_MAIN);
	m_stc[STC_MBTN_MULTIKEYTWO].ModifyCtrlStyle(ST_VCENTER, ST_LEFT);
	m_stc[STC_MBTN_MULTIKEYTWO].SetFont(Font(11), CLR_WHITE);
	m_stc[STC_MBTN_MULTIKEYTWO].SetBkColor(CLR_MAIN);
	m_stc[STC_MBTN_MULTIKEYTHREE].ModifyCtrlStyle(ST_VCENTER, ST_LEFT);
	m_stc[STC_MBTN_MULTIKEYTHREE].SetFont(Font(11), CLR_WHITE);
	m_stc[STC_MBTN_MULTIKEYTHREE].SetBkColor(CLR_MAIN);


	m_stc[STC_MBTN_STATUS1].ShowWindow(SW_SHOW);
	m_stc[STC_MBTN_STATUS2].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS3].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS4].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS5].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS6].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS7].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_STATUS8].ShowWindow(SW_HIDE);

 	UI_BTN btn[] = 
 	{
  	//	UI_BTN(this, BTN_MBTN_ADDPROFILE, CRect(155+40, 30, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILEOFF)),
  		UI_BTN(this, BTN_MBTN_EDITPROFILE, CRect(215-50, 30, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITOFF, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILEOFF, CLR_TRPT), NULL, BTN_CHECK),
  	//	UI_BTN(this, BTN_MBTN_DELPROFILE,  CRect(195+40, 30, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_DELETEFILE, IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILEOFF)),
  		
		UI_BTN(this, BTN_MBTN_LEFT, CRect(310, 165, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[0],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
		UI_BTN(this, BTN_MBTN_RIGHT, CRect(490, 60, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[2],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),

		UI_BTN(this, BTN_MBTN_MIDDLE, CRect(519, 91, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[1],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
		UI_BTN(this, BTN_MBTN_FORWARD, CRect(321, 214, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[5],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
		UI_BTN(this, BTN_MBTN_BACKWARD, CRect(341, 256, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[6],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
		UI_BTN(this, BTN_MBTN_DPIINC, CRect(531, 125, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[3],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
		UI_BTN(this, BTN_MBTN_DPIDEC, CRect(543, 161, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_MBTN_M3ON, IDB_MBTN_M3ON, IDB_MBTN_M3ON, 0, CLR_TRPT), &UIBTN_STRING(s_btnDefault[4],	CLR_WHITE, CLR_WHITE,CLR_WHITE,CLR_GRAY2,CLR_WHITE, CLR_WHITE, CLR_WHITE, CLR_GRAY2, Font(10)), BTN_RADIO),
	

		UI_BTN(this, BTN_MBTN_APPLY, CRect(240+80, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYOFF, CLR_TRPT)),
		UI_BTN(this, BTN_MBTN_RESET, CRect(340+75, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_RESETON, IDB_MOUSE_RESETON, IDB_MOUSE_RESETON, IDB_MOUSE_RESETOFF, CLR_TRPT)),
		UI_BTN(this, BTN_MBTN_DEFAULT, CRect(440+70, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTOFF, CLR_TRPT)),	
 	};
 
 	for(int i=BTN_MBTN_EDITPROFILE; i <= BTN_MBTN_DEFAULT; i++)
 	{
		m_btn[i].CreateButton(btn[i - (int)BTN_MBTN_EDITPROFILE]);
 		m_btn[i].SetCursor(IDC_CUR_HAND);
	//	m_btn[i].SetBkColor(CLR_WHITE);
 	}

	


	m_edit[EDIT_MBTN_PROFILE].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(10,  35, 140,  47), this, EDIT_MBTN_PROFILE);
	m_edit[EDIT_MBTN_PROFILE].SetFont(Font(9), CLR_WHITE);
	m_edit[EDIT_MBTN_PROFILE].SetBkColor(CLR_DARK);
	m_edit[EDIT_MBTN_PROFILE].ShowWindow(SW_HIDE);


	m_combobox[COMBOX_MBTN_PROFILE].Create(CRect(10, 35, 0, 0), this, COMBOX_MBTN_PROFILE);
	m_combobox[COMBOX_MBTN_PROFILE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL ,IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, 0, CLR_NONE);
	m_combobox[COMBOX_MBTN_PROFILE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_MBTN_PROFILE].SetCursor(IDC_CUR_HAND);
	m_combobox[COMBOX_MBTN_PROFILE].SetArrowWidth(20);
	m_combobox[COMBOX_MBTN_PROFILE].GetDropList()->SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_MBTN_PROFILE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_MBTN_PROFILE].GetDropList()->SetHighlightBkColor(CLR_MAIN);


 	for (int i = 0; i < 5; i++)
 	{
 		CString sValue;
 		//sValue.Format(CLangX::Get(LANG_PROFILE) + _T("%d"), i+1);
 		sValue.Format(_T("PROFILE %d"), i+1);
 		m_combobox[COMBOX_MBTN_PROFILE].AddString(sValue, 0, CLR_MAIN);
 	}
 	m_combobox[COMBOX_MBTN_PROFILE].SetCurSel(0);

 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].Create(CRect(10, 65, 0, 0), this, COMBOX_MBTN_DEFAULTSETTING);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetComboBoxBitmap(IDB_MBTN_COMB_LONG, IDB_MBTN_COMB_LONG, IDB_MBTN_COMB_LONG, 0, CLR_NONE);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetFont(Font(11), CLR_WHITE);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCursor(IDC_CUR_HAND);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetArrowWidth(20);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].GetDropList()->SetFont(Font(11), CLR_WHITE);
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].GetDropList()->SetBkColor(RGB(0, 0, 0));
 	m_combobox[COMBOX_MBTN_DEFAULTSETTING].GetDropList()->SetHighlightBkColor(CLR_MAIN);

	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("MOUSE"),	0, CLR_WHITE);
	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("KEY MAPPING"),	0, CLR_WHITE);
	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("MACRO"),	0, CLR_WHITE);
	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("MULTI-KEY"),	0, CLR_WHITE);
	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("MULTIMEIDA"),	0, CLR_WHITE);
	m_combobox[COMBOX_MBTN_DEFAULTSETTING].AddString(_T("DEFAULT"),	0, CLR_WHITE);



	m_list[COMBOX_MBTN_MOUSE].CreateList(LST_HOTKEY, CRect(5, 20, 244, 200), &m_stc[STC_MBTN_MOUSE], 1, 30, true);//305265673424 140, 216, 410, 460
	m_list[COMBOX_MBTN_MOUSE].SetScrollSliCtrl(
		UI_SLIDERCTRL(&m_list[COMBOX_MBTN_MOUSE], 1, CRect(225,  10, 0, 0), IDB_MBTN_SCR_BAR, IDB_MBTN_SCR_BAR, 0, IDB_MBTN_SCR_SLI, IDB_MBTN_SCR_SLI, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE)
		, UI_BTN(&m_list[COMBOX_MBTN_MOUSE], 2, CRect(225,   0, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   0))
		, UI_BTN(&m_list[COMBOX_MBTN_MOUSE], 3, CRect(225, 170, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, 0)));
	m_list[COMBOX_MBTN_MOUSE].InsertColumn(0, _T("ICON"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_MOUSE].InsertColumn(1, _T("NAME"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_MOUSE].SetColumnWidth(0,  0); // 砞竚糴
	m_list[COMBOX_MBTN_MOUSE].SetColumnWidth(1, 234);
	//m_list[COMBOX_MBTN_MOUSE].SetItemText(m_list[].InsertImgItem(0, IDB_MARCO_DELAY), 1, _T("")); 
	m_list[COMBOX_MBTN_MOUSE].RemoveImgItem(0);

	for (int i = 0; i < s_nMouseKey; i++)
	{
		m_list[COMBOX_MBTN_MOUSE].SetItemText(m_list[COMBOX_MBTN_MOUSE].InsertImgItem(m_list[COMBOX_MBTN_MOUSE].GetItemCount(), 0), 1, s_MouseKey[i]);
	}


	// Peter Lee 2017/7/9 change comboo to listbox
	m_list[COMBOX_MBTN_HOTKEY].CreateList(LST_HOTKEY, CRect(5, 20, 244, 200), &m_stc[STC_MBTN_MUTILMEDIA], 1, 30, true);//305265673424 140, 216, 410, 460
	m_list[COMBOX_MBTN_HOTKEY].SetScrollSliCtrl(
		UI_SLIDERCTRL(&m_list[COMBOX_MBTN_HOTKEY], 1, CRect(225,  10, 0, 0), IDB_MBTN_SCR_BAR, IDB_MBTN_SCR_BAR, 0, IDB_MBTN_SCR_SLI, IDB_MBTN_SCR_SLI, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE)
		, UI_BTN(&m_list[COMBOX_MBTN_HOTKEY], 2, CRect(225,   0, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   0))
		, UI_BTN(&m_list[COMBOX_MBTN_HOTKEY], 3, CRect(225, 170, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, 0)));
	m_list[COMBOX_MBTN_HOTKEY].InsertColumn(0, _T("ICON"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_HOTKEY].InsertColumn(1, _T("NAME"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_HOTKEY].SetColumnWidth(0,  0); // 砞竚糴
	m_list[COMBOX_MBTN_HOTKEY].SetColumnWidth(1, 234);
	//m_list[COMBOX_MBTN_HOTKEY].SetItemText(m_list[].InsertImgItem(0, IDB_MARCO_DELAY), 1, _T("")); 
	m_list[COMBOX_MBTN_HOTKEY].RemoveImgItem(0);

	for (int i = 0; i < s_nMultiMedia; i++)
	{
		m_list[COMBOX_MBTN_HOTKEY].SetItemText(m_list[COMBOX_MBTN_HOTKEY].InsertImgItem(m_list[COMBOX_MBTN_HOTKEY].GetItemCount(), 0), 1, s_sMultiMedia[i]);
	}

	// Peter Lee 2017/7/9 change comboo to listbox
	m_list[COMBOX_MBTN_MACRO].CreateList(LST_MACRO, CRect(5, 20, 244, 200), &m_stc[STC_MBTN_MACRO], 1, 30, true);
	m_list[COMBOX_MBTN_MACRO].SetScrollSliCtrl(
		UI_SLIDERCTRL(&m_list[COMBOX_MBTN_MACRO], 1, CRect(225,  10, 0, 0), IDB_MBTN_SCR_BAR, IDB_MBTN_SCR_BAR, 0, IDB_MBTN_SCR_SLI, IDB_MBTN_SCR_SLI, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE)
		, UI_BTN(&m_list[COMBOX_MBTN_MACRO], 2, CRect(225,   0, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   0))
		, UI_BTN(&m_list[COMBOX_MBTN_MACRO], 3, CRect(225, 170, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, 0)));
	m_list[COMBOX_MBTN_MACRO].InsertColumn(0, _T("ICON"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_MACRO].InsertColumn(1, _T("NAME"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_MACRO].SetColumnWidth(0,  0); // 砞竚糴
	m_list[COMBOX_MBTN_MACRO].SetColumnWidth(1, 234);
	//m_list[COMBOX_MBTN_MACRO].SetItemText(m_list[].InsertImgItem(0, IDB_MARCO_DELAY), 1, _T("")); 
	m_list[COMBOX_MBTN_MACRO].RemoveImgItem(0);

	// Peter Lee 2017/7/9 change comboo to listbox
	m_list[COMBOX_MBTN_KEYMAPPING].CreateList(LST_KEYMAPPING, CRect(5, 20, 244, 200), &m_stc[STC_MBTN_KEYMAPPING], 1, 30, true);//305265673424 140, 216, 410, 460
	m_list[COMBOX_MBTN_KEYMAPPING].SetScrollSliCtrl(
		UI_SLIDERCTRL(&m_list[COMBOX_MBTN_KEYMAPPING], 1, CRect(225,  10, 0, 0), IDB_MBTN_SCR_BAR, IDB_MBTN_SCR_BAR, 0, IDB_MBTN_SCR_SLI, IDB_MBTN_SCR_SLI, 0, CLR_TRPT, WS_CHILD | WS_VISIBLE)
		, UI_BTN(&m_list[COMBOX_MBTN_KEYMAPPING], 2, CRect(225,   0, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   IDB_MBTN_SCROLL_UP,   0))
		, UI_BTN(&m_list[COMBOX_MBTN_KEYMAPPING], 3, CRect(225, 170, 0, 0), &UIBTN_IMAGE(IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, IDB_MBTN_SCROLL_DOWN, 0)));
	m_list[COMBOX_MBTN_KEYMAPPING].InsertColumn(0, _T("ICON"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_KEYMAPPING].InsertColumn(1, _T("NAME"), LVCFMT_CENTER);
	m_list[COMBOX_MBTN_KEYMAPPING].SetColumnWidth(0,  0); // 砞竚糴
	m_list[COMBOX_MBTN_KEYMAPPING].SetColumnWidth(1, 234);
	//m_list[COMBOX_MBTN_KEYMAPPING].SetItemText(m_list[].InsertImgItem(0, IDB_MARCO_DELAY), 1, _T("")); 
	m_list[COMBOX_MBTN_KEYMAPPING].RemoveImgItem(0);

	for (int i = 0; i < s_nKeyMapping; i++)
	{
		m_list[COMBOX_MBTN_KEYMAPPING].SetItemText(m_list[COMBOX_MBTN_KEYMAPPING].InsertImgItem(m_list[COMBOX_MBTN_KEYMAPPING].GetItemCount(), 0), 1, s_KeyMapping[i]);
	}
	m_list[COMBOX_MBTN_KEYMAPPING].SetCurSel(0);

// 	m_combobox[COMBOX_MBTN_MOUSE].Create(CRect(10, 20, 0, 0), &m_stc[STC_MBTN_MOUSE], COMBOX_MBTN_MOUSE);
// 	m_combobox[COMBOX_MBTN_MOUSE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_TRPT);
// 	m_combobox[COMBOX_MBTN_MOUSE].SetFont(Font(11), CLR_WHITE); // 字体
// 	m_combobox[COMBOX_MBTN_MOUSE].SetCursor(IDC_CUR_HAND); // 鼠标手型
// 	m_combobox[COMBOX_MBTN_MOUSE].SetArrowWidth(20);
// 	m_combobox[COMBOX_MBTN_MOUSE].GetDropList()->SetFont(Font(11));
// 	m_combobox[COMBOX_MBTN_MOUSE].GetDropList()->SetBkColor(RGB(0, 0, 0));
// 	m_combobox[COMBOX_MBTN_MOUSE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
// 	m_combobox[COMBOX_MBTN_MOUSE].ModifyCtrlStyle(ST_RIGHT,ST_LEFT);
// 
// 	for (int i = 0; i < s_nMouseKey; i++)
// 	{
// 		m_combobox[COMBOX_MBTN_MOUSE].AddString(s_MouseKey[i], 0, CLR_MAIN);
// 	}
//  	m_combobox[COMBOX_MBTN_MOUSE].SetCurSel(0);
// 
// 	//绘制MUTILMEDIA下拉框
// 	m_combobox[COMBOX_MBTN_HOTKEY].Create(CRect(10, 20, 0, 0), &m_stc[STC_MBTN_MUTILMEDIA], COMBOX_MBTN_HOTKEY);
// 	m_combobox[COMBOX_MBTN_HOTKEY].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
// 	m_combobox[COMBOX_MBTN_HOTKEY].SetFont(Font(11), CLR_WHITE);
// 	m_combobox[COMBOX_MBTN_HOTKEY].SetCursor(IDC_CUR_HAND); 
// 	m_combobox[COMBOX_MBTN_HOTKEY].SetArrowWidth(20);
// 	m_combobox[COMBOX_MBTN_HOTKEY].GetDropList()->SetFont(Font(11));
// 	m_combobox[COMBOX_MBTN_HOTKEY].GetDropList()->SetBkColor(RGB(0, 0, 0));
// 	m_combobox[COMBOX_MBTN_HOTKEY].GetDropList()->SetHighlightBkColor(CLR_MAIN);
// 	m_combobox[COMBOX_MBTN_HOTKEY].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);
// 	for (int i = 0; i < s_nMultiMedia; i++)
// 	{
// 		m_combobox[COMBOX_MBTN_HOTKEY].AddString(s_sMultiMedia[i], 0, CLR_WHITE);
// 	}
// 
// 	//绘制MACRO下拉框
// 	m_combobox[COMBOX_MBTN_MACRO].Create(CRect(10, 20, 0, 0), &m_stc[STC_MBTN_MACRO], COMBOX_MBTN_MACRO);
// 	m_combobox[COMBOX_MBTN_MACRO].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_NONE);
// 	m_combobox[COMBOX_MBTN_MACRO].SetFont(Font(11), CLR_WHITE);
// 	m_combobox[COMBOX_MBTN_MACRO].SetCursor(IDC_CUR_HAND); 
// 	m_combobox[COMBOX_MBTN_MACRO].SetArrowWidth(20);
// 	m_combobox[COMBOX_MBTN_MACRO].GetDropList()->SetFont(Font(11));
// 	m_combobox[COMBOX_MBTN_MACRO].GetDropList()->SetBkColor(RGB(0, 0, 0));
// 	m_combobox[COMBOX_MBTN_MACRO].GetDropList()->SetHighlightBkColor(CLR_MAIN);
// 	m_combobox[COMBOX_MBTN_MACRO].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);
// 
// 
// 	//绘制key mappiing下拉框
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].Create(CRect(10, 20, 0, 0), &m_stc[STC_MBTN_KEYMAPPING], COMBOX_MBTN_KEYMAPPING);
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, CLR_TRPT);
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].SetFont(Font(11), CLR_WHITE); // 字体
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].SetCursor(IDC_CUR_HAND); // 鼠标手型
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].SetArrowWidth(20);
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].GetDropList()->SetFont(Font(11));
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].GetDropList()->SetBkColor(RGB(0, 0, 0));
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].GetDropList()->SetHighlightBkColor(CLR_MAIN);
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].ModifyCtrlStyle(ST_RIGHT,ST_LEFT);
// 
// 	for (int i = 0; i < s_nKeyMapping; i++)
// 	{
// 		m_combobox[COMBOX_MBTN_KEYMAPPING].AddString(s_KeyMapping[i], 0, CLR_MAIN);
// 	}
// 	m_combobox[COMBOX_MBTN_KEYMAPPING].SetCurSel(0);

// 	m_hotkeY.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(20,  45, 136,  65), &m_stc[STC_MBTN_MULTIKEY], 0);
// 	m_hotkeY.SetBkColor(CLR_DARK);
// 	m_hotkeY.SetFont(Font(11), CLR_WHITE);
	m_hotkeY.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(73,  30, 75,  32), &m_stc[STC_MBTN_MULTIKEY], 0);
	m_hotkeY.SetBkColor(CLR_DARK);
	m_hotkeY.SetFont(Font(5), CLR_DARK);

}



LRESULT CMouseButtonDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{

	int nCurProfile =  s_nCurProfile.nProfile;
	
	switch(wParam)
	{

#if 1
	case BTN_MBTN_EDITPROFILE:
		{
			bool bCheck = m_btn[BTN_MBTN_EDITPROFILE].IsCheck();
			m_edit[EDIT_MBTN_PROFILE].ShowWindow(bCheck ? SW_SHOW : SW_HIDE);
			m_combobox[COMBOX_MBTN_PROFILE].ShowWindow(bCheck ? SW_HIDE : SW_SHOW);

			if (bCheck)
			{
				m_edit[EDIT_MBTN_PROFILE].SetWindowText(m_btnProfiles[0][nCurProfile].sProfileName);
			}
			else
			{
				CString sName = _T("");
				m_edit[EDIT_MBTN_PROFILE].GetWindowText(sName);
				sName.Trim();
				if (_T("") == sName)
				{
					sName = m_btnProfiles[0][nCurProfile].sProfileName;
					m_edit[EDIT_MBTN_PROFILE].SetWindowText(sName);
				}
				m_btnProfiles[0][nCurProfile].sProfileName = sName;
				m_combobox[COMBOX_MBTN_PROFILE].ResetContent();
				for (int i = 0; i < LED_PROFILE_CONT; i++)
				{
					m_combobox[COMBOX_MBTN_PROFILE].AddString(m_btnProfiles[0][i].sProfileName, 0, CLR_WHITE);
				}
				m_combobox[COMBOX_MBTN_PROFILE].SetCurSel(nCurProfile);


				CArray<LED_SETTING> profiles;
				for (int i = 0; i < LED_PROFILE_CONT; i++)
				{
					profiles.Add(m_btnProfiles[0][i]);
				}

				Aorus()->GetCfg()->SetLedProfiles(DEVICE_AM300, profiles, 0, 0);
			}
			return 1;

		}

#endif
	//****************************************************************
		case BTN_MBTN_APPLY:
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);

			CmdLock();
			int item = m_combobox[COMBOX_MBTN_DEFAULTSETTING].GetCurSel();
			switch (item)
			{

			case 0: // mouse
				{
					//int index = m_combobox[COMBOX_MBTN_MOUSE].GetCurSel();
					int index = m_list[COMBOX_MBTN_MOUSE].GetCurSel();
					OnSave(GetMouseKeyFun(index));
					CString s;
					//m_combobox[COMBOX_MBTN_MOUSE].GetWindowText(s);
					s = m_list[COMBOX_MBTN_MOUSE].GetItemText(index, 1);
				//	m_list[COMBOX_MBTN_MOUSE].GetWindowText(s);
					SetBtnCapture(s, m_cur_selected + BTN_MBTN_LEFT);
				}
				break;
			case 1: // key mapping
				{
					//int index = m_combobox[COMBOX_MBTN_KEYMAPPING].GetCurSel();
					int index = m_list[COMBOX_MBTN_KEYMAPPING].GetCurSel();
					OnSave(GetKeyMappingKeyFun(index));
					CString s;
					//m_combobox[COMBOX_MBTN_KEYMAPPING].GetWindowText(s);
					s = m_list[COMBOX_MBTN_KEYMAPPING].GetItemText(index, 1);
			//		m_list[COMBOX_MBTN_KEYMAPPING].GetWindowText(s);
					SetBtnCapture(s, m_cur_selected + BTN_MBTN_LEFT);
				}
				break;
			case 2: // macro
				{
					//int index = m_combobox[COMBOX_MBTN_MACRO].GetCurSel();
					int index = m_list[COMBOX_MBTN_MACRO].GetCurSel();
					GVORDER_KEYFUN fun = GetMacroKeyFun(index);
					// 無效macro
					if (fun.fnType == GVORDER_FUN_NONE)
					{
						ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
				//		ShowLoadingWindow(GetParent()->GetParent(), SW_HIDE);
						AfxMessageBox(_T("The current macro script is empty"));
					}
					else
					{
						OnSave(fun);
						CString s;
						//m_combobox[COMBOX_MBTN_MACRO].GetWindowText(s);
						s = m_list[COMBOX_MBTN_MACRO].GetItemText(index, 1);
					//	m_list[COMBOX_MBTN_MACRO].GetWindowText(s);
						SetBtnCapture(s, m_cur_selected + BTN_MBTN_LEFT);
					}
				}
				break;
			case 3: // hot key
				{
					CString name = m_hotkeY.GetHotKeyName();
					WORD vk;
					WORD modifiers;
					m_hotkeY.GetHotKey(vk, modifiers);
					if (modifiers == 0)
					{
						ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
					//	ShowLoadingWindow(GetParent()->GetParent(), SW_HIDE);
						CString s;
						s.Format( _T("%s is not a valid multi-key"), name);
						AfxMessageBox(s);
					}
					else
					{
						GVORDER_KEYFUN keyfun;
						keyfun.fnType = GVORDER_FUN_KEYBOARD;
						keyfun.value.keyboard.keyCode = vk;
						keyfun.value.keyboard.keyModifier = modifiers;
						if(0 == modifiers)
						{
							ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
						//	ShowLoadingWindow(GetParent()->GetParent(), SW_HIDE);
							CString s;
							s.Format( _T("%s is not a valid multi-key"), name);
							AfxMessageBox(s);
							return 1;
						}

						OnSave(keyfun);
						SetBtnCapture(name, m_cur_selected + BTN_MBTN_LEFT);
					}
				}
				break;
			case 4: // multimedia
				{
					//int index = m_combobox[COMBOX_MBTN_HOTKEY].GetCurSel();
					int index = m_list[COMBOX_MBTN_HOTKEY].GetCurSel();
					OnSave(GetMultimediaKeyFun(index));
					CString s;
					//m_combobox[COMBOX_MBTN_HOTKEY].GetWindowText(s);

					s = m_list[COMBOX_MBTN_HOTKEY].GetItemText(index, 1);
				//	m_list[COMBOX_MBTN_HOTKEY].GetWindowText(s);
					SetBtnCapture(s, m_cur_selected + BTN_MBTN_LEFT);
				}
				break;


 			case 5: // Default
 				{
 					OnSave(GetDefaultKeyFun(m_cur_selected));
 					SetBtnCapture(s_btnDefault[m_cur_selected], m_cur_selected + BTN_MBTN_LEFT);
 				}
 				break;
			}
			Sleep(1000);
			CmdUnLock();;
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	case BTN_MBTN_RESET:
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			CmdLock();
			GVORDER_KEYFUN keyfun;
			keyfun.nIndex = key_index[m_cur_selected]; // 左右中45加減
			keyfun.nProfile = s_nCurProfile.nProfile;
			CAM300Ctrl::GetKeyMapping(keyfun);
			SetBtnInfo(keyfun, m_cur_selected);
			CmdUnLock();
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	case BTN_MBTN_DEFAULT:
		{		
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			CmdLock();
	//		m_panel[PAN_MOUSE_BUTTONS_LEFT_NAV].SetCurItem(0);
			m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(6);
			EnableLeftPanelOne(-1);
			CAM300Ctrl::SetKeyMappingDefault(s_nCurProfile.nProfile, GVORDER_DEVICE_MOUSE);
			for (int i = 0; i < 7; i++)
			{
				SetBtnCapture(s_btnDefault[i], i + BTN_MBTN_LEFT);
			}
			CAM300Ctrl::SelProfile(s_nCurProfile.nProfile);
			CmdUnLock();
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	case BTN_MBTN_LEFT: // 
	case BTN_MBTN_MIDDLE:
	case BTN_MBTN_RIGHT:
	case BTN_MBTN_FORWARD:
	case BTN_MBTN_BACKWARD:
	case BTN_MBTN_DPIINC:
	case BTN_MBTN_DPIDEC:
		{
			m_stc[STC_MBTN_STATUS1].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS2].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS3].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS4].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS5].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS6].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS7].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_STATUS8].ShowWindow(SW_HIDE);


			// 設置選中某一個
			m_btn[BTN_MBTN_LEFT].SetCheck(BTN_MBTN_LEFT == wParam);
			m_btn[BTN_MBTN_MIDDLE].SetCheck(BTN_MBTN_MIDDLE == wParam);
			m_btn[BTN_MBTN_RIGHT	].SetCheck(BTN_MBTN_RIGHT == wParam);
			m_btn[BTN_MBTN_FORWARD].SetCheck(BTN_MBTN_FORWARD == wParam);
			m_btn[BTN_MBTN_BACKWARD	].SetCheck(BTN_MBTN_BACKWARD == wParam);
			m_btn[BTN_MBTN_DPIINC].SetCheck(BTN_MBTN_DPIINC == wParam);
			m_btn[BTN_MBTN_DPIDEC].SetCheck(BTN_MBTN_DPIDEC == wParam);
			// 記錄下選中的按鈕index，從0-6
			m_cur_selected = wParam - BTN_MBTN_LEFT;

			switch(m_cur_selected)
			{
			case 0:m_stc[STC_MBTN_STATUS2].ShowWindow(SW_SHOW); break;
			case 1:m_stc[STC_MBTN_STATUS3].ShowWindow(SW_SHOW); break;
			case 2:m_stc[STC_MBTN_STATUS4].ShowWindow(SW_SHOW); break;
			case 3:m_stc[STC_MBTN_STATUS7].ShowWindow(SW_SHOW); break;
			case 4:m_stc[STC_MBTN_STATUS8].ShowWindow(SW_SHOW); break;
			case 5:m_stc[STC_MBTN_STATUS5].ShowWindow(SW_SHOW); break;
			case 6:m_stc[STC_MBTN_STATUS6].ShowWindow(SW_SHOW); break;
	
			}

			return OnMouseButtonClicked(wParam);
		}
	}
	return 1;
}

void CMouseButtonDlg::OnPaint()
{
	CUiDlg::OnPaint();
}


void CMouseButtonDlg::GetMacrosList()
{
	CmdLock();
	int nIndex = -1;
	if (m_nValidMacroCount > 0 && m_list[COMBOX_MBTN_MACRO] >= 0)
	{
		nIndex = m_list[COMBOX_MBTN_MACRO].GetCurSel();
		nIndex = m_validMacros[nIndex].nIndex;
	}
	m_list[COMBOX_MBTN_MACRO].RemoveAllItem(); // ?????
	GVORDER_MACROS_ATTR lstmacros[MACRO_COUNT];
	CAM300Ctrl::GetMacrosList(lstmacros, MACRO_COUNT);
	int marcoIndex = 0;
	for (int i = 0; i < MACRO_COUNT; i++)
	{
		GVORDER_MACROS_ATTR marco = lstmacros[i];
		if (MacroIsValid(marco))
		{
			//m_combobox[COMBOX_MBTN_MACRO].AddString(marco.szName, 0, CLR_MAIN);
			m_list[COMBOX_MBTN_MACRO].SetItemText(m_list[COMBOX_MBTN_MACRO].InsertImgItem(m_list[COMBOX_MBTN_MACRO].GetItemCount(), 0), 1, marco.szName);
			if (nIndex == i)
			{
				m_list[COMBOX_MBTN_MACRO].SetCurSel(marcoIndex);
			}
			GVORDER_MACROS macros;
			macros.nIndex = i;
			macros.attr = marco;
			m_validMacros[marcoIndex++] = macros;
		}
	}
	m_nValidMacroCount = marcoIndex;
	CmdUnLock();
}

bool CMouseButtonDlg::MacroIsValid(GVORDER_MACROS_ATTR macro)
{
	return macro.nIcon >= 1 && macro.nIcon <= MACRO_COUNT;
}


void CMouseButtonDlg::InitBtnState()
{

	InitProfile();//初始化Profile設置  Terry 201707/13

	CmdLock();
	int leftClickIndex = -1; // 存儲左鍵的indextn
	for (int i = 0; i < 7; i++)
	{
		m_btn[i + BTN_MBTN_LEFT].Enable(true); // 所有按鍵都enable

		GVORDER_KEYFUN keyfun;
		keyfun.nIndex = key_index[i]; // 左右中45加減
		keyfun.nProfile = s_nCurProfile.nProfile;
		//	GvOrderGetKeyMapping(keyfun, s_MouseIndex); // 取得鍵信息
		CAM300Ctrl::GetKeyMapping(keyfun);
		if (keyfun.fnType == 0xff || keyfun.fnType == GVORDER_FUN_DEFAULT) // 沒有設置過
		{
			// 設置默認的按鍵信息
			SetBtnCapture(s_btnDefault[i], i + BTN_MBTN_LEFT);
			if (s_btnDefault[i] == CLangX::Get(LKEY_MOUSE_LFET)) // 如果當前鍵是左鍵
			{
				if (leftClickIndex == -1) // 第一次找到左鍵
				{
					leftClickIndex = i; // 記錄當前的索引
				}else
				{
					leftClickIndex = -1; // 不是第一次找到左鍵了，說明有多個左鍵，全部enable，否則disable左鍵
				}
			}
			continue;
		}

		if(
			keyfun.fnType !=  GVORDER_FUN_MACROSONCE &&
			keyfun.fnType !=  GVORDER_FUN_MACROSLOOP &&
			keyfun.fnType !=  GVORDER_FUN_MACROCSFIRE) // 不是marco
		{
			//int index = GetLeftListIndex(keyfun);
			CString sValue = GetKeyFunName(keyfun);
			SetBtnCapture(sValue, i + BTN_MBTN_LEFT);
			if (sValue == CLangX::Get(LKEY_MOUSE_LFET)) // 如果當前鍵是左鍵
			{
				if (leftClickIndex == -1) // 第一次找到左鍵
				{
					leftClickIndex = i; // 記錄當前的索引
				}else
				{
					leftClickIndex = -1; // 不是第一次找到左鍵了，說明有多個左鍵，全部enable，否則disable左鍵
				}
			}
		}
		else
		{
			GVORDER_MACROS_ATTR lstmacros[MACRO_COUNT];
			//	GvOrderGetMacrosList(lstmacros, MACRO_COUNT, s_MouseIndex);
			CAM300Ctrl::GetMacrosList(lstmacros, MACRO_COUNT);
			int index = keyfun.value.macros.macrosIndex;
			if (index > 50)
			{
				continue;
			}
			if (!MacroIsValid(lstmacros[index]))
			{
				continue;
			}
			//int icon =lstmacros[index].nIcon - 1 + IDB_ICON_MACRO_01;
			SetBtnCapture(lstmacros[index].szName, i + BTN_MBTN_LEFT);
		}
	}
	if (leftClickIndex != -1)
	{
		m_btn[leftClickIndex + BTN_MBTN_LEFT].Enable(false); // 禁用按鈕
		if (m_cur_selected == leftClickIndex) // 如果當前禁用的按鈕是當前選擇的，則使下一個變成選中的
		{
			m_btn[m_cur_selected + BTN_MBTN_LEFT].SetCheck(false);
			if (++m_cur_selected == 8) // 如果當前選擇的是最後一個，則設置第一個為選中的
			{
				m_cur_selected = 0;
			}
			m_btn[m_cur_selected + BTN_MBTN_LEFT].SetCheck(true);
		}
	}

	// 設置完鍵信息后，根據當前選中的鍵，設置按鍵左邊的信息
	GVORDER_KEYFUN keyfun;
	keyfun.nIndex = key_index[m_cur_selected]; // 左右中45加減
	keyfun.nProfile = s_nCurProfile.nProfile;
	//	GvOrderGetKeyMapping(keyfun, s_MouseIndex); // 取得鍵信息
	CAM300Ctrl::GetKeyMapping(keyfun);
	SetBtnInfo(keyfun, m_cur_selected);
	CmdUnLock();
}

LRESULT CMouseButtonDlg::OnMouseButtonClicked(WPARAM wParam)
{
	switch (wParam)
	{
	case BTN_MBTN_LEFT: // 
	case BTN_MBTN_RIGHT:
	case BTN_MBTN_MIDDLE:
	case BTN_MBTN_FORWARD:
	case BTN_MBTN_BACKWARD:
	case BTN_MBTN_DPIINC:
	case BTN_MBTN_DPIDEC:

		CmdLock();
		GVORDER_KEYFUN keyfun;
		keyfun.nIndex = key_index[wParam - BTN_MBTN_LEFT];
		keyfun.nProfile = s_nCurProfile.nProfile;
		//	GvOrderGetKeyMapping(keyfun, s_MouseIndex); // 取得這個鍵存儲什麼信息
		CAM300Ctrl::GetKeyMapping(keyfun);
 		SetBtnInfo(keyfun, wParam - BTN_MBTN_LEFT); // 把這個鍵的index傳過去
		CmdUnLock();
		break;
	}
	return 1;
}

LRESULT CMouseButtonDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nCurSel = (int)lParam; 
	switch(wParam)
	{
	case COMBOX_MBTN_DEFAULTSETTING:
		{
			m_stc[STC_MBTN_MOUSE].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_KEYMAPPING].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_MACRO].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_MULTIKEY].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_MUTILMEDIA].ShowWindow(SW_HIDE);
			m_stc[STC_MBTN_DEFAULT].ShowWindow(SW_HIDE);

			switch(nCurSel)
			{
			case 0: m_stc[STC_MBTN_MOUSE].ShowWindow(SW_SHOW); break;
			case 1: m_stc[STC_MBTN_KEYMAPPING].ShowWindow(SW_SHOW); break;
			case 2: m_stc[STC_MBTN_MACRO].ShowWindow(SW_SHOW); break;
			case 3: m_stc[STC_MBTN_MULTIKEY].ShowWindow(SW_SHOW); m_hotkeY.SetFocus();break;
			case 4: m_stc[STC_MBTN_MUTILMEDIA].ShowWindow(SW_SHOW); break;
			case 5: m_stc[STC_MBTN_DEFAULT].ShowWindow(SW_SHOW); break;
			}
			break;
		}
	case COMBOX_MBTN_PROFILE: 

		s_nCurProfile.nProfile = lParam;
		CAM300Ctrl::SelProfile(lParam);
		InitBtnState();
		CAM300Ctrl::GetProfile(s_nCurProfile);
		s_LastApplyProfile = s_nCurProfile;
		//m_ledDlg.SendMessage(WM_UI_COMBOBOX_SELCHANGED, 2, lParam);
		CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
		pParent->SwitchM3LedDlProfile(lParam);
		break;
	}
	return 1;
}

void CMouseButtonDlg::OnSave(GVORDER_KEYFUN fun)
{
	fun.nIndex = key_index[m_cur_selected];
	fun.nProfile = s_nCurProfile.nProfile;
	CmdLock();
	CAM300Ctrl::SetKeyMapping(fun);
	CAM300Ctrl::SelProfile(s_nCurProfile.nProfile);
	CmdUnLock();
}

void CMouseButtonDlg::SetBtnCapture(CString s, int btn)
{
	m_btn[btn].SetCapture(s);

	int leftClickIndex = -1;
	for (int i = 0; i < 7; i++) // 找左鍵
	{
		m_btn[i + BTN_MBTN_LEFT].Enable(true);
		CString s = m_btn[i + BTN_MBTN_LEFT].GetCapture();
		if (s == CLangX::Get(LKEY_MOUSE_LFET) || s == CLangX::Get(LKEY_MOUSE_LFET)) // 左鍵
		{
			if (leftClickIndex == -1) // 第一次找到左鍵 記錄當前的索引
			{
				leftClickIndex = i;
			}else
			{
				leftClickIndex = -1; // 不是第一次找到左鍵了，說明有多個左鍵，全部enable，否則disable左鍵
			}
		}
	}
	if (leftClickIndex != -1)
	{
		m_btn[leftClickIndex + BTN_MBTN_LEFT].SetCheck(false);
		m_btn[leftClickIndex + BTN_MBTN_LEFT].Enable(false); // 禁用按鈕
	}
}

void CMouseButtonDlg::SetBtnInfo(GVORDER_KEYFUN keyfun, int btn_index)
{
	//判斷應該勾選哪一個單選按鈕

	int index = 0;
	// Default
	if (btn_index == GetDefaultIndex(keyfun)) // 如果該按鍵存儲的是基本按鍵，而且選中的和存儲的都是一致的，則為Default
	{

	//	m_panel[PAN_MOUSE_BUTTONS_LEFT_NAV].SetCurItem(0);
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(5);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 6);
	}
	else if ((index = GetMouseCMBIndex(keyfun)) != -1) // mouse
	{
		/*m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(1);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 1);
		m_combobox[COMBOX_MBTN_MOUSE].SetCurSel(index);
		m_combobox[COMBOX_MBTN_MOUSE].Invalidate(TRUE);
		m_combobox[COMBOX_MBTN_MOUSE].UpdateWindow();*/

		// Peter Lee 2017/7/9
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(0);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 1);
		m_list[COMBOX_MBTN_MOUSE].SetCurSel(index);
		m_list[COMBOX_MBTN_MOUSE].Invalidate(TRUE);
		m_list[COMBOX_MBTN_MOUSE].UpdateWindow();
	}
	else if ((index = GetKeyMappingCMBIndex(keyfun)) != -1) // key mapping
	{
		/*m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(2);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 2);
		m_combobox[COMBOX_MBTN_KEYMAPPING].SetCurSel(index);
		m_combobox[COMBOX_MBTN_KEYMAPPING].Invalidate(TRUE);
		m_combobox[COMBOX_MBTN_KEYMAPPING].UpdateWindow();*/

		// Peter Lee 2017/7/9
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(1);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 2);
		m_list[COMBOX_MBTN_KEYMAPPING].SetCurSel(index);
		m_list[COMBOX_MBTN_KEYMAPPING].Invalidate(TRUE);
		m_list[COMBOX_MBTN_KEYMAPPING].UpdateWindow();
	}
	else if ((index = GetMacroCMBIndex(keyfun)) != -1) // macro
	{
		/*m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(3);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 3);
		m_combobox[COMBOX_MBTN_MACRO].SetCurSel(index);
		m_combobox[COMBOX_MBTN_MACRO].Invalidate(TRUE);
		m_combobox[COMBOX_MBTN_MACRO].UpdateWindow();*/

		// Peter Lee 2017/7/9
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(2);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 3);
		m_list[COMBOX_MBTN_MACRO].SetCurSel(index);
		m_list[COMBOX_MBTN_MACRO].Invalidate(TRUE);
		m_list[COMBOX_MBTN_MACRO].UpdateWindow();
	}
	else if ((index = GetMultimediaCMBIndex(keyfun)) != -1) // multimedia
	{
		/*m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(5);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 5);
		m_combobox[COMBOX_MBTN_HOTKEY].SetCurSel(index);
		m_combobox[COMBOX_MBTN_HOTKEY].Invalidate(TRUE);
		m_combobox[COMBOX_MBTN_HOTKEY].UpdateWindow();*/

		// Peter Lee 2017/7/9
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(4);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 5);
		m_list[COMBOX_MBTN_HOTKEY].SetCurSel(index);
		m_list[COMBOX_MBTN_HOTKEY].Invalidate(TRUE);
		m_list[COMBOX_MBTN_HOTKEY].UpdateWindow();
	}
	else if ((index = GetMultiKeyCMBIndex(keyfun)) != -1) // multi key
	{
		m_combobox[COMBOX_MBTN_DEFAULTSETTING].SetCurSel(4);
		SwitchLeftBtn(COMBOX_MBTN_DEFAULTSETTING, 4);
		m_hotkeY.SetHotKey(keyfun.value.keyboard.keyCode, keyfun.value.keyboard.keyModifier);
		showMultiKey();
	}

}

// LRESULT CMouseButtonDlg::OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam)
// {
// 	int nPanelId = (int)wParam;
// 	int nPanelItem = (int)lParam;
// 	switch(nPanelId)
// 	{
// 	case PAN_MOUSE_BUTTONS_LEFT_NAV:
// 		{
// 			switch (lParam)
// 			{
// 			case 0:
// 				EnableLeftPanelOne(-1);
// 				break;
// 			default:
// 				SwitchLeftBtn(wParam, lParam);
// 				break;
// 			}
// 		}
// 		break;
// 	}
// 	return 1;
// }


void CMouseButtonDlg::SwitchLeftBtn(WPARAM wParam, LPARAM lParam)
{
	int nPanelId = (int)wParam;
	int nPanelItem = (int)lParam;


	m_stc[STC_MBTN_MOUSE].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_KEYMAPPING].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_MACRO].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_MULTIKEY].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_MUTILMEDIA].ShowWindow(SW_HIDE);
	m_stc[STC_MBTN_DEFAULT].ShowWindow(SW_HIDE);

	switch(nPanelId)
	{
	case COMBOX_MBTN_DEFAULTSETTING:
		{
			switch (lParam)
			{
			case 1:
				m_stc[STC_MBTN_MOUSE].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(COMBOX_MBTN_MOUSE);
				break;
			case 2:
				m_stc[STC_MBTN_KEYMAPPING].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(COMBOX_MBTN_KEYMAPPING);
				break;
			case 3:
				m_stc[STC_MBTN_MACRO].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(COMBOX_MBTN_MACRO);
				break;
			case 4:
				m_stc[STC_MBTN_MULTIKEY].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(HOT_KEY_ID);
				break;
			case 5:
				m_stc[STC_MBTN_MUTILMEDIA].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(COMBOX_MBTN_HOTKEY);
				break;
			case 6:
				m_stc[STC_MBTN_DEFAULT].ShowWindow(SW_SHOW);
				EnableLeftPanelOne(-1);
				break;
			}
		}
		break;
	}
}


void CMouseButtonDlg::EnableLeftPanelOne(int curSel)
{
	/*for (int i = COMBOX_MBTN_MOUSE; i <= COMBOX_MBTN_HOTKEY; i++)
	{
		if(i != curSel)  m_combobox[i].SetWindowText(_T("SELECT"));
		m_combobox[i].Enable(false);
		m_combobox[i].Invalidate(TRUE);
		m_combobox[i].UpdateWindow();
	}
	m_hotkeY.EnableWindow(FALSE);*/

	if (curSel == -1)
	{
		return;
	}

	if (curSel == HOT_KEY_ID)
	{
		m_hotkeY.EnableWindow(TRUE);
		m_hotkeY.SetBkColor(CLR_ENABLE);
	} 
	else
	{
		m_combobox[curSel].Enable(true);
		m_hotkeY.SetBkColor(CLR_DARK);
	}
}

GVORDER_KEYFUN CMouseButtonDlg::GetDefaultKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_DEFAULT;
	return keyfun;
}
GVORDER_KEYFUN CMouseButtonDlg::GetMouseKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
	case 0: // Left Click"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= VM_LEFT;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 1: // Right Click"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= VM_RIGHT;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 2: // Middle Click"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= VM_MIDDLE;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 3: // Browser Forward"  4
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= VM_BTN_4;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 4: // Browser Backward"  5
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= VM_BTN_5;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;

	case 5: // dpi +
		{
			keyfun.fnType = GVORDER_FUN_PLUSDPI;
			keyfun.value.mouse.msbutton= 0;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 6: // dpi -
		{
			keyfun.fnType = GVORDER_FUN_SUBDPI;
			keyfun.value.mouse.msbutton= 0;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = 0;
		}
		break;
	case 7: // Forward Scroll"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= 0;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = VM_UP_SCROLL;
		}
		break;
	case 8: // Backward Scroll"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= 0;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = VM_DOWN_SCROLL;
		}
		break;
	}
	return keyfun;
}
GVORDER_KEYFUN CMouseButtonDlg::GetKeyMappingKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
	case 0:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_0;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 1:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_1;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 2:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_2;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 3:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_3;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 4:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_4;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 5:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_5;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 6:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_6;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 7:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_7;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 8:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_8;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 9:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_9;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;
		//===================================================================
	case 10:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_A;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 11:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_B;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 12:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_C;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 13:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_D;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 14:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_E;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 15:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 16:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_G;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 17:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_H;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 18:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_I;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 19:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_J;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 20:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_K;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 21:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_L;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 22:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_M;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 23:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_N;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 24:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_O;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 25:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_P;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 26:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_Q;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 27:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_R;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 28:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_S;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 29:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_T;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 30:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_U;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 31:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_V;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 32:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_W;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 33:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_X;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 34:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_Y;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 35:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_Z;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;
		//===================================================================
	case 36:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F1;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 37:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F2;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 38:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F3;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 39:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F4;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 40:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F5;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 41:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F6;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 42:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F7;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 43:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F8;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 44:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F9;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 45:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F10;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 46:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F11;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 47:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_F12;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;
		//===================================================================
	case 48:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD0;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 49:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD1;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 50:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD2;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 51:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD3;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 52:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD4;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 53:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD5;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 54:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD6;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 55:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD7;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 56:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD8;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;

	case 57:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode= VK_NUMPAD9;
			keyfun.value.keyboard.keyModifier = 0;
		}
		break;
		//===================================================================
		// L Shift
	case 58:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_LSHIFT;
		}
		break;
		// L Ctrl
	case 59:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;

		}
		break;
		// L Alt
	case 60:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_LMENU;

		}
		break;
		//Enter
	case 61:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_RETURN;
			keyfun.value.keyboard.keyModifier = 0;

		}
		break;
		// R Shift
	case 62:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_RSHIFT;

		}
		break;
		// R Ctrl
	case 63:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_RCONTROL;

		}
		break;
		// R Alt
	case 64:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_RMENU;

		}
		break;

		// Win
	case 65:
		{	
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = 0;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;
	}
	return keyfun;
}
GVORDER_KEYFUN CMouseButtonDlg::GetMacroKeyFun(int index)
{
	GVORDER_KEYFUN fun;
	fun.fnType = GVORDER_FUN_NONE;
	//取出marco
	GVORDER_MACROS macros = m_validMacros[index];
	/*macros.nIndex = index;
	GvOrderGetMacrosKey(macros, s_MouseIndex);*/

	if (MacroIsValid(macros.attr))
	{
		switch(macros.attr.RunType)
		{
		case 0:
			fun.fnType = GVORDER_FUN_MACROSONCE;
			break;
		case 1:
			fun.fnType = GVORDER_FUN_MACROCSFIRE;
			break;
		case 2:
			fun.fnType = GVORDER_FUN_MACROSLOOP;
			break;
		}
		fun.value.macros.type = macros.attr.RunType + 6;
		fun.value.macros.macrosIndex = macros.nIndex;
	}
	return fun;
}

//GVORDER_KEYFUN CMouseButtonsDlg::GetApplicationKeyFun(int index)
//{
//}
//GVORDER_KEYFUN CMouseButtonsDlg::GetProfileKeyFun(int index)
//{
//}
GVORDER_KEYFUN CMouseButtonDlg::GetMultimediaKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
	//9: Calculator
	case 0:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_CACULATOR;
		}
		break;

		//10: Double Click
	case 1:
		{
			keyfun.fnType = GVORDER_FUN_MOUSELOOP;
			keyfun.value.mouseloop.msbutton = 1;
			keyfun.value.mouseloop.times = 2;
			keyfun.value.mouseloop.delay = 5;
		}
		break;

		//12: Restore(Ctrl+Z;
	case 2:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD; // 類型，是鍵盤還是鼠標之類的
			keyfun.value.keyboard.keyCode = VK_Z;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL; // Shelse ift\Ctrl之類的，沒有就傳0
		}
		break;

		//13: Cut(Ctrl+X;
	case 3:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_X;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//14: Copy(Ctrl+C;
	case 4:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_C;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//15: Paste(Ctrl+V;
	case 5:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_V;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//16: ADD New(Ctrl+N;
	case 6:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_N;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//17: Close(Ctrl+W;
	case 7:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_W;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//18: Open(Ctrl+O;
	case 8:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_O;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//19: Minimize
	case 9:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_DOWN;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//20: Maximize
	case 10:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_UP;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//21: Zoom In
	case 11:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_SUBTRACT;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//22: Zoom Out
	case 12:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ADD;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//23: Close Program
	case 13:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_F4;
			keyfun.value.keyboard.keyModifier = VK_LMENU;
		}
		break;

		//24: Volume Up
	case 14:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_VOLUP;
		}
		break;	
		//25: Volume Down
	case 15:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_VOLDOWN;
		}
		break;	
		//26: Mute
	case 16:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MUTE;
		}
		break;

		//31: Magnelse ifier
	case 17:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ADD;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//32: Desktop
	case 18:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_D;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//33: Internet Explorer
	case 19:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_BROWSER;
		}
		break;	
		//34: Browser Favorites
	case 20:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_D;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//35: Previous Window
	case 21:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ESCAPE;
			keyfun.value.keyboard.keyModifier = VK_LMENU;
		}
		break;

		//36: E-mail
	case 22:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_EMAIL;
		}
		break;

		//37: Play/Pause
	case 23:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_PLAY;
		}
		break;	
		//38: Previous
	case 24:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_PREV;
		}
		break;	
		//39: Next
	case 25:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_NEXT;
		}
		break;

		// MEDIA PLAYER
	case 26:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MEDIAPLAYER;
		}
		break;	
		// Mode Key
	case 27:
		{
			keyfun.fnType = GVORDER_FUN_SWITCHPRO;
		}
		break;			
		// DPI Loop
	case 28:
		{
			keyfun.fnType = GVORDER_FUN_LOOPDPI;
		}
		break;			
		// Lock DPI(Firekey;
	case 29:
		{
			keyfun.fnType = GVORDER_FUN_FIREDPI;
		}
		break;
		// Lock DPI(Toggle;
	case 30:
		{
			keyfun.fnType = GVORDER_FUN_SWITCHDPI;

			keyfun.value.dpi.x = 500;
			keyfun.value.dpi.y = 500;
		}
		break;	
	}
		return keyfun;

}
//GVORDER_KEYFUN CMouseButtonsDlg::GetShortCutKeyFun(int index)
//{
//}

// 默認的按鍵只有原始按鍵，取得按鍵的index，再去數組中取得其在數組中的index。
int CMouseButtonDlg::GetDefaultIndex(GVORDER_KEYFUN keyfun)
{
	for (int i = 0; i < 7; i++)
	{
		if ((keyfun.fnType == GVORDER_FUN_DEFAULT || keyfun.fnType == 255) && keyfun.nIndex == key_index[i])
		{
			return i;
		}
	}
	return -1;
}

// 取得keyfun的名稱
CString CMouseButtonDlg::GetKeyFunName(GVORDER_KEYFUN keyfun)
{
	int index = 0;
	CString s = _T("");
	// Default
	if ((index = GetDefaultIndex(keyfun)) != -1) // 如果該按鍵存儲的是基本按鍵，而且選中的和存儲的都是一致的，則為Default
	{
		s = s_btnDefault[index];
	}
	else if ((index = GetMouseCMBIndex(keyfun)) != -1) // mouse
	{
		s = s_MouseKey[index];
	}
	else if ((index = GetKeyMappingCMBIndex(keyfun)) != -1) // key mapping
	{
		s = s_KeyMapping[index];
	}
	else if ((index = GetMacroCMBIndex(keyfun)) != -1) // macro
	{
		for (int i = 0; i < m_nValidMacroCount; i++)
		{
			if(m_validMacros[i].nIndex == keyfun.value.macros.macrosIndex)
			{
				s= m_validMacros[i].attr.szName;
			}
		}
	}
	else if ((index = GetMultimediaCMBIndex(keyfun)) != -1) // multimedia
	{
		s = s_sMultiMedia[index];
	}
	else if ((index = GetMultiKeyCMBIndex(keyfun)) != -1) // multi key
	{
		m_hotkeY.SetHotKey(keyfun.value.keyboard.keyCode, keyfun.value.keyboard.keyModifier);
		s = m_hotkeY.GetHotKeyName();
		m_hotkeY.SetHotKey(0, 0);
	}
	//else if ((index = GetApplicationCMBIndex(keyfun)) != -1) // Application
	//{
	//}
	//else if ((index = GetProfileCMBIndex(keyfun)) != -1) // profile
	//{
	//}
	//else if ((index = GetShortCutCMBIndex(keyfun)) != -1) // shortcut
	//{
	//}
	return s;
}

// 判斷按鍵是否屬於Mouse，是則返回其index，不是返回-1
int CMouseButtonDlg::GetMouseCMBIndex(GVORDER_KEYFUN keyfun)
{
	//0: Left Click
	if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== VM_LEFT &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == 0)
		return 0;
	//1: Right Click
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== VM_RIGHT &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == 0)
		return 1;
	//2: Middle Click
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== VM_MIDDLE &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == 0)
		return 2;
	//3: Browser Forward  4
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== VM_BTN_4 &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == 0)
		return 3;
	//4: Browser Backward  5
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== VM_BTN_5 &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == 0)
		return 4;
	//5: DPI + 
	else if(
		keyfun.fnType == GVORDER_FUN_PLUSDPI)
		return 5;
	//6: DPI -
	else if(
		keyfun.fnType == GVORDER_FUN_SUBDPI)
		return 6;

	//7: Forward Scroll
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== 0 &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == VM_UP_SCROLL)
		return 7;
	//8: Backward Scroll
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSE &&
		keyfun.value.mouse.msbutton== 0 &&
		keyfun.value.mouse.tiltcount == 0 &&
		keyfun.value.mouse.wheelcount == VM_DOWN_SCROLL)
		return 8;
	else
		return -1;
}



// 判斷按鍵是否屬於key mapping，是則返回其index，不是返回-1
int CMouseButtonDlg::GetKeyMappingCMBIndex(GVORDER_KEYFUN keyfun)
{
	//  0 - 9
	if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_0 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 0;
	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_1 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 1;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_2 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 2;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_3 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 3;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_4 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 4;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_5 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 5;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_6 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 6;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_7 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 7;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_8 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 8;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_9 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 9;

	//  0 - 9 end ------------------------------------------------------

	//  A - Z  ------------------------------------------------------

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_A &&
		keyfun.value.keyboard.keyModifier == 0)
		return 10;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_B &&
		keyfun.value.keyboard.keyModifier == 0)
		return 11;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_C &&
		keyfun.value.keyboard.keyModifier == 0)
		return 12;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_D &&
		keyfun.value.keyboard.keyModifier == 0)
		return 13;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_E &&
		keyfun.value.keyboard.keyModifier == 0)
		return 14;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F &&
		keyfun.value.keyboard.keyModifier == 0)
		return 15;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_G &&
		keyfun.value.keyboard.keyModifier == 0)
		return 16;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_H &&
		keyfun.value.keyboard.keyModifier == 0)
		return 17;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_I &&
		keyfun.value.keyboard.keyModifier == 0)
		return 18;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_J &&
		keyfun.value.keyboard.keyModifier == 0)
		return 19;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_K &&
		keyfun.value.keyboard.keyModifier == 0)
		return 20;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_L &&
		keyfun.value.keyboard.keyModifier == 0)
		return 21;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_M &&
		keyfun.value.keyboard.keyModifier == 0)
		return 22;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_N &&
		keyfun.value.keyboard.keyModifier == 0)
		return 23;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_O &&
		keyfun.value.keyboard.keyModifier == 0)
		return 24;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_P &&
		keyfun.value.keyboard.keyModifier == 0)
		return 25;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_Q &&
		keyfun.value.keyboard.keyModifier == 0)
		return 26;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_R &&
		keyfun.value.keyboard.keyModifier == 0)
		return 27;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_S &&
		keyfun.value.keyboard.keyModifier == 0)
		return 28;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_T &&
		keyfun.value.keyboard.keyModifier == 0)
		return 29;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_U &&
		keyfun.value.keyboard.keyModifier == 0)
		return 30;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_V &&
		keyfun.value.keyboard.keyModifier == 0)
		return 31;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_W &&
		keyfun.value.keyboard.keyModifier == 0)
		return 32;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_X &&
		keyfun.value.keyboard.keyModifier == 0)
		return 33;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_Y &&
		keyfun.value.keyboard.keyModifier == 0)
		return 34;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_Z &&
		keyfun.value.keyboard.keyModifier == 0)
		return 35;

	//  A - Z end ------------------------------------------------------

	//  F1 - f12  ------------------------------------------------------

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F1 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 36;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F2 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 37;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F3 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 38;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F4 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 39;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F5 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 40;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F6 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 41;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F7 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 42;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F8 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 43;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F9 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 44;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F10 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 45;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F11 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 46;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F12 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 47;

	//  F1 - f12  END------------------------------------------------------

	//  NUM0 - NUM9  ------------------------------------------------------

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD0 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 48;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD1 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 49;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD2 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 50;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD3 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 51;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD4 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 52;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD5 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 53;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD6 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 54;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD7 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 55;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD8 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 56;

	else if (keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_NUMPAD9 &&
		keyfun.value.keyboard.keyModifier == 0)
		return 57;

	//  NUM0 - NUM9 END ------------------------------------------------------

	// L Shift
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_LSHIFT)
		return 58;
	// L Ctrl
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 59;
	// L Alt
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_LMENU)
		return 60;
	//Enter
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_RETURN &&
		keyfun.value.keyboard.keyModifier == 0)
		return 61;
	// R Shift
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_RSHIFT)
		return 62;
	// R Ctrl
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_RCONTROL)
		return 63;
	// R Alt
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_RMENU)
		return 64;

	// Win
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == 0 &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 65;
	else
		return -1;
}

// 判斷按鍵是否屬於Macro，是則返回其index，不是返回-1
int CMouseButtonDlg::GetMacroCMBIndex(GVORDER_KEYFUN keyfun)
{
	if(
		keyfun.fnType !=  GVORDER_FUN_MACROSONCE &&
		keyfun.fnType !=  GVORDER_FUN_MACROSLOOP &&
		keyfun.fnType !=  GVORDER_FUN_MACROCSFIRE) // 不是marco
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < MACRO_COUNT; i++)
		{
			GVORDER_MACROS m = m_validMacros[i];
			if (m.nIndex == keyfun.value.macros.macrosIndex)
			{
				return i;
			}
		}
		return 0;
	}
}

// 判斷按鍵是否屬於熱鍵，是則返回其index，不是返回-1
int CMouseButtonDlg::GetMultiKeyCMBIndex(GVORDER_KEYFUN keyfun)
{
	// L Shift +
	if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_LSHIFT)
		return 0;
		// L Ctrl +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 1;
	// L Alt +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_LMENU)
		return 2;
	// R Shift +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_RSHIFT)
		return 3;
	// R Ctrl +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_RCONTROL)
		return 4;
	// R Alt +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_RMENU)
		return 5;
	// Win+
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 6;
	// Shift +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier & MOD_SHIFT)
		return 7;
	// Ctrl +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier & MOD_CONTROL)
		return 8;
	// Alt +
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode != 0 &&
		keyfun.value.keyboard.keyModifier & MOD_ALT)
		return 9;
	else
		return -1;
}


// 判斷按鍵是否屬於application，是則返回其index，不是返回-1
int CMouseButtonDlg::GetApplicationCMBIndex(GVORDER_KEYFUN keyfun)
{
	return -1;
}
// 判斷按鍵是否屬於profile，是則返回其index，不是返回-1
int CMouseButtonDlg::GetProfileCMBIndex(GVORDER_KEYFUN keyfun)
{
	return -1;
}

// 判斷按鍵是否屬於Multimedia，是則返回其index，不是返回-1
int CMouseButtonDlg::GetMultimediaCMBIndex(GVORDER_KEYFUN keyfun)
{
	//9: Calculator
	if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_CACULATOR)
		return 0;

	//10: Double Click
	else if(
		keyfun.fnType == GVORDER_FUN_MOUSELOOP &&
		keyfun.value.mouseloop.msbutton == 1 &&
		keyfun.value.mouseloop.times == 2 &&
		keyfun.value.mouseloop.delay == 5)
		return 1;

	//12: Restore(Ctrl+Z)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD && // 類型，是鍵盤還是鼠標之類的
		keyfun.value.keyboard.keyCode == VK_Z &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL // Shelse ift\Ctrl之類的，沒有就傳0
		)
		return 2;
	//13: Cut(Ctrl+X)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_X &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 3;
	//14: Copy(Ctrl+C)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_C &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 4;
	//15: Paste(Ctrl+V)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_V &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 5;
	//16: ADD New(Ctrl+N)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_N &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 6;
	//17: Close(Ctrl+W)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_W &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 7;
	//18: Open(Ctrl+O)
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_O &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 8;

	//=================================================================================

	//19: Minimize
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_DOWN &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 9;
	//20: Maximize
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_UP &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 10;

	//21: Zoom In
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_SUBTRACT &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 11;
	//22: Zoom Out
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_ADD &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 12;

	//23: Close Program
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_F4 &&
		keyfun.value.keyboard.keyModifier == VK_LMENU)
		return 13;
	//24: Volume Up
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_VOLUP)
		return 14;
	//25: Volume Down
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_VOLDOWN)
		return 15;
	//26: Mute
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_MUTE)
		return 16;

	//=============================================================================

	//31: Magnelse ifier
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_ADD &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 17;
	//32: Desktop
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_D &&
		keyfun.value.keyboard.keyModifier == VK_LWIN)
		return 18;
	//33: Internet Explorer
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_BROWSER)
		return 19;
	//34: Browser Favorites
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_D &&
		keyfun.value.keyboard.keyModifier == VK_LCONTROL)
		return 20;
	//35: Previous Window
	else if(
		keyfun.fnType == GVORDER_FUN_KEYBOARD &&
		keyfun.value.keyboard.keyCode == VK_ESCAPE &&
		keyfun.value.keyboard.keyModifier == VK_LMENU)
		return 21;
	//36: E-mail
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_EMAIL)
		return 22;

	//=============================================================================

	//37: Play/Pause
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_PLAY)
		return 23;
	//38: Previous
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_PREV)
		return 24;
	//39: Next
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_NEXT)
		return 25;

	// MEDIA PLAYER
	else if(
		keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_MEDIAPLAYER)
		return 26;
	// Mode Key
	else if(
		keyfun.fnType == GVORDER_FUN_SWITCHPRO)
		return 27;
	// DPI Loop
	else if(
		keyfun.fnType == GVORDER_FUN_LOOPDPI)
		return 28;
	// Lock DPI(Firekey)
	else if(
		keyfun.fnType == GVORDER_FUN_FIREDPI)
		return 29;
	// Lock DPI(Toggle)
	else if(
		keyfun.fnType == GVORDER_FUN_SWITCHDPI)
		return 30;
	else 
		return -1;
}

// 判斷按鍵是否屬於ShortCut是則返回其index，不是返回-1
int CMouseButtonDlg::GetShortCutCMBIndex(GVORDER_KEYFUN keyfun)
{
	return -1;
}

BOOL CMouseButtonDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE)) //攔截enter和esc按鍵
	{
		return TRUE; // 攔截消息
	}
	return CUiDlg::PreTranslateMessage(pMsg);
}

void CMouseButtonDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if (bShow)
	{
		m_hotkeY.SetFocus();
		InitProfile();
		OnUiComboBoxSelChanged(COMBOX_MBTN_PROFILE, s_nCurProfile.nProfile);
		m_combobox[COMBOX_MBTN_PROFILE].SetCurSel(s_nCurProfile.nProfile);
	}

	CWnd::OnShowWindow(bShow, nStatus);
}

void CMouseButtonDlg::InitProfile()
{
	int m_nProSel; 
	int nDevices = 1; 
	int m_nDevice = DEVICE_AM300;
	if (DEVICE_VGA == m_nDevice)
	{
		CVGA* pVGA = (CVGA*)Aorus()->GetDevice(DEVICE_VGA);
		nDevices = pVGA->Ctrl()->GetGpuCount();
	}

	LED_SETTING ledCur;
	for (int i = 0; i < nDevices; i++)
	{
		int nProSel = 0;
		CArray<LED_SETTING> profiles;
		Aorus()->GetCfg()->GetLedProfiles(m_nDevice, profiles, nProSel, i);
		if ((int)profiles.GetSize() <= 0)
		{
			m_nProSel = 0;
			LED_SETTING ledNew;
			ledNew.sProfileName = "Profile1";
			profiles.Add(ledNew);
		}

		for(int k = 0; k < (int)profiles.GetSize(); k++)
		{
			LED_SETTING ledP = profiles.GetAt(k);
			m_btnProfiles[0][k] = ledP;
		}

		m_combobox[COMBOX_MBTN_PROFILE].ResetContent();
		for (int i =0; i < LED_PROFILE_CONT; i++)
		{
			m_combobox[COMBOX_MBTN_PROFILE].AddString(m_btnProfiles[0][i].sProfileName, 0, CLR_MAIN);

		}
	}
	m_combobox[COMBOX_MBTN_PROFILE].SetCurSel(s_nCurProfile.nProfile);

}

LRESULT CMouseButtonDlg::OnNewPaint(WPARAM wParam, LPARAM lParam)
{
	CString name = m_hotkeY.GetHotKeyName();
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

	m_stc[STC_MBTN_MULTIKEYONE].SetCaption(strOne);
	m_stc[STC_MBTN_MULTIKEYTWO].SetCaption(strTwo);
	m_stc[STC_MBTN_MULTIKEYTHREE].SetCaption(strThree);

	return 1;
}