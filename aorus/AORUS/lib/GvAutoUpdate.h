#ifndef _GVAUTOUPDATE_23e3n4vc0nsdf_H
#define _GVAUTOUPDATE_23e3n4vc0nsdf_H

#ifdef  GV_AUTO_UPDATE
#define GVAUTOUPDATEAPI  __declspec(dllexport)
#else
#define GVAUTOUPDATEAPI  __declspec(dllimport)
#endif


#define AUDT_UTILITY_OCGURU		0x0001
#define AUDT_UTILITY_ATBIOS		0x0002
#define AUDT_UTILITY_OCGURUII	0x0003
#define AUDT_UTILITY_K85AP		0x0004
#define AUDT_UTILITY_AORUS		0x0005
#define AUDT_UTILITY_XM300		0x0006
#define AUDT_UTILITY_XTREME		0x0007
#define AUDT_UTILITY_AORUSX		0x0008


typedef struct _AUDT_FILEVERSION 
{
	WORD wMajor;
	WORD wMinor;
	WORD wRevision;
	WORD wBuild;  

} AUDT_FILEVERSION, *PAUDT_FILEVERSION;


// model specification. 
typedef struct _AUDT_MODELSPECA
{
#define AUDT_MAX_IMAGE	8

	char szModelName[48];					// example: GV-R667D3-2GI
	char szProductId[8];					// Product id in gigabyte web site. example: 4181
	int  nImageCount;						// Model images count.
	char szImageUrls[AUDT_MAX_IMAGE][256];	// Model Image Urls.
	char szRevision[10];					// Model revision. example: 1.1

	char szChipset[128];					// example: Radeon HD 6670
	char szTools[256];						// Software tools supported.
	char szCoreClock[64];					// example: 800 MHz
	char szMemoryClock[64];					// example: 1600 MHz
	char szShaderClock[64];					// example: 2000 MHz
	char szProcessTech[64];					// Process Technology. example: 40 nm
	char szMemorySize[64];					// example: 2 GB
	char szMemoryBus[64];					// example: 128 bit
	char szMemoryType[64];					// example: DDR3
	char szDirectX[64];						// DirectX version supported. example: 11
	char szOpenGL[64];						// OpenGL version supported. example: 4.1
	char szPCBForm[64];						// example: ATX
	char szIOPort[256];						// example: HDMI * 1;DVI-D * 1;D-sub * 1;
	char szDigitalMaxResolution[64];		// example: 2560 x 1600
	char szAnalogMaxResolution[64];			// example: 2048 x 1536
	char szMultiView[64];					// example: 2
	char szCardBus[64];						// example: PCI-E 2.1
	char szCardSize[256];					// example: H=37.7 mm, L=211.8 mm, W=136.8 mm
	char szPowerRequirement[256];			// example: 400 W

} AUDT_MODELSPECA, *PAUDT_MODELSPECA;


typedef struct _AUDT_MODELSPECW
{
#define AUDT_MAX_IMAGE	8

	wchar_t szModelName[48];				// example: GV-R667D3-2GI
	wchar_t szProductId[8];					// Product id in gigabyte web site. example: 4181
	int  nImageCount;						// Model images count.
	wchar_t szImageUrls[AUDT_MAX_IMAGE][256];// Model Image Urls.
	wchar_t szRevision[10];					// Model revision. example: 1.1

	wchar_t szChipset[128];					// example: Radeon HD 6670
	wchar_t szTools[256];					// Software tools supported.
	wchar_t szCoreClock[64];				// example: 800 MHz
	wchar_t szMemoryClock[64];				// example: 1600 MHz
	wchar_t szShaderClock[64];				// example: 2000 MHz
	wchar_t szProcessTech[64];				// Process Technology. example: 40 nm
	wchar_t szMemorySize[64];				// example: 2 GB
	wchar_t szMemoryBus[64];				// example: 128 bit
	wchar_t szMemoryType[64];				// example: DDR3
	wchar_t szDirectX[64];					// DirectX version supported. example: 11
	wchar_t szOpenGL[64];					// OpenGL version supported. example: 4.1
	wchar_t szPCBForm[64];					// example: ATX
	wchar_t szIOPort[256];					// example: HDMI * 1;DVI-D * 1;D-sub * 1;
	wchar_t szDigitalMaxResolution[64];		// example: 2560 x 1600
	wchar_t szAnalogMaxResolution[64];		// example: 2048 x 1536
	wchar_t szMultiView[64];				// example: 2
	wchar_t szCardBus[64];					// example: PCI-E 2.1
	wchar_t szCardSize[256];				// example: H=37.7 mm, L=211.8 mm, W=136.8 mm
	wchar_t szPowerRequirement[256];		// example: 400 W

} AUDT_MODELSPECW, *PAUDT_MODELSPECW;

#ifdef UNICODE
#define AUDT_MODELSPEC    AUDT_MODELSPECW
#define PAUDT_MODELSPEC   PAUDT_MODELSPECW
#else
#define AUDT_MODELSPEC    AUDT_MODELSPECA
#define PAUDT_MODELSPEC   PAUDT_MODELSPECA
#endif // !UNICODE


typedef struct _AUDT_MODELA
{
	char szModelName[48];					// example: GV-R667D3-2GI
	char szTiptopName[48];					// example: 9VR667D32I

}AUDT_MODELA, *PAUDT_MODELA; 

typedef struct _AUDT_MODELW
{
	wchar_t szModelName[48];				// example: GV-R667D3-2GI
	wchar_t szTiptopName[48];				// example: 9VR667D32I

}AUDT_MODELW, *PAUDT_MODELW; 

#ifdef UNICODE
#define AUDT_MODEL    AUDT_MODELW
#define PAUDT_MODEL   PAUDT_MODELW
#else
#define AUDT_MODEL    AUDT_MODELA
#define PAUDT_MODEL   PAUDT_MODELA
#endif // !UNICODE


typedef struct _AUDT_BIOSINFOA
{
	char szBiosVer[12];					// example: F1
	char szUpdateTime[24];				// example: 2010-07-28
	char szUpdateInfo[500];

}AUDT_BIOSINFOA, *PAUDT_BIOSINFOA; 

typedef struct _AUDT_BIOSINFOW
{
	wchar_t szBiosVer[12];					// example: F1
	wchar_t szUpdateTime[24];				// example: 2010-07-28
	wchar_t szUpdateInfo[500];

}AUDT_BIOSINFOW, *PAUDT_BIOSINFOW; 


#ifdef UNICODE
#define AUDT_BIOSINFO    AUDT_BIOSINFOW
#define PAUDT_BIOSINFO   PAUDT_BIOSINFOW
#else
#define AUDT_BIOSINFO    AUDT_BIOSINFOA
#define PAUDT_BIOSINFO   PAUDT_BIOSINFOA
#endif // !UNICODE


extern "C"
{
	/****************************************************************************************
	 * 功能描述：
	 * 判断本dll为UNICODE-DLL还是ANSI-DLL. 
	 *
	 * 返回值：返回TRUE为UNICODE-DLL, FALSE为ANSI-DLL.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvIsAutoUpdateUnicode();

	/****************************************************************************************
	 * 功能描述：
	 * 从官网中获取Model的图片链接. 调用该API成功的前提为平台处于联网状态下.
	 *
	 * 参数：
	 * [in]szModelName      当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    当前显卡Model的版本号. 如1.1. 该值可为NULL.
	 *
	 * [out]szUrl           调用成功时, 返回Model的图片Url.
	 *
	 * 返回值：成功返回TRUE. 否则返回FALSE.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI  BOOL GvGetModelImageA(const char    szModelName[48], const char    szRevision[10], char    szUrl[260], int& nUrlSize);
	GVAUTOUPDATEAPI  BOOL GvGetModelImageW(const wchar_t szModelName[48], const wchar_t szRevision[10], wchar_t szUrl[260], int& nUrlSize);
	#ifdef UNICODE
	#define GvGetModelImage GvGetModelImageW
	#else
	#define GvGetModelImage GvGetModelImageA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 从官网中获取Model的specification, 并将其写入指定Ini文件中. 调用该API成功的前提为平台处于联网状态下.
	 *
	 * 参数：
	 * [in]szModelName      当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    当前显卡Model的版本号. 如1.1. 该值可为NULL.
	 *
	 * [in]szIniFile        调用成功时, 存放Model specification的Ini路径.
	 *
	 * 返回值：成功返回TRUE. 否则返回FALSE.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvParseModelSpecToFileA(char    szModelName[48],  char    szRevision[10], const char*    szIniFile);
	GVAUTOUPDATEAPI BOOL GvParseModelSpecToFileW(wchar_t szModelName[48],  wchar_t szRevision[10], const wchar_t* szIniFile);
	#ifdef UNICODE
	#define GvParseModelSpecToFile GvParseModelSpecToFileW
	#else
	#define GvParseModelSpecToFile GvParseModelSpecToFileA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 从官网中获取Model的specification. 调用该API成功的前提为平台处于联网状态下.
	 *
	 * 参数：
	 * [in]szModelName      当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    当前显卡Model的版本号. 如1.1. 该值可为NULL.
	 *
	 * [out]PAUDT_MODELSPEC 调用成功时, 返回Model的规格参数. 注意: 调用成功时, 并非AUDT_MODELSPEC
	 *                      结构体中的所有域都有值, 根据该变量值是否为空(即"")来判断该域是否有值.
	 *
	 * 返回值：成功返回TRUE. 否则返回FALSE.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvGetModelSpecificationA(char    szModelName[48],  char    szRevision[10], PAUDT_MODELSPECA pModelSpec);
	GVAUTOUPDATEAPI BOOL GvGetModelSpecificationW(wchar_t szModelName[48],  wchar_t szRevision[10], PAUDT_MODELSPECW pModelSpec);
	#ifdef UNICODE
	#define GvGetModelSpecification GvGetModelSpecificationW
	#else
	#define GvGetModelSpecification GvGetModelSpecificationA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 获取Model的官网URL.
	 *
	 * 参数：
	 * [in]szModelName    当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 *
	 * [in/out]szModelUrl 若查找成功, 则返回Model对应的官网URL
	 *                    否则, 返回技嘉官网URL
	 *
	 * [in/out]nUrlSize   szModelUrl缓冲区大小.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI void GvGetModelUrlA(const char    szModelName[48], char    szModelUrl[260], int& nUrlSize);
	GVAUTOUPDATEAPI void GvGetModelUrlW(const wchar_t szModelName[48], wchar_t szModelUrl[260], int& nUrlSize);
	#ifdef UNICODE
	#define GvGetModelUrl GvGetModelUrlW
	#else
	#define GvGetModelUrl GvGetModelUrlA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 获取Model的官网FAQ URL.
	 *
	 * 参数：
	 * [in]szModelName    当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 *
	 * [in/out]szFAQUrl   若查找成功, 则返回Model对应的官网FAQ URL
	 *                    否则, 返回技嘉官网FAQ URL
	 *
	 * [in/out]nUrlSize   szFAQUrl缓冲区大小.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI void GvGetFAQUrlA(const char    szModelName[48], char    szFAQUrl[260], int& nUrlSize);
	GVAUTOUPDATEAPI void GvGetFAQUrlW(const wchar_t szModelName[48], wchar_t szFAQUrl[260], int& nUrlSize);
	#ifdef UNICODE
	#define GvGetFAQUrl GvGetFAQUrlW
	#else
	#define GvGetFAQUrl GvGetFAQUrlA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 弹出的更新向导页面, 实现显卡BIOS自动更新(与User互动).
	 *
	 * 参数：
	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 * [in]szCurBiosVer  当前显卡的BIOS版本. 如: F1
	 *
	 * 返回值：无
	 *
	 ****************************************************************************************/
	GVAUTOUPDATEAPI	void GvBiosUpdateA(const char    szModelName[48], const char    szCurBiosVer[10]);
	GVAUTOUPDATEAPI	void GvBiosUpdateW(const wchar_t szModelName[48], const wchar_t szCurBiosVer[10]);
	#ifdef UNICODE
	#define GvBiosUpdate GvBiosUpdateW
	#else
	#define GvBiosUpdate GvBiosUpdateA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 弹出的更新向导页面, 实现显卡BIOS自动更新(与User互动).
	 *
	 * 参数：
	 * [in ]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 * [in ]szCurBiosVer  当前显卡的BIOS版本. 如: F1
	 * [out]szSavePath    用户选择的保存路径
	 *
	 * 返回值：无
	 *
	 ****************************************************************************************/
	GVAUTOUPDATEAPI	void GvBiosUpdatePathA(const char    szModelName[48], const char    szCurBiosVer[10], char szSavePath[260]);
	GVAUTOUPDATEAPI	void GvBiosUpdatePathW(const wchar_t szModelName[48], const wchar_t szCurBiosVer[10], wchar_t szSavePath[260]);
	#ifdef UNICODE
	#define GvBiosUpdatePath GvBiosUpdatePathW
	#else
	#define GvBiosUpdatePath GvBiosUpdatePathA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 弹出的更新向导页面, 实现显卡Driver自动更新(与User互动).
	 *
	 * 参数：
	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 * [in]szCurDrvVer   当前显卡Driver版本. 如: 8.671
	 * [in]szCurDrvDate  当前显卡更新日期. 如: 2001-01-01. 注意: 日期字串格式必须满足:YYYY-MM-DD的格式或者 MM-DD-YYYY格式
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI void GvDriverUpdateA(const char    szModelName[48], const char    szCurDrvVer[48], const char    szCurDrvDate[16]);
	GVAUTOUPDATEAPI void GvDriverUpdateW(const wchar_t szModelName[48], const wchar_t szCurDrvVer[48], const wchar_t szCurDrvDate[16]);
	#ifdef UNICODE
	#define GvDriverUpdate GvDriverUpdateW
	#else
	#define GvDriverUpdate GvDriverUpdateA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 弹出的更新向导页面, 实现显卡工具自动更新(与User互动).
	 *
	 * 参数：
	 * [in]nUtility      待更新工具类型, 见本文件定义. 如AUDT_UTILITY_OCGURU.
	 * [in]curVersion    待更新工具当前运行的版本号. 可通过GvGetModuleVersion()获取.
 	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH. 可为NULL.
 	 *                   若为NULL时, 则忽略新版工具(若存在)与当前平台显卡的兼容性, 直接Update.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI void GvUtilityUpdateA(int nUtility, AUDT_FILEVERSION curVersion, char*    szModelName=NULL);
	GVAUTOUPDATEAPI void GvUtilityUpdateW(int nUtility, AUDT_FILEVERSION curVersion, wchar_t* szModelName=NULL);
	#ifdef UNICODE
	#define GvUtilityUpdate GvUtilityUpdateW
	#else
	#define GvUtilityUpdate GvUtilityUpdateA
	#endif // !UNICODE


	/****************************************************************************************
	 * 功能描述：
	 * 实现显卡工具新版本更新检测(无需与User互动).
	 *
	 * 参数：
	 * [in]nUtility      待更新工具类型, 见本文件定义. 如AUDT_UTILITY_OCGURU.
	 * [in]curVersion    待更新工具当前运行的版本号. 可通过GvGetModuleVersion()获取.
	 * [in/out]szUrl     当检测到更新版本时，返回更新版本的下载链接地址.
	 * [in/out]nUrlSize  缓冲区的大小.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvCheckUtiUpdateA(int nUtility, AUDT_FILEVERSION curVersion, char    szUrl[260], int& nUrlSize);
	GVAUTOUPDATEAPI BOOL GvCheckUtiUpdateW(int nUtility, AUDT_FILEVERSION curVersion, wchar_t szUrl[260], int& nUrlSize);
	#ifdef UNICODE
	#define GvCheckUtiUpdate GvCheckUtiUpdateW
	#else
	#define GvCheckUtiUpdate GvCheckUtiUpdateA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 获取指定路径下的程序(exe/dll)版本号.
	 *
	 * 参数：
	 * [in]szModuleName  程序所在路径. 支持绝对路径或相对路径. 相对路径指的是相对本DLL的存放路径.
	 * [in]bRelative	 为TRUE, szModuleName包含的为相对路径; 否则为绝对路径;
	 * [out]pVersion     存放获取到的版本号.
	 *
	 * 返回值：TRUE表示获取成功, FALSE表示获取失败.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvGetModuleVersionA(const char*    szModuleName, BOOL bRelative, PAUDT_FILEVERSION pVersion);
	GVAUTOUPDATEAPI BOOL GvGetModuleVersionW(const wchar_t* szModuleName, BOOL bRelative, PAUDT_FILEVERSION pVersion);
	#ifdef UNICODE
	#define GvGetModuleVersion GvGetModuleVersionW
	#else
	#define GvGetModuleVersion GvGetModuleVersionA
	#endif // !UNICODE


	/****************************************************************************************
	 * 功能描述：
	 * 获取GIGABYTE官网上的所有机种列表. 使用时GvGetModels()时, 先调用GvGetModels(NULL, nCount)
	 * 获取Model个数, 再由调用者分配内存, 再调用GvGetModels(pszModels, nCount)获取机种列表
	 *
	 * 参数：
	 * [in/out]pszModels 存放机种列表的Buffer
	 * [in/out]nCount    当pszModels为NULL时, 由nCount返回机种列表个数, 当不为NULL时, 表示
	 *                   pszModels Buffer含有多少个AUDT_MODEL;
	 *
	 * 返回值：TRUE表示获取成功, FALSE表示获取失败.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvGetModelsA(PAUDT_MODELA& pszModels, int& nCount);
	GVAUTOUPDATEAPI BOOL GvGetModelsW(PAUDT_MODELW& pszModels, int& nCount);
	#ifdef UNICODE
	#define GvGetModels GvGetModelsW
	#else
	#define GvGetModels GvGetModelsA
	#endif // !UNICODE


	/****************************************************************************************
	 * 功能描述：
	 * 获取GIGABYTE官网上指定机种的的所有BIOS列表. 使用时GvGetBioses()时, 先调用GvGetBioses(szModelName, NULL, nCount)
	 * 获取Bios个数, 再由调用者分配内存, 再调用GvGetBioses(szModelName, pszBioses, nCount)获取Bios列表
	 *
	 * 参数：
	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH
	 * [in/out]pszModels 存放Bios列表的Buffer
	 * [in/out]nCount    当pszBioses为NULL时, 由nCount返回机种列表个数, 当不为NULL时, 表示
	 *                   pszBioses Buffer含有多少个AUDT_BIOSINFO;
	 *
	 * 返回值：TRUE表示获取成功, FALSE表示获取失败.
	 *
	 ****************************************************************************************/
	GVAUTOUPDATEAPI	BOOL GvGetBiosesA(const char    szModelName[48], PAUDT_BIOSINFOA& pszBioses, int& nCount);
	GVAUTOUPDATEAPI	BOOL GvGetBiosesW(const wchar_t szModelName[48], PAUDT_BIOSINFOW& pszBioses, int& nCount);
	#ifdef UNICODE
	#define GvGetBioses GvGetBiosesW
	#else
	#define GvGetBioses GvGetBiosesA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 实现显卡Bios新版本更新检测(无需与User互动).
	 *
	 * 参数：
	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH.
	 * [in]sCurBiosVer   当前显卡的BIOS版本. 如: F1.
	 * [in/out]szUrl     当检测到更新版本时，返回更新版本的下载链接地址.
	 * [in/out]nUrlSize  缓冲区的大小.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvCheckBiosUpdateA(char    szModelName[48], const char	   szCurBiosVer[10], char    szUrl[260], int& nUrlSize);
	GVAUTOUPDATEAPI BOOL GvCheckBiosUpdateW(wchar_t szModelName[48], const wchar_t szCurBiosVer[10], wchar_t szUrl[260], int& nUrlSize);
	#ifdef UNICODE
	#define GvCheckBiosUpdate GvCheckBiosUpdateW
	#else
	#define GvCheckBiosUpdate GvCheckBiosUpdateA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 实现显卡Bios新版本更新检测(无需与User互动)，包含Bios信息.
	 *
	 * 参数：
	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH.
	 * [in]sCurBiosVer   当前显卡的BIOS版本. 如: F1.
	 * [in/out]szUrl     当检测到更新版本时，返回更新版本的下载链接地址.
	 * [in/out]nUrlSize  缓冲区的大小.
	 * [out]pszBioses    Bios信息，包含版本，更新日期和Release Note.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvBiosUpdateDetailA(char    szModelName[48], const char	szCurBiosVer[10], char    szUrl[260], int& nUrlSize, PAUDT_BIOSINFOA pszBioses);
	GVAUTOUPDATEAPI BOOL GvBiosUpdateDetailW(wchar_t szModelName[48], const wchar_t szCurBiosVer[10], wchar_t szUrl[260], int& nUrlSize, PAUDT_BIOSINFOW pszBioses);
	#ifdef UNICODE
	#define GvBiosUpdateDetail GvBiosUpdateDetailW
	#else
	#define GvBiosUpdateDetail GvBiosUpdateDetailA
	#endif // !UNICODE

	/****************************************************************************************
	 * 功能描述：
	 * 弹出的更新向导页面, 实现显卡工具自动更新(与User互动).
	 *
	 * 参数：
	 * [in]nUtility      待更新工具类型, 见本文件定义. 如AUDT_UTILITY_OCGURU.
	 * [in]curVersion    待更新工具当前运行的版本号. 可通过GvGetModuleVersion()获取.
 	 * [in]szModelName   当前显卡Model名称. 注意, 必须为完整Model名称, 如: GV-RX16P256D-RH. 可为NULL.
 	 *                   若为NULL时, 则忽略新版工具(若存在)与当前平台显卡的兼容性, 直接Update.
	 *
	 * 返回值：无
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI void GvUtilityUpdatePathA(int nUtility, AUDT_FILEVERSION curVersion, char*    szModelName=NULL, char* szSavePath=NULL, int nPathSize = 0);
	GVAUTOUPDATEAPI void GvUtilityUpdatePathW(int nUtility, AUDT_FILEVERSION curVersion, wchar_t* szModelName=NULL, wchar_t* szSavePath=NULL, int nPathSize = 0);
	#ifdef UNICODE
	#define GvUtilityUpdatePath GvUtilityUpdatePathW
	#else
	#define GvUtilityUpdatePath GvUtilityUpdatePathA
	#endif // !UNICODE

}


#endif 
