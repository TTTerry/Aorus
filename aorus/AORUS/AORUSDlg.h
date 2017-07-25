// AORUSDlg.h : header file
//

#pragma once
#include"VGAHomeDlg.h"
#include "DisplayClkDlg.h"
#include "LedDlg.h"
#include "VgaProfDlg.h"
#include "RemoteSetting.h"
#include "SettingDlg.h"
#include "MonitorDlg.h"
#include "KeyAssignDlg.h"
#include "KBLedDlg.h"
#include "MousePointerDlg.h"
#include "MouseButtonDlg.h"
#include "MacroKeyDlg.h"
#include "inc/vga/MobileCtrl.h"

#include ".\inc\mouse\AM300Cmd.h"
#include ".\inc\mouse\AM300Ctrl.h"
#include ".\inc\mouse\CmdFormat.h"


// CAORUSDlg dialog
class CAORUSDlg : public CUiDlg
{
// Construction
	#define TRAYICON_UID			0x01001001
	#define TIMER_HOME_LEDRANDOM	1
	typedef enum _HOME_BTN_ID // °´Å¥
	{
		BTN_HOME_REMOTE=0,
		BTN_HOME_SETTING,
		BTN_HOME_MIN,
		BTN_HOME_CLOSE,
		BTN_HOME_MENULEFT,
		BTN_HOME_MENURIGHT,
		BTN_HOME_LED,
		BTN_HOME_MONIT,
		BTN_HOME_SEMIPASS,
		BTN_HOME_ENTERPRO,
		BTN_HOME_BACKHOME,
		BTN_HOME_DEVARROWL,
		BTN_HOME_DEVARROWR,

		BTN_HOME_MACRO,
		BTN_HOME_POINTER,
		BTN_HOME_MOUSEBUTTON,
		BTN_HOME_KEYASSIGN,

		BTN_HOME_NUM
	}home_btn;
	typedef enum _HOME_PNL_ID
	{
		PAN_HOME_DEVICE=0,
		PAN_HOME_NUM
	}home_pan;
	typedef enum _HOME_STC_ID
	{
		STC_HOME_GIGABYTE_LOGO,
		STC_HOME_AORUS_LOGO,
		STC_HOME_RGB_FUSION,
		STC_HOME_NUM
	}home_stc;
	typedef enum _HOME_COMB_ID
	{
		COMB_HOME_CARDSEL,
		COMB_HOME_NUM
	}home_comb;
public:
	CAORUSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AORUS_DIALOG };

// Implementation
protected:
	HICON m_hIcon;
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiPanelSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	LRESULT OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);

	afx_msg void OnRawInput(UINT nInputcode, HRAWINPUT hRawInput);

	void OnOK(){}
	DECLARE_MESSAGE_MAP()

public:
	void Initstate();

    void SwitchUI(int nBtnClick);
	void UpdateCardSelCombbox(int nDeviceId); 
	void SyncLedBtnClr(COLORREF clr);
	CRect OnFit(CRect rcCli, int nLeft, int nTop);
	void SyncMobile(WPARAM wParam, LPARAM lParam);
	void MobileUpdateUI(int nWhatToUpdate);
	void Enable(bool bEnable);
	bool IsMonitorShow();
    bool GetFanStopState();
	void OnFollowMove(int nType, CRect rc);
	
	int GetDeviceSel();
	CVGA* GetVGA()  { return &m_DevVGA; }
	int  GetVGASel() { return m_nVGASel; }
	int  GetVGAProfileSel() { return m_nVGAProSel; }
	void SetVGAProfileSel(int nProfile) { m_nVGAProSel = nProfile; }

	CCfg* GetCfg();
	CDevice* GetDevice(int nDevice/*should be DEVICE_*** */);  
	void ReInitAllDevicesLedState(); // Re-init all devices' led dialog state, if led-sync is changed.
	
	CMobileCtrl m_MobileCtrl;

	void ScanDevices();
	void ScanDevice(CString sDevice);
	void FreeDevice(CString sDevice);
	static UINT OnScanDevice(LPVOID pParam);
	
	void Ui();
	void UiMain();
	void OnMinimize();
	void OnClose();
	void OnOpen();
	void SwitchDevice(int nId);

	void CreateDeivceIcons();
	void UpdateDeivceIcons();
	void ShowDeviceIcons(CArray<UINT>& deviceIds, bool bShow);

	static UINT KeepLedMonitor(LPVOID pParam);

	void SwitchM3LedDlProfile(int iProfile);
	void SwitchM3ButtonProfile(int iProfile);
	void SwitchAK700LedProfile(int iProfile);
	void SwitchAK700KeyProfile(int iProfile);

	BOOL KillProcessFromName(CString strProcessName);


private:
	int m_nVGASel;
	int m_nVGAProSel;	// VGA profile selected
	int m_nDeviceSel;	// ex: DEVICE_VGA
	int m_nDevShiftL;	// Device icon left shift
	int m_LastVgaSel;
	bool m_bWinClose;

    CVGAHomeDlg  m_VgaHomeDlg;
	CDisplayClkDlg m_DispClkDlg;
    CVgaProfDlg m_VgaProDlg;
    CRemoteSetting m_cRemoteSettingDlg;
	CSettingDlg  m_settingDlg;
	CMonitorDlg m_CMonitorDlg;
	CLedDlg m_LedDlg[DEVICE_COUNT];

	CKeyAssignDlg m_KeyAssignDlg;
	CMacroKeyDlg m_MacroKeyDlg;
	CKBLedDlg m_KBLedDlg;
	CMousePointerDlg m_MousePointerDlg;
	CMouseButtonDlg m_MouseButtonDlg;


	CUiButton m_btn[BTN_HOME_NUM];
	CUiPanelCtrl m_panel[PAN_HOME_NUM];
	CUiStatic m_stc[STC_HOME_NUM];
	CUiComboBox m_combobox[COMB_HOME_NUM];
	CUiTrayIcon	m_trayIcon;

	static CCfg m_Cfg; // must declare as staic variable, or will cause stack overflow.

	CMB		m_DevMB;
	CVGA	m_DevVGA;
	CSLI	m_DevSLI;
	CATC700 m_DevATC700;
	CAC300	m_DevAC300;
	CAH300	m_DevAH300;
	CAM300	m_DevAM300;
	CAK700		m_DevAK700;
	CH5			m_DevH5;

	
	HANDLE m_hInstance;
	HDEVNOTIFY m_deviceNotifyHandle;  // for receive WM_DEVICECHANGE message
};


