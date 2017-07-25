// KBBaseDlg.cpp : implementation file

#include "stdafx.h"
#include "AORUS.h"
#include "KeyAssignDlg.h"
#include "AORUSDlg.h"


#define KEYs_107	107	// 107 Keys

// Location of AK700's keys
extern CRect s_KeysAK700[KEYs_107];

// CKeyAssignDlg dialog

IMPLEMENT_DYNAMIC(CKeyAssignDlg, CUiDlg)

CKeyAssignDlg::CKeyAssignDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CKeyAssignDlg::IDD, pParent)
{
	m_curSel = -1;
	m_nKeySel = 0;

}

CKeyAssignDlg::~CKeyAssignDlg()
{
}

void CKeyAssignDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BOOL CKeyAssignDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	return true;
}

BEGIN_MESSAGE_MAP(CKeyAssignDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
	ON_MESSAGE(WM_UI_KEYBOARD_SELCHANGE, OnUiKeyboardSelChanged)
	ON_WM_SHOWWINDOW()
//	ON_WM_INPUT()
	
END_MESSAGE_MAP()


// CKeyAssignDlg message handlers

void CKeyAssignDlg::Ui()
{
	UiMain();
}

void CKeyAssignDlg::UiMain()
{
	SetBkBitmap(IDB_LED_BGCOMMON, 0xff, CLR_TRPT); 

	UI_BTN btn[] = 
	{
	//	UI_BTN(this, BTN_KBASSIGN_PROADD,  CRect(163,  23, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILEOFF)),
		UI_BTN(this, BTN_KBASSIGN_PROEDIT, CRect(183-10,  23, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITOFF, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILEOFF, CLR_TRPT), NULL, BTN_CHECK),
	//	UI_BTN(this, BTN_KBASSIGN_PRODEL,  CRect(203,  23, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_DELETEFILE, IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILEOFF)),
		UI_BTN(this, BTN_KBASSIGN_DEFAULT, CRect(443, 269+20, 0, 0), &UIBTN_IMAGE(IDB_BTN_ON, IDB_BTN_ON, IDB_BTN_ON,   0,  0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_VGALED_DEFAULT),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_KBASSIGN_APPLY,   CRect(324, 269+20, 0, 0), &UIBTN_IMAGE(IDB_BTN_ON, IDB_BTN_ON, IDB_BTN_ON,   0,  0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_VGALED_APPLY),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
	};

	for (int i = BTN_KBASSIGN_PROEDIT; i < BTN_KBASSIGN_NUM; i++)
	{
		m_btn[i].CreateButton(btn[i]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}
// 	m_btn[BTN_KBASSIGN_PROADD].ShowWindow(SW_HIDE);
// 	m_btn[BTN_KBASSIGN_PROEDIT].ShowWindow(SW_HIDE);
// 	m_btn[BTN_KBASSIGN_PRODEL].ShowWindow(SW_HIDE);



	m_combobox[COMBOX_KBASSIGN_PROFILE].Create(CRect(23, 25, 0, 0), this, COMBOX_KBASSIGN_PROFILE);
	m_combobox[COMBOX_KBASSIGN_PROFILE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, 0, CLR_NONE);
	m_combobox[COMBOX_KBASSIGN_PROFILE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_KBASSIGN_PROFILE].SetCursor(IDC_CUR_HAND);
	m_combobox[COMBOX_KBASSIGN_PROFILE].SetArrowWidth(20);
	m_combobox[COMBOX_KBASSIGN_PROFILE].GetDropList()->SetFont(Font(11),CLR_WHITE);
	m_combobox[COMBOX_KBASSIGN_PROFILE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_KBASSIGN_PROFILE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_KBASSIGN_PROFILE].ModifyCtrlStyle(ST_RIGHT, ST_LEFT);

	for (int i = 0; i < 5; i++)
	{
		CString sValue;
		//sValue.Format(CLangX::Get(LANG_PROFILE) + _T("%d"), i+1);
		sValue.Format(_T("PROFILE %d"), i+1);
		m_combobox[COMBOX_KBASSIGN_PROFILE].AddString(sValue, 0, CLR_MAIN);
	}
	m_combobox[COMBOX_KBASSIGN_PROFILE].SetCurSel(0);

	m_edit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, CRect(23,  25, 153,  39), this, EDIT_KEYASSIGN_PROFILENAME);
	m_edit.SetFont(Font(9), CLR_WHITE);
	m_edit.SetBkColor(CLR_DARK);
	m_edit.ShowWindow(SW_HIDE);


	m_StyleDlg.Create(IDD_VGA_MONITORING, GetDesktopWindow());


	m_nKeys = 104; // Default: 104 Keys
	m_KB.CreateKeyboard(UI_KEYBOARD(this, 1, CRect(70, 65, 0, 0), IDB_PAN_KB104_OFF, IDB_PAN_KB104_ON, CLR_MAIN, CLR_TRPT));
	for (int i = 0; i < KEYs_107; i++)
	{
		m_KB.AddItem(&UIKB_RECT(i, s_KeysAK700[i]));
		m_KB.SetItemStatus(i, false);
	}
	m_KB.SetSingle(true);

	// Petter Lee 2017/6/18 need to be assign
	m_nProfileSel = 0;
	CXK700Cmd::ConnectXK700();
}

LRESULT CKeyAssignDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	int index;

	switch(wParam)
	{
//	case BTN_KBASSIGN_PROADD: break;
	case BTN_KBASSIGN_PROEDIT: 
		{
			bool bCheck = m_btn[BTN_KBASSIGN_PROEDIT].IsCheck();
			m_edit.ShowWindow(bCheck ? SW_SHOW : SW_HIDE);
			m_combobox[COMBOX_KBASSIGN_PROFILE].ShowWindow(bCheck ? SW_HIDE : SW_SHOW);

			if (bCheck)
			{
				m_edit.SetWindowText(m_kassignProfile[0][m_nProfileSel].sProfileName);
			}
			else
			{
				CString sName = _T("");
				m_edit.GetWindowText(sName);
				sName.Trim();
				if (_T("") == sName)
				{
					sName = m_kassignProfile[0][m_nProfileSel].sProfileName;
					m_edit.SetWindowText(sName);
				}
				m_kassignProfile[0][m_nProfileSel].sProfileName = sName;
				m_combobox[COMBOX_KBASSIGN_PROFILE].ResetContent();
				for (int i = 0; i < 5; i++)
				{
					m_combobox[COMBOX_KBASSIGN_PROFILE].AddString(m_kassignProfile[0][i].sProfileName, 0, CLR_WHITE);
				}
				m_combobox[COMBOX_KBASSIGN_PROFILE].SetCurSel(m_nProfileSel);

				//保存PROFILE設定
				CArray<LED_SETTING> profiles;
				for (int i = 0; i < LED_PROFILE_CONT; i++)
				{
					profiles.Add(m_kassignProfile[0][i]);
				}

				Aorus()->GetCfg()->SetLedProfiles(DEVICE_AK700, profiles, 0, 0);
			}
			return 1;
		}
		break;
//	case BTN_KBASSIGN_PRODEL: break;
	case BTN_KBASSIGN_APPLY: 


	//	ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
		switch (m_StyleDlg.GetCurStyle())
		{	
		case LKEY_DEFAULT:
			{
				OnSave(SetSingleKeyDefault());
			}
			break;

		case LKEY_MUTILKEY:
			{		
				GVORDER_KEYFUN funkey;
				if (m_StyleDlg.GetMutilKey(funkey))
				{
					OnSave(funkey);
				}
			}
			break;
		case LKEY_TXTINPUT:
			SaveTxtInfor();//保存文本到檔案
			break;
		case LKEY_MOUSEACTION:
			index = m_StyleDlg.GetMouseKeySel();
			OnSave(GetMouseKeyFun(index));
			break;
		case LKEY_FNKEY:	
			index = m_StyleDlg.GetFunctionKeySel();
			OnSave(GetFunctionKeyFun(index));
			break;
		case LKEY_MEDIAPLAYER:
			index = m_StyleDlg.GetMediaPlayerSel();
			OnSave(GetMultimediaKeyFun(index));
			break;
		case LKEY_HOTKEY:
			index = m_StyleDlg.GetHotKeySel();
			OnSave(GetHotKeyFun(index));
			break;
		case LKEY_MACRO:
			index = m_StyleDlg.GetMacroKeySel();
			OnSave(GetMacroKeyFun(index));
			break;
		}
//		ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		break;
	case BTN_KBASSIGN_DEFAULT:
//		ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);

		CmdLock();
		CKbLedCtrl::SetKeyFunToDefault(m_nProfileSel);
		OnUiKeyboardSelChanged(1, m_nKeySel);
		CmdUnLock();
		AfxMessageBox(_T("All key reset to default"));
//		ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);

		break;
	default:break;
	}

	return 1;
}

LRESULT CKeyAssignDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	int nCurSel = (int)lParam; 
	switch(wParam)
	{
	case COMBOX_KBASSIGN_PROFILE: 
		m_nProfileSel = m_combobox[COMBOX_KBASSIGN_PROFILE].GetCurSel();
		SetProfile(m_nProfileSel);

		CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
		pParent->SwitchAK700LedProfile(m_nProfileSel);
		//m_KbAssign.SetProfile(m_nProfileSel);
		break;
	}

	return 1;
}

LRESULT CKeyAssignDlg::OnUiKeyboardSelChanged(WPARAM wParam, LPARAM lParam)
{
	m_nKeySel = (int)lParam; 

	if (!m_StyleDlg.IsWindowVisible())
	{
// 		CRect rcCli;
// 		CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
// 		pParent->GetClientRect(rcCli);
// 		m_StyleDlg.SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
// 		m_StyleDlg.OnFit(rcCli);
//  		int nX = rcCli.left + rcCli.Width();
//  		int nY = rcCli.top + 78;
// 
// 		m_StyleDlg.SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
// 		m_StyleDlg.SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
//		m_StyleDlg.ShowWindow(SW_SHOW);
	}

#if 1 
 	switch(wParam)
 	{
 	case 1: 
 		{
 			GVORDER_KEYFUN keyfun;
 			keyfun.nIndex = s_nKeyFwIndex[m_nKeySel];
 			keyfun.nProfile = m_nProfileSel;
 			CKbLedCtrl::GetKeyFun(keyfun); // 取得這?鍵存儲什麼信息
 			SetBtnInfo(keyfun);
 			break;
 		}
 	}
#endif

	return 1;
}

GVORDER_KEYFUN CKeyAssignDlg::GetHotKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
		//23: Close Program
	case 0:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_F4;
			keyfun.value.keyboard.keyModifier = VK_LMENU;
		}
		break;

		//20: Maximize
//  	case 1:
//  		{
//  			keyfun.fnType = GVORDER_FUN_KEYBOARD;
//  			keyfun.value.keyboard.keyCode = VK_UP;
//  			keyfun.value.keyboard.keyModifier = VK_LWIN;
//  		}
//  		break;

		//19: Minimize
// 	case 2:
// 		{
// 			keyfun.fnType = GVORDER_FUN_KEYBOARD;
// 			keyfun.value.keyboard.keyCode = VK_DOWN;
// 			keyfun.value.keyboard.keyModifier = VK_LWIN;
// 		}
// 		break;

		//32: Desktop
	case 1:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_D;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//14: Next Tab(Ctrl+TAB;
	case 2:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_TAB;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//14: Prev Tab(Ctrl+Shift+TAB;
	case 3:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_TAB;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;	// can not add shift??
		}
		break;

		//14: Restore default zoom(Ctrl+0;
	case 4:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_0;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//14: Copy(Ctrl+C;
	case 5:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_C;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//15: Paste(Ctrl+V;
	case 6:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_V;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

	//13: Cut(Ctrl+X;
	case 7:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_X;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

	//13: Undo(Ctrl+Z;
	case 8:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_Z;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

	//13: Redo(Ctrl+Y;
	case 9:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_Y;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

	/*	// MEDIA PLAYER
	case 0:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MEDIAPLAYER;
		}
		break;	

		//33: Internet Explorer
	case 2:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_BROWSER;
		}
		break;	
		//31: Magnelse ifier
	case 3:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ADD;
			keyfun.value.keyboard.keyModifier = VK_LWIN;
		}
		break;

		//12: Restore(Ctrl+Z;
	case 8:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD; // ?琌龄絃?琌公夹ぇ?
			keyfun.value.keyboard.keyCode = VK_Z;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL; // Shelse ift\Ctrlぇ?⊿Τ碞肚0
		}
		break;

	//	//10: Double Click
	//case 1:
	//	{
	//		keyfun.fnType = GVORDER_FUN_MOUSELOOP;
	//		keyfun.value.mouseloop.msbutton = 1;
	//		keyfun.value.mouseloop.times = 2;
	//		keyfun.value.mouseloop.delay = 5;
	//	}
	//	break;

		//35: Previous Window
	case 9:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ESCAPE;
			keyfun.value.keyboard.keyModifier = VK_LMENU;
		}
		break;

		//22: Zoom Out
	case 10:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_ADD;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//21: Zoom In
	case 11:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_SUBTRACT;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;*/

		//16: ADD New(Ctrl+N;
	/*case 16:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_N;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//17: Close(Ctrl+W;
	case 17:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_W;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//18: Open(Ctrl+O;
	case 18:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_O;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;

		//34: Browser Favorites
	case 19:
		{
			keyfun.fnType = GVORDER_FUN_KEYBOARD;
			keyfun.value.keyboard.keyCode = VK_D;
			keyfun.value.keyboard.keyModifier = VK_LCONTROL;
		}
		break;*/
	}
	return keyfun;
}

GVORDER_KEYFUN CKeyAssignDlg::GetFunctionKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
	case PANEL_FUNKEY_MAIL:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_EMAIL;
		}
		break;
	case PANEL_FUNKEY_WEB:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_BROWSER;
		}
		break;
	case PANEL_FUNKEY_MEDIAPLAY:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MEDIAPLAYER;
		}
		break;
	case PANEL_FUNKEY_MUTE:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MUTE;
		}
		break;
	case PANEL_FUNKEY_MYPC:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_COMPUTER;
		}
		break;

	case PANEL_FUNKEY_CACULATOR:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_CACULATOR;
		}
		break;
	}
	return keyfun;
}

GVORDER_KEYFUN CKeyAssignDlg::GetMultimediaKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	switch (index)
	{
		//24: Volume Up
	case PANEL_MEDIA_VOLUP:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_VOLUP;
		}
		break;	
		//25: Volume Down
	case PANEL_MEDIA_VOLDOWN:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_VOLDOWN;
		}
		break;	
		//26: Mute
	/*case 2:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_MUTE;
		}
		break;*/
		//37: Play/Pause
	case PANEL_MEDIA_STOP:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_STOP;
		}
		break;	

		//37: Play/Pause
	case PANEL_MEDIA_PLAY:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_PLAY;
		}
		break;	
		//38: Previous
	case PANEL_MEDIA_PREVIOUS:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_PREV;
		}
		break;	
		//39: Next
	case PANEL_MEDIA_NEXT:
		{
			keyfun.fnType = GVORDER_FUN_MEDIA;
			keyfun.value.media.key = GVORDER_MEDIA_NEXT;
		}
		break;

	}
	return keyfun;

}

GVORDER_KEYFUN CKeyAssignDlg::GetMouseKeyFun(int index)
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
	// peter lee 2016/7/13
	/*case 5: // dpi +
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
		break;*/
	case 5: // Forward Scroll"
		{
			keyfun.fnType = GVORDER_FUN_MOUSE;
			keyfun.value.mouse.msbutton= 0;
			keyfun.value.mouse.tiltcount = 0;
			keyfun.value.mouse.wheelcount = VM_UP_SCROLL;
		}
		break;
	case 6: // Backward Scroll"
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

GVORDER_KEYFUN CKeyAssignDlg::GetMacroKeyFun(int index)
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_NONE;
	//取出marco
	GVORDER_MACROS macros;
	macros.nIndex = m_StyleDlg.GetCmbMacronIndex(index);//add by Terry, To get the macro nIndex
	CKbLedCtrl::GetMacrosKey(macros);

	if (MacroIsValid(macros.attr))
	{
		switch(macros.attr.RunType)
		{
		case 0:
			keyfun.fnType = GVORDER_FUN_MACROSONCE;
			break;
		case 1:
			keyfun.fnType = GVORDER_FUN_MACROCSFIRE;//
			break;
		case 2:
			keyfun.fnType = GVORDER_FUN_MACROSLOOP;
			break;
		}
		keyfun.value.macros.type = macros.attr.RunType + 6;
		keyfun.value.macros.macrosIndex = macros.nIndex;
	}
	return keyfun;
}


GVORDER_KEYFUN CKeyAssignDlg::SetSingleKeyDefault()
{
	GVORDER_KEYFUN keyfun;
	keyfun.fnType = GVORDER_FUN_DEFAULT;
	keyfun.value.keyboard.keyCode = 0;
	keyfun.value.keyboard.keyModifier = 0;
	return keyfun;
}

void CKeyAssignDlg::OnSave(GVORDER_KEYFUN fun)
{
	if (0 == m_nKeySel)
	{
		AfxMessageBox(_T("Please choose a key to continue..."));
		return;
	}
	fun.nIndex = s_nKeyFwIndex[m_nKeySel];
	fun.nProfile = m_nProfileSel;

	CKbLedCtrl::SetKeyFun(fun);
	// why this??
// 	if (7 == GetCurItem())
// 	{
// 		
// 		s_VgaCtrl.SetApplication(fun.nIndex, m_sAppPath);
// 	}
	AfxMessageBox(_T("Set up successful!"));
}

bool CKeyAssignDlg::MacroIsValid(GVORDER_MACROS_ATTR macro)
{
	return macro.nIcon >= 1 && macro.nIcon <= KB_MARCO_COUNT && (0 <= macro.RunType && macro.RunType <= 2);
}

void CKeyAssignDlg::InitState()
{
	InitProfile();

	m_StyleDlg.InitState();
}

void CKeyAssignDlg::SetProfile(int nProfile)
{
	m_nProfileSel = nProfile;

	CXK700Cmd::SwitchProfile(m_nProfileSel);
	Sleep(100);

	CKbLedCtrl::LoadProfileClrList(m_nProfileSel);
	if (m_curSel > 0)
	{
		OnUiKeyboardSelChanged(1, m_nKeySel);
	}

	/*CKbLedCtrl::LoadProfileClrList(m_nProfileSel);
	if (m_curSel > 0)
	{
		OnUiKeyboardSelChanged(1, m_curSel);
	}*/
}

 void CKeyAssignDlg::SaveTxtInfor()
 {
	 CString sInput;
	 sInput = m_StyleDlg.GetInputStr();

	 GVORDER_KEYFUN fun;
	 fun.fnType = GVORDER_FUN_APP;
	 fun.nIndex = s_nKeyFwIndex[m_nKeySel];
	 fun.nProfile = m_nProfileSel;

	 CKbLedCtrl::SetKeyFun(fun);
	 Aorus()->GetCfg()->SetTxtInputInfor(fun.nIndex, sInput);
 }


#if 1

 void CKeyAssignDlg::SetBtnInfo(GVORDER_KEYFUN keyfun)
 {
	 ResetCtrl();
	// 判斷應?勾選哪一?單選按鈕
	 int index = 0;
//	  Default
  	 if (GetDefaultIndex(keyfun)) // 如果?按鍵存儲的是基本按鍵，而且選中的和存儲的都是一致的，則為Default
  	 {
  		  m_StyleDlg.SetCurStyle(0);
	
  	 }

	 if ((index = GetHotKeyCMBIndex(keyfun)) != -1)//hotkey
	 {
		 m_StyleDlg.SetCurStyle(6);
		 m_StyleDlg.SetCurHotKeySel(index);
	 }

	else if ((index = GetMultiKeyCMBIndex(keyfun)) != -1) // multi key
	  {
		  m_StyleDlg.SetCurStyle(1);
		  
		  m_StyleDlg.SetCurMultiKeySel(keyfun.value.keyboard.keyCode, keyfun.value.keyboard.keyModifier);
		  m_StyleDlg.showMultiKey();
		  
	 }

 	 else if ((index = GetTxtInputCMBIndex(keyfun)) != -1)//txtinput
 	 {
		 m_StyleDlg.SetCurStyle(2);
		 CString sOutput = _T("");
 		Aorus()->GetCfg()->GetTxtInputInfor(index, sOutput);	
		m_StyleDlg.SetOutputStr(sOutput);
 	 }

	else if ((index = GetMouseCMBIndex(keyfun)) != -1) // mouse
	 {
		 m_StyleDlg.SetCurStyle(3);
		 m_StyleDlg.SetCurMouseKeySel(index);
	 }

	else if ((index = GetFunctionKeyCMBIndex(keyfun)) != -1) // functionkey
	{
		m_StyleDlg.SetCurStyle(4);
		m_StyleDlg.SetFunctionKeySel(index-1);
	}

 	else if ((index = GetMultimediaCMBIndex(keyfun)) != -1) // multimedia
 	{
 		m_StyleDlg.SetCurStyle(5);
 		m_StyleDlg.SetMediaPlayerSel(index-1);
 	}

	 else if ((index = GetMacroCMBIndex(keyfun)) != -1) // macro
	 {
		 m_StyleDlg.SetCurStyle(7);
		 m_StyleDlg.SetCurMacroKeySel(index);
	 }	
 }
	
 // 判斷按鍵是否屬於Multimedia，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetMultimediaCMBIndex(GVORDER_KEYFUN keyfun)
 {
	 //26: stop
	 if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_STOP)

		 return PANEL_MEDIA_STOP;

	 //play
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_PLAY)

		 return PANEL_MEDIA_PLAY;

	 //38: Previous
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_PREV)
		 return PANEL_MEDIA_PREVIOUS;
	 //39: Next
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_NEXT)
		 return PANEL_MEDIA_NEXT;
	 //24: Volume Up
	else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_VOLUP)
		 return PANEL_MEDIA_VOLUP;
	 //25: Volume Down
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_VOLDOWN)
		 return PANEL_MEDIA_VOLDOWN;
	 else 
		 return -1;
 }			

 // 判斷按鍵是否屬於Mouse，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetMouseCMBIndex(GVORDER_KEYFUN keyfun)
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
	 //7: Forward Scroll
	 else if(
		 keyfun.fnType == GVORDER_FUN_MOUSE &&
		 keyfun.value.mouse.msbutton== 0 &&
		 keyfun.value.mouse.tiltcount == 0 &&
		 keyfun.value.mouse.wheelcount == VM_UP_SCROLL)
		 return 5;
	 //8: Backward Scroll
	 else if(
		 keyfun.fnType == GVORDER_FUN_MOUSE &&
		 keyfun.value.mouse.msbutton== 0 &&
		 keyfun.value.mouse.tiltcount == 0 &&
		 keyfun.value.mouse.wheelcount == VM_DOWN_SCROLL)
		 return 6;
	 else
		 return -1;
 }
 // 判斷按鍵是否屬於熱鍵，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetMultiKeyCMBIndex(GVORDER_KEYFUN keyfun)
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



 // 判斷按鍵是否屬於Macro，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetMacroCMBIndex(GVORDER_KEYFUN keyfun)
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
		 GVORDER_MACROS_ATTR lstmacros[KB_MARCO_COUNT];
		 int index = keyfun.value.macros.macrosIndex;
		 for (int i = 0; i < m_StyleDlg.GetMacroKeyCount(); i++)		 
		 {
 		//	 if (index == m_StyleDlg.m_cmbMarco[i].nIndex)
			 if (index == m_StyleDlg.GetCmbMacronIndex(i))
 			 {
 				 return i;
 			 }
		 }
		 return -1;
	 }
 }



 // 判斷按鍵是否屬於FunctionKey，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetFunctionKeyCMBIndex(GVORDER_KEYFUN keyfun)
 {
	 //36: E-mail
	 if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_EMAIL)
		 return PANEL_FUNKEY_MAIL;
	 //33: Internet Explorer
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_BROWSER)
		 return PANEL_FUNKEY_WEB;
	//media player
	 else if (
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_MEDIAPLAYER)
		return PANEL_FUNKEY_MEDIAPLAY;

	 else if (	
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_MUTE)
		return PANEL_FUNKEY_MUTE;

	 //32: Desktop
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		keyfun.value.media.key == GVORDER_MEDIA_COMPUTER)
		 return PANEL_FUNKEY_MYPC;
	 //9: Calculator
	 else if(
		 keyfun.fnType == GVORDER_FUN_MEDIA &&
		 keyfun.value.media.key == GVORDER_MEDIA_CACULATOR)
		 return PANEL_FUNKEY_CACULATOR;
	 else 
		 return -1;
 }
 //判斷案件是否屬於Txtinput是則返回其index, 不是返回-1
 int CKeyAssignDlg::GetTxtInputCMBIndex(GVORDER_KEYFUN keyfun)
 {
	 if (keyfun.fnType == GVORDER_FUN_APP)
	 {
		 return keyfun.nIndex;
	 }
	 
	return -1;
 }

 //判斷是否屬於HotKey是則返回其index, 不是返回-1
 int CKeyAssignDlg::GetHotKeyCMBIndex(GVORDER_KEYFUN keyfun)
 {
	 //alt+F4
	 if(
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_F4 &&
		 keyfun.value.keyboard.keyModifier == VK_LMENU 
		 )
		 return 0;
	 //alt + space + X
// 	 else if (
// 		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
// 		 keyfun.value.keyboard.keyCode == VK_SPACE &&
// 		 keyfun.value.keyboard.keyCode == VK_X &&
// 		 keyfun.value.keyboard.keyModifier == VK_LMENU 
// 		 )
// 		 return 1;
	 //alt + space + N
// 	 else if (
// 		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
// 		 keyfun.value.keyboard.keyCode == VK_SPACE &&
// 		 keyfun.value.keyboard.keyCode == VK_N &&
// 		 keyfun.value.keyboard.keyModifier == VK_LMENU 
// 		 )
// 		 return 2;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_D &&
		 keyfun.value.keyboard.keyModifier == VK_LWIN 
		 )
		 return 1;
	
	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_TAB &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 2;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_TAB &&
		 keyfun.value.keyboard.keyCode == VK_LSHIFT &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 3;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_0 &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 4;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_C &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 5;
	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_V &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 6;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_X &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 7;
	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_Z &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 8;

	 else if (
		 keyfun.fnType == GVORDER_FUN_KEYBOARD && 
		 keyfun.value.keyboard.keyCode == VK_Y &&
		 keyfun.value.keyboard.keyModifier == VK_LCONTROL 
		 )
		 return 9;

	return -1;
 }
			
 // 判斷按鍵是否屬於profile，是則返回其index，不是返回-1
 int CKeyAssignDlg::GetProfileCMBIndex(GVORDER_KEYFUN keyfun)
 {
	 if(keyfun.fnType == GVORDER_FUN_SWITCHPRO)
		 return keyfun.value.profile.nProfile;
	 return -1;
 }

#endif			
			
 void CKeyAssignDlg::ResetCtrl()
 {

	m_StyleDlg.ClearSetting();//清空控件信息
 }
			
 int CKeyAssignDlg::GetDefaultIndex(GVORDER_KEYFUN keyfun)
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


 void CKeyAssignDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
 {
	 if (bShow)
	 {
		 InitProfile();
		 OnUiComboBoxSelChanged(COMBOX_KBASSIGN_PROFILE, m_nProfileSel);
		 m_combobox[COMBOX_KBASSIGN_PROFILE].SetCurSel(m_nProfileSel);
	 }

	 CWnd::OnShowWindow(bShow, nStatus);
 }

 void CKeyAssignDlg::InitProfile()
 {
	 int m_nProSel;
	 int nDevices = 1; 
	 int m_nDevice = DEVICE_AK700;
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
			 m_kassignProfile[0][k] = ledP;
		 }

		 m_combobox[COMBOX_KBASSIGN_PROFILE].ResetContent();
		 for (int i =0; i < LED_PROFILE_CONT; i++)
		 {
			 m_combobox[COMBOX_KBASSIGN_PROFILE].AddString(m_kassignProfile[0][i].sProfileName, 0, CLR_MAIN);
		 }
	 }
	 m_combobox[COMBOX_KBASSIGN_PROFILE].SetCurSel(m_nProfileSel);
 }