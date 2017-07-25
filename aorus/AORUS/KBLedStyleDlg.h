#pragma once




#define LKEY_KBLEDS_CONSISTENCE	0
#define LKEY_KBLEDS_PULSING		1
#define LKEY_KBLEDS_REACTIVE	2
#define LKEY_KBLEDS_RIPPLE		3
#define LKEY_KBLEDS_CYCLING		4
#define LKEY_KBLEDS_WAVE		5
#define LKEY_KBLEDS1_BRIGHTNESS	 6
#define LKEY_KBLEDS1_SPEED		7

#define LKEY_KBLEDS2_BRIGHTNESS	 8
#define LKEY_KBLEDS2_SPEED		9
#define LKEY_KBLEDS2_COLOR		10
#define LKEY_KBLEDS2_RANDOM		11

#define LKEY_KBLEDS3_BRIGHTNESS	 12
#define LKEY_KBLEDS3_SPEED		13
#define LKEY_KBLEDS3_DURATION	14

#define LKEY_KBLEDS_QTY			15

typedef enum {
		SEL_STYLE_CONSISTENCE = 0,
		SEL_STYLE_PULSING,
		SEL_STYLE_REACTIVE,
		SEL_STYLE_RIPPLE,
		SEL_STYLE_CYCLING,
		SEL_STYLE_WAVE
};

class CKBLedStyleDlg : public CUiDlg
{
	typedef enum {
        BTN_KBLEDS_ONOFF = 0,
		BTN_KBLEDS_CLOSE,
		BTN_KBLEDS1_COLOR_1,
		BTN_KBLEDS1_COLOR_2,
		BTN_KBLEDS1_COLOR_3,
		BTN_KBLEDS1_COLOR_4,
		BTN_KBLEDS1_COLOR_5,
		BTN_KBLEDS1_COLOR_6,
		BTN_KBLEDS1_COLOR_7,
		BTN_KBLEDS1_COLOR_8,
		BTN_KBLEDS1_COLOR_9,
		
		BTN_KBLEDS2_COLOR_1,
		BTN_KBLEDS2_COLOR_2,
		BTN_KBLEDS2_COLOR_3,
		BTN_KBLEDS2_COLOR_4,
		BTN_KBLEDS2_COLOR_5,
		BTN_KBLEDS2_COLOR_6,
		BTN_KBLEDS2_COLOR_7,
		BTN_KBLEDS2_COLOR_8,
		BTN_KBLEDS2_COLOR_9,
 		BTN_KBLEDS2_SEL1,
 		BTN_KBLEDS2_SEL2,
 		BTN_KBLEDS2_CLR1,
 		BTN_KBLEDS2_CLR2,

		BTN_KBLEDS3_COLOR_1,
		BTN_KBLEDS3_COLOR_2,
		BTN_KBLEDS3_COLOR_3,
		BTN_KBLEDS3_COLOR_4,
		BTN_KBLEDS3_COLOR_5,
		BTN_KBLEDS3_COLOR_6,
		BTN_KBLEDS3_COLOR_7,
		BTN_KBLEDS3_COLOR_8,
		BTN_KBLEDS3_COLOR_9,

		BTN_KBLEDS4_ADDMODE,
		BTN_KBLEDS4_DELMODE,
		BTN_KBLEDS4_WIDTH_UP,
		BTN_KBLEDS4_WIDTH_DOWN,
		BTN_KBLEDS4_TIME_UP,
		BTN_KBLEDS4_TIME_DOWN,

		/*BTN_KBLEDS5_COLOR_1,
		BTN_KBLEDS5_COLOR_2,
		BTN_KBLEDS5_COLOR_3,
		BTN_KBLEDS5_COLOR_4,
		BTN_KBLEDS5_COLOR_5,
		BTN_KBLEDS5_COLOR_6,
		BTN_KBLEDS5_COLOR_7,
		BTN_KBLEDS5_COLOR_8,
		BTN_KBLEDS5_COLOR_9,*/

		BTN_KBLEDS6_ADDMODE,
		BTN_KBLEDS6_DELMODE,
		BTN_KBLEDS6_ANGLE_UP,
		BTN_KBLEDS6_ANGLE_DOWN,
		BTN_KBLEDS6_TIME_UP,
		BTN_KBLEDS6_TIME_DOWN,

		BTN_KBLEDS_NUM,
	};

	typedef enum {
		COMBOX_KBLEDS_STYLE = 0,
		COMBOX_KNLEDS_RIPPLE,
		COMBOX_KNLEDS_RIPPLE_START,
		COMBOX_KNLEDS_RIPPLE_END,
		COMBOX_KNLEDS_WAVE,
		COMBOX_KNLEDS_WAVE_START,
		COMBOX_KNLEDS_WAVE_END,

		COMBOX_KBLEDS_NUM,
	};

	typedef enum {
		STC_KEYLEDS_CONSISTANCE = 0,
		STC_KEYLEDS_PULSING,
		STC_KEYLEDS_REACTIVE,
		STC_KEYLEDS_RIPPLE,
		STC_KEYLEDS_CYCING,
		STC_KEYLEDS_WAVE,
		STC_KBLEDS1_BRIGHTNESS,
		//STC_KBLEDS1_SPEED,
		STC_KBLEDS1_COLORBG,

		STC_KBLEDS2_BRIGHTNESS,
		STC_KBLEDS2_SPEED,
		STC_KBLEDS2_COLORBG,

		//STC_KBLEDS3_BRIGHTNESS,
		//STC_KBLEDS3_SPEED,
		STC_KBLEDS3_DURATION,
		STC_KBLEDS3_COLORBG,

	//	STC_KBLEDS4_BRIGHTNESS,
		STC_KBLEDS4_SPEED,
		STC_KBLEDS4_COLORBG,
		STC_KBLEDS4_START,
		STC_KBLEDS4_END,
		STC_KBLEDS4_WIDTH,
		STC_KBLEDS4_TIMES,

		STC_KBLEDS5_BRIGHTNESS,
		STC_KBLEDS5_SPEED,
		//STC_KBLEDS5_COLORBG,

	//	STC_KBLEDS6_BRIGHTNESS,
		STC_KBLEDS6_SPEED,
		STC_KBLEDS6_COLORBG,
		STC_KBLEDS6_START,
		STC_KBLEDS6_END,
		STC_KBLEDS6_ANGLE,
		STC_KBLEDS6_TIMES,

		STC_KEYLEDS_NUM,
	};



	typedef enum {
		EDIT_KBLEDS1_R,
		EDIT_KBLEDS1_G,
		EDIT_KBLEDS1_B,

		EDIT_KBLEDS2_R,
		EDIT_KBLEDS2_G,
		EDIT_KBLEDS2_B,

		EDIT_KBLEDS3_R,
		EDIT_KBLEDS3_G,
		EDIT_KBLEDS3_B,

		EDIT_KBLEDS4_WIDTH,
		EDIT_KBLEDS4_TIMES,

		EDIT_KBLEDS5_R,
		EDIT_KBLEDS5_G,
		EDIT_KBLEDS5_B,

		EDIT_KBLEDS6_ANGLE,
		EDIT_KBLEDS6_TIMES,


		EDIT_KBLEDS_NUM,
	};

	typedef enum {
		SLIDER_KBLEDS1_SPEED,
		SLIDER_KBLEDS1_BRGIHTNESS,
		SLIDER_KBLEDS1_RGB,

		SLIDER_KBLEDS2_SPEED,
		SLIDER_KBLEDS2_BRGIHTNESS,
		SLIDER_KBLEDS2_RGB,

		SLIDER_KBLEDS3_SPEED,
		SLIDER_KBLEDS3_BRGIHTNESS,
		SLIDER_KBLEDS3_DURATION,
		SLIDER_KBLEDS3_RGB,

		SLIDER_KBLEDS4_SPEED,
		SLIDER_KBLEDS4_BRGIHTNESS,
		SLIDER_KBLEDS4_RGB,

		SLIDER_KBLEDS5_SPEED,
		SLIDER_KBLEDS5_BRGIHTNESS,
		SLIDER_KBLEDS5_RGB,

		SLIDER_KBLEDS6_SPEED,
		SLIDER_KBLEDS6_BRGIHTNESS,
		SLIDER_KBLEDS6_RGB,

		SLIDER_KBLEDS_NUM,
	};

	typedef enum {
		ANG_KBLED_WAVE,
	};


	DECLARE_DYNAMIC(CKBLedStyleDlg)

public:
	CKBLedStyleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKBLedStyleDlg();
	bool bSyncCyclingSty;

	//Terry 2017/07/17
	//統一控燈鍵盤界面LED STYLE顯示當前支持模式
 	void SyncLedControlMode() {
		SwitchStyle(0);
		m_combobox[COMBOX_KBLEDS_STYLE].ResetContent();
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_CONSISTENCE),  0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_PULSING),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_CYCLING),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].SetCurSel(0);
		SwitchStyle(0);
		m_panelColor.Enable(false);
		m_btn[BTN_KBLEDS2_SEL2].Enable(false);
		m_btn[BTN_KBLEDS2_CLR2].Enable(false);
		bSyncCyclingSty = true;
		UpdateWindow();
	}
	//取消統一控燈鍵盤部分LED STYLE恢復初始支持模式
	void NormalLedMode() {
		SwitchStyle(0);
		m_combobox[COMBOX_KBLEDS_STYLE].ResetContent();
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_CONSISTENCE),  0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_PULSING),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_REACTIVE),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_RIPPLE),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_CYCLING),		0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].AddString(CLangX::Get(s_Words, s_nWords, LKEY_KBLEDS_WAVE),			0, CLR_WHITE);
		m_combobox[COMBOX_KBLEDS_STYLE].SetCurSel(0);
		SwitchStyle(0);

		m_panelColor.Enable(true);
		m_btn[BTN_KBLEDS2_SEL2].Enable(true);
		m_btn[BTN_KBLEDS2_CLR2].Enable(true);
		bSyncCyclingSty = false;
		UpdateWindow();
	}

	DWORD getCurSyncColor() {return CurColor;}
	int getCurSyncStyle() {return m_nCurStyle;}

	//統一控燈鍵盤界面LED開關控制
	bool bSwichStaues(){		
		bool bOn = m_btn[BTN_KBLEDS_ONOFF].IsCheck();
		m_stc[STC_KEYLEDS_CONSISTANCE].EnableWindow(bOn);
		m_stc[STC_KEYLEDS_PULSING].EnableWindow(bOn);
		m_stc[STC_KEYLEDS_CYCING].EnableWindow(bOn);

		return bOn;
	}

	


// Dialog Data
	enum { IDD = IDD_VGA_MONITORING };

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
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnUiSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiSliderMoving(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiEditChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiMulitSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiAngleChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void	Ui(void);
	void	UiMain(void);
	void	OnClose();
	void	SwitchStyle(int nStyle);

	void	OnColor(COLORREF clr);
	void	EditRGBChange();
	void	ShowClr(int nStyle, KB_CLR_CFG clr[]);
	void	LoadPresent();
	void	SaveCLRPress(int nType);

public:
	void    OnFit(CRect rc);
	void	InitState();
	int		GetCurStyle();	// Peter Lee 2017/6/19
	void	ReadClr(int nStyle, KB_CLR_CFG& clr);
	void	ReadCfg(int nPage, KB_LED_CFG& cfg);
	bool	IsBreathing1Selected();

private:
	CUiButton m_btn[BTN_KBLEDS_NUM];
	CUiComboBox m_combobox[COMBOX_KBLEDS_NUM];
// 
// 	CKBLedConsistDlg m_StyleConsist;
// 	CKBLedPulsingDlg m_StylePulsing;
// 	CKBLedReactiveDlg m_StyleReactive;
// 	CKBLedRippleDlg m_StyleRipple;
// 	CKBLedCyclingDlg m_StyleCycling;
// 	CKBLedWaveDlg m_StyleWave;

	static int s_nWords;
	static LANG_WORD s_Words[48];
	int m_nCurStyle;

	CUiStatic m_stc[STC_KEYLEDS_NUM];
	CUiEdit	m_edit[EDIT_KBLEDS_NUM];
	CUiSliderCtrl m_slider[SLIDER_KBLEDS_NUM]; 
	CUiMulitSliderCtrl m_mulitslider[SLIDER_KBLEDS_NUM]; 
	CUiPanelCtrl m_panelColor;
	CUiAngleCtrl	m_AngleCtrl;

	int m_nRippleLastSel;
	int m_nWaveLastSel;

	KB_LED_CFG m_config[6];
	KB_LED_CFG m_curCfg;

	COLORREF CurColor;

};
