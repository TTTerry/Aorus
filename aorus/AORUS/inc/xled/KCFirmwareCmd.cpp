
#include "StdAfx.h"
#include "KCFirmwareCmd.h"
#include "setupapi.h"

extern "C"
{
#include "../../lib/hidsdi.h"
}

//#pragma comment(lib, "../../lib/hid.lib")

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "Setupapi.lib")


HANDLE GetDeviceHandle(GUID* pGuid, DWORD instance)
{
	HDEVINFO info;

	// Get handle to relevant device information set
	info = SetupDiGetClassDevs(pGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

	if(info == INVALID_HANDLE_VALUE)
		return NULL;

	// Get interface data for the requested instance
	SP_INTERFACE_DEVICE_DATA ifdata;
	ifdata.cbSize = sizeof(ifdata);

	if (!SetupDiEnumDeviceInterfaces(info, NULL, pGuid, instance, &ifdata)) {
		SetupDiDestroyDeviceInfoList(info);
		return NULL;
	}

	// Get size of symbolic link name
	DWORD ReqLen;

	SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &ReqLen, NULL);

	PSP_INTERFACE_DEVICE_DETAIL_DATA ifDetail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)(new char[ReqLen]);

	if( ifDetail == NULL) {
		SetupDiDestroyDeviceInfoList(info);
		return NULL;
	}

	// Get symbolic link name
	ifDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

	if(!SetupDiGetDeviceInterfaceDetail(info, &ifdata, ifDetail, ReqLen, NULL, NULL)) {
		SetupDiDestroyDeviceInfoList(info);
		delete ifDetail;
		return NULL;
	}

	// Open file
	HANDLE pDevice = CreateFile( ifDetail->DevicePath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	/*HANDLE pDevice = CreateFile( ifDetail->DevicePath,
	GENERIC_READ | GENERIC_WRITE,
	FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);*/

	if ( pDevice == INVALID_HANDLE_VALUE)
		pDevice = NULL;

	delete ifDetail;
	SetupDiDestroyDeviceInfoList(info);

	return pDevice;
}

//---------------------------------------------------------------------------
bool GetAttCapab(WORD wVID, WORD wPID, HANDLE hidDevice, USHORT& InputReportLen, USHORT& OutputReportLen)
{
	HIDD_ATTRIBUTES HidAttributes;
	PHIDP_PREPARSED_DATA hidPreparsedData;
	HIDP_CAPS Capab;


	HidD_GetAttributes(hidDevice, &HidAttributes);

	if((HidAttributes.VendorID == wVID && HidAttributes.ProductID == wPID) != 0x00)
		;
	else
		return false;

	HidD_GetPreparsedData(hidDevice, &hidPreparsedData);
	NTSTATUS Status = HidP_GetCaps( hidPreparsedData, &Capab);
	if(Status == HIDP_STATUS_SUCCESS) {
		InputReportLen  = Capab.InputReportByteLength;
		OutputReportLen = Capab.OutputReportByteLength;
		if (Capab.UsagePage == 0xff01)
			return true;
		else
			return false;
	} else
		return false;
}

extern "C" {
	BOOL PASCAL HidVFD_GetDevice(WORD wVID, WORD wPID, HANDLE& hidDevice, USHORT* InputReportLen, USHORT* OutputReportLen)
		//extern "C" BOOL __declspec(dllexport) __stdcall HidVFD_GetDevice(HANDLE& hidDevice, USHORT* InputReportLen, USHORT* OutputReportLen)
	{
		GUID HidGuid;
		DWORD Instance = 0;

		HidD_GetHidGuid(&HidGuid);

		while (Instance < 100) {
			hidDevice = GetDeviceHandle(&HidGuid, Instance);
			if (hidDevice != NULL) {
				if(GetAttCapab(wVID, wPID, hidDevice, *InputReportLen, *OutputReportLen))
					return true;
				CloseHandle(hidDevice);
			}

			Instance++;
		}

		return false;
	}
}


CKCFirmwareCmd::CKCFirmwareCmd()
{
	m_hDevice = NULL;
}

CKCFirmwareCmd::~CKCFirmwareCmd()
{
}

bool CKCFirmwareCmd::ConnectXK700(WORD wVID, WORD wPID)
{		
	BYTE szData[9] = {0x00, 0xD4, 0x40, 0x00, 0x05, 0x80, 0x00, 0x00, 0xcd};
	BYTE szReceive[65] = "";
	USHORT K8000InputReportLen, K8000OutputReportLen;
	K8000InputReportLen = 0;
	K8000OutputReportLen = 0;
	return HidVFD_GetDevice(wVID, wPID, m_hDevice, &K8000InputReportLen, &K8000OutputReportLen) > 0 ? true : false;
}

void CKCFirmwareCmd::SyncPCColor(BYTE R, BYTE G, BYTE B)
{
	BYTE szData[9] = {0x00, 0x01, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = R;
	szData[4] = G;
	szData[5] = B;
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
}

void CKCFirmwareCmd::GetRGBColor(BYTE colorIdx, BYTE *pR, BYTE *pG, BYTE *pB)
{
	BYTE szData[9] = {0x00, 0x01, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = colorIdx;
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(m_hDevice, szData, 9);
	//if (szData[2] != 0xca)
	//	;	// error
	
	*pR = szData[3];
	*pG = szData[4];
	*pB = szData[5];
}

void CKCFirmwareCmd::GetLedSetting(BYTE* pbType, BYTE* pbSpeed, BYTE* pbMinBrightness, BYTE* pbBrightness, BYTE* pbColorIndex, BYTE* pbCycleCount)
{
	BYTE szData[9] = {0x00, 0x01, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(m_hDevice, szData, 9);
	//if (szData[2] != 0xcb)
	//	;	// error
	*pbType = szData[3];
	*pbSpeed = szData[5];
	*pbBrightness = szData[4];
	*pbMinBrightness = szData[8];
	*pbColorIndex = szData[7];
	*pbCycleCount = szData[6];
}

void CKCFirmwareCmd::GetFWVersion(BYTE *pHVer, BYTE *pLVer)
{
	BYTE szData[9] = {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(m_hDevice, szData, 9);
	//if (szData[1] != 0x80)
	//	;	// error
	
	*pHVer = szData[2];
	*pLVer = szData[3];
}

void CKCFirmwareCmd::SetColor(BYTE bColorIndex, BYTE R, BYTE G, BYTE B)
{
	BYTE szData[9] = {0x00, 0x01, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = R;
	szData[4] = G;
	szData[5] = B;
	szData[6] = bColorIndex;
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
}

void CKCFirmwareCmd::SaveSetting()
{
	BYTE szData[9] = {0x00, 0x01, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
}

void CKCFirmwareCmd::SetLedSetting(BYTE bType, BYTE bSpeed, BYTE bMinBrightness, BYTE bBrightness, BYTE bColorIndex, BYTE bCycleCount)
{
	BYTE szData[9] = {0x00, 0x01, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = bType;
	szData[4] = bBrightness;
	szData[5] = bSpeed;
	szData[6] = bCycleCount;
	szData[7] = bColorIndex;
	szData[8] = bMinBrightness;
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
}

DWORD CKCFirmwareCmd::SendCommandByte(int nIndex, int nBrd, int nHID, BYTE* szCmd, BYTE* szReceive, int& nCmdLen)
{
	CmdLock();
	BYTE szData[9] = {0x00, 0x01, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	//BYTE szData[9] = {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	memcpy(szData + 2, szCmd + 1, 8);
	BOOL b = HidD_SetFeature(m_hDevice, szData, 9);
	Sleep(100);
	if (szReceive != NULL)
	{
		b = HidD_GetFeature(m_hDevice, szData, 9);
		memcpy(szReceive, szData + 1, 8);
	}
	CmdUnLock();
	return b;
}