#include "StdAfx.h"
#include "AudioVolume.h"

IMMDeviceEnumerator *CAudioVolume::pDeviceEnumerator = NULL;
IMMDevice *CAudioVolume::pDevice = NULL;
IAudioMeterInformation *CAudioVolume::pMeterInfo = NULL;


CAudioVolume::CAudioVolume(void)
{
}

CAudioVolume::~CAudioVolume(void)
{
}

int CAudioVolume::Init()
{
	CoInitialize(NULL);
	HRESULT hr;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
	if (FAILED(hr))
		return 0;
	hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	if (FAILED(hr))
		return 0;
	hr = pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	if (FAILED(hr))
		return 0;
	return 1;
}

float CAudioVolume::GetVolume()
{
	HRESULT hr = S_OK;
	float volume = 0;
	DWORD dwState = 0;
	if(NULL != pMeterInfo) hr = pMeterInfo->GetPeakValue(&volume);
	if (volume < 0.01 || FAILED(hr))
	{
		if(NULL != pDevice) pDevice->Release();
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
		if (FAILED(hr))
			return 0;
		if(NULL != pMeterInfo) pMeterInfo->Release();
		hr = pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);
		if (FAILED(hr))
			return 0;
		hr = pMeterInfo->GetPeakValue(&volume);
		if (volume < 0.01)
			return 0;
		if (FAILED(hr))
			return 0;
	}

	return float(volume * 100.0);
}
