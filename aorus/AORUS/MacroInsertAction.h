// InsertActionDlg.h : header file
//

#pragma once
// 
// #define RAW_DEV_HID 0x01
// #define RAW_DEV_KB  0x02
// #define RAW_DEV_MS  0x04

// CInsertActionDlg dialog
class CInsertActionDlg : public CUiDlg
{
	typedef enum {
		EDIT_INSERT_FUN_X,
		EDIT_INSERT_FUN_Y,
		EDIT_INSERT_FUN_MS,
		EDIT_INSERT_FUN_NUM
	};

	typedef enum {
		STC_INSERT_FUN_SWITCH,
		STC_INSERT_FUN_KB,
		STC_INSERT_FUN_MOUSE,
		STC_INSERT_FUN_LOCATION,
		STC_INSERT_FUN_LOCATION_X,
		STC_INSERT_FUN_LOCATION_Y,
		STC_INSERT_FUN_DELAY,
		STC_INSERT_FUN_DELAY_WORD,
		STC_INSERT_FUN_DELAY_TIME,
		STC_INSERT_FUN_NUM
	};

	typedef enum {
		PAN_INSERT_FUN_SWITCH,
	};

// Construction
public:
	CInsertActionDlg(CWnd* pParent = NULL);	// standard constructor
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data
	enum { IDD = IDD_DLG_INSERT };

	
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	afx_msg void OnPaint();
	afx_msg LRESULT OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRawInput(UINT nInputcode, HRAWINPUT hRawInput);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

	void Ui();
	void UiMain();

	static UINT Recode(LPVOID pParam);
	
private:
	
	static int s_nWords;
	static LANG_WORD s_Words[48];

	CUiStatic m_stc[STC_INSERT_FUN_NUM];
	CUiEdit   m_edit[EDIT_INSERT_FUN_NUM];
	CUiPanelCtrl m_panel;

	bool		m_bRecord;

public:
	int			m_nType;
	int			m_nDelay;
	CPoint		m_pt;
	RAWINPUT	m_input;
};
