#include "StdAfx.h"
#include "KbLedCtrl.h"
#include "XK700Cmd.h"

#define CLR_COUNT 32
#define CLRLIST_COUNT 105
#define CLR_LIST_ADDR 0x30000


typedef struct _CLR_LST
{
	int nCount;
	COLORREF lstClr[128];

}CLR_LST, *PCLR_LST;

static CLR_LST s_lstClr[CLRLIST_COUNT] = {0};
static int s_KEYClr[KEY_ROW][KEY_COL] = {0};
static int s_KEYLight[KEY_ROW][KEY_COL] = {0};
static int s_KEYSpeed[KEY_ROW][KEY_COL] = {0};
static bool s_KEYSel[KEY_ROW][KEY_COL] = {0};
static DWORD s_KEYClrList[KEY_ROW][KEY_COL] = {0};

BYTE CKbLedCtrl::m_Memory[MEM_SIZE] = {0};
BYTE CKbLedCtrl::m_LedMemory[MEM_SIZE] = {0};
BYTE CKbLedCtrl::m_LedValueMemory[MEM_SIZE] = {0};
int CKbLedCtrl::m_nClrList[MAX_PROFILE_COUNT] = {0};
int CKbLedCtrl::m_nClrCount = 0;
bool CKbLedCtrl::m_isReadLedMem = false;
bool CKbLedCtrl::m_isReadValueMem = false;

DWORD CKbLedCtrl::m_dwClrLastAddr[MAX_PROFILE_COUNT] = {0};
DWORD CKbLedCtrl::m_dwDefineRippleLastAddr = 0;
DWORD CKbLedCtrl::m_DefineWaveIndex[MAX_PROFILE_COUNT] = {0};
DWORD CKbLedCtrl::m_DefineRippleIndex[MAX_PROFILE_COUNT] = {0};
bool CKbLedCtrl::m_bIsSave = false;
bool CKbLedCtrl::m_bIsKeyType = false;          //设置键盘类型，使用m_dwKTClrLastAddr
DWORD CKbLedCtrl::m_dwKTClrLastAddr = 0;    
DWORD CKbLedCtrl::m_nKTClrList = 0;
BYTE CKbLedCtrl::m_LedMemoryKT[0x2000] = {0};   
BYTE CKbLedCtrl::m_LedValueMemoryKT[0x1000] = {0};
BYTE CKbLedCtrl::m_RippleMemoryKT[0x1000] ={0};
DWORD CKbLedCtrl::m_dwKTRippleLastAddr = 0;

DWORD s_dwProAddrs[] = {
	0x0000,
	0x0280,	
	0x0500,	
	0x0780,	
	0x0a00,	
	0x0c80,	
	0x1000,	
	0x1280,	
	0x1500,	
	0x1780,	
};

DWORD s_dwLedAddrs[] = {
	0x20000,
	0x21000,	
	0x22000,	
	0x23000,	
	0x24000,		
};

DWORD s_dwLedMemAddrs[] = {
	0x30000,
	0x32000,	
	0x34000,	
	0x36000,	
	0x38000,		
};

DWORD s_dwRippleMemAddrs[] = {
	0x20F60,
	0x21F60,	
	0x22F60,	
	0x23F60,	
	0x24F60,		
};

CKbLedCtrl::CKbLedCtrl(void)
{
}

CKbLedCtrl::~CKbLedCtrl(void)
{
}

void CKbLedCtrl::LoadProfileClrList(int nProfile)
{

	CXK700Cmd::SetLEDStatus(false);  //LEDOFF
	if(m_isReadLedMem == FALSE)
	{
		m_isReadLedMem = TRUE;
		CXK700Cmd::MyReadByte(0x20000, MEM_SIZE , m_LedMemory);
		Sleep(500);
	}	


	if(m_isReadValueMem == FALSE)
	{
		m_isReadValueMem = TRUE;
		CXK700Cmd::MyReadByte(0x30000, MEM_SIZE , m_LedValueMemory);
		Sleep(500);
	}


		CXK700Cmd::SetLEDStatus(true);  //LEDON


	DWORD dwAddr = s_dwLedAddrs[nProfile] - DEF_MEM_ADDR;
	BYTE* byProfile = &m_LedMemory[dwAddr];


	m_nClrList[nProfile] = byProfile[0]; // Led Profile 起始爲顔色列表數量



	dwAddr = 3 * (m_nClrList[nProfile]) + 1; // 計算最後一組顔色列表的地址存放地址

	if (m_nClrList[nProfile] == 0)	// never write
		m_dwClrLastAddr[nProfile] = 0;
	else
		m_dwClrLastAddr[nProfile] = ( (byProfile[dwAddr] << 16) | (byProfile[dwAddr + 1] << 8) | (byProfile[dwAddr + 2] << 0)) - s_dwLedMemAddrs[nProfile];

	//int nClrCount = m_LedMemory[m_dwClrLastAddr[nProfile]];	???
	int nClrCount = m_LedMemory[s_dwLedAddrs[nProfile] - DEF_MEM_ADDR];		// peter lee 2016/7/18
	m_dwClrLastAddr[nProfile]  += nClrCount * 3 + 1;

	if(m_nClrList[nProfile] == 0xff)
	{
		m_nClrList[nProfile] = 0;
		m_dwClrLastAddr[nProfile]  = 0;
	}

	m_nClrList[nProfile]++;

	m_nClrCount = CLR_COUNT;
	ZeroMemory(m_DefineWaveIndex, sizeof(DWORD) * 5);
}

void CKbLedCtrl::ResetClrList(int nProfile)
{
	m_nClrList[nProfile] = 0;
	m_dwClrLastAddr[nProfile] = 0;
	CKbLedCtrl::DeleteDefineProfile(nProfile);
}


void CKbLedCtrl::LoadMemory()
{

	DWORD dwTime = ::GetTickCount();
	DWORD dwAddr = 0x0000;
	CXK700Cmd::MyReadByte(dwAddr, MEM_SIZE , m_Memory);
	DWORD dwTick = GetTimeElapse(dwTime);
	CString sTime;
	sTime.Format(_T("used %.2f s to load memory\n"), dwTick / 1000.0);
	TRACE(sTime);
}

void CKbLedCtrl::GetMarcoList(GVORDER_MACROS_ATTR lstmacros[], int nCount)
{
	DWORD dwAddr = 0x10100; // XK700 Marco屬性存儲起始地址
	GvOrderGetMacrosListFromByte(&m_Memory[dwAddr], lstmacros, nCount);
}

void CKbLedCtrl::SetMacrosKey(GVORDER_MACROS macros)
{
	DWORD dwMarcoAddr = 0x2000;
	DWORD dwAttrAddr = 0x10100;
	int nIndex = macros.nIndex;
	BYTE* byUnits = &m_Memory[dwMarcoAddr + nIndex * 0x240];
	BYTE* byAttr = &m_Memory[dwAttrAddr + nIndex * 0x10];

	GvOrderSetMacrosToByte(byUnits, byAttr, macros);

	DWORD dwAddr = (dwMarcoAddr - 0x2000) / 0x1000 * 0x1000 + 0x2000;

	CXK700Cmd::Write4KByte(&m_Memory[dwAddr], dwAddr);
	dwAddr = 0x10000;
	CXK700Cmd::Write4KByte(&m_Memory[dwAddr], dwAddr); // 0xf740 = 0x10740 - 0x1000, 
	
}

void CKbLedCtrl::GetMacrosKey(GVORDER_MACROS& macros)
{
	DWORD dwMarcoAddr = 0x2000;
	DWORD dwAttrAddr = 0x10100;
	int nIndex = macros.nIndex;
	BYTE* byUnits = &m_Memory[dwMarcoAddr + nIndex * 0x240];
	BYTE* byAttr = &m_Memory[dwAttrAddr + nIndex * 0x10];

	GvOrderGetMacrosFromByte(byUnits, byAttr, macros);

	macros.nIndex = nIndex;
}

void CKbLedCtrl::SetKeyFun(GVORDER_KEYFUN fnkey)
{
	BYTE byKey[10];
	GvOrderSetKeyFunToByte(byKey, fnkey);

	if (fnkey.fnType == GVORDER_FUN_MACROSONCE
		|| fnkey.fnType == GVORDER_FUN_MACROSLOOP	
		|| fnkey.fnType == GVORDER_FUN_MACROCSFIRE)
	{
		DWORD dwMarcoAddr = 0x2000;
		dwMarcoAddr = dwMarcoAddr + fnkey.value.macros.macrosIndex * 0x240;
		byKey[1] = ADDRH(dwMarcoAddr);
		byKey[2] = ADDRM(dwMarcoAddr);
		byKey[3] = ADDRL(dwMarcoAddr);
	}




	int nProfile = fnkey.nProfile;
	int nKeyIndex = fnkey.nIndex;
	nKeyIndex = nKeyIndex / 0x10 * 0x40 + nKeyIndex % 0x10;

	nKeyIndex += s_dwProAddrs[nProfile];

	int nTypeAddr = nKeyIndex + 0x80 ;
	int nData1Addr = nTypeAddr + 0x10;
	int nData2Addr = nData1Addr + 0x10 ;
	int nData3Addr = nData2Addr + 0x10;
	m_Memory[nTypeAddr]  = byKey[0];
	m_Memory[nData1Addr] = byKey[1];
	m_Memory[nData2Addr] = byKey[2];
	m_Memory[nData3Addr] = byKey[3];

	CXK700Cmd::Write4KByte(m_Memory, 0);

	if(0 <= nProfile && nProfile < 5)
	{
		CXK700Cmd::SetLEDStatus(true);
		CXK700Cmd::SwitchProfile(nProfile);
		CXK700Cmd::SetLEDStatus(true);
		CXK700Cmd::SwitchProfile(nProfile);//解決設置KEYASSIGN燈滅的問題和設置完不生效的問題
		CXK700Cmd::SetLEDStatus(true);

	}
}

void CKbLedCtrl::SetKeyFunToDefault(int nProfile)
{
	BYTE* byData = &m_Memory[s_dwProAddrs[nProfile] + 0x80];
	memset(byData, 0xff, 0x200); // 重置所有按鍵設置

	CXK700Cmd::Write4KByte(m_Memory, 0);

	if(0 <= nProfile && nProfile < 5) CXK700Cmd::SwitchProfile(nProfile);
}

void CKbLedCtrl::GetKeyFun(GVORDER_KEYFUN& fnkey)
{
	int nProfile = fnkey.nProfile;
	int nKeyIndex = fnkey.nIndex;
	/*
	┌──────┬──────┬──────┐
	│ type │ type │ ...  │
	├──────┼──────┼──────┤
	│ opt1 │ opt1 │ ...  │
	├──────┼──────┼──────┤
	│ opt2 │ opt2 │ ...  │
	├──────┼──────┼──────┤
	│ opt3 │ opt3 │ ...  │
	├──────┼──────┼──────┤
	│ type │ type │ ...  │
	├──────┼──────┼──────┤
	│ opt1 │ opt1 │ ...  │
	├──────┼──────┼──────┤
	│ opt2 │ opt2 │ ...  │
	├──────┼──────┼──────┤
	│ opt3 │ opt3 │ ...  │
	└──────┴──────┴──────┘

	\*	轉換實際Key fun起始位置， 每個key fun結構如上 */

	nKeyIndex = nKeyIndex / 0x10 * 0x40 + nKeyIndex % 0x10;
	DWORD dwAddrs[] = {
		0x0000,
		0x0280,	
		0x0500,	
		0x0780,	
		0x0a00,	
		0x0c80,	
		0x1000,	
		0x1280,	
		0x1500,	
		0x1780,	
	};

	BYTE byKey[4] = { 0xff, 0xff, 0xff, 0xff };
	nKeyIndex += dwAddrs[nProfile];

	int nTypeAddr = nKeyIndex + 0x80 ;
	int nData1Addr = nTypeAddr + 0x10;
	int nData2Addr = nData1Addr + 0x10;
	int nData3Addr = nData2Addr + 0x10;

	byKey[0] = m_Memory[nTypeAddr] ;
	byKey[1] = m_Memory[nData1Addr];
	byKey[2] = m_Memory[nData2Addr];
	byKey[3] = m_Memory[nData3Addr];

	GvOrderGetKeyFunFromByte(byKey, fnkey);

	if (fnkey.fnType == GVORDER_FUN_MACROSONCE
		|| fnkey.fnType == GVORDER_FUN_MACROSLOOP	
		|| fnkey.fnType == GVORDER_FUN_MACROCSFIRE)
	{
		DWORD dwMarcoAddr = (byKey[1] << 16) | (byKey[2] << 8) | (byKey[3] << 0);
		fnkey.value.macros.macrosIndex = (WORD)((dwMarcoAddr - 0x2000) / 0x240);
	}

	fnkey.nProfile = nProfile;
}

void CKbLedCtrl::GetSelItem(/* out */bool bSels[KEY_ROW][KEY_COL], /* in */bool bStatus[], int nCount)
{
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KeyId[m][n] == 0 || s_KeyId[m][n] > nCount) continue;
			int nIndex = s_KeyId[m][n] - 1;
			bSels[m][n] = bStatus[nIndex];
		}
	}
}

void CKbLedCtrl::ToConsistent(bool bStatus[], COLORREF clr, int nBright, int nSpeed, bool bOn, int nProfile)
{
	GetSelItem(s_KEYSel, bStatus);
	int nClrList = m_nClrList[nProfile];

	if(m_bIsKeyType)
		nClrList = m_nKTClrList;

	int nTimer = 1000;



	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(!s_KEYSel[m][n]) continue;
			s_KEYClr[m][n] = 0;
			s_KEYClrList[m][n] = nClrList;
			s_KEYLight[m][n] = 0;
			s_KEYSpeed[m][n] = nSpeed;
		}
	}

	s_lstClr[nClrList].nCount = 1;
	for (int i = 0; i < 1; i++)
	{
		if(bOn)
		{
			int r = GetRValue(clr);
			int g = GetGValue(clr);
			int b =  GetBValue(clr);
			s_lstClr[nClrList].lstClr[i] = RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
		}
		else
		{
			s_lstClr[nClrList].lstClr[i] = 0;
		}
	}
	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToPulsing(bool bStatus[], COLORREF clr1, COLORREF clr2, int nBright, int nSpeed, bool bRandom, bool bOn, int nProfile)
{
	GetSelItem(s_KEYSel, bStatus);
	int nClrList = m_nClrList[nProfile];

	if(m_bIsKeyType)
		nClrList = m_nKTClrList;

	int nTimer = 100;
	int nClrCount = (bRandom ? 7 : 2);
	if(bRandom) m_nClrCount = 126;
	else m_nClrCount = 63;
	float Operity = (float)(nBright / 10.0 / m_nClrCount * 2.0 * nClrCount);
	COLORREF lstclr[7] = { 
		RGB(255,   0,   0),
		RGB(255,  90,   0),
		RGB(255, 200,   0),
		RGB(  0, 255,   0),
		RGB(  0, 255, 255),
		RGB(  0,   0, 255),
		RGB(255,   0, 255),
	};
	if (!bRandom)
	{
		lstclr[0] = clr1;
		lstclr[1] = clr2;
	}

	if(!bOn)
	{
		nBright = 0;
	}

	for (int j = 0; j < nClrCount; j++)
	{
		for (int i = 0; i <= m_nClrCount / nClrCount / 2; i++)
		{
			s_lstClr[nClrList].lstClr[i + j * m_nClrCount / nClrCount] = RGB(
				GetRValue(lstclr[j]) * (i) * Operity * nBright * 0.1, 
				GetGValue(lstclr[j]) * (i) * Operity * nBright * 0.1, 
				GetBValue(lstclr[j]) * (i) * Operity * nBright * 0.1
				);
			s_lstClr[nClrList].lstClr[m_nClrCount / nClrCount - i + j * m_nClrCount / nClrCount] = RGB(
				GetRValue(lstclr[j]) * (i) * Operity * nBright * 0.1, 
				GetGValue(lstclr[j]) * (i) * Operity * nBright * 0.1, 
				GetBValue(lstclr[j]) * (i) * Operity * nBright * 0.1
				);
		}
	}
	s_lstClr[nClrList].nCount = m_nClrCount;

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nSpeed;
		}
	}
	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToReactive(bool bStatus[], COLORREF clr, int nSpeed, int nProfile)
{
	GetSelItem(s_KEYSel, bStatus);

	byte p1 = GetRValue(clr);
	byte p2 = GetGValue(clr);
	byte p3 = GetBValue(clr);
	byte p4 = 192 + nSpeed; //b110 1  bbbb   type off_on  speed  
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = p2;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = p1 - 1;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = p4;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = p3;
		}
	}
	ToByte(0, 0, 0, nSpeed, nProfile);
}

void CKbLedCtrl::ToRipple(bool bStatus[], int nWidth, int nStart, int nTimes, COLORREF clrs[], int nCount, int nSpeed, int nProfile, bool bOn)
{
	GetSelItem(s_KEYSel, bStatus);
	if(m_isReadLedMem == FALSE)
	{
		m_isReadLedMem = TRUE;
		CXK700Cmd::MyReadByte(0x20000, MEM_SIZE , m_LedMemory);
		Sleep(500);
	}	

	int nClrList = m_nClrList[nProfile];
	int Index = 0;
	

	if(m_bIsKeyType)
		nClrList = m_nKTClrList;



	BYTE* LEDMEM;

	DWORD *dwClrLasAddr = 0;

	if(m_bIsKeyType)
	{

		LEDMEM = m_LedMemoryKT;

	}
	else
	{
		//LEDMEM = &m_LedValueMemory[s_dwLedAddrs[nProfile] - LED_START_MEM_ADDR];
		LEDMEM = &m_LedMemory[s_dwRippleMemAddrs[nProfile] - DEF_MEM_ADDR];		// Peter Lee 2016/7/26
	}



	byte p1 = (byte)m_DefineRippleIndex[nProfile];    //flag
	//byte p2 = ADDRM(m_dwDefineRippleLastAddr);   //M Addr
	//byte p3 = ADDRL(m_dwDefineRippleLastAddr);    //L Addr
	byte p2 = 0;   //M Addr
	byte p3 = 0;    //L Addr
	byte p4 = 240;  //0b1111 0000



	if(!m_bIsKeyType)
		m_DefineRippleIndex[nProfile]++; //flag: 0 ~ 4  

	if(m_DefineRippleIndex[nProfile] > 4)
	{
		m_DefineRippleIndex[nProfile] = 0;
	}



	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = p2;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = p1 - 1;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = p4;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = p3;
		}
	}

	//BYTE* byClrList  = &LEDMEM[0xF60];
	BYTE* byClrList  = LEDMEM;	// Peter Lee 2016/7/26

	int nIndex =  p1 * 0x20;

	byClrList[nIndex++] = nCount;

	for(int i =0; i < 7; i++)
	{

		int r = GetRValue(clrs[i]);
		int g = GetGValue(clrs[i]);
		int b = GetBValue(clrs[i]);

		if(bOn)
		{
			byClrList[nIndex++] = r;
			byClrList[nIndex++] =g;
			byClrList[nIndex++] =b;
		}
		else
		{
			byClrList[nIndex++] = 0;
			byClrList[nIndex++] = 0;
			byClrList[nIndex++] = 0;
		}
	}


	byClrList[nIndex++] = nWidth;
	byClrList[nIndex++] = nStart;
	byClrList[nIndex++] = nTimes;
	byClrList[nIndex++] = nSpeed - 1;


	ToByte(0, 100, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToCycling(bool bStatus[], int nBright, int nSpeed, bool bOn, int nProfile)
{
	GetSelItem(s_KEYSel, bStatus);
	int nClrList = m_nClrList[nProfile];

	if(m_bIsKeyType)
		nClrList = m_nKTClrList;

	int nTimer = 100;
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] =  nSpeed;
		}
	}

	if(!bOn) nBright = 0;
	else nBright = nBright;

	s_lstClr[nClrList].nCount = 128;
	for (int i = 0; i < s_lstClr[nClrList].nCount; i++)
	{
		COLORREF clr = HSBToRGB(i * (360.0 / s_lstClr[nClrList].nCount));
		s_lstClr[nClrList].lstClr[i] = RGB(nBright / 10.0 * GetRValue(clr), nBright / 10.0 * GetGValue(clr), nBright / 10.0 * GetBValue(clr));
	}
	ToByte(s_lstClr[nClrList].nCount, 100, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToWave(bool bStatus[], int nAngle, COLORREF clr[], int nCount, bool bOn, int nBright, int nSpeed, int nProfile)
{
	int nClr = 0;
	GetSelItem(s_KEYSel, bStatus);
	int nClrList = m_nClrList[nProfile];


	if(m_bIsKeyType)
		nClrList = m_nKTClrList;

	int nTimer = 50;
	for (int cot = 0; cot < nCount - 1 && bOn;cot++)
	{
		COLORREF clr1, clr2;

		if(nCount == 1)
		{
			clr1 = RGB(nBright / 10.0 * GetRValue(clr[cot]), nBright / 10.0 * GetGValue(clr[cot]), nBright / 10.0 * GetBValue(clr[cot]));
			clr2 = RGB(nBright / 10.0 * GetRValue(clr[cot]), nBright / 10.0 * GetGValue(clr[cot]), nBright / 10.0 * GetBValue(clr[cot]));
			FormToColor(clr1, clr2, CLR_COUNT/nCount, &s_lstClr[nClrList].lstClr[cot * CLR_COUNT/nCount]);
		}
		else
		{
			clr1 = RGB(nBright / 10.0 * GetRValue(clr[cot]), nBright / 10.0 * GetGValue(clr[cot]), nBright / 10.0 * GetBValue(clr[cot]));
			clr2 = RGB(nBright / 10.0 * GetRValue(clr[cot + 1]), nBright / 10.0 * GetGValue(clr[cot + 1]), nBright / 10.0 * GetBValue(clr[cot + 1]));
			FormToColor(clr1, clr2, CLR_COUNT/(nCount - 1), &s_lstClr[nClrList].lstClr[cot * CLR_COUNT/nCount]);
		}
	}
	nSpeed --;

	s_lstClr[nClrList].nCount = CLR_COUNT;
	if(!bOn) ZeroMemory(s_lstClr[nClrList].lstClr, sizeof(COLORREF)* 128);


	CPoint ptCoor[KEY_ROW + KEY_COL + KEY_ROW + KEY_COL][KEY_COL + KEY_ROW + KEY_ROW + KEY_COL];
	CPoint ptSame[KEY_ROW][KEY_COL];
	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n <  KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			ptCoor[m][n] = CPoint(-1, -1);
		}
	}

	int nKEYClr[KEY_ROW][KEY_COL] = {0};
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			ptSame[m][n] = CPoint(-1, -1);
			nKEYClr[m][n] = -1;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = -1;
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = 0;
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nSpeed;
		}
	}


	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n < KEY_COL; n++)
		{
			int i = (int)(m * cos(nAngle / 180.0 * 3.14159265358979323846) - n * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			int j = (int)(n * cos(nAngle / 180.0 * 3.14159265358979323846) + m * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			if(i < 0 || j < 0) continue;
			if(ptCoor[i][j] != CPoint(-1, -1)) 
				ptSame[m][n] = ptCoor[i][j];
			else ptCoor[i][j] = CPoint(m, n);
		}
	}

	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			if(ptCoor[m][n] == CPoint(-1, -1)) continue;
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr, nKEYClr);
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr);
		}
		nClr++;
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(ptSame[m][n] == CPoint(-1, -1)) continue;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = nKEYClr[ptSame[m][n].x][ptSame[m][n].y];
		}
	}

#ifdef XK700_105
	//0 1 K45

	if(s_KEYSel[0][1])  //同步成周围四个键值的LED
	{
		if(s_KEYSel[3][0]) 
		{
			s_KEYClr[0][1] = s_KEYClr[3][0];
		}
		else if(s_KEYSel[4][0])
			s_KEYClr[0][1] = s_KEYClr[4][0];
		else if(s_KEYSel[4][1])
			s_KEYClr[0][1] = s_KEYClr[4][1];
		else if(s_KEYSel[5][1])
			s_KEYClr[0][1] = s_KEYClr[5][1];

	}
#endif

	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToWave(bool bStatus[], int nAngle, COLORREF clr[], int nCount, bool bOn, int nBright, int nSpeed, int start, int time, int nProfile)
{
	int nClr = 0;
	GetSelItem(s_KEYSel, bStatus);

	int nClrList = m_nClrList[nProfile];


	if(m_bIsKeyType)
		nClrList = m_nKTClrList;

	BYTE waveType = 0;
	BYTE times = time;

	if(start == 1)
	{
		waveType = 176; // 101  1
	}
	else
	{
		waveType = 160; // 101  0
	}

	m_DefineWaveIndex[nProfile]++;

	if(m_DefineWaveIndex[nProfile] > 15)
		m_DefineWaveIndex[nProfile] = 0;


	int nTimer = 50;
	for (int cot = 0; cot < nCount - 1 && bOn;cot++)
	{
		COLORREF clr1, clr2;

		if(nCount == 1)
		{
			clr1 = clr[cot];
			clr2 = clr[cot];
			FormToColor(clr1, clr2, CLR_COUNT/nCount, &s_lstClr[nClrList].lstClr[cot * CLR_COUNT/nCount]);
		}
		else
		{
			clr1 = clr[cot];
			clr2 = clr[cot + 1];
			FormToColor(clr1, clr2, CLR_COUNT/(nCount - 1), &s_lstClr[nClrList].lstClr[cot * CLR_COUNT/nCount]);
		}
	}
	nSpeed --;

	s_lstClr[nClrList].nCount = CLR_COUNT;
	if(!bOn) ZeroMemory(s_lstClr[nClrList].lstClr, sizeof(COLORREF)* 128);
	s_lstClr[nClrList].nCount = CLR_COUNT;

	CPoint ptCoor[KEY_ROW + KEY_COL + KEY_ROW + KEY_COL][KEY_COL + KEY_ROW + KEY_ROW + KEY_COL];
	CPoint ptSame[KEY_ROW][KEY_COL];
	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n <  KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			ptCoor[m][n] = CPoint(-1, -1);
		}
	}

	int nKEYClr[KEY_ROW][KEY_COL] = {0};
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			ptSame[m][n] = CPoint(-1, -1);
			nKEYClr[m][n] = -1;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = -1;  //p2
			if(s_KEYSel[m][n]) s_KEYClrList[m][n] = nClrList;   //p1
			if(s_KEYSel[m][n]) s_KEYLight[m][n] = waveType + times;   //p4
			if(s_KEYSel[m][n]) s_KEYSpeed[m][n] = nSpeed + m_DefineWaveIndex[nProfile] << 4;  //p3
		}
	}

	// 旋轉矩陣
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n < KEY_COL; n++)
		{
			int i = (int)(m * cos(nAngle / 180.0 * 3.14159265358979323846) - n * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			int j = (int)(n * cos(nAngle / 180.0 * 3.14159265358979323846) + m * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			if(i < 0 || j < 0) continue;
			if(ptCoor[i][j] != CPoint(-1, -1)) 
				ptSame[m][n] = ptCoor[i][j];
			else ptCoor[i][j] = CPoint(m, n);
		}
	}

	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			if(ptCoor[m][n] == CPoint(-1, -1)) continue;
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr, nKEYClr);
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr);
		}
		nClr++;
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(ptSame[m][n] == CPoint(-1, -1)) continue;
			if(s_KEYSel[m][n]) s_KEYClr[m][n] = nKEYClr[ptSame[m][n].x][ptSame[m][n].y];
		}
	}


#ifdef K105 //105
	//0 1 K45

	if(s_KEYSel[0][1])  //同步成周围四个键值的LED
	{
		if(s_KEYSel[3][0]) 
		{
			s_KEYClr[0][1] = s_KEYClr[3][0];
		}
		else if(s_KEYSel[4][0])
			s_KEYClr[0][1] = s_KEYClr[4][0];
		else if(s_KEYSel[4][1])
			s_KEYClr[0][1] = s_KEYClr[4][1];
		else if(s_KEYSel[5][1])
			s_KEYClr[0][1] = s_KEYClr[5][1];

	}
#endif

	ToByte(s_lstClr[nClrList].nCount, nTimer, nClrList, nSpeed, nProfile);
}

void CKbLedCtrl::ToByte(int nClrCount, int nTimer, int nClrIndex, int nSpeed, int nProfile)
{
	if(m_isReadLedMem == FALSE)
	{
		m_isReadLedMem = TRUE;
		CXK700Cmd::MyReadByte(0x20000, MEM_SIZE , m_LedMemory);
		Sleep(500);
	}	


	if(m_isReadValueMem == FALSE)
	{
		m_isReadValueMem = TRUE;
		CXK700Cmd::MyReadByte(0x30000, MEM_SIZE , m_LedValueMemory);
		Sleep(500);
	}


	BYTE* LEDMEM;
	BYTE* LEDKEYMEM;
	const int BLOCK = 64 * 64;
	// 顔色列表起始地址
	DWORD dwClrAddr;
	BYTE* byClrList;
	DWORD dwLedOffest = 0;



	DWORD *dwClrLasAddr = 0;

	if(m_bIsKeyType)
	{
		dwClrLasAddr = &m_dwKTClrLastAddr;
		LEDMEM = m_LedValueMemoryKT;
		LEDKEYMEM = m_LedMemoryKT;
	}
	else
	{
		dwClrLasAddr = &m_dwClrLastAddr[nProfile];
		LEDMEM = &m_LedValueMemory[s_dwLedMemAddrs[nProfile] - LED_START_MEM_ADDR];
		LEDKEYMEM = &m_LedMemory[s_dwLedAddrs[nProfile] - DEF_MEM_ADDR];
	}

	dwClrAddr = *dwClrLasAddr + s_dwLedMemAddrs[nProfile];

	
	if(dwClrAddr > s_dwLedMemAddrs[nProfile] + 0x2000)
	{
		::MessageBox(NULL, _T("键盘空间已满！重新设置"), _T(""), NULL);
		m_dwClrLastAddr[nProfile] = 0;
		m_nClrList[nProfile] = 0;
		dwClrAddr =  s_dwLedMemAddrs[nProfile];
		DeleteDefineProfile(nProfile);
		return ;
	}
	else if(dwClrAddr > s_dwLedMemAddrs[nProfile] + 0x1000)
	{
		dwLedOffest = 0x1000;
		//LEDMEM = &m_LedValueMemory[s_dwLedMemAddrs[nProfile] - LED_START_MEM_ADDR + dwLedOffest];
	}
	

	
	byClrList = LEDMEM;

	byClrList[*dwClrLasAddr] = nClrCount;
	int nIndex = *dwClrLasAddr + 1;

	// 生成Clr List 1
	for(int i = 0; i < nClrCount; i++)
	{
		byClrList[nIndex++] = GetRValue(s_lstClr[nClrIndex].lstClr[i]);
		byClrList[nIndex++] = GetGValue(s_lstClr[nClrIndex].lstClr[i]);
		byClrList[nIndex++] = GetBValue(s_lstClr[nClrIndex].lstClr[i]);
	}


	*dwClrLasAddr += nClrCount * 3 + 1;



	//BYTE* byKey = &LEDKEYMEM[s_dwLedAddrs[nProfile] - DEF_MEM_ADDR];		bug
	BYTE* byKey = LEDKEYMEM;		// 2016/7/18



	nIndex = 0x180;
	if(m_bIsKeyType)
		byKey[0] = (BYTE)m_nKTClrList;
	else
		byKey[0] = m_nClrList[nProfile];
	byKey[1 + nClrIndex * 3] = ADDRH(dwClrAddr);
	byKey[2 + nClrIndex * 3] = ADDRM(dwClrAddr);
	byKey[3 + nClrIndex * 3] = ADDRL(dwClrAddr);

	for (int i = KEY_ROW - 1; i >= 0; i--)
	{
		int nCount = 0;
		for (int j = 0; j < KEY_COL; j++)
		{

			if(!s_KEYSel[i][j])
			{
				nIndex+= 4;
				nCount++;
				continue;

			}

			byKey[nIndex++] = (BYTE)(s_KEYClrList[i][j] + 1);
			byKey[nIndex++] = s_KEYClr[i][j];
			byKey[nIndex++] = s_KEYSpeed[i][j];
			byKey[nIndex++] = s_KEYLight[i][j];
			nCount++;
			if(nIndex >= BLOCK)
			{
				//AfxMessageBox(_T("超出索引!"));
				break;
			}
		}
		for (int j = nCount; j < 21; j++)
		{
			byKey[nIndex++] = 0;
			byKey[nIndex++] = 0;
			byKey[nIndex++] = 0;
		}
	}
	// ?入Profile1 ~ 5

	if(!m_bIsSave)
	{
		/*if(dwClrAddr > s_dwLedMemAddrs[nProfile] + 0x1000)
		{
			CXK700Cmd::Write4KByte(&LEDMEM[0x1000], s_dwLedMemAddrs[nProfile] + dwLedOffest);
		}
		else
		{
			CXK700Cmd::Write4KByte(LEDMEM, s_dwLedMemAddrs[nProfile] + dwLedOffest);
		}*/
		CXK700Cmd::Write4KByte(LEDMEM, s_dwLedMemAddrs[nProfile]);		// first 0x1000
		CXK700Cmd::Write4KByte(&LEDMEM[0x1000], s_dwLedMemAddrs[nProfile] + 0x1000);	// 2nd 0x1000

		Sleep(100);
		CXK700Cmd::Write4KByte(LEDKEYMEM, s_dwLedAddrs[nProfile]);
	}

	m_bIsSave = false;  //下次ToByte到设备上，除非又要合并操作


	if(m_bIsKeyType)
		m_nKTClrList++;
	else
		m_nClrList[nProfile]++;

	if(m_nClrList[nProfile] == 0xff)
		m_nClrList[nProfile] = 0;

	m_nClrCount = CLR_COUNT;
}




void CKbLedCtrl::Wave(int nProfile, int nAngle, int nClr, int nBright, int nSpeed, COLORREF clr[], int nCount)
{
	BYTE* byDefault = &m_LedMemory[0x15000 - 0x10000];

	DWORD	dwIndex =  0x560;

	dwIndex += 128 * nProfile;

	GetWaveByte(270 - nAngle, &byDefault[dwIndex]); 

	dwIndex =  0x7E0;

	dwIndex += 112 * nProfile;
	byDefault[dwIndex++] = 0x20;


	for (int cot = 0; cot < nCount;cot++)
	{
		COLORREF clr1, clr2;

		if(nCount == 1)
		{
			clr1 = clr[cot];
			clr2 = clr[cot];
			FormToColor(clr1, clr2, CLR_COUNT / nCount, byDefault, &dwIndex);
		}
		else
		{
			clr1 = clr[cot];
			clr2 = clr[cot + 1];
			FormToColor(clr1, clr2, CLR_COUNT / (nCount - 1), byDefault, &dwIndex);
		}
	}

	for(int i = 0; i < CLR_COUNT % nCount; i++)
	{
		COLORREF c = clr[nCount - 1];
		byDefault[dwIndex++] = GetRValue(c);
		byDefault[dwIndex++] = GetGValue(c);
		byDefault[dwIndex++] = GetBValue(c);
	}

	CXK700Cmd::Write4KByte(byDefault, 0x15000);

}

void CKbLedCtrl::GetWaveByte(int nAngle, BYTE* byMem)
{
	int nClr = 0, nIndex = 0;
	CPoint ptCoor[KEY_ROW + KEY_COL + KEY_ROW + KEY_COL][KEY_COL + KEY_ROW + KEY_ROW + KEY_COL];
	CPoint ptSame[KEY_ROW][KEY_COL];
	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n <  KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			ptCoor[m][n] = CPoint(-1, -1);
		}
	}

	int nKEYClr[KEY_ROW][KEY_COL] = {0};
	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			ptSame[m][n] = CPoint(-1, -1);
			nKEYClr[m][n] = -1;
		}
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n < KEY_COL; n++)
		{
			int i = (int)(m * cos(nAngle / 180.0 * 3.14159265358979323846) - n * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			int j = (int)(n * cos(nAngle / 180.0 * 3.14159265358979323846) + m * sin(nAngle / 180.0 * 3.14159265358979323846) + KEY_COL);
			if(i < 0 || j < 0) AfxMessageBox(_T("Warning"));
			if(ptCoor[i][j] != CPoint(-1, -1)) 
				ptSame[m][n] = ptCoor[i][j];
			else 
				ptCoor[i][j] = CPoint(m, n);
		}
	}

	for (int m = 0; m < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; m++)
	{
		for (int n = 0; n < KEY_ROW + KEY_COL + KEY_ROW + KEY_COL; n++)
		{
			if(ptCoor[m][n] == CPoint(-1, -1)) continue;
			SetClr(ptCoor[m][n].x, ptCoor[m][n].y, nClr, nKEYClr);
		}
		nClr++;
	}

	for (int m = 0; m < KEY_ROW; m++)
	{
		for (int n = 0; n <  KEY_COL; n++)
		{
			if(ptSame[m][n] == CPoint(-1, -1)) continue;
			nKEYClr[m][n] = nKEYClr[ptSame[m][n].x][ptSame[m][n].y];
		}
	}

	for (int i = KEY_ROW - 1; i >= 0; i--)
	{
		int nCount = 0;
		for (int j = 0; j < KEY_COL; j++)
		{
			byMem[nIndex++] = nKEYClr[i][j];
		}
	}
}

void CKbLedCtrl::FormToColor(COLORREF from, COLORREF to, int count, BYTE* byDefault, DWORD *Index)
{
	for(int i = 1; i <= count; i++)
	{
		int r = 0,g = 0, b = 0, fromR, toR, fromG, toG, fromB, toB;

		fromR = GetRValue(from);
		toR = GetRValue(to);

		fromG = GetGValue(from);
		toG = GetGValue(to);

		fromB = GetBValue(from);
		toB = GetBValue(to);

		if(fromR > toR )
		{
			r = fromR - i * (fromR - toR) / count;
		}
		else
		{
			r = fromR + i * (toR - fromR) / count;
		}

		if(fromG > toG )
		{
			g = fromG - i * (fromG - toG) / count;
		}
		else
		{
			g = fromG + i * (toG - fromG) / count;
		}

		if(fromB > toB )
		{
			b = fromB - i * (fromB - toB) / count;
		}
		else
		{
			b = fromB + i * (toB - fromB) / count;
		}

		byDefault[(*Index)++] = r;
		byDefault[(*Index)++] = g;
		byDefault[(*Index)++] = b;
	}
}

void CKbLedCtrl::FormToColor(COLORREF from, COLORREF to, int count, COLORREF clr[])
{
	for(int i = 1; i <= count; i++)
	{
		int r = 0,g = 0, b = 0, fromR, toR, fromG, toG, fromB, toB;

		fromR = GetRValue(from);
		toR = GetRValue(to);

		fromG = GetGValue(from);
		toG = GetGValue(to);

		fromB = GetBValue(from);
		toB = GetBValue(to);

		if(fromR > toR )
		{
			r = fromR - i * (fromR - toR) / count;
		}
		else
		{
			r = fromR + i * (toR - fromR) / count;
		}

		if(fromG > toG )
		{
			g = fromG - i * (fromG - toG) / count;
		}
		else
		{
			g = fromG + i * (toG - fromG) / count;
		}

		if(fromB > toB )
		{
			b = fromB - i * (fromB - toB) / count;
		}
		else
		{
			b = fromB + i * (toB - fromB) / count;
		}

		clr[i] = RGB(r, g, b);
	}
}

bool CKbLedCtrl::SetClr(int i, int j, int nClr, int nKey[KEY_ROW][KEY_COL])
{
	if(i < 0 || j < 0 || i >= KEY_ROW || j >= KEY_COL || nKey[i][j] > 0) return false;
	nKey[i][j] = (CLR_COUNT - nClr % CLR_COUNT);
	return true;
}

bool CKbLedCtrl::SetClr(int i, int j, int nClr)
{
	if(i < 0 || j < 0 || i >= KEY_ROW || j >= KEY_COL || s_KEYClr[i][j] > 0) return false;
	s_KEYClr[i][j] = (CLR_COUNT - nClr % CLR_COUNT);
	return true;
}

bool CKbLedCtrl::SaveMemery(int nProfile, CString filename)
{

	if(filename.IsEmpty())
		return false;


	BYTE* LEDMEM;
	BYTE* LEDKEYMEM;

	if(filename.Find(_T("USERDEFINE")) < 0)
	{
		LEDKEYMEM = CKbLedCtrl::m_LedMemoryKT;
		LEDMEM = CKbLedCtrl::m_LedValueMemoryKT;
	}
	else
	{
		LEDKEYMEM = &CKbLedCtrl::m_LedMemory[s_dwLedAddrs[nProfile] - DEF_MEM_ADDR];
		LEDMEM = &CKbLedCtrl::m_LedValueMemory[s_dwLedMemAddrs[nProfile] - LED_START_MEM_ADDR];
	}

	CFile file;
	BYTE byMemory[10240] = "";


	//Create Directory
	CString szPathLedMem = GetCfgPath(nProfile);

	CreateDir(szPathLedMem);


	szPathLedMem += filename + _T(".bin");

	//写入键盘对应LED数据(addr = 0x11000)
	if(!file.Open(szPathLedMem, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite))
	{
		return false;
	}



	file.Write(LEDKEYMEM, 4096);
	

	file.Close();


	//写入LED值的数据(addr = 0x18000)
	szPathLedMem = GetCfgPath(nProfile) + filename + _T("LED.bin");


	if(!file.Open(szPathLedMem, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite))
	{
		return false;
	}


	file.Write(LEDMEM, 8192);

	file.Close();

	return true;
}

bool CKbLedCtrl::ReadMemeryToSet(int nProfile, CString filename)
{
	if(filename.IsEmpty())
		return false;

	CString szPathLedMem = _T("");
	CFile file;
	BYTE byLedMemory[8192] = "";
	BYTE byLedValueMemory[8192] = "";
	BYTE byRippleMemory[8192] = "";
	szPathLedMem = GetCfgPath(nProfile) + filename + _T(".bin");

	if(!file.Open(szPathLedMem, CFile::typeBinary | CFile::modeRead))
	{
		return false;
	}

	file.Read(byLedMemory, 8192);
	file.Close();	


	CXK700Cmd::Write4KByte(byLedMemory, s_dwLedAddrs[nProfile]);



	szPathLedMem = GetCfgPath(nProfile) + filename + _T("LED.bin");

	if(!file.Open(szPathLedMem, CFile::typeBinary | CFile::modeRead))
	{
		return false;
	}

	file.Read(byLedValueMemory, 4096);
	file.Close();	
	Sleep(100);
	CXK700Cmd::Write4KByte(byLedValueMemory, s_dwLedMemAddrs[nProfile]);

	//Sleep(100);
	//CXK700Cmd::Write4KByte(&byLedValueMemory[4096], s_dwLedMemAddrs[nProfile]);

	return true;
}

void CKbLedCtrl::EnableKeyType(bool keyType)
{
	m_bIsKeyType = keyType;          //设置键盘类型，使用m_dwKTClrLastAddr
	m_dwKTClrLastAddr = 0;     
	m_nKTClrList = 0;
	m_dwKTRippleLastAddr = 0;

	if(keyType)
	{
		int i;

		for( i=0 ; i < 0x1000; i++)
		{
			m_LedMemoryKT[i] = 0; 
			m_LedValueMemoryKT[i] = 0;
			m_RippleMemoryKT[i] = 0;
		}
		for(; i < 0x2000; i++)
		{
			m_LedMemoryKT[i] = 0; 

		}
	}

}
void CKbLedCtrl::DeleteDefineProfile(int nProfile)
{
	CString szPathLedMem = _T("");

	CString filename("USERDEFINE");

	szPathLedMem = GetCfgPath(nProfile) + filename + _T(".bin");
	::DeleteFile(szPathLedMem);
	szPathLedMem = GetCfgPath(nProfile) + filename + _T("LED.bin");
	::DeleteFile(szPathLedMem);
	szPathLedMem = GetCfgPath(nProfile) + filename + _T("RIP") + _T(".bin");
	::DeleteFile(szPathLedMem);

}

void CKbLedCtrl::DeleteProfile(int nProfile)
{
	DeleteDirectory(GetCfgPath(nProfile));
}


void CKbLedCtrl::Default(BYTE nProfile)
{

	CXK700Cmd::WireDefault(nProfile);
	DeleteProfile(nProfile);

	if(0 <= nProfile && nProfile < 5)
	{
		CXK700Cmd::SetLEDStatus(true);
		CXK700Cmd::SwitchProfile(nProfile);
		CXK700Cmd::SetLEDStatus(true);
		CXK700Cmd::SwitchProfile(nProfile);//解決設置KEYASSIGN燈滅的問題和設置完不生效的問題
		CXK700Cmd::SetLEDStatus(true);
	}

}

void CKbLedCtrl::DeleteDirectory(CString directory_path)   //删除一个文件夹下的所有内容  
{     
    CFileFind finder;  
    CString path;  
    path.Format(_T("%s/*.*"),directory_path);  
    BOOL bWorking = finder.FindFile(path);  
    while(bWorking){  
        bWorking = finder.FindNextFile();  
        if(finder.IsDirectory() && !finder.IsDots()){//处理文件夹  
            DeleteDirectory(finder.GetFilePath()); //递归删除文件夹  
            RemoveDirectory(finder.GetFilePath());  
        }  
        else{//处理文件  
            DeleteFile(finder.GetFilePath());  
        }  
    }  
}  

CString CKbLedCtrl::GetCfgPath(int nProfile)
{
	CString sPath = _T("");
	if(nProfile < 0) sPath.Format(_T("%sGvCfg\\XK700\\cfg\\"), GetModuleDirectory());
	else sPath.Format(_T("%sGvCfg\\XK700\\profile%d\\"), GetModuleDirectory(), nProfile + 1);
	
	if (!PathIsDirectory(sPath))
	{
		CreateDir(sPath);
	}

	return sPath;
}
