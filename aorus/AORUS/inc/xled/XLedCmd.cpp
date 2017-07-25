#include "StdAfx.h"
#include "XLedCmd.h"

#define VID 0x1044
#define PID1 0x8000
#define PID2 0x7A21
#define HID 3

#define CMD_LENGTH 8
#define CMD_GET_BRIGHT	0x000000
#define CMD_GET_COLOR	0x000001
#define CMD_SET_BRIGHT	0x000002
#define CMD_SET_COLOR	0x000003
#define CMD_DEF_COLOR	0x000004


#define CMD_DATA_TYPE		2
#define CMD_DATA_BRIGHT		3
#define CMD_DATA_SPEED		4
#define CMD_DATA_COUNT		5

#define CMD_DATA_R			2
#define CMD_DATA_G			3
#define CMD_DATA_B			4
#define CMD_DATA_INDEX		5

#define CMD_DATA_STATUS		0

#define CMD_STU_READ		0
#define CMD_STU_WRITE		1
#define CMD_STU_INPUT		3



DEVICE_CONFIG::_DEVICE_CONFIG()
{
	nType = TYPE_BRIGHT;
	nBright = 100;
	nSpeed = 8;
	nClrCount = 7;
	bOn = true;
	for (int i = 0; i < CLR_MAX_COUNT; i++)
	{
		if (i < CLR_DEFINE_COUNT)
		{
			clrArray[i] = s_clr[i];
		}
		else
		{
			clrArray[i] = RGB(0, 0, 0);
		}
	}
}

DEVICE_CONFIG::_DEVICE_CONFIG(GVORDER_LED_CFG cfg)
{
	nType = (int)cfg.type;
	bOn = GVORDER_LED_OFF != cfg.type;
	nBright = bOn ? cfg.nBright * 2 : 0;
	nSpeed = 10 - cfg.nSpeed;
	nClrCount = cfg.nClrCount;
	for (int i = 0; i < nClrCount; i++)
	{
		clrArray[i] = cfg.clrArray[i];
	}
}

DEVICE_CONFIG& DEVICE_CONFIG::operator = (const DEVICE_CONFIG& config)
{
	nType = config.nType;
	nBright = config.nBright;
	nSpeed = config.nSpeed;
	nClrCount = config.nClrCount;
	bOn = config.bOn;
	for (int i = 0; i < CLR_MAX_COUNT; i++)
	{
		clrArray[i] = config.clrArray[i];
	}

	return *this;
}

GVORDER_LED_CFG DEVICE_CONFIG::ToGvOrder()
{
	GVORDER_LED_CFG cfg;
	cfg.type = (GVORDER_LED_MODE)nType;
	cfg.nBright = nBright / 2;
	cfg.nSpeed = 10 - nSpeed;
	cfg.nClrCount = nClrCount;
	for (int i = 0; i < nClrCount; i++)
	{
		cfg.clrArray[i] = clrArray[i];
	}
	if(0 == cfg.nBright)
	{
		cfg.nBright = 10;
		cfg.type = GVORDER_LED_OFF;
	}
	return cfg;
}

static BYTE s_lstCmd[][8] = {
	{ 0x00, 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Get Bright Setting
	{ 0x00, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Get RGB By Index
	{ 0x01, 0xC9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Set Bright Setting
	{ 0x01, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Set RGB By Index
	{ 0x01, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Set RGB Define
};

CXLedCmd::CXLedCmd(void)
{
	m_bGet = false;
	m_nIndex = -1;
}

CXLedCmd::~CXLedCmd(void)
{
	GvFreeFireware(m_nIndex);
}

bool CXLedCmd::Init()
{
	return Init(m_wVID, m_wPID);
}

bool CXLedCmd::Init(WORD wVID, WORD wPID)
{
	m_wVID = wVID;
	m_wPID = wPID;
	return m_Device.ConnectXK700(wVID, wPID);
}

int  CXLedCmd::GetDeviceCount()
{
	if (m_nIndex < 0 && !Init()) return 0;
	m_dwLastError = GVAPI_OK;
	int nCount = 0;
	m_dwLastError = GvGetBoards(m_nIndex, m_stKeyBoards, nCount);
	return nCount;
}

bool CXLedCmd::IsConnect(int nBrd)
{
	/*if (m_nIndex < 0 && !Init()) return false;
	if (nBrd >= GVFW_MAX_BOARD)  return false;

	m_dwLastError = GVAPI_OK;

	return GvIsConnectBrd(m_nIndex, nBrd) == TRUE;*/


	return TRUE;
}

bool CXLedCmd::SetLightSetting(DEVICE_CONFIG config, DWORD dwPerf, int nBrd)
{
	if (nBrd >= GVFW_MAX_BOARD)  return false;

	if (dwPerf & CONFIG_TYPE)   m_config[nBrd].nType = config.nType;
	if (dwPerf & CONFIG_BRIGHT) m_config[nBrd].nBright = config.nBright;
	if (dwPerf & CONFIG_SPEED)  m_config[nBrd].nSpeed = config.nSpeed;
	if (dwPerf & CONFIG_COLOR) 
	{
		m_config[nBrd].nClrCount = config.nClrCount;
		for (int i = 0; i < CLR_MAX_COUNT; i++)
		{
			m_config[nBrd].clrArray[i] = config.clrArray[i];
		}
	}

	m_dwLastError = GVAPI_OK;

	int nCmdLength = CMD_LENGTH;
	BYTE szCmd[CMD_LENGTH]	= {0};
	BYTE szReceive[1024]	= {0};

	for (int i = 0; i < m_config[nBrd].nClrCount && m_config[nBrd].nClrCount < 7; i++)
	{
		BYTE szData[6] = { GetRValue(m_config[nBrd].clrArray[i]), GetGValue(m_config[nBrd].clrArray[i]), GetBValue(m_config[nBrd].clrArray[i]), i + 8, 0x01, 0x00 };
		GetCmd(szCmd, CMD_SET_COLOR, szData);
		m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);
		Sleep(100);
		if (!m_dwLastError) return false;
	}

	// Peter Lee 2017/6/13 marked speed and bright setting same with SaveLightSetting
	int iBright = m_config[nBrd].nBright;
	if (m_config[nBrd].nType != TYPE_FLASHING && m_config[nBrd].nType != TYPE_DUALFLASHING)
		iBright = (m_config[nBrd].nBright + 5) / 10;
	BYTE szData[6] = { m_config[nBrd].nType, iBright, 10 - (m_config[nBrd].nSpeed), m_config[nBrd].nClrCount, m_config[nBrd].nClrCount < 8 ? 0x08 : 0x00, 0x00 };
	//if(TYPE_OFF == m_config[nBrd].nType)
	//{
	//	//szData[0] = 1;
	//	//szData[2] = 0;
	//}
	GetCmd(szCmd, CMD_SET_BRIGHT, szData);
	m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);

	if (m_dwLastError != GVAPI_OK) return false;

	return true;
}

bool CXLedCmd::GetLightSetting(DEVICE_CONFIG& config, int nBrd)
{
	if (m_nIndex < 0 && !Init()) return false;
	if (nBrd >= GVFW_MAX_BOARD)  return false;

	if(Read(config))
	{
		return true;
	}

	m_bGet = true;

	m_dwLastError = GVAPI_OK;
	
	int nCmdLength = CMD_LENGTH;
	BYTE szCmd[CMD_LENGTH]	= {0};
	BYTE szReceive[1024]	= {0};

	GetCmd(szCmd, CMD_GET_BRIGHT);
	//GvConnectBrd(m_nIndex, nBrd, HID);
	//m_dwLastError = GvSendCommandByte(m_nIndex, nBrd, HID, szCmd, szReceive, nCmdLength);
	m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, szReceive, nCmdLength);

	if (m_dwLastError != GVAPI_OK) return false;

	m_config[nBrd].nType		= szReceive[CMD_DATA_TYPE];
	m_config[nBrd].nBright		= szReceive[CMD_DATA_BRIGHT];
	m_config[nBrd].nSpeed		= szReceive[CMD_DATA_SPEED];
	m_config[nBrd].nClrCount	= szReceive[CMD_DATA_COUNT];

	for (int i = 0; i < m_config[nBrd].nClrCount && m_config[nBrd].nClrCount < 7; i++)
	{
		BYTE szData[6] = { i + 8, 0x00, 0x00, 0x00, 0x00, 0x00 };
		GetCmd(szCmd, CMD_GET_COLOR, szData);
		//m_dwLastError = GvSendCommandByte(m_nIndex, nBrd, HID, szCmd, szReceive, nCmdLength);
		m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, szReceive, nCmdLength);
		if (m_dwLastError != GVAPI_OK) return false;
		m_config[nBrd].clrArray[i] = RGB(szReceive[CMD_DATA_R], szReceive[CMD_DATA_G], szReceive[CMD_DATA_B]);
	}

	config = m_config[nBrd];
	return true;
}

bool CXLedCmd::SaveLightSetting(int nBrd)
{
	if (m_nIndex < 0 && !Init()) return false;
	if (nBrd >= GVFW_MAX_BOARD)  return false;

	//GvConnectBrd(m_nIndex, nBrd, HID);
	m_dwLastError = GVAPI_OK;

	int nCmdLength = CMD_LENGTH;
	BYTE szCmd[CMD_LENGTH]	= {0};
	BYTE szReceive[1024]	= {0};

	for (int i = 0; i < m_config[nBrd].nClrCount && m_config[nBrd].nClrCount < 7; i++)
	{
		BYTE szData[6] = { GetRValue(m_config[nBrd].clrArray[i]), GetGValue(m_config[nBrd].clrArray[i]), GetBValue(m_config[nBrd].clrArray[i]), i + 8, 0x01, 0x00 };
		GetCmd(szCmd, CMD_SET_COLOR, szData);
		//m_dwLastError = GvSendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);
		m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);
		Sleep(100);
		if (m_dwLastError != GVAPI_OK) return false;
	}

	// Peter Lee 2017/6/13 marked speed and bright setting same with SetLightSetting
	int iBright = m_config[nBrd].nBright;
	if (m_config[nBrd].nType != TYPE_FLASHING && m_config[nBrd].nType != TYPE_DUALFLASHING)
		iBright = (m_config[nBrd].nBright + 5) / 10;
	BYTE szData[6] = { m_config[nBrd].nType, iBright, 10 - m_config[nBrd].nSpeed, m_config[nBrd].nClrCount, m_config[nBrd].nClrCount < 8 ? 0x08 : 0x00, 0x00 };
	// Peter Lee 2017/6/13 marked for bug fix, same as SetLightSetting, or flash will become consistant
	//if(4 == m_config[nBrd].nType)
	//{
	//	szData[0] = 1;
	//	szData[2] = 0;
	//}
	GetCmd(szCmd, CMD_SET_BRIGHT, szData);
	//m_dwLastError = GvSendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);
	m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);

	if (m_dwLastError != GVAPI_OK) return false;

	m_Device.SaveSetting();
	Save(m_config[nBrd]);
	return true;
}

bool CXLedCmd::SetLightClr(COLORREF clr, int nBrd)
{
	if (m_nIndex < 0 && !Init()) return false;
	if (nBrd >= GVFW_MAX_BOARD)  return false;

	//GvConnectBrd(m_nIndex, nBrd, HID);
	m_dwLastError = GVAPI_OK;

	int nCmdLength = CMD_LENGTH;
	BYTE szCmd[CMD_LENGTH]	= {0};
	BYTE szReceive[1024]	= {0};

	BYTE szData[6] = { 0x00, GetRValue(clr), GetGValue(clr), GetBValue(clr), 0x00, 0x00 };
	GetCmd(szCmd, CMD_DEF_COLOR, szData);
	//m_dwLastError = GvSendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);
	m_dwLastError = m_Device.SendCommandByte(m_nIndex, nBrd, HID, szCmd, NULL, nCmdLength);

	if (m_dwLastError != GVAPI_OK) return false;

	return true;
}

DEVICE_CONFIG CXLedCmd::ByteToConfig(BYTE szData[])
{
	DEVICE_CONFIG config;
	config.nType	= szData[CMD_DATA_TYPE];
	config.nBright	= szData[CMD_DATA_BRIGHT];
	config.nSpeed	= szData[CMD_DATA_SPEED];
	config.nClrCount= szData[CMD_DATA_COUNT];
	return config;
}

void CXLedCmd::GetCmd(BYTE szCmd[], DWORD dwCmd, BYTE* szData, int nDataIndex)
{
	memcpy(szCmd, s_lstCmd[dwCmd], CMD_LENGTH);
	if (szData != NULL)
	{
		memcpy(szCmd + nDataIndex, szData, CMD_LENGTH - nDataIndex);
	}
}

bool CXLedCmd::Save(DEVICE_CONFIG config)
{
	CString sPath;
	sPath.Format(GetModuleDirectory() + _T("GvTemp\\%04x.io"), m_wPID);
	BYTE Datas[sizeof(DEVICE_CONFIG) + 8] = "XLedCFG";
	BYTE* Mem = &Datas[8];
	memset(Mem, 0xff, sizeof(DEVICE_CONFIG) - 8);

	memcpy(Mem, (void*)&config, sizeof(DEVICE_CONFIG));

	CFile file;
	if(!file.Open(sPath, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite))
	{
		return false;
	}

	file.Write(Datas, sizeof(DEVICE_CONFIG) + 8);
	file.Close();

	return true;
}

bool CXLedCmd::Read(DEVICE_CONFIG& config)
{
	CString sPath;
	sPath.Format(GetModuleDirectory() + _T("GvTemp\\%04x.io"), m_wPID);
	if(!PathFileExists(sPath)) return false;
	BYTE Datas[sizeof(DEVICE_CONFIG) + 8] = {0};
	BYTE* Mem = &Datas[8];
	memset(Datas, 0xff, sizeof(DEVICE_CONFIG) + 8);
	CFile file;
	if(!file.Open(sPath, CFile::typeBinary | CFile::modeRead))
	{
		return false;
	}

	file.Read(Datas, sizeof(DEVICE_CONFIG) + 8);
	file.Close();

	if(strcmp((char*)Datas, "XLedCFG") != 0) return false;

	memcpy((void*)&config, Mem, sizeof(DEVICE_CONFIG));

	return true;
}