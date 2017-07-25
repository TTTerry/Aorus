#pragma once

#include "../../common/definition.h"

//#define PROFILE_SIZE 0x40

#define MCU_ATART_ADDR	0xb800
#define MACRO_COUNT 50

static DWORD m_AM300ProfileAddr[5] = {
	MCU_ATART_ADDR + 0x000, MCU_ATART_ADDR + 0x0C0, MCU_ATART_ADDR + 0x180, MCU_ATART_ADDR + 0x240, MCU_ATART_ADDR + 0x300,
};

static DWORD s_AM300MsProfileAddr[5] = {
	MCU_ATART_ADDR + 0x040, MCU_ATART_ADDR + 0x100, MCU_ATART_ADDR + 0x1c0, MCU_ATART_ADDR + 0x280, MCU_ATART_ADDR + 0x3d0,
};

static GVORDER_MEMORY_PARAM m_param;
static BYTE	m_KeyProfile[5][PROFILE_SIZE * 3];
static BYTE m_TotalKey[KEYMAP_TOTAL_SIZE];
static BYTE m_MarosKey[MACROS_KEYS_COUNT][MACROS_KEYS_SIZE];
static BYTE m_MarosPro[MACROS_KEYS_COUNT][MACROS_NAME_SIZE];

class CAM300Ctrl
{
public:
	CAM300Ctrl(void);
	~CAM300Ctrl(void);

	static void LoadMemory(GVORDER_MEMORY_PARAM param);
	static DWORD GetCurProfile(GVORDER_PROFILE& profile);
	static DWORD SelProfile(int nProfile);
	static DWORD GetProfile(GVORDER_PROFILE& profile);
	static DWORD SetProfile(GVORDER_PROFILE profile);
	//Terry 2017/07/03
	static DWORD GetDPI(GVORDER_DPI& dpi);
	static DWORD GetCurDPI(GVORDER_DPI& dpi);
	static DWORD SetDPI(GVORDER_DPI dpi);
	static DWORD GetReportRate(int& nReportRate);
	static DWORD SetReportRate(int nReportRate);
	static DWORD SelDPI(int nDpiIndex);

	static DWORD GetKeyMapping(GVORDER_KEYFUN& fnkey);
	static DWORD GetMacrosList(GVORDER_MACROS_ATTR lstmacros[], int nCount);
	static DWORD getMacroList(GVORDER_MACROS_ATTR lstmacros[], int& nCount);
	static DWORD SetKeyMappingDefault(int nProfile, GVORDER_DEVICE_TYPE type);
	static DWORD SetKeyMapping(GVORDER_KEYFUN fnkey);
	static DWORD SetKeyMappingAddr(GVORDER_KEYFUN fnkey, DWORD dwAddr);

	static DWORD GetMacrosKey(GVORDER_MACROS& macros);
	static DWORD SetMacrosKey(GVORDER_MACROS macros);




private:
	GVORDER_MEMORY_PARAM m_param;
	//static void StopFlase();
	//static void EraseFlase4K(int Addr);
	//static void MyWriteByte(BYTE* pBytes, int nLen);
	//static HANDLE hAM300;

	//static GVORDER_MEMORY_PARAM m_param;
	//static BYTE	m_KeyProfile[5][PROFILE_SIZE * 3];

};
