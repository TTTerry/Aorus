#pragma once

#define CLR_MAX_COUNT 10

#define TYPE_MEMORY   	0
#define TYPE_BRIGHT		1
#define TYPE_BREATH		2
#define TYPE_CYCLING	3
#define TYPE_SINGLE 	4
#define TYPE_TWICE   	5


typedef struct _SYNCLED_CONFIG
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
	int nSecond;

	COLORREF clrArray[CLR_MAX_COUNT];

	CString GetClrString();
	void SetClrString(CString sClr);
	_SYNCLED_CONFIG();
	_SYNCLED_CONFIG& operator = (const _SYNCLED_CONFIG& config);

}SYNCLED_CONFIG, *PSYNCLED_CONFIG;


class CSyncLed
{
public:
	CSyncLed(void);
	~CSyncLed(void);

	static void Begin();
	static void End();
	static void Set(SYNCLED_CONFIG config, bool bSave = false);
	static bool Read(SYNCLED_CONFIG& config);
	static bool Save(SYNCLED_CONFIG config);
	static void RefreshMemory();


	static SHELLEXECUTEINFO m_st;

};