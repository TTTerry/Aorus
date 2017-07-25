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
	 * ����������
	 * �жϱ�dllΪUNICODE-DLL����ANSI-DLL. 
	 *
	 * ����ֵ������TRUEΪUNICODE-DLL, FALSEΪANSI-DLL.
	 * 
	 ****************************************************************************************/
	GVAUTOUPDATEAPI BOOL GvIsAutoUpdateUnicode();

	/****************************************************************************************
	 * ����������
	 * �ӹ����л�ȡModel��ͼƬ����. ���ø�API�ɹ���ǰ��Ϊƽ̨��������״̬��.
	 *
	 * ������
	 * [in]szModelName      ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    ��ǰ�Կ�Model�İ汾��. ��1.1. ��ֵ��ΪNULL.
	 *
	 * [out]szUrl           ���óɹ�ʱ, ����Model��ͼƬUrl.
	 *
	 * ����ֵ���ɹ�����TRUE. ���򷵻�FALSE.
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
	 * ����������
	 * �ӹ����л�ȡModel��specification, ������д��ָ��Ini�ļ���. ���ø�API�ɹ���ǰ��Ϊƽ̨��������״̬��.
	 *
	 * ������
	 * [in]szModelName      ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    ��ǰ�Կ�Model�İ汾��. ��1.1. ��ֵ��ΪNULL.
	 *
	 * [in]szIniFile        ���óɹ�ʱ, ���Model specification��Ini·��.
	 *
	 * ����ֵ���ɹ�����TRUE. ���򷵻�FALSE.
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
	 * ����������
	 * �ӹ����л�ȡModel��specification. ���ø�API�ɹ���ǰ��Ϊƽ̨��������״̬��.
	 *
	 * ������
	 * [in]szModelName      ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 *
	 * [in]szRevision	    ��ǰ�Կ�Model�İ汾��. ��1.1. ��ֵ��ΪNULL.
	 *
	 * [out]PAUDT_MODELSPEC ���óɹ�ʱ, ����Model�Ĺ�����. ע��: ���óɹ�ʱ, ����AUDT_MODELSPEC
	 *                      �ṹ���е���������ֵ, ���ݸñ���ֵ�Ƿ�Ϊ��(��"")���жϸ����Ƿ���ֵ.
	 *
	 * ����ֵ���ɹ�����TRUE. ���򷵻�FALSE.
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
	 * ����������
	 * ��ȡModel�Ĺ���URL.
	 *
	 * ������
	 * [in]szModelName    ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 *
	 * [in/out]szModelUrl �����ҳɹ�, �򷵻�Model��Ӧ�Ĺ���URL
	 *                    ����, ���ؼ��ι���URL
	 *
	 * [in/out]nUrlSize   szModelUrl��������С.
	 *
	 * ����ֵ����
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
	 * ����������
	 * ��ȡModel�Ĺ���FAQ URL.
	 *
	 * ������
	 * [in]szModelName    ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 *
	 * [in/out]szFAQUrl   �����ҳɹ�, �򷵻�Model��Ӧ�Ĺ���FAQ URL
	 *                    ����, ���ؼ��ι���FAQ URL
	 *
	 * [in/out]nUrlSize   szFAQUrl��������С.
	 *
	 * ����ֵ����
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
	 * ����������
	 * �����ĸ�����ҳ��, ʵ���Կ�BIOS�Զ�����(��User����).
	 *
	 * ������
	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 * [in]szCurBiosVer  ��ǰ�Կ���BIOS�汾. ��: F1
	 *
	 * ����ֵ����
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
	 * ����������
	 * �����ĸ�����ҳ��, ʵ���Կ�BIOS�Զ�����(��User����).
	 *
	 * ������
	 * [in ]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 * [in ]szCurBiosVer  ��ǰ�Կ���BIOS�汾. ��: F1
	 * [out]szSavePath    �û�ѡ��ı���·��
	 *
	 * ����ֵ����
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
	 * ����������
	 * �����ĸ�����ҳ��, ʵ���Կ�Driver�Զ�����(��User����).
	 *
	 * ������
	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 * [in]szCurDrvVer   ��ǰ�Կ�Driver�汾. ��: 8.671
	 * [in]szCurDrvDate  ��ǰ�Կ���������. ��: 2001-01-01. ע��: �����ִ���ʽ��������:YYYY-MM-DD�ĸ�ʽ���� MM-DD-YYYY��ʽ
	 *
	 * ����ֵ����
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
	 * ����������
	 * �����ĸ�����ҳ��, ʵ���Կ������Զ�����(��User����).
	 *
	 * ������
	 * [in]nUtility      �����¹�������, �����ļ�����. ��AUDT_UTILITY_OCGURU.
	 * [in]curVersion    �����¹��ߵ�ǰ���еİ汾��. ��ͨ��GvGetModuleVersion()��ȡ.
 	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH. ��ΪNULL.
 	 *                   ��ΪNULLʱ, ������°湤��(������)�뵱ǰƽ̨�Կ��ļ�����, ֱ��Update.
	 *
	 * ����ֵ����
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
	 * ����������
	 * ʵ���Կ������°汾���¼��(������User����).
	 *
	 * ������
	 * [in]nUtility      �����¹�������, �����ļ�����. ��AUDT_UTILITY_OCGURU.
	 * [in]curVersion    �����¹��ߵ�ǰ���еİ汾��. ��ͨ��GvGetModuleVersion()��ȡ.
	 * [in/out]szUrl     ����⵽���°汾ʱ�����ظ��°汾���������ӵ�ַ.
	 * [in/out]nUrlSize  �������Ĵ�С.
	 *
	 * ����ֵ����
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
	 * ����������
	 * ��ȡָ��·���µĳ���(exe/dll)�汾��.
	 *
	 * ������
	 * [in]szModuleName  ��������·��. ֧�־���·�������·��. ���·��ָ������Ա�DLL�Ĵ��·��.
	 * [in]bRelative	 ΪTRUE, szModuleName������Ϊ���·��; ����Ϊ����·��;
	 * [out]pVersion     ��Ż�ȡ���İ汾��.
	 *
	 * ����ֵ��TRUE��ʾ��ȡ�ɹ�, FALSE��ʾ��ȡʧ��.
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
	 * ����������
	 * ��ȡGIGABYTE�����ϵ����л����б�. ʹ��ʱGvGetModels()ʱ, �ȵ���GvGetModels(NULL, nCount)
	 * ��ȡModel����, ���ɵ����߷����ڴ�, �ٵ���GvGetModels(pszModels, nCount)��ȡ�����б�
	 *
	 * ������
	 * [in/out]pszModels ��Ż����б��Buffer
	 * [in/out]nCount    ��pszModelsΪNULLʱ, ��nCount���ػ����б����, ����ΪNULLʱ, ��ʾ
	 *                   pszModels Buffer���ж��ٸ�AUDT_MODEL;
	 *
	 * ����ֵ��TRUE��ʾ��ȡ�ɹ�, FALSE��ʾ��ȡʧ��.
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
	 * ����������
	 * ��ȡGIGABYTE������ָ�����ֵĵ�����BIOS�б�. ʹ��ʱGvGetBioses()ʱ, �ȵ���GvGetBioses(szModelName, NULL, nCount)
	 * ��ȡBios����, ���ɵ����߷����ڴ�, �ٵ���GvGetBioses(szModelName, pszBioses, nCount)��ȡBios�б�
	 *
	 * ������
	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH
	 * [in/out]pszModels ���Bios�б��Buffer
	 * [in/out]nCount    ��pszBiosesΪNULLʱ, ��nCount���ػ����б����, ����ΪNULLʱ, ��ʾ
	 *                   pszBioses Buffer���ж��ٸ�AUDT_BIOSINFO;
	 *
	 * ����ֵ��TRUE��ʾ��ȡ�ɹ�, FALSE��ʾ��ȡʧ��.
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
	 * ����������
	 * ʵ���Կ�Bios�°汾���¼��(������User����).
	 *
	 * ������
	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH.
	 * [in]sCurBiosVer   ��ǰ�Կ���BIOS�汾. ��: F1.
	 * [in/out]szUrl     ����⵽���°汾ʱ�����ظ��°汾���������ӵ�ַ.
	 * [in/out]nUrlSize  �������Ĵ�С.
	 *
	 * ����ֵ����
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
	 * ����������
	 * ʵ���Կ�Bios�°汾���¼��(������User����)������Bios��Ϣ.
	 *
	 * ������
	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH.
	 * [in]sCurBiosVer   ��ǰ�Կ���BIOS�汾. ��: F1.
	 * [in/out]szUrl     ����⵽���°汾ʱ�����ظ��°汾���������ӵ�ַ.
	 * [in/out]nUrlSize  �������Ĵ�С.
	 * [out]pszBioses    Bios��Ϣ�������汾���������ں�Release Note.
	 *
	 * ����ֵ����
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
	 * ����������
	 * �����ĸ�����ҳ��, ʵ���Կ������Զ�����(��User����).
	 *
	 * ������
	 * [in]nUtility      �����¹�������, �����ļ�����. ��AUDT_UTILITY_OCGURU.
	 * [in]curVersion    �����¹��ߵ�ǰ���еİ汾��. ��ͨ��GvGetModuleVersion()��ȡ.
 	 * [in]szModelName   ��ǰ�Կ�Model����. ע��, ����Ϊ����Model����, ��: GV-RX16P256D-RH. ��ΪNULL.
 	 *                   ��ΪNULLʱ, ������°湤��(������)�뵱ǰƽ̨�Կ��ļ�����, ֱ��Update.
	 *
	 * ����ֵ����
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
