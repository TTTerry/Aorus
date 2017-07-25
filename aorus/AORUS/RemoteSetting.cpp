// RemoteSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "AORUS.h"
#include "RemoteSetting.h"
#include "AORUSDlg.h"


// CRemoteSetting 对话框

IMPLEMENT_DYNAMIC(CRemoteSetting, CUiDlg)

CRemoteSetting::CRemoteSetting(CWnd* pParent /*=NULL*/)
	: CUiDlg(CRemoteSetting::IDD, pParent)
{

}

CRemoteSetting::~CRemoteSetting()
{
}

void CRemoteSetting::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRemoteSetting, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
END_MESSAGE_MAP()


// CRemoteSetting 消息处理程序
BOOL CRemoteSetting::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	return true;
}

void CRemoteSetting::Ui()
{
	UiMain();
}

void CRemoteSetting::UiMain()
{
	SetBkBitmap(IDB_REMOTE_BG, 0xff, CLR_TRPT);

	UI_BTN btn[]=
	{
		UI_BTN(this, BTN_REMOTE_CLOSE,   CRect(273,  8, 0,  0), &UIBTN_IMAGE(IDB_HOME_CLOSEON,	IDB_HOME_CLOSEON,	IDB_HOME_CLOSEON,	0)),
        UI_BTN(this, BTN_REMOTE_APPLY,   CRect(105,  158, 0,  0), &UIBTN_IMAGE(IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	0),&UIBTN_STRING(CLangX::Get(LANG_REMOTE_APPLY),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11))),
        UI_BTN(this, BTN_REMOTE_CANCEL,   CRect(180,  158, 0,  0), &UIBTN_IMAGE(IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	IDB_SETTINGPAGE_BTNON,	0),&UIBTN_STRING(CLangX::Get(LANG_REMOTE_CANCEL),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(11)))
	};
	for(int i=BTN_REMOTE_CLOSE; i <= BTN_REMOTE_CANCEL; i++)
	{
		m_btn[i].CreateButton(btn[i]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	m_edit[EDIT_REMOTE_NAME].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT, CRect(101,  73, 241,  87), this, EDIT_REMOTE_NAME);
	m_edit[EDIT_REMOTE_NAME].SetFont(Font(10), CLR_WHITE);
	m_edit[EDIT_REMOTE_NAME].SetBkColor(CLR_BLACK);
	//m_edit[EDIT_REMOTE_NAME].SetAsIntNumberEdit(30);

	m_edit[EDIT_REMOTE_PASSWORD].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT, CRect(101,  104, 241,  118), this, EDIT_REMOTE_PASSWORD);
	m_edit[EDIT_REMOTE_PASSWORD].SetFont(Font(10), CLR_WHITE);
	m_edit[EDIT_REMOTE_PASSWORD].SetBkColor(CLR_BLACK);

	m_stc[STC_REMOTE_NAME].CreateStatic(UI_STATIC(this, STC_REMOTE_NAME,	CRect(11, 72, 94, 88), CLangX::Get(LANG_REMOTE_NAME), NULL, CLR_TRPT));
	m_stc[STC_REMOTE_NAME].ModifyCtrlStyle(ST_VCENTER,ST_RIGHT);
	m_stc[STC_REMOTE_NAME].SetFont(Font(10), CLR_WHITE);

	m_stc[STC_REMOTE_PASSWORD].CreateStatic(UI_STATIC(this, STC_REMOTE_PASSWORD,	CRect(11, 103, 94, 119), CLangX::Get(LANG_REMOTE_PASSWORD), NULL, CLR_TRPT));
	m_stc[STC_REMOTE_PASSWORD].ModifyCtrlStyle(ST_VCENTER,ST_RIGHT);
	m_stc[STC_REMOTE_PASSWORD].SetFont(Font(10), CLR_WHITE);

	m_stc[STC_REMOTE_CAPTION].CreateStatic(UI_STATIC(this, STC_REMOTE_CAPTION,	CRect(15, 13, 250, 30), CLangX::Get(LANG_REMOTE_CAPTION), NULL, CLR_TRPT));
	m_stc[STC_REMOTE_CAPTION].ModifyCtrlStyle(ST_VCENTER,ST_LEFT);
	m_stc[STC_REMOTE_CAPTION].SetFont(Font(11), CLR_MAIN);

	ShowWindow(SW_HIDE);
	CString csName=_T("");
	CString csKey=_T("");
	
	Aorus()->GetCfg()->GetLoadingInfo(csName,csKey);
	m_edit[EDIT_REMOTE_NAME].SetWindowText(csName);
	m_edit[EDIT_REMOTE_PASSWORD].SetWindowText(csKey);
}
LRESULT CRemoteSetting::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_REMOTE_CANCEL:
	case BTN_REMOTE_CLOSE:
		{
		     ShowWindow(SW_HIDE);
			 CString csName=_T("");
			 CString csKey=_T("");
			 Aorus()->GetCfg()->GetLoadingInfo(csName,csKey);
			 m_edit[EDIT_REMOTE_NAME].SetWindowText(csName);
			 m_edit[EDIT_REMOTE_PASSWORD].SetWindowText(csKey);
			 SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			 CAORUSDlg* pMain = (CAORUSDlg*)AfxGetMainWnd();
			 pMain->Enable(TRUE);
			 pMain->SetForegroundWindow();
		}
		break;
	case BTN_REMOTE_APPLY:
		{
			CString csName=_T("");
			CString csKey=_T("");
			m_edit[EDIT_REMOTE_NAME].GetWindowText(csName);
			m_edit[EDIT_REMOTE_PASSWORD].GetWindowText(csKey);
			//m_stc[STC_REMOTE_NAME].GetWindowText(csName);
			//m_stc[STC_REMOTE_PASSWORD].GetWindowText(csKey); 
			Aorus()->GetCfg()->SetLoadingInfo(csName,csKey);
			ShowWindow(SW_HIDE);
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			CAORUSDlg* pMain = (CAORUSDlg*)AfxGetMainWnd();
			pMain->Enable(TRUE);
			pMain->SetForegroundWindow();
		}
		break;
	}
	
    return 1;
}
void CRemoteSetting::OnOK()
{
	CString csName=_T("");
	CString csKey=_T("");
	m_edit[EDIT_REMOTE_NAME].GetWindowText(csName);
	m_edit[EDIT_REMOTE_PASSWORD].GetWindowText(csKey);
	//m_stc[STC_REMOTE_NAME].GetWindowText(csName);
	//m_stc[STC_REMOTE_PASSWORD].GetWindowText(csKey); 
	Aorus()->GetCfg()->SetLoadingInfo(csName,csKey);
	ShowWindow(SW_HIDE);
	SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CAORUSDlg* pMain = (CAORUSDlg*)AfxGetMainWnd();
	pMain->Enable(TRUE);
	pMain->SetForegroundWindow();
}
//BOOL CRemoteSetting::PreTranslateMessage(MSG* pMsg)
//{
//	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)   
//	{
//		return TRUE;
//	}
//}