#pragma once
#include "KCFirmwareCmd.h"

//
#define TYPE_BRIGHT			1	// Static mode
#define TYPE_BREATH			2	// Breath
#define TYPE_CYCLING		3	// Color Cycle
#define TYPE_FLASHING		4	// Once Twinkle
#define TYPE_DUALFLASHING	5	// Twice Twinkle



#define CLR_MAX_COUNT 10

typedef struct _DEVICE_CONFIG
{

#define CONFIG_TYPE		0x00001
#define CONFIG_BRIGHT	0x00002
#define CONFIG_SPEED	0x00004
#define CONFIG_COLOR	0x00008
#define CONFIG_ALL		0xFFFFF

	int nType;
	int nBright;
	int nSpeed;
	int nClrCount;
	bool bOn;
	COLORREF clrArray[CLR_MAX_COUNT];

	_DEVICE_CONFIG();
	_DEVICE_CONFIG(GVORDER_LED_CFG cfg);
	_DEVICE_CONFIG& operator = (const _DEVICE_CONFIG& config);

	GVORDER_LED_CFG ToGvOrder();

}DEVICE_CONFIG, *PDEVICE_CONFIG;


class CXLedCmd
{
public:
	CXLedCmd(void);
	~CXLedCmd(void);

	bool	Init();
	bool	Init(WORD wVID, WORD wPID);
	int		GetDeviceCount();
	bool	IsConnect(int nBrd = 0);
	DWORD	GetErrorLast(){ return m_dwLastError; }
	bool	SetLightSetting(DEVICE_CONFIG config, DWORD dwPerf, int nBrd);
	bool	SetLightClr(COLORREF clr, int nBrd);
	bool	GetLightSetting(DEVICE_CONFIG& config, int nBrd);
	bool	SaveLightSetting(int nBrd);
	DEVICE_CONFIG ByteToConfig(BYTE szData[]);
	bool	Read(DEVICE_CONFIG& config);
	bool	Save(DEVICE_CONFIG config);

private:
	void	GetCmd(BYTE szCmd[], DWORD dwCmd, BYTE* szData = NULL, int nDataIndex = 2);

	int				m_nIndex;
	GVFW_BOARDINFO	m_stKeyBoards[GVFW_MAX_BOARD];
	DEVICE_CONFIG	m_config[GVFW_MAX_BOARD];
	DWORD			m_dwLastError;
	CKCFirmwareCmd  m_Device;
	WORD			m_wVID;
	WORD			m_wPID;
	bool			m_bGet;
};
