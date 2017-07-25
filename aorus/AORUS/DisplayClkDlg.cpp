// DisplayClkDlg.cpp : implementation file

#include "stdafx.h"
#include "AORUS.h"
#include "DisplayClkDlg.h"
#include "AORUSDlg.h"

// CDisplayClkDlg dialog

IMPLEMENT_DYNAMIC(CDisplayClkDlg, CUiDlg)

CDisplayClkDlg::CDisplayClkDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CDisplayClkDlg::IDD, pParent)
{

}

CDisplayClkDlg::~CDisplayClkDlg()
{
}

void CDisplayClkDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BOOL CDisplayClkDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	return true;
}

BEGIN_MESSAGE_MAP(CDisplayClkDlg, CUiDlg)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDisplayClkDlg message handlers

void CDisplayClkDlg::Ui()
{
	UiMain();
}

void CDisplayClkDlg::UiMain()
{
	SetBkBitmap(IDB_VGAHOME_BG2, 0xff, CLR_TRPT); // …Ë÷√±≥æ∞Õº;
	
	UI_STATIC stc[] = 
	{
		UI_STATIC(this,  STC_CLKVIEW_GPUCLKTITLE,	   CRect( 25,  26, 194,  46),	CLangX::Get(LANG_VGAOC_GPUCLK),	  0),
		UI_STATIC(this,  STC_CLKVIEW_MEMCLKTITLE,      CRect(25, 72, 194, 92),	CLangX::Get(LANG_VGAOC_MEMCLK), 0),
		UI_STATIC(this,  STC_CLKVIEW_GPUCLKUINIT,      CRect(293,  32, 337,  50),	L"MHz",    0),
	    UI_STATIC(this,  STC_CLKVIEW_MEMCLKUINIT,	   CRect(293, 79, 337, 97),	L"MHz",    0),
		UI_STATIC(this,  STC_CLKVIEW_GPUCLKVALUE,      CRect( 184, 17, 291, 52),	L"1936",   0),
		UI_STATIC(this,  STC_CLKVIEW_MEMCLKVALUE,      CRect(184, 64, 291,  99),	L"10400",   0),
		
	};
	for(int i=STC_CLKVIEW_GPUCLKTITLE; i<=STC_CLKVIEW_MEMCLKTITLE; i++)
	{
		m_stc[i].CreateStatic(stc[i]);
		m_stc[i].SetFont(Font(14), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT | ST_SINGLELINE);
	}
	for(int i=STC_CLKVIEW_GPUCLKUINIT; i<=STC_CLKVIEW_MEMCLKUINIT; i++)
	{
		m_stc[i].CreateStatic(stc[i]);
		m_stc[i].SetFont(Font(14), CLR_MAIN);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_LEFT| ST_SINGLELINE);
	}
	for(int i=STC_CLKVIEW_GPUCLKVALUE; i<=STC_CLKVIEW_MEMCLKVALUE; i++)
	{
		m_stc[i].CreateStatic(stc[i]);
		m_stc[i].SetFont(Font(28), CLR_WHITE);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_RIGHT | ST_SINGLELINE);
	}
}
void CDisplayClkDlg::InitState()
{
	if(!Aorus()->GetVGA()->Ctrl()->IsNvCard())
		m_stc[STC_CLKVIEW_GPUCLKTITLE].SetCaption(CLangX::Get(LANG_VGAOC_AMDCLK));
    UpdateUI();
	SetTimer(0,1000,NULL);
}
void CDisplayClkDlg::UpdateUI()
{
	VGA_SPECIALPERFS perfBase;
	Aorus()->GetVGA()->Ctrl()->GetSpecialPerformaces(perfBase);
    VGA_PERFORMANCE perf;
	Aorus()->GetVGA()->Ctrl()->GetPerformances(VGA_PERF_GPUCLK|VGA_PERF_MEMCLK,Aorus()->GetVGASel(),perf);
	CString strGpuClk,strMemClk;

	if (Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_OCBOOST) >= 0 
		&& 0 == perf.dwGpuClkCurve 
		&& perf.nGpuClk == Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_OC))
	{
		perf.nGpuClk =Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_OCBOOST);
	}
	else if (Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_ECOBOOST) >= 0 
		&& 0 == perf.dwGpuClkCurve 
		&& perf.nGpuClk == Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_ECO))
	{
		perf.nGpuClk = Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK, VGA_MODE_ECOBOOST) - perfBase.nGpuBoostClk;
	}
	// Peter Lee 2017/5/4 bug fix
	else if(Aorus()->GetVGA()->Ctrl()->IsBoost3())
		perf.nGpuClk = perf.nGpuClk>>1;

	// Peter Lee 2017/5/4 bug fix
	/*if(!Aorus()->GetVGA()->Ctrl()->IsBoost3())
		strGpuClk.Format(L"%d",perf.nGpuClk+perfBase.nGpuBoostClk);
	else
		strGpuClk.Format(L"%d",(perf.nGpuClk>>1)+perfBase.nGpuBoostClk);*/
	strGpuClk.Format(L"%d",perf.nGpuClk+perfBase.nGpuBoostClk);
    strMemClk.Format(L"%d",perf.nMemClk+perfBase.nMemBaseClk);
	m_stc[STC_CLKVIEW_GPUCLKVALUE].SetCaption(strGpuClk);
	m_stc[STC_CLKVIEW_MEMCLKVALUE].SetCaption(strMemClk);

}
void CDisplayClkDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 0:UpdateUI();break;
	}
}