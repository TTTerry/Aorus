#pragma once
#include "MacroInsertAction.h"
// CMacroKeyDlg dialog

// #define KB_MARCO_COUNT 50
// typedef struct _CMB_KB_MARCO
// {
// #define MARCO_NEW	1
// #define MARCO_LOAD	2
// #define MARCO_DEL	3
// 
// 	int nIndex;
// 	int nType;
// 
// }CBB_MARCO, *PCMB_MARCO;

class CMacroKeyDlg : public CUiDlg
{
	typedef enum {
		BTN_KBMACRO_PROADD = 0,
		BTN_KBMACRO_PROEDIT,
		BTN_KBMACRO_PRODEL,
		BTN_KBMACRO_IMPORT,
		BTN_KBMACRO_EXPORT,
		BTN_KBMACRO_APPLY,
		BTN_KBMACRO_INSFUN,
		BTN_KBMACRO_INSTIME,
		BTN_KBMACRO_DELONE,
		BTN_KBMACRO_DELALL,
		BTN_KBMACRO_KB,
		BTN_KBMACRO_MOUSE,
		BTN_KBMACRO_LOCATION,
		BTN_KBMACRO_ONCLOSE,
	//	BTN_KBMACRO_MINIMIZE,

		BTN_KBMACRO_RECORD,
		BTN_KBMACRO_NUM
	};

	typedef enum {
		STC_KBMACRO_DELAY_TIME = 0,
		STC_KBMACRO_AUTO_DETECT,
		STC_KBMACRO_FIXED_TIME,
		STC_KBMARCO_MS,
		STC_KBMARCO_NO_DELAY,
		STC_KBMARCO_EXEC_MODE,
		STC_KBMARCO_ONE_TIME,
		STC_KBMARCO_LOOP_MODE,
		STC_KBMARCO_FIRE_MODE,
		STC_KBMACRO_KB,
		STC_KBMACRO_MOUSE,
		STC_KBMACRO_LOCATION,
		STC_KBMACRO_HOTKEY,
		STC_KBMACRO_HOTKEY_START,
		STC_KBMACRO_HOTKEY_STOP,
		STC_KBMACRO_NUM
	};

	typedef enum {
		COMBOX_KBMACRO_PROFILE = 0,
		COMBOX_KBMACRO_NUM,
	};

	typedef enum {
		LST_KBMACRO = 0,
	};

	typedef enum {
		PANEL_KBMACRO_DELAYTIME_NAV,
		PANEL_KBMACRO_EXECMODE_NAV,
		PANEL_KBMACRO_NUM,
	};

	typedef enum {
		EDIT_KBMACRO_MACRO,
		EDIT_KBMACRO_MS,
		EDIT_KBMACRO_NUM,
	};


	DECLARE_DYNAMIC(CMacroKeyDlg)

public:
	CMacroKeyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMacroKeyDlg();

	void InitMacroState();
	void LoadMacrosList();

// Dialog Data
	enum { IDD = IDD_VGA_MONITORING };
	void SetDeviceType(int iType) { m_DeviceType = iType; };

protected:

	HICON  m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnPaint();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

	afx_msg LRESULT OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRawInput(UINT nInputcode, HRAWINPUT hRawInput);

	DECLARE_MESSAGE_MAP()

	void	Ui(void);
	void	UiMain(void);

	void	OnClose();
	void	OnMinimize();
	void OnApply();

	void EnableRecodeUi(bool bEnable, bool bRecord = true);
	int  MouseCoorToData(int nValue, int nResolu);
	int  DataToMouseCoor(int nValue, int nResolu);
	CString GetKeyName(DWORD dwKeyCode);
	void ShowMarcoKey(GVORDER_MACROS marco);
	void ShowMarcoUnit(GVORDER_MACROS_UNIT unit);

	//未完成...
	void LoadMarcoKey(int nItem);
	void RecodeMarcoKey();


	void OnClear();
	int  GetEmptyMarcoIndex();
	bool ShowLocation(CPoint pt, bool bInsert);	// ?
	bool ShowInputKey(RAWMOUSE mouse, bool bLocation, bool bInsert);		//？
	bool ShowInputKey(RAWKEYBOARD keyboard, bool bInsert);	// bInsert = true means insert, false means append
	CString ShowInputTime();
	void ShowRealTime(int nDelay, bool bInsert);	//？
	void TranslateKey(RAWKEYBOARD& key);
	bool IsSpecialKey(USHORT vKey);
	void AddMarcoKey();
	void RemoveMarcoKey();
	void EditMarcoName();
	void ImportMarcoKey();
	void ExportMarcoKey();
	void OnDefault();
	void ApplyEnable(bool bEnable);

	CString Browse(LPCTSTR lpszFilter, LPCTSTR lpszDefExt, BOOL bOpen);
	bool MacroIsValid(GVORDER_MACROS_ATTR macro);

	static UINT ApplyThread(LPVOID lpParam);




public:
	void    OnFit(CRect rc);
	void	InitState();

private:

	static int s_nWords;
	static LANG_WORD s_Words[48];

	int  m_nIndex;
	CUiButton m_btn[BTN_KBMACRO_NUM];
	CUiComboBox m_combobox[COMBOX_KBMACRO_NUM];
	CUiStatic m_stc[STC_KBMACRO_NUM];
	CUiPanelCtrl m_panel[PANEL_KBMACRO_NUM];
	CUiListCtrl		m_list;
	CUiEdit m_edit[EDIT_KBMACRO_NUM];
	CUiHotKeyCtrl m_HotKeyStart;
	CUiHotKeyCtrl m_HotKeyStop;

	CBB_MARCO m_cmbMarco[KB_MARCO_COUNT];
	GVORDER_MACROS m_curmarco;
	GVORDER_MACROS m_marcos[KB_MARCO_COUNT]; // Marco Key緩存
	CPtrArray m_lstMarco;	// Marco List，與下拉框對應
	CPtrArray m_delmarco;	// 被刪除的Marco
	CPtrArray m_newmarco;	// 新增的Marco

	CPoint	  m_Resolution; // 屏幕分辨率，用於計算鼠標坐標
	bool	  m_bRecord;	// 是否在記錄
	bool	  m_bUpdate;	// 頁面是否更新内容
	int	 	  m_dwLastTime;	// 上次計時
	int	 	  m_dwLastItem;	// 最後選中的下拉框
	int		  m_DeviceType;

};
