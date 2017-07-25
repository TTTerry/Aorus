#pragma once


// CKeyAssignStyleDlg dialog
#define LKEY_DEFAULT				0
#define LKEY_MUTILKEY			1
#define LKEY_TXTINPUT			2
#define LKEY_MOUSEACTION		3
#define LKEY_FNKEY				4
#define LKEY_MEDIAPLAYER		5
#define LKEY_HOTKEY				6
#define LKEY_MACRO				7

#define LKEY_ALT_F4				8
// #define LKEY_ALT_SPACE_X		8
// #define LKEY_ALT_SPACE_N		9
#define LKEY_WIN_D				9
#define LKEY_CTRL_TAB			10
#define LKEY_CTRL_SHIFT_TAB		11
// #define LKEY_CTRL_WHEEL_UP		13
// #define LKEY_CTRL_WHEEL_DOWN	14
#define LKEY_CTRL_0				12
#define LKEY_CTRL_C				13
#define LKEY_CTRL_V				14
#define LKEY_CTRL_X				15
#define LKEY_CTRL_Z				16
#define LKEY_CTRL_Y				17

#define LKEY_MOUSE_LFET			18
#define LKEY_MOUSE_RIGHT		19
#define LKEY_MOUSE_MIDDLE		20
#define LKEY_MOUSE_PREPAGE		21
#define LKEY_MOUSE_NEXTPAGE		22
#define LKEY_MOUSE_WHEELUP		23
#define LKEY_MOUSE_WHEELDOWN	24

#define LKEY_QTY				25

typedef enum {
		PANEL_MEDIA_STOP = 1,
		PANEL_MEDIA_PLAY,
		PANEL_MEDIA_PREVIOUS,
		PANEL_MEDIA_NEXT,
		PANEL_MEDIA_VOLUP,
		PANEL_MEDIA_VOLDOWN
};

typedef enum {
		PANEL_FUNKEY_MAIL = 1,
		PANEL_FUNKEY_WEB,
		PANEL_FUNKEY_MEDIAPLAY,
		PANEL_FUNKEY_MUTE,
		PANEL_FUNKEY_MYPC,
		PANEL_FUNKEY_CACULATOR
};

class CKeyAssignStyleDlg : public CUiDlg
{
	typedef enum {
		STC_KEYASSIGN_DEFAULT,
		STC_KEYASSIGN_MUTILKEY,
		STC_KEYASSIGN_TXTINPUT,
		STC_KEYASSIGN_MOUSEACTION,
		STC_KEYASSIGN_FNKEY,
		STC_KEYASSIGN_MEDIAPLAYER,
		STC_KEYASSIGN_HOTKEY,
		STC_KEYASSIGN_MACRO,
		STC_KEYASSIGN_TXTINPUTDESC,
		STC_KEYASSIGN_MOUSEACTIONDESC,
		STC_KEYASSIGN_HOTKEYDESC,
		STC_KEYASSIGN_MACRODESC,
		STC_KEYASSIGN_MUTILKEYONE,
		STC_KEYASSIGN_MUTILKEYTWO,
		STC_KEYASSIGN_MUTILKEYTHREE,
		STC_KEYASSIGN_NUM
	};

	typedef enum {
		BTN_KEYASSIGN_CLOSE,
		BTN_KEYASSIGN_NUM
	};

	typedef enum {
		EDIT_KEYASSIGN_INPUTKEY1,
		EDIT_KEYASSIGN_INPUTKEY2,
		EDIT_KEYASSIGN_INPUTKEY3,
		EDIT_KEYASSIGN_TEXTINPUT,
		EDIT_KEYASSIGN_NUM
	};

	typedef enum {
		PANEL_KEYASSIGN_FNKEY,
		PANEL_KEYASSIGN_MEDIA,
		PANEL_KEYASSIGN_NUM
	};

	typedef enum {
		COMBOX_KEYASSIGN_STYLE,
		COMBOX_KEYASSIGN_HOTKEY,
		COMBOX_KEYASSIGN_MOUSE,
		COMBOX_KEYASSIGN_MACRO,
		COMBOX_KEYASSIGN_NUM,
	};


	DECLARE_DYNAMIC(CKeyAssignStyleDlg)

public:
	CKeyAssignStyleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKeyAssignStyleDlg();
	void InitState();
	void UpdateUI();
// Dialog Data
	enum { IDD = IDD_VGA_LED_DIALOG };

	void OnFit(CRect rc);

	int GetMacroKeySel() { return m_combobox[COMBOX_KEYASSIGN_MACRO].GetCurSel(); } // Terry 2017/6/21
	int GetCurStyle() { return m_combobox[COMBOX_KEYASSIGN_STYLE].GetCurSel(); }
	int GetMouseKeySel() { return m_combobox[COMBOX_KEYASSIGN_MOUSE].GetCurSel(); }	// Peter Lee 2017/6/18
	int GetHotKeySel() { return m_combobox[COMBOX_KEYASSIGN_HOTKEY].GetCurSel(); }	// Peter Lee 2017/6/18
	int GetMediaPlayerSel() { return m_nMediaPlayerSel; };							// Peter Lee 2017/6/18
	int GetFunctionKeySel() { return m_nFunctionKeySel; };							// Peter Lee 2017/6/18
	int GetCmbMacronIndex(int Index) {return m_cmbMarco[Index].nIndex; } //Terry 2017/6/22
	bool GetMutilKey(GVORDER_KEYFUN &keyfun);


	int GetMacroKeyCount() {return m_combobox[COMBOX_KEYASSIGN_MACRO].GetCount();}// Terry 2017/06/27
	void SetCurMacroKeySel(int Index) {m_combobox[COMBOX_KEYASSIGN_MACRO].SetCurSel(Index);}
	void SetCurMouseKeySel(int Index) {m_combobox[COMBOX_KEYASSIGN_MOUSE].SetCurSel(Index);}
	void SetCurMultiKeySel(BYTE code, BYTE modefier) {m_HKey1.SetHotKey(code, modefier);}
	void SetCurHotKeySel(int Index) {m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetCurSel(Index);}
 	void SetMediaPlayerSel(int Index) {m_panel[PANEL_KEYASSIGN_MEDIA].SetCurItem(Index);}
 	void SetFunctionKeySel(int Index) {m_panel[PANEL_KEYASSIGN_FNKEY].SetCurItem(Index);}
// 	void SetMediaPlayerSel(int Index) {m_nMediaPlayerSel = Index;}
// 	void SetFunctionKeySel(int Index) {m_nFunctionKeySel = Index;}
	void SetMultiKeyFocus() {m_HKey1.SetFocus();}
	void showMultiKey() {OnNewPaint(0, 0);}


	
	void SetCurStyle(int Index) { m_combobox[COMBOX_KEYASSIGN_STYLE].SetCurSel(Index); SwitchAssignStyle(Index);}
	CString GetInputStr();
	void SetOutputStr(CString str);
	void ClearSetting() {
		m_EditTxtInput[EDIT_KEYASSIGN_TEXTINPUT].SetWindowText(_T(""));
		m_HKey1.SetHotKey(NULL, NULL);
		m_panel[PANEL_KEYASSIGN_MEDIA].SetCurItem(NULL);
		m_panel[PANEL_KEYASSIGN_FNKEY].SetCurItem(NULL);
		m_combobox[COMBOX_KEYASSIGN_MACRO].SetWindowText(_T(""));
		m_combobox[COMBOX_KEYASSIGN_HOTKEY].SetCurSel(0);
		m_combobox[COMBOX_KEYASSIGN_MOUSE].SetCurSel(0);
}
	//void GetCMBMacro() {return m_cmbMarco[KB_MARCO_COUNT];}

	void SwitchAssignStyle(int Index);


	
protected:
	HICON  m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewPaint(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
	void Ui();
	void UiMain();
	void OnClose();
	bool MacroIsValid(GVORDER_MACROS_ATTR macro);
	

private:
	CUiButton m_btn[BTN_KEYASSIGN_NUM];
    CUiStatic m_stc[STC_KEYASSIGN_NUM];
    CUiPanelCtrl m_panel[PANEL_KEYASSIGN_NUM];
	CUiComboBox m_combobox[COMBOX_KEYASSIGN_NUM];
	CUiHotKeyCtrl m_HKey1;
// 	CUiHotKeyCtrl m_HKey2;
// 	CUiHotKeyCtrl m_HKey3;
	CUiEdit m_EditTxtInput[EDIT_KEYASSIGN_NUM];

	static int s_nWords;
	static LANG_WORD s_Words[48];
	static int s_nHotKeys;
	static int s_HotKeys[24];
	static CString s_HotKeysName[24];
	static int s_nMouses;
	static int s_Mouses[12];	// Mouse action selection
	CBB_MARCO m_cmbMarco[KB_MARCO_COUNT];


	int m_nMediaPlayerSel;
	int m_nFunctionKeySel;
};
