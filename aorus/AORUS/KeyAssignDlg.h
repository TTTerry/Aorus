#pragma once

#include "KeyAssignStyleDlg.h"

//#include "MacroKeyDlg.h"

// CKeyAssignDlg dialog

// #define MARCO_COUNT 50 
// typedef struct _CMB_MARCO
// {
// #define MARCO_NEW	1
// #define MARCO_LOAD	2
// #define MARCO_DEL	3
// 
// 	int nIndex;
// 	int nType;
// 
// }CBB_MARCO, *PCMB_MARCO;

class CKeyAssignDlg : public CUiDlg
{
	typedef enum 
	{
	//	BTN_KBASSIGN_PROADD = 0,
		BTN_KBASSIGN_PROEDIT,
	//	BTN_KBASSIGN_PRODEL,
		BTN_KBASSIGN_APPLY,
		BTN_KBASSIGN_DEFAULT,
		BTN_KBASSIGN_NUM
	};

	typedef enum
	{
		COMBOX_KBASSIGN_PROFILE = 0,
		COMBOX_KBASSIGN_NUM,
	};

	typedef enum
	{
		EDIT_KEYASSIGN_PROFILENAME,
	};

	DECLARE_DYNAMIC(CKeyAssignDlg)

public:
	CKeyAssignDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKeyAssignDlg();
	void InitState();
	void UpdateUI();
// Dialog Data
	void ChangeCurProfile(int iProfile) {m_nProfileSel = iProfile;}
	void InitProfile();
	enum { IDD = IDD_VGA_LED_DIALOG };

	CKeyAssignStyleDlg m_StyleDlg;
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiKeyboardSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	afx_msg void OnRawInput(UINT nInputCode, HRAWINPUT hRawInput);
	DECLARE_MESSAGE_MAP()
	void Ui();
	void UiMain();
	bool MacroIsValid(GVORDER_MACROS_ATTR macro);
	void SetProfile(int nProfile);
	int m_curSel;
	CString m_sAppPath;

	void ResetCtrl();

	




private:
	
	int m_nKeys; // 104/105/106/107...
	CUiKeyboardCtrl m_KB;
	CUiButton m_btn[BTN_KBASSIGN_NUM];
	CUiComboBox m_combobox[COMBOX_KBASSIGN_NUM];
	CUiEdit m_edit;


	int m_nProfileSel;
	int m_nKeySel;

	// command
	GVORDER_KEYFUN GetHotKeyFun(int index);
	GVORDER_KEYFUN GetMultimediaKeyFun(int index);
	GVORDER_KEYFUN GetFunctionKeyFun(int index);
	GVORDER_KEYFUN GetMouseKeyFun(int index);
	GVORDER_KEYFUN GetMacroKeyFun(int index);
	GVORDER_KEYFUN SetSingleKeyDefault();//Terry 2017/07/11

	//Terry 2017/06/27
	int  GetMouseCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetMacroCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetMultiKeyCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetProfileCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetMultimediaCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetFunctionKeyCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetTxtInputCMBIndex(GVORDER_KEYFUN keyfun);
	int  GetHotKeyCMBIndex(GVORDER_KEYFUN keyfun);
	void SetBtnInfo(GVORDER_KEYFUN keyfun);
	int GetDefaultIndex(GVORDER_KEYFUN keyfun);


	void SetApplication();

	void SaveTxtInfor();
	void OnSave(GVORDER_KEYFUN fun);
	LED_SETTING m_kassignProfile[GVDISP_CARD_MAXNUM][LED_PROFILE_CONT];
};
