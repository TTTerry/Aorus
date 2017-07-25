#pragma once

// CCustomizedDlg 对话框
#define CUST_TYPE_CLK 0
#define CUST_TYPE_FAN 1

class CCustomizedDlg : public CUiDlg
{
	typedef enum _VGACUSTOMIZED_STC_ID
	{
		STC_VGACUS_CAPTION,
		STC_VGACUS_Y_CAPTION,
		STC_VGACUS_X_CAPTION,
		STC_VGACUS_Y_1,
		STC_VGACUS_Y_2,
		STC_VGACUS_Y_3,
		STC_VGACUS_Y_4,
		STC_VGACUS_Y_5,
		STC_VGACUS_Y_6,

		
		
		STC_VGACUS_X_1,
		STC_VGACUS_X_2,
		STC_VGACUS_X_3,
		STC_VGACUS_X_4,
		STC_VGACUS_X_5,
		STC_VGACUS_X_6,
		STC_VGACUS_X_7,
		STC_VGACUS_X_8,
		STC_VGACUS_X_9,
		STC_VGACUS_X_10,
		STC_VGACUS_X_11,
		STC_VGACUS_NUM,
		STC_VGACUS_CURVE
	};
	typedef enum _VGACUSTOMIZED_BTN_ID
	{
		BTN_VGACUS_CLOSE,
		BTN_VGACUS_ACTIVEOC,
		BTN_VGACUS_NUM
	};
	DECLARE_DYNAMIC(CCustomizedDlg)

public:
	CCustomizedDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCustomizedDlg();

	void InitState();
	void ShowOcScannerBtn(bool flag);
	void UpdateUI(int Cureveindex);
	void GetGpuVFCurve(VGA_PERFORMANCE &perf);
	void GetFanVFCurve(FAN_SETTING &fansetting);
	int PtToClk(int nPt);
	int PtToVol(int nPt);
	int VolToPt(int nVol);
	int ClkToPt(int nClk);
	bool isPass();
	void ResetFurmark();
	void OnScanerFinish(int nIndex, int nVol, int nClk);
	void OnScanerApply();

	int SetType(int nType);
	int GetType();
	void OnFit(CRect rc);
    void OnReset();
	void OnDefault();
// 对话框数据
	enum { IDD = IDD_VGA_CUSTOMIZED_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void Ui();
	void UiMain();
	CPoint NoFanStopcurvePts[10];
	int NoFanStopCurveNum;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnUiCurveMoving(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiCurveMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiCurveRemove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUiButtonClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFanStopStateChange(WPARAM wParam, LPARAM lParam);
	static DWORD OCScannerThread(LPVOID lpParameter);
	DECLARE_MESSAGE_MAP()

private:
	CUiStatic m_stc[STC_VGACUS_NUM];
	CUiButton m_btn[BTN_VGACUS_NUM];

	CUiStatic  m_stcCurve;
	CUiCurveGraphCtrl  m_GpuClkScan;
	CUiCurveGraphCtrl  m_GpuClkCurve;
	CUiCurveGraphCtrl  m_fanCurve;

	int m_CurCurve;//0:gpu clock;1:fanspeed;
	GVDISP_CLOCK_VFPTS m_VFGpuclkBase;
	GVDISP_CLOCK_VFSET m_VFGpuclkCus;
	GVDISP_CLOCK_VFSET m_defaultVFGpuCus;
	int m_nMinVoltage;
	int m_nMaxVoltage;

	BOOL m_bScanning;
	int m_nFurmarkLastCount;
	HANDLE m_hThread;
	CFurmarkReader m_Reader;
	GVDISP_CLOCK_VFPTS m_ScanClks;

	GVDISP_CLOCK_VFPTS m_Clks;
	GVDISP_CLOCK_VFPTS m_DefaultClks;
	GVDISP_CLOCK_VFSET m_Offsets;
	CPoint m_curvePt[100];
	CPoint m_DefaultPt[100];
	int m_nVolIndex;

	int	m_nType;
};
