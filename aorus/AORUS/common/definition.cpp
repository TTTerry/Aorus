#include "stdafx.h"
#include "definition.h"

_LED_SETTING::_LED_SETTING()
{
	sProfileName = _T("Profile1");
	bOn = true;
	bMutilColor = false;
	nType = SLI_TYPE_GA;
	nRangeMax = 100;
	nRangeMin = 0;
	nSelectCard = 0;
	clrLed = RGB(255, 20, 0);
	nSpeed = 10;
	dwStyle = 0;
	dwVariation = 0;
}

VGA_PARAM_MONISETTING::_VGA_PARAM_MONISETTING()
{
	bGpuClk		= true;
	bMemClk		= true;
	bGpuVol		= true;
	bMemVol		= false;
	bPower		= true;
	bFanSpd		= true;
	bFanRpm		= true;
	bTemperature= true;
	bPower		= true;
	bGPUsage	= true;
	bCPUsage	= true;
	bCPUClock	= false;
	bMemUsage	= true;
	bPageUsage	= true;
	bLogRecord  = false;
	nTimeInterval = 3000;
	sLogFile	= Gv::OS::GetCurDirectory() + _T("GvTemp\\");
};

VGA_PARAM_MONISETTING& VGA_PARAM_MONISETTING::operator = (const VGA_PARAM_MONISETTING& setting)
{
	bGpuClk		= setting.bGpuClk;
	bMemClk		= setting.bMemClk;
	bGpuVol		= setting.bGpuVol;
	bMemVol		= setting.bMemVol;
	bFanSpd		= setting.bFanSpd;
	bFanRpm     = setting.bFanRpm;
	bTemperature= setting.bTemperature;
	bPower		= setting.bPower;
	sLogFile	= setting.sLogFile;
	bGPUsage	= setting.bGPUsage;
	bCPUsage	= setting.bCPUsage;
	bCPUClock	= setting.bCPUClock;
	bMemUsage	= setting.bMemUsage;
	bPageUsage	= setting.bPageUsage;
	bLogRecord	= setting.bLogRecord;
	nTimeInterval = setting.nTimeInterval;
	return *this;
}

VGA_PARAM_BASESETTING::_VGA_PARAM_BASESETTING()
{
	bSyncLed = FALSE;
	bAutoRun = TRUE;
	bMinimize = TRUE; 
	bCloseMin = FALSE;
	bCheckUpdate = FALSE;
	bSyncMutil = FALSE;
	sLastCheckUpdate = _T("----/--/--");
}

VGA_PARAM_BASESETTING& VGA_PARAM_BASESETTING::operator = (const VGA_PARAM_BASESETTING& setting)
{
	bSyncLed = setting.bSyncLed;
	bSyncMutil = setting.bSyncMutil;
	bAutoRun = setting.bAutoRun;
	bMinimize = setting.bMinimize; 
	bCloseMin = setting.bCloseMin;
	bCheckUpdate = setting.bCheckUpdate;
	sLastCheckUpdate = setting.sLastCheckUpdate;

	return *this;
}

_FAN_SETTING::_FAN_SETTING()
{
	nCurveStep = 0;
	nFanMode = VGA_FANMODE_AUTO;
	nFanPercent = 30;
	bFanStop = true;
	for(int i=0; i<VGA_FANCURVE_STEPS; i++)
	{
		curve[i].nFanSpeed = 0;
		curve[i].nTemperature = 0;
	}
}

_FAN_SETTING& _FAN_SETTING::operator = (const _FAN_SETTING& setting)
{
	nCurveStep = setting.nCurveStep;
	nFanMode = setting.nFanMode;
	nFanPercent = setting.nFanPercent;
	bFanStop = setting.bFanStop;
	for(int i=0; i<VGA_FANCURVE_STEPS; i++)
	{
		curve[i].nFanSpeed = setting.curve[i].nFanSpeed;
		curve[i].nTemperature = setting.curve[i].nTemperature;
	}
	return *this;
}

VGA_CARD_INFO::_VGA_CARD_INFO()
{
	nCardType   = VGA_CARD_UNKNOWN;
	sDevDesc	= _T("");
	sModelName	= _T("");
	sBiosVer	= _T("");
	sDriverVer	= _T("");
	sDriverDate	= _T("");
	sVid		= _T("");
	sDid		= _T("");
	sSsid		= _T("");
	sSvid		= _T("");
	sMemSize	= _T("");
}

VGA_CARD_INFO& VGA_CARD_INFO::operator = (const VGA_CARD_INFO& info)
{
	sDevDesc	= info.sDevDesc;
	nCardType   = info.nCardType;
	sModelName	= info.sModelName;
	sBiosVer	= info.sBiosVer;
	sDriverVer	= info.sDriverVer;
	sDriverDate	= info.sDriverDate;
	sVid		= info.sVid;
	sDid		= info.sDid;
	sSsid		= info.sSsid;
	sSvid		= info.sSvid;
	sMemSize	= info.sMemSize;

	return* this;
}

VGA_PERFORMANCE::_VGA_PERFORMANCE()
{
	nGpuClk			= 0;
	nMemClk			= 0;
	nGpuVol			= 0;
	nMaxVol			= 0;
	nMemVol			= 0;
	nPower			= 0;  
	nGPUsage		= 0;  
	nFanSpd			= 0;
	nFanMode		= 0;
	nTemperature	= 0;
	bTempPowerLink	= 0;
	nFanRPM			= 0;
	bVolLock        = 1;
	dwGpuClkCurve	= false;
	dwMemClkCurve	= false;
}

VGA_SPECIALPERFS::_VGA_SPECIALPERFS()
{
	nGpuBaseClk  = 0;
	nGpuBoostClk = 0;
	nMemBaseClk  = 0;
	nGpuBaseVol  = 0;
	nMaxBaseVol  = 0;
}
