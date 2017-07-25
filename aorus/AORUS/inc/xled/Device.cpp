 #include "StdAfx.h"
#include "Device.h"
#include "../../AorusDlg.h"
#include "../mouse/AM300Cmd.h"
#include "../mouse/AM300Ctrl.h"
#include "../kb/XK700Cmd.h"
#include "../kb/KbLedCtrl.h"
#include "../kb/KbCfg.h"

///////////////////////////////////////////////////////////////////////////////////
//
// CDevice
// 
///////////////////////////////////////////////////////////////////////////////////

#pragma region CDevice

CDevice::CDevice(void)
{
	m_nDevice = 0; m_bConnected = false;
}
CDevice::~CDevice(void)
{
}

int CDevice::GetDeviceId() { return m_nDevice; }

//
// for led setting. Do nothing
// 

bool CDevice::IsThisDevice(CString sDeviceDesc) { return false; }
bool CDevice::OnConnect(HWND hWnd) { return false; }
void CDevice::Unconnect() {}
bool CDevice::IsConnected() { return false; }

void CDevice::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed) 
{
	if (!bSyncLed) 
		return; 

	styles.RemoveAll();

	// Check what devices here. 
	// if only VGA & SLI exist, more styles are allow to use.

	//CArray<LED_STYLE> stylesV; // use VGA's styles as std. 
	//CDevice* pVGA = Aorus()->GetDevice(DEVICE_VGA);
	//pVGA->GetLedStylesSupported(stylesV, false);
	//for (int k = 0; k < (int)stylesV.GetSize(); k++)
	//{
	//	LED_STYLE style = stylesV.GetAt(k);
	//	int nStyle = style.nId;

	//	bool bAllDevicesSupported = true;
	//	for (int i = 0; i < DEVICE_COUNT; i++)
	//	{
	//		CDevice* pDevice = Aorus()->GetDevice(s_DevIds[i]);
	//		if (!pDevice->IsConnected())
	//			continue;

	//		if (pDevice->m_nDevice == DEVICE_VGA) 
	//			continue;

	//		bool bExisted = false;
	//		CArray<LED_STYLE> stylesD;
	//		pDevice->GetLedStylesSupported(stylesD, false);
	//		for (int m = 0; m < (int)stylesD.GetSize(); m++)
	//		{
	//			if (stylesD.GetAt(m).nId == nStyle) { bExisted = true; break; }
	//		}
	//		if (bExisted) continue;
	//		bAllDevicesSupported = false; break;  // Cur device NOT support this style.
	//	}
	//	
	//	if (bAllDevicesSupported) 
	//		styles.Add(style);
	//}

	//for (int i = 0; i < (int)styles.GetSize(); i++)
	//{
	//	LED_STYLE style = styles.GetAt(i);
	//	m_Styles.Add(style);
	//}


	bool bOnlyVGA = true;
	for (int i = 0; i < DEVICE_COUNT; i++)
	{
		CDevice* pDevice = Aorus()->GetDevice(s_DevIds[i]);
		if (!pDevice->IsConnected())
			continue;
		int nDevice = pDevice->GetDeviceId();
		if (nDevice != DEVICE_VGA && nDevice != DEVICE_SLI)
		{
			bOnlyVGA = false; break;
		}
	}
	bool bMBExisted = false;
	if (Aorus()->GetDevice(DEVICE_MB)->IsConnected() || Aorus()->GetDevice(DEVICE_MB)->OnConnect())
	{
		bMBExisted = true;
	}
	if (bMBExisted)
	{
		styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
		return;
	}
	if (!bOnlyVGA || Aorus()->GetVGA()->Ctrl()->IsIXEBCard())
	{
		styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
		styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
		styles.Add(LED_STYLE(LED_STYLE_FLASHING,	CLangX::Get(LANG_VGALED_VGASTYLE_FLASH)));
		styles.Add(LED_STYLE(LED_STYLE_DUALFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_DUALFLASH)));		
		styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));		
		return;
	}

	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
	styles.Add(LED_STYLE(LED_STYLE_FLASHING,	CLangX::Get(LANG_VGALED_VGASTYLE_FLASH)));
	styles.Add(LED_STYLE(LED_STYLE_DUALFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_DUALFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_MONITORING,	CLangX::Get(LANG_VGALED_VGASTYLE_VARIA)));
	styles.Add(LED_STYLE(LED_STYLE_AUDIOFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_AUDIOFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));
}
bool CDevice::IsSupportLedMonitoring() { return false; }
void CDevice::GetLedMonitorItems(CArray<LED_MONITOR>& monitors) { }
bool CDevice::IsSupportLedSync() { return true; }
bool CDevice::IsSupportLed() { return true; }
void CDevice::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave) {}
#pragma endregion

///////////////////////////////////////////////////////////////////////////////////
//
// CUsbDevice
// 
///////////////////////////////////////////////////////////////////////////////////
CUsbDevice::CUsbDevice(void) 
{
}
CUsbDevice::~CUsbDevice(void)
{
}

bool CUsbDevice::MaybeThisDevice(CString sDeviceDesc)
{
	// Device desc, such as: USB\VID_1044&PID_7A15&REV_0200&MI_01

	CString sPID = _T("");
	sPID.Format(_T("%04X"), m_device.dwPID);
	return (sDeviceDesc.Find(sPID) >= 0) ? true : false;
}

bool CUsbDevice::OnConnect(HWND hWnd)
{
	m_bConnected = m_xLedCtrl.Init((WORD)m_device.dwVID, (WORD)m_device.dwPID);
	return m_bConnected;
}

void CUsbDevice::Unconnect()   { m_bConnected = false; }
bool CUsbDevice::IsConnected() { return m_bConnected; }
void CUsbDevice::SetLedSetting(int nDevIndex/*will be ignored...*/, int nProfile, LED_SETTING led, bool bSave)
{
	DEVICE_CONFIG cfg;
	cfg.nType = -1;
	cfg.bOn = led.bOn;
	cfg.nBright = led.nRangeMax;
	cfg.nSpeed = led.nSpeed;

	for (int i = 0; i < 7; i++) 
	{
		cfg.clrArray[i] = s_clr[i];
	}
	
	switch(led.dwStyle)
	{
	case LED_STYLE_CONSISTENT:	
		cfg.nType = TYPE_BRIGHT; 
		cfg.nClrCount = 1;
		cfg.clrArray[0] = led.clrLed;
		break;
	case LED_STYLE_BREATHING:	
		cfg.nType = TYPE_BREATH; 
		cfg.nClrCount = led.bMutilColor ? 7 : 1;
		if (!led.bMutilColor) cfg.clrArray[0] = led.clrLed;
		// Peter Lee 2017/6/13 marked for all bright same value
		//cfg.nBright = (cfg.nBright + 5) / 10; // BUG MAYBE... 
		break;
	case LED_STYLE_FLASHING:	
		cfg.nType = TYPE_FLASHING; 
		cfg.nClrCount = led.bMutilColor ? 7 : 1;
		if (!led.bMutilColor) cfg.clrArray[0] = led.clrLed;
		if (0 == cfg.nSpeed) cfg.nSpeed = 1; 
		break;
	case LED_STYLE_DUALFLASHING:
		cfg.nType = TYPE_DUALFLASHING; 
		cfg.nClrCount = led.bMutilColor ? 7 : 1;
		if (!led.bMutilColor) cfg.clrArray[0] = led.clrLed;
		if (0 == cfg.nSpeed) cfg.nSpeed = 1; 
		break;
	case LED_STYLE_CIRCLING:	
		cfg.nType = TYPE_CYCLING; 
		cfg.nClrCount = 7;
		// Peter Lee 2017/6/13 marked for all bright same value
		//cfg.nBright = (cfg.nBright + 5) / 10; // BUG MAYBE... 
		break;
	default: break;  // others: unsupported
	}

	if (cfg.nType < 0) return; // unsupported

	for (int i = cfg.nClrCount; i < CLR_MAX_COUNT; i++)
	{
		cfg.clrArray[i] = RGB(0, 0, 0);
	}
	
	if (!cfg.bOn) { cfg.nType = TYPE_BRIGHT; cfg.nBright = 0;}
	m_xLedCtrl.SetLightSetting(DEVICE_CONFIG(cfg), CONFIG_ALL, 0);
	if (bSave)
	{
		m_xLedCtrl.SaveLightSetting(0);
	}
}

void CUsbDevice::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed)
{
	if (bSyncLed)
	{
		return CDevice::GetLedStylesSupported(styles, true);
	}

	styles.RemoveAll();
	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
	styles.Add(LED_STYLE(LED_STYLE_FLASHING,	CLangX::Get(LANG_VGALED_VGASTYLE_FLASH)));
	styles.Add(LED_STYLE(LED_STYLE_DUALFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_DUALFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));
}

///////////////////////////////////////////////////////////////////////////////////
//
// CIXEB / ATC700 / AC300 / AH300
// 
///////////////////////////////////////////////////////////////////////////////////
CIXEB::CIXEB(void) 
{ 
	m_nDevice = DEVICE_VGA; GVORDER_DEVICE dev = { 0x1044, 0x7A27, 2 }; m_device = dev; 
}
CIXEB::~CIXEB(void) 
{
}
CATC700::CATC700(void) 
{ 
	m_nDevice = DEVICE_ATC700; GVORDER_DEVICE dev = { 0x1044, 0x7A29, 2 }; m_device = dev; 
}
CATC700::~CATC700(void) 
{
}
CAC300::CAC300(void) 
{ 
	m_nDevice = DEVICE_AC300;  GVORDER_DEVICE dev = { 0x1044, 0x7A30, 2 }; m_device = dev; 
}
CAC300::~CAC300(void) 
{
}
CAH300::CAH300(void) 
{ 
	m_nDevice = DEVICE_AH300; GVORDER_DEVICE dev = { 0x1044, 0x7A31, 2 }; m_device = dev;
}
CAH300::~CAH300(void) 
{
}

CH5::CH5(void)
{
	m_nDevice = DEVICE_H5; GVORDER_DEVICE dev = { 0x1044, 0x7A34, 2 }; m_device = dev;
}
CH5::~CH5(void)
{
}
///////////////////////////////////////////////////////////////////////////////////
//
// AM300
// 
///////////////////////////////////////////////////////////////////////////////////
CAM300::CAM300(void) 
{
	m_nDevice = DEVICE_AM300; GVORDER_DEVICE dev = { 0x1044, 0x7A28, 2 }; m_device = dev;
}
CAM300::~CAM300(void)
{
}

bool CAM300::MaybeThisDevice(CString sDeviceDesc)
{
	// Device desc, such as: USB\VID_1044&PID_7A15&REV_0200&MI_01

	CString sPID = _T("");
	sPID.Format(_T("%04X"), m_device.dwPID);
	return (sDeviceDesc.Find(sPID) >= 0) ? true : false;
}

bool CAM300::OnConnect(HWND hWnd)
{
 #ifdef _DEBUG
 	m_bConnected = true; return m_bConnected;
 #endif
	m_bConnected = CAM300Cmd::ConnectAM300();
	if (m_bConnected)	// Peter Lee 2017/7/3
	{
		GVORDER_MEMORY_PARAM param;
		param.type = GVORDER_DEVICE_MOUSE;
		param.nMarcoCount = 50;
		param.nProfileCount = 5;	
		CAM300Ctrl::LoadMemory(param);
	}
	return m_bConnected;
}

void CAM300::Unconnect()   { m_bConnected = false; }
bool CAM300::IsConnected() { return m_bConnected; }
void CAM300::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave)
{
	GVORDER_PROFILE cfg;
	cfg.nProfile = nProfile;
	cfg.bBackLight = led.bOn; // light on
	cfg.bEnable = false;
	cfg.nBrightness = led.nRangeMax;
	cfg.nSpeed = led.nSpeed;
	cfg.clr = led.clrLed;

	switch(led.dwStyle)
	{
	case LED_STYLE_CONSISTENT:	
		cfg.nBeathType = GVORDER_LED_CONSISTENT; 
		break;
	case LED_STYLE_BREATHING:	
		cfg.nBeathType = led.bMutilColor ? (GVORDER_LED_MODE)6 : GVORDER_LED_BREATHING; 
		break;
 	case LED_STYLE_FLASHING:	
		cfg.nBeathType = led.bMutilColor ? (GVORDER_LED_MODE)7 : GVORDER_LED_SINGLETWINKLE; 
 		break;
 	case LED_STYLE_DUALFLASHING:
		cfg.nBeathType = led.bMutilColor ? (GVORDER_LED_MODE)8 : GVORDER_LED_TWICETWINKLE; 
 		break;
	case LED_STYLE_CIRCLING:	
		cfg.nBeathType = GVORDER_LED_CYCLING; 
		break;
	default: return;  // others: unsupported
	}

	if (!led.bOn)
	{
		cfg.nBeathType = GVORDER_LED_OFF; // cfg.nBright = 0;
	}

	CmdLock();
	CAM300Cmd::ChangeLedType(cfg, led.bMutilColor);
	if (bSave)
	{
		CAM300Ctrl::SetProfile(cfg);
		CAM300Ctrl::SelProfile(cfg.nProfile);
	}
	CmdUnLock();
}

void CAM300::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed)
{
	if (bSyncLed)
	{
		return CDevice::GetLedStylesSupported(styles, true);
	}

	styles.RemoveAll();
	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
 	styles.Add(LED_STYLE(LED_STYLE_FLASHING,	CLangX::Get(LANG_VGALED_VGASTYLE_FLASH)));
 	styles.Add(LED_STYLE(LED_STYLE_DUALFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_DUALFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));
}

///////////////////////////////////////////////////////////////////////////////////
//
// AK700
// 
///////////////////////////////////////////////////////////////////////////////////
CAK700::CAK700(void) 
{
	m_nDevice = DEVICE_AK700; GVORDER_DEVICE dev = { 0x1044, 0x7A2C, 2 }; m_device = dev;
}
CAK700::~CAK700(void)
{
}

bool CAK700::MaybeThisDevice(CString sDeviceDesc)
{
	// Device desc, such as: USB\VID_1044&PID_7A15&REV_0200&MI_01

	CString sPID = _T("");
	sPID.Format(_T("%04X"), m_device.dwPID);
	return (sDeviceDesc.Find(sPID) >= 0) ? true : false;
}

bool CAK700::OnConnect(HWND hWnd)
{
// #ifdef _DEBUG
// 	m_bConnected = true; return m_bConnected;
// #endif
	m_bConnected = CXK700Cmd::ConnectXK700();
	return m_bConnected;
}

void CAK700::Unconnect()   { m_bConnected = false; }
bool CAK700::IsConnected() { return m_bConnected; }
void CAK700::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave)
{
	return;
	int nOff = led.bOn ? 128 : 0;
	if (led.bMutilColor && led.dwStyle == LED_STYLE_BREATHING)
	{
		led.dwStyle = LED_STYLE_CIRCLING;
	}

	CXK700Cmd::SetLEDStatus(false); //LED OFF
	CmdLock();
	
	switch(led.dwStyle)
	{
	case LED_STYLE_CONSISTENT: {
			CXK700Cmd::ChgLedType(nProfile, LED_CONSISTENT);
			CXK700Cmd::ChgLedSetting(
				LED_CONSIST | nOff, 
				0, 
				GetRValue(led.clrLed), 
				GetGValue(led.clrLed), 
				GetBValue(led.clrLed),
				(led.nRangeMax + 5) / 10, // for AK700, brightness range [0, 10]
				0);
			CKbLedCtrl::ResetClrList(nProfile);
		} break;
	case LED_STYLE_BREATHING: {
			CXK700Cmd::ChgLedType(nProfile, LED_PULSING);
			CXK700Cmd::ChgLedSetting(
				LED_PULSING | nOff, 
				1, 
				GetRValue(led.clrLed), 
				GetGValue(led.clrLed), 
				GetBValue(led.clrLed),
				(led.nRangeMax + 5) / 10, // for AK700, brightness range [0, 10]
				led.nSpeed);
			CKbLedCtrl::ResetClrList(nProfile);
		} break;	
	case LED_STYLE_CIRCLING: {
			CXK700Cmd::ChgLedType(nProfile, LED_CYCLING);
			CXK700Cmd::ChgLedSetting(
				LED_CYCLING | nOff, 
				0, 0, 0, 0,
				(led.nRangeMax + 5) / 10, // for AK700, brightness range [0, 10]
				10);
			CKbLedCtrl::ResetClrList(nProfile);
			
		} break;
	}

	CmdUnLock();
	//Sleep(500);
	CXK700Cmd::SetLEDStatus(true);  //LED ON
}

void CAK700::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed)
{
	if (bSyncLed)
	{
		return CDevice::GetLedStylesSupported(styles, true);
	}

	styles.RemoveAll();
	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
	styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));
}

void CAK700::OnHIDInput(RAWINPUT* raw)
{

 if (raw->data.hid.bRawData[1] == 0xBF) 
	{
		int nIndex = raw->data.hid.bRawData[2];
		CString sStr = _T("");
		Aorus()->GetCfg()->GetTxtInputInfor(nIndex, sStr);

		//讀取文檔文本複製到剪貼簿
		int len = WideCharToMultiByte(CP_ACP, 0, sStr, -1, NULL, 0, NULL, NULL);  
		char *str = new char[len +1];  
		WideCharToMultiByte(CP_ACP, 0, sStr, -1, str, len, NULL, NULL );  
		SaveToClipboard(str);
		delete[] str;  
		
		if (!sStr.IsEmpty())
		{
			keybd_event(0x11, 0, 0, 0);//press Ctrl
			keybd_event(0x56, 0, 0, 0);//press V
			keybd_event(0x56, 0, 2, 0);//release V
			keybd_event(0x11, 0, 2, 0);//release  Ctrl
		}
	}
}

void CAK700::SaveToClipboard(char *str)
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		char *buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_MOVEABLE, strlen(str)+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, (LPCSTR)str);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}
}


///////////////////////////////////////////////////////////////////////////////////
//
// Mother board
// 
///////////////////////////////////////////////////////////////////////////////////
CMB::CMB(void) 
{
	m_nDevice = DEVICE_MB;
}
CMB::~CMB(void)
{
}

bool CMB::OnConnect(HWND hWnd)
{
	m_bConnected = (m_Ctrl.GetSuportFlag() > 0) ? true : false;
	return m_bConnected;
}

void CMB::Unconnect()   {  } // Do nothing
bool CMB::IsConnected() { return m_bConnected; }
void CMB::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed)
{
	if (bSyncLed)
	{
		return CDevice::GetLedStylesSupported(styles, true);
	}

	styles.RemoveAll();
	CString sName = _T("");
	m_Ctrl.GetModuleName(sName);
	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_MBSTYLE_CONS)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_MBSTYLE_BREATHING)));
	if (sName == _T("Z270-Gaming 3") || sName == _T("Z270-Gaming K3"))  // Old MB version, DON'T support other styles
		return;
	styles.Add(LED_STYLE(LED_STYLE_FLASHING,	 CLangX::Get(LANG_VGALED_MBSTYLE_FLASHING)));
	styles.Add(LED_STYLE(LED_STYLE_MONITORING,	 CLangX::Get(LANG_VGALED_MBSTYLE_VARIATION)));
	styles.Add(LED_STYLE(LED_STYLE_AUDIOFLASHING,CLangX::Get(LANG_VGALED_MBSTYLE_AUDIOFLASHING)));
	if ((m_Ctrl.GetSuportFlag() & (1 << 6)))  // support wave style
	{
		styles.Add(LED_STYLE(LED_STYLE_WAVE, CLangX::Get(LANG_VGALED_MBSTYLE_WAVE)));
	}

}
bool CMB::IsSupportLedMonitoring()
{
	return m_bConnected ? true : false; 
}
void CMB::GetLedMonitorItems(CArray<LED_MONITOR>& monitors)
{
	monitors.RemoveAll();
	monitors.Add(LED_STYLE(LED_MONITOR_CPU_USAGE,		CLangX::Get(LANG_VGALED_MBVARIA_CPUUTI)));
	monitors.Add(LED_STYLE(LED_MONITOR_CPU_TEMPERATURE,	CLangX::Get(LANG_VGALED_MVSTYLE_CPUTEMP)));
	monitors.Add(LED_STYLE(LED_MONITOR_SYS_TEMPERATURE,	CLangX::Get(LANG_VGALED_MVSTYLE_SYSTEMP)));
	monitors.Add(LED_STYLE(LED_MONITOR_CPU_FANSPEED,	CLangX::Get(LANG_VGALED_MVSTYLE_CPUFANSPD)));
}
bool CMB::IsSupportLed()
{
	return (m_Ctrl.GetSuportFlag() > 0) ? true : false;
}
bool CMB::IsSupportLedSync()
{
	if (m_Ctrl.GetSuportFlag() <= 0)
		return false;

	CString sMBName = _T("");
	m_Ctrl.GetModuleName(sMBName);
	// Z270-Gaming 3's FW is old version, not support led sync.
	return (sMBName == _T("Z270-Gaming 3") || sMBName == _T("Z270-Gaming K3")) ? false : true;
}
void CMB::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave)
{
	m_Ctrl.SetLedSetting(led);
}
///////////////////////////////////////////////////////////////////////////////////
//
// CVGA
// 
///////////////////////////////////////////////////////////////////////////////////
CVGACtrl CVGA::m_Ctrl;
CVGA::CVGA(void) 
{
	m_nDevice = DEVICE_VGA;
}
CVGA::~CVGA(void)
{
}
bool CVGA::OnConnect(HWND hWnd)
{
	ASSERT(NULL != hWnd);
	m_bConnected = m_Ctrl.Initialize(hWnd);
	return m_bConnected;
}
void CVGA::Unconnect()   {  } // Do nothing
bool CVGA::IsConnected() { return m_bConnected; }
void CVGA::GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed)
{
	if (bSyncLed)
	{
		return CDevice::GetLedStylesSupported(styles, true);
	}

	styles.RemoveAll();
	styles.Add(LED_STYLE(LED_STYLE_CONSISTENT,	CLangX::Get(LANG_VGALED_VGASTYLE_CONSI)));
	styles.Add(LED_STYLE(LED_STYLE_BREATHING,	CLangX::Get(LANG_VGALED_VGASTYLE_BREATH)));
	styles.Add(LED_STYLE(LED_STYLE_FLASHING,	CLangX::Get(LANG_VGALED_VGASTYLE_FLASH)));
	styles.Add(LED_STYLE(LED_STYLE_DUALFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_DUALFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_MONITORING,	CLangX::Get(LANG_VGALED_VGASTYLE_VARIA)));
	styles.Add(LED_STYLE(LED_STYLE_AUDIOFLASHING,CLangX::Get(LANG_VGALED_VGASTYLE_AUDIOFLASH)));
	styles.Add(LED_STYLE(LED_STYLE_CIRCLING,	CLangX::Get(LANG_VGALED_VGASTYLE_RANDOM)));
}
bool CVGA::IsSupportLedMonitoring()
{
	return m_Ctrl.IsLedCard() ? true : false;
}
void CVGA::GetLedMonitorItems(CArray<LED_MONITOR>& monitors)
{
	monitors.RemoveAll();
	monitors.Add(LED_STYLE(LED_MONITOR_GPU_TEMPERATURE,	CLangX::Get(LANG_VGALED_VGAVARIA_GPUTEMP)));
	monitors.Add(LED_STYLE(LED_MONITOR_GPU_USAGE,		CLangX::Get(LANG_VGALED_VGAVARIA_GPUUTI)));
	monitors.Add(LED_STYLE(LED_MONITOR_GPU_FANSPEED,	CLangX::Get(LANG_VGALED_VGAVARIA_GPUFANSPD)));
}
bool CVGA::IsSupportLed()
{
	return m_Ctrl.IsLedCard() ? true : false;
}
bool CVGA::IsSupportLedSync()
{
	return m_Ctrl.IsLedCard() ? true : false;
}
void CVGA::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave)
{
	m_Ctrl.SetLedSetting(nDevIndex, led, bSave);
}


///////////////////////////////////////////////////////////////////////////////////
//
// CSLI
// 
///////////////////////////////////////////////////////////////////////////////////
CSLI::CSLI(void) 
{
	m_nDevice = DEVICE_SLI;
}
CSLI::~CSLI(void)
{
}
bool CSLI::OnConnect(HWND hWnd)
{
	m_bConnected = (m_Ctrl.IsNvSli() && m_Ctrl.IsLedCard()) ? true : false;
	return m_bConnected;
}
void CSLI::Unconnect()   {  } // Do nothing
bool CSLI::IsConnected() { return m_bConnected; }
bool CSLI::IsSupportLedMonitoring()
{
	return false;
}
bool CSLI::IsSupportLed()
{
	return m_bConnected;
}
bool CSLI::IsSupportLedSync()
{
	return m_bConnected;
}
void CSLI::SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave)
{
	m_Ctrl.SetLedSetting(2, led, bSave);  // if has SLI, 0: GPU1 / 1: GPU2 / 2: SLI device.
}




