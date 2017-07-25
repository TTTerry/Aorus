#pragma once

#define WM_SYN_MOBILESTATE		      WM_USER + 1000
#define WM_FANTOP_BTN_CHANGE          WM_USER + 1001

#define ADDRL(_x_) (((_x_) >>  0) & 0xff)
#define ADDRM(_x_) (((_x_) >>  8) & 0xff)
#define ADDRH(_x_) (((_x_) >> 16) & 0xff)


#define CLR_TRPT		RGB(255,   0, 255)	// transparent color
#define CLR_MAIN		RGB(255, 102,   0)
#define CLR_WHITE		RGB(255, 255, 255)
#define CLR_BLACK       RGB(0,0,0)
#define CLR_DARK		RGB( 27,  27,  27)
#define CLR_GRAY		RGB( 80,  80,  80)
#define CLR_GRAY2		RGB(130,  130,  130)
#define CLR_GRAY3		RGB(93,  93,  93)
#define CLR_NORMAL		RGB(200, 200, 200)
#define CLR_ENABLE		RGB(233, 84, 3)



// 9 kinds of color specified:
#define CLR_DEFINE_COUNT 8
static COLORREF s_clr[9] = {
	RGB(255,   0,   0),
	RGB(255,  96,   0),
	RGB(255, 255,   0),
	RGB(  0, 210,   0), 
	RGB(  0, 255, 255),
	RGB(  0,   0, 255),
	RGB(150,   0, 180),
	RGB(255,   0, 254),
	RGB(255, 255, 255),
};
//Terry 2017/6/22
#define KB_MARCO_COUNT 50 
typedef struct _CMB_MARCO
{
#define MARCO_NEW	1
#define MARCO_LOAD	2
#define MARCO_DEL	3

	int nIndex;
	int nType;

}CBB_MARCO, *PCMB_MARCO;

#define RAW_DEV_HID 0x01
#define RAW_DEV_KB  0x02
#define RAW_DEV_MS  0x04
bool RawInputDevices(HWND hWnd, DWORD nType, bool bRegister);


COLORREF StringToColor(CString sClr);
CString ColorToString(COLORREF clrRGB);
COLORREF HexToRGB(CString sClr);
CString RGBToHex(COLORREF clrRGB);
COLORREF HSBToRGB(float h, float s = 1.0, float v = 1.0);
float RGBtoHSB(COLORREF clr);
HANDLE InstallFont(DWORD dwFontID);
void UninstallFont(HANDLE hFont);
CString GetModuleDirectory();
BOOL CreateFileShortcut(CString sFileName, CString sLnkFileDir, CString sLnkFileName, CString sWorkDir, CString sArguments, WORD wHotkey, CString sDescription, int iShowCmd = SW_SHOWNORMAL);
CString BrowseFolder(HWND hWnd);
CString BrowseFile(LPCTSTR lpszFilter, LPCTSTR lpszDefExt, BOOL bOpen);
void DebugLog(const wchar_t* pszFormat, ...);
void LogFile(const wchar_t* pszFormat, ...);
void ShowLoadingWindow(LPVOID pParam, int status);
void CreateDir(CString sPath);
DWORD GetTimeElapse(DWORD dwOldTick);


void InitLock();
void CmdLock();
void CmdUnLock();
