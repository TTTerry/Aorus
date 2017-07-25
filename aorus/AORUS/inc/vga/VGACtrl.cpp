#include "StdAfx.h"
#include "VGACtrl.h"
#include "afxmt.h"
#include "..\cpu\CPUInfo.h"
#include "..\led\NvApiTemp.h"
#include "..\audio\AudioVolume.h"

CCPUInfo s_cpu;
CIXEB s_DevIXEB;
static CMutex s_Mutex = CMutex(FALSE, _T("I2C_FOR_AORUS_LED_CTRL_GIGABYTE"), NULL);

static void Lock()   { s_Mutex.Lock();   }
static void Unlock() { s_Mutex.Unlock(); }

typedef struct _ONESTEP_OC
{
	CString sModelName;
	int nGpuOCStep;
	int nGpuECOClk;
	int nMemOCStep;
	int nMemECOClk;
	int nOCPower;
	int nECOPower;
	int nGpuOCBoost;
	int nGpuECOBoost;

}ONESTEP_OC, *PONESTEP_OC;

#define ONESTEP_COUNT 134
static ONESTEP_OC s_stOneStepOc[ONESTEP_COUNT] = 
{
	{ _T("GV-N970WF3OC-4GD"), 35, 1051, -1, -1, -1, -1, 35, -1 },
	{ _T("GV-N970G1 GAMING-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N970IXOC-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N970IX-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N970WF3-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },

	{ _T("GV-N980G1 GAMING-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980WF3OC-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980X3WA-4GD-1"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980X3WA-4GD-2"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980X3WA-4GD-3"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980X3WA-4GD-4"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980WF3-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N98TG1 GAMING-6GD"), 38, 1000, -1, -1, -1, -1, 38, -1 },
	{ _T("GV-N98TWF3OC-6GD"), 38, 1000, -1, -1, -1, -1, 38, -1 },

	{ _T("GV-N960IX-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960IXOC-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960G1 GAMING-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960G1 GAMING-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2OC-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2OC-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2CN-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960OC-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960OC-4GD"), 26, 1127, -1, -1, -1, -1, 25, -1 },

	{ _T("GV-N98TXTREME-6GD"), 25, 1000, -1, -1, 110, 90, 25, -1 },
	{ _T("GV-N98TXTREME W-6GD"), 25, 1000, -1, -1, 110, 90, 25, -1 },
	{ _T("GV-N980XTREME-4GD"), 25, 1127, -1, -1, 110, 80, 25, -1 },
	{ _T("GV-N970XTREME-4GD"), 25, 1051, -1, -1, 110, 80, 25, -1 },
	{ _T("GV-NTITANXXTREME-12GD-B"), 25, 1000, -1, -1, 110, 100, 25, -1 },

	{ _T("GV-N950XTREME-2GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950WF2OC-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950OC-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950WF2CN-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950CN-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950XTREME C-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N950D5-2GD"), 25, 1026, -1, -1, -1, -1, 25, -1 },

	{ _T("GV-N970TTOC-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N970TT-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960IXOC-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960WF2-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960D5-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },

	{ _T("GV-N980XTREME C-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980WAOC-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N970XTREME C-4GD"), 25, 1051, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N98TXTREME C-6GD"), 26, 1000, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N98TWF3-6GD"), 26, 1000, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N980OC-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N960XTREME-4GD"), 25, 1127, -1, -1, -1, -1, 25, -1 },

	{ _T("GV-NTITANXD5-12GD-B"), 0, 1000, -1, -1, -1, -1, 0, -1 },
	{ _T("GV-N1070XTREME-8GD"), 50, 1506, 148, 8008, -1, -1, 25, 1683 },
	{ _T("GV-N1060XTREME-6GD"), 50, 1506, 152, 8008, -1, -1, 26, 1683 },
	{ _T("GV-N1070XTREME C-8GD"), 50, 1506, -1, -1, -1, -1, 25, -1 },
	{ _T("GV-N1070G1 GAMING-8GD"), 52, 1506, -1, -1, -1, -1, 38, 1683 },
	{ _T("GV-N1070G1 ROCK-8GD"), 50, 1506, -1, -1, -1, -1, 26, 1683 },
	{ _T("GV-N1080XTREME-8GD-PP"), 50, 1607, 194, 10010 , -1, -1, 38, 1733 },
	{ _T("GV-N1080XTREME-8GD"), 50, 1607, 194, 10010 , -1, -1, 38, 1733 },
	{ _T("GV-N1080AORUS X-8GD"), 50, 1607, 194, 10010 , -1, -1, 38, 1733 },	
	{ _T("GV-N108TAORUS X-11GD"), 50, 1480, 216, 11010 , -1, -1, 25, 1582 },	// Peter Lee 2017/3/29	
	{ _T("GV-N1060AORUS-6GD"), 50, 1506, -1, -1 , -1, -1, 25, 1708 },	// Peter Lee 2017/3/30
	{ _T("GV-N1060XTREME9-6GD"), 50, 1506, -1, -1 , -1, -1, 26, 1708 },	// Peter Lee 2017/3/30
	{ _T("GV-N1060AORUS X-6GD"), 50, 1506, -1, -1 , -1, -1, 26, 1708 },	// Peter Lee 2017/4/18 renamed from	GV-N1060XTREME9-6GD
	{ _T("GV-N1070AORUS-8GD"), 50, 1506, -1, -1 , -1, -1, 38, 1683 },	// Peter Lee 2017/3/30
	{ _T("GV-N1080AORUS-8GD"), 50, 1607, -1, -1 , -1, -1, 26, 1733 },	// Peter Lee 2017/3/30
	{ _T("GV-N1080AORUS X11-8GD"), 50, 1607, -1, -1 , -1, -1, 38, 1733 },	// Peter Lee 2017/3/30
	{ _T("GV-N108TAORUS-11GD"), 50, 1480, -1, -1 , -1, -1, 25, 1582 },	// Peter Lee 2017/3/30
	{ _T("GV-N108TGAMING OC-11GD"), 52, 1480, -1, -1 , -1, -1, 25, 1582 },	// Peter Lee 2017/3/30
	{ _T("GV-N1030D5-2GL"), 50, 1227, -1, -1 , -1, -1, 38, 1468 },	// Peter Lee 2017/4/18
	{ _T("GV-N108TGAMING-11GD"), 52, 1480, -1, -1 , -1, -1, 38, 1582 },	// Peter Lee 2017/4/25
	{ _T("GV-N1030SL-2GL"), 50, 1227, -1, -1 , -1, -1, 38, 1468 },	// Peter Lee 2017/4/26
	{ _T("GV-N1030OC-2GI"), 50, 1227, -1, -1, -1, -1, 26, 1468 },	// Peter Lee 2017/5/4
	{ _T("GV-N108TTURBO-11GD"), 46, 1480, -1, -1, -1, -1, 38, 1582 },	// Peter Lee 2017/6/1
	{ _T("GV-N1070IXEB-8GD"), 50, 1507, -1, -1, -1, -1, 25, 1683 },	// Peter Lee 2017/6/2, this is a virtual device, all setting same with GV-N1070IXOC-8GD
	{ _T("GV-N108TAORUSX W-11GD"), 50, 1480, 216, 11010, -1, -1, 25, 1582 },	// Peter Lee 2017/6/7
	{ _T("GV-N108TAORUSX WB-11GD"), 50, 1480, 216, 11010, -1, -1, 25, 1582 },	// Peter Lee 2017/6/7
	{ _T("GV-N108TGAMINGOC BLACK-11GD"), 52, 1480, -1, -1 , -1, -1, 25, 1582 },	// Peter Lee 2017/6/16
	
	{ _T("GV-N1080XTREME W-8GD"), 50, 1607, 194, 10010, -1, -1, 38, 1733 },
	{ _T("GV-N1080XTREME C-8GD"), 50, 1607, -1, -1, -1, -1, 38, 1733 },
	{ _T("GV-N1080G1 GAMING-8GD"), 52, 1607, -1, -1, -1, -1, 25, 1733 },	
	{ _T("GV-N1070WF2OC-8GD"), 52, 1506, -1, -1, -1, -1, 25, 1683 },
	{ _T("GV-N1070WF2-8GD"), 52, 1506, -1, -1, -1, -1, 25, 1683 },
	{ _T("GV-N1060G1 GAMING-6GD"), 52, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060G1 GAMING-3GD"), 52, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060G1 ROCK-6GD"), 50, 1506, -1, -1, -1, -1, 25, 1708 },
	{ _T("GV-N1060IXOC-6GD"), 50, 1506, -1, -1, -1, -1, 25, 1708 },
	{ _T("GV-N1060D5-6GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060D5-3GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1080G1 ROCK-8GD"), 50, 1607, -1, -1, -1, -1, 26, 1733 },
	{ _T("GV-N1080WF3OC-8GD"), 50, 1607, -1, -1, -1, -1, 26, 1733 },
	{ _T("GV-N1070IXOC-8GD"), 50, 1507, -1, -1, -1, -1, 25, 1683 },
	{ _T("GV-N1070IX-8GD"), 50, 1506, -1, -1, -1, -1, 38, 1683 },
	{ _T("GV-N1060IXOC-3GD"), 50, 1506, -1, -1, -1, -1, 25, 1708 },
	{ _T("GV-N1060IX-6GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060IX-3GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060WF2CN-6GD"), 50, 1506, -1, -1, -1, -1, 25, 1708 },
	{ _T("GV-N1060WF2OC-3GD"), 52, 1506, -1, -1, -1, -1, 26, 1708 },
	{ _T("GV-N1060WF2CN-3GD"), 50, 1506, -1, -1, -1, -1, 25, 1708 },
	{ _T("GV-N1060WF2OC-6GD"), 52, 1506, -1, -1, -1, -1, 26, 1708 },
	{ _T("GV-N1060WF2-3GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1060WF2-6GD"), 50, 1506, -1, -1, -1, -1, 38, 1708 },
	{ _T("GV-N1080TTOC-8GD"), 50, 1607, -1, -1, -1, -1, 26, 1733 },
	{ _T("GV-N1060XTREME-3GD"), 50, 1506, 152, 8008, -1, -1, 26, -1 },
	{ _T("GV-N1080XTREME WB-8GD"), 50, 1607, -1, -1, -1, -1, 38, 1733 },
	{ _T("GV-N105TD5-4GD"), 52, 1291, -1, -1, -1, -1, 38, 1392 },
	{ _T("GV-N105TOC-4GD"), 50, 1290, -1, -1, -1, -1, 25, 1392 },
	{ _T("GV-N105TCN-4GD"), 50, 1290, -1, -1, -1, -1, 25, 1392 },
	{ _T("GV-N105TG1 GAMING-4GD"), 52, 1290, -1, -1, -1, -1, 26, 1392 },
	{ _T("GV-N105TWF2OC-4GD"), 52, 1290, -1, -1, -1, -1, 26, 1392 },
	{ _T("GV-N1050G1 GAMING-2GD"), 50, 1354, -1, -1, -1, -1, 25, 1455 },
	{ _T("GV-N1050WF2OC-2GD"), 50, 1354, -1, -1, -1, -1, 25, 1455 },
	{ _T("GV-N1050D5-2GD"), 50, 1354, -1, -1, -1, -1, 38, 1455 },
	{ _T("GV-N1050OC-2GD"), 50, 1354, -1, -1, -1, -1, 25, 1455 },
	{ _T("GV-N1050CN-2GD"), 50, 1354, -1, -1, -1, -1, 25, 1455 },
	{ _T("GV-N1080D5X-8GD"), 50, 1607, -1, -1, -1, -1, 38, 1733 },
	{ _T("GV-N1050WF2-2GD"), 76, 1354, -1, -1, -1, -1, 51, 1455 },
	{ _T("GV-N105TWF2-4GD"), 52, 1354, -1, -1, -1, -1, 38, 1455 },
	{ _T("GV-N1050OC-2GL"), 52, 1354, -1, -1, -1, -1, 38, 1455 },
	{ _T("GV-N1060AORUS-8GD"), 50, 1506, -1, -1 , -1, -1, 25, 1708 },
	{ _T("GV-N105TOC-4GL"), 50, 1290, -1, -1, -1, -1, 25, 1392 },	// Peter Lee 2017/6/5
	{ _T("GV-N1050-2GL"), 50, 1354, -1, -1, -1, -1, 38, 1455 },		// Peter Lee 2017/6/5

	// Peter Lee 2017/4/20 RX4 no longer support on step OC
	/*{ _T("GV-RX460WF2OC-2GD"), 1236, 1200, -1, -1, -1, -1, 24, -1 }, 
	{ _T("GV-RX460WF2OC-4GD"), 1236, 1200, -1, -1, -1, -1, 24, -1 }, 
	{ _T("GV-RX480G1 GAMING-4GD"), 1309, 1266, -1, -1, -1, -1, 24, -1 }, 
	{ _T("GV-RX470G1 GAMING-4GD"), 1255, 1206, -1, -1, -1, -1, 25, -1 }, 
	{ _T("GV-RX470WF2-4GD"), 1230, 1266, -1, -1, -1, -1, 24, -1 }, 
	{ _T("GV-RX480WF2-4"), 1291, 1206, -1, -1, -1, -1, 25, -1 }, 
	{ _T("GV-RX480WF2-8GD"), 1291, 1206, -1, -1, -1, -1, 25, -1 }, */

	{ _T("GV-RX550D5-2GD"), 1195, 1183, -1, -1, -1, -1, 1195, 1183 },	// Peter Lee 2017/3/30
	{ _T("GV-RX550GAMING OC-2GD"), 1219, 1183, -1, -1, -1, -1, 1219, 1183 },	// Peter Lee 2017/3/30
	{ _T("GV-RX570AORUS-4GD"), 1295, 1244, -1, -1, -1, -1, 1295, 1244 },	// Peter Lee 2017/3/30
	{ _T("GV-RX570GAMING-4GD"), 1255, 1244, -1, -1, -1, -1, 1255, 1244 },	// Peter Lee 2017/3/30
	{ _T("GV-RX580AORUS-4GD"), 1380, 1340, -1, -1, -1, -1, 1380, 1340 },	// Peter Lee 2017/4/7
	{ _T("GV-RX580GAMING-4GD"), 1355, 1340, -1, -1, -1, -1, 1355, 1340 },	// Peter Lee 2017/4/7
	{ _T("GV-RX580AORUS-8GD"), 1380, 1340, -1, -1, -1, -1, 1380, 1340 },	// Peter Lee 2017/4/7
	{ _T("GV-RX580GAMING-8GD"), 1355, 1340, -1, -1, -1, -1, 1355, 1340 },	// Peter Lee 2017/4/7
	{ _T("GV-RX580XTRAORUS-8GD"), 1439, 1411, -1, -1, -1, -1, 1439, 1411 },	// Peter Lee 2017/3/30
	{ _T("GV-RX560GAMING OC-4GD"), 1300, 1275, -1, -1, -1, -1, 1300, 1275 },	// Peter Lee 2017/4/25
	{ _T("GV-RX560GAMING OC-2GD"), 1300, 1275, -1, -1, -1, -1, 1300, 1275 },	// Peter Lee 2017/4/25
	{ _T("GV-RX560OC-2GD"), 1199, 1176, -1, -1, -1, -1, 1199, 1176 },	// Peter Lee 2017/6/16
	{ _T("GV-RX560OC-4GD"), 1199, 1176, -1, -1, -1, -1, 1199, 1176 },	// Peter Lee 2017/6/16
	{ _T("GV-RX560GAMING OC-4GD 2.0"), 1234, 1176, -1, -1, -1, -1, 1234, 1176 },	// Peter Lee 2017/6/16
};


CVGACtrl::CVGACtrl(void)
{
	m_sCardIds = _T("");
	m_sLogPath = _T("");
	m_nNumOfCards = -1;
	m_nNumPerfLs = -1;
	m_bLightCard = false;
	m_nOneStepIndex = -1;
	m_hWnd = NULL;
	m_pLogFile = NULL;	
	m_bIXEB = false;
}

CVGACtrl::~CVGACtrl(void)
{
}

bool CVGACtrl::Initialize(const HWND& hWnd)
{
	#ifdef _DEBUG
	BOOL bUnicode = FALSE;
	#ifdef UNICODE
	bUnicode = TRUE;
	#endif

	BOOL bUnicodeDll = GvIsAutoUpdateUnicode();
	if((bUnicode && !bUnicodeDll) || (!bUnicode && bUnicodeDll))
	{
		AfxMessageBox(_T("EXE & DLL are NOT both UNICODE!"));
	}
	#endif

	CString sMemSize = _T("");
	CString sId[4];
	BOOL bIdsSuccessful = FALSE;
	GVDISP_VGA_INFO vgaInfo  = {0};

	m_hWnd = hWnd;
	m_cardInfo.nCardType = VGA_CARD_UNKNOWN;
	if(GVAPI_OK != GvInitDispLib())
		return true;

	BOOL bNewNvCard = FALSE;
	BOOL bBoost2Card = FALSE;
	BOOL bBoost3Card = FALSE;

	GvIsNvNewSeries(bNewNvCard);  // Nvidia card after N680 (include N680)
	GvIsNvBoost2(bBoost2Card);    // Nvidia card after N760 (include N760)
	GvIsNvBoost3(bBoost3Card);    // Nvidia card after N980 (include N980)

	if(m_cardInfo.sModelName.IsEmpty())
	{
		VGA_BIOS_INFO biosInfo = {0};
		if (GVAPI_OK == GvInitBiosLib() && 
		    GVAPI_OK == GvReadBiosInfoFromAdapter(0, &biosInfo))
		{
			CString sBiosVer   = biosInfo.szBiosVer; 
			CString sModelName = biosInfo.szModelName;
			m_cardInfo.sModelName = sModelName;
			m_cardInfo.sBiosVer   = sBiosVer;

			if(sModelName == _T("GV-N1080XTREME-8GD-PP")) m_cardInfo.sModelName = _T("GV-N1080XTREME-8GD");
			for (int i = 0; i < ONESTEP_COUNT; i++)
			{
				if (m_cardInfo.sModelName.MakeUpper().Find(s_stOneStepOc[i].sModelName) >= 0)
				{
					m_nOneStepIndex = i;
				}
			}
			// Peter Lee 2017/4/19 for GV-N108TAORUS-11GD & GV-N108TAORUS X-11GD
			// F3 TGP = 300W, F4 TGP = 250W; both OC mode want set power to 300W
			// F3: OC power target = 100%, F4: OC power target = 120%, 
			if((sModelName == _T("GV-N108TAORUS X-11GD") || sModelName == _T("GV-N108TAORUS-11GD")) && sBiosVer == _T("F4"))
			{
				s_stOneStepOc[m_nOneStepIndex].nOCPower = 120;
			}
		}
		GvFreeBiosLib();
	}

	if(GVAPI_OK == GvGetVgaInfo(&vgaInfo))
	{
        m_nNumOfCards = vgaInfo.nNumCards;

		CString sDriverVer  = vgaInfo.szDrvVersions[0];
		CString sDriverDate = vgaInfo.szDrvDates[0];
		CString sDevDesc    = vgaInfo.szDevDescs[0];

		sId[0].Format(_T("%04X"), vgaInfo.wVIDs[0]);
		sId[1].Format(_T("%04X"), vgaInfo.wDIDs[0]);
		sId[2].Format(_T("%04X"), vgaInfo.wSSIDs[0]);
		sId[3].Format(_T("%04X"), vgaInfo.wSVIDs[0]);

		m_cardInfo.sVid		   = sId[0];
		m_cardInfo.sDid		   = sId[1];
		m_cardInfo.sSsid	   = sId[2];
		m_cardInfo.sSvid	   = sId[3];
		m_cardInfo.sDriverVer  = sDriverVer;
		m_cardInfo.sDriverDate = sDriverDate;
		m_cardInfo.sDevDesc    = sDevDesc;

		bIdsSuccessful = TRUE;
		m_sCardIds = sId[0] + _T("_") + sId[1] + _T("_") + sId[2] + _T("_") + sId[3];

		if(0x1002 == vgaInfo.wVIDs[0])
		{
			m_cardInfo.nCardType = VGA_CARD_AMD;
		}
		if(0x10DE == vgaInfo.wVIDs[0])
		{
			m_cardInfo.nCardType = VGA_CARD_NV;
		}

		if (VGA_CARD_NV == m_cardInfo.nCardType)
		{
				if(vgaInfo.wSSIDs[0] == 0x36FD	// GV-N1080XTREME-8GD-1.0 DP3
				|| vgaInfo.wSSIDs[0] == 0x36FE	// GV-N1080XTREME-8GD-1.0 HDMI3
				|| vgaInfo.wSSIDs[0] == 0x3700	// GV-N106TXTREME-8GD 1.0
				|| vgaInfo.wSSIDs[0] == 0x3701	// GV-N1070G1 GAMING-8GD
				|| vgaInfo.wSSIDs[0] == 0x3702	// GV-N1080G1 GAMING-8GD
				|| vgaInfo.wSSIDs[0] == 0x3706	// GV-N1070XTREME-8GD 1.0 
				|| vgaInfo.wSSIDs[0] == 0x3707	// GV-N1070XTREME-8GD 1.0 
				|| vgaInfo.wSSIDs[0] == 0x3708	// GV-N1070XTREME-8GD 2.0 
				|| vgaInfo.wSSIDs[0] == 0x3709	// GV-N1070XTREME-8GD 2.0 
				|| vgaInfo.wSSIDs[0] == 0x370A	// GV-N1070XTREME-8GD 3.0
				|| vgaInfo.wSSIDs[0] == 0x370E	// GV-N1080XTREME W-8GD 1.0 DP x 3
				|| vgaInfo.wSSIDs[0] == 0x3710	// GV-N1080XTREME-8GD -2.0 DP x3
				|| vgaInfo.wSSIDs[0] == 0x3711	// GV-N1080XTREME-8GD -2.0 HDMI x3           
				|| vgaInfo.wSSIDs[0] == 0x3712	// GV-N1080XTREME W-8GD -2.0 DP x3                      
				|| vgaInfo.wSSIDs[0] == 0x3713	// GV-N1080XTREME W-8GD -2.0 HDMI x3                            
				|| vgaInfo.wSSIDs[0] == 0x3716	// GV-N1060G1 GAMING-6GD 1.0	                          
				|| vgaInfo.wSSIDs[0] == 0x3719	// GV-N1060G1 GAMING-6GD JD 1.0	                          
				|| vgaInfo.wSSIDs[0] == 0x3720	// GV-N1060D5-6GD 1.0 Peter Lee 2017/6/5
				|| vgaInfo.wSSIDs[0] == 0x3741	// GV-N1060D5-6GD 2.0 Peter Lee 2017/6/5
				|| vgaInfo.wSSIDs[0] == 0x3721	// GV-N1060G1 GAMING-3GD 1.0	                          
				|| vgaInfo.wSSIDs[0] == 0x371C  // GV-N1060XTREME-6GD 1.0 DP X 3
				|| vgaInfo.wSSIDs[0] == 0x371D	// GV-N1060XTREME-6GD 1.0 HDMI X 3
				|| vgaInfo.wSSIDs[0] == 0x371E	// GV-N1060XTREME-3GD 1.0 DP X 3
				|| vgaInfo.wSSIDs[0] == 0x371F	// GV-N1060XTREME-3GD 1.0 HDMI X 3                         
				|| vgaInfo.wSSIDs[0] == 0x370F	// GV-N1080XTREME W-8GD 1.0 HDMI x 3
				|| vgaInfo.wSSIDs[0] == 0x371C	// GV-N1060XTREME-6GD 1.0 DP X 3
				|| vgaInfo.wSSIDs[0] == 0x371D	// GV-N1060XTREME-6GD 1.0 HDMI X 3
				|| vgaInfo.wSSIDs[0] == 0x371E	// GV-N1060XTREME-3GD 1.0 DP X 3
				|| vgaInfo.wSSIDs[0] == 0x371F	// GV-N1060XTREME-3GD 1.0 HDMI X 3
				|| vgaInfo.wSSIDs[0] == 0x3720	// GV-N1060D5-6GD 1.0 HDMI X 3
				|| vgaInfo.wSSIDs[0] == 0x372A	// GV-N1050G1 GAMING-4GD
				|| vgaInfo.wSSIDs[0] == 0x372F  // GV-N1080XTREME WB-8GD 1.0 DP
				|| vgaInfo.wSSIDs[0] == 0x3738	// GV-N1080XTREME WB-8GD 1.0 HDMI
				|| vgaInfo.wSSIDs[0] == 0x372A	// GV-N1050XTREME
				|| vgaInfo.wSSIDs[0] == 0x3731	// GV-N1060D5-3GD 1.0 Peter Lee 2017/6/5
				|| vgaInfo.wSSIDs[0] == 0x3742	// GV-N1060D5-3GD 2.0 Peter Lee 2017/6/5
				|| vgaInfo.wSSIDs[0] == 0x3739	// GV-N1060XTREME-6GD 2.0
				|| vgaInfo.wSSIDs[0] == 0x373A	// GV-N1060XTREME-3GD 2.0
				|| vgaInfo.wSSIDs[0] == 0x372A	// GV-N105TG1 GAMING-4GD 1.0
				|| vgaInfo.wSSIDs[0] == 0x372B	// GV-N1050G1 GAMING-2GD 1.0
				|| vgaInfo.wSSIDs[0] == 0x3739	// GV-N1060G1 GAMING-6GD 2.0
				|| vgaInfo.wSSIDs[0] == 0x373A	// GV-N1060G1 GAMING-3GD 2.0
				|| vgaInfo.wSSIDs[0] == 0x3748	// GV-N1080AORUS X-8GD 1.0
				|| vgaInfo.wSSIDs[0] == 0x3757  // GV-N1060AORUS X-6GD 1.0 DP
				|| vgaInfo.wSSIDs[0] == 0x3758	// GV-N1060AORUS X-6GD 1.0 HDMI
			) {
				m_bLightCard = TRUE;					
			}
		}
		else if (vgaInfo.wVIDs[0] == 0x1002)
		{
			if(vgaInfo.wSSIDs[0] == 0x22D0	// GV-RX480G1 GAMING-8GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22D4	// GV-RX480G1 GAMING-4GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22D7	// GV-RX470G1 GAMING-4GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22DF	// GV-RX480WF2-8GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22E0	// GV-RX480WF2-4GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22E1	// GV-RX470WF2-4GD 1.0
			|| vgaInfo.wSSIDs[0] == 0x22E7	// GV-RX480G1 GAMING-8GD 1.1
			|| vgaInfo.wSSIDs[0] == 0x22E8	// GV-RX480G1 GAMING-4GD 1.1
			|| vgaInfo.wSSIDs[0] == 0x22E9	// GV-RX470G1 GAMING-4GD 1.1
			|| vgaInfo.wSSIDs[0] == 0x22F0	// GV-RX570AORUS-4GD 1.0
			) {
				m_bLightCard = TRUE;					
			}
		}

		m_bLightCard = m_bLightCard || CVGALed::GetVersion() > 1.0;

		// Peter Lee 2017/6/7 Special case for GV-N108TTURBO-11GD
		// this model has no led control but first mp 1.5K mount M0 MCU
		// SW detected MCU ic, need to skip
		if (VGA_CARD_NV == m_cardInfo.nCardType && vgaInfo.wSSIDs[0] == 0x376B)
			m_bLightCard = FALSE;

		sMemSize.Format(_T("%d MB"), vgaInfo.nMemorySizes[0]);
		m_cardInfo.sMemSize = sMemSize;

		GVDISP_CLOCK_INFO clkInfo = {0};
		if(GVAPI_OK == GvGetPerfClockInfo(0, GVDISP_CLOCK_DOMAIN_ID_GPU, &clkInfo))
		{
			m_nNumPerfLs = clkInfo.nNumPerfLs;
		}

		m_nNumPerfLs = (m_nNumPerfLs <= 0) ? 1 : m_nNumPerfLs;	

		GetCurClockCurve(&m_GpuBaseVfs);
		for (int i = 0; i < m_BaseOffsets.nNumVFPoints; i++)
		{
			GvGetVfClockSet(0, m_BaseOffsets.offset[i].nIndex, m_BaseOffsets.offset[i].nOffset);
		}
	}

#ifdef _DEBUG
	//m_nNumOfCards = 2;
	//m_cardInfo.nCardType = VGA_CARD_NV;
	//m_cardInfo.sModelName = _T("GV-N1060AORUS X-6GD");
	//m_bLightCard = true;
#endif

	// check IXEB (external VGA)

	// marketing asked: 
	// if only GV-N1070IXOC-8GD here: don't show led icon.
	// if GV-N1070IXOC-8GD & IXEB here: hide VGA device icon, and only show IXEB device icon.

	if (m_cardInfo.sSsid == _T("36FC") && m_cardInfo.sModelName != _T("GV-N1070IXOC-8GD"))
	{
		m_cardInfo.sModelName = _T("GV-N1070IXEB-8GD");
		m_bIXEB = s_DevIXEB.OnConnect();
		m_bLightCard = m_bIXEB ? true : false;
		for (int i = 0; i < ONESTEP_COUNT; i++)
		{
			if (m_cardInfo.sModelName.MakeUpper().Find(s_stOneStepOc[i].sModelName) >= 0)
			{
				m_nOneStepIndex = i;
			}
		}
	}

	return true;
}

bool CVGACtrl::IsVgaCard()
{
	return m_cardInfo.nCardType != VGA_CARD_UNKNOWN;
}

bool CVGACtrl::IsLedCard()
{
	return m_bLightCard;
}

bool CVGACtrl::IsNvCard()
{
	return m_cardInfo.nCardType == VGA_CARD_NV;
}

bool CVGACtrl::IsSwUpdate()
{
	AUDT_FILEVERSION version = {0};
	TCHAR szModule[MAX_PATH] = {0};
	int nLen = MAX_PATH;
	GetModuleFileName(NULL, szModule, sizeof(szModule));
	if(GvGetModuleVersion(szModule, FALSE, &version))
	{
		ZeroMemory(szModule, MAX_PATH);
		GvCheckUtiUpdate(AUDT_UTILITY_AORUS, version, szModule, nLen);
		return _tcslen(szModule) > 0;
	}
	return false;
}

bool CVGACtrl::IsNvSli()
{
#ifdef _DEBUG
	//return true;
#endif
	BOOL bSli = FALSE;
	GvIsNvSLI(bSli);
	return (bSli == TRUE) ? true : false;
}

const VGA_CARD_INFO* CVGACtrl::GetCardInfo()
{
	return &m_cardInfo;
}

int CVGACtrl::GetGpuCount()
{
	return m_nNumOfCards;
}

// 2017/5/20 Peter Lee , fix bug move up static param from function param to local param
// issue desc: check led sync, gaming mode gpu clock same to eco gpu clock
static DWORD s_dwPerfs = 0;
static VGA_PARAM_RANGE	s_GpuClkR;
static VGA_PARAM_RANGE	s_MemClkR;
static VGA_PARAM_RANGE	s_GpuVolR;
static VGA_PARAM_RANGE	s_MaxVolR;
static VGA_PARAM_RANGE	s_MemVolR;
static VGA_PARAM_RANGE	s_PowerR;
static VGA_PARAM_RANGE	s_TempR;
static VGA_PARAM_RANGE	s_FanSpdR;

void CVGACtrl::GetPerfInfo(int nPerf, VGA_PARAM_RANGE& range)
{
	if(IsNvCard())
	{
		if(VGA_PERF_MEMVOL == nPerf)
		{
			return;	// Ingored.
		}
	}

	// 2017/5/20 Peter Lee , fix bug move up static param from function param to local param
	// issue desc: check led sync, gaming mode gpu clock same to eco gpu clock
	/*static DWORD s_dwPerfs = 0;
	static VGA_PARAM_RANGE	s_GpuClkR;
	static VGA_PARAM_RANGE	s_MemClkR;
	static VGA_PARAM_RANGE	s_GpuVolR;
	static VGA_PARAM_RANGE	s_MaxVolR;
	static VGA_PARAM_RANGE	s_MemVolR;
	static VGA_PARAM_RANGE	s_PowerR;
	static VGA_PARAM_RANGE	s_TempR;
	static VGA_PARAM_RANGE	s_FanSpdR;*/

	if(s_dwPerfs & nPerf)
	{
		switch(nPerf)
		{
		case VGA_PERF_GPUCLK:	range = s_GpuClkR;	return;
		case VGA_PERF_MEMCLK:	range = s_MemClkR;	return;
		case VGA_PERF_GPUVOL:	range = s_GpuVolR;	return;
		case VGA_PERF_OVERVOL:	range = s_MaxVolR;	return;
		case VGA_PERF_MEMVOL:	range = s_MemVolR;	return;
		case VGA_PERF_POWER:	range = s_PowerR;	return;
		case VGA_PERF_TEMPER:	range = s_TempR;	return;
		case VGA_PERF_FANSPD:	range = s_FanSpdR;	return;
		}
	}

	s_dwPerfs |= nPerf;

	switch(nPerf)
	{
	case VGA_PERF_GPUCLK:{
			GVDISP_CLOCK_INFO clkInfo = {0};
			if(GVAPI_OK == GvGetPerfClockInfo(0, GVDISP_CLOCK_DOMAIN_ID_GPU, &clkInfo))
			{
				s_GpuClkR.nMax  = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nMax;	// P0-state
				s_GpuClkR.nMin  = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nMin;
				s_GpuClkR.nStep = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nStep;

				if(!IsNvCard()) s_GpuClkR.nStep = 1;

				if (m_nOneStepIndex >= 0)
				{
					VGA_SPECIALPERFS specialPerf;
					VGA_PARAM_RANGE  range;
					GetSpecialPerformaces(specialPerf);
					int nStep = s_stOneStepOc[m_nOneStepIndex].nGpuECOClk - specialPerf.nGpuBaseClk;
					s_GpuClkR.nMax = nStep * 2 + 2000;
				}

				range = s_GpuClkR;
			}
			break;
		}
	case VGA_PERF_MEMCLK:{	
			GVDISP_CLOCK_INFO clkInfo = {0};
			if(GVAPI_OK == GvGetPerfClockInfo(0, GVDISP_CLOCK_DOMAIN_ID_MEMORY, &clkInfo))
			{
				s_MemClkR.nMax  = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nMax;	// P0-state
				s_MemClkR.nMin  = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nMin;
				s_MemClkR.nStep = clkInfo.stRanges[clkInfo.nNumPerfLs - 1].nStep;

				if(!IsNvCard()) s_MemClkR.nStep = 1;

				GVDISP_RAM_TYPE type;
				if(GVAPI_OK == GvGetRamType(0, type))
				{
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
					{
						s_MemClkR.nMax  *= 2;
						s_MemClkR.nMin  *= 2;
						s_MemClkR.nStep *= 2;
					}
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
					{
						s_MemClkR.nMax  *= 2;
						s_MemClkR.nMin  *= 2;
						s_MemClkR.nStep *= 2;
					}
					if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
					{
						s_MemClkR.nMax  *= 2;
						s_MemClkR.nMin  *= 2;
						s_MemClkR.nStep *= 2;
					}
					if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
					{
						s_MemClkR.nMax  *= 4;
						s_MemClkR.nMin  *= 4;
						s_MemClkR.nStep *= 4;
					}
				}

				range = s_MemClkR;
			}
			break;
		}
	case  VGA_PERF_OVERVOL:{
			GVDISP_PARAM_RANGE stRange = {0};
			if (GVAPI_OK == GvGetPerfOVoltageInfo(0, &stRange))
			{
				s_MaxVolR.nMax  = stRange.nMax;
				s_MaxVolR.nMin  = stRange.nMin;
				s_MaxVolR.nStep = stRange.nStep;
				range = s_MaxVolR;
			}
			break;
		}
	case VGA_PERF_GPUVOL:{
			GVDISP_VOLTAGE_INFO info = {0};
			if(GVAPI_OK == GvGetPerfVoltageInfo(0, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &info, GVDISP_CTRL_MODE_FIRMWARE) || GVAPI_OK == GvGetPerfVoltageInfo(0, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &info))
			{
				s_GpuVolR.nMax  = info.stRange.nMax;
				s_GpuVolR.nMin  = info.stRange.nMin;
				s_GpuVolR.nStep = info.stRange.nStep;

				// ONLY FOR N680SO
				if(m_sCardIds == _T("10DE_1180_353D_1458") || 
					m_sCardIds == _T("10DE_1180_354D_1458"))
				{
					VGA_SPECIALPERFS specialPerf;
					if(GetSpecialPerformaces(specialPerf))
					{
						if(specialPerf.nGpuBaseVol + s_GpuVolR.nMin > 1175000) // 1.175 V
						{
							s_GpuVolR.nMin = 1175000 - specialPerf.nGpuBaseVol;
						}

						if(specialPerf.nGpuBaseVol + s_GpuVolR.nMax > 1175000) // 1.175 V
						{
							s_GpuVolR.nMax = 1175000 - specialPerf.nGpuBaseVol;
						}
					}
				}

				range = s_GpuVolR;
			}
			break;
		}

	case VGA_PERF_MEMVOL:{
			GVDISP_VOLTAGE_INFO info = {0};
			if(GVAPI_OK == GvGetPerfVoltageInfo(0, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, &info, GVDISP_CTRL_MODE_FIRMWARE))
			{
				s_MemVolR.nMax  = info.stRange.nMax;
				s_MemVolR.nMin  = info.stRange.nMin;
				s_MemVolR.nStep = info.stRange.nStep;
				range = s_MemVolR;
			}
			break;
		}
	case VGA_PERF_POWER:{
			GVDISP_POWER_INFO info = {0};
			if(GVAPI_OK == GvGetPowerInfo(0, &info))
			{
				s_PowerR.nMax  = info.stRange.nMax;
				s_PowerR.nMin  = info.stRange.nMin;
				s_PowerR.nStep = info.stRange.nStep;
				range = s_PowerR;
			}
			break;
		}
	case VGA_PERF_TEMPER:{
			GVDISP_TEMP_INFO info = {0};
			if(GVAPI_OK == GvGetTempInfo(0, &info))
			{
				s_TempR.nMax  = info.stRange.nMax;
				s_TempR.nMin  = info.stRange.nMin;
				s_TempR.nStep = info.stRange.nStep;
				range = s_TempR;
			}
			break;
		}
	case VGA_PERF_FANSPD:{
			GVDISP_FANSPEED_INFO info = {0};
			if(GVAPI_OK == GvGetFanSpeedInfo(0, GVDISP_FANSPD_TYPE_PERCENT, &info))
			{
				s_FanSpdR.nMax  = info.stRange.nMax;
				s_FanSpdR.nMin  = info.stRange.nMin;
				s_FanSpdR.nStep = info.stRange.nStep;
				range = s_FanSpdR;

				FAN_SETTING setting;
				GetFanAutoSetting(setting);
				s_FanSpdR.nMin = setting.curve[0].nFanSpeed;
			}
			break;
		}
	}
}

void CVGACtrl::GetCurrentPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perfs)
{
	nCard = nCard % GetGpuCount();
	if(dwPerfs & VGA_PERF_GPUCLK)		GetCurrentPerformance(VGA_PERF_GPUCLK,		&perfs.nGpuClk, nCard);
	if(dwPerfs & VGA_PERF_MEMCLK)		GetCurrentPerformance(VGA_PERF_MEMCLK,		&perfs.nMemClk, nCard);
	if(dwPerfs & VGA_PERF_GPUVOL)		GetCurrentPerformance(VGA_PERF_GPUVOL,		&perfs.nGpuVol, nCard);
	if(dwPerfs & VGA_PERF_MEMVOL)		GetCurrentPerformance(VGA_PERF_MEMVOL,		&perfs.nMemVol, nCard);
	if(dwPerfs & VGA_PERF_POWER)		GetCurrentPerformance(VGA_PERF_POWER,		&perfs.nPower, nCard);
	if(dwPerfs & VGA_PERF_FANSPD)		GetCurrentPerformance(VGA_PERF_FANSPD,		&perfs.nFanSpd, nCard);
	if(dwPerfs & VGA_PERF_FANRPM)		GetCurrentPerformance(VGA_PERF_FANRPM,		&perfs.nFanRPM, nCard);
	if(dwPerfs & VGA_PERF_TEMPER)		GetCurrentPerformance(VGA_PERF_TEMPER,		&perfs.nTemperature, nCard);
	if(dwPerfs & VGA_PERF_GPUSAGE)		GetCurrentPerformance(VGA_PERF_GPUSAGE,	&perfs.nGPUsage, nCard);
}

void CVGACtrl::GetCurrentMBInfo(DWORD dwPerfs, VGA_MB_INFO& perfs)
{
	static TKTime upTime;
	if(dwPerfs & VGA_PERF_CPUSAGE)		{ s_cpu.GetUsage(&perfs.nCPUsage, &upTime);}
	//if(dwPerfs & VGA_PERF_CPUCLK)		{perfs.fCPUClk = s_cpu.GetCPUClock();}
	if(dwPerfs & VGA_PERF_MEMUSAGE || dwPerfs & VGA_PERF_PAGEFILE)
	{
		MEMORY_ACTIVITY Info;
		s_cpu.GetMemoryUsage(&Info);
		perfs.nMemUsage = Info.iMemUsage;
		perfs.fPageUsage = (Info.iTotalPage - Info.iFreePage) * 1.0 / Info.iTotalPage;
	}
}

void CVGACtrl::GetPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perfs)
{
	nCard = nCard % GetGpuCount();
	// Get user setting value.
	if(dwPerfs & VGA_PERF_GPUCLK)	GetPerformance(VGA_PERF_GPUCLK, &perfs.nGpuClk, nCard);
	if(dwPerfs & VGA_PERF_MEMCLK)	GetPerformance(VGA_PERF_MEMCLK, &perfs.nMemClk, nCard);
	if(dwPerfs & VGA_PERF_GPUVOL)	GetPerformance(VGA_PERF_GPUVOL, &perfs.nGpuVol, nCard);
	if(dwPerfs & VGA_PERF_MEMVOL)	GetPerformance(VGA_PERF_MEMVOL, &perfs.nMemVol, nCard);
	if(dwPerfs & VGA_PERF_POWER)	GetPerformance(VGA_PERF_POWER,	&perfs.nPower,  nCard);
	if(dwPerfs & VGA_PERF_TEMPER)	GetPerformance(VGA_PERF_TEMPER, &perfs.nTemperature, nCard);
	if(dwPerfs & VGA_PERF_FANSPD)	
	{
		// DON'T get fan speed back. It will not be apply immediately.
		if(VGA_FANMODE_AUTO == perfs.nFanMode)
		{
			GetPerformance(VGA_PERF_FANSPD, &perfs.nFanSpd, nCard);
		}
	}
}

void CVGACtrl::SetPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perf)
{
	nCard = nCard % GetGpuCount();
	if(dwPerfs & VGA_PERF_GPUCLK)	SetPerformance(VGA_PERF_GPUCLK, nCard, &perf.nGpuClk);
	if(dwPerfs & VGA_PERF_MEMCLK)	SetPerformance(VGA_PERF_MEMCLK, nCard, &perf.nMemClk);
	if(dwPerfs & VGA_PERF_GPUVOL)	SetPerformance(VGA_PERF_GPUVOL, nCard, &perf.nGpuVol);
	//if(dwPerfs & VGA_PERF_MAXVOL)	SetPerformance(VGA_PERF_MAXVOL, nCard, &perf.nMaxVol);
	if(dwPerfs & VGA_PERF_MEMVOL)	SetPerformance(VGA_PERF_MEMVOL, nCard, &perf.nMemVol);
	if(dwPerfs & VGA_PERF_POWER)	SetPerformance(VGA_PERF_POWER,  nCard,	&perf.nPower);
	if(dwPerfs & VGA_PERF_TEMPER)	SetPerformance(VGA_PERF_TEMPER, nCard, &perf.nTemperature, &perf.bTempPowerLink);
	if(dwPerfs & VGA_PERF_FANSPD)
	{
		switch(perf.nFanMode)
		{
		case VGA_FANMODE_AUTO:		SetPerformanceDefault(VGA_PERF_FANSPD, nCard); break;	// Must stop green mode first.
		case VGA_FANMODE_MANUAL:	SetPerformance(VGA_PERF_FANSPD, nCard, &perf.nFanSpd); break;
		}
	}
	if(dwPerfs & VGA_PERF_GCLKCUV && perf.dwGpuClkCurve != 1)
	{
		SetVfClockClock(perf.GpuVf, GVDISP_CLOCK_DOMAIN_ID_GPU, nCard);
	}
	if(dwPerfs & VGA_PERF_MCLKCUV && perf.dwMemClkCurve != 1)
	{
		SetVfClockClock(perf.MemVf, GVDISP_CLOCK_DOMAIN_ID_MEMORY, nCard);
	}
}

void CVGACtrl::GetPerformancesDefault(DWORD dwPerfs, VGA_PERFORMANCE& perf)
{
	if(dwPerfs & VGA_PERF_FANSPD)		perf.nFanMode = VGA_FANMODE_AUTO;
	if(dwPerfs & VGA_PERF_GPUCLK)		GetPerformanceDefault(VGA_PERF_GPUCLK,		&perf.nGpuClk);
	if(dwPerfs & VGA_PERF_MEMCLK)		GetPerformanceDefault(VGA_PERF_MEMCLK,		&perf.nMemClk);
	if(dwPerfs & VGA_PERF_GPUVOL)		GetPerformanceDefault(VGA_PERF_GPUVOL,		&perf.nGpuVol);
	//if(dwPerfs & VGA_PERF_MAXVOL)		GetPerformanceDefault(VGA_PERF_MAXVOL,		&perf.nMaxVol);
	if(dwPerfs & VGA_PERF_MEMVOL)		GetPerformanceDefault(VGA_PERF_MEMVOL,		&perf.nMemVol);
	if(dwPerfs & VGA_PERF_POWER)		GetPerformanceDefault(VGA_PERF_POWER,		&perf.nPower);
	if(dwPerfs & VGA_PERF_FANSPD)		GetPerformanceDefault(VGA_PERF_FANSPD,		&perf.nFanSpd);
	if(dwPerfs & VGA_PERF_TEMPER)		GetPerformanceDefault(VGA_PERF_TEMPER,		&perf.nTemperature);
	if(dwPerfs &VGA_PERF_GCLKCUV)       perf.dwGpuClkCurve=CLK_CURVE_BASE;
	if(dwPerfs &VGA_PERF_MCLKCUV)      perf.dwMemClkCurve=CLK_CURVE_BASE;  
	
}

void CVGACtrl::SetFanSetting(int nCard, FAN_SETTING  setting)
{
	nCard = nCard % GetGpuCount();
	switch(setting.nFanMode)
	{
	case VGA_FANMODE_AUTO:		
		GvSetFanSpeedDefault(nCard); 
		break;
	case VGA_FANMODE_MANUAL:
		SetPerformance(VGA_PERF_FANSPD, nCard, &setting.nFanPercent);
		break;	
	}
}

void CVGACtrl::SetFanSettingDefault(int nCard)
{
	nCard = nCard % GetGpuCount();
	GvSetFanSpeedDefault(nCard);
}

void CVGACtrl::FanSpeedMintoring(FAN_SETTING settings[], int nCurTemperature[])
{
	GVDISP_CTRL_MODE mode;
	GvGetFanCtrlMode(0, mode);	// keep query...

	for(int i=0; i < GetGpuCount(); i++)
	{
		if(VGA_FANMODE_AUTO != settings[i].nFanMode && VGA_FANMODE_MANUAL != settings[i].nFanMode)
		{
			int nIndex = 0;
			for(int j = settings[i].nCurveStep - 1; j >= 0; j--)
			{
				if(nCurTemperature[i] >= settings[i].curve[j].nTemperature)
				{
					nIndex = j; break;
				}
			}

			int nFirstTemp = settings[i].curve[0].nTemperature;
			for (int k = 0; k < settings[i].nCurveStep; k++)
			{
				if(settings[i].curve[k].nFanSpeed <= 0) continue;
				nFirstTemp = settings[i].curve[k].nTemperature;
				break;
			}
			int nFanSpeed = settings[i].curve[nIndex].nFanSpeed;
			if (nIndex != settings[i].nCurveStep - 1)
			{
				int nSpeedBefore = settings[i].curve[nIndex + 1].nFanSpeed;
				int nTempBefore = settings[i].curve[nIndex + 1].nTemperature;
				int nSpeedAfter = settings[i].curve[nIndex].nFanSpeed;
				int nTempAfter = settings[i].curve[nIndex].nTemperature;
				nFanSpeed = (int)(nSpeedAfter + (nSpeedAfter - nSpeedBefore) * (nCurTemperature[i] - nTempAfter) * 1.0 / (nTempAfter - nTempBefore));
			}

			int nStopSpeed = 20;
			if(!IsNvCard()) nStopSpeed = 33;
			if(nFanSpeed < nStopSpeed && !settings[i].bFanStop)
			{
				GvSetFanCtrlMode(i, GVDISP_CTRL_MODE_DRIVER);
				GvSetCurrentFanSpeed(i, 0, GVDISP_FANSPD_TYPE_PERCENT, nStopSpeed, GVDISP_CTRL_MODE_DRIVER);
			}
			else
			{
				GvSetFanCtrlMode(i, GVDISP_CTRL_MODE_DRIVER);
				GvSetCurrentFanSpeed(i, 0, GVDISP_FANSPD_TYPE_PERCENT, nFanSpeed, GVDISP_CTRL_MODE_DRIVER);
			}
		}
		else if (VGA_FANMODE_AUTO == settings[i].nFanMode && !settings[i].bFanStop)
		{
			FAN_SETTING setting;
			GetFanAutoSetting(setting);
			if(nCurTemperature[i] < setting.curve[1].nTemperature)
			{
				int nFanSpeed = 20;
				if(!IsNvCard()) nFanSpeed = 33;
				GvSetFanCtrlMode(i, GVDISP_CTRL_MODE_DRIVER);
				GvSetCurrentFanSpeed(i, 0, GVDISP_FANSPD_TYPE_PERCENT, nFanSpeed, GVDISP_CTRL_MODE_DRIVER);
			}
			else
			{
				GvSetFanSpeedDefault(i); 
			}
		}
		else if(VGA_FANMODE_MANUAL == settings[i].nFanMode)
		{
			GvSetFanCtrlMode(i, GVDISP_CTRL_MODE_DRIVER);
			GvSetCurrentFanSpeed(i, 0, GVDISP_FANSPD_TYPE_PERCENT, settings[i].nFanPercent, GVDISP_CTRL_MODE_DRIVER);
		}
		else if(IsSupportFanStop())
		{
			//Peter Lee fix AMD OC, gaming mode, fan do not stop
			if (settings[i].bFanStop && !IsNvCard())
			{
				FAN_SETTING setting;
				GetFanAutoSetting(setting);
				if(nCurTemperature[i] < setting.curve[1].nTemperature)
				{
					// stop fan
					GvSetFanCtrlMode(i, GVDISP_CTRL_MODE_DRIVER);
					GvSetCurrentFanSpeed(i, 0, GVDISP_FANSPD_TYPE_PERCENT, 0, GVDISP_CTRL_MODE_DRIVER);
				}
			}
			GvSetFanSpeedDefault(i); 
		}
	}
}

void CVGACtrl::GetFanAutoSetting(FAN_SETTING& setting)
{
	setting.nFanMode = VGA_FANMODE_AUTO;
	setting.nCurveStep = 0;

	setting.nCurveStep = 4;
	setting.curve[0].nTemperature = 0;
	setting.curve[0].nFanSpeed = 0;
	setting.curve[1].nTemperature = 58;
	setting.curve[1].nFanSpeed = 0;
	setting.curve[2].nTemperature = 59;
	setting.curve[2].nFanSpeed = 33;
	setting.curve[3].nTemperature = 90;
	setting.curve[3].nFanSpeed = 100;

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080XTREME-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 53;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080AORUS X")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 54;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 55;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N108TAORUS X")) >= 0)
	{
		// Peter Lee 2017/5/4 bug fix
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 55;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 55;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 100;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060AORUS")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 100;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TD5-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050D5-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N105TOC-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050OC-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N105TCN-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050CN-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 57;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 58;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TWF2OC-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050WF2OC-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N105TWF2-")) >= 0)		// Peter Lee 2017/6/5
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 57;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 58;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TG1 GAMING-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050G1 GAMING-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 57;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 58;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080TTOC-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 25;
		setting.curve[1].nTemperature = 42;
		setting.curve[1].nFanSpeed = 25;
		setting.curve[2].nTemperature = 82;
		setting.curve[2].nFanSpeed = 50;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070D5-8GD-B")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 53;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060XTREME-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 53;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-NTITANXXTREME-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 22;
		setting.curve[1].nTemperature = 61;
		setting.curve[1].nFanSpeed = 50;
		setting.curve[2].nTemperature = 81;
		setting.curve[2].nFanSpeed = 62;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 93;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N960XTREME-")) >= 0)
	{
		setting.nCurveStep = 5;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[0].nTemperature = 60;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 61;
		setting.curve[1].nFanSpeed = 50;
		setting.curve[2].nTemperature = 70;
		setting.curve[2].nFanSpeed = 65;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N970XTREME")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N980XTREME")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 44;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 45;
		setting.curve[2].nFanSpeed = 55;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 90;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N950XTREME-")) >= 0)
	{
		setting.nCurveStep = 5;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 55;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 56;
		setting.curve[2].nFanSpeed = 55;
		setting.curve[3].nTemperature = 100;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080G1 GAMING-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N1080G1 ROCK-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080XTREME W")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N108TAORUSX W-")) >= 0		// 2017/6/7 Peter Lee
		|| GetCardInfo()->sModelName.Find(_T("GV-N108TAORUSX WB-")) >= 0)	// 2017/6/7 Peter Lee
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 30;
		setting.curve[1].nTemperature = 50;
		setting.curve[1].nFanSpeed = 30;
		setting.curve[2].nTemperature = 65;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080WF3OC-")) >= 0 
		|| GetCardInfo()->sModelName.Find(_T("GV-N1080D5X-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070XTREME-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070IX")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 40;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName == _T("GV-N1080D5X-8GD"))
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 48;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060IX")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 55;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 56;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060WF2")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 57;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 58;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070G1 GAMING-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 30;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070G1 ROCK-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 70;
		setting.curve[2].nFanSpeed = 50;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060G1 GAMING")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 30;
		setting.curve[3].nTemperature = 100;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060G1 ROCK")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 55;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 56;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060D5")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 100;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX460WF2OC")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 46;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 47;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX480G1 GAMING")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-RX480WF2")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 50;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX470G1 GAMING-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-RX470WF2")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 46;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 47;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080G1 ROCK-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 57;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 58;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX570AORUS-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 44;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 49;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1030D5-")) >= 0 ||
		GetCardInfo()->sModelName.Find(_T("GV-N1030SL-")) >= 0)	// Peter Lee 2017/4/18
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 45;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 60;
		setting.curve[2].nFanSpeed = 55;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N105TOC-4GL")) >= 0
	 || GetCardInfo()->sModelName.Find(_T("GV-N1050OC-2GL")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 35;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 70;
		setting.curve[2].nFanSpeed = 52;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N108TGAMING-")) >= 0)	// Peter Lee 2017/4/25
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 59;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 59;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}	
	if (GetCardInfo()->sModelName.Find(_T("GV-RX560GAMING OC-")) >= 0)
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 50;
		setting.curve[1].nFanSpeed = 0;
		setting.curve[2].nTemperature = 60;
		setting.curve[2].nFanSpeed = 33;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1030OC-")) >= 0)	// Peter Lee 2017/5/4
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 0;
		setting.curve[1].nTemperature = 45;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 60;
		setting.curve[2].nFanSpeed = 55;
		setting.curve[3].nTemperature = 90;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N108TTURBO-")) >= 0)	// Peter Lee 2017/6/1
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 49;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 78;
		setting.curve[2].nFanSpeed = 55;
		setting.curve[3].nTemperature = 97;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1050-")) >= 0)	// Peter Lee 2017/6/5
	{
		setting.nCurveStep = 4;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 35;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 70;
		setting.curve[2].nFanSpeed = 52;
		setting.curve[3].nTemperature = 95;
		setting.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX560OC-")) >= 0)// Peter Lee 2017/6/16
	{
		setting.nCurveStep = 3;
		setting.curve[0].nTemperature = 0;
		setting.curve[0].nFanSpeed = 33;
		setting.curve[1].nTemperature = 50;
		setting.curve[1].nFanSpeed = 33;
		setting.curve[2].nTemperature = 90;
		setting.curve[2].nFanSpeed = 100;
	}
}

void CVGACtrl::GetFanSilentSetting(FAN_SETTING& green)
{
	green.nFanMode = VGA_FANMODE_DEFINE;
	green.nCurveStep = 8;
	green.curve[0].nFanSpeed = 0;
	green.curve[0].nTemperature = 0;
	green.curve[1].nFanSpeed = 0;
	green.curve[1].nTemperature = 51;
	green.curve[2].nFanSpeed = 33;
	green.curve[2].nTemperature = 52;
	green.curve[3].nFanSpeed = 38;
	green.curve[3].nTemperature = 60;
	green.curve[4].nFanSpeed = 41;
	green.curve[4].nTemperature = 67;
	green.curve[5].nFanSpeed = 44;
	green.curve[5].nTemperature = 75;
	green.curve[6].nFanSpeed = 46;
	green.curve[6].nTemperature = 85;
	green.curve[7].nFanSpeed = 90;
	green.curve[7].nTemperature = 100;

	if (GetCardInfo()->sModelName.Find(_T("GV-NTITANXXTREME-")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 22;
		green.curve[1].nTemperature = 61;
		green.curve[1].nFanSpeed = 33;
	}


	if (GetCardInfo()->sModelName.Find(_T("GV-N105TD5-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050D5-")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 57;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 70;
		green.curve[2].nFanSpeed = 40;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TOC-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050OC-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N105TCN-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050CN-")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 57;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 64;
		green.curve[2].nFanSpeed = 24;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TG1")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050G1")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 52;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 61;
		green.curve[2].nFanSpeed = 25;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TWF2")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050WF2")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 57;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 65;
		green.curve[2].nFanSpeed = 32;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080XTREME-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 95;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N960XTREME-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N980XTREME-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N970XTREME-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 95;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080G1 GAMING-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 95;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080XTREME W-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070XTREME-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 95;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070G1 GAMING-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070G1 ROCK-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[0].nFanSpeed = 33;
		green.curve[0].nTemperature = 0;
		green.curve[1].nFanSpeed = 33;
		green.curve[1].nTemperature = 51;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1070WF2OC-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060G1 GAMING-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 100;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060D5-")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 70;
		green.curve[2].nFanSpeed = 46;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName == _T("GV-N1080D5X-8GD")) // 需完全匹配，因?有機種 GV-N1080D5X-8GD-B
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 70;
		green.curve[2].nFanSpeed = 46;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX460WF2OC-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX470G1 GAMING-")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-RX470WF2")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-RX480G1 GAMING-")) >= 0)
	{
		//green.nCurveStep++;
		green.curve[7].nTemperature = 90;
		green.curve[7].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N105TOC-4GL")) >= 0
		|| GetCardInfo()->sModelName.Find(_T("GV-N1050OC-2GL")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 33;
		green.curve[1].nTemperature = 35;
		green.curve[1].nFanSpeed = 33;
		green.curve[2].nTemperature = 85;
		green.curve[2].nFanSpeed = 50;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1080AORUS")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 70;
		green.curve[2].nFanSpeed = 37;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}

	if (GetCardInfo()->sModelName.Find(_T("GV-N1060AORUS")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 70;
		green.curve[2].nFanSpeed = 37;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName == _T("GV-N108TAORUS X-11GD"))	// Peter Lee 2017/3/29
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 55;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 55;
		green.curve[2].nFanSpeed = 28;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 81;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1070AORUS-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 62;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 62;
		green.curve[2].nFanSpeed = 29;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 89;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1060XTREME9-")) >= 0 ||
		GetCardInfo()->sModelName == _T("GV-N1060AORUS X-6GD"))	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 65;
		green.curve[2].nFanSpeed = 45;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX580XTRAORUS-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 77;
		green.curve[2].nFanSpeed = 40;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX550GAMING OC-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 75;
		green.curve[2].nFanSpeed = 33;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1080AORUS X11-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 57;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 58;
		green.curve[2].nFanSpeed = 28;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 81;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1080AORUS-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 55;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 56;
		green.curve[2].nFanSpeed = 30;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 91;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N108TAORUS-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 75;
		green.curve[2].nFanSpeed = 47;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N108TGAMING OC-")) >= 0 ||	// Peter Lee 2017/3/30
		GetCardInfo()->sModelName.Find(_T("GV-N108TGAMINGOC BLACK-")) >= 0)	// Peter Lee 2017/6/16	
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 74;
		green.curve[2].nFanSpeed = 45;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX550D5-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 75;
		green.curve[2].nFanSpeed = 37;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}		
	if (GetCardInfo()->sModelName.Find(_T("GV-N1060AORUS-")) >= 0)	// Peter Lee 2017/3/30
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 48;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 68;
		green.curve[2].nFanSpeed = 33;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX570AORUS-")) >= 0)	// Peter Lee 2017/4/1
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 77;
		green.curve[2].nFanSpeed = 40;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX570GAMING-")) >= 0)	// Peter Lee 2017/4/1
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 74;
		green.curve[2].nFanSpeed = 35;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}		
	if (GetCardInfo()->sModelName.Find(_T("GV-RX580AORUS-")) >= 0)	// Peter Lee 2017/4/7
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 78;
		green.curve[2].nFanSpeed = 45;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}		
	if (GetCardInfo()->sModelName.Find(_T("GV-RX580GAMING-")) >= 0)	// Peter Lee 2017/4/7
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0; 
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 78;
		green.curve[2].nFanSpeed = 45;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1030D5-")) >= 0)	// Peter Lee 2017/4/18
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 33;
		green.curve[1].nTemperature = 45;
		green.curve[1].nFanSpeed = 33;
		green.curve[2].nTemperature = 75;
		green.curve[2].nFanSpeed = 60;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 91;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N108TGAMING-")) >= 0)	// Peter Lee 2017/4/25
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 58;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 59;
		green.curve[2].nFanSpeed = 30;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 78;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX560GAMING OC-")) >= 0)	// Peter Lee 2017/4/25
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 59;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 60;
		green.curve[2].nFanSpeed = 33;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 73;
	}	
	// Peter Lee 2017/5/4; GV-N105TOC-4GD & GV-N1050OC-2GD 1.1(BIOS F60)
	// ECO fan speed = gaming fan speed
	if ((GetCardInfo()->sModelName == _T("GV-N105TOC-4GD")
		|| GetCardInfo()->sModelName == _T("GV-N1050OC-2GD"))
		&& GetCardInfo()->sBiosVer == _T("F60"))
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 57;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 58;
		green.curve[2].nFanSpeed = 33;
		green.curve[3].nTemperature = 95;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1030OC-")) >= 0)	// Peter Lee 2017/5/4
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 62;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 63;
		green.curve[2].nFanSpeed = 40;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-N1070IX")) >= 0)
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 49;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 50;
		green.curve[2].nFanSpeed = 40;
		green.curve[3].nTemperature = 90;
		green.curve[3].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName.Find(_T("GV-RX560OC-")) >= 0)	// Peter Lee 2017/6/16
	{
		green.nFanMode=VGA_FANMODE_AUTO;
		green.nCurveStep = 3;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 33;
		green.curve[1].nTemperature = 50;
		green.curve[1].nFanSpeed = 33;
		green.curve[2].nTemperature = 90;
		green.curve[2].nFanSpeed = 100;
	}
	if (GetCardInfo()->sModelName == _T("GV-RX560GAMING OC-4GD 2.0"))	// Peter Lee 2017/6/16
	{
		green.nCurveStep = 4;
		green.curve[0].nTemperature = 0;
		green.curve[0].nFanSpeed = 0;
		green.curve[1].nTemperature = 64;
		green.curve[1].nFanSpeed = 0;
		green.curve[2].nTemperature = 65;
		green.curve[2].nFanSpeed = 29;
		green.curve[3].nTemperature = 100;
		green.curve[3].nFanSpeed = 53;
	}
}


void CVGACtrl::SetLedSetting(int nCard, LED_SETTING  setting, bool bSave)
{
	if (m_bIXEB)
	{
		return s_DevIXEB.SetLedSetting(0, 0, setting, bSave);
	}

	static COLORREF s_clrSelect = RGB( 0, 0, 0);	
	static int nCurClk = 0;
	static LED_SETTING settings[GVDISP_CARD_MAXNUM];
	static DWORD s_dwMode[GVDISP_CARD_MAXNUM] = { -1 };
	DWORD dwMode = 0;
	setting.nSelectCard = nCard;
	dwMode = setting.bOn ? LED_MODE_AUTO : LED_MODE_OFF;
 
	// Peter Lee 2017/6/2 check cycling color
	if (setting.dwStyle == 6)
	{
		setting.dwStyle = 0;
		setting.bMutilColor = true;
	}
		
	if (setting.bMutilColor) dwMode |= LED_CLR_U;
	dwMode |= ((int)pow(2.0, setting.dwStyle * 1.0) * LED_TYPE_NONE);

	COLORREF clrSelect = setting.clrLed;
	if(setting.dwStyle == LED_STYLE_BREATHING && CVGALed::GetVersion() < 1.0) 
		clrSelect = RGB(
		GetRValue(setting.clrLed) * setting.nRangeMax / 100.0, 
		GetGValue(setting.clrLed) * setting.nRangeMax / 100.0, 
		GetBValue(setting.clrLed) * setting.nRangeMax / 100.0
		);
	// Peter Lee 2017/6/2, SLI, need to lower RGB value to fix ledd flashing bug, RGB value * 0.8
	if (nCard == 2)	
	{
		clrSelect = RGB(
		GetRValue(setting.clrLed) * 0.8, 
		GetGValue(setting.clrLed) * 0.8, 
		GetBValue(setting.clrLed) * 0.8);
	}
	setting.clrLed = clrSelect;

	if(setting.dwStyle >= LED_STYLE_MONITORING)
	{
		dwMode = LED_TYPE_NONE | (dwMode & 0xffff);
	}

	// 不是可变模式与可变模式的base变化时
	Lock();
	//if(setting.nSelectCard == -2) 
	if(setting.nSelectCard == -1) 
		CVGALed::SwitchMode(setting.nSelectCard, setting.nSelectCard < 0 ? CTRL_MODE_SYNC : CTRL_MODE_CARD);
	else 
		CVGALed::SwitchMode(setting.nSelectCard, CTRL_MODE_CARD);
	if(setting.dwStyle < LED_STYLE_MONITORING) 
		CVGALed::SetLedLight(setting.nSelectCard,  dwMode>>12, setting.nSpeed, setting.nRangeMax, setting.nRangeMin);
	//CVGALed::SetColor(setting.nSelectCard, GetRValue(setting.clrLed), GetGValue(setting.clrLed), GetBValue(setting.clrLed));
	CVGALed::SetColor(setting.nSelectCard, GetRValue(setting.clrLed), GetGValue(setting.clrLed), GetBValue(setting.clrLed));
	if(s_dwMode[setting.nSelectCard + 1] != dwMode) 
		CVGALed::SetLed(setting.nSelectCard, dwMode, 0);
	if(settings[setting.nSelectCard + 1].nType != setting.nType) 
		CVGALed::SetSliType(setting.nType, 0);
	if(bSave) 
		CVGALed::Save(nCard);
	Unlock();

	settings[setting.nSelectCard + 1] = setting;
	s_dwMode[setting.nSelectCard + 1] = dwMode;
}

void CVGACtrl::LedMintoring(int nCard, LED_SETTING setting)
{
	VGA_PERFORMANCE perf;
	LED_SETTING ledSetting = setting;
	if (nCard < GetGpuCount())
	{
		if (LED_STYLE_MONITORING == ledSetting.dwStyle && ledSetting.dwVariation >= 0)
		{
			COLORREF clr;
			double fBright = ledSetting.nRangeMax;
			GetCurrentPerformances(VGA_PERF_TEMPER | VGA_PERF_GPUCLK | VGA_PERF_GPUVOL | VGA_PERF_FANSPD | VGA_PERF_GPUSAGE, nCard, perf);

			if(LED_MONITOR_GPU_FANSPEED == ledSetting.dwVariation && !IsNvCard()) 
				fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0 * perf.nFanSpd / 1.00;

			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );


			if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE)
			{
				if(perf.nTemperature <= 40) clr = RGB(0, 255, 0);
				else if(perf.nTemperature <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_USAGE)
			{
				if(perf.nGPUsage <= 40) clr = RGB(0, 255, 0);
				else if(perf.nGPUsage <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED)
			{
				if(perf.nFanSpd <= 35) clr = RGB(0, 255, 0);
				else if(perf.nFanSpd <= 50) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			// Peter Lee 2017/6/12 bug fix
			if (m_bIXEB)
			{
				Lock();
				if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE || 
					ledSetting.dwVariation == LED_MONITOR_GPU_USAGE || 
					ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED) 
				{
					ledSetting.clrLed = clr;
					ledSetting.nRangeMax = (int)fBright;
					ledSetting.dwStyle = LED_STYLE_CONSISTENT;
					ledSetting.bMutilColor = false;
					s_DevIXEB.SetLedSetting(0, 0, ledSetting, false);
				}
				Unlock();
			}
			else	// real VGA card
			{
				Lock();
				CVGALed::SwitchMode(nCard < 0 ? -1 : nCard, nCard < 0 ? CTRL_MODE_SYNC : CTRL_MODE_CARD);
				CVGALed::SetLedLight(nCard, dwMode>>12, ledSetting.nSpeed, (int)fBright);
				if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE || 
					ledSetting.dwVariation == LED_MONITOR_GPU_USAGE || 
					ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED) 
					CVGALed::SetColor(nCard, GetRValue(clr), GetGValue(clr), GetBValue(clr));
				Unlock();
			}
		}

		if (LED_STYLE_AUDIOFLASHING == ledSetting.dwStyle)
		{
			double fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0; // ?算?值
			fBright = fBright * CAudioVolume::GetVolume() / 0.5 ;	// 50%为全亮
			fBright += ledSetting.nRangeMin; // 叠加最小值
			ledSetting.nRangeMax = (int)fBright;

			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );

			// Peter Lee 2017/6/12 bug fix
			if (m_bIXEB)
			{
				Lock();				
				ledSetting.nRangeMax = (int)fBright;
				ledSetting.dwStyle = LED_STYLE_CONSISTENT;
				ledSetting.bMutilColor = false;
				s_DevIXEB.SetLedSetting(0, 0, ledSetting, false);
				Unlock();
			}
			else	// real VGA card
			{
				Lock();
				CVGALed::SwitchMode(nCard < 0 ? -1 : nCard, nCard < 0 ? CTRL_MODE_SYNC : CTRL_MODE_CARD);
				CVGALed::SetLedLight(nCard, dwMode>>12, ledSetting.nSpeed, (int)fBright);
				CVGALed::SetColor(nCard, GetRValue(ledSetting.clrLed), GetGValue(ledSetting.clrLed), GetBValue(ledSetting.clrLed));

				Unlock();
			}
		}
	}
	else
	{
		static int nTimer = 5;
		COLORREF clr;
		if (LED_STYLE_MONITORING == ledSetting.dwStyle && ledSetting.dwVariation >= 0)
		{
			GetCurrentPerformances(VGA_PERF_TEMPER | VGA_PERF_GPUCLK | VGA_PERF_GPUVOL | VGA_PERF_FANSPD | VGA_PERF_GPUSAGE, 0, perf);
			double fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0; // ?算?值
			switch(ledSetting.dwVariation)
			{
			case LED_MONITOR_GPU_TEMPERATURE: fBright = fBright * perf.nTemperature / 1.00 ;	break;
			case LED_MONITOR_GPU_USAGE: fBright = fBright * perf.nGPUsage / 1.00;		break;
			case LED_MONITOR_GPU_FANSPEED: fBright = fBright * perf.nFanSpd / 1.00;		break;
			}

			if(LED_MONITOR_GPU_FANSPEED == ledSetting.dwVariation && !IsNvCard()) 
				fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0 * perf.nFanSpd / 1.00;

			fBright += ledSetting.nRangeMin; // 叠加最小值
			if (ledSetting.nType == SLI_TYPE_NV) ledSetting.nRangeMax = (int)fBright;

			if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE)
			{
				if(perf.nTemperature <= 40) clr = RGB(0, 255, 0);
				else if(perf.nTemperature <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_USAGE)
			{
				if(perf.nGPUsage <= 40) clr = RGB(0, 255, 0);
				else if(perf.nGPUsage <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED)
			{
				if(perf.nFanSpd <= 35) clr = RGB(0, 255, 0);
				else if(perf.nFanSpd <= 50) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

		}

		if (LED_STYLE_AUDIOFLASHING == ledSetting.dwStyle)
		{
			double fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0; // ?算?值
			fBright = fBright * CAudioVolume::GetVolume() / 1.00 ;	
			fBright += ledSetting.nRangeMin; // 叠加最小值
			ledSetting.nRangeMax = (int)fBright;
			ledSetting.dwStyle = LED_STYLE_CONSISTENT;
		}

		if(!ledSetting.bOn) ledSetting.nRangeMax = 0;

		LED_SETTING sli = ledSetting;
		if(ledSetting.dwStyle >= LED_STYLE_MONITORING) sli.dwStyle = LED_STYLE_CONSISTENT;
		if (CVGALed::GetVersion() >= 1.0 && setting.dwStyle >= LED_STYLE_MONITORING && nCard >= 0 && nTimer-- < 0)
		{
			Lock();
			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );
			CVGALed::SwitchMode(2, CTRL_MODE_SLI);
			CVGALed::SetLedLight(2, dwMode>>12, ledSetting.nSpeed, ledSetting.nRangeMax);
			if(LED_STYLE_MONITORING == ledSetting.dwStyle) 
				CVGALed::SetColor(nCard, GetRValue(clr), GetGValue(clr), GetBValue(clr));
			Unlock();
			nTimer = 5;
		}
		if (ledSetting.nType == SLI_TYPE_NV)
		{
			CVGALed::SetLight(sli, -1);
		}
		else
		{
			CVGALed::SetLight(100, -1, -1);
		}
	}
}

void CVGACtrl::LedMintoringSync(LED_SETTING setting)
{
	VGA_PERFORMANCE perf;
	LED_SETTING ledSetting = setting;
	if (1)
	{
		if (LED_STYLE_MONITORING == ledSetting.dwStyle && ledSetting.dwVariation >= 0)
		{
			COLORREF clr;
			double fBright = ledSetting.nRangeMax;
			GetCurrentPerformances(VGA_PERF_TEMPER | VGA_PERF_GPUCLK | VGA_PERF_GPUVOL | VGA_PERF_FANSPD | VGA_PERF_GPUSAGE, 0, perf);

			if(LED_MONITOR_GPU_FANSPEED == ledSetting.dwVariation && !IsNvCard()) 
				fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0 * perf.nFanSpd / 1.00;

			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );

			if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE)
			{
				if(perf.nTemperature <= 40) clr = RGB(0, 255, 0);
				else if(perf.nTemperature <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_USAGE)
			{
				if(perf.nGPUsage <= 40) clr = RGB(0, 255, 0);
				else if(perf.nGPUsage <= 70) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			if (ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED)
			{
				if(perf.nFanSpd <= 35) clr = RGB(0, 255, 0);
				else if(perf.nFanSpd <= 50) clr = RGB(255, 255, 0);
				else clr = RGB(255, 102, 0);
			}

			Lock();
			CVGALed::SwitchMode(-1, CTRL_MODE_SYNC);
			CVGALed::SetLedLight(-1, dwMode>>12, ledSetting.nSpeed, (int)fBright);
			if (ledSetting.dwVariation == LED_MONITOR_GPU_TEMPERATURE || 
				ledSetting.dwVariation == LED_MONITOR_GPU_USAGE || 
				ledSetting.dwVariation == LED_MONITOR_GPU_FANSPEED) 
				CVGALed::SetColor(-1, GetRValue(clr), GetGValue(clr), GetBValue(clr));
			Unlock();
		}

		if (LED_STYLE_AUDIOFLASHING == ledSetting.dwStyle)
		{
			double fBright = ( ledSetting.nRangeMax - ledSetting.nRangeMin ) / 100.0; // ?算?值
			fBright = fBright * CAudioVolume::GetVolume() / 0.5 ;	// 50%为全亮
			fBright += ledSetting.nRangeMin; // 叠加最小值
			ledSetting.nRangeMax = (int)fBright;

			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );

			Lock();
			CVGALed::SwitchMode(-1, CTRL_MODE_SYNC);
			CVGALed::SetLedLight(-1, dwMode>>12, ledSetting.nSpeed, (int)fBright);
			CVGALed::SetColor(-1, GetRValue(ledSetting.clrLed), GetGValue(ledSetting.clrLed), GetBValue(ledSetting.clrLed));

			Unlock();
		}
		if (LED_STYLE_BREATHING == ledSetting.dwStyle)
		{
			static int iDir = 0;
			static int iSpeed = 0;
			static int iBright = 0;
			//if (iSpeed == 0)
			//{
				iSpeed = ledSetting.nSpeed;
				if (iDir == 0)
				{
					iBright += 10;
					if (iBright >= ledSetting.nRangeMax)
						iDir = 1;
				}
				else
				{
					iBright -= 10;
					if (iBright <= ledSetting.nRangeMin)
					{
						iDir = 0;
					}
				}
			//}
			//else
				//iSpeed--;

			DWORD dwMode = LED_TYPE_NONE
				| ( ledSetting.bOn ? LED_MODE_AUTO : LED_MODE_OFF );
			Lock();
			CVGALed::SwitchMode(-1, CTRL_MODE_SYNC);
			CVGALed::SetLedLight(-1, dwMode>>12, ledSetting.nSpeed, iBright);
			CVGALed::SetColor(-1, GetRValue(ledSetting.clrLed), GetGValue(ledSetting.clrLed), GetBValue(ledSetting.clrLed));

			Unlock();

		}
	}
}

void CVGACtrl::SetAllLedSetting(LED_SETTING setting, bool bSave)
{
	SetLedSetting(-1, setting);
}

CString CVGACtrl::LogHeader(DWORD dwPerfs, CString sSavePath)
{
	m_sLogPath = sSavePath;
	static DWORD dwLastPerfs = 0;
	bool bWriteHeader = dwLastPerfs != dwPerfs;
	CString sFile = _T("");

	if(_T("") != m_sLogPath)
	{
		sFile = m_sLogPath;
	}

	if(_T("") != sFile)
	{
		m_pLogFile = new CStdioFile;
		bWriteHeader = bWriteHeader || !PathFileExists(sFile);
		if(!m_pLogFile->Open(sFile, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
		{
			delete m_pLogFile;
			m_pLogFile = NULL;
		}

		if (bWriteHeader)
		{
			CString sTitle = _T("");
			sTitle += _T("Date Time\t\t");
			if(dwPerfs & VGA_PERF_GPUCLK)  sTitle += _T("GPU Clock(MHz)\t"); 
			if(dwPerfs & VGA_PERF_MEMCLK)  sTitle += _T("Memory Clock(MHz)\t"); 
			if(dwPerfs & VGA_PERF_GPUVOL)  sTitle += _T("GPU Voltage(mV)\t");
			if(dwPerfs & VGA_PERF_MEMVOL)  sTitle += _T("Memory Voltage(mV)\t");
			if(dwPerfs & VGA_PERF_POWER)   sTitle += _T("Power(%)\t");
			if(dwPerfs & VGA_PERF_TEMPER)  sTitle += _T("GPU Temperature('C)\t");
			if(dwPerfs & VGA_PERF_FANSPD)  sTitle += _T("FAN Speed(%)\t");
			if(dwPerfs & VGA_PERF_FANRPM)  sTitle += _T("FAN Speed(RPM)\t");
			if(dwPerfs & VGA_PERF_GPUSAGE) sTitle += _T("GPU Usage(%)\t\t");
			if(dwPerfs & VGA_PERF_CPUSAGE) sTitle += _T("CPU Usage(%)\t\t");
			if(dwPerfs & VGA_PERF_CPUCLK)  sTitle += _T("CPU Clock(MHz)\t\t");
			if(dwPerfs & VGA_PERF_MEMUSAGE)sTitle += _T("Memory Usage(%)\t\t");
			if(dwPerfs & VGA_PERF_PAGEFILE)sTitle += _T("Page File Usage(%)\t");
			sTitle += _T("\n");
			m_pLogFile->SeekToEnd();
			m_pLogFile->WriteString(sTitle);
		}
		dwLastPerfs = dwPerfs;	
	}
	return m_sLogPath;
}

CString CVGACtrl::LogOutToTxt(VGA_PERFORMANCE perf, VGA_MB_INFO MbInfo, DWORD dwPerfs, CString sSavePath)
{
	LogHeader(dwPerfs, sSavePath);
	if(NULL != m_pLogFile)
	{
		ULONGLONG nFileLen = m_pLogFile->GetLength();
		if(nFileLen < 10485760) // 10MB
		{
			CString sTmp, sItem =_T("");

			SYSTEMTIME stT;
			::GetLocalTime(&stT);//06-30-2010 16:00:00
			sTmp.Format(_T("%02d-%02d-%04d %02d:%02d:%02d\t"), stT.wMonth, stT.wDay, stT.wYear, stT.wHour, stT.wMinute, stT.wSecond); // Format as : 06-30-2010 16:00:00
			sItem += sTmp;
			sTmp.Format(_T("%d\t\t"), perf.nGpuClk);
			if(dwPerfs & VGA_PERF_GPUCLK) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), perf.nMemClk);
			if(dwPerfs & VGA_PERF_MEMCLK) sItem += sTmp;
			sTmp.Format(_T("%0.3f\t\t"), perf.nGpuVol / 1000000.0);
			if(dwPerfs & VGA_PERF_GPUVOL) sItem += sTmp;
			sTmp.Format(_T("%0.3f\t\t"), perf.nMemVol / 1000000.0);
			if(dwPerfs & VGA_PERF_MEMVOL) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), perf.nPower);
			if(dwPerfs & VGA_PERF_POWER) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), perf.nTemperature);
			if(dwPerfs & VGA_PERF_TEMPER) sItem += sTmp;
			sTmp.Format(_T("%d\t\t"), perf.nFanSpd);
			if(dwPerfs & VGA_PERF_FANSPD) sItem += sTmp;
			sTmp.Format(_T("%d\t\t"), perf.nFanRPM);
			if(dwPerfs & VGA_PERF_FANRPM) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), perf.nGPUsage);
			if(dwPerfs & VGA_PERF_GPUSAGE) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), MbInfo.nCPUsage);
			if(dwPerfs & VGA_PERF_CPUSAGE) sItem += sTmp;
			sTmp.Format(_T("%.2f\t\t\t"), MbInfo.fCPUClk * 10);
			if(dwPerfs & VGA_PERF_CPUCLK) sItem += sTmp;
			sTmp.Format(_T("%d\t\t\t"), MbInfo.nMemUsage);
			if(dwPerfs & VGA_PERF_MEMUSAGE) sItem += sTmp;
			sTmp.Format(_T("%f\t\t\t"), MbInfo.fPageUsage);
			if(dwPerfs & VGA_PERF_PAGEFILE) sItem += sTmp;
			sItem += _T("\n");
			m_pLogFile->SeekToEnd();
			m_pLogFile->WriteString(sItem);
		}
		StopLogOut();
	}
	return m_sLogPath;
}

void CVGACtrl::StopLogOut ()
{
	if(NULL != m_pLogFile)
	{
		m_pLogFile->Close();
		delete m_pLogFile;
		m_pLogFile = NULL;
	}
}

int  CVGACtrl::GetOneStep(DWORD dwPerf, DWORD dwType)
{
	switch(dwType)
	{
	case VGA_MODE_OC:	return GetOneStepOc(dwPerf);
	case VGA_MODE_GAME:	return GetOneStepDefault(dwPerf);
	case VGA_MODE_ECO:	return GetOneStepEOc(dwPerf);
	case VGA_MODE_OCBOOST:	return GetOneStepOcBoost();
	case VGA_MODE_ECOBOOST:	return GetOneStepEcoBoost();
	}
	return 0;
}

void CVGACtrl::ContactUs()
{
	TCHAR szUrl[MAX_PATH] = _T("http://www.gigabyte.com/about-gigabyte/contact-us.aspx");
	ShellExecute(NULL, _T("open"), szUrl, NULL, NULL, SW_SHOW);
}

void CVGACtrl::ConnectToUrl()
{
	int nUrlCount = 260;
	TCHAR szUrl[260] = {0};
	CString sModelName = GetCardInfo()->sModelName;

	GvGetModelUrl((LPTSTR)(LPCTSTR)sModelName, szUrl, nUrlCount);
	ShellExecute(NULL, _T("open"), szUrl, NULL, NULL, SW_SHOW);
}

void CVGACtrl::ConnectToFAQ()
{
	int nUrlCount = 260;
	TCHAR szUrl[260] = {0};
	CString sModelName = GetCardInfo()->sModelName;

	GvGetFAQUrl((LPTSTR)(LPCTSTR)sModelName, szUrl, nUrlCount);
	ShellExecute(NULL, _T("open"), szUrl, NULL, NULL, SW_SHOW);
}

void CVGACtrl::BiosUpdate()
{
	CString sBiosVer   = GetCardInfo()->sBiosVer;
	CString sModelName = GetCardInfo()->sModelName;

	GvBiosUpdate((LPTSTR)(LPCTSTR)sModelName, (LPTSTR)(LPCTSTR)sBiosVer);
}
void CVGACtrl::DriverUpdate()
{
	CString sModelName  = GetCardInfo()->sModelName;
	CString sDriverVer  = GetCardInfo()->sDriverVer;
	CString sDriverDate = GetCardInfo()->sDriverDate;	

	GvDriverUpdate((LPTSTR)(LPCTSTR)sModelName, (LPTSTR)(LPCTSTR)sDriverVer, (LPTSTR)(LPCTSTR)sDriverDate);
}
bool CVGACtrl::IsOneStepCard()
{
   if(GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_OC))
	   return true;
   else
	   return false;
}

void CVGACtrl::SoftwareUpdate()
{
	AUDT_FILEVERSION version = {0};
	TCHAR szModule[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModule, sizeof(szModule));
	if(GvGetModuleVersion(szModule, FALSE, &version))
	{
		CString sSavePath = Gv::OS::GetCurDirectory() + _T("GvTemp\\setup.exe");
		int nLen = 260;
		GvUtilityUpdatePath(AUDT_UTILITY_AORUSX, version, NULL, sSavePath.GetBuffer(260), nLen);
		sSavePath.ReleaseBuffer();
		Gv::Shell shell;
		if(PathFileExists(sSavePath)) shell.Execute(sSavePath);
	}
}

void CVGACtrl::GetGpuBaseSet(GVDISP_CLOCK_VFSET &GpuBaseOffset)
{
	GpuBaseOffset.nNumVFPoints = m_BaseOffsets.nNumVFPoints;
	for (int i=0; i < m_BaseOffsets.nNumVFPoints; i++)
	{
		GpuBaseOffset.offset[i].nIndex = m_BaseOffsets.offset[i].nIndex;
		GpuBaseOffset.offset[i].nOffset = m_BaseOffsets.offset[i].nOffset;
	}
}

void CVGACtrl::GetGpuBaseVfs(GVDISP_CLOCK_VFPTS &GpuBaseVfs)
{
    GpuBaseVfs.nNumVFPoints=m_GpuBaseVfs.nNumVFPoints;
    for (int i=0;i<GpuBaseVfs.nNumVFPoints;i++)
    {
		GpuBaseVfs.vfs[i].nIndex=m_GpuBaseVfs.vfs[i].nIndex;
		GpuBaseVfs.vfs[i].value.nClock=m_GpuBaseVfs.vfs[i].value.nClock;
		GpuBaseVfs.vfs[i].value.nVoltage=m_GpuBaseVfs.vfs[i].value.nVoltage;
    }
       

}
void CVGACtrl::GetCurClockCurve(PGVDISP_CLOCK_VFPTS pVF)
{
	GVDISP_CLOCK_VFSET vf = {0};
	pVF->nNumVFPoints = 0;
	GvGetVfClock(0, GVDISP_CLOCK_DOMAIN_ID_GPU, pVF);
	GvGetVfClockOffset(0, GVDISP_CLOCK_DOMAIN_ID_GPU, &vf);
	for (int i = 0; i < vf.nNumVFPoints; i++)
	{
		pVF->vfs[i].value.nClock = (pVF->vfs[i].value.nClock - vf.offset[i].nOffset / 2);
	}
}

void CVGACtrl::TranlateClockOffset(PGVDISP_CLOCK_VFSET pVfset, int nMin, int nMax)
{
	int nMinOffset = (nMin * 2 - m_GpuBaseVfs.vfs[0].value.nClock) * 2;
	int nMaxOffset = (nMax * 2 - m_GpuBaseVfs.vfs[m_GpuBaseVfs.nNumVFPoints - 1].value.nClock) * 2;
	pVfset->nNumVFPoints = 2;
	pVfset->offset[0].nIndex = m_GpuBaseVfs.vfs[0].nIndex;
	pVfset->offset[1].nIndex = m_GpuBaseVfs.vfs[m_GpuBaseVfs.nNumVFPoints - 1].nIndex;
	pVfset->offset[0].nOffset = nMinOffset;
	pVfset->offset[1].nOffset = nMaxOffset;
}

void CVGACtrl::TranlateClockVF(GVDISP_CLOCK_VFSET Vfset, int& nMin, int& nMax)
{
	nMin = (m_GpuBaseVfs.vfs[0].value.nClock + Vfset.offset[0].nOffset / 2) / 2;
	nMax = (m_GpuBaseVfs.vfs[m_GpuBaseVfs.nNumVFPoints - 1].value.nClock + Vfset.offset[1].nOffset / 2) / 2;
}

int CVGACtrl::OffsetToVFPtClk(GVDISP_CLOCK_VFOFFSET offset)
{
	return (OffsetIndexToClk(offset.nIndex) + offset.nOffset / 2) / 2;
}

int CVGACtrl::OffsetIndexToVol(const int nIndex)
{
	for (int i = 0; i < m_GpuBaseVfs.nNumVFPoints; i++)
	{
		if(nIndex == m_GpuBaseVfs.vfs[i].nIndex)
		{
			return m_GpuBaseVfs.vfs[i].value.nVoltage;
		}
	}
	return 0;
}

int CVGACtrl::OffsetIndexToClk(const int nIndex)
{
	for (int i = 0; i < m_GpuBaseVfs.nNumVFPoints; i++)
	{
		if (nIndex == m_GpuBaseVfs.vfs[i].nIndex)
		{
			return m_GpuBaseVfs.vfs[i].value.nClock;
		}
	}
	return 0;
}

GVDISP_CLOCK_VFOFFSET CVGACtrl::VFPtToOffset(GVDISP_CLOCK_VFPT vfpt)
{
	GVDISP_CLOCK_VFOFFSET offset;
	int nBaseClock = 0;
	for (int i = 0; i < m_GpuBaseVfs.nNumVFPoints; i++)
	{
		vfpt.nIndex = m_GpuBaseVfs.vfs[i].nIndex;
		nBaseClock = m_GpuBaseVfs.vfs[i].value.nClock;
		if(vfpt.value.nVoltage <= m_GpuBaseVfs.vfs[i].value.nVoltage) break;
	}
	offset.nIndex = vfpt.nIndex;
	offset.nOffset = (vfpt.value.nClock * 2 - nBaseClock) * 2;

	return offset;
}

GVDISP_CLOCK_VFPT CVGACtrl::OffsetToVFPt(GVDISP_CLOCK_VFOFFSET offset)
{
	GVDISP_CLOCK_VFPT vfpt;
	int nBaseClock = 0;
	vfpt.nIndex = offset.nIndex;
	vfpt.value.nClock = OffsetIndexToClk(offset.nIndex);
	for (int i = 0; i < m_GpuBaseVfs.nNumVFPoints; i++)
	{
		if (offset.nIndex == m_GpuBaseVfs.vfs[i].nIndex)
		{
			vfpt.value.nClock = (m_GpuBaseVfs.vfs[i].value.nClock + offset.nOffset / 2) / 2;
			vfpt.value.nVoltage = m_GpuBaseVfs.vfs[i].value.nVoltage;
			return vfpt;
		}
	}
	return vfpt;
}

bool CVGACtrl::SetVfClockClock(GVDISP_CLOCK_VFSET vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard)
{
	if (1 == vfset.nNumVFPoints)
	{
		if(GVAPI_OK != GvSetVfClock(nCard, GVDISP_CLOCK_DOMAIN_ID_GPU, vfset.offset[0].nIndex, vfset.offset[0].nOffset))
			return false;
	}

	GVDISP_CLOCK_VFSET vfpt;
	GVDISP_CLOCK_VFPTS vfpts;
	if(GVAPI_OK != GvGetVfClockOffset(nCard, id, &vfpt)) return false;
	if(GVAPI_OK != GvGetVfClock(nCard, id, &vfpts)) return false;
	int nVfVol[GVDISP_PLEVEL_MAXNUM] = {0};

	for (int i = 0; i < vfset.nNumVFPoints - 1; i++)
	{
		GVDISP_CLOCK_VFPT vfPrev = OffsetToVFPt(vfset.offset[i]);
		GVDISP_CLOCK_VFPT vfNext = OffsetToVFPt(vfset.offset[i + 1]);
		float k = (float)((vfset.offset[i + 1].nOffset - vfset.offset[i].nOffset) * 1.0 / (vfNext.value.nVoltage - vfPrev.value.nVoltage));

		for (int j = 0; j < vfpt.nNumVFPoints; j++)
		{
			if(vfpt.offset[j].nIndex > vfset.offset[i + 1].nIndex
				|| vfpt.offset[j].nIndex < vfset.offset[i].nIndex) continue;

			GVDISP_CLOCK_VFPT vfCur = OffsetToVFPt(vfpt.offset[j]);

			vfpt.offset[j].nOffset = (int)((k * (vfCur.value.nVoltage - vfPrev.value.nVoltage) + vfset.offset[i].nOffset));

		}
	}

	for(int i = 0; i < vfpt.nNumVFPoints; i++)
	{
		GvSetVfClock(nCard, GVDISP_CLOCK_DOMAIN_ID_GPU, vfpt.offset[i].nIndex, vfpt.offset[i].nOffset);
	}
	return true;
}

bool CVGACtrl::GetVfClockClock(GVDISP_CLOCK_VFSET& vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard)
{
	GVDISP_CLOCK_VFSET vfpt;
	if(GVAPI_OK != GvGetVfClockOffset(nCard, id, &vfpt)) return false;
	vfset.nNumVFPoints = 2;
	vfset.offset[0] = vfpt.offset[0];
	vfset.offset[1] = vfpt.offset[vfpt.nNumVFPoints - 1];
	return true;
}

BOOL CVGACtrl::GetCurrentPerformance(int nPerf, int* pValue, int nCard)
{
	*pValue = 0;

	switch(nPerf)
	{
		case VGA_PERF_GPUCLK:{
			GVDISP_ACTIVITY activity = {0};
			activity.dwPerfs = GVDISP_PERF_GPUCLK;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nGpuClock;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_MEMCLK:{
			GVDISP_ACTIVITY activity = {0};
			activity.dwPerfs = GVDISP_PERF_MEMCLK;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nMemoryClock;

				GVDISP_RAM_TYPE type;
				if(GVAPI_OK == GvGetRamType(nCard, type))
				{
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
					{
						*pValue *= 2;	// return data rate, not written clock.
					}
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
					{
						*pValue *= 2;	// return data rate, not written clock.
					}
					else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
					{
						*pValue  *= 2;
					}
					else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
					{
						*pValue  *= 4;
					}
				}
				return TRUE;
			}
			break;
		}
		case VGA_PERF_GPUVOL:{
			GVDISP_ACTIVITY activity = {0};
			GVDISP_VOLTAGES vol = {0};
			activity.dwPerfs = GVDISP_PERF_GPUVOL;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nGpuVoltage;
				if(*pValue == 0 && GVAPI_OK == GvGetPerfVoltage(0, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol, GVDISP_CTRL_MODE_FIRMWARE))
				{
					*pValue = vol.nVoltage;	// uV	real voltage, not level
					if(!IsNvCard()) *pValue = 0; // 关闭A卡读取
					return TRUE;
				}
				if(!IsNvCard()) *pValue = 0; // 关闭A卡读取
				return TRUE;
			}
			break;
		}
		case VGA_PERF_MEMVOL:{
			GVDISP_VOLTAGES vol = {0};
			if(GVAPI_OK == GvGetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, &vol, GVDISP_CTRL_MODE_FIRMWARE))
			{
				*pValue = vol.nVoltage;	// uV	real voltage, not level
				return TRUE;
			}
			break;
		}
		case VGA_PERF_POWER:{
			GVDISP_ACTIVITY activity = {0};
			activity.dwPerfs = GVDISP_PERF_POWER;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nPower;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_GPUSAGE:{
			GVDISP_ACTIVITY activity = {0};
			activity.dwPerfs = GVDISP_PERF_GPUUSAGE;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nGpuUsage;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_FANSPD:{
			int nFanSpd = 0;
			if(GVAPI_OK == GvGetCurrentFanSpeed(nCard, 0, GVDISP_FANSPD_TYPE_PERCENT, nFanSpd, GVDISP_CTRL_MODE_DRIVER))
			{
				*pValue = nFanSpd;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_FANRPM:{
			int nFanSpd = 0;
			if(GVAPI_OK == GvGetCurrentFanSpeed(nCard, 0, GVDISP_FANSPD_TYPE_RPM, nFanSpd, GVDISP_CTRL_MODE_DRIVER))
			{
				*pValue = nFanSpd;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_TEMPER:{
			GVDISP_ACTIVITY activity = {0};
			activity.dwPerfs = GVDISP_PERF_TEMPERATURE;
			if(GVAPI_OK == GvGetActivity(nCard, &activity))
			{
				*pValue = activity.curPerfs.nTemperature;
				return TRUE;
			}
			break;
		}
	}

	return FALSE;
}

BOOL CVGACtrl::GetPerformance(int nPerformance, int* pValue, int nCard)
{
	*pValue = 0;

	if(IsNvCard())
	{
		if(VGA_PERF_MEMVOL == nPerformance)
		{
			return FALSE;	// Ingored.
		}
	}

	//if(IsBoost3() && VGA_PERF_MAXVOL == nPerformance) nPerformance = VGA_PERF_OVERVOL;

	switch(nPerformance)
	{
		case VGA_PERF_GPUCLK:{
			GVDISP_CLOCKS clk = {0};
			if(GVAPI_OK == GvGetPerfClock(nCard, GVDISP_CLOCK_DOMAIN_ID_GPU, &clk))
			{
				*pValue = clk.nPerfLClocks[clk.nNumPerfLs - 1]; // P0-State
				return TRUE;
			}
			break;
		}
		case VGA_PERF_MEMCLK:{
			GVDISP_CLOCKS clk = {0};
			if(GVAPI_OK == GvGetPerfClock(nCard, GVDISP_CLOCK_DOMAIN_ID_MEMORY, &clk))
			{
				*pValue = clk.nPerfLClocks[clk.nNumPerfLs - 1];

				GVDISP_RAM_TYPE type;
				if(GVAPI_OK == GvGetRamType(nCard, type))
				{
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
					{
						*pValue  *= 2;
					}
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
					{
						*pValue  *= 2;
					}
					else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
					{
						*pValue  *= 2;
					}
					else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
					{
						*pValue  *= 4;
					}
				}
				else 

					return TRUE;
			}
			break;
		}
		case VGA_PERF_GPUVOL:{
			GVDISP_VOLTAGES vol = {0};
			if(GVAPI_OK == GvGetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol, GVDISP_CTRL_MODE_FIRMWARE) || GVAPI_OK == GvGetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol))
			{
				*pValue = vol.nVoltage;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_OVERVOL:{
			int nPercent = 0;
			if(GVAPI_OK == GvGetPerfOVoltage(0, nPercent))
			{
				*pValue = nPercent;
				return TRUE;
			}
			break;
		}
		//case VGA_PERF_MAXVOL:{
		//	GVDISP_VOLTAGES vol = {0};
		//	if(GVAPI_OK == GvGetPerfVoltage(nCard, IsNewNvCard() ? GVDISP_VOLTAGE_DOMAIN_ID_MAX : GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol))
		//	{
		//		*pValue = vol.nVoltage;
		//		return TRUE;
		//	}
		//	break;
		//}
		case VGA_PERF_MEMVOL:{
			GVDISP_VOLTAGES vol = {0};
			if(GVAPI_OK == GvGetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, &vol, GVDISP_CTRL_MODE_FIRMWARE))
			{
				*pValue = vol.nVoltage;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_POWER:{
			int nPower = 0;
			if(GVAPI_OK == GvGetPower(nCard, nPower))
			{
				*pValue = nPower;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_FANSPD:{
			int nFanSpd = 0;
			if(GVAPI_OK == GvGetCurrentFanSpeed(nCard, 0, GVDISP_FANSPD_TYPE_PERCENT, nFanSpd))
			{
				*pValue = nFanSpd;
				return TRUE;
			}
			break;
		}
		case VGA_PERF_TEMPER:{
			int nTemp = 0;
			if(GVAPI_OK == GvGetTemp(nCard, nTemp))
			{
				*pValue = nTemp;
				return TRUE;
			}
			break;
		}
	}

	return FALSE;
}

BOOL CVGACtrl::SetPerformance(int nPerf, int nCard, int* pValue, int* pValue2)
{
	if(IsNvCard())
	{
		if(VGA_PERF_MEMVOL == nPerf)
		{
			return FALSE;	// Ingored.
		}
	}

	int	nValue = *pValue;
	int	nValue2 = pValue2 != NULL ? *pValue2 : 0;
	BOOL bSuccessful = FALSE;
	GVDISP_RAM_TYPE type;

	if(VGA_PERF_MEMCLK == nPerf)
	{
		if(GVAPI_OK == GvGetRamType(0, type))
		{
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
			{
				nValue /= 2;
			}
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
			{
				nValue /= 2;
			}
			if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
			{
				nValue /= 2;
			}
			if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
			{
				nValue /= 4;
			}
		}
	}

	//if(!IsNvCard() && (VGA_PERF_GPUVOL == nPerf || VGA_PERF_MAXVOL == nPerf)) return FALSE;

	//if(IsBoost3() && VGA_PERF_MAXVOL == nPerf) nPerf = VGA_PERF_OVERVOL;

	{
		switch(nPerf)
		{
		case VGA_PERF_GPUCLK:	bSuccessful = (GVAPI_OK == GvSetPerfClock  (nCard, GVDISP_CLOCK_DOMAIN_ID_GPU,      m_nNumPerfLs - 1, nValue)); break;
		case VGA_PERF_MEMCLK:	bSuccessful = (GVAPI_OK == GvSetPerfClock  (nCard, GVDISP_CLOCK_DOMAIN_ID_MEMORY,   m_nNumPerfLs - 1, nValue)); break;
		case VGA_PERF_GPUVOL:	bSuccessful = (GVAPI_OK == GvSetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU,    GVDISP_VOLTAGE_TYPE_VALUE, nValue, GVDISP_CTRL_MODE_FIRMWARE) || GVAPI_OK == GvSetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU,    GVDISP_VOLTAGE_TYPE_VALUE, nValue)); break;
		case VGA_PERF_OVERVOL:	bSuccessful = (GVAPI_OK == GvSetPerfOVoltage(nCard, nValue)); break;
		//case VGA_PERF_MAXVOL:	bSuccessful = (GVAPI_OK == GvSetPerfVoltage(nCard, IsNewNvCard() ? GVDISP_VOLTAGE_DOMAIN_ID_MAX : GVDISP_VOLTAGE_DOMAIN_ID_GPU,    GVDISP_VOLTAGE_TYPE_VALUE, nValue)); break;
		case VGA_PERF_MEMVOL:	bSuccessful = (GVAPI_OK == GvSetPerfVoltage(nCard, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, GVDISP_VOLTAGE_TYPE_VALUE, nValue, GVDISP_CTRL_MODE_FIRMWARE)); break;
		case VGA_PERF_POWER:	bSuccessful = (GVAPI_OK == GvSetPower(nCard, nValue)); break;								
		case VGA_PERF_FANSPD:	bSuccessful = (GVAPI_OK == GvSetCurrentFanSpeed(nCard, 0, GVDISP_FANSPD_TYPE_PERCENT, nValue)); break;
		case VGA_PERF_TEMPER:	bSuccessful = (GVAPI_OK == GvSetTemp(nCard, nValue, nValue2)) ? TRUE : FALSE; break;	
		}
	}

	return bSuccessful;
}

BOOL CVGACtrl::GetPerformanceDefault(int nPerf, int* pValue)
{
	*pValue = 0;

	if(IsNvCard())
	{
		if(VGA_PERF_MEMVOL == nPerf)
		{
			return FALSE;	// Ingored.
		}
	}

	switch(nPerf)
	{
		case VGA_PERF_GPUCLK:{
			static bool bGet = false;
			static int nValue = 0;
			GVDISP_CLOCKS clk = {0};
			if(!bGet && GVAPI_OK == GvGetPerfClockDefault(0, GVDISP_CLOCK_DOMAIN_ID_GPU, &clk))
			{
				*pValue = clk.nPerfLClocks[clk.nNumPerfLs - 1];
				nValue = *pValue;
				bGet = true;
				return TRUE;
			}
			*pValue = nValue;
			return TRUE;
			break;
		}
		case VGA_PERF_MEMCLK:{
			static bool bGet = false;
			static int nValue = 0;
			GVDISP_CLOCKS clk = {0};
			if(!bGet && GVAPI_OK == GvGetPerfClockDefault(0, GVDISP_CLOCK_DOMAIN_ID_MEMORY, &clk))
			{
				*pValue = clk.nPerfLClocks[clk.nNumPerfLs - 1];

				GVDISP_RAM_TYPE type;
				if(GVAPI_OK == GvGetRamType(0, type))
				{
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
					{
						*pValue *= 2;
					}
					if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
					{
						*pValue *= 2;
					}
					if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
					{
						*pValue *= 2;
					}
					if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
					{
						*pValue *= 4;
					}
				}

				nValue = *pValue;
				bGet = true;
				return TRUE;
			}
			*pValue = nValue;
			return TRUE;
			break;
		}
		case VGA_PERF_OVERVOL:{
			int vol = 0;
			if(GVAPI_OK == GvGetPerfOVoltageDefault(0, vol))
			{
				*pValue = vol; 
				return TRUE;
			}
			break;
		}
		case VGA_PERF_GPUVOL:{
			static bool bGet = false;
			static int nValue = 0;
			GVDISP_VOLTAGES vol = {0};
			if(!bGet && GVAPI_OK == GvGetPerfVoltageDefault(0, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol, GVDISP_CTRL_MODE_FIRMWARE) || GVAPI_OK == GvGetPerfVoltageDefault(0, GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol))
			{
				*pValue = vol.nVoltage; 
				nValue = *pValue;
				bGet = true;
				return TRUE;
			}
			*pValue = nValue;
			return TRUE;
			break;
		}
		//case VGA_PERF_MAXVOL:{
		//	GVDISP_VOLTAGES vol = {0};
		//	if(GVAPI_OK == GvGetPerfVoltageDefault(0, IsNewNvCard() ? GVDISP_VOLTAGE_DOMAIN_ID_MAX : GVDISP_VOLTAGE_DOMAIN_ID_GPU, &vol))
		//	{
		//		*pValue = vol.nVoltage; 
		//		return TRUE;
		//	}
		//	break;
		//}
		case VGA_PERF_MEMVOL:{
			static bool bGet = false;
			static int nValue = 0;
			GVDISP_VOLTAGES vol = {0};
			if(!bGet && GVAPI_OK == GvGetPerfVoltageDefault(0, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, &vol, GVDISP_CTRL_MODE_FIRMWARE))
			{
				*pValue = vol.nVoltage;
				nValue = *pValue;
				bGet = true;
				return TRUE;
			}
			*pValue = nValue;
			return TRUE;
			break;
		}
		case VGA_PERF_POWER:{
			int nPower = 0;
			if(GVAPI_OK == GvGetPowerDefault(0, nPower))
			{
				*pValue = nPower;
				;
			}
			break;
		}
		case VGA_PERF_FANSPD:			break;
		case VGA_PERF_TEMPER:{
			int nTemp = 0;
			if(GVAPI_OK == GvGetTempDefault(0, nTemp))
			{
				*pValue = nTemp;
			}
			break;
		}
	}

	return FALSE;
}

BOOL CVGACtrl::SetPerformanceDefault(int nPerformance, int nCard)
{
	if(IsNvCard())
	{
		if(VGA_PERF_MEMVOL == nPerformance)
		{
			return FALSE;	// Ingored.
		}
	}

	//if (IsBoost3() && VGA_PERF_MAXVOL == nPerformance) nPerformance = VGA_PERF_OVERVOL;

	//if(!IsNvCard() && (VGA_PERF_GPUVOL == nPerformance || VGA_PERF_MAXVOL == nPerformance)) return FALSE;

	BOOL bSuccessful = FALSE;
	// 	for(int i=0; i<m_nNumOfCards; i++)
	{
		switch(nPerformance)
		{
		case VGA_PERF_GPUCLK:		bSuccessful = (GVAPI_OK == GvSetPerfClockDefault(nCard, GVDISP_CLOCK_DOMAIN_ID_GPU)); break;
		case VGA_PERF_MEMCLK:		bSuccessful = (GVAPI_OK == GvSetPerfClockDefault(nCard, GVDISP_CLOCK_DOMAIN_ID_MEMORY)); break;
		case VGA_PERF_GPUVOL:		bSuccessful = (GVAPI_OK == GvSetPerfVoltageDefault(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU, GVDISP_CTRL_MODE_FIRMWARE) || GVAPI_OK == GvSetPerfVoltageDefault(nCard, GVDISP_VOLTAGE_DOMAIN_ID_GPU)); break;
		case VGA_PERF_OVERVOL:		bSuccessful = (GVAPI_OK == GvSetPerfOVoltageDefault(nCard)); break;
		//case VGA_PERF_MAXVOL:		bSuccessful = (GVAPI_OK == GvSetPerfVoltageDefault(nCard, IsNewNvCard() ? GVDISP_VOLTAGE_DOMAIN_ID_MAX : GVDISP_VOLTAGE_DOMAIN_ID_GPU)); break;
		case VGA_PERF_MEMVOL:		bSuccessful = (GVAPI_OK == GvSetPerfVoltageDefault(nCard, GVDISP_VOLTAGE_DOMAIN_ID_MEMORY, GVDISP_CTRL_MODE_FIRMWARE)); break;
		case VGA_PERF_POWER:		bSuccessful = (GVAPI_OK == GvSetPowerDefault(nCard)); break;
		case VGA_PERF_TEMPER:		bSuccessful = (GVAPI_OK == GvSetTempDefault(nCard)); break;
		case VGA_PERF_FANSPD:		bSuccessful = (GVAPI_OK == GvSetFanSpeedDefault(nCard)); break;
		}
	}

	return bSuccessful;
}

int CVGACtrl::GetOneStepDefault(DWORD dwPerf)
{
	static int nValue = -1;
	if(nValue < 0) GetPerformanceDefault(dwPerf, &nValue);
	return nValue;
}

int CVGACtrl::GetOneStepOc(DWORD dwPerf)
{
	if (m_nOneStepIndex < 0) return 0;
	if (VGA_PERF_GPUCLK == dwPerf)
	{
		return s_stOneStepOc[m_nOneStepIndex].nGpuOCStep;
	}
	else if (VGA_PERF_MEMCLK == dwPerf)
	{
		return s_stOneStepOc[m_nOneStepIndex].nMemOCStep;
	}
	else if (VGA_PERF_POWER == dwPerf)
	{
		return s_stOneStepOc[m_nOneStepIndex].nOCPower;
	}
	return 0;
}

int CVGACtrl::GetOneStepOcBoost()
{
	if(m_nOneStepIndex < 0) return 0;
	return s_stOneStepOc[m_nOneStepIndex].nGpuOCBoost;
}

int CVGACtrl::GetOneStepEcoBoost()
{
	if(m_nOneStepIndex < 0) return 0;
	return s_stOneStepOc[m_nOneStepIndex].nGpuECOBoost;
}

int CVGACtrl::GetOneStepEOc(DWORD dwPerf)
{
	VGA_SPECIALPERFS specialPerf;
	VGA_PARAM_RANGE  range;
	int nStep = 0;
	GetSpecialPerformaces(specialPerf);
	if (VGA_PERF_GPUCLK == dwPerf)
	{
		GetPerfInfo(VGA_PERF_GPUCLK, range);
		nStep = s_stOneStepOc[m_nOneStepIndex].nGpuECOClk - specialPerf.nGpuBaseClk;
		nStep = nStep < range.nMin ? range.nMin : nStep;
		if(!IsNvCard()) nStep = s_stOneStepOc[m_nOneStepIndex].nGpuECOClk;
	}
	else if (VGA_PERF_MEMCLK == dwPerf)
	{
		GetPerfInfo(VGA_PERF_MEMCLK, range);
		nStep = s_stOneStepOc[m_nOneStepIndex].nMemECOClk - specialPerf.nMemBaseClk;
		nStep = nStep < range.nMin ? range.nMin : nStep;
		GVDISP_RAM_TYPE type;
		if(GVAPI_OK == GvGetRamType(0, type))
		{
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
			{
				nStep /= 2;
			}
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
			{
				nStep /= 2;
			}
			if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
			{
				nStep /= 2;
			}
			if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
			{
				nStep /= 4;
			}
		}
	}
	else if (VGA_PERF_POWER == dwPerf)
	{
		GetPerfInfo(VGA_PERF_POWER, range);
		nStep = s_stOneStepOc[m_nOneStepIndex].nECOPower;
		nStep = nStep < range.nMin ? range.nMin : nStep;
	}
	if(IsNvCard())nStep *= 2;
	return nStep;
}

bool CVGACtrl::GetSpecialPerformaces(VGA_SPECIALPERFS& perf)
{
	GVDISP_RAM_TYPE type;
	GVDISP_ACTIVITY activity = {0};
	if(GVAPI_OK == GvGetActivity(0, &activity))
	{
		perf.nGpuBaseClk  = activity.nGpuBaseClock;
		perf.nGpuBoostClk = activity.nGpuBoostClock;
		perf.nMemBaseClk  = activity.nMemBaseClock;
		perf.nGpuBaseVol  = activity.nGpuBaseVoltage;  // uV
		perf.nMaxBaseVol  = activity.nMaxBaseVoltage;  // uV
		if(GVAPI_OK == GvGetRamType(0, type))
		{
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5X == type))
			{
				perf.nMemBaseClk *= 2;	// return data rate, not written clock.
			}
			if(IsNvCard() && (GVDISP_RAM_TYPE_DDR5 == type || GVDISP_RAM_TYPE_DDR3 == type))
			{
				perf.nMemBaseClk *= 2;	// return data rate, not written clock.
			}
			else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR3 == type)
			{
				perf.nMemBaseClk  *= 2;
			}
			else if(!IsNvCard() && GVDISP_RAM_TYPE_DDR5 == type)
			{
				perf.nMemBaseClk  *= 4;
			}

		}

		return true;
	}

	return false;
}

bool CVGACtrl::IsAorus()
{
	return m_cardInfo.sModelName.Find(_T("AORUS")) >= 0;
}

// fan curve 1st speed = 0 means can support fan stop
bool CVGACtrl::IsSupportFanStop()
{
	FAN_SETTING fansetting;
	GetFanAutoSetting(fansetting);
	// Peter Lee 2017/5/22
	// Peter Lee 2017/6/2 remove IXEB	
	//if (m_bIXEB)
		//return false;
	if (fansetting.curve[0].nFanSpeed == 0)
		return true;
	else
		return false;
}

bool CVGACtrl::IsBoost3()
{
	BOOL bBoost3 = FALSE;
	GvIsNvBoost3(bBoost3);
	return (bBoost3 == TRUE) ? true : false;
}