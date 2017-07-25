#ifndef _GVDISPLAY_H
#define _GVDISPLAY_H

#ifdef  GVDISPLAY_EXPORTS
#define GVDISPLAY_API __declspec(dllexport) 
#else
#define GVDISPLAY_API __declspec(dllimport) 
#endif


////////////////////////////////////////////////////////////////////////////////////
// Defined for error code
// 
#define GVAPI_OK							0x00000000
#define GVAPI_DISP_FAILED					0x00000001
#define GVAPI_DISP_UNSUPPORTED				0x20000002
#define GVAPI_DISP_INVALID_PARAMETER		0x20000003
#define GVAPI_DISP_INVALID_DRIVER			0x20000004
#define GVAPI_DISP_INVALID_HANDLE			0x20000005
#define GVAPI_DISP_LIB_NOTREADY				0x20000006
#define GVAPI_DISP_LIB_AREADYINIT			0x20000007
#define GVAPI_DISP_LIB_DESTROYED			0x20000008
#define GVAPI_DISP_DEVICE_CONFLICT			0x20000009
#define GVAPI_DISP_UNKNOWN_CARDTYPE			0x2000000A
#define GVAPI_DISP_XDECRYPT_FAILED			0x2000000B
#define GVAPI_DISP_ATIPDL_UNSUPPORTED		0x2000000C
#define GVAPI_DISP_ATIADL_UNSUPPORTED		0x2000000D
#define GVAPI_DISP_UNKNOWN_CHIPTYPE			0x2000000E
#define GVAPI_DISP_INVALID_PWMINI			0x2000000F

#define GVAPI_DISP_NVINIT_FAILED			0x20000100
#define GVAPI_DISP_NVHANDLE_INVALID			0x20000101
#define GVAPI_DISP_NVPSTATES_GET_FAILED		0x20000102
#define GVAPI_DISP_NVPSTATES_SET_FAILED		0x20000103
#define GVAPI_DISP_NVPERFCLK_GET_FAILED		0x20000104
#define GVAPI_DISP_NVPERFCLK_SET_FAILED		0x20000105
#define GVAPI_DISP_NVCOOLER_GET_FAILED		0x20000106
#define GVAPI_DISP_NVCOOLER_SET_FAILED		0x20000107
#define GVAPI_DISP_NVTACHREAD_GET_FAILED	0x20000108
#define GVAPI_DISP_NVTACHREAD_SET_FAILED	0x20000109
#define GVAPI_DISP_NVALLCLKFQ_GET_FAILED	0x2000010A
#define GVAPI_DISP_NVPSTATES20_GET_FAILED	0x2000010C
#define GVAPI_DISP_NVPSTATES20_SET_FAILED	0x2000010D
#define GVAPI_DISP_NVALLCLKFRQS_GET_FAILED	0x2000010E
#define GVAPI_DISP_NVPWPOLINFO_GET_FAILED	0x2000010F
#define GVAPI_DISP_NVPWPOLSTUS_GET_FAILED	0x20000110
#define GVAPI_DISP_NVPWPOLSTUS_SET_FAILED	0x20000111
#define GVAPI_DISP_NVPWTOPINFO_GET_FAILED	0x20000112 
#define GVAPI_DISP_NVPWTOPSTUS_GET_FAILED	0x20000113 
#define GVAPI_DISP_NVTMPOLINFO_GET_FAILED	0x20000114
#define GVAPI_DISP_NVTMPOLSTUS_GET_FAILED	0x20000115
#define GVAPI_DISP_NVTMPOLSTUS_SET_FAILED	0x20000116
#define GVAPI_DISP_NVTMTOPINFO_GET_FAILED	0x20000117 
#define GVAPI_DISP_NVTMTOPSTUS_GET_FAILED	0x20000118 
#define GVAPI_DISP_NVVOLDMSTUS_GET_FAILED	0x20000119 
#define GVAPI_DISP_NVI2CREADEXFAILED		0x20000120 
#define GVAPI_DISP_NVGETVOLTAGES_GET_FAILED	0x20000121 
#define GVAPI_DISP_NVGETDOMAINS_GET_FAILED	0x20000122 
#define GVAPI_DISP_CONNDISP_GET_FAILED		0x20000123
#define GVAPI_DISP_TIMING_GET_FAILED		0x20000124
#define GVAPI_DISP_TRYDISP_SET_FAILED		0x20000125
#define GVAPI_DISP_SAVEDISP_SET_FAILED		0x20000126
#define GVAPI_DISP_QUERYSLI_SUP_FAILED		0x20000127
#define GVAPI_DISP_SLILIGHT_SET_FAILED		0x20000128
#define GVAPI_DISP_DOMAINIFO_GET_FAILED		0x20000129
#define GVAPI_DISP_VFPOINTINFO_GET_FAILED	0x20000130
#define GVAPI_DISP_VFPOINTSTATUS_GET_FAILED	0x20000131
#define GVAPI_DISP_VFPOINTS_GET_FAILED		0x20000132
#define GVAPI_DISP_VFPOINTS_SET_FAILED		0x20000133
#define GVAPI_DISP_INVALID_VFPOINTINDEX		0x20000134
#define GVAPI_DISP_VFPOINT_ISFIXED			0x20000135
#define GVAPI_DISP_VOLTRAILS_GET_FAILED		0x20000136
#define GVAPI_DISP_VOLTRAILS_SET_FAILED		0x20000137
#define GVAPI_DISP_LOCKCLK_GET_FAILED		0x20000138
#define GVAPI_DISP_LOCKCLK_SET_FAILED		0x20000139
#define GVAPI_DISP_LOCKVOL_GET_FAILED		0x20000140
#define GVAPI_DISP_LOCKVOL_SET_FAILED		0x20000141

#define GVAPI_DISP_ATIINIT_FAILED			0x20000200
#define GVAPI_DISP_ATIHANDLE_INVALID		0x20000201
#define GVAPI_DISP_ATIODPARAM_GET_FAILED	0x20000202
#define GVAPI_DISP_ATIODPERFL_GET_FAILED	0x20000203
#define GVAPI_DISP_ATIODPERFL_SET_FAILED	0x20000204
#define GVAPI_DISP_ATIFANINFO_GET_FAILED	0x20000205
#define GVAPI_DISP_ATIFANSPD_GET_FAILED		0x20000206
#define GVAPI_DISP_ATIFANSPD_SET_FAILED		0x20000207
#define GVAPI_DISP_ATIFANDEF_SET_FAILED		0x20000208
#define GVAPI_DISP_ATIPMACT_GET_FAILED		0x20000209
#define GVAPI_DISP_ATIWRI2C_FAILED			0x20000210

//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for video graphics adapter
// 
#define GVDISP_VGATYPE_ATI				0x01
#define GVDISP_VGATYPE_NVIDIA			0x02

#define GVDISP_CARD_MAXNUM				0x0A
#define GVDISP_PLEVEL_MAXNUM			0x0F
#define GVDISP_FANCURVE_MAXNUM			0x0F
#define GVDISP_VFPT_MAXNUM				0xF0
//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for basic used
//

// VGA card information
typedef struct _GVDISP_VGA_INFO {

	int   nNumCards;
	int   nCardTypes[GVDISP_CARD_MAXNUM];			// NVIDIA or ATI
	int	  nMemorySizes[GVDISP_CARD_MAXNUM];// MB	// Memory size of VGAs
	
	WORD  wVIDs [GVDISP_CARD_MAXNUM];				// Vendor ID
	WORD  wDIDs [GVDISP_CARD_MAXNUM];				// Device ID
	WORD  wSSIDs[GVDISP_CARD_MAXNUM];				//  
	WORD  wSVIDs[GVDISP_CARD_MAXNUM];				// Sub vendor ID
	
	TCHAR szDevDescs   [GVDISP_CARD_MAXNUM][64];	// VGA chipset description: GeForce 7100 GS
	TCHAR szDrvDates   [GVDISP_CARD_MAXNUM][32];	// VGA driver date : 11-20-2009
	TCHAR szDrvVersions[GVDISP_CARD_MAXNUM][32];	// VGA driver version : 6.14.11.9562

	struct {										// VGA's Bus information, that is VGA device location.

	BYTE acBus;
	BYTE acDevice;
	BYTE acFunction;

	} stLocs[GVDISP_CARD_MAXNUM];

} GVDISP_VGA_INFO, *PGVDISP_VGA_INFO;


typedef struct _GVDISP_PARAM_RANGE {

	LONG nMax;
	LONG nMin;
	LONG nStep;

} GVDISP_PARAM_RANGE, *PGVDISP_PARAM_RANGE;

typedef enum _GVDISP_CTRL_MODE {		// Perf control mode. 
	
	GVDISP_CTRL_MODE_DRIVER = 0,
	GVDISP_CTRL_MODE_FIRMWARE,

} GVDISP_CTRL_MODE, *PGVDISP_CTRL_MODE;

////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for clocks operations
// 
typedef enum _GVDISP_CLOCK_DOMAIN_ID {
	
	GVDISP_CLOCK_DOMAIN_ID_GPU = 0,
	GVDISP_CLOCK_DOMAIN_ID_MEMORY,
	GVDISP_CLOCK_DOMAIN_ID_SHADER,

} GVDISP_CLOCK_DOMAIN_ID;

typedef struct _GVDISP_CLOCK_INFO {

	int nNumPerfLs;
	GVDISP_PARAM_RANGE stRanges[GVDISP_PLEVEL_MAXNUM]; // MHz

} GVDISP_CLOCK_INFO, *PGVDISP_CLOCK_INFO;

typedef struct _GVDISP_CLOCKS {

	int nNumPerfLs;
	int nPerfLClocks[GVDISP_PLEVEL_MAXNUM]; // MHz

} GVDISP_CLOCKS, *PGVDISP_CLOCKS;

typedef struct _GVDISP_CLOCK_VFINFO {

	GVDISP_PARAM_RANGE stVfIndex;
	GVDISP_PARAM_RANGE stRangesd; // MHz

} GVDISP_CLOCK_VFINFO, *PGVDISP_CLOCK_VFINFO;


typedef struct _GVDISP_CLOCK_VFPT {

	int nIndex;
	struct
	{
		long nVoltage;	// uV
		int nClock;		// MHz
	}value; 

} GVDISP_CLOCK_VFPT, *PGVDISP_CLOCK_VFPT;

typedef struct _GVDISP_CLOCK_VFPTS {

	int nNumVFPoints;
	GVDISP_CLOCK_VFPT vfs[GVDISP_VFPT_MAXNUM]; // MHz

} GVDISP_CLOCK_VFPTS, *PGVDISP_CLOCK_VFPTS;

typedef struct _GVDISP_CLOCK_VFOFFSET {

	int nIndex;
	int nOffset;

} GVDISP_CLOCK_VFOFFSET, *PGVDISP_CLOCK_VFOFFSET;

typedef struct _GVDISP_CLOCK_VFSET {

	int nNumVFPoints;
	GVDISP_CLOCK_VFOFFSET offset[GVDISP_VFPT_MAXNUM]; 

} GVDISP_CLOCK_VFSET, *PGVDISP_CLOCK_VFSET;

//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for display operations
// 
typedef enum _GVDISP_DISPLAY_DOMAIN_ID {

	GVDISP_DISPLAY_DOMAIN_ID_CLOCK = 0,

} GVDISP_DISPLAY_DOMAIN_ID;

typedef struct _GVDISP_DISPLAY_INFO {

	GVDISP_PARAM_RANGE stRanges; // MHz

} GVDISP_DISPLAY_INFO, *PGVDISP_DISPLAY_INFO;

typedef struct _GVDISP_DISPLAY {

	int nWidth;
	int nHeight;
	int nColor;
	int nRefreshRate; // MHz
	int nPixelClock; // 10^4 MHz

} GVDISP_DISPLAY, *PGVDISP_DISPLAY;

typedef struct _GVDISP_DISPLAY_RANGE {

// 	GVDISP_PARAM_RANGE stAllowedRanges; // MHz
// 	GVDISP_PARAM_RANGE stDisallowedRanges; // MHz
	int nWidth;
	int nHeight;
	GVDISP_PARAM_RANGE stDisplay; 

} GVDISP_DISPLAY_RANGE, *PGVDISP_DISPLAY_RANGE;

//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for voltages operations
// 

typedef enum _GVDISP_VOLTAGE_DOMAIN_ID {
	
	GVDISP_VOLTAGE_DOMAIN_ID_GPU = 0,
	GVDISP_VOLTAGE_DOMAIN_ID_MEMORY,
	GVDISP_VOLTAGE_DOMAIN_ID_PCIE,
	GVDISP_VOLTAGE_DOMAIN_ID_VDDCI,
	GVDISP_VOLTAGE_DOMAIN_ID_MAX,

} GVDISP_VOLTAGE_DOMAIN_ID;

typedef enum _GVDISP_VOLTAGE_TYPE {		// Voltage type.		

		GVDISP_VOLTAGE_TYPE_LEVEL = 0,	// Voltage level
		GVDISP_VOLTAGE_TYPE_VALUE,		// Voltage value

} GVDISP_VOLTAGE_TYPE, *PGVDISP_VOLTAGE_TYPE;

typedef struct _GVDISP_VOLTAGE_INFO {

	GVDISP_PARAM_RANGE stLevel;			// Voltage level range
	GVDISP_PARAM_RANGE stRange;	// uV	// Voltage value range

} GVDISP_VOLTAGE_INFO, *PGVDISP_VOLTAGE_INFO;

typedef struct _GVDISP_VOLTAGES {

	int  nLevel;					// Voltage level
	LONG nVoltage;	// uV			// Voltage Value. 

} GVDISP_VOLTAGES, *PGVDISP_VOLTAGES;
//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for fan speed operations. Used in Fan APIs
// 

typedef enum _GVDISP_FANSPD_TYPE {		// Fan speed type.		

		GVDISP_FANSPD_TYPE_PERCENT = 0,
		GVDISP_FANSPD_TYPE_RPM,

} GVDISP_FANSPD_TYPE, *PGVDISP_FANSPD_TYPE;

typedef struct _GVDISP_FANSPEED_INFO {

	GVDISP_PARAM_RANGE stRange;	// Fan speed range. 

} GVDISP_FANSPEED_INFO, *PGVDISP_FANSPEED_INFO;

typedef enum _GVDISP_FANCTRL_MODE {		// Fan speed ctrl mode.		

		GVDISP_FANCTRL_MODE_AUTO = 0,
		GVDISP_FANCTRL_MODE_MANUAL,

} GVDISP_FANCTRL_MODE, *PGVDISP_FANCTRL_MODE;

typedef struct _GVDISP_FANCURVE {

	
	GVDISP_FANCTRL_MODE	mode;		// Auto/Manual mode.
	int nStepCount;					// steps of fan curve. <!! it will be ingored if mode=GVDISP_FANCTRL_MODE_AUTO >

	struct							
	{
		int nDB;
		int nTemperature;	
	} steps[GVDISP_FANCURVE_MAXNUM];	// <!! it will be ingored if mode=GVDISP_FANCTRL_MODE_AUTO >		

} GVDISP_FANCURVE, *PGVDISP_FANCURVE;

//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Defined for power operations
// <!! ONLY used for Nvidia's new series. (after N680) >

typedef struct _GVDISP_POWER_INFO {

	GVDISP_PARAM_RANGE stRange;

} GVDISP_POWER_INFO, *PGVDISP_POWER_INFO;
//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Defined for temperature operations
// <!! ONLY used for Nvidia's new series. (after N680) >

typedef struct _GVDISP_TEMP_INFO {

	GVDISP_PARAM_RANGE stRange;

} GVDISP_TEMP_INFO, *PGVDISP_TEMP_INFO;
//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Defined for RAM operations
// <!! ONLY used for Nvidia now. >

typedef enum _GVDISP_RAM_TYPE	// type of graphic memory
{
	GVDISP_RAM_TYPE_UNKNOWN = 0, 
    GVDISP_RAM_TYPE_SDRAM,
    GVDISP_RAM_TYPE_DDR1,
    GVDISP_RAM_TYPE_DDR2,
    GVDISP_RAM_TYPE_DDR3,
    GVDISP_RAM_TYPE_DDR4,
    GVDISP_RAM_TYPE_DDR5,
	GVDISP_RAM_TYPE_LPDDR2,
	GVDISP_RAM_TYPE_DDR5X,

} GVDISP_RAM_TYPE, *PGVDISP_RAM_TYPE;
//
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// Defined for Activity operations
// 

// Used in GVDISP_ACTIVITY.dwPerfs
#define GVDISP_PERF_GPUCLK		0x00000001		// GPU clock
#define GVDISP_PERF_MEMCLK		0x00000002		// memory clock
#define GVDISP_PERF_SHDCLK		0x00000004		// shader clock
#define GVDISP_PERF_GPUVOL		0x00000008		// GPU voltage
#define GVDISP_PERF_POWER		0x00000010		// power target. <!! ONLY used for Nvidia's new series. (after N680) >
#define GVDISP_PERF_GPUUSAGE	0x00000020		// GPU usage.
#define GVDISP_PERF_TEMPERATURE	0x00000040		// GPU temperature
#define GVDISP_PERF_ALL			0xffffffff

// Used in GvGetActivity().
typedef struct _GVDISP_ACTIVITY {
	
	DWORD	dwPerfs;				// [in]  Combination of GVDISP_PERF_xx flags. <!! Must set it if you want to get current performance of VGA. >

	int 	nCurPerfLevel;			// [out] VGA's current performance level.
	int		nGpuBaseClock;			// [out] GPU base clock.		<!! ONLY used for Nvidia's new series. (after N680) >
	int		nGpuBoostClock;			// [out] GPU boost clock.		<!! ONLY used for Nvidia's new series. (after N680) >
	int		nMemBaseClock;			// [out] Memory default clock.	<!! ONLY used for Nvidia's new series. (after N680) >
	LONG	nGpuBaseVoltage;  //uV	// [out] GPU default voltage.	<!! ONLY used for Nvidia's new series. (after N680) >
	LONG	nMaxBaseVoltage;		// uV

	struct GVDISP_CUR_PERF
	{
		int		nGpuClock;
		int		nMemoryClock;
		int		nShaderClock;
		LONG	nGpuVoltage;		// uV
		int		nPower;				// <!! ONLY used for Nvidia's new series. (after N680) >
		int		nGpuUsage;
		int		nTemperature;

	} curPerfs;		// [out] current performances of VGA.

} GVDISP_ACTIVITY, *PGVDISP_ACTIVITY;

//
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Defined for PWM operations
// 

// used in GvGetPwmIcType()
typedef enum _GVDISP_PWMIC_TYPE {

	GVDISP_PWMIC_TYPE_UNKNOWN = 0,
	GVDISP_PWMIC_TYPE_CHIL8212,
	GVDISP_PWMIC_TYPE_CHIL8225,
	GVDISP_PWMIC_TYPE_CHIL8228,
	GVDISP_PWMIC_TYPE_CHIL8318,
	GVDISP_PWMIC_TYPE_CHIL3567,
	
} GVDISP_PWMIC_TYPE, *PGVDISP_PWMIC_TYPE;

// PWM phase mode
typedef enum _GVDISP_PWMPHASE_MODE {

	GVDISP_PWMPHASE_MODE_FULL = 0,
	GVDISP_PWMPHASE_MODE_AUTO,	

} GVDISP_PWMPHASE_MODE, *PGVDISP_PWMPHASE_MODE;

// PWM voltage ID
typedef enum _GVDISP_PWMVOLTAGE_ID		
{
	GVDISP_PWMVOLTAGE_ID_12V,		// uV
	GVDISP_PWMVOLTAGE_ID_3V3,		
	GVDISP_PWMVOLTAGE_ID_PCIE,		

} GVDISP_PWMVOLTAGE_ID, *PGVDISP_PWMVOLTAGE_ID;

// PWM domain ID
typedef enum _GVDISP_PWM_DOMAIN_ID
{
	GVDISP_PWM_DOMAIN_ID_GPU,
	GVDISP_PWM_DOMAIN_ID_MEMORY,	
	GVDISP_PWM_DOMAIN_ID_PCIE,		
	GVDISP_PWM_DOMAIN_ID_VDDCI,		

} GVDISP_PWM_DOMAIN_ID, *PGVDISP_PWM_DOMAIN_ID;

typedef struct _GVDISP_PWM_INFO {

	GVDISP_PARAM_RANGE stRange;		

} GVDISP_PWM_INFO, *PGVDISP_PWM_INFO;

//
////////////////////////////////////////////////////////////////////////////////////

// Used in CNvDisplay::ReadI2C() & CNvDisplay::WriteI2C().
typedef struct _GVDISP_I2C_REGADDR
{
	unsigned char	nSavePort;		// The address of the I2C slave.
	int				nRegAddrUsed;	// How many bytes are used in buffer szRegAddr[].
	unsigned char	szRegAddr[8];	// The I2C target register address buffer. Fill it with command & data.
	int				nDataSize;		// The Data Size
	int				nI2cSpeed;		// I2C Speed
	unsigned char	nDDCPort;		// I2C DDC Port; 1= B, 2 = C

} GVDISP_I2C_REGADDR, *PGVDISP_I2C_REGADDR;
//
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Defined for lock clocks operations
// 
typedef enum _GVDISP_LOCK_DOMAIN_ID {

	GVDISP_LOCK_DOMAIN_ID_GPU = 0,
	GVDISP_LOCK_DOMAIN_ID_MEMORY,
	GVDISP_LOCK_DOMAIN_ID_VOLTAGE,

} GVDISP_LOCK_DOMAIN_ID;


extern "C"
{
	// Base information APIs
	GVDISPLAY_API DWORD GvInitDispLib();
	GVDISPLAY_API DWORD GvFreeDispLib();

	GVDISPLAY_API DWORD GvIsVgaOnBoard(BOOL& bOnBoard);			// If monitor connect to On-Board VGA,  return TRUE.
	GVDISPLAY_API DWORD GvIsNvNewSeries(BOOL& bNewNvSerials);
	GVDISPLAY_API DWORD GvIsNvBoost2(BOOL& bNvBoost2);
	GVDISPLAY_API DWORD GvIsNvBoost3(BOOL& bNvBoost3);
	GVDISPLAY_API DWORD GvGetVgaInfo(PGVDISP_VGA_INFO pInfo);
	GVDISPLAY_API DWORD GvGetRamType(int nGpuIndex, GVDISP_RAM_TYPE& type);
	
	// Voltages APIs
	// <!! For Nvidia's new series(after N680), we operate the offset value. >
	GVDISPLAY_API DWORD GvGetPerfVoltageInfo(int nGpuIndex, GVDISP_VOLTAGE_DOMAIN_ID id, PGVDISP_VOLTAGE_INFO pInfo, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);
	GVDISPLAY_API DWORD GvGetPerfVoltage(int nGpuIndex, GVDISP_VOLTAGE_DOMAIN_ID id, PGVDISP_VOLTAGES pVols, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);
	GVDISPLAY_API DWORD GvGetPerfVoltageDefault(int nGpuIndex, GVDISP_VOLTAGE_DOMAIN_ID id, PGVDISP_VOLTAGES pVols, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);

	GVDISPLAY_API DWORD GvSetPerfVoltage(int nGpuIndex, GVDISP_VOLTAGE_DOMAIN_ID id, GVDISP_VOLTAGE_TYPE type, LONG nVol, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);
	GVDISPLAY_API DWORD GvSetPerfVoltageDefault(int nGpuIndex, GVDISP_VOLTAGE_DOMAIN_ID id, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);

	// Over Voltages APIs
	// <!! For Nvidia's new series(after N1070), we operate the offset value. >
	GVDISPLAY_API DWORD GvGetPerfOVoltageInfo(int nGpuIndex, PGVDISP_PARAM_RANGE pRange);
	GVDISPLAY_API DWORD GvGetPerfOVoltage(int nGpuIndex, int & nPercent);
	GVDISPLAY_API DWORD GvGetPerfOVoltageDefault(int nGpuIndex, int & nPercent);

	GVDISPLAY_API DWORD GvSetPerfOVoltage(int nGpuIndex, int nPercent);
	GVDISPLAY_API DWORD GvSetPerfOVoltageDefault(int nGpuIndex);

	// Clocks APIs
	// <!! For Nvidia's new series(after N680), we operate the offset value. >
	GVDISPLAY_API DWORD GvGetPerfClockInfo(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCK_INFO pInfo);
	GVDISPLAY_API DWORD GvGetPerfClock(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCKS pClks);
	GVDISPLAY_API DWORD GvGetPerfClockDefault(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCKS pClks);

	GVDISPLAY_API DWORD GvSetPerfClock(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, int nPLevel, int nClock);
	GVDISPLAY_API DWORD GvSetPerfClockDefault(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id);

	GVDISPLAY_API DWORD GvGetVfClockInfo(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCK_VFINFO pInfo);
	GVDISPLAY_API DWORD GvGetVfClock(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCK_VFPTS pClks);
	GVDISPLAY_API DWORD GvGetVfClockOffset(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCK_VFSET pClks);
	GVDISPLAY_API DWORD GvGetVfClockSet(int nGpuIndex, int nIndex, int& nClock);
	GVDISPLAY_API DWORD GvGetVfClockDefault(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, PGVDISP_CLOCK_VFPTS pClks);

	GVDISPLAY_API DWORD GvSetVfClock(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id, int nIndex, int nClock);
	GVDISPLAY_API DWORD GvSetVfClockDefault(int nGpuIndex, GVDISP_CLOCK_DOMAIN_ID id);

	// Display APIs
	// <!! For Nvidia's new series(after N680), we operate the offset value. >
	GVDISPLAY_API DWORD GvGetPerfDisplayClockRange(int nGpuIndex, GVDISP_DISPLAY_DOMAIN_ID id, PGVDISP_DISPLAY_RANGE pRange);
	GVDISPLAY_API DWORD GvGetPerfDisplayClock(int nGpuIndex, GVDISP_DISPLAY_DOMAIN_ID id, PGVDISP_DISPLAY pClks);
	GVDISPLAY_API DWORD GvGetPerfDisplayClockDefault(int nGpuIndex, GVDISP_DISPLAY_DOMAIN_ID id, PGVDISP_DISPLAY pClks);
	GVDISPLAY_API DWORD GvSetPerfDisplayClock(int nGpuIndex, GVDISP_DISPLAY_DOMAIN_ID id, PGVDISP_DISPLAY pClks);

	GVDISPLAY_API DWORD GvSetPerfDisplayClockRange(int nGpuIndex, GVDISP_DISPLAY_DOMAIN_ID id, PGVDISP_DISPLAY_RANGE pRange);

	// Fan APIs
	GVDISPLAY_API DWORD GvGetFanCtrlMode(int nGpuIndex, GVDISP_CTRL_MODE& mode);
	GVDISPLAY_API DWORD GvSetFanCtrlMode(int nGpuIndex, GVDISP_CTRL_MODE  mode);

	GVDISPLAY_API DWORD GvGetFanSpeedInfo(int nGpuIndex, GVDISP_FANSPD_TYPE type, PGVDISP_FANSPEED_INFO pInfo, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);
	GVDISPLAY_API DWORD GvGetCurrentFanSpeed(int nGpuIndex, int iFanIndex, GVDISP_FANSPD_TYPE type, int& nFanSpeed, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);

	GVDISPLAY_API DWORD GvSetCurrentFanSpeed(int nGpuIndex, int iFanIndex, GVDISP_FANSPD_TYPE type, int  nFanSpeed, GVDISP_CTRL_MODE mode=GVDISP_CTRL_MODE_DRIVER);
	GVDISPLAY_API DWORD GvSetFanSpeedDefault(int nGpuIndex); // In default state, fan is controled by driver, in the auto mode.

	// Power APIs 
	// <!! ONLY used for Nvidia's new series. (after N680) >
	GVDISPLAY_API DWORD GvGetPowerInfo(int nGpuIndex, PGVDISP_POWER_INFO pInfo);
	GVDISPLAY_API DWORD GvGetPower(int nGpuIndex, int& nPower);
	GVDISPLAY_API DWORD GvGetPowerDefault(int nGpuIndex, int& nPower);

	GVDISPLAY_API DWORD GvSetPower(int nGpuIndex, int nPower);
	GVDISPLAY_API DWORD GvSetPowerDefault(int nGpuIndex);

	// Temperature APIs 
	// <!! ONLY used for Nvidia's new series. (after N680) > !!!!!! NEW !!!!!!
	GVDISPLAY_API DWORD GvGetTempInfo(int nGpuIndex, PGVDISP_TEMP_INFO pInfo);
	GVDISPLAY_API DWORD GvGetTemp(int nGpuIndex, int& nTemp);
	GVDISPLAY_API DWORD GvGetTempDefault(int nGpuIndex, int& nTemp);

	GVDISPLAY_API DWORD GvSetTemp(int nGpuIndex, int nTemp, bool bRemTdpLim = FALSE);
	GVDISPLAY_API DWORD GvSetTempDefault(int nGpuIndex);

	// Activity APIs
	GVDISPLAY_API DWORD GvGetActivity(int nGpuIndex, PGVDISP_ACTIVITY pActivity);

	// PWM APIs
	GVDISPLAY_API DWORD GvGetPwmVoltage(int nGpuIndex, GVDISP_PWMVOLTAGE_ID id, LONG& nVoltage); // Uint=uV
	GVDISPLAY_API DWORD GvGetPwmCurrent(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, LONG& nCurrent, BOOL bInOut);	// bInOut=TRUE: In; bInOut=FALSE: Out; // Uint=mA
	
	GVDISPLAY_API DWORD GvGetPwmPahseMode(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, GVDISP_PWMPHASE_MODE& mode, int& nCurLeds, int& nTotalLeds);
	GVDISPLAY_API DWORD GvGetPwmPahseModeDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, GVDISP_PWMPHASE_MODE& mode);
	GVDISPLAY_API DWORD GvSetPwmPahseMode(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, GVDISP_PWMPHASE_MODE mode);
	GVDISPLAY_API DWORD GvSetPwmPahseModeDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id);

	GVDISPLAY_API DWORD GvGetPwmLoadLineInfo(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, PGVDISP_PWM_INFO pInfo);	// Uint=%
	GVDISPLAY_API DWORD GvGetPwmLoadLine(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int& nLoadline);
	GVDISPLAY_API DWORD GvGetPwmLoadLineDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int& nLoadline);
	GVDISPLAY_API DWORD GvSetPwmLoadLine(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int nLoadline);
	GVDISPLAY_API DWORD GvSetPwmLoadLineDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id);

	GVDISPLAY_API DWORD GvGetPwmFrqInfo(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, PGVDISP_PWM_INFO pInfo); // Uint=KHz
	GVDISPLAY_API DWORD GvGetPwmFrq(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int& nFrq);
	GVDISPLAY_API DWORD GvGetPwmFrqDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int& nFrq);
	GVDISPLAY_API DWORD GvSetPwmFrq(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id, int nFrq);
	GVDISPLAY_API DWORD GvSetPwmFrqDefault(int nGpuIndex, GVDISP_PWM_DOMAIN_ID id);

	GVDISPLAY_API DWORD GvGetFanCurve(int nGpuIndex, GVDISP_FANCURVE& curve);
	GVDISPLAY_API DWORD GvSetFanCurve(int nGpuIndex, GVDISP_FANCURVE  curve);

	// SLI Light API
	GVDISPLAY_API DWORD GvIsSLILight(int nGpuIndex, BOOL& bNvSLILight);
	GVDISPLAY_API DWORD GvSetSLILight(int nGpuIndex, int nValue);

	// Logo Light API
	GVDISPLAY_API DWORD GvIsLogoLight(int nGpuIndex, BOOL& bNvLogoLight);
	GVDISPLAY_API DWORD GvSetLogoLight(int nGpuIndex, int nValue);

	// Nv I2C API
	GVDISPLAY_API DWORD GvWriteI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr);
	GVDISPLAY_API DWORD GvReadI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr, unsigned char* szData);

	// Lock Clock Nv
	GVDISPLAY_API DWORD GvSetLockClock(int nGpuIndex, GVDISP_LOCK_DOMAIN_ID id, int nClock);
	GVDISPLAY_API DWORD GvGetLockClock(int nGpuIndex, GVDISP_LOCK_DOMAIN_ID id, int& nClock);

	// Lock Voltage Nv
	GVDISPLAY_API DWORD GvSetLockVoltage(int nGpuIndex, long nVoltage); // uv
	GVDISPLAY_API DWORD GvGetLockVoltage(int nGpuIndex, long& nVoltage);

	GVDISPLAY_API DWORD GvIsNvSLI(BOOL& bNvSLI);
}

#endif