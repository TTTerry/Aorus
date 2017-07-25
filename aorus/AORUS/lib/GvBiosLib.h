#ifndef _GVBIOS_LIB_H
#define _GVBIOS_LIB_H


#ifdef  GVBIOSLIB_EXPORTS
#define GVBIOSLIB_API __declspec(dllexport)
#else
#define GVBIOSLIB_API __declspec(dllimport)
#endif


#define GVAPI_OK						0x00000000
#define GVAPI_LIBRARY_ALREADY_INIT		0x20000000
#define GVAPI_DRIVER_INIT_FAILED		0x20000001
#define GVAPI_OBJECT_INIT_FAILED		0x20000002
#define GVAPI_INVALID_ADAPTER			0x20000003
#define GVAPI_OBJECT_ALREADY_DELETE		0x20000004
#define GVAPI_FILE_EXCEPTION			0x20000005
#define GVAPI_BIOSINFO_ISSAME			0x20000006
#define GVAPI_BIOSID_NOT_MATCH			0x20000007
#define GVAPI_BIOSVERSION_NOT_MATCH		0x20000008
#define GVAPI_FILE_NOT_FOUND			0x20000009
#define GVAPI_FLASH_ATIBIOS_FAILED		0x2000000A
#define GVAPI_BACKUP_ATIBIOS_FAILED		0x2000000B
#define GVAPI_FLASH_NVBIOS_FAILED		0x2000000C
#define GVAPI_BACKUP_NVBIOS_FAILED		0x2000000D
#define GVAPI_PARSE_GVBIOS_FAILED		0x2000000E
#define GVAPI_INVALID_BIOSTABLE			0x2000000F
#define GVAPI_MAPPING_BIOS_FAILED		0x20000010
#define GVAPI_INVALID_GVTABLE			0x20000011
#define GVAPI_INVALID_SIGNONMESSAGE		0x20000012
#define GVAPI_INVALID_PARAMETER			0x20000013
#define GVAPI_TOOL_VERCMD_FAILED		0x20000014
#define GVAPI_PARSE_VERCMDFILE_FAILED	0x20000015

#define VGA_ADAPTER_TYPE_NV				1
#define VGA_ADAPTER_TYPE_ATI			2
#define MAX_ADAPTER_NUM					4


// VGA adapter location information

typedef struct _VGA_ADAPTER_LOC {

	BYTE acBus;      // PCI bus number
	BYTE acDevice;   // PCI device number
	BYTE acFunction; // PCI function number

} VGA_ADAPTER_LOC, *PVGA_ADAPTER_LOC;



// VGA adapter information

typedef struct _VGA_ADAPTER_INFO {

	int  iNumAdapters;       // How many valid adapters exists
	struct {
		WORD wVID;           // Vendor ID
		WORD wDID;           // Device ID
		WORD wSSID;          // Sub System ID
		WORD wSVID;          // Sub Vendor ID

		WORD wType;          // VGA type (NV or ATI)
		VGA_ADAPTER_LOC loc; // VGA adapter location(bus, device, function)
		
	} pInfos[MAX_ADAPTER_NUM];

} VGA_ADAPTER_INFO, *PVGA_ADAPTER_INFO;



// BIOS Version

typedef struct _VGA_BIOS_VERA {

	char cFixed;              // Fixed character, such as 'F'
	char cFirst;              // The first number
	char cSecond;             // The second number
	char cVerifySeparator;    // Verifying code separator, such as '-'
	char cVerifyLength;       // Verifying code length
	int  iVerLength;          // BIOS version code length, it should be 1 or 2, except verifying code

} VGA_BIOS_VERA, *PVGA_BIOS_VERA;

typedef struct _VGA_BIOS_VERW {

	wchar_t cFixed;           // Fixed character, such as 'F'
	wchar_t cFirst;           // The first number
	wchar_t cSecond;          // The second number
	wchar_t cVerifySeparator; // Verifying code separator, such as '-'
	wchar_t cVerifyLength;    // Verifying code length
	int     iVerLength;       // BIOS version code length, it should be 1 or 2, except verifying code

} VGA_BIOS_VERW, *PVGA_BIOS_VERW;

#ifdef UNICODE
#define VGA_BIOS_VER    VGA_BIOS_VERW
#define PVGA_BIOS_VER  PVGA_BIOS_VERW
#else
#define VGA_BIOS_VER    VGA_BIOS_VERA
#define PVGA_BIOS_VER  PVGA_BIOS_VERA
#endif // !UNICODE



// BIOS information

typedef struct _VGA_BIOS_INFOA {

	WORD  wVGAType;					// VGA manufacturer, NV or ATI
	char szModelName[128];			// BIOS model name in string
	char szBiosVer[32];				// BIOS version in string
	char szFileName[MAX_PATH];		// BIOS file name in string
	DWORD dwCheckSum;				// Identify BIOS file is not be changed. dwCheckSum is ingored when calling GvReadBiosInfoFromAdapter().
	WORD  wVID;						// Vendor ID
	WORD  wDID;						// Device ID
	WORD  wSSID;					// Sub System ID
	WORD  wSVID;					// Sub Vendor ID
	char szSrcBiosVer[128];			// Source BIOS version
	char szSignOnMessage[128];		// Sign on message add by HW RD
	char szBiosFileName[128];		// BIOS File Name, stored in AMD's BIOS. only for AMD BIOS. ex: R797TO3D.F80
	VGA_BIOS_VERA biosVer;			// BIOS version structure
	char szPID[10];					// Program ID

} VGA_BIOS_INFOA, *PVGA_BIOS_INFOA;

typedef struct _VGA_BIOS_INFOW {

	WORD  wVGAType;					// VGA manufacturer, NV or ATI
	wchar_t szModelName[128];		// BIOS model name in string
	wchar_t szBiosVer[32];			// BIOS version in string
	wchar_t szFileName[MAX_PATH];	// BIOS file name in string
	DWORD dwCheckSum;				// Identify BIOS file is not be changed. dwCheckSum is ingored when calling GvReadBiosInfoFromAdapter().
	WORD  wVID;						// Vendor ID
	WORD  wDID;						// Device ID
	WORD  wSSID;					// Sub System ID
	WORD  wSVID;					// Sub Vendor ID
	wchar_t szSrcBiosVer[128];		// Source BIOS version
	wchar_t szSignOnMessage[128];	// Sign on message add by HW RD
	wchar_t szBiosFileName[128];	// BIOS File Name, stored in AMD's BIOS. only for AMD BIOS. ex: R797TO3D.F80
	VGA_BIOS_VERW biosVer;			// BIOS version structure
	wchar_t szPID[10];				// Program ID

} VGA_BIOS_INFOW, *PVGA_BIOS_INFOW;

#ifdef UNICODE
#define VGA_BIOS_INFO    VGA_BIOS_INFOW
#define PVGA_BIOS_INFO  PVGA_BIOS_INFOW
#else
#define VGA_BIOS_INFO    VGA_BIOS_INFOA
#define PVGA_BIOS_INFO  PVGA_BIOS_INFOA
#endif // !UNICODE



// UEFI BIOS Version
typedef struct _VGA_UEFI_INFOA {

	bool bUEFI;
	char szGopVer[64];			// GOP Driver Version

} VGA_UEFI_INFOA, *PVGA_UEFI_INFOA;

typedef struct _VGA_UEFI_INFOW {

	bool bUEFI;
	wchar_t szGopVer[64];		// GOP Driver Version

} VGA_UEFI_INFOW, *PVGA_UEFI_INFOW;

#ifdef UNICODE
#define VGA_UEFI_INFO    VGA_UEFI_INFOW
#define PVGA_UEFI_INFO  PVGA_UEFI_INFOW
#else
#define VGA_UEFI_INFO    VGA_UEFI_INFOA
#define PVGA_UEFI_INFO  PVGA_UEFI_INFOA
#endif // !UNICODE




extern "C"
{
	GVBIOSLIB_API DWORD GvInitBiosLib();
	GVBIOSLIB_API DWORD GvFreeBiosLib();

	GVBIOSLIB_API DWORD GvGetEEPROM(int iAdapterIndex, DWORD& dwRomSize);
	
	// NOTE: DON'T try to get checksum from this function. See VGA_BIOS_INFO definition.
	GVBIOSLIB_API DWORD GvReadBiosInfoFromAdapterA(int iAdapterIndex, PVGA_BIOS_INFOA pInfo);   
	GVBIOSLIB_API DWORD GvReadBiosInfoFromAdapterW(int iAdapterIndex, PVGA_BIOS_INFOW pInfo);

	GVBIOSLIB_API DWORD GvFlashBiosA(int iAdapterIndex, const char*    szFileName);
	GVBIOSLIB_API DWORD GvFlashBiosW(int iAdapterIndex, const wchar_t* szFileName);

	GVBIOSLIB_API DWORD GvFlashBiosNoQueryA(int iAdapterIndex, const char*    szFileName);
	GVBIOSLIB_API DWORD GvFlashBiosNoQueryW(int iAdapterIndex, const wchar_t* szFileName);

	GVBIOSLIB_API DWORD GvSaveBiosFileA(int iAdapterIndex, const char*    szFileName);
	GVBIOSLIB_API DWORD GvSaveBiosFileW(int iAdapterIndex, const wchar_t* szFileName);
	
	GVBIOSLIB_API DWORD GvReadAdapterInfo(PVGA_ADAPTER_INFO pInfo);

	GVBIOSLIB_API DWORD GvReadBiosInfoFromFileA(PVGA_BIOS_INFOA pInfo, const char*    szFileName);
	GVBIOSLIB_API DWORD GvReadBiosInfoFromFileW(PVGA_BIOS_INFOW pInfo, const wchar_t* szFileName);

	// Read BIOS info from BIOS-file, and save it into ini-file.
	GVBIOSLIB_API DWORD GvParseBiosInfoToFileA(const char*    szBiosFile, const char*    szIniFile);
	GVBIOSLIB_API DWORD GvParseBiosInfoToFileW(const wchar_t* szBiosFile, const wchar_t* szIniFile);


	// Check UEFI BIOS.
	GVBIOSLIB_API DWORD GvCheckUEFIBiosFromFileA(PVGA_UEFI_INFOA pInfo, const char*    szFileName);
	GVBIOSLIB_API DWORD GvCheckUEFIBiosFromFileW(PVGA_UEFI_INFOW pInfo, const wchar_t* szFileName);

    
#ifdef UNICODE
#define GvReadBiosInfoFromAdapter GvReadBiosInfoFromAdapterW
#define GvFlashBios               GvFlashBiosW
#define GvFlashBiosNoQuery        GvFlashBiosNoQueryW
#define GvSaveBiosFile            GvSaveBiosFileW
#define GvReadBiosInfoFromFile    GvReadBiosInfoFromFileW
#define GvParseBiosInfoToFile	  GvParseBiosInfoToFileW
#define GvCheckUEFIBiosFromFile	  GvCheckUEFIBiosFromFileW
#else
#define GvReadBiosInfoFromAdapter GvReadBiosInfoFromAdapterA
#define GvFlashBios               GvFlashBiosA
#define GvFlashBiosNoQuery        GvFlashBiosNoQueryA
#define GvSaveBiosFile            GvSaveBiosFileA
#define GvReadBiosInfoFromFile    GvReadBiosInfoFromFileA
#define GvParseBiosInfoToFile	  GvParseBiosInfoToFileA
#define GvCheckUEFIBiosFromFile	  GvCheckUEFIBiosFromFileA
#endif // !UNICODE

}


#endif