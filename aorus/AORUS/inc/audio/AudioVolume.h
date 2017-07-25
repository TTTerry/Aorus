#pragma once
#include "Mmdeviceapi.h "
#include "endpointvolume.h"

class CAudioVolume
{
public:
	CAudioVolume(void);
	~CAudioVolume(void);

	static int Init();
	static float GetVolume();

	static IMMDeviceEnumerator *pDeviceEnumerator;
	static IMMDevice *pDevice;
	static IAudioMeterInformation *pMeterInfo;
};
