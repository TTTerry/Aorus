// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AORUS.h"
#include "SettingDlg.h"
#include "AORUSDlg.h"


IMPLEMENT_DYNAMIC(CSettingDlg, CUiDlg)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_WM_MOVING()
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序
BOOL CSettingDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	return true;
}

void CSettingDlg::Ui()
{
	UiMain();
}

void CSettingDlg::UiMain()
{
	HDC hdc = ::GetDC(m_hWnd);
	int nDC = _ttoi(_T("98"));//::GetDeviceCaps(hdc, LOGPIXELSY);
	int nHPixel11 = (int)((11.5 * nDC) / 72);
	::ReleaseDC(m_hWnd, hdc);

	m_hFont = InstallFont(IDR_MAIN_FONT);
	m_font11u.CreateFont(nHPixel11, 0, 0, 0, FW_NORMAL, FALSE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Aldrich"));


	SetBkBitmap(IDB_SETTING_BG, 0xff, CLR_TRPT); // 设置背景图;
	m_stc[STC_SETTING_GENERAL_PAD].CreateStatic(UI_STATIC(this, STC_SETTING_GENERAL_PAD,  CRect(20, 55, 275, 185), _T(""), NULL, CLR_TRPT));
	m_stc[STC_SETTING_VGA_PAD].CreateStatic(UI_STATIC(this, STC_SETTING_VGA_PAD,  CRect(20, 55, 275, 175), _T(""), NULL, CLR_TRPT));
	m_stc[STC_SETTING_VGA_PAD].ShowWindow(SW_HIDE);
	UI_STATIC sta[] =
	{	
		UI_STATIC(this, STC_SETTING_CAPTION,	CRect(15, 13, 72, 30),CLangX::Get(LANG_SET_CAPTION), NULL, CLR_TRPT),

		UI_STATIC(&m_stc[STC_SETTING_GENERAL_PAD], STC_SETTING_START_WITH_WINDOWS,	CRect(20, 10, 230, 25), CLangX::Get(LANG_SET_START_WITH_WINDOW), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_GENERAL_PAD], STC_SETTING_START_MIN,		CRect(20, 32, 230, 48),CLangX::Get(LANG_SET_START_MIN), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_GENERAL_PAD], STC_SETTING_MIN_TO_TRAY,		CRect(20, 55, 230, 70), CLangX::Get(LANG_SET_CLOSEBTN_TO_TRAY), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_GENERAL_PAD], STC_SETTING_AUTO_CHECK_FOR_UPDATES,	CRect(20, 78, 735, 93),CLangX::Get(LANG_SET_AUTOCHECK_FOR_UPDATE), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_GENERAL_PAD], STC_SETTING_LAST_CHECKED_ON,	CRect(4, 98, 132, 139),CLangX::Get(LANG_SET_LAST_CHECK_ON), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_BIOSVER,		CRect(6, 12, 64, 24), CLangX::Get(LANG_SET_BIOS_VER), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_DRIVERVER,	CRect(6, 70, 64, 84),CLangX::Get(LANG_SET_DRI_VER), NULL, CLR_TRPT),
		// 2017/4/28 Peter Lee
		//UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_BIOSVER_INFO,		CRect(72, 12, 144, 24), _T("Unknown"), NULL, CLR_TRPT),
		//UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_DRIVERVER_INFO,	CRect(72, 70, 144, 84),_T("Unknown"), NULL, CLR_TRPT),
		// 2017/5/4 Peter Lee
		UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_BIOSVER_INFO,		CRect(88, 12, 200, 24), _T("Unknown"), NULL, CLR_TRPT),
		UI_STATIC(&m_stc[STC_SETTING_VGA_PAD], STC_SETTING_DRIVERVER_INFO,	CRect(88, 70, 200, 84),_T("Unknown"), NULL, CLR_TRPT),
	};

	m_stc[STC_SETTING_CAPTION].CreateStatic(sta[0]);
	m_stc[STC_SETTING_CAPTION].ModifyCtrlStyle(ST_VCENTER,ST_LEFT);
	m_stc[STC_SETTING_CAPTION].SetFont(Font(11), CLR_MAIN);

	for (int i = STC_SETTING_START_WITH_WINDOWS;i <= STC_SETTING_DRIVERVER_INFO;i++)
	{
		m_stc[i].CreateStatic(sta[i - (int)STC_SETTING_CAPTION]);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
		m_stc[i].SetFont(Font(11), CLR_WHITE);
	}
	m_stc[STC_SETTING_LAST_CHECKED_ON].ModifyCtrlStyle(ST_VCENTER | ST_SINGLELINE, ST_LEFT | ST_TOP);

	UI_BTN btn[] = 
	{
		UI_BTN(this, BTN_SETTING_CLOSE,   CRect(272,  8, 289, 24), &UIBTN_IMAGE(IDB_HOME_CLOSEON,	IDB_HOME_CLOSEON,	IDB_HOME_CLOSEON,	0)),
		UI_BTN(this, BTN_SETTING_GENETAL, CRect( 15, 36,   0,  0),&UIBTN_IMAGE(0, 0, 0, 0, IDB_SETTING_TAB_ON, IDB_SETTING_TAB_ON, IDB_SETTING_TAB_ON, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_SET_GENERAL),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11)), BTN_RADIO),
		UI_BTN(this, BTN_SETTING_VGA,     CRect( 85, 36,   0,  0),&UIBTN_IMAGE(0, 0, 0, 0, IDB_SETTING_TAB_ON, IDB_SETTING_TAB_ON, IDB_SETTING_TAB_ON, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_SET_VGA),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11)), BTN_RADIO),
		UI_BTN(&m_stc[STC_SETTING_GENERAL_PAD], BTN_SETTING_START_WITH_WINDOWS,   CRect(3, 11,  0,0),&UIBTN_IMAGE(IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, 0, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, 0, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(&m_stc[STC_SETTING_GENERAL_PAD], BTN_SETTING_START_MINI,   CRect(3, 34,  0,0),&UIBTN_IMAGE(IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, 0, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, 0, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(&m_stc[STC_SETTING_GENERAL_PAD], BTN_SETTING_MIN_TO_TRAY,   CRect(3, 57,  0,0),&UIBTN_IMAGE(IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, 0, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, 0, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(&m_stc[STC_SETTING_GENERAL_PAD], BTN_SETTING_AUTO_UPDATE,   CRect(3, 80,  0,0),&UIBTN_IMAGE(IDB_CHECKBOX_UNCHECK, IDB_CHECKBOX_UNCHECK, 0, 0, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, IDB_CHECKBOX_CHECKED, 0, CLR_TRPT), NULL, BTN_CHECK),
		UI_BTN(&m_stc[STC_SETTING_GENERAL_PAD], BTN_SETTING_CHECK_FOR_UPDATE_GENERAL,   CRect(133, 100, 0,  0), &UIBTN_IMAGE(IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_OFF),&UIBTN_STRING(CLangX::Get(LANG_SET_CHECK_FOR_UPDATE),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(10))),
		UI_BTN(&m_stc[STC_SETTING_VGA_PAD], BTN_SETTING_CHECK_FOR_UPDATE_BIOS,  CRect(120,  32, 0,  0), &UIBTN_IMAGE(IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_OFF),&UIBTN_STRING(CLangX::Get(LANG_SET_CHECK_FOR_UPDATE),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(10))),
		UI_BTN(&m_stc[STC_SETTING_VGA_PAD], BTN_SETTING_CHECK_FOR_UPDATE_DRIVER,   CRect(120,  86, 0,  0), &UIBTN_IMAGE(IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_ON,	IDB_SETTING_BTN2_OFF),&UIBTN_STRING(CLangX::Get(LANG_SET_CHECK_FOR_UPDATE),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(10))),
		UI_BTN(this, BTN_SETTING_OK,   CRect(149,  200,0,  0), &UIBTN_IMAGE(IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	0),&UIBTN_STRING(CLangX::Get(LANG_SET_OK),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_SETTING_CANCEL,   CRect(217,  200, 0,  0), &UIBTN_IMAGE(IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	0),&UIBTN_STRING(CLangX::Get(LANG_SET_CANCEL),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
		UI_BTN(this, BTN_SETTING_CONTACT,  CRect(15, 200, 100, 215), NULL, &UIBTN_STRING(CLangX::Get(LANG_CONTACT), CLR_MAIN, CLR_MAIN, CLR_MAIN, CLR_MAIN, &m_font11u)),
	};
	for(int i=BTN_SETTING_CLOSE; i <= BTN_SETTING_CONTACT; i++)
	{
		m_btn[i].CreateButton(btn[i - (int)BTN_SETTING_CLOSE]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}
	// Peter Lee 2017/4/28 get version info

	m_stc[STC_SETTING_BIOSVER_INFO].SetCaption(Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sBiosVer);
	m_stc[STC_SETTING_DRIVERVER_INFO].SetCaption(Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sDriverVer);
}

LRESULT CSettingDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_SETTING_CANCEL:
	case BTN_SETTING_CLOSE:
		{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			CAORUSDlg* pMain = (CAORUSDlg*)AfxGetMainWnd();
			pMain->Enable(TRUE);	
			VGA_PARAM_BASESETTING basesetting;
			Aorus()->GetCfg()->GetBaseSetting(basesetting);
			m_btn[BTN_SETTING_START_WITH_WINDOWS].SetCheck(basesetting.bAutoRun? true:false);
			m_btn[BTN_SETTING_START_MINI].SetCheck(basesetting.bMinimize? true:false);
			m_btn[BTN_SETTING_MIN_TO_TRAY].SetCheck(basesetting.bCloseMin? true:false);
			m_btn[BTN_SETTING_AUTO_UPDATE].SetCheck(basesetting.bCheckUpdate? true:false);
			ShowWindow(SW_HIDE);
		}
		break;
	case BTN_SETTING_GENETAL:
		{
			m_btn[BTN_SETTING_GENETAL].SetCheck(true);
			m_btn[BTN_SETTING_VGA].SetCheck(false);
			m_stc[STC_SETTING_GENERAL_PAD].ShowWindow(SW_SHOW);
			m_stc[STC_SETTING_VGA_PAD].ShowWindow(SW_HIDE);
		}break;
	case BTN_SETTING_VGA:
		{
			m_btn[BTN_SETTING_GENETAL].SetCheck(false);
			m_btn[BTN_SETTING_VGA].SetCheck(true);
			m_stc[STC_SETTING_GENERAL_PAD].ShowWindow(SW_HIDE);
			m_stc[STC_SETTING_VGA_PAD].ShowWindow(SW_SHOW);
		}break;
	case BTN_SETTING_START_WITH_WINDOWS:
	case BTN_SETTING_START_MINI:
	case BTN_SETTING_MIN_TO_TRAY:
	case BTN_SETTING_AUTO_UPDATE:
		break;
	case BTN_SETTING_CHECK_FOR_UPDATE_GENERAL:
		{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

			Aorus()->GetVGA()->Ctrl()->SoftwareUpdate();
			VGA_PARAM_BASESETTING basesetting;
			Aorus()->GetCfg()->GetBaseSetting(basesetting);
			basesetting.sLastCheckUpdate = ((CTime)CTime::GetCurrentTime()).Format(_T("%Y-%m-%d %H:%M:%S"));
			m_stc[STC_SETTING_LAST_CHECKED_ON].SetCaption( CLangX::Get(LANG_SET_LAST_CHECK_ON)+_T("  :\r\n")+basesetting.sLastCheckUpdate);
			Aorus()->GetCfg()->SetBaseSetting(basesetting);
		}break;
	case BTN_SETTING_CHECK_FOR_UPDATE_BIOS:
		{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		    Aorus()->GetVGA()->Ctrl()->BiosUpdate();
		}break;
	case BTN_SETTING_CHECK_FOR_UPDATE_DRIVER:
		{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			Aorus()->GetVGA()->Ctrl()->DriverUpdate();
		}
		break;
	case BTN_SETTING_OK:
		{
			VGA_PARAM_BASESETTING basesetting;
			Aorus()->GetCfg()->GetBaseSetting(basesetting);
			basesetting.bAutoRun=m_btn[BTN_SETTING_START_WITH_WINDOWS].IsCheck();
			basesetting.bMinimize=m_btn[BTN_SETTING_START_MINI].IsCheck();
			basesetting.bCloseMin=m_btn[BTN_SETTING_MIN_TO_TRAY].IsCheck();
			basesetting.bCheckUpdate=m_btn[BTN_SETTING_AUTO_UPDATE].IsCheck();
			Aorus()->GetCfg()->SetBaseSetting(basesetting);
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			CAORUSDlg* pMain = (CAORUSDlg*)AfxGetMainWnd();
			pMain->Enable(TRUE);
			ShowWindow(SW_HIDE);
		}
	break;
	case BTN_SETTING_CONTACT:
		Aorus()->GetVGA()->Ctrl()->ContactUs();
		break;	
	}
	return 1;
}
void CSettingDlg::Initstate()
{
    VGA_PARAM_BASESETTING basesetting;
	Aorus()->GetCfg()->GetBaseSetting(basesetting);
	m_btn[BTN_SETTING_START_WITH_WINDOWS].SetCheck(basesetting.bAutoRun? true:false);
	m_btn[BTN_SETTING_START_MINI].SetCheck(basesetting.bMinimize? true:false);
	m_btn[BTN_SETTING_MIN_TO_TRAY].SetCheck(basesetting.bCloseMin? true:false);
	m_btn[BTN_SETTING_AUTO_UPDATE].SetCheck(basesetting.bCheckUpdate? true:false);
	m_btn[BTN_SETTING_GENETAL].SetCheck(true);
	m_btn[BTN_SETTING_VGA].SetCheck(false);
	CString csLastCheck;
	csLastCheck=CLangX::Get(LANG_SET_LAST_CHECK_ON)+L"  :\r\n"+basesetting.sLastCheckUpdate;
	m_stc[STC_SETTING_LAST_CHECKED_ON].SetCaption(csLastCheck);

}

void CSettingDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CRect rcdesk,rcRect;
	GetDesktopWindow()->GetClientRect(rcdesk);
	CRect newRc(*pRect);
	if ((pRect->top+newRc.Height())>=rcdesk.bottom)
	{
		newRc.MoveToXY(CPoint(pRect->left,rcdesk.bottom-newRc.Height()));
		pRect->top = newRc.top;
		pRect->left = newRc.left;
		pRect->bottom = newRc.bottom;
		pRect->right = newRc.right;
	}
	CUiDlg::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
}
