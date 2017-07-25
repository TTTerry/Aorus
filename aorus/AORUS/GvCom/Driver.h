#ifndef _GV_COM_DLL_DRIVER_H_
#define _GV_COM_DLL_DRIVER_H_

#include "Base.h"

namespace Gv {

class GVDLL Driver : public Base
{
public:
	 Driver();
	~Driver();

public:
	bool Install();		// Install Driver
	void Free();		// Release Driver
	bool IsInstalled();	// Check driver installed or not.

	bool SetPortLong(WORD wPort, DWORD  dwValue);
	bool GetPortLong(WORD wPort, DWORD& dwValue);
	bool SetPortWord(WORD wPort, WORD  wValue);
	bool GetPortWord(WORD wPort, WORD& wValue);
	bool SetPortByte(WORD wPort, BYTE  acValue);
	bool GetPortByte(WORD wPort, BYTE& acValue);

	bool MapMemPhysToLinear  (unsigned long nPhysAddr, unsigned long nLength, BYTE** ppBuffer);
	bool UnMapMemPhysToLinear(unsigned long nPhysAddr, unsigned long nLen);

private:
	bool Install(bool bIsWow64, bool bDemandLoaded);
	bool Start();
	bool Remove();

private:
	HANDLE m_hGbDriver;
};

}

#endif