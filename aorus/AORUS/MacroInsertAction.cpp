// InsertActionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AORUS.h"
#include "AORUSDlg.h"
#include "MacroInsertAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  LANG_MS	0
#define  LANG_KEYBOARD 1
#define  LANG_MOUSE 2
#define LANG_LOCATION 3
#define LKEY_QTY				4
int CInsertActionDlg::s_nWords = LKEY_QTY;
LANG_WORD CInsertActionDlg::s_Words[48] = 
{
	LANG_WORD(LANG_MS,		_T("毫秒"), _T("毫秒"), _T("MS")),
	LANG_WORD(LANG_KEYBOARD,		_T("键盘"), _T("鍵盤"), _T("KEYBOARD")),
	LANG_WORD(LANG_MOUSE,		_T("鼠标"), _T("滑鼠"), _T("MOUSE")),
	LANG_WORD(LANG_LOCATION,			_T("位置"), _T("指標"), _T("LOCATION")),
};
// CInsertActionDlg dialog

CInsertActionDlg::CInsertActionDlg(CWnd* pParent /*=NULL*/)
: CUiDlg(CInsertActionDlg::IDD, pParent)
{
	m_bRecord = false;
	m_nType = 0;
	m_pt = CPoint(0, 0);
}

void CInsertActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInsertActionDlg, CUiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UI_PANEL_SELCHANGE, OnUiPanelSelChanged)
	//}}AFX_MSG_MAP
	ON_WM_INPUT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CInsertActionDlg message handlers

BOOL CInsertActionDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);// 窗口不會顯示在系統任務欄

	Ui();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInsertActionDlg::OnPaint()
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
HCURSOR CInsertActionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CInsertActionDlg::Ui()
{

	UiMain();
}

void CInsertActionDlg::UiMain()
{
	SetBkBitmap(IDB_INSERT_ACTION_BG, 0xff, CLR_TRPT); // 设置背景图

	m_stc[STC_INSERT_FUN_SWITCH].CreateStatic(UI_STATIC(this, STC_INSERT_FUN_SWITCH,  CRect(0, 0, 154, 100), _T("")));
//	m_stc[STC_INSERT_FUN_KB].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_SWITCH],   STC_INSERT_FUN_LOCATION,    CRect(135, 65, 229, 81), _T("")));
	m_stc[STC_INSERT_FUN_KB].CreateStatic(UI_STATIC(this, STC_INSERT_FUN_KB, CRect(0, 0, 154, 100), _T("Press any key to insert")));
 	m_stc[STC_INSERT_FUN_KB].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_KB].ModifyCtrlStyle(0, ST_VCENTER | ST_CENTER | ST_SINGLELINE);
 	m_stc[STC_INSERT_FUN_KB].ShowWindow(SW_HIDE);

 	m_stc[STC_INSERT_FUN_MOUSE].CreateStatic(UI_STATIC(this, STC_INSERT_FUN_MOUSE, CRect(0, 0, 154, 100), _T("Click any button to insert")));
 	m_stc[STC_INSERT_FUN_MOUSE].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_MOUSE].ModifyCtrlStyle(0, ST_VCENTER | ST_CENTER | ST_SINGLELINE);
 	m_stc[STC_INSERT_FUN_MOUSE].ShowWindow(SW_HIDE);

	m_stc[STC_INSERT_FUN_LOCATION].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_SWITCH],   STC_INSERT_FUN_LOCATION,    CRect(45, 75, 150, 91), _T("")));
 	m_stc[STC_INSERT_FUN_LOCATION_X].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_LOCATION], STC_INSERT_FUN_LOCATION_X,  CRect(  0,  0,  15, 16), _T("x:")));
 	m_stc[STC_INSERT_FUN_LOCATION_Y].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_LOCATION], STC_INSERT_FUN_LOCATION_Y,  CRect( 46,  0,  66, 16), _T(",y:")));
 	
 	m_stc[STC_INSERT_FUN_LOCATION_X].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_LOCATION_X].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
 	m_stc[STC_INSERT_FUN_LOCATION_Y].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_LOCATION_Y].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
 
 	m_stc[STC_INSERT_FUN_LOCATION].ShowWindow(SW_HIDE);

	m_stc[STC_INSERT_FUN_DELAY].CreateStatic(UI_STATIC(this, STC_INSERT_FUN_DELAY, CRect(0, 0, 154, 100), _T("")));
 
 	m_stc[STC_INSERT_FUN_DELAY_WORD].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_DELAY], STC_INSERT_FUN_DELAY_WORD, CRect(10, 40, 185, 55), _T("Insert the delay time :")));
 	m_stc[STC_INSERT_FUN_DELAY_WORD].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_DELAY_WORD].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
 
 	m_stc[STC_INSERT_FUN_DELAY_TIME].CreateStatic(UI_STATIC(&m_stc[STC_INSERT_FUN_DELAY], STC_INSERT_FUN_DELAY_TIME, CRect(42, 55, 62, 70), CLangX::Get(s_Words, s_nWords, LANG_MS)));
 	m_stc[STC_INSERT_FUN_DELAY_TIME].SetFont(Font(11), CLR_WHITE);
 	m_stc[STC_INSERT_FUN_DELAY_TIME].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);

  	m_edit[EDIT_INSERT_FUN_X].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(15, 0, 0, 0), &m_stc[STC_INSERT_FUN_LOCATION], EDIT_INSERT_FUN_X);
  	m_edit[EDIT_INSERT_FUN_X].SetFont(Font(10), CLR_WHITE);
  	m_edit[EDIT_INSERT_FUN_X].SetBkBitmap(IDB_EDT_INSERT_LINE, TRUE);
  	m_edit[EDIT_INSERT_FUN_X].SetAsIntNumberEdit(4);
  
  	m_edit[EDIT_INSERT_FUN_Y].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(66, 0, 0, 0), &m_stc[STC_INSERT_FUN_LOCATION], EDIT_INSERT_FUN_Y);
  	m_edit[EDIT_INSERT_FUN_Y].SetFont(Font(10), CLR_WHITE);
  	m_edit[EDIT_INSERT_FUN_Y].SetBkBitmap(IDB_EDT_INSERT_LINE, TRUE);
  	m_edit[EDIT_INSERT_FUN_Y].SetAsIntNumberEdit(4);
 
 	m_edit[EDIT_INSERT_FUN_MS].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(10, 55, 42, 71), &m_stc[STC_INSERT_FUN_DELAY], EDIT_INSERT_FUN_MS);//185, 40, 217, 56
 	m_edit[EDIT_INSERT_FUN_MS].SetFont(Font(11), CLR_WHITE);
 	m_edit[EDIT_INSERT_FUN_MS].SetBkBitmap(IDB_EDT_INSERT_LINE, TRUE);
 	m_edit[EDIT_INSERT_FUN_MS].SetAsIntNumberEdit(5);
 	
	m_panel.Create(&m_stc[STC_INSERT_FUN_SWITCH], PAN_INSERT_FUN_SWITCH, CRect(0, 0, 100, 65));//100 92
 	m_panel.AddItem(&UIPC_ITEM(0, CRect(10, 10, 50, 22), &UIPC_IMAGE(IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_CHECKED, CLR_TRPT), &UIPC_STRING(CLangX::Get(s_Words, s_nWords, LANG_KEYBOARD),	CLR_WHITE, CLR_MAIN, CLR_MAIN, Font(10),  Font(10),  Font(10))));
 	m_panel.AddItem(&UIPC_ITEM(1, CRect(10, 30, 50, 42), &UIPC_IMAGE(IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_CHECKED, CLR_TRPT), &UIPC_STRING(CLangX::Get(s_Words, s_nWords, LANG_MOUSE),		CLR_WHITE, CLR_MAIN, CLR_MAIN,  Font(10),  Font(10),  Font(10))));
 	m_panel.AddItem(&UIPC_ITEM(2, CRect(10, 50, 50, 62), &UIPC_IMAGE(IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_UNCHECKED, IDB_PAN_INSERT_CHECKED, CLR_TRPT), &UIPC_STRING(CLangX::Get(s_Words, s_nWords, LANG_LOCATION),	CLR_WHITE, CLR_MAIN, CLR_MAIN,  Font(10),  Font(10),  Font(10))));
 	m_panel.SetCursor(IDC_CUR_HAND);
 	m_panel.SetCurItem(-1);

 	CRect c;
 	GetParent()->GetClientRect(&c);
 	GetParent()->ClientToScreen(&c);
 	CRect t;
 	GetWindowRect(t);
 	MoveWindow(c.left + 695, c.top + 365, t.Width(), t.Height());
 
 	m_stc[STC_INSERT_FUN_SWITCH].ShowWindow(4 != m_nType ? SW_SHOW : SW_HIDE);
 	m_stc[STC_INSERT_FUN_DELAY ].ShowWindow(4 == m_nType ? SW_SHOW : SW_HIDE);


}

LRESULT CInsertActionDlg::OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nPanelId = (int)wParam;
	int nPanelItem = (int)lParam;
  	switch(nPanelId)
  	{
  	case PAN_INSERT_FUN_SWITCH: 
  		m_nType = nPanelItem;
  		if(m_nType < 2) RawInputDevices(m_hWnd, m_nType < 1 ? RAW_DEV_KB : RAW_DEV_MS, m_bRecord);
  		m_bRecord = true;
  		m_stc[STC_INSERT_FUN_KB + m_nType].ShowWindow(SW_SHOW);
  		if(m_nType < 2) 
  		{
  			m_stc[STC_INSERT_FUN_SWITCH].ShowWindow(SW_HIDE);
  		}
  		AfxBeginThread(Recode, this); 
  		break;
  	}
	return 1;
}

BOOL CInsertActionDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) //攔截esc按鍵
	{
		OnCancel();
		return TRUE; // 攔截消息
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) //攔截enter按鍵
	{
		switch (GetFocus()->GetDlgCtrlID())
		{
			case EDIT_INSERT_FUN_X:
			case EDIT_INSERT_FUN_Y:
				{
					m_pt = CPoint(m_edit[EDIT_INSERT_FUN_X].GetWindowsValue(), m_edit[EDIT_INSERT_FUN_Y].GetWindowsValue());
					OnOK();
					break;
				}
			case EDIT_INSERT_FUN_MS:
				{
					m_nDelay = m_edit[EDIT_INSERT_FUN_MS].GetWindowsValue();
					//Terry 2017/06/30
					if (m_nDelay >= 60000)
					{
						m_nDelay = 60000;
					}
					OnOK();
					break;
				}
		}
		return TRUE; // 攔截消息
	}
	return CUiDlg::PreTranslateMessage(pMsg);
}

void CInsertActionDlg::OnRawInput(UINT nInputcode, HRAWINPUT hRawInput)
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
				if(mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN
				|| mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN
				|| mouse.usButtonFlags == RI_MOUSE_MIDDLE_BUTTON_DOWN
				|| 0x0078 == mouse.usButtonData
				|| 0xff88 == mouse.usButtonData)
				{
					m_input = *raw;
					m_bRecord = false;
					RawInputDevices(m_hWnd, RAW_DEV_MS, m_bRecord);
					OnOK();
				}
				else if(m_nType >= 2)
				{
					CPoint point;
					GetCursorPos(&point);
					m_edit[EDIT_INSERT_FUN_X].SetWindowsValue(point.x);
					m_edit[EDIT_INSERT_FUN_Y].SetWindowsValue(point.y);
					m_pt = point;
				}
			}
			if (raw->header.dwType == RIM_TYPEKEYBOARD) // 鍵盤
			{
				RAWKEYBOARD keyboard = raw->data.keyboard;
				if (((keyboard.Flags & RI_KEY_BREAK) != RI_KEY_BREAK 
				  && (keyboard.Flags & RI_KEY_MAKE ) == RI_KEY_MAKE )
				  || (keyboard.Flags & RI_KEY_BREAK) == RI_KEY_BREAK)
				{
					m_input = *raw;
					m_bRecord = false;
					RawInputDevices(m_hWnd, RAW_DEV_KB, m_bRecord);
					OnOK();
				}
			}
		}
	}

	CUiDlg::OnRawInput(nInputcode, hRawInput);
}

UINT CInsertActionDlg::Recode(LPVOID pParam)
{
 	CInsertActionDlg* pMain = (CInsertActionDlg*)pParam;
 	Sleep(500);
 	RawInputDevices(pMain->m_hWnd, pMain->m_nType < 1 ? RAW_DEV_KB : RAW_DEV_MS, pMain->m_bRecord);
 	pMain->m_bRecord = true;
 	pMain->m_stc[STC_INSERT_FUN_KB + pMain->m_nType].ShowWindow(SW_SHOW);
	return 0;
}

void CInsertActionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bRecord)
	{
		m_edit[EDIT_INSERT_FUN_X].SetWindowsValue(point.x);
		m_edit[EDIT_INSERT_FUN_Y].SetWindowsValue(point.y);
	}
	CUiDlg::OnMouseMove(nFlags, point);
}

