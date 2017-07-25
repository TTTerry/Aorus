#pragma once

#include "MacroKeyDlg.h"

#define MACRO_COUNT 50
#define PROFILE_COUNT 5

extern GVORDER_PROFILE s_nCurProfile; // 當前profile
extern GVORDER_PROFILE s_LastApplyProfile;

// CMouseButtonDlg dialog

class CMouseButtonDlg : public CUiDlg
{
	typedef enum 
	{
	//	BTN_MBTN_ADDPROFILE,
		BTN_MBTN_EDITPROFILE,
	//	BTN_MBTN_DELPROFILE,
		BTN_MBTN_LEFT,
 		BTN_MBTN_RIGHT,
		BTN_MBTN_MIDDLE,
		BTN_MBTN_FORWARD,
		BTN_MBTN_BACKWARD,
 		BTN_MBTN_DPIINC,
 		BTN_MBTN_DPIDEC,
		BTN_MBTN_APPLY,
		BTN_MBTN_RESET,
		BTN_MBTN_DEFAULT,
		BTN_MBTN_NUM
	};

	typedef enum
	{
		COMBOX_MBTN_PROFILE,
		COMBOX_MBTN_DEFAULTSETTING,
		COMBOX_MBTN_MOUSE,
		COMBOX_MBTN_HOTKEY,
		COMBOX_MBTN_MACRO,
		COMBOX_MBTN_KEYMAPPING,
		COMBOX_MBTN_NUM,
	};

	typedef enum
	{
		STC_MBTN_STATUS1,
		STC_MBTN_STATUS2,
		STC_MBTN_STATUS3,
		STC_MBTN_STATUS4,
		STC_MBTN_STATUS5,
		STC_MBTN_STATUS6,
		STC_MBTN_STATUS7,
		STC_MBTN_STATUS8,

		STC_MBTN_MOUSE,
		STC_MBTN_KEYMAPPING,
		STC_MBTN_MACRO,
		STC_MBTN_MULTIKEY,
		STC_MBTN_MUTILMEDIA,
		STC_MBTN_DEFAULT,
	
		STC_MBTN_MULTIKEYONE,	//Terry 2017/07/14
		STC_MBTN_MULTIKEYTWO,
		STC_MBTN_MULTIKEYTHREE,
// 		STC_MBTN_BUTTON_LEFT,
// 		STC_MBTN_BUTTON_RIGHT,
// 		STC_MBTN_BUTTON_MIDDLE,
// 		STC_MBTN_BUTTON_FORWARD,
// 		STC_MBTN_BUTTON_BACKWARD,
// 		STC_MBTN_BUTTON_DPIINC,
// 		STC_MBTN_BUTTON_DPIDEC,
		STC_MBTN_NUM,
	};

	typedef enum
	{
		EDIT_MBTN_PROFILE,
		EDIT_MBTN_NUM,
	};

	// Peter Lee 2017/7/9
	typedef enum 
	{
		LST_HOTKEY = 0,
		LST_MACRO,
		LST_KEYMAPPING
	};
	DECLARE_DYNAMIC(CMouseButtonDlg)

public:
	CMouseButtonDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMouseButtonDlg();
	void InitBtnState();
	void GetMacrosList();
	void GetKeyMappingList();
	int GetLeftListIndex(GVORDER_KEYFUN keyfun);
	bool MacroIsValid(GVORDER_MACROS_ATTR macro);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateUI();

	void ChangeCurProfile(int iProfile) {s_nCurProfile.nProfile = iProfile;}
	void InitProfile();
	void showMultiKey() {OnNewPaint(0, 0);}
	// Dialog Data
	enum { IDD = IDD_VGA_LED_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//Terry 2017/07/14
	afx_msg LRESULT OnNewPaint(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	void Ui();
	void UiMain();

	LRESULT OnMouseButtonClicked(WPARAM wParam);
	void SetBtnInfo(GVORDER_KEYFUN keyfun, int btn_index);
	void SetBtnCapture(CString s, int btn);
	void SwitchLeftBtn(WPARAM wParam, LPARAM lParam);

	int GetDefaultIndex(GVORDER_KEYFUN keyfun);
	int GetMouseCMBIndex(GVORDER_KEYFUN keyfun);
	int GetKeyMappingCMBIndex(GVORDER_KEYFUN keyfun);
	int GetMacroCMBIndex(GVORDER_KEYFUN keyfun);
	int GetMultiKeyCMBIndex(GVORDER_KEYFUN keyfun);
	int GetApplicationCMBIndex(GVORDER_KEYFUN keyfun);
	int GetProfileCMBIndex(GVORDER_KEYFUN keyfun);
	int GetMultimediaCMBIndex(GVORDER_KEYFUN keyfun);
	int GetShortCutCMBIndex(GVORDER_KEYFUN keyfun);

	GVORDER_KEYFUN GetDefaultKeyFun(int index);
	GVORDER_KEYFUN GetMouseKeyFun(int index);
	GVORDER_KEYFUN GetKeyMappingKeyFun(int index);
	GVORDER_KEYFUN GetMacroKeyFun(int index);
	GVORDER_KEYFUN GetMultiKeyKeyFun();
	GVORDER_KEYFUN GetApplicationKeyFun(int index);
	GVORDER_KEYFUN GetProfileKeyFun(int index);
	GVORDER_KEYFUN GetMultimediaKeyFun(int index);
	GVORDER_KEYFUN GetShortCutKeyFun(int index);

	void OnSave(GVORDER_KEYFUN fun);

	CString GetKeyFunName(GVORDER_KEYFUN keyfun);
	void EnableLeftPanelOne(int curSel);

private:

	static int s_nWords;
	static LANG_WORD s_Words[48];

	static int s_nMouses;
	static int s_Mouses[12];

	static int s_nMultiMedia;
	static int s_MultiMedia[29];
	static CString s_sMultiMedia[29];

	static int s_nKeyMapping;
	static CString  s_KeyMapping[105];

	static int s_nMouseKey;
	static CString s_MouseKey[20];

	CUiStatic m_stc[STC_MBTN_NUM];
	CUiButton m_btn[BTN_MBTN_NUM];
	CUiComboBox m_combobox[COMBOX_MBTN_NUM];
	CUiHotKeyCtrl m_hotkeY;
	CUiEdit	m_edit[EDIT_MBTN_NUM];
	CUiListCtrl		m_list[STC_MBTN_NUM];


	int m_cur_selected; // 當前選中的按鈕

	GVORDER_MACROS	m_validMacros[MACRO_COUNT]; // 存儲有效的macro
	int m_nValidMacroCount;

	LED_SETTING m_btnProfiles[GVDISP_CARD_MAXNUM][LED_PROFILE_CONT];
};
