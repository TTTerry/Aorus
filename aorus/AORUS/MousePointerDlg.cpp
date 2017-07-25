// MousePointerDlg.cpp : implementation file

#include "stdafx.h"
#include "AORUS.h"
#include "MousePointerDlg.h"
#include "AORUSDlg.h"
#include ".\inc\mouse\AM300Cmd.h"
#include ".\inc\mouse\AM300Ctrl.h"
#include ".\inc\mouse\CmdFormat.h"


// CMousePointerDlg dialog


extern GVORDER_PROFILE s_nCurProfile; // 當前profile

static int s_Report_Rate[] =
{
	0,
	8,// 1
	7, // 2
	6, // 3
	5, // 4
	4, // 5
	3, // 6
	2, // 7
	1, // 8
};

static CString s_sReport_Rate[] =
{
	_T(""), _T("1000"), _T("500"), _T("333"), _T("250"), _T("200"), _T("166"), _T("142"),_T("125"), 
};


IMPLEMENT_DYNAMIC(CMousePointerDlg, CUiDlg)

CMousePointerDlg::CMousePointerDlg(CWnd* pParent /*=NULL*/)
	: CUiDlg(CMousePointerDlg::IDD, pParent)
{
	m_ndpiIndex = 0;
	m_nReportRate = 8;
}

CMousePointerDlg::~CMousePointerDlg()
{
}

void CMousePointerDlg::DoDataExchange(CDataExchange* pDX)
{
	CUiDlg::DoDataExchange(pDX);
}

BOOL CMousePointerDlg::OnInitDialog()
{
	CUiDlg::OnInitDialog();
	Ui();
	return true;
}

BEGIN_MESSAGE_MAP(CMousePointerDlg, CUiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UI_BUTTON_CLICKED, OnUiButtonClicked)
	ON_MESSAGE(WM_UI_SLIDER_MOVING, OnUiSliderMoving)

END_MESSAGE_MAP()


// CMousePointerDlg message handlers

void CMousePointerDlg::OnPaint()
{
	CUiDlg::OnPaint();
}

void CMousePointerDlg::Ui()
{
	UiMain();
}

void CMousePointerDlg::UiMain()
{
	SetBkBitmap(IDB_LED_BGCOMMON, 0xff, CLR_TRPT); 


	UI_BTN btn[] = 
	{
// 		UI_BTN(this, BTN_MPOINT_ADDPROFILE, CRect(145, 35, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILE, IDB_VGAPRO_ADDFILEOFF)),
// 		UI_BTN(this, BTN_MPOINT_EDITPROFILE, CRect(165, 35, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITON, IDB_VGAPRO_EDITOFF, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILE, IDB_VGAPRO_SAVEFILEOFF, CLR_TRPT), NULL, BTN_CHECK),
// 		UI_BTN(this, BTN_MPOINT_DELPROFILE,  CRect(185, 35, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_DELETEFILE, IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILE,	IDB_VGAPRO_DELETEFILEOFF)),

		UI_BTN(this, BTN_MPOINT_DPI1,	CRect(15, 45, 0, 0), &UIBTN_IMAGE(IDB_MPOINT_M3DPI1_OFF, IDB_MPOINT_M3DPI1_OFF, IDB_MPOINT_M3DPI1_OFF, IDB_MPOINT_M3DPI1_OFF, IDB_MPOINT_M3DPI1_ON, IDB_MPOINT_M3DPI1_ON, IDB_MPOINT_M3DPI1_ON, IDB_MPOINT_M3DPI1_OFF, CLR_TRPT), NULL, BTN_RADIO),
		UI_BTN(this, BTN_MPOINT_DPI2,	CRect(15, 125, 0, 0), &UIBTN_IMAGE(IDB_MPOINT_M3DPI2_OFF, IDB_MPOINT_M3DPI2_OFF, IDB_MPOINT_M3DPI2_OFF, IDB_MPOINT_M3DPI2_OFF, IDB_MPOINT_M3DPI2_ON, IDB_MPOINT_M3DPI2_ON, IDB_MPOINT_M3DPI2_ON, IDB_MPOINT_M3DPI2_OFF, CLR_TRPT), NULL, BTN_RADIO),
		UI_BTN(this, BTN_MPOINT_DPI3,	CRect(15, 205, 0, 0), &UIBTN_IMAGE(IDB_MPOINT_M3DPI3_OFF, IDB_MPOINT_M3DPI3_OFF, IDB_MPOINT_M3DPI3_OFF, IDB_MPOINT_M3DPI3_OFF, IDB_MPOINT_M3DPI3_ON, IDB_MPOINT_M3DPI3_ON, IDB_MPOINT_M3DPI3_ON, IDB_MPOINT_M3DPI3_OFF, CLR_TRPT), NULL, BTN_RADIO),
		UI_BTN(this, BTN_MPOINT_DPI4,	CRect(15, 285, 0, 0), &UIBTN_IMAGE(IDB_MPOINT_M3DPI4_OFF, IDB_MPOINT_M3DPI4_OFF, IDB_MPOINT_M3DPI4_OFF, IDB_MPOINT_M3DPI4_OFF, IDB_MPOINT_M3DPI4_ON, IDB_MPOINT_M3DPI4_ON, IDB_MPOINT_M3DPI4_ON, IDB_MPOINT_M3DPI4_OFF, CLR_TRPT), NULL, BTN_RADIO),

		UI_BTN(this, BTN_MPOINT_DPI1_LINK,  CRect(70+5, 55+10, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, 0, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, 0, CLR_TRPT),NULL,BTN_CHECK),
		UI_BTN(this, BTN_MPOINT_DPI2_LINK,  CRect(70+5, 135+10, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, 0, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, 0, CLR_TRPT),NULL,BTN_CHECK),
		UI_BTN(this, BTN_MPOINT_DPI3_LINK,  CRect(70+5, 215+10, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, 0, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, 0, CLR_TRPT),NULL,BTN_CHECK),
		UI_BTN(this, BTN_MPOINT_DPI4_LINK,  CRect(70+5, 295+10, 0, 0), &UIBTN_IMAGE(IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, IDB_VGAPRO_UNLINK_ON, 0, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, IDB_VGAPRO_LINK_ON, 0, CLR_TRPT),NULL,BTN_CHECK),

		UI_BTN(this, BTN_MPOINT_DPI1_XDEC, CRect(200, 40, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
		UI_BTN(this, BTN_MPOINT_DPI1_XINC, CRect(250, 40, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
		UI_BTN(this, BTN_MPOINT_DPI1_YDEC, CRect(200, 80, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
		UI_BTN(this, BTN_MPOINT_DPI1_YINC, CRect(250, 80, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),

 		UI_BTN(this, BTN_MPOINT_DPI2_XDEC, CRect(200, 120, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI2_XINC, CRect(250, 120, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI2_YDEC, CRect(200, 160, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI2_YINC, CRect(250, 160, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 
 		UI_BTN(this, BTN_MPOINT_DPI3_XDEC, CRect(200, 200, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI3_XINC, CRect(250, 200, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI3_YDEC, CRect(200, 240, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI3_YINC, CRect(250, 240, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 
 		UI_BTN(this, BTN_MPOINT_DPI4_XDEC, CRect(200, 280, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI4_XINC, CRect(250, 280, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI4_YDEC, CRect(200, 320, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, IDB_BTN_M3_POINTER_DIP_DEC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),
 		UI_BTN(this, BTN_MPOINT_DPI4_YINC, CRect(250, 320, 0, 0), &UIBTN_IMAGE(IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, IDB_BTN_M3_POINTER_DIP_INC, 0, 0, 0, 0, 0, CLR_TRPT),NULL),

 		UI_BTN(this, BTN_MPOINT_REPORT_RATE_DEC,   CRect(326, 260, 0, 0), &UIBTN_IMAGE(IDB_BTN_DECCLICK, IDB_BTN_DECCLICK, IDB_BTN_DECCLICK, 0, 0, 0, 0, 0, CLR_TRPT)),
 		UI_BTN(this, BTN_MPOINT_REPORT_RATE_INC,   CRect(604, 260, 0, 0), &UIBTN_IMAGE(IDB_BTN_INCCLICK, IDB_BTN_INCCLICK, IDB_BTN_INCCLICK, 0, 0, 0, 0, 0, CLR_TRPT)),

		UI_BTN(this, BTN_MPOINT_APPLY, CRect(240+80, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYON, IDB_MOUSE_APPLYOFF, CLR_TRPT)),
		UI_BTN(this, BTN_MPOINT_RESET, CRect(340+75, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_RESETON, IDB_MOUSE_RESETON, IDB_MOUSE_RESETON, IDB_MOUSE_RESETOFF, CLR_TRPT)),
		UI_BTN(this, BTN_MPOINT_DEFAULT, CRect(440+70, 290, 0, 0), &UIBTN_IMAGE(IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTON, IDB_MOUSE_DEFAULTOFF, CLR_TRPT)),	
	};

	for(int i=BTN_MPOINT_DPI1; i <= BTN_MPOINT_DEFAULT; i++)
	{
		m_btn[i].CreateButton(btn[i - (int)BTN_MPOINT_DPI1]);
		m_btn[i].SetCursor(IDC_CUR_HAND);
	}

	//四種模式對應四張背景圖
	UI_STATIC sta[] = 
	{
		UI_STATIC(this, STC_MPOINT_STATUS1, CRect(350, 50, 0, 0), _T(""), IDB_MPOINT_M3DPI1_STATUS, CLR_TRPT),
		UI_STATIC(this, STC_MPOINT_STATUS2, CRect(350, 50, 0, 0), _T(""), IDB_MPOINT_M3DPI2_STATUS, CLR_TRPT),
		UI_STATIC(this, STC_MPOINT_STATUS3, CRect(350, 50, 0, 0), _T(""), IDB_MPOINT_M3DPI3_STATUS, CLR_TRPT),
		UI_STATIC(this, STC_MPOINT_STATUS4, CRect(350, 50, 0, 0), _T(""), IDB_MPOINT_M3DPI4_STATUS, CLR_TRPT),
	};

	for (int i = STC_MPOINT_STATUS1; i <= STC_MPOINT_STATUS4; i++)
	{
		m_stc[i].CreateStatic(sta[i - (int)STC_MPOINT_STATUS1]);
	}

	m_stc[STC_MPOINT_STATUS1].ShowWindow(SW_HIDE);
	m_stc[STC_MPOINT_STATUS2].ShowWindow(SW_HIDE);
	m_stc[STC_MPOINT_STATUS3].ShowWindow(SW_HIDE);
	m_stc[STC_MPOINT_STATUS4].ShowWindow(SW_HIDE);


	UI_STATIC sta1[] = 
	{
		UI_STATIC(this, STC_MPOINT_DPI1_X,	CRect(215, 43, 248, 50), _T("50DPI"), NULL, CLR_TRPT),
		UI_STATIC(this, STC_MPOINT_DPI1_Y,	CRect(215, 83, 248, 90), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI2_X,	CRect(215, 123, 248, 130), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI2_Y,	CRect(215, 163, 248, 170), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI3_X,	CRect(215, 203, 248, 210), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI3_Y,	CRect(215, 343, 248, 250), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI4_X,	CRect(215, 283, 248, 290), _T("50DPI"), NULL, CLR_TRPT),
  		UI_STATIC(this, STC_MPOINT_DPI4_Y,	CRect(215, 323, 248, 330), _T("6400DPI"), NULL, CLR_TRPT),

 		UI_STATIC(this, STC_MPOINT_REPORT_RATE,	CRect(310, 278-30, 360, 285-30), _T("REPORT RATE"), NULL, CLR_TRPT),
 		UI_STATIC(this, STC_MPOINT_REPORT_RATE_VAL, CRect(580, 278-30, 630, 285-30), _T("0000"), NULL, CLR_TRPT),
	};

	for (int i = STC_MPOINT_DPI1_X; i <= STC_MPOINT_REPORT_RATE_VAL; i++)
	{
		m_stc[i].CreateStatic(sta1[i - (int)STC_MPOINT_DPI1_X]);
		m_stc[i].ModifyCtrlStyle(0, ST_VCENTER | ST_CENTER | ST_SINGLELINE);
		m_stc[i].SetFont(Font(6), CLR_WHITE);
	}

	UI_SLIDERCTRL sld[] = {
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI1,	CRect(95,  70,  0,  0), IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_OFF, IDB_SLD_DPI_SLD_BAR_OFF, IDB_SLD_DPI_SLD_BAR_ON, IDB_SLD_DPI_SLD_BAR_OFF, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI2,	CRect(95,  150,  0,  0), IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_OFF, IDB_SLD_DPI_SLD_BAR_OFF, IDB_SLD_DPI_SLD_BAR_ON, IDB_SLD_DPI_SLD_BAR_OFF, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI3,	CRect(95,  230,  0,  0), IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_OFF, IDB_SLD_DPI_SLD_BAR_OFF, IDB_SLD_DPI_SLD_BAR_ON, IDB_SLD_DPI_SLD_BAR_OFF, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI4,	CRect(95,  310,  0,  0), IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_OFF, IDB_SLD_DPI_SLD_BAR_OFF, IDB_SLD_DPI_SLD_BAR_ON, IDB_SLD_DPI_SLD_BAR_OFF, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_REPORT_RATE,	CRect(340,  260,  0,  0), IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_ON, IDB_SLD_DPI_BAR_OFF, IDB_SLD_REPORT_RATE_OFF, IDB_SLD_REPORT_RATE_ON, IDB_SLD_REPORT_RATE_OFF, CLR_TRPT),
	};

	for(int i=SLD_MPOINT_DPI1; i <= SLD_MPOINT_REPORT_RATE; i++)
	{
		m_slider[i].CreateSliderCtrl(sld[i - (int)SLD_MPOINT_DPI1]);
		if (i == SLD_MPOINT_REPORT_RATE)
		{
			m_slider[i].SetRange(1, 8);
		}
		else
		{
			m_slider[i].SetRange(1, 128);
		}
	}

	UI_SLIDERCTRL slider[] = 
	{
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI1_X,	CRect(95, 50,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI1_Y,	CRect(95, 90,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI2_X,	CRect(95, 130,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI2_Y,	CRect(95, 170,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI3_X,	CRect(95, 210,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI3_Y,	CRect(95, 250,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI4_X,	CRect(95, 290,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
		UI_SLIDERCTRL(this, SLD_MPOINT_DPI4_Y,	CRect(95, 330,   0,   0), 0, 0, 0, IDB_SLI_DPI_00, IDB_SLI_DPI_10, IDB_SLI_DPI_00, CLR_TRPT),
	};

	for(int i=SLD_MPOINT_DPI1_X; i<=SLD_MPOINT_DPI4_Y; i++)
	{
		m_slider[i].CreateSliderCtrl(slider[i - (int)SLD_MPOINT_DPI1_X]);
		m_slider[i].SetRange(1, 128);
	}

	m_combobox[COMBOX_MPOINT_PROFILE].Create(CRect(10, 35, 0, 0), this, COMBOX_MPOINT_PROFILE);
	m_combobox[COMBOX_MPOINT_PROFILE].SetComboBoxBitmap(IDB_VGALED_COMB_NORMAL ,IDB_VGALED_COMB_NORMAL, IDB_VGALED_COMB_NORMAL, 0, CLR_NONE);
	m_combobox[COMBOX_MPOINT_PROFILE].SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_MPOINT_PROFILE].SetCursor(IDC_CUR_HAND);
	m_combobox[COMBOX_MPOINT_PROFILE].SetArrowWidth(20);
	m_combobox[COMBOX_MPOINT_PROFILE].GetDropList()->SetFont(Font(11), CLR_WHITE);
	m_combobox[COMBOX_MPOINT_PROFILE].GetDropList()->SetBkColor(RGB(0, 0, 0));
	m_combobox[COMBOX_MPOINT_PROFILE].GetDropList()->SetHighlightBkColor(CLR_MAIN);
	m_combobox[COMBOX_MPOINT_PROFILE].ShowWindow(SW_HIDE);

// 	m_stc.CreateStatic(UI_STATIC(this, 0, CRect(10, 10, 200,200), _T("CMousePointerDlg"), NULL, CLR_NONE));
// 	m_stc.SetFont(Font(18), CLR_MAIN);
}

void CMousePointerDlg::InitState()
{
	int tick1 = ::GetTickCount();
	CmdLock();

	for (int i = 0; i < 4; i++) // 一初始化就馬上提出來
	{
		m_dpi[i].nIndex = i;

		CAM300Ctrl::GetDPI(m_dpi[i]);
	}

	EnableAll(true); // 在設定之前，先enable所有的控件
	for (int i = 0; i < 4; i++) // 設置xy\link等控件的值
	{
		GVORDER_DPI d = m_dpi[i];
		ShowXY(i, d.nX, d.nY);
	}

	// 取得當前的DPIindex
	GVORDER_DPI curDPI;
	CAM300Ctrl::GetCurDPI(curDPI);
	m_ndpiIndex = curDPI.nIndex;

	// 設置現在是DPI幾
	OnUiButtonClicked(m_ndpiIndex + BTN_MPOINT_DPI1, 0);
	ShowXY(m_ndpiIndex, curDPI.nX, curDPI.nY);

	// 取得report
	int nReport = 0; // 從8到1，8表示125， 1表示1000
	CAM300Ctrl::GetReportRate(nReport);
	m_slider[SLD_MPOINT_REPORT_RATE].Enable(true);
	m_slider[SLD_MPOINT_REPORT_RATE].SetPos(s_Report_Rate[nReport]);
	m_stc[STC_MPOINT_REPORT_RATE_VAL].SetCaption(s_sReport_Rate[nReport]);
	m_btn[BTN_MPOINT_REPORT_RATE_DEC].Enable(true);
	m_btn[BTN_MPOINT_REPORT_RATE_INC].Enable(true);
	m_nReportRate = nReport;
	int tick2 = ::GetTickCount();
	CString sValue;
	sValue.Format(_T("Loading DPI:%d\n"), tick2 - tick1);
	TRACE(sValue);
	CmdUnLock();
}

LRESULT CMousePointerDlg::OnUiButtonClicked(WPARAM wParam, LPARAM lParam)
{

// 	m_stc[STC_MPOINT_STATUS1].ShowWindow(SW_HIDE);
// 	m_stc[STC_MPOINT_STATUS2].ShowWindow(SW_HIDE);
// 	m_stc[STC_MPOINT_STATUS3].ShowWindow(SW_HIDE);
// 	m_stc[STC_MPOINT_STATUS4].ShowWindow(SW_HIDE);

	switch(wParam)
	{
	case BTN_MPOINT_REPORT_RATE_DEC:
	case BTN_MPOINT_REPORT_RATE_INC:
		m_slider[SLD_MPOINT_REPORT_RATE].SetPos(m_slider[SLD_MPOINT_REPORT_RATE].GetPos() + (BTN_MPOINT_REPORT_RATE_DEC == wParam ? -1 : 1));
		m_stc[STC_MPOINT_REPORT_RATE_VAL].SetCaption(s_sReport_Rate[GetReportRate(m_slider[SLD_MPOINT_REPORT_RATE].GetPos())]);
		break;

	case BTN_MPOINT_APPLY:
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			int nReportRate = m_slider[SLD_MPOINT_REPORT_RATE].GetPos();
			int nDPIX = 0;
			int nDPIY = 0;
			switch (m_ndpiIndex)
			{
			case 0:
				nDPIX = m_slider[SLD_MPOINT_DPI1_X].GetPos(); // 取得DPIX和Y
				nDPIY = m_slider[SLD_MPOINT_DPI1_Y].GetPos();
				break;
			case 1:
				nDPIX = m_slider[SLD_MPOINT_DPI2_X].GetPos(); // 取得DPIX和Y
				nDPIY = m_slider[SLD_MPOINT_DPI2_Y].GetPos();
				break;
			case 2:
				nDPIX = m_slider[SLD_MPOINT_DPI3_X].GetPos(); // 取得DPIX和Y
				nDPIY = m_slider[SLD_MPOINT_DPI3_Y].GetPos();
				break;
			case 3:
				nDPIX = m_slider[SLD_MPOINT_DPI4_X].GetPos(); // 取得DPIX和Y
				nDPIY = m_slider[SLD_MPOINT_DPI4_Y].GetPos();
				break;
			}
			CmdLock();
			GVORDER_DPI dpi = {m_ndpiIndex, nDPIX, nDPIY}; // 保存dpi
			m_dpi[m_ndpiIndex] = dpi;
			CAM300Ctrl::SetDPI(dpi);
			Sleep(100);
			CAM300Ctrl::SelDPI(m_ndpiIndex);
			Sleep(100);
			m_nReportRate = GetReportRate(nReportRate);
			CAM300Ctrl::SetReportRate(m_nReportRate);
			Sleep(100);
			CmdUnLock();
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	case BTN_MPOINT_RESET:
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			OnUiSliderMoving(SLD_MPOINT_REPORT_RATE, GetReportRate(m_nReportRate));
			GVORDER_DPI dpi = m_dpi[m_ndpiIndex];
			ShowXY(m_ndpiIndex, dpi.nX, dpi.nY);
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;
	case BTN_MPOINT_DEFAULT:
		{
			ShowLoadingWindow(AfxGetMainWnd(), SW_SHOW);
			CmdLock();

			// 全部設置為enable
			EnableAll(true);
			// 設置所有的xy值，全部link
			ShowXY(0, 16, 16);
			ShowXY(1, 32, 32);
			ShowXY(2, 48, 48);
			ShowXY(3, 64, 64);
			//設置當前的在哪個dpi上
			OnUiButtonClicked(m_ndpiIndex + BTN_MPOINT_DPI1, 0);
			// 全部set使其生效
			for (int i = 0; i < 4; i++)
			{
				GVORDER_DPI dpi = {i, (i + 1) * 16, (i + 1) * 16}; // 保存dpi
				m_dpi[i] = dpi;
				CAM300Ctrl::SetDPI(dpi);
				Sleep(100);
			}
			CAM300Ctrl::SelDPI(m_ndpiIndex);
			Sleep(100);
			m_nReportRate = 1;
			m_slider[SLD_MPOINT_REPORT_RATE].SetPos(GetReportRate(m_nReportRate));
			OnUiSliderMoving(SLD_MPOINT_REPORT_RATE, GetReportRate(m_nReportRate));
			CAM300Ctrl::SetReportRate(m_nReportRate);
			CmdUnLock();
			ShowLoadingWindow(AfxGetMainWnd(), SW_HIDE);
		}
		break;

	case BTN_MPOINT_DPI1: // 切換dpi級別
	case BTN_MPOINT_DPI2:
	case BTN_MPOINT_DPI3:
	case BTN_MPOINT_DPI4:
		{
 	 	m_stc[STC_MPOINT_STATUS1].ShowWindow(SW_HIDE);
 	 	m_stc[STC_MPOINT_STATUS2].ShowWindow(SW_HIDE);
 	 	m_stc[STC_MPOINT_STATUS3].ShowWindow(SW_HIDE);
 	 	m_stc[STC_MPOINT_STATUS4].ShowWindow(SW_HIDE);
		CmdLock();
		m_btn[BTN_MPOINT_DPI1].SetCheck(BTN_MPOINT_DPI1 == wParam);
		m_btn[BTN_MPOINT_DPI2].SetCheck(BTN_MPOINT_DPI2 == wParam);
		m_btn[BTN_MPOINT_DPI3].SetCheck(BTN_MPOINT_DPI3 == wParam);
		m_btn[BTN_MPOINT_DPI4].SetCheck(BTN_MPOINT_DPI4 == wParam);
		m_ndpiIndex = wParam - BTN_MPOINT_DPI1;

		switch(m_ndpiIndex)
		{
			case 0: m_stc[STC_MPOINT_STATUS1].ShowWindow(SW_SHOW); break;
			case 1: m_stc[STC_MPOINT_STATUS2].ShowWindow(SW_SHOW); break;
			case 2: m_stc[STC_MPOINT_STATUS3].ShowWindow(SW_SHOW); break;
			case 3: m_stc[STC_MPOINT_STATUS4].ShowWindow(SW_SHOW); break;
		}
		EnableDPIOne(m_ndpiIndex);
		OnUiButtonClicked(m_ndpiIndex + BTN_MPOINT_DPI1_LINK, 0);
		if(lParam >= 0)CAM300Ctrl::SelDPI(m_ndpiIndex);
		CmdUnLock();
	    }
		break;

	case BTN_MPOINT_DPI1_LINK: // 連接xy
		{
			bool b = m_btn[BTN_MPOINT_DPI1_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI1].Enable(b);
			m_slider[SLD_MPOINT_DPI1_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI1_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI1_YINC].Enable(!b);
		}
		break;
	case BTN_MPOINT_DPI2_LINK:
		{
			bool b = m_btn[BTN_MPOINT_DPI2_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI2].Enable(b);
			m_slider[SLD_MPOINT_DPI2_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI2_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI2_YINC].Enable(!b);
		}
		break;
	case BTN_MPOINT_DPI3_LINK:
		{
			bool b = m_btn[BTN_MPOINT_DPI3_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI3].Enable(b);
			m_slider[SLD_MPOINT_DPI3_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI3_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI3_YINC].Enable(!b);
		}
		break;
	case BTN_MPOINT_DPI4_LINK:
		{
			bool b = m_btn[BTN_MPOINT_DPI4_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI4].Enable(b);
			m_slider[SLD_MPOINT_DPI4_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI4_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI4_YINC].Enable(!b);
		}
		break;

	case BTN_MPOINT_DPI1_XDEC: // dpi1加減
	case BTN_MPOINT_DPI1_XINC:
		{
			m_slider[SLD_MPOINT_DPI1_X].SetPos(m_slider[SLD_MPOINT_DPI1_X].GetPos() + (BTN_MPOINT_DPI1_XDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI1_X].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI1_X].GetPos()));
			if (m_btn[BTN_MPOINT_DPI1_LINK].IsCheck()) // 如果是聯動的，則在dpi加減的時候，同時改變中間的聯動桿
			{
				m_slider[SLD_MPOINT_DPI1].SetPos(m_slider[SLD_MPOINT_DPI1_X].GetPos());
				m_slider[SLD_MPOINT_DPI1_Y].SetPos(m_slider[SLD_MPOINT_DPI1_X].GetPos());
				m_stc[STC_MPOINT_DPI1_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI1_X].GetPos()));
			}
		}
		break;
	case BTN_MPOINT_DPI1_YDEC:
	case BTN_MPOINT_DPI1_YINC:
		{
			m_slider[SLD_MPOINT_DPI1_Y].SetPos(m_slider[SLD_MPOINT_DPI1_Y].GetPos() + (BTN_MPOINT_DPI1_YDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI1_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI1_Y].GetPos()));
		}
		break;

	case BTN_MPOINT_DPI2_XDEC: // dpi2加減
	case BTN_MPOINT_DPI2_XINC:
		{
			m_slider[SLD_MPOINT_DPI2_X].SetPos(m_slider[SLD_MPOINT_DPI2_X].GetPos() + (BTN_MPOINT_DPI2_XDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI2_X].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI2_X].GetPos()));
			if (m_btn[BTN_MPOINT_DPI2_LINK].IsCheck()) // 如果是聯動的，則在dpi加減的時候，同時改變中間的聯動桿
			{
				m_slider[SLD_MPOINT_DPI2].SetPos(m_slider[SLD_MPOINT_DPI2_X].GetPos());
				m_slider[SLD_MPOINT_DPI2_Y].SetPos(m_slider[SLD_MPOINT_DPI2_X].GetPos());
				m_stc[STC_MPOINT_DPI2_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI2_X].GetPos()));
			}
		}
		break;
	case BTN_MPOINT_DPI2_YDEC:
	case BTN_MPOINT_DPI2_YINC:
		{
			m_slider[SLD_MPOINT_DPI2_Y].SetPos(m_slider[SLD_MPOINT_DPI2_Y].GetPos() + (BTN_MPOINT_DPI2_YDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI2_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI2_Y].GetPos()));
		}
		break;

		//=================================================================================================

	case BTN_MPOINT_DPI3_XDEC: // dpi3加減
	case BTN_MPOINT_DPI3_XINC:
		{
			m_slider[SLD_MPOINT_DPI3_X].SetPos(m_slider[SLD_MPOINT_DPI3_X].GetPos() + (BTN_MPOINT_DPI3_XDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI3_X].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI3_X].GetPos()));
			if (m_btn[BTN_MPOINT_DPI3_LINK].IsCheck()) // 如果是聯動的，則在dpi加減的時候，同時改變中間的聯動桿
			{
				m_slider[SLD_MPOINT_DPI3].SetPos(m_slider[SLD_MPOINT_DPI3_X].GetPos());
				m_slider[SLD_MPOINT_DPI3_Y].SetPos(m_slider[SLD_MPOINT_DPI3_X].GetPos());
				m_stc[STC_MPOINT_DPI3_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI3_X].GetPos()));
			}
		}
		break;
	case BTN_MPOINT_DPI3_YDEC:
	case BTN_MPOINT_DPI3_YINC:
		{
			m_slider[SLD_MPOINT_DPI3_Y].SetPos(m_slider[SLD_MPOINT_DPI3_Y].GetPos() + (BTN_MPOINT_DPI3_YDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI3_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI3_Y].GetPos()));
		}
		break;

		//=================================================================================================

	case BTN_MPOINT_DPI4_XDEC: // dpi4加減
	case BTN_MPOINT_DPI4_XINC:
		{
			m_slider[SLD_MPOINT_DPI4_X].SetPos(m_slider[SLD_MPOINT_DPI4_X].GetPos() + (BTN_MPOINT_DPI4_XDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI4_X].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI4_X].GetPos()));
			if (m_btn[BTN_MPOINT_DPI4_LINK].IsCheck()) // 如果是聯動的，則在dpi加減的時候，同時改變中間的聯動桿
			{
				m_slider[SLD_MPOINT_DPI4].SetPos(m_slider[SLD_MPOINT_DPI4_X].GetPos());
				m_slider[SLD_MPOINT_DPI4_Y].SetPos(m_slider[SLD_MPOINT_DPI4_X].GetPos());
				m_stc[STC_MPOINT_DPI4_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI4_X].GetPos()));
			}
		}
		break;
	case BTN_MPOINT_DPI4_YDEC:
	case BTN_MPOINT_DPI4_YINC:
		{
			m_slider[SLD_MPOINT_DPI4_Y].SetPos(m_slider[SLD_MPOINT_DPI4_Y].GetPos() + (BTN_MPOINT_DPI4_YDEC == wParam ? -1 : 1));
			m_stc[STC_MPOINT_DPI4_Y].SetCaption(GetDPIString(m_slider[SLD_MPOINT_DPI4_Y].GetPos()));
		}
		break;

	}
	
	return 1;
}



LRESULT CMousePointerDlg::OnUiSliderMoving(WPARAM wParam, LPARAM lParam)
{
	int nCurValue = (int)lParam;
	switch(wParam)
	{
	case SLD_MPOINT_DPI1_X: // 8個xy
		m_stc[STC_MPOINT_DPI1_X].SetCaption(GetDPIString(nCurValue));
		if (m_btn[BTN_MPOINT_DPI1_LINK].IsCheck())
		{
			m_slider[SLD_MPOINT_DPI1].SetPos(nCurValue);
		}
		break;
	case SLD_MPOINT_DPI1_Y:
		m_stc[STC_MPOINT_DPI1_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI2_X:
		m_stc[STC_MPOINT_DPI2_X].SetCaption(GetDPIString(nCurValue));
		if (m_btn[BTN_MPOINT_DPI2_LINK].IsCheck())
		{
			m_slider[SLD_MPOINT_DPI2].SetPos(nCurValue);
		}
		break;
	case SLD_MPOINT_DPI2_Y:
		m_stc[STC_MPOINT_DPI2_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI3_X:
		m_stc[STC_MPOINT_DPI3_X].SetCaption(GetDPIString(nCurValue));
		if (m_btn[BTN_MPOINT_DPI3_LINK].IsCheck())
		{
			m_slider[SLD_MPOINT_DPI3].SetPos(nCurValue);
		}
		break;
	case SLD_MPOINT_DPI3_Y:
		m_stc[STC_MPOINT_DPI3_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI4_X:
		if (m_btn[BTN_MPOINT_DPI4_LINK].IsCheck())
		{
			m_slider[SLD_MPOINT_DPI4].SetPos(nCurValue);
		}
		m_stc[STC_MPOINT_DPI4_X].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI4_Y:
		m_stc[STC_MPOINT_DPI4_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI1: // 4個聯動桿
		m_slider[SLD_MPOINT_DPI1_X].SetPos(nCurValue);
		m_slider[SLD_MPOINT_DPI1_Y].SetPos(nCurValue);
		m_stc[STC_MPOINT_DPI1_X].SetCaption(GetDPIString(nCurValue));
		m_stc[STC_MPOINT_DPI1_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI2:
		m_slider[SLD_MPOINT_DPI2_X].SetPos(nCurValue);
		m_slider[SLD_MPOINT_DPI2_Y].SetPos(nCurValue);
		m_stc[STC_MPOINT_DPI2_X].SetCaption(GetDPIString(nCurValue));
		m_stc[STC_MPOINT_DPI2_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI3:
		m_slider[SLD_MPOINT_DPI3_X].SetPos(nCurValue);
		m_slider[SLD_MPOINT_DPI3_Y].SetPos(nCurValue);
		m_stc[STC_MPOINT_DPI3_X].SetCaption(GetDPIString(nCurValue));
		m_stc[STC_MPOINT_DPI3_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_DPI4:
		m_slider[SLD_MPOINT_DPI4_X].SetPos(nCurValue);
		m_slider[SLD_MPOINT_DPI4_Y].SetPos(nCurValue);
		m_stc[STC_MPOINT_DPI4_X].SetCaption(GetDPIString(nCurValue));
		m_stc[STC_MPOINT_DPI4_Y].SetCaption(GetDPIString(nCurValue));
		break;
	case SLD_MPOINT_REPORT_RATE:
		m_stc[STC_MPOINT_REPORT_RATE_VAL].SetCaption(s_sReport_Rate[GetReportRate(lParam)]);
		break;
	}

	return 1;
}

int CMousePointerDlg::GetReportRate(int pos)
{
	for (int i = 1; i <= 8; i++)
	{
		if (pos == s_Report_Rate[i])
		{
			return i;
		}
	}
	return 1;
}

CString CMousePointerDlg::GetDPIString(int num)
{
	CString s;
	s.Format(_T("%dDPI"), num * 50);
	return s;
}

void CMousePointerDlg::EnableAll(bool b)
{
	for (int i = BTN_MPOINT_DPI1_LINK; i <= BTN_MPOINT_DPI4_LINK; i++) // link
	{
		m_btn[i].Enable(b);
	}
	for (int i = SLD_MPOINT_DPI1; i <= SLD_MPOINT_DPI4; i++) // 聯動桿
	{
		m_slider[i].Enable(b);
	}
	for (int i = SLD_MPOINT_DPI1_X; i <= SLD_MPOINT_DPI4_Y; i++) // 8個拉動桿
	{
		m_slider[i].Enable(b);
	}
	for (int i = BTN_MPOINT_DPI1_XDEC; i <= BTN_MPOINT_DPI4_YINC; i++) // 16個加減
	{
		m_btn[i].Enable(b);
	}
}

void CMousePointerDlg::EnableDPIOne(int index)
{
	for (int i = BTN_MPOINT_DPI1_LINK; i <= BTN_MPOINT_DPI4_LINK; i++) // link
	{
		m_btn[i].Enable(false);
	}
	for (int i = SLD_MPOINT_DPI1; i <= SLD_MPOINT_DPI4; i++) // 聯動桿
	{
		m_slider[i].Enable(false);
	}
	for (int i = SLD_MPOINT_DPI1_X; i <= SLD_MPOINT_DPI4_Y; i++) // 8個拉動桿
	{
		m_slider[i].Enable(false);
	}
	for (int i = BTN_MPOINT_DPI1_XDEC; i <= BTN_MPOINT_DPI4_YINC; i++) // 16個加減
	{
		m_btn[i].Enable(false);
	}

	//以上全部false

	//只開啟index
	m_btn[index + BTN_MPOINT_DPI1_LINK].Enable(true);
	m_slider[index + SLD_MPOINT_DPI1].Enable(true);

	switch (index)// 2個拉動桿,4個加減
	{
	case 0:
		m_slider[SLD_MPOINT_DPI1_X].Enable(true);
		m_slider[SLD_MPOINT_DPI1_Y].Enable(true);

		m_btn[BTN_MPOINT_DPI1_XDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI1_XINC].Enable(true);
		m_btn[BTN_MPOINT_DPI1_YDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI1_YINC].Enable(true);
		break;
	case 1:
		m_slider[SLD_MPOINT_DPI2_X].Enable(true);
		m_slider[SLD_MPOINT_DPI2_Y].Enable(true);

		m_btn[BTN_MPOINT_DPI2_XDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI2_XINC].Enable(true);
		m_btn[BTN_MPOINT_DPI2_YDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI2_YINC].Enable(true);
		break;
	case 2:
		m_slider[SLD_MPOINT_DPI3_X].Enable(true);
		m_slider[SLD_MPOINT_DPI3_Y].Enable(true);

		m_btn[BTN_MPOINT_DPI3_XDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI3_XINC].Enable(true);
		m_btn[BTN_MPOINT_DPI3_YDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI3_YINC].Enable(true);
		break;
	case 3:
		m_slider[SLD_MPOINT_DPI4_X].Enable(true);
		m_slider[SLD_MPOINT_DPI4_Y].Enable(true);

		m_btn[BTN_MPOINT_DPI4_XDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI4_XINC].Enable(true);
		m_btn[BTN_MPOINT_DPI4_YDEC].Enable(true);
		m_btn[BTN_MPOINT_DPI4_YINC].Enable(true);
		break;
	}
}

void CMousePointerDlg::ShowXY(int index, int x, int y)
{
	// 設置DPI X Y 的數值顯示框和pos，設置是否link
	switch (index)
	{
	case 0:
		{
			m_slider[SLD_MPOINT_DPI1_X].SetPos(x);
			m_slider[SLD_MPOINT_DPI1_Y].SetPos(y);
			m_stc[STC_MPOINT_DPI1_X].SetCaption(GetDPIString(x));
			m_stc[STC_MPOINT_DPI1_Y].SetCaption(GetDPIString(y));

			// x和y不相等，則不要link
			m_btn[BTN_MPOINT_DPI1_LINK].SetCheck(x == y);

			// 如果link了，那麼disable y，enable中間拉動桿，否則enable y，disable 中間的聯動桿
			bool b = m_btn[BTN_MPOINT_DPI1_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI1].Enable(b);
			m_slider[SLD_MPOINT_DPI1_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI1_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI1_YINC].Enable(!b);

			if (b) // 如果link了，設置中間拉動桿的pos
			{
				m_slider[SLD_MPOINT_DPI1].SetPos(x);
			}
		}
		break;
	case 1:
		{
			m_slider[SLD_MPOINT_DPI2_X].SetPos(x);
			m_slider[SLD_MPOINT_DPI2_Y].SetPos(y);
			m_stc[STC_MPOINT_DPI2_X].SetCaption(GetDPIString(x));
			m_stc[STC_MPOINT_DPI2_Y].SetCaption(GetDPIString(y));

			// x和y不相等，則不要link
			m_btn[BTN_MPOINT_DPI2_LINK].SetCheck(x == y);

			bool b = m_btn[BTN_MPOINT_DPI2_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI2].Enable(b);
			m_slider[SLD_MPOINT_DPI2_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI2_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI2_YINC].Enable(!b);

			if (b) // 如果link了，設置中間拉動桿的pos
			{
				m_slider[SLD_MPOINT_DPI2].SetPos(x);
			}
		}
		break;
	case 2:
		{
			m_slider[SLD_MPOINT_DPI3_X].SetPos(x);
			m_slider[SLD_MPOINT_DPI3_Y].SetPos(y);
			m_stc[STC_MPOINT_DPI3_X].SetCaption(GetDPIString(x));
			m_stc[STC_MPOINT_DPI3_Y].SetCaption(GetDPIString(y));

			m_btn[BTN_MPOINT_DPI3_LINK].SetCheck(x == y);

			bool b = m_btn[BTN_MPOINT_DPI3_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI3].Enable(b);
			m_slider[SLD_MPOINT_DPI3_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI3_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI3_YINC].Enable(!b);

			if (b) // 如果link了，設置中間拉動桿的pos
			{
				m_slider[SLD_MPOINT_DPI3].SetPos(x);
			}
		}
		break;
	case 3:
		{
			m_slider[SLD_MPOINT_DPI4_X].SetPos(x);
			m_slider[SLD_MPOINT_DPI4_Y].SetPos(y);
			m_stc[STC_MPOINT_DPI4_X].SetCaption(GetDPIString(x));
			m_stc[STC_MPOINT_DPI4_Y].SetCaption(GetDPIString(y));

			m_btn[BTN_MPOINT_DPI4_LINK].SetCheck(x == y);

			bool b = m_btn[BTN_MPOINT_DPI4_LINK].IsCheck();
			m_slider[SLD_MPOINT_DPI4].Enable(b);
			m_slider[SLD_MPOINT_DPI4_Y].Enable(!b);
			m_btn[BTN_MPOINT_DPI4_YDEC].Enable(!b);
			m_btn[BTN_MPOINT_DPI4_YINC].Enable(!b);

			if (b) // 如果link了，設置中間拉動桿的pos
			{
				m_slider[SLD_MPOINT_DPI4].SetPos(x);
			}
		}
		break;
	}
}

void CMousePointerDlg::OnHIDInput(BYTE* byData)
{
	if(byData[0] == 0xab)// dpi
	{
		m_ndpiIndex = byData[1]; // 當前dpiindex
		TCHAR szVersion[1024];
// 		CmdLock();
// 		GvOrderVersion(szVersion, s_MouseIndex);
// 		CmdUnLock();

		GVORDER_DPI dpi = m_dpi[m_ndpiIndex];

		OnUiButtonClicked(m_ndpiIndex + BTN_MPOINT_DPI1, -1);
		ShowXY(m_ndpiIndex, dpi.nX, dpi.nY);
	}
	else if(byData[0] == 0xaa) // 切換profile
	{
		TCHAR szVersion[1024];
		CmdLock();
	//	GvOrderVersion(szVersion, s_MouseIndex);
		CmdUnLock();
		//if(NULL != m_pParent) ((CGhostDlg*)m_pParent)->LoadProfile(byData[2]);
	}
	else if(byData[0] == 0xBC) // 左滾右滾
	{
		CmdLock();
		DWORD dwThread = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
		::AttachThreadInput(dwThread, ::GetCurrentThreadId(), TRUE);
		HWND hWnd = ::GetFocus();
		::AttachThreadInput(dwThread, ::GetCurrentThreadId(), FALSE);
		while (hWnd != NULL)
		{
			//for (int i = 0; i < s_leftAndRightScroll; i++)
			//{
			//	switch (byData[2])
			//	{
			//	case 1:        // left; scroll left
			//		::SendMessage(hWnd, WM_HSCROLL, SB_LINELEFT, 0);
			//		break;
			//	case 2:        // right; scroll right
			//		::SendMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, 0);
			//		break;
			//	}
			//}
			hWnd = CWnd::FromHandle(hWnd)->GetTopWindow()->GetSafeHwnd();
		}
		TCHAR szVersion[1024];
	//	GvOrderVersion(szVersion, s_MouseIndex);
		CmdUnLock();
	}
	else if(byData[0] == 0xBF)
	{
		CmdLock();
		//AfxMessageBox(_T("Get Ghost Cmd"));
		TCHAR szVersion[1024];
	//	GvOrderVersion(szVersion, s_MouseIndex);
		CmdUnLock();
	}
}

BOOL CMousePointerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)    
	{
		return TRUE;
	}

	return CUiDlg::PreTranslateMessage(pMsg);
}