#ifndef _GV_COM_DLL_DEVICE_H_
#define _GV_COM_DLL_DEVICE_H_

#include "Base.h"

namespace Gv {

class GVDLL Device : public Base
{
public: 

	/////////////////////////////////////////////////
	// Graphics Information
	/////////////////////////////////////////////////
	#define GRAPHICS_NUM  10
	enum GraphicsV { VGA_Unknown = 0, VGA_AMD = 1, VGA_NVIDIA = 2 }; // Graphics Vendor
	
	// Graphics adapter info
	struct GVDLL ADAPTER_V {
		int  nGraphics;				// How many valid adapters exists
		struct {
			WORD wVID;				// Vendor ID
			WORD wDID;				// Device ID
			WORD wSSID;				// Sub System ID
			WORD wSVID;				// Sub Vendor ID
			GraphicsV Vendor;		// VGA type (NVIDIA or AMD)
			struct {
				BYTE acBus;			// PCI bus number
				BYTE acDevice;		// PCI device number
				BYTE acFunction;	// PCI function number
			} Location;				// VGA adapter location(bus, device, function)
		} Cards[GRAPHICS_NUM];
	};
	// Graphics BIOS version
	struct GVDLL BIOS_V_VER {
		TCHAR cFixed;				// Fixed character, such as 'F'
		TCHAR cFirst;				// The first number
		TCHAR cSecond;				// The second number
		TCHAR cVerifySeparator;		// Verifying code separator, such as '-'
		TCHAR cVerifyLength;		// Verifying code length
		int   nVerLength;			// BIOS version code length, it should be 1 or 2, except verifying code
	};
	// Graphics BIOS info
	struct GVDLL BIOS_V {			// Graphics BIOS
		TCHAR szModelName[128];		// BIOS model name in string
		TCHAR szSignOnMessage[128];	// Sign on message add by HW RD
		TCHAR szPID[10];			// Program ID
		TCHAR szIds[24];			// Four Ids: 1458_xxxx_xxxx_xxxx
		TCHAR szBiosVer[32];		// BIOS version in string
		BIOS_V_VER BiosVer;			// BIOS version structure
	};

public:
	 Device();
	~Device();

public:
	bool GetGraphicsBIOS(BIOS_V& biosV);
	bool GetGraphicsAdapters(ADAPTER_V& adapterV);
	
private:
	Driver m_Driver;
};

}


#endif