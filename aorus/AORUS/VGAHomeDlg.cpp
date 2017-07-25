// VGAHomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AORUS.h"
#include "VGAHomeDlg.h"
#include "AORUSDlg.h"


// CVGAHomeDlg dialog

IMPLEMENT_DYNAMIC(CVGAHomeDlg, CUiDlg)

CVGAHomeDlg::CVGAHomeDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CVGAHomeDlg::IDD, pParent)
{

}

CVGAHomeDlg::~CVGAHomeDlg()
{
}

void CVGAHomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVGAHomeDlg, CUiDlg)
	ON_WM_TIMER()
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_COMBOBOX_SELCHANGED, OnUiComboBoxSelChanged)
END_MESSAGE_MAP()

BOOL CVGAHomeDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	VGA_PARAM_BASESETTING baseSetting;
	if(VGA_CARD_UNKNOWN!=Aorus()->GetVGA()->Ctrl()->GetCardInfo()->nCardType)
	{
		m_bVgaCard=TRUE;
	}
	Ui();
	return true;
}
// CVGAHomeDlg message handlers

void CVGAHomeDlg::Ui()
{
	UiMain();
}

void CVGAHomeDlg::UiMain()
{
	SetBkBitmap(IDB_VGAHOME_BG1, 0xff, CLR_TRPT);
	UI_BTN btn[] = 
	{
		UI_BTN(this, BTN_VGAH_OCMODE,		CRect(15, 12, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_OCMODE_BGL1, IDB_OCMODE_BGL1, IDB_OCMODE_BGL1, 0, CLR_TRPT),NULL, BTN_RADIO),
		UI_BTN(this, BTN_VGAH_GAMINGMODE,	CRect(165, 12, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_GAMINGMODE_BGL1, IDB_GAMINGMODE_BGL1, IDB_GAMINGMODE_BGL1, 0, CLR_TRPT),NULL, BTN_RADIO),
		UI_BTN(this, BTN_VGAH_SILENTMODE,	CRect(313, 12, 0, 0), &UIBTN_IMAGE(0, 0, 0, 0, IDB_SILENTMODE_BGL1, IDB_SILENTMODE_BGL1, IDB_SILENTMODE_BGL1, 0, CLR_TRPT),NULL, BTN_RADIO),
		UI_BTN(this, BTN_VGAH_USERMODE,		CRect(463, 12, 0, 0), &UIBTN_IMAGE(0, IDB_USERMODE_BG, 0, 0, IDB_USERMODE_BG, IDB_USERMODE_BG, IDB_USERMODE_BG, 0, CLR_TRPT),NULL, BTN_RADIO),
		
	};
	for (int i=BTN_VGAH_OCMODE; i <= BTN_VGAH_USERMODE; i++)
	{
		m_btn[i].CreateButton(btn[i]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}
	UIBTN_IMAGE Img[13]=
	{
		UIBTN_IMAGE(0, IDB_OCMODE_BGL1, 0, 0, IDB_OCMODE_BGL1, IDB_OCMODE_BGL1, IDB_OCMODE_BGL1, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL2, 0, 0, IDB_OCMODE_BGL2, IDB_OCMODE_BGL2, IDB_OCMODE_BGL2, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL3, 0, 0, IDB_OCMODE_BGL3, IDB_OCMODE_BGL3, IDB_OCMODE_BGL3, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL4, 0, 0, IDB_OCMODE_BGL4, IDB_OCMODE_BGL4, IDB_OCMODE_BGL4, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL5, 0, 0, IDB_OCMODE_BGL5, IDB_OCMODE_BGL5, IDB_OCMODE_BGL5, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL6, 0, 0, IDB_OCMODE_BGL6, IDB_OCMODE_BGL6, IDB_OCMODE_BGL6, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL7, 0, 0, IDB_OCMODE_BGL7, IDB_OCMODE_BGL7, IDB_OCMODE_BGL7, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL8, 0, 0, IDB_OCMODE_BGL8, IDB_OCMODE_BGL8, IDB_OCMODE_BGL8, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL9, 0, 0, IDB_OCMODE_BGL9, IDB_OCMODE_BGL9, IDB_OCMODE_BGL9, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL10, 0, 0, IDB_OCMODE_BGL10, IDB_OCMODE_BGL10, IDB_OCMODE_BGL10, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL11, 0, 0, IDB_OCMODE_BGL11, IDB_OCMODE_BGL11, IDB_OCMODE_BGL11, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL12, 0, 0, IDB_OCMODE_BGL12, IDB_OCMODE_BGL12, IDB_OCMODE_BGL12, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_OCMODE_BGL13, 0, 0, IDB_OCMODE_BGL13, IDB_OCMODE_BGL13, IDB_OCMODE_BGL13, 0, CLR_TRPT)

	};
	m_btn[BTN_VGAH_OCMODE].SetPlayBtimap(Img,13);
	UIBTN_IMAGE ImgGame[9]=
	{
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL1, 0, 0, IDB_GAMINGMODE_BGL1, IDB_GAMINGMODE_BGL1, IDB_GAMINGMODE_BGL1, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL2, 0, 0, IDB_GAMINGMODE_BGL2, IDB_GAMINGMODE_BGL2, IDB_GAMINGMODE_BGL2, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL3, 0, 0, IDB_GAMINGMODE_BGL3, IDB_GAMINGMODE_BGL3, IDB_GAMINGMODE_BGL3, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL4, 0, 0, IDB_GAMINGMODE_BGL4, IDB_GAMINGMODE_BGL4, IDB_GAMINGMODE_BGL4, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL5, 0, 0, IDB_GAMINGMODE_BGL5, IDB_GAMINGMODE_BGL5, IDB_GAMINGMODE_BGL5, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL6, 0, 0, IDB_GAMINGMODE_BGL6, IDB_GAMINGMODE_BGL6, IDB_GAMINGMODE_BGL6, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL7, 0, 0, IDB_GAMINGMODE_BGL7, IDB_GAMINGMODE_BGL7, IDB_GAMINGMODE_BGL7, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL8, 0, 0, IDB_GAMINGMODE_BGL8, IDB_GAMINGMODE_BGL8, IDB_GAMINGMODE_BGL8, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_GAMINGMODE_BGL9, 0, 0, IDB_GAMINGMODE_BGL9, IDB_GAMINGMODE_BGL9, IDB_GAMINGMODE_BGL9, 0, CLR_TRPT)
	};
    m_btn[BTN_VGAH_GAMINGMODE].SetPlayBtimap(ImgGame,9);

	UIBTN_IMAGE ImgSilent[3]=
	{
		UIBTN_IMAGE(0, IDB_SILENTMODE_BGL1, 0, 0, IDB_SILENTMODE_BGL1, IDB_SILENTMODE_BGL1, IDB_SILENTMODE_BGL1, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_SILENTMODE_BGL2, 0, 0, IDB_SILENTMODE_BGL2, IDB_SILENTMODE_BGL2, IDB_SILENTMODE_BGL2, 0, CLR_TRPT),
		UIBTN_IMAGE(0, IDB_SILENTMODE_BGL3, 0, 0, IDB_SILENTMODE_BGL3, IDB_SILENTMODE_BGL3, IDB_SILENTMODE_BGL3, 0, CLR_TRPT)


	};
	m_btn[BTN_VGAH_SILENTMODE].SetPlayBtimap(ImgSilent,3);

	m_combobox[COMB_VGAH_PROFILESEL].Create(CRect(42, 103, 102, 119), &m_btn[BTN_VGAH_USERMODE], COMB_VGAH_PROFILESEL);
	m_combobox[COMB_VGAH_PROFILESEL].SetComboBoxBitmap(IDB_PROFILESEL_BG, IDB_PROFILESEL_BG, IDB_PROFILESEL_BG, IDB_PROFILESEL_BG, CLR_TRPT);
	m_combobox[COMB_VGAH_PROFILESEL].SetFont(Font(8), CLR_GRAY); // 字体
	m_combobox[COMB_VGAH_PROFILESEL].SetCursor(IDC_CUR_HAND); // 鼠标手型
	m_combobox[COMB_VGAH_PROFILESEL].SetArrowWidth(20);
	m_combobox[COMB_VGAH_PROFILESEL].GetDropList()->SetFont(Font(8));
	m_combobox[COMB_VGAH_PROFILESEL].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMB_VGAH_PROFILESEL].GetDropList()->SetHighlightBkColor(CLR_GRAY);
	m_combobox[COMB_VGAH_PROFILESEL].ModifyCtrlStyle(ST_RIGHT,ST_CENTER);// 去掉右对齐，加入居中
	//m_btn[BTN_VGAH_OCMODE].Play();
	//SetTimer(0, 2000, NULL);

	// Peter Lee 2017/6/5 bug fix, 1030SL no sink, gaming & silent mode no different, disable silent button
	if (Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N1030SL-2GL") || 
		Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N1050D5-2GD") ||
		Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N105TD5-4GD") ||
		Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N108TTURBO-11GD") ||
		Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N1050-2GL") ||
		Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName == _T("GV-N105TWF2-4GD"))
		m_btn[BTN_VGAH_SILENTMODE].Enable(FALSE);
}

void CVGAHomeDlg::OnTimer(UINT_PTR nIDEvent)
{

}

LRESULT CVGAHomeDlg::OnUiComboBoxSelChanged(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case COMB_VGAH_PROFILESEL:
		Aorus()->SetVGAProfileSel(m_combobox[COMB_VGAH_PROFILESEL].GetCurSel());
		Aorus()->GetCfg()->SetProfileSel(Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());
		if (m_btn[BTN_VGAH_USERMODE].IsCheck())
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			VGA_PERFORMANCE perf;
			FAN_SETTING fansetting;
			Aorus()->GetCfg()->GetPerformances(VGA_PERF_ALL,perf,Aorus()->GetVGAProfileSel(),Aorus()->GetVGASel());
			Aorus()->GetCfg()->GetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());
			Aorus()->GetCfg()->SetCurFanSetting(fansetting,Aorus()->GetVGASel());
			Aorus()->GetVGA()->Ctrl()->SetFanSetting(Aorus()->GetVGASel(),fansetting);
			Aorus()->GetVGA()->Ctrl()->SetPerformances(VGA_PERF_ALL,Aorus()->GetVGASel(),perf);
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	}
	return 1;
}

LRESULT CVGAHomeDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case BTN_VGAH_OCMODE:
	case BTN_VGAH_GAMINGMODE:
	case BTN_VGAH_SILENTMODE:
	case BTN_VGAH_USERMODE:
		{
			m_btn[BTN_VGAH_OCMODE].SetCheck(wParam==BTN_VGAH_OCMODE? true:false);
			m_btn[BTN_VGAH_GAMINGMODE].SetCheck(wParam==BTN_VGAH_GAMINGMODE? true:false);
			m_btn[BTN_VGAH_SILENTMODE].SetCheck(wParam==BTN_VGAH_SILENTMODE? true:false);
			m_btn[BTN_VGAH_USERMODE].SetCheck(wParam==BTN_VGAH_USERMODE? true:false);
			m_btn[BTN_VGAH_OCMODE].Stop();
			m_btn[BTN_VGAH_GAMINGMODE].Stop();
			m_btn[BTN_VGAH_SILENTMODE].Stop();
			m_btn[BTN_VGAH_USERMODE].Stop();

			if(wParam!=BTN_VGAH_USERMODE)
			{
				m_btn[wParam].Play();
				ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
				VGA_PERFORMANCE perf;
				/*perf=m_perfDefault;
				int GPUClk[]={Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_OC),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_GAME),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_ECO)};
				perf.nGpuClk=GPUClk[wParam-BTN_VGAH_OCMODE];
				int MEMClk[]={Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_OC),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_GAME),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_ECO)};
				if (MEMClk[BTN_VGAH_OCMODE] > 0)	// Peter Lee 2017/3/31
					perf.nMemClk=MEMClk[wParam-BTN_VGAH_OCMODE];
				Aorus()->GetVGA()->Ctrl()->SetPerformances(VGA_PERF_ALL,Aorus()->GetVGASel(),perf);*/

				int GPUClk[]={Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_OC),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_GAME),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_ECO)};
				int MEMClk[]={Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_OC),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_GAME),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_ECO)};
				int OCPower[]={Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_POWER,VGA_MODE_OC),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_POWER,VGA_MODE_GAME),Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_POWER,VGA_MODE_ECO)};
				perf=m_perfDefault;
				DWORD dwPerf = 0;
				if (GPUClk[0] > 0)
				{
					perf.nGpuClk=GPUClk[wParam-BTN_VGAH_OCMODE];
					dwPerf |= VGA_PERF_GPUCLK;
				}
				if (MEMClk[0] > 0)
				{
					perf.nMemClk=MEMClk[wParam-BTN_VGAH_OCMODE];
					dwPerf |= VGA_PERF_MEMCLK;
				}
				if (OCPower[0] > 0)
				{
					perf.nPower=OCPower[wParam-BTN_VGAH_OCMODE];
					if (perf.nPower <= 0)
						perf.nPower = 100;
					dwPerf |= VGA_PERF_POWER;
				}
				Aorus()->GetVGA()->Ctrl()->SetPerformances(dwPerf,Aorus()->GetVGASel(),perf);
				if (wParam==BTN_VGAH_OCMODE||wParam==BTN_VGAH_GAMINGMODE)
				{
					FAN_SETTING fansetting;
					fansetting.nFanMode=VGA_FANMODE_AUTO;	
					fansetting.bFanStop=Aorus()->GetFanStopState();
					Aorus()->GetVGA()->Ctrl()->SetFanSetting(Aorus()->GetVGASel(), fansetting);
					Aorus()->GetCfg()->SetCurFanSetting(fansetting, Aorus()->GetVGASel());
					// Peter Lee 2017/6/16 special case for 1070IXEB
					if (wParam==BTN_VGAH_OCMODE && Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName.Find(_T("1070IXEB")) >= 0)
					{
						fansetting.nFanMode=VGA_FANMODE_DEFINE;
						fansetting.nCurveStep = 4;
						fansetting.curve[0].nTemperature = 0;
						fansetting.curve[0].nFanSpeed = 0;
						fansetting.curve[1].nTemperature = 55;
						fansetting.curve[1].nFanSpeed = 0;
						fansetting.curve[2].nTemperature = 55;
						fansetting.curve[2].nFanSpeed = 40;
						fansetting.curve[3].nTemperature = 80;
						fansetting.curve[3].nFanSpeed = 96;
						fansetting.bFanStop=Aorus()->GetFanStopState();
						Aorus()->GetVGA()->Ctrl()->SetFanSetting(Aorus()->GetVGASel(),fansetting);
						Aorus()->GetCfg()->SetCurFanSetting(fansetting,Aorus()->GetVGASel());
					}
				}	
				else if (wParam==BTN_VGAH_SILENTMODE)
				{
					FAN_SETTING fansetting;
					fansetting.nFanMode=VGA_FANMODE_DEFINE;		// Peter Lee 2017/6/16 movced up
					Aorus()->GetVGA()->Ctrl()->GetFanSilentSetting(fansetting);					
					fansetting.bFanStop=Aorus()->GetFanStopState();
					Aorus()->GetVGA()->Ctrl()->SetFanSetting(Aorus()->GetVGASel(),fansetting);
					Aorus()->GetCfg()->SetCurFanSetting(fansetting,Aorus()->GetVGASel());
					//Aorus()->GetCfg()->SetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());					
				}
			}
			else
			{
				ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
				VGA_PERFORMANCE perf;
				FAN_SETTING fansetting;
				Aorus()->GetCfg()->GetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());
				Aorus()->GetCfg()->GetPerformances(VGA_PERF_ALL,perf,Aorus()->GetVGAProfileSel(),Aorus()->GetVGASel());
				Aorus()->GetCfg()->SetCurFanSetting(fansetting,Aorus()->GetVGASel());
				Aorus()->GetVGA()->Ctrl()->SetFanSetting(Aorus()->GetVGASel(),fansetting);
				Aorus()->GetVGA()->Ctrl()->SetPerformances(VGA_PERF_ALL,Aorus()->GetVGASel(),perf);
			}
			Aorus()->GetCfg()->SetVgaMode(wParam - BTN_VGAH_OCMODE + 1, Aorus()->GetVGASel());
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	}
	return 1;
}
void CVGAHomeDlg::InitState()
{
	UpdateUI();
   
    int ProfileCount=Aorus()->GetCfg()->GetProfileCount(Aorus()->GetVGASel());
	int nMode = Aorus()->GetCfg()->GetVgaMode(Aorus()->GetVGASel());
	Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_ALL, m_perfDefault);
	if(!Aorus()->GetVGA()->Ctrl()->IsOneStepCard())
	{
		if (nMode!=VGA_MODE_USER)
		{
			nMode=VGA_MODE_USER;
			Aorus()->GetCfg()->SetVgaMode(nMode,Aorus()->GetVGASel());
		}
		m_btn[BTN_VGAH_OCMODE].Enable(FALSE);
		m_btn[BTN_VGAH_GAMINGMODE].Enable(FALSE);
		m_btn[BTN_VGAH_SILENTMODE].Enable(FALSE);
	}
	switch (nMode)
	{
	case VGA_MODE_OC:
		{
			OnUiButtonClicked(BTN_VGAH_OCMODE,0);
			break;
		}
	case VGA_MODE_GAME:
		{
			OnUiButtonClicked(BTN_VGAH_GAMINGMODE,0);
			break;
		}
	case VGA_MODE_ECO:
		{
			OnUiButtonClicked(BTN_VGAH_SILENTMODE,0);
			break;
		}
	case VGA_MODE_USER:
		{
			if (ProfileCount>0)
			{
				OnUiButtonClicked(BTN_VGAH_USERMODE,0);

			}
			else
			{
				OnUiButtonClicked(BTN_VGAH_OCMODE,0);
			}
			break;
		}  
	}
}
void CVGAHomeDlg::UpdateUI()
{
	int ProfileCount=Aorus()->GetCfg()->GetProfileCount(Aorus()->GetVGASel());
	m_combobox[COMB_VGAH_PROFILESEL].ResetContent();
	if(ProfileCount>0)
	{
		m_btn[BTN_VGAH_USERMODE].EnableWindow(true);
		for (int i=0;i<ProfileCount;i++)
		{//init profile COMBOX
			CString csName;
			Aorus()->GetCfg()->GetProfileName(i,Aorus()->GetVGASel(),csName);
			m_combobox[COMB_VGAH_PROFILESEL].AddString(csName,0,CLR_WHITE);
		}
		m_combobox[COMB_VGAH_PROFILESEL].SetCurSel(Aorus()->GetVGAProfileSel());
	}
	else
	{
		m_btn[BTN_VGAH_USERMODE].EnableWindow(false);
	}

	int nMode = Aorus()->GetCfg()->GetVgaMode(Aorus()->GetVGASel());
	switch (nMode)
	{
	case VGA_MODE_OC:
		{
			m_btn[BTN_VGAH_OCMODE].SetCheck(true);
			m_btn[BTN_VGAH_GAMINGMODE].SetCheck(false);
			m_btn[BTN_VGAH_SILENTMODE].SetCheck(false);;
			m_btn[BTN_VGAH_USERMODE].SetCheck(false);
			break;
		}
	case VGA_MODE_GAME:
		{

			m_btn[BTN_VGAH_OCMODE].SetCheck(false);
			m_btn[BTN_VGAH_GAMINGMODE].SetCheck(true);
			m_btn[BTN_VGAH_SILENTMODE].SetCheck(false);
			m_btn[BTN_VGAH_USERMODE].SetCheck(false);
			break;
		}
	case VGA_MODE_ECO:
		{
			m_btn[BTN_VGAH_OCMODE].SetCheck(false);
			m_btn[BTN_VGAH_GAMINGMODE].SetCheck(false);
			m_btn[BTN_VGAH_SILENTMODE].SetCheck(true);
			m_btn[BTN_VGAH_USERMODE].SetCheck(false);
			break;
		}
	case VGA_MODE_USER:
		{
			m_btn[BTN_VGAH_OCMODE].SetCheck(false);
			m_btn[BTN_VGAH_GAMINGMODE].SetCheck(false);
			m_btn[BTN_VGAH_SILENTMODE].SetCheck(false);
			m_btn[BTN_VGAH_USERMODE].SetCheck(true);
			m_combobox[COMB_VGAH_PROFILESEL].SetCurSel(Aorus()->GetVGAProfileSel());
			break;
		}  
	}
}