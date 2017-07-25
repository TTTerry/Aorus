// CustomizedDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AORUS.h"
#include "CustomizedDlg.h"
#include "AORUSDlg.h"

// CCustomizedDlg 对话框
static CString s_FanCvrY[]={L"100",L"80",L"60",L"40",L"20",L"0"};
static CString s_FanCvrX[]={L"0",L"10",L"20",L"30",L"40",L"50",L"60",L"70",L"80",L"90",L"100"};
static CString s_GpuCvrY[]={L"3000",L"2400",L"1800",L"1200",L"600",L"0"};
//static CString s_GpuCvrX[]={L"0.45",L"0.52",L"0.61",L"0.69",L"0.77",L"0.85",L"0.92",L"1.00",L"1.07",L"1.17",L"1.24"};
static CString s_GpuCvrX[]={L"0.80",L"0.84",L"0.88",L"0.92",L"0.96",L"1.00",L"1.04",L"1.08",L"1.12",L"1.16",L"1.24"};
static CString s_GpuScanX[]={L"0.80",L"0.84",L"0.88",L"0.92",L"0.96",L"1.00",L"1.04",L"1.08",L"1.12",L"1.16",L"1.24"};


IMPLEMENT_DYNAMIC(CCustomizedDlg, CUiDlg)

CCustomizedDlg::CCustomizedDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CCustomizedDlg::IDD, pParent)
{
	m_bScanning = false;
	m_hThread = NULL;
	for (int i = 0; i < 100; i++)
	{
		m_curvePt[i] = CPoint(-1, -1);
	}
	NoFanStopCurveNum=0;
}

CCustomizedDlg::~CCustomizedDlg()
{
	if(NULL != m_hThread)
	{
		m_Reader.Destroy();
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

void CCustomizedDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomizedDlg, CUiDlg)
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_GRAPHCTRL_MOVING, OnUiCurveMoving)
	ON_MESSAGE(WM_UI_GRAPHCTRL_MOVED, OnUiCurveMoved)
	ON_MESSAGE(WM_FANTOP_BTN_CHANGE,OnFanStopStateChange)
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
END_MESSAGE_MAP()


// CCustomizedDlg 消息处理程序
BOOL CCustomizedDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	return true;
}

void CCustomizedDlg::Ui()
{
	UiMain();
}

void CCustomizedDlg::UiMain()
{
	SetBkBitmap(IDB_CUSTOMIZE_BG, 0xff, CLR_TRPT);
	UI_STATIC stc[]=
	{
		UI_STATIC(this, STC_VGACUS_CAPTION,	CRect(7, 12, 102, 26), CLangX::Get(LANG_VGACUST_CAP), NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_CAPTION,	CRect(30, 40, 246, 54), CLangX::Get(LANG_VGACUST_CLK), NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_CAPTION,	CRect(89, 231, 249, 252), CLangX::Get(LANG_VGACUST_VOL) , NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_1,	CRect(5, 64, 31, 74), L"3000", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_2,	CRect(5, 91, 31, 101), L"2400", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_3,	CRect(5, 119, 31, 129), L"1800", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_4,	CRect(5, 146, 31, 156), L"1200", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_5,	CRect(5, 173, 31, 183), L"800", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_Y_6,	CRect(5, 200, 31, 210), L"0", NULL, CLR_TRPT),
	
		UI_STATIC(this, STC_VGACUS_X_1,	CRect( 25, 213,  48, 231), L"0.58", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_2,	CRect( 50, 213,  71, 231), L"0.67", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_3,	CRect( 73, 213,  97, 231), L"0.74", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_4,	CRect( 99, 213, 120, 231), L"0.81", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_5,	CRect(120, 213, 144, 231), L"0.88", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_6,	CRect(145, 213, 168, 231), L"0.95", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_7,	CRect(170, 213, 191, 231), L"1.02", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_8,	CRect(192, 213, 213, 231), L"1.09", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_9,	CRect(216, 213, 237, 231), L"1.16", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_10,CRect(239, 213, 260, 231), L"1.23", NULL, CLR_TRPT),
		UI_STATIC(this, STC_VGACUS_X_11,CRect(261, 213, 282, 231), L"1.20", NULL, CLR_TRPT),
	};
	m_stc[STC_VGACUS_CAPTION].CreateStatic(stc[STC_VGACUS_CAPTION]);
	m_stc[STC_VGACUS_CAPTION].ModifyCtrlStyle(0, ST_LEFT | ST_VCENTER | ST_SINGLELINE);
	m_stc[STC_VGACUS_CAPTION].SetFont(Font(11), CLR_MAIN);

	for (int i = STC_VGACUS_Y_1;i <= STC_VGACUS_X_11;i++)
	{
		m_stc[i].CreateStatic(stc[i]);
		m_stc[i].ModifyCtrlStyle(0, ST_RIGHT | ST_VCENTER | ST_SINGLELINE);
		m_stc[i].SetFont(Font(8), CLR_WHITE);
	}
	for (int i = STC_VGACUS_Y_CAPTION;i <= STC_VGACUS_X_CAPTION;i++)
	{
		m_stc[i].CreateStatic(stc[i]);
		m_stc[i].ModifyCtrlStyle(ST_BOTTOM,ST_LEFT);
		m_stc[i].SetFont(Font(11), CLR_MAIN);
	}
	m_stc[STC_VGACUS_X_CAPTION].ModifyCtrlStyle(ST_LEFT, ST_CENTER);

	m_btn[BTN_VGACUS_CLOSE].CreateButton( UI_BTN(this, BTN_VGACUS_CLOSE,   CRect(272, 9,  0,0),&UIBTN_IMAGE(IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, IDB_HOME_CLOSEON, 0, 0, 0, 0, 0, CLR_TRPT)));
	m_btn[BTN_VGACUS_CLOSE].SetCursor(IDC_CUR_HAND);

	m_btn[BTN_VGACUS_ACTIVEOC].CreateButton( UI_BTN(this, BTN_VGACUS_ACTIVEOC,   CRect(85, 260,  0,0),&UIBTN_IMAGE(IDB_BIGBTN_ON, IDB_BIGBTN_ON, IDB_BIGBTN_ON, 0, 0, 0, 0, 0, CLR_TRPT),&UIBTN_STRING(CLangX::Get(LANG_VGACUST_ACTOCSCANER),	CLR_WHITE, CLR_WHITE,CLR_WHITE,0,Font(9))));
	m_btn[BTN_VGACUS_ACTIVEOC].SetCursor(IDC_CUR_HAND);


	
	//m_stcCurve.CreateStatic(UI_STATIC(this, STC_VGACUS_CURVE,  CRect(34, 68, 268, 208), _T(""), 0, CLR_TRPT));
	m_stcCurve.CreateStatic(UI_STATIC(this, STC_VGACUS_CURVE,  CRect(31, 58, 285, 213), _T(""), 0, CLR_TRPT));
	//m_GpuClkCurve.Create(&m_stcCurve, 0, CRect(0, 0, 234, 140));
	m_GpuClkCurve.Create(&m_stcCurve, 0, CRect(0, 0, 254, 155));
	m_GpuClkCurve.SetAdjustDirection(UICGC_ADJUST_YDIR); // 設置y可以調整
	m_GpuClkCurve.SetCursor(IDC_CUR_HAND);
	m_GpuClkCurve.CreateGraph(0, 2, CLR_MAIN, CLR_MAIN); // ?的index，?的?度，?和點的?色
	m_GpuClkCurve.CreateGraph(1, 2, CLR_GRAY, CLR_GRAY); // ?的index，?的?度，?和點的?色
	m_GpuClkCurve.SetCoordXRange(0, 100); // 設置x和y的range
	m_GpuClkCurve.SetCoordYRange(0, 3000);
	m_GpuClkCurve.SetAdjustYRange(0, 3000);
	//m_GpuClkCurve.SetMargin(2, 2, 13, 2);
	//m_GpuClkCurve.SetMargin(10, 10, 10, 5);
	m_GpuClkCurve.SetMargin(5, 10, 16, 6);
	m_GpuClkCurve.SetFont(Font(11), CLR_WHITE);
	m_GpuClkCurve.AddPoint(true);
	m_GpuClkCurve.SetFreeMove(true); // 設置自由移動，不受前後點位置Y軸約束
	m_GpuClkCurve.MoveTotal(false);
	/*CPoint curvePts[2] = {CPoint(0, 0), CPoint(100, 0)};
	m_GpuClkCurve.SetValue(0, curvePts, 2);*/
	m_GpuClkCurve.SetValueRatio((float)0.00625, 1);
	m_GpuClkCurve.ShowWindow(SW_SHOW);
	m_GpuClkCurve.Enable(1, false);
	m_GpuClkCurve.ShowPoint(1, false);

	m_GpuClkScan.Create(&m_stcCurve, 1, CRect(0, 0, 254, 155));
	m_GpuClkScan.SetAdjustDirection(UICGC_ADJUST_YDIR); // 設置y可以調整
	m_GpuClkScan.SetCursor(IDC_CUR_HAND);
	m_GpuClkScan.CreateGraph(0, 2, CLR_GRAY, CLR_GRAY); // ?的index，?的?度，?和點的?色
	m_GpuClkScan.CreateGraph(1, 2, CLR_MAIN, CLR_MAIN); // ?的index，?的?度，?和點的?色
	m_GpuClkScan.SetCoordXRange(8000000, 12400000); // 設置x和y的range
	m_GpuClkScan.SetCoordYRange(0, 3000);
	m_GpuClkScan.SetAdjustYRange(0, 3000);
	//m_GpuClkScan.SetMargin(10, 10, 10, 5);
	m_GpuClkScan.SetMargin(5, 10, 16, 6);
	m_GpuClkScan.SetFont(Font(11), CLR_WHITE);
	m_GpuClkScan.AddPoint(false);
	m_GpuClkScan.SetFreeMove(false); // 設置自由移動，不受前後點位置Y軸約束
	m_GpuClkScan.MoveTotal(false);
	m_GpuClkScan.SetValueRatio((float)0.00625, 1);
	m_GpuClkScan.Enable(0, false);
	m_GpuClkScan.Enable(1, false);
	m_GpuClkScan.EnableLine(0, true);
	m_GpuClkScan.ShowPoint(0, false);
	m_GpuClkScan.EnableLine(1, false);
	m_GpuClkScan.ShowWindow(SW_SHOW);

	VGA_PARAM_RANGE	fanR;
	Aorus()->GetVGA()->Ctrl()->GetPerfInfo(VGA_PERF_FANSPD ,fanR);
	//m_fanCurve.Create(this, 0, CRect(456, 118, 851, 383));
	//m_fanCurve.Create(&m_stcCurve, 0, CRect(0, 0, 234, 140));
	m_fanCurve.Create(&m_stcCurve, 2, CRect(0, 0, 254, 155));
	m_fanCurve.SetAdjustDirection(UICGC_ADJUST_XYDIR); // 設置xy都可以調整
	m_fanCurve.SetCursor(IDC_CUR_HAND);
	m_fanCurve.CreateGraph(0, 4, CLR_MAIN, CLR_GRAY); // ?的index，?的?度，?和點的?色
	m_fanCurve.SetCoordXRange(0, 100); // 設置x和y的range
	m_fanCurve.SetCoordYRange(0, 100);
	m_fanCurve.SetAdjustXRange(0, 100);
	m_fanCurve.SetAdjustYRange(0, 100);
	//m_fanCurve.SetMargin(5, 13, 5, 5);
	m_fanCurve.SetMargin(5, 10, 16, 6);
	m_fanCurve.SetFont(Font(11), CLR_WHITE);
	m_fanCurve.AddPoint(true);
	m_fanCurve.SetValueUnit(_T("°C"), _T("%"));
	m_fanCurve.SetFreeMove(false); // 設置自由移動，不受前後點位置Y軸約束
	m_fanCurve.MoveTotal(false);
// Peter Lee 2017/6/16 removed debug setting
/*#ifdef _DEBUG
	m_fanCurve.SetAdjustYRange(0, 100);
#else
	m_fanCurve.SetAdjustYRange(fanR.nMin, fanR.nMax);
#endif*/
	m_fanCurve.SetAdjustYRange(fanR.nMin, fanR.nMax);
	m_fanCurve.ShowWindow(SW_HIDE);
}

void CCustomizedDlg::UpdateUI(int Cureveindex)
{
	if(Cureveindex == 0)
	{
		//GPUCLK 曲?圖
		//m_FanSpdCurve.ShowWindow(SW_HIDE);
		for(int i=STC_VGACUS_Y_1;i<=STC_VGACUS_Y_6;i++)
		{
			m_stc[i].SetCaption(s_GpuCvrY[i-STC_VGACUS_Y_1]);
		}
		for(int i=STC_VGACUS_X_1;i<=STC_VGACUS_X_11;i++)
		{
			m_stc[i].SetCaption(s_GpuCvrX[i-STC_VGACUS_X_1]);
		}
		m_stc[STC_VGACUS_Y_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_CLK));
		m_stc[STC_VGACUS_X_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_VOL));

		/*VGA_PERFORMANCE perf;
		Aorus()->GetCfg()->GetPerformances(VGA_PERF_GCLKCUV,perf,Aorus()->GetVGAProfileSel(),Aorus()->GetVGASel());
		VGA_SPECIALPERFS spePerf;
		Aorus()->GetVGA()->Ctrl()->GetSpecialPerformaces(spePerf);
		int numpoint=perf.GpuVf.nNumVFPoints;
		CPoint curvePts[GVDISP_VFPT_MAXNUM];
		//if(perf.dwGpuClkCurve==CLK_CURVE_MANUAL&&numpoint>0)
		if(numpoint>0)
		{
			for(int i = 0; i < perf.GpuVf.nNumVFPoints; i++)
			{
				curvePts[i] = CPoint(
					VolToPt(Aorus()->GetVGA()->Ctrl()->OffsetIndexToVol(perf.GpuVf.offset[i].nIndex)), 
					ClkToPt(Aorus()->GetVGA()->Ctrl()->OffsetToVFPtClk(perf.GpuVf.offset[i]))
					); 
			}
			m_GpuClkCurve.SetValue(0, curvePts, perf.GpuVf.nNumVFPoints);
		}*/
		m_fanCurve.ShowWindow(SW_HIDE);
		m_GpuClkScan.ShowWindow(SW_HIDE);
		m_GpuClkCurve.ShowWindow(SW_SHOW);
	}
	else if(Cureveindex == 1)
	{
		//FANSPEED曲?圖
		for(int i=STC_VGACUS_Y_1;i<=STC_VGACUS_Y_6;i++)
		{
			m_stc[i].SetCaption(s_FanCvrY[i-STC_VGACUS_Y_1]);
		}
		for(int i=STC_VGACUS_X_1;i<=STC_VGACUS_X_11;i++)
		{
			m_stc[i].SetCaption(s_FanCvrX[i-STC_VGACUS_X_1]);
		}
		m_stc[STC_VGACUS_Y_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_FANSPD));
		m_stc[STC_VGACUS_X_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_FANTEMP));

		//m_GpuClkCurve.ShowWindow(SW_HIDE);
		/*FAN_SETTING fansetting;
		Aorus()->GetCfg()->GetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());
		int numpoint=fansetting.nCurveStep;
		if(numpoint>0,fansetting.nFanMode==VGA_FANMODE_DEFINE)
		{
			CPoint curvePts[GVDISP_FANCURVE_MAXNUM];
			for(int i=0;i<numpoint;i++)
			{
				curvePts[i]=CPoint(fansetting.curve[i].nTemperature,fansetting.curve[i].nFanSpeed);
			}
			m_fanCurve.SetValue(0,curvePts,numpoint);
		}*/
		m_GpuClkCurve.ShowWindow(SW_HIDE);
		m_GpuClkScan.ShowWindow(SW_HIDE);
		m_fanCurve.ShowWindow(SW_SHOW);
	}
	else
	{
		for(int i=STC_VGACUS_Y_1;i<=STC_VGACUS_Y_6;i++)
		{
			m_stc[i].SetCaption(s_GpuCvrY[i-STC_VGACUS_Y_1]);
		}
		for(int i=STC_VGACUS_X_1;i<=STC_VGACUS_X_11;i++)
		{
			m_stc[i].SetCaption(s_GpuScanX[i-STC_VGACUS_X_1]);
		}

		m_stc[STC_VGACUS_Y_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_CLK));
		m_stc[STC_VGACUS_X_CAPTION].SetCaption(CLangX::Get(LANG_VGACUST_VOL));

		m_fanCurve.ShowWindow(SW_HIDE);
		m_GpuClkCurve.ShowWindow(SW_HIDE);	
		m_GpuClkScan.ShowWindow(SW_SHOW);	
	}

	m_nType = Cureveindex;
}

void CCustomizedDlg::InitState()
{
		//初始化风扇默认图
	FAN_SETTING FanDefaultSetting;
	Aorus()->GetVGA()->Ctrl()->GetFanAutoSetting(FanDefaultSetting);
	CPoint FancurvePts[10];
	for(int i=0; i<FanDefaultSetting.nCurveStep; i++)
	{
		FancurvePts[i].x = FanDefaultSetting.curve[i].nTemperature;
		FancurvePts[i].y = FanDefaultSetting.curve[i].nFanSpeed;
	}
	m_fanCurve.SetValue(0, FancurvePts, FanDefaultSetting.nCurveStep);
	m_fanCurve.ShowWindow(FALSE);

	if(!Aorus()->GetVGA()->Ctrl()->IsNvCard()) return;
	ZeroMemory(&m_Clks, sizeof(GVDISP_CLOCK_VFPTS));
	ZeroMemory(&m_Offsets, sizeof(GVDISP_CLOCK_VFSET));

	Aorus()->GetVGA()->Ctrl()->GetGpuBaseVfs(m_VFGpuclkBase);
	Aorus()->GetVGA()->Ctrl()->GetGpuBaseVfs(m_DefaultClks);
	Aorus()->GetVGA()->Ctrl()->GetGpuBaseVfs(m_Clks);
	Aorus()->GetVGA()->Ctrl()->GetGpuBaseSet(m_Offsets);

	if(m_Clks.nNumVFPoints <= 0) 
		return;

	for (int i = 0; i < m_Clks.nNumVFPoints; i++)
	{
		if(m_DefaultClks.vfs[i].value.nVoltage < 800000) m_nVolIndex = i;
		m_DefaultPt[i] = CPoint(m_DefaultClks.vfs[i].value.nVoltage, m_DefaultClks.vfs[i].value.nClock / 2);
	}

	int nMinVoltage = 800000;//m_DefaultClks.vfs[0].value.nVoltage;
	int nMaxVoltage = m_DefaultClks.vfs[m_DefaultClks.nNumVFPoints - 1].value.nVoltage;

	m_GpuClkScan.SetCoordXRange(nMinVoltage, nMaxVoltage);
	m_GpuClkScan.SetAdjustXRange(nMinVoltage, nMaxVoltage);
	m_GpuClkCurve.SetCoordXRange(nMinVoltage, nMaxVoltage);
	m_GpuClkCurve.SetAdjustXRange(nMinVoltage, nMaxVoltage);
	m_GpuClkScan.SetValue(0, &m_DefaultPt[m_nVolIndex], m_DefaultClks.nNumVFPoints - m_nVolIndex - 1);
	m_GpuClkCurve.SetValue(1, &m_DefaultPt[m_nVolIndex], m_DefaultClks.nNumVFPoints - m_nVolIndex - 1);

	//m_ocCurve.SetAdjustYRange(m_nMinBase + range.nMin / 4 - 10, m_nMaxBase + range.nMax / 4); 
	double fOffset = (m_VFGpuclkBase.nNumVFPoints-m_nVolIndex) / 10.0;
	int nCount = 11, nIndex = 0;
	CPoint curvePts[11];
	for (int i = m_nVolIndex; i < m_VFGpuclkBase.nNumVFPoints || nIndex < 10; i = (int)(fOffset * nIndex) + m_nVolIndex)
	{
		GVDISP_CLOCK_VFPT vfpt = m_VFGpuclkBase.vfs[i];
		vfpt.value.nClock /= 2;
		m_VFGpuclkCus.offset[nIndex] = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
		nIndex++;
	}

	m_ScanClks.nNumVFPoints=m_VFGpuclkBase.nNumVFPoints;
	for (int i = 0; i < m_VFGpuclkBase.nNumVFPoints; i++)
	{
		m_ScanClks.vfs[i]=m_VFGpuclkBase.vfs[i];
	}


	GVDISP_CLOCK_VFPT vfpt = m_VFGpuclkBase.vfs[m_VFGpuclkBase.nNumVFPoints - 1];
	vfpt.value.nClock /= 2;
	m_VFGpuclkCus.offset[nCount - 1] = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
	m_VFGpuclkCus.nNumVFPoints = nCount;
	m_defaultVFGpuCus = m_VFGpuclkCus;
	m_nMinVoltage =800000; //m_VFGpuclkBase.vfs[0].value.nVoltage;
	m_nMaxVoltage = m_VFGpuclkBase.vfs[m_VFGpuclkBase.nNumVFPoints - 1].value.nVoltage;

	//初始化GPU默认图
	CPoint curveClkPts[100];
	for(int i = 0; i < m_VFGpuclkCus.nNumVFPoints; i++)
	{
		curveClkPts[i] = CPoint(
			VolToPt(Aorus()->GetVGA()->Ctrl()->OffsetIndexToVol(m_VFGpuclkCus.offset[i].nIndex)), 
			ClkToPt(Aorus()->GetVGA()->Ctrl()->OffsetToVFPtClk(m_VFGpuclkCus.offset[i]))
			); 
	}
	m_GpuClkCurve.SetValue(0, curveClkPts, m_VFGpuclkCus.nNumVFPoints);
	m_GpuClkCurve.ShowWindow(SW_SHOW);



}

void CCustomizedDlg::ShowOcScannerBtn(bool flag)
{
	if(flag)
	{
		if(!Aorus()->GetVGA()->Ctrl()->IsOneStepCard())
		{
			m_btn[BTN_VGACUS_ACTIVEOC].ShowWindow(SW_HIDE);
		}
		else
		{
			m_btn[BTN_VGACUS_ACTIVEOC].ShowWindow(SW_HIDE);
			m_btn[BTN_VGACUS_ACTIVEOC].ShowWindow(SW_SHOW);
		}
	}
	else
	{
		m_btn[BTN_VGACUS_ACTIVEOC].ShowWindow(SW_HIDE);
	}
}

int CCustomizedDlg::ClkToPt(int nClk)
{
	return nClk;
}

int CCustomizedDlg::PtToClk(int nPt)
{
	return nPt;
}

int CCustomizedDlg::VolToPt(int nVol)
{
	return nVol/* / 6250*/;
}

int CCustomizedDlg::PtToVol(int nPt)
{
	return nPt/* * 6250*/;
}

LRESULT CCustomizedDlg::OnUiCurveMoving(WPARAM wParam, LPARAM lParam)
{
	CPoint *Pt = (CPoint*)lParam;
	switch(wParam)
	{
	case 0: 
		{
			VGA_PARAM_RANGE range;
			Aorus()->GetVGA()->Ctrl()->GetPerfInfo(VGA_PERF_GPUCLK, range);
			GVDISP_CLOCK_VFPT vfpt;
			vfpt.value.nVoltage = PtToVol(Pt->x);
			vfpt.value.nClock = PtToClk(Pt->y);
			GVDISP_CLOCK_VFOFFSET offset = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
			if (offset.nOffset > range.nMax) offset.nOffset = range.nMax;
			if (offset.nOffset < range.nMin) offset.nOffset = range.nMin;
			vfpt = Aorus()->GetVGA()->Ctrl()->OffsetToVFPt(offset);
			Pt->y = ClkToPt(vfpt.value.nClock);
			Pt->x = VolToPt(vfpt.value.nVoltage);
		}
		break;
	case 1:
		{

		}
		break;
	}
	return 1;
}

LRESULT CCustomizedDlg::OnUiCurveMoved(WPARAM wParam, LPARAM lParam)
{
	CPoint *Pt = (CPoint*)lParam;
	switch(wParam)
	{
	case 0: 
		{
			VGA_PARAM_RANGE range;
			Aorus()->GetVGA()->Ctrl()->GetPerfInfo(VGA_PERF_GPUCLK, range);
			GVDISP_CLOCK_VFPT vfpt;
			vfpt.value.nVoltage = PtToVol(Pt->x);
			vfpt.value.nClock = PtToClk(Pt->y);
			GVDISP_CLOCK_VFOFFSET offset = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
			if (offset.nOffset > range.nMax) offset.nOffset = range.nMax;
			if (offset.nOffset < range.nMin) offset.nOffset = range.nMin;
			vfpt = Aorus()->GetVGA()->Ctrl()->OffsetToVFPt(offset);
			Pt->y = ClkToPt(vfpt.value.nClock);
			Pt->x = VolToPt(vfpt.value.nVoltage);
			CPoint curvePts[100];
			int nCount = 100;
			m_GpuClkCurve.GetValue(0, curvePts, nCount);
			VGA_PERFORMANCE perf;
			for(int i = 0; i < nCount; i++)
			{
				GVDISP_CLOCK_VFPT vfpt;
				vfpt.value.nVoltage = PtToVol(curvePts[i].x);
				vfpt.value.nClock = PtToClk(curvePts[i].y);
				perf.GpuVf.offset[i] = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
			}
			perf.GpuVf.nNumVFPoints = nCount;
			perf.nGpuClk = 0;
		}
		break;
	case 1:
		{
			
		}
		break;
	case 2:
		{
			m_fanCurve.GetValue(0, NoFanStopcurvePts, NoFanStopCurveNum);
		}break;
	}
	return 1;
}

LRESULT CCustomizedDlg::OnUiCurveRemove(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0: 
		{
		}break;
	case 1:
		{

		}break;
	}
	return 1;
}

void CCustomizedDlg::GetGpuVFCurve(VGA_PERFORMANCE &perf)
{
	CPoint curvePts[100];
	int nCount = 100;
	m_GpuClkCurve.GetValue(0, curvePts, nCount);
	for(int i = 0; i < nCount; i++)
	{
		GVDISP_CLOCK_VFPT vfpt;
		vfpt.value.nVoltage = PtToVol(curvePts[i].x);
		vfpt.value.nClock = PtToClk(curvePts[i].y);
		perf.GpuVf.offset[i] = Aorus()->GetVGA()->Ctrl()->VFPtToOffset(vfpt);
	}
	perf.GpuVf.nNumVFPoints = nCount;
}

void CCustomizedDlg::GetFanVFCurve(FAN_SETTING &fansetting)
{
	/*CPoint curvePts[10];
	int nCount = 10;*/
	m_fanCurve.GetValue(0, NoFanStopcurvePts, NoFanStopCurveNum);
	fansetting.nCurveStep=NoFanStopCurveNum;
	for(int i = 0; i < NoFanStopCurveNum; i++)
	{
		fansetting.curve[i].nTemperature=NoFanStopcurvePts[i].x;
		fansetting.curve[i].nFanSpeed=NoFanStopcurvePts[i].y;
	}
}

DWORD CCustomizedDlg::OCScannerThread(LPVOID lpParameter)
{
	CCustomizedDlg* pMain = (CCustomizedDlg*) lpParameter;
	//AfxGetMainWnd()->SetWindowPos(&AfxGetMainWnd()->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |SWP_NOACTIVATE);

	CString sTemp = _T(""), sPath = _T(""), sParam = _T("");
	int nVolFrom = 0, nVolTo = 0;
	// 讀取控件設定值
	int nCount		= pMain->m_ScanClks.nNumVFPoints;
	int nTime		= 10;
	int nStep		= 30;
	int nClkBegin	= 0;
	int nClkEnd		= 200;
	int nClkBack	= nStep;//pMain->GetDlgItemInt(IDC_EDIT_BACK) * 2;

	nVolFrom = (int)(0.8 * 1000000);
	nVolTo = (int)(1.0 * 1000000);

	sPath = Gv::OS::GetCurDirectory() + _T("scanner\\AORUS_GRAPHICS_ENGINE_x32.exe");
	if(!Aorus()->GetVGA()->Ctrl()->IsAorus()) sPath = Gv::OS::GetCurDirectory() + _T("scanner\\AORUS_GRAPHICS_ENGINE_x32_GIGABYTE.exe");
	sParam = _T("-nogui -width=1024 -height=768 -furmark -scan");

	for (int i = 0; i < nCount && pMain->m_bScanning; i++)
	{
		int n = pMain->m_Clks.nNumVFPoints - 1 - i;
		int nOffset = 0, nVoltage = 0, nClock = 0, nIndex = 0;
		nIndex	 = pMain->m_Clks.vfs[n].nIndex;
		nClock	 = pMain->m_DefaultClks.vfs[n].value.nClock;
		nVoltage = pMain->m_Clks.vfs[n].value.nVoltage;
		nOffset	 = pMain->m_Offsets.offset[n].nOffset;
		// 讀取列表控件載入的VF Point

		if (nVoltage < nVolFrom || nVoltage > nVolTo) continue;

		if (nOffset < nClkBegin) nOffset = nClkBegin;
		GvSetLockVoltage(0, nVoltage); // 鎖定?壓

		int j = 0;
		for (j = nOffset; j <= nClkEnd && pMain->m_bScanning; j += nStep)
		{
			// 初始化Furmark Scanner
			if (!pMain->m_Reader.IsRunning())
			{
				//Launcher Furmark...
				pMain->m_Reader.Launcher(sPath, sParam);
				Sleep(2000); // 等待?動
				//Init Furmark...;
				if(!pMain->m_Reader.ReadSignature())
				{
					//Read Furmark Failed
					goto DONE;
				}
				//pMain->SetForegroundWindow();
			}
			GvSetVfClock(0, GVDISP_CLOCK_DOMAIN_ID_GPU, nIndex, j); // 超頻
			pMain->ResetFurmark();
			for(int t = 0; t < nTime - 2 && pMain->m_bScanning && pMain->isPass(); t++) 
				Sleep(1000);
			if (!pMain->isPass())		// 檢查是否超頻錯誤
			{
				j -= nClkBack;
				if(j < 0) j = 0;
				GvGetVfClockSet(0, nIndex, j);	// 設置回上一階
				pMain->OnScanerFinish(n, nVoltage, j);
				break;
			}
			if(pMain->m_bScanning) pMain->OnScanerFinish(n, nVoltage, j);
		}
		if (j >= nClkEnd)
		{
			pMain->OnScanerFinish(n, nVoltage, j);
		}
	}

DONE:
	GvSetLockVoltage(0, 0); // 解除?壓鎖定
	pMain->m_Reader.Destroy();
	pMain->OnScanerApply();
	CloseHandle(pMain->m_hThread);
	pMain->m_hThread = NULL;
	return 0;
}

void CCustomizedDlg::OnScanerFinish(int nIndex, int nVol, int nClk)
{
	m_Reader.Destroy();
	Sleep(2000);
	m_curvePt[nIndex] = CPoint(m_Clks.vfs[nIndex].value.nVoltage, (m_Clks.vfs[nIndex].value.nClock+nClk) / 2);
	m_GpuClkScan.SetValue(1, &m_curvePt[m_nVolIndex], m_DefaultClks.nNumVFPoints - m_nVolIndex - 1);
}

void CCustomizedDlg::OnScanerApply()
{
	GVDISP_CLOCK_VFPTS vfpts;
	Aorus()->GetVGA()->Ctrl()->GetCurClockCurve(&vfpts);
	CPoint curvePts[100];
	int nCount = 100;
	for(int i = 0; i < vfpts.nNumVFPoints; i++)
	{
		curvePts[i].x = VolToPt(vfpts.vfs[i].value.nVoltage);
		curvePts[i].y = ClkToPt(vfpts.vfs[i].value.nClock/2);
	}
	CPoint curveScanPt[100];
	int nScanCount = 100;
	m_GpuClkScan.GetValue(1 , curveScanPt ,nScanCount);
	for (int i=0; i<nScanCount ; i++)
	{
		if ((curvePts+m_nVolIndex+i)->y<curveScanPt[i].y)
		{
			(curvePts+m_nVolIndex+i)->y=curveScanPt[i].y;
		}
	}
	m_GpuClkCurve.SetValue(0, curvePts+m_nVolIndex, vfpts.nNumVFPoints-m_nVolIndex);
	UpdateUI(0);
}

void CCustomizedDlg::ResetFurmark()
{
	if (m_Reader.IsRunning())
	{
		DWORD cur = 0, tot = 0;
		m_Reader.GetNumArtifacts(&cur, &tot);
		m_nFurmarkLastCount = tot;
	}
}

bool CCustomizedDlg::isPass()
{
	if (m_Reader.IsRunning())
	{
		DWORD cur = 0, tot = 0;
		m_Reader.GetNumArtifacts(&cur, &tot);
		return m_nFurmarkLastCount == tot;
	}
	return false;
}
LRESULT CCustomizedDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_VGACUS_CLOSE:
		{
			ShowWindow(SW_HIDE);
			if (m_bScanning)
			{
				m_btn[BTN_VGACUS_ACTIVEOC].SetCapture(CLangX::Get(LANG_VGACUST_ACTOCSCANER));
				m_bScanning = false;
				WaitForSingleObject(m_hThread, 1000);
				if(NULL != m_hThread)
				{
					CloseHandle(m_hThread);
					m_hThread = NULL;
					//OnScanerApply();
				}
			}
		}
		break;
	case BTN_VGACUS_ACTIVEOC:
		{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			if (m_bScanning)
			{
				m_btn[BTN_VGACUS_ACTIVEOC].SetCapture(CLangX::Get(LANG_VGACUST_ACTOCSCANER));
				m_bScanning = false;
				WaitForSingleObject(m_hThread, 1000);
				if(NULL != m_hThread)
				{
					CloseHandle(m_hThread);
					m_hThread = NULL;
					OnScanerApply();
				}
				/*if(NULL != m_hThread)
				{
					if(WAIT_OBJECT_0 == WaitForSingleObject(m_hThread, INFINITE))
					{
						CloseHandle(m_hThread);
						m_hThread = NULL;
						OnScanerApply();
					}
				}*/
			}
			else
			{
				m_btn[BTN_VGACUS_ACTIVEOC].SetCapture(CLangX::Get(LANG_VGACUST_STOPOCSCANER));
				m_bScanning = true;
				if (m_hThread == NULL)
				{
					UpdateUI(2);
					m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(OCScannerThread), (LPVOID)this, 0, NULL);
				}

			}
		}
		break;
	}
	return 1;
}
LRESULT CCustomizedDlg::OnFanStopStateChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam==0)
	{
		CPoint curvePts[10];
		int nCount = 10;
		m_fanCurve.GetValue(0, curvePts, nCount);
		for(int i = 0; i < nCount; i++)
		{
			if(curvePts[i].y<20) curvePts[i].y=20;
		}
		m_fanCurve.SetValue(0, curvePts, nCount);
		m_fanCurve.SetAdjustYRange(20, 100);
	}
	else
	{
		m_fanCurve.SetAdjustYRange(0, 100);
		if (NoFanStopCurveNum>0)
		{
			m_fanCurve.SetValue(0, NoFanStopcurvePts, NoFanStopCurveNum);
		}
	}
    return 1;
}
int CCustomizedDlg::GetType()
{
	return m_nType;	
}

void CCustomizedDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CUiDlg::OnActivate(nState, pWndOther, bMinimized);

	((CAORUSDlg*)AfxGetMainWnd())->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CCustomizedDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CUiDlg::OnMoving(fwSide, pRect);

	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	CRect rcCli;
	pParent->GetClientRect(rcCli);
	int nWidth = rcCli.Width();
	GetClientRect(rcCli);
	ClientToScreen(&rcCli);

	pParent->OnFollowMove(0, pParent->OnFit(rcCli, 0 - nWidth, -79));

}

void CCustomizedDlg::OnFit(CRect rc)
{
	CAORUSDlg* pParent = (CAORUSDlg*)AfxGetMainWnd();
	if(NULL != pParent)
	{
		int nX = rc.left + rc.Width();
		int nY = rc.top + 78;
		SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE);
	}
	SetWindowPos(&wndTop, 0, 0 , 0, 0, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
}
void CCustomizedDlg::OnReset()
{
	//reset GPU曲线图
	VGA_PERFORMANCE perf;
	Aorus()->GetCfg()->GetPerformances(VGA_PERF_GCLKCUV,perf, Aorus()->GetVGAProfileSel(), Aorus()->GetVGASel());
	CPoint curveClkPts[100];
	if( perf.GpuVf.nNumVFPoints>0)
	{
		for(int i = 0; i < perf.GpuVf.nNumVFPoints; i++)
		{
			curveClkPts[i] = CPoint(
				VolToPt(Aorus()->GetVGA()->Ctrl()->OffsetIndexToVol(perf.GpuVf.offset[i].nIndex)), 
				ClkToPt(Aorus()->GetVGA()->Ctrl()->OffsetToVFPtClk(perf.GpuVf.offset[i]))
				); 
		}
		m_GpuClkCurve.SetValue(0, curveClkPts, perf.GpuVf.nNumVFPoints);
	}
	else
	{
		if (m_defaultVFGpuCus.nNumVFPoints>0)
		{
			for(int i = 0; i < m_defaultVFGpuCus.nNumVFPoints; i++)
			{
				curveClkPts[i] = CPoint(
					VolToPt(Aorus()->GetVGA()->Ctrl()->OffsetIndexToVol(m_defaultVFGpuCus.offset[i].nIndex)), 
					ClkToPt(Aorus()->GetVGA()->Ctrl()->OffsetToVFPtClk(m_defaultVFGpuCus.offset[i]))
					); 
			}
			m_GpuClkCurve.SetValue(0, curveClkPts, m_VFGpuclkCus.nNumVFPoints);
		}
	}
	//reset FAN曲线图
	FAN_SETTING fansetting;
	Aorus()->GetCfg()->GetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());


	CPoint FancurvePts[10];
	if (fansetting.nCurveStep>0)
	{
		NoFanStopCurveNum=fansetting.nCurveStep;
		for(int i=0; i<fansetting.nCurveStep; i++)
		{
			FancurvePts[i].x = fansetting.curve[i].nTemperature;
			FancurvePts[i].y = fansetting.curve[i].nFanSpeed;
			NoFanStopcurvePts[i].x=FancurvePts[i].x;
			NoFanStopcurvePts[i].y=FancurvePts[i].y;
		}
		if(!Aorus()->GetFanStopState())
		{
			for(int i=0; i<fansetting.nCurveStep; i++)
			{
				if (FancurvePts[i].y<20)
				{
					FancurvePts[i].y=20;
				}
			}
		}
		m_fanCurve.SetValue(0, FancurvePts, fansetting.nCurveStep);
	}
	else
	{
		FAN_SETTING FanDefaultSetting;
		Aorus()->GetVGA()->Ctrl()->GetFanAutoSetting(FanDefaultSetting);
		NoFanStopCurveNum=FanDefaultSetting.nCurveStep;
		CPoint FancurvePts[10];
		for(int i=0; i<FanDefaultSetting.nCurveStep; i++)
		{
			FancurvePts[i].x = FanDefaultSetting.curve[i].nTemperature;
			FancurvePts[i].y = FanDefaultSetting.curve[i].nFanSpeed;
			NoFanStopcurvePts[i].x=FancurvePts[i].x;
			NoFanStopcurvePts[i].y=FancurvePts[i].y;
		}
		if(!Aorus()->GetFanStopState())
		{
			for(int i=0; i<FanDefaultSetting.nCurveStep; i++)
			{
				if (FancurvePts[i].y<20)
				{
					FancurvePts[i].y=20;
				}
			}
		}
		m_fanCurve.SetValue(0, FancurvePts, FanDefaultSetting.nCurveStep);
	}

}
void CCustomizedDlg::OnDefault()
{
	////初始化GPU默认图
	CPoint curveClkPts[100];
	for(int i = 0; i < m_defaultVFGpuCus.nNumVFPoints; i++)
	{
		curveClkPts[i] = CPoint(
			VolToPt(Aorus()->GetVGA()->Ctrl()->OffsetIndexToVol(m_defaultVFGpuCus.offset[i].nIndex)), 
			ClkToPt(Aorus()->GetVGA()->Ctrl()->OffsetToVFPtClk(m_defaultVFGpuCus.offset[i]))
			); 
	}
	m_GpuClkCurve.SetValue(0, curveClkPts, m_VFGpuclkCus.nNumVFPoints);


	////初始化风扇默认图
	FAN_SETTING FanDefaultSetting;
	Aorus()->GetVGA()->Ctrl()->GetFanAutoSetting(FanDefaultSetting);
	CPoint FancurvePts[10];
	NoFanStopCurveNum=FanDefaultSetting.nCurveStep;
	for(int i=0; i<FanDefaultSetting.nCurveStep; i++)
	{
		FancurvePts[i].x = FanDefaultSetting.curve[i].nTemperature;
		FancurvePts[i].y = FanDefaultSetting.curve[i].nFanSpeed;
		NoFanStopcurvePts[i].x=FancurvePts[i].x;
		NoFanStopcurvePts[i].y=FancurvePts[i].y;
	}
	if(!Aorus()->GetFanStopState())
	{
		for(int i=0; i<FanDefaultSetting.nCurveStep; i++)
		{
			if (FancurvePts[i].y<20)
			{
				FancurvePts[i].y=20;
			}
		}
	}
	m_fanCurve.SetValue(0, FancurvePts, FanDefaultSetting.nCurveStep);
//	InitState();
}