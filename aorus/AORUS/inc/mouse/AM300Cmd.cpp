#include "StdAfx.h"
#include "AM300Cmd.h"
#include "setupapi.h"
#include "CmdFormat.h"

extern "C"
{
#include "../../lib/hidsdi.h"
}

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "Setupapi.lib")

HANDLE CAM300Cmd::hAM300 = NULL;

BYTE CAM300Cmd::bStatus[10] = {0};
BYTE CAM300Cmd::iLength = 0;

CAM300Cmd::CAM300Cmd()
{
}

CAM300Cmd::~CAM300Cmd()
{
}

HANDLE Get_DeviceHandle_AM300(GUID* pGuid, DWORD instance)
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
bool GetAttCapab_AM300(HANDLE hidDevice, USHORT& InputReportLen, USHORT& OutputReportLen)
{
	HIDD_ATTRIBUTES HidAttributes;
	PHIDP_PREPARSED_DATA hidPreparsedData;
	HIDP_CAPS Capab;


	HidD_GetAttributes(hidDevice, &HidAttributes);

	if((HidAttributes.VendorID == 0x1044 && HidAttributes.ProductID == 0x7A28) != 0x00)
		CAM300Cmd::bStatus[CAM300Cmd::iLength++] = 1;
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
	BOOL PASCAL HidVFD_GetDevice_AM300(HANDLE& hidDevice, USHORT* InputReportLen, USHORT* OutputReportLen)
		//extern "C" BOOL __declspec(dllexport) __stdcall HidVFD_GetDevice(HANDLE& hidDevice, USHORT* InputReportLen, USHORT* OutputReportLen)
	{
		GUID HidGuid;
		DWORD Instance = 0;

		HidD_GetHidGuid(&HidGuid);

		while (Instance < 100) {
			hidDevice = Get_DeviceHandle_AM300(&HidGuid, Instance);
			if (hidDevice != NULL) {
				if(GetAttCapab_AM300(hidDevice, *InputReportLen, *OutputReportLen))
					return true;
				CloseHandle(hidDevice);
			}

			Instance++;
		}

		return false;
	}
}


bool CAM300Cmd::ConnectAM300()
{		
	BYTE szData[9] = {0x00, 0xD4, 0x40, 0x00, 0x05, 0x80, 0x00, 0x00, 0xcd};
	BYTE szReceive[65] = "";
	USHORT K8000InputReportLen, K8000OutputReportLen;
	K8000InputReportLen = 0;
	K8000OutputReportLen = 0;
	return HidVFD_GetDevice_AM300(hAM300, &K8000InputReportLen, &K8000OutputReportLen) > 0 ? true : false;
	//BOOL b = HidD_SetFeature(hAM300, szData, 9);
}


void CAM300Cmd::EraseFlase4K(int Addr)
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = (byte)((Addr & 0xff0000) >> 16);
	szData[4] = (byte)((Addr & 0x00ff00) >> 8);
	szData[5] = (byte)(Addr & 0x0000ff);
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	CmdUnLock();
}

void CAM300Cmd::StopFlase()
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xd5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xd5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	CmdUnLock();
}

void CAM300Cmd::MyWriteByte(BYTE* pBytes, int nLen)
{
	CmdLock();
	DWORD dwWritten;
	BYTE szReceive[65] = "";
	for (int i = 1; i < 65; i++)
		szReceive[i] = pBytes[i - 1];

	BOOL b = WriteFile(hAM300, szReceive, 65, &dwWritten, NULL);
	CmdUnLock();
}

void CAM300Cmd::MyReadByte(int Addr, int nLen, BYTE* byMemory)
{
	CmdLock();
	int i, j, iLoop, TempAddr, iAdd = 0;
	DWORD dwRead;
	BYTE szBuf[65] = "";
	// send addr first
	TempAddr = Addr;
	//BYTE szData[9] = {0x00, 0x02, 0xd4, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xd4, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	iLoop = nLen >> 6;	// div 64
	for (i = 0; i < iLoop; i++)
	{			
		szData[3] = (byte)((TempAddr & 0xff0000) >> 16);
		szData[4] = (byte)((TempAddr & 0x00ff00) >> 8);
		szData[5] = (byte)(TempAddr & 0x0000ff);
		TempAddr += 64;
		BOOL b = HidD_SetFeature(hAM300, szData, 9);

		b = ReadFile(hAM300, szBuf, 65, &dwRead, NULL);
		//Sleep(10);
		for (j = 1; j < 65; j++)
		{
			byMemory[iAdd++] = szBuf[j];
		}
	}
	CmdUnLock();
}

void CAM300Cmd::Write4KByte(BYTE* pBytes, int dwAddr)
{
	EraseFlase4K(dwAddr);
	Sleep(200);
	for (int i = 0; i < 64 * 64; i+=64)
	{
		MyWriteByte(&pBytes[i], 64);
		Sleep(20);
	}
	StopFlase();

}

void CAM300Cmd::SyncPCColor(BYTE R, BYTE G, BYTE B)
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[3] = R;
	szData[4] = G;
	szData[5] = B;
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	CmdUnLock();
}

void CAM300Cmd::SwitchProfile(BYTE Profile)
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[2] = Profile;
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	CmdUnLock();
}

void CAM300Cmd::ChgLedType(BYTE Profile, BYTE bType)
{
	CmdLock();
//	BYTE szData[9] = {0x00, 0x01, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xd1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
 	szData[2] = Profile;
 	szData[3] = bType;
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	Sleep(100);
	CmdUnLock();
}

void CAM300Cmd::ChgLedSetting(BYTE type, BYTE colorIdx, BYTE R, BYTE G, BYTE B, BYTE bright, BYTE speed)
{
	CmdLock();
	BYTE szData[9] = {0x00, 0xc9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[2] = type;
	szData[3] = colorIdx;
	szData[4] = R;
	szData[5] = G;
	szData[6] = B;
	szData[7] = bright;
	szData[8] = speed;
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	Sleep(100);
	CmdUnLock();
}

void CAM300Cmd::GetLedSetting(BYTE Profile, BYTE* pbType, BYTE* pbSpeed, BYTE* pbBrightness, BYTE* pbDir)
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	szData[2] = Profile;
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(hAM300, szData, 9);
	//if (szData[1] != 0xcb)
	//	;	// error
	*pbType = szData[2];
	*pbSpeed = szData[3];
	*pbBrightness = szData[4];
	*pbDir = szData[7];
	CmdUnLock();
}

BYTE CAM300Cmd::GetProfileIdx()
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(hAM300, szData, 9);
	//if (szData[1] != 0xb1)
	//	;	// error
	CmdUnLock();
	return szData[2];
}


void CAM300Cmd::SetLEDStatus(bool isOn)
{
	CmdLock();
	//BYTE szData[9] = {0x00, 0x02, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE szData[9] = {0x00, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	if(isOn)
		szData[2] = 0;
	else
		szData[2] = 1;

	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	
	Sleep(100);
	CmdUnLock();
}


BYTE CAM300Cmd::WireDefault(BYTE nProfile)
{
	BYTE szData[9] = {0x00, 0xd2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	szData[2] = nProfile;
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(hAM300, szData, 9);
	//if (szData[1] != 0xd2)
	//	;	// error
	return szData[2];

	// test clear flash
	/*BYTE szData[9] = {0x00, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(hAM300, szData, 9);

	
	Sleep(3000);
	return 1;*/
}

void CAM300Cmd::GetFWVersion()
{
	BYTE szData[9] = {0x00, 0xd6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BOOL b = HidD_SetFeature(hAM300, szData, 9);	
	Sleep(100);
	// getfeature
	b = HidD_GetFeature(hAM300, szData, 9);
	//if (szData[1] != 0xd6)
	//	;	// error	
}

void CAM300Cmd::ReadMCU64Byte(int Addr, BYTE* pMemory)
{
	CmdLock();
	int j, iAdd = 0;
	DWORD dwRead;
	BYTE szBuf[65] = "";

	BYTE szData[9] = {0x00, 0xda, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	szData[3] = (byte)((Addr & 0xff0000) >> 16);
	szData[4] = (byte)((Addr & 0x00ff00) >> 8);
	szData[5] = (byte)(Addr & 0x0000ff);

	BOOL b = HidD_SetFeature(hAM300, szData, 9);

	b = ReadFile(hAM300, szBuf, 65, &dwRead, NULL);
	//Sleep(10);
	for (j = 1; j < 65; j++)
	{
		pMemory[j - 1] = szBuf[j];
	}

	CmdUnLock();
}

void CAM300Cmd::SendCmdAndReadBack(BYTE* pCmd)
{
	CmdLock();
	BOOL b = HidD_SetFeature(hAM300, pCmd, 9);
	Sleep(10);
	// getfeature
	b = HidD_GetFeature(hAM300, pCmd, 9);
	
	CmdUnLock();
}

void CAM300Cmd::SendCmd(BYTE* pCmd)
{
	CmdLock();
	BOOL b = HidD_SetFeature(hAM300, pCmd, 9);
	Sleep(10);
	
	CmdUnLock();
}

//Change Led type
void CAM300Cmd::ChangeLedType(GVORDER_PROFILE Profile, bool bMultiColor)
{
	CmdLock();

	BYTE szData[9] = {0x00, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	CCmdFormat::toLedData(Profile, szData, bMultiColor);
	BOOL b = HidD_SetFeature(hAM300, szData, 9);
	Sleep(100);
	CmdUnLock();
}

void CAM300Cmd::WriteMCU64Byte(int Addr, BYTE* pMemory)
{
	CmdLock();
	int i, iAdd = 0;
	DWORD dwWrite;
	BYTE szBuf[65] = "";
	for (i = 1; i < 65; i++)
	{
		szBuf[i] = pMemory[i-1];
	}

	BYTE szData[9] = {0x00, 0xdb, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	szData[3] = (byte)((Addr & 0xff0000) >> 16);
	szData[4] = (byte)((Addr & 0x00ff00) >> 8);
	szData[5] = (byte)(Addr & 0x0000ff);

	BOOL b = HidD_SetFeature(hAM300, szData, 9);

	b = WriteFile(hAM300, szBuf, 65, &dwWrite, NULL);

	CmdUnLock();

}