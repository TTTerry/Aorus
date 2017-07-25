#include "StdAfx.h"
#include "NvApiTemp.h"
#include "afxmt.h"
#include "../../AORUSDlg.h"

int CVGALed::m_nLight = LED_MIN_LIGHT;
static CMutex s_Mutex = CMutex(FALSE, _T("FW_FOR_OCVGA_LED_GIGABYTE"), NULL);

static void Lock()   { s_Mutex.Lock();   }
static void Unlock() { s_Mutex.Unlock(); }

const int s_nCurve[] = { 
	 10,	 15,	 25,	 30,	 31,	 33,
	 35,	 40,	 45,	 50,	 55,
	 60,	 70,	 80,	 90,	 95,
	 100,	100,
};

static int m_nMin = 0;
static int m_nMax = 0;
int CVGALed::m_nColorIndex = 0;
bool CVGALed::m_bRandClr = false;
DWORD CVGALed::m_dwMode = LED_MODE_ON;
DWORD CVGALed::m_dwI2CAddr = 144;
int CVGALed::m_nCount = 0;

CVGALed::CVGALed(void)
{
}

CVGALed::~CVGALed(void)
{
}

bool CVGALed::SwitchMode(int nIndex, DWORD dwMode)
{
	//return false;
	if(GetVersion(nIndex) < 1.0) return false;
	GVDISP_I2C_REGADDR test = {0};

	if(Aorus()->GetVGA()->Ctrl()->GetGpuCount() == nIndex || CTRL_MODE_SLI == dwMode)
	{
		nIndex = -1;
		dwMode = CTRL_MODE_SLI;
	}
	memset(test.szRegAddr, 0, sizeof(test.szRegAddr));
	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.szRegAddr[0] = 0xAC;
	test.szRegAddr[1] = (unsigned char)dwMode;
	test.nSavePort = 142;//port;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	int res = WriteI2C(nIndex, &test);

	return true;
}

bool CVGALed::IsFanStop(int nIndex)
{
	GVDISP_I2C_REGADDR test = {0};
	test.nDDCPort = 1;
	test.nRegAddrUsed = 4;
	test.nSavePort = (unsigned char)m_dwI2CAddr;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	unsigned char buf[8];
	int res = ReadI2C(nIndex, &test, buf);
	return buf[0] < 10;
}

CString CVGALed::TranslateStatus(DWORD dwStatus)
{
	CString sStatus = _T("");

	if (dwStatus & POWER_ONE_LOW)
		sStatus += _T("Power One is too Low...  ");
	else if (dwStatus & POWER_ONE_HIGH)
		sStatus += _T("Power One is too High...  ");

	if (dwStatus & POWER_TWO_LOW)
		sStatus += _T("Power Two is too Low...  ");
	else if (dwStatus & POWER_TWO_HIGH)
		sStatus += _T("Power Two is too High...  ");

	return sStatus;
}

DWORD CVGALed::GetPowerStatus(int nIndex)
{
	GVDISP_I2C_REGADDR test = {0};
	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.nSavePort = (unsigned char)m_dwI2CAddr;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	unsigned char buf[8];
	int res = ReadI2C(nIndex, &test, buf);
	return buf[6];
}

void CVGALed::SetLed(int nIndex, DWORD dwMode, DWORD dwLED)
{
	m_bRandClr = (dwMode & LED_CLR_U) > 0 ? true : false;
	SetLed(nIndex, dwMode | dwLED);
}

void CVGALed::SetLedLight(int nIndex, DWORD dwMode, int nSpeed, int nRange, int nMinRange)
{
	GVDISP_I2C_REGADDR test = {0};

	nSpeed = nSpeed;
	if(nSpeed >= 10 || (dwMode & LED_TYPE_NONE)) nSpeed = 9;
	if(nRange >= 100) nRange = 99;

	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.nSavePort = (unsigned char)m_dwI2CAddr;//port;
	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	if (GetVersion(nIndex) >= 1.0)
	{
		test.szRegAddr[0] = 0x84;
		test.szRegAddr[1] = nMinRange;
		int res = WriteI2C(nIndex, &test);
	}

	test.szRegAddr[0] = 0x88;
	test.szRegAddr[1] = (unsigned char)dwMode;
	test.szRegAddr[2] = nSpeed;
	test.szRegAddr[3] = nRange;

	WriteI2C(nIndex, &test);
}

void CVGALed::SetLed(int nIndex, DWORD dwMode)
{
	dwMode = dwMode & 0xFF;
	m_dwMode = dwMode;
	GVDISP_I2C_REGADDR test = {0};

	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.szRegAddr[0] = (unsigned char)dwMode;
	test.nSavePort = (unsigned char)m_dwI2CAddr;//port;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

 	int res = WriteI2C(nIndex, &test);
	test.szRegAddr[0] = 0x81;
	WriteI2C(nIndex, &test);
	test.szRegAddr[0] = 0x83;
	WriteI2C(nIndex, &test);
	if (dwMode & LED_MODE_OFF)
	{
		SetLight(0, -1, nIndex + 1);
	}
}

void CVGALed::SetColor(int nIndex, int nR, int nG, int nB)
{
	//if(nR == 255 && nG == 255 && nB == 255)
	//{
	//	nR = 190;
	//	nG = 150;
	//	nB = 130;
	//}

	if (Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName.Find(_T("1080G1 GAMING")) >= 0
	 || Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName.Find(_T("1070G1 GAMING")) >= 0
	 || Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName.Find(_T("1070XTREME"))    >= 0
	 || Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sModelName.Find(_T("1080XTREME"))    >= 0)
	{ // 修掉色偏
		nG = (int)(nG * 0.5);
		nB = (int)(nB * 0.5);
	}

	GVDISP_I2C_REGADDR test = {0};

	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.szRegAddr[0] = 0x40;
	test.szRegAddr[1] = nR;
	test.szRegAddr[2] = nG;
	test.szRegAddr[3] = nB;
	test.nSavePort = (unsigned char)m_dwI2CAddr;//port;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	int res = WriteI2C(nIndex, &test);
}

// Only For 1080 & up
void CVGALed::Save(int nIndex)
{
	GVDISP_I2C_REGADDR test = {0};

	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.szRegAddr[0] = 0xAA;
	test.nSavePort = (unsigned char)m_dwI2CAddr;//port;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	int res = WriteI2C(nIndex, &test);
}

void CVGALed::SetSliType(int nType, int nIndex)
{
	GVDISP_I2C_REGADDR test = {0};

	test.nDDCPort = 1;
	test.nRegAddrUsed = 0;
	test.szRegAddr[0] = 0xCC;
	test.szRegAddr[1] = nType;
	test.nSavePort = (unsigned char)m_dwI2CAddr;//port;

	test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 

	int res = WriteI2C(-1, &test);
}

float CVGALed::GetVersion(int nGpuIndex)
{
	static float fVersion = 0;
	static bool bGet = false;
	if (!bGet)
	{
		GVDISP_I2C_REGADDR test = {0};
		unsigned char buf[8] = {0};

		test.nDDCPort = 1;
		test.nRegAddrUsed = 0;
		test.szRegAddr[0] = 0xAB;
		test.szRegAddr[1] = 0;
		test.szRegAddr[2] = 0;
		test.szRegAddr[3] = 0;
		test.nSavePort = 142;//port;
		test.nDataSize = Aorus()->GetVGA()->Ctrl()->IsNvCard() ? 4 : 3; 
		int res = ReadI2C(nGpuIndex, &test, buf);
		if(buf[0] != 0xab) res = ReadI2C(nGpuIndex, &test, buf);
		if(buf[0] == 0xab) fVersion = (float)((buf[1] >> 4) * 1.0 + (buf[1] & 0xf) * 0.1);
		bGet = true;

		//CString str;
		//str.Format(_T("ver=%f"), fVersion);
		//::MessageBox(NULL, str,NULL,MB_OK);	// peter lee 2017/4/7 test
		if(fVersion >= 1.0) m_dwI2CAddr = 142;
	}

	return fVersion;
}

DWORD CVGALed::WriteI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr) 
{
	pRegAddr->nI2cSpeed = 100;
	pRegAddr->nRegAddrUsed = 0;
	
	LogFile(_T("%d, %x, %d : %x, %x, %x, %x"), nGpuIndex, pRegAddr->nSavePort, pRegAddr->nI2cSpeed, pRegAddr->szRegAddr[0], pRegAddr->szRegAddr[1], pRegAddr->szRegAddr[2], pRegAddr->szRegAddr[3]);

	Lock();
	DWORD dwReturn = GVAPI_OK;
	if (nGpuIndex < 0 || (nGpuIndex == Aorus()->GetVGA()->Ctrl()->GetGpuCount() && GetVersion(0) > 1.0))
	{
		for (int i = 0; i < Aorus()->GetVGA()->Ctrl()->GetGpuCount(); i++)
		{
			dwReturn = GvWriteI2C(i, pRegAddr);
		}
	}
	else
	{
		dwReturn = GvWriteI2C(nGpuIndex, pRegAddr);
	}
	Sleep(100);
	Unlock();


	return dwReturn;
}

DWORD CVGALed::ReadI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr, unsigned char*  data) {

	pRegAddr->nI2cSpeed = 100;
	pRegAddr->nRegAddrUsed = 0;

	Lock();

	DWORD dwReturn = GVAPI_OK;
	if (nGpuIndex < 0)
	{
		for (int i = 0; i < Aorus()->GetVGA()->Ctrl()->GetGpuCount(); i++)
		{
			dwReturn = GvReadI2C(i, pRegAddr, data);
		}
	}
	else
	{
		dwReturn = GvReadI2C(nGpuIndex, pRegAddr, data);
	}

	Unlock();

	return dwReturn;
}

void CVGALed::SetLight(LED_SETTING setting, int nCount)
{
	if (setting.dwStyle == 0)
	{
		static int s_nCount = 0;
		SetLight(setting.nRangeMax, -1, nCount);
		setting.nSpeed = 100;
		if(s_nCount++ > 90)
		{
			ChangeClr(nCount);
			s_nCount = 0;
		}
		return;
	}
	if(setting.nRangeMin != m_nMin || m_nMax != setting.nRangeMax) m_nCount = m_nLight = setting.nRangeMin; 
	m_nMin = setting.nRangeMin;
	m_nMax = setting.nRangeMax;
	if (setting.dwStyle == 1)
	{
		SetLightBeach(nCount, setting.nSpeed, setting.nRangeMax); 
	}
	if (setting.dwStyle == 2)
	{
		SetLightFlash(nCount, setting.nSpeed, setting.nRangeMax);
	}
	if (setting.dwStyle == 3)
	{
		SetLightDoubleFlash(nCount, setting.nSpeed, setting.nRangeMax);
	}
}

void CVGALed::SetLight(int nValue, int nType, int nGpuIndex)
{
	static int nSliIndex = -1;
	if (nSliIndex < 0)
	{
		BOOL bSub = FALSE;
		for(int i = 0; i < Aorus()->GetVGA()->Ctrl()->GetGpuCount(); i++)
		{
			GvIsSLILight(i, bSub);
			if(bSub)
			{
				nSliIndex = i;
				break;
			}
		}
	}

	CString sValue;
	sValue.Format(_T("##NV## %d, %d"), nSliIndex, nValue);

	// support 1 or -1
	if (nSliIndex >= 0 && nGpuIndex < 0)
	{
		GvSetSLILight(nSliIndex, nValue);
	}

	// 0 or -1
	if (nGpuIndex >= 0)
	{
		GvSetLogoLight(nGpuIndex, nValue);
	}
}

void CVGALed::SetLightBeach(int nCount, int nSpeed, int nRange)
{
	static int s_nAdd = -1;
	static int s_nWait = 0;
	static int s_nTimes = 0;
	//static int s_nCount = 0;
	//int nRange = 100;
	//int nSpeed = 5;

	SetLight(m_nLight, -1, nCount);

	if(s_nWait > 0)
	{
		s_nWait --;
		return;
	}

	if (m_nLight == m_nMin) ChangeClr(nCount);

	s_nTimes ++;
	s_nAdd *= (m_nCount <= m_nMin || m_nCount >= m_nMax) ? -1 : 1;
	//s_nCount += s_nAdd * (s_nAdd < 0 && m_nLight < 20 ? 10 : 5);
	m_nCount += s_nAdd;
	m_nLight = m_nCount;
	if(m_nLight > m_nMax) m_nLight = m_nMax;
	if(m_nLight < m_nMin) m_nLight = m_nMin;

	if (m_nCount <= 0)
	{
		s_nWait = (10 - nSpeed) * 5;
		s_nTimes = 0;
		m_nCount = m_nMin;
	}
}

void CVGALed::SetLightFlash(int nCount, int nSpeed, int nRange)
{
	static int s_nAdd = 1;
	static int s_nWait = 0;
	//int nRange = 100;
	//int nSpeed = 2;

	SetLight(m_nLight, -1, nCount);

	if(s_nWait > 0)
	{
		s_nWait --;
		return;
	}


	m_nLight = (m_nLight == m_nMin) ? nRange : m_nMin;
	s_nWait = 10;

	if (m_nLight == m_nMin)
	{
		s_nWait = (10 - nSpeed) * 20 + 30;
	}
}

void CVGALed::SetLightDoubleFlash(int nCount, int nSpeed, int nRange)
{
	static int s_nOdd = 0;
	static int s_nWait = 0;
	//int nRange = 100;
	//int nSpeed = 2;

	SetLight(m_nLight, -1, nCount);

	if(s_nWait > 0)
	{
		s_nWait --;
		return;
	}

	if (0 == s_nOdd && m_nLight == m_nMin)
	{
		ChangeClr(nCount);
	}

	m_nLight = (m_nLight == m_nMin) ? nRange : m_nMin;
	s_nWait = 10;

	if (2 == s_nOdd)
	{
		s_nWait = (10 - nSpeed) * 20 + 20;
		s_nOdd = 0;
	}


	if (m_nLight == nRange)
	{
		s_nOdd++;
	}
}

void CVGALed::ChangeClr(int nCount)
{
	if(m_bRandClr)
	{
		m_nColorIndex = (m_nColorIndex + 1) % 7;
		DWORD dwMode = m_dwMode & ~(s_ClrCmd[6]);
	}
}
