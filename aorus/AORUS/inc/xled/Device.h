#pragma once
#include "XLedCmd.h"
#include "../../common/definition.h"

#define LED_MONITOR LED_STYLE

//
// CDevice
//
class CDevice
{
public:
	 CDevice(void);
	~CDevice(void);

	int GetDeviceId();

	//
	// device connection
	//
	virtual bool IsThisDevice(CString sDeviceDesc); // Device desc, such as: USB\VID_1044&PID_7A15&REV_0200&MI_01
	virtual bool OnConnect(HWND hWnd = NULL);  // Connect deivce
	virtual void Unconnect();
	virtual bool IsConnected();

	//
	// for led setting 
	// 
	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);

	// If this device supports 
	// LED_STYLE_MONITORING led style:
	virtual bool IsSupportLedMonitoring();
	virtual void GetLedMonitorItems(CArray<LED_MONITOR>& monitors);

	virtual bool IsSupportLed();	 // true: this device support led function. default: true.
	virtual bool IsSupportLedSync(); // true: this deivce support sync led effect with other kind of devices. default: true.

	virtual void SetLedSetting(int nDevIndex, // Device index. ex: for VGA, GPU0/GPU1...
		int nProfile,		// profile index: 0/1/2...
		LED_SETTING led,	// LED cfg 
		bool bSave = false	// false: DON'T save, just show effect on led.
		);



protected:
	int m_nDevice;
	bool m_bConnected;
};

//
// Video graphics cardx
//
class CVGA : public CDevice
{
public:
	 CVGA(void);
	~CVGA(void);

	// The functions below: see CDevice

	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();
	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);

	virtual bool IsSupportLedMonitoring();
	virtual void GetLedMonitorItems(CArray<LED_MONITOR>& monitors);
	virtual bool IsSupportLed();
	virtual bool IsSupportLedSync(); 
	virtual void SetLedSetting(int nDevIndex, int nProfile,	LED_SETTING led, bool bSave = false);

	CVGACtrl* Ctrl() { return &m_Ctrl; }; // to control VGA

protected:
	static CVGACtrl m_Ctrl;
};

//
// SLI
//
class CSLI : public CVGA
{
public:
	 CSLI(void);
	~CSLI(void);

	// The functions below: see CDevice

	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();
	virtual bool IsSupportLedMonitoring();
	virtual bool IsSupportLed();
	virtual bool IsSupportLedSync(); 
	virtual void SetLedSetting(int nDevIndex, int nProfile,	LED_SETTING led, bool bSave = false);
};

//
// Mother board, which support led function
//
class CMB : public CDevice
{
public:
	 CMB(void);
	~CMB(void);

	// The functions below: see CDevice

	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();
	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);

	virtual bool IsSupportLedMonitoring();
	virtual void GetLedMonitorItems(CArray<LED_MONITOR>& monitors);
	virtual bool IsSupportLed();
	virtual bool IsSupportLedSync(); 
	virtual void SetLedSetting(int nDevIndex, int nProfile,	LED_SETTING led, bool bSave = false);

	CMBCtrl* Ctrl() { return &m_Ctrl; }; // to control MB

protected:
	CMBCtrl m_Ctrl;
};


//
// CUsbDevice
//
class CUsbDevice : public CDevice
{
public:
	 CUsbDevice(void);
	~CUsbDevice(void);

	// The functions below: see CDevice

	virtual bool MaybeThisDevice(CString sDeviceDesc); 
	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();

	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);
	virtual void SetLedSetting(int nDevIndex, int nProfile, LED_SETTING led, bool bSave = false);

protected:
	CXLedCmd m_xLedCtrl;
	GVORDER_DEVICE m_device;
};


//
// IXEB
class CIXEB : public CUsbDevice
{
public:
	  CIXEB(void);
	 ~CIXEB(void);
	#ifdef _DEBUG
	//virtual bool OnConnect(HWND hWnd = NULL) { m_bConnected = true; return  m_bConnected; }
	#endif
};

// ATC700
class CATC700 : public CUsbDevice
{
public:
	 CATC700(void);
	~CATC700(void);
	#ifdef _DEBUG
	//virtual bool OnConnect(HWND hWnd = NULL) { m_bConnected = true; return  m_bConnected; }
	#endif
};

// AC300
class CAC300 : public CUsbDevice
{
public:
	 CAC300(void);
	~CAC300(void);
	#ifdef _DEBUG
	//virtual bool OnConnect(HWND hWnd = NULL) { m_bConnected = true; return  m_bConnected; }
	#endif
};

// AH300
class CAH300 : public CUsbDevice
{
public:
	 CAH300(void);
	~CAH300(void);
	#ifdef _DEBUG
	//virtual bool OnConnect(HWND hWnd = NULL) { m_bConnected = true; return  m_bConnected; }
	#endif
};

//
// CAM300
//
class CAM300 : public CDevice
{
public:
	 CAM300(void);
	~CAM300(void);

	// The functions below: see CDevice

	virtual bool MaybeThisDevice(CString sDeviceDesc); 
	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();

	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);
	virtual void SetLedSetting(int nDevIndex, int nProfile,	LED_SETTING led, bool bSave = false);


protected:
	GVORDER_DEVICE m_device;
};


//
// CAK700
//
class CAK700 : public CDevice
{
public:
	 CAK700(void);
	~CAK700(void);

	// The functions below: see CDevice


	virtual bool MaybeThisDevice(CString sDeviceDesc); 
	virtual bool OnConnect(HWND hWnd = NULL);
	virtual void Unconnect();
	virtual bool IsConnected();

	virtual void GetLedStylesSupported(CArray<LED_STYLE>& styles, bool bSyncLed);
	virtual void SetLedSetting(int nDevIndex, int nProfile,	LED_SETTING led, bool bSave = false);

	void OnHIDInput(RAWINPUT* raw);
	void SaveToClipboard(char *str); //複製到剪貼簿

protected:
	GVORDER_DEVICE m_device;
};


// AH300
class CH5 : public CUsbDevice
{
public:
	CH5(void);
	~CH5(void);
#ifdef _DEBUG
	//virtual bool OnConnect(HWND hWnd = NULL) { m_bConnected = true; return  m_bConnected; }
#endif
};
