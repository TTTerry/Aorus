#pragma once
#include "../mainboard/MBLedLib.h"
typedef struct _RawSMBIOSData
{
	BYTE	Used20CallingMethod;
	BYTE	SMBIOSMajorVersion;
	BYTE	SMBIOSMinorVersion;
	BYTE	DmiRevision;
	DWORD	Length;
	PBYTE	SMBIOSTableData;
} RawSMBIOSData, *PRawSMBIOSData;
typedef struct _SMBIOSHEADER_
{
	BYTE Type;
	BYTE Length;
	WORD Handle;
} SMBIOSHEADER, *PSMBIOSHEADER;
typedef struct _TYPE_2_ {
	SMBIOSHEADER	Header;
	UCHAR	Manufacturer;
	UCHAR	Product;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	AssetTag;
	UCHAR	FeatureFlags;
	UCHAR	LocationInChassis;
	UINT16	ChassisHandle;
	UCHAR	Type;
	UCHAR	NumObjHandle;
	UINT16	*pObjHandle;
} BoardInfo, *PBoardInfo;
class CMBCtrl
{
public:
	CMBCtrl();
	~CMBCtrl();
	void SetLedSetting(LED_SETTING  setting);
	void SetBrightness(LED_SETTING  setting);
	void SetSpeed(LED_SETTING  setting);
	void GetModuleName(CString &modename);
	int GetSuportFlag();
	bool IsConnected() { return m_bConnected; }
protected:
	DECLARE_MESSAGE_MAP()
	void OnTimer(UINT_PTR nIDEvent);
	static UINT DelaySetLED(LPVOID lpParam);
	HANDLE m_hDelaySetLedEvent;
	HANDLE m_hDelaySetLedThread;
private:
	CString m_modelname;
	HWND m_hWnd;
	Led_Struce *Ptr_Struct;
	LED_SETTING m_LastSetting;
	void GetModuleName();
	void DumpSMBIOSStruct(void *Addr, UINT Len);
	bool DispatchStructType(PSMBIOSHEADER hdr);
	bool ProcBoardInfo(void* p);
	const char* toPointString(void* p);
	const char* LocateStringA(const char* str, UINT i);
	const wchar_t* LocateStringW(const char* str, UINT i);

	bool m_bConnected;
};