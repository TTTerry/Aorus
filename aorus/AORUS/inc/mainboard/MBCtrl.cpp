#include "stdafx.h"
#include "MBCtrl.h"
//CMBCtrl *g_Mbctrl;
CMBCtrl::CMBCtrl()
{
	m_bConnected = false;
	//g_Mbctrl=this;
	m_hWnd = NULL;
    Ptr_Struct=Get_LED_Struct();
	GetModuleName();
	m_hDelaySetLedEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hDelaySetLedThread=CreateThread((LPSECURITY_ATTRIBUTES)NULL,0,
		(LPTHREAD_START_ROUTINE)DelaySetLED,
		this,
		0,
		NULL);
}
#ifdef UNICODE
#define LocateString	LocateStringW
#else
#define LocateString	LocateStringA
#endif
CMBCtrl::~CMBCtrl()
{
	CloseHandle(m_hDelaySetLedEvent);
	CloseHandle(m_hDelaySetLedThread);
}

BEGIN_MESSAGE_MAP(CMBCtrl, CMBCtrl)
	//ON_WM_TIMER()
END_MESSAGE_MAP()
int CMBCtrl::GetSuportFlag()
{
	int nFlags = -1;
	if(Ptr_Struct != NULL)
		nFlags = Ptr_Struct->Support_Flag;
	else if((Ptr_Struct = Get_LED_Struct()) != NULL)
		nFlags = Ptr_Struct->Support_Flag;

	m_bConnected = (nFlags > 0) ? true : false;
	return nFlags;
}
void CMBCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==0)
	{
		KillTimer(NULL,0);
		SetLedSetting(m_LastSetting);
	}

}
UINT CMBCtrl::DelaySetLED(LPVOID lpParam)
{	
	//WaitForSingleObject()
	CMBCtrl* pMain = (CMBCtrl*) lpParam;
	while (1)
	{
		WaitForSingleObject(pMain->m_hDelaySetLedEvent,INFINITE);
		for (;;)
		{
			Led_Struce* TempPtr_Struct;
			TempPtr_Struct=Get_LED_Struct();
			if (TempPtr_Struct->Fun_Type==Fun_Type_Ready)
			{
				pMain->SetLedSetting(pMain->m_LastSetting);
				break;
			}
			Sleep(1000);
		}
	}
	return 1;
}
void CMBCtrl::SetLedSetting(LED_SETTING  setting)
{
	Led_Struce* TempPtr_Struct;
	TempPtr_Struct=Get_LED_Struct();
	if(TempPtr_Struct!=NULL)
	{
		if(TempPtr_Struct->Fun_Type!=Fun_Type_Ready)
		{
			m_LastSetting=setting;
			SetEvent(m_hDelaySetLedEvent);
			//SetTimer(NULL,0,500,NULL);
			//MessageBox("Please Wait write to MCU!",NULL,MB_OK);
		}
		else
		{
			if (Ptr_Struct==NULL)
			{
				Ptr_Struct=Get_LED_Struct();
			}
			if (Ptr_Struct!=NULL)
			{
			    Ptr_Struct->Fun_Type=Fun_Type_Write;
			    Ptr_Struct->Write_mcu_fun=Write_mcu_All;
			//	Ptr_Struct->Write_mcu_fun=Write_mcu_Bri;

			    Ptr_Struct->Brightness=setting.nRangeMax;
			    Ptr_Struct->Speed=setting.nSpeed;
				//Ptr_Struct->Current_Easy_Color=setting.clrLed;
				int r=(setting.clrLed>>16)&0xff;
				int g=(setting.clrLed>>8)&0xff;
				int b=setting.clrLed&0xff;
				Ptr_Struct->Brightness=setting.nRangeMax/30;
				Ptr_Struct->Speed=setting.nSpeed/4;
 
			    Ptr_Struct->Current_Easy_Color=r+(g<<8)+(b<<16);
				if (!setting.bOn)
				{
					Ptr_Struct->Current_Pattern=PatternType_off;
				}
				else
				{
					switch(setting.dwStyle)
					{
					case LED_STYLE_CONSISTENT: {
							Ptr_Struct->Current_Pattern=PatternType_Static;
							Ptr_Struct->Current_Mode=Mode_Easy;
						}break;
					case LED_STYLE_BREATHING: {
							Ptr_Struct->Current_Pattern=PatternType_Pulse;
							Ptr_Struct->Current_Mode=Mode_Easy;
						}break;
					case LED_STYLE_FLASHING: {
							Ptr_Struct->Current_Pattern=PatternType_Flash;
							Ptr_Struct->Current_Mode=Mode_Easy;
						}
						break;
					case LED_STYLE_MONITORING: {
							int nMode = 0; 
							if (setting.dwVariation == LED_MONITOR_CPU_USAGE) nMode = 0;
							else if (setting.dwVariation == LED_MONITOR_CPU_TEMPERATURE) nMode = 1;
							else if (setting.dwVariation == LED_MONITOR_SYS_TEMPERATURE) nMode = 2;
							else if (setting.dwVariation == LED_MONITOR_CPU_FANSPEED) nMode = 3;
							Ptr_Struct->Current_Mode=Mode_Easy;
							Ptr_Struct->Current_Pattern=PatternType_Inte;
							Ptr_Struct->Other_Mode = nMode + 1;
						}break;
					case LED_STYLE_AUDIOFLASHING: {
							Ptr_Struct->Current_Mode=Mode_Easy;
							Ptr_Struct->Current_Pattern=PatternType_Music;
						}break;
					case LED_STYLE_WAVE: {
							Ptr_Struct->Current_Mode=Mode_Easy;
							if (GetSuportFlag()&(1<<6))
							{
								Ptr_Struct->Current_Pattern=PatternType_Wave;
							}
							else
							{
								Ptr_Struct->Current_Pattern=PatternType_Random;
							}
							
						}break;
					case LED_STYLE_CIRCLING: {
							Ptr_Struct->Current_Mode=Mode_Easy;
							Ptr_Struct->Current_Pattern=PatternType_Random;
						}break;
					default:Ptr_Struct->Current_Pattern=PatternType_Static;break;
					}
					
				}
				if(TempPtr_Struct->Current_Mode==Ptr_Struct->Current_Mode&&
					TempPtr_Struct->Current_Pattern==Ptr_Struct->Current_Pattern&&
					TempPtr_Struct->Other_Mode==Ptr_Struct->Other_Mode)
				{
					if (TempPtr_Struct->Brightness!=Ptr_Struct->Brightness)
					{
						Ptr_Struct->Write_mcu_fun=Write_mcu_Bri;
					}
					else if (TempPtr_Struct->Speed!=Ptr_Struct->Speed)
					{
						Ptr_Struct->Write_mcu_fun=Write_mcu_Speed;
					}
					else if (TempPtr_Struct->Current_Easy_Color!=Ptr_Struct->Current_Easy_Color)
					{
						Ptr_Struct->Write_mcu_fun=Write_mcu_Color;
					}
				}
			    Set_LED_Struct(Ptr_Struct);
		}
	}
   }
}

void CMBCtrl::SetSpeed(LED_SETTING  setting)
{
	if (Ptr_Struct==NULL)
	{
		Ptr_Struct=Get_LED_Struct();
	}
	if (Ptr_Struct!=NULL)
	{
	    Ptr_Struct->Fun_Type=Fun_Type_Write;
	    Ptr_Struct->Write_mcu_fun=Write_mcu_Speed;
	    Ptr_Struct->Speed=setting.nSpeed/4;
	    Set_LED_Struct(Ptr_Struct);
	}
}
void CMBCtrl::SetBrightness(LED_SETTING  setting)
{
	if (Ptr_Struct==NULL)
	{
		Ptr_Struct=Get_LED_Struct();
	}
	if (Ptr_Struct!=NULL)
	{
	    Ptr_Struct->Fun_Type=Fun_Type_Write;
	    Ptr_Struct->Write_mcu_fun=Write_mcu_Bri;
	    Ptr_Struct->Brightness=setting.nRangeMax/30;
	    Set_LED_Struct(Ptr_Struct);
	}
}
void CMBCtrl::GetModuleName()
{
	// the seqence just for x86, but don't worry we know SMBIOS/DMI only exist on x86 platform
	DWORD needBufferSize = 0;
	const BYTE byteSignature[] = { 'B', 'M', 'S', 'R' };
	const DWORD Signature = *((DWORD*)byteSignature);
	LPBYTE pBuff = NULL;
	needBufferSize = GetSystemFirmwareTable(Signature, 0, NULL, 0);

	//_tprintf(TEXT("We need prepare %d bytes for recevie SMBIOS/DMI Table\n"), needBufferSize);
	pBuff = (LPBYTE) malloc(needBufferSize);
	if (pBuff)
	{
		GetSystemFirmwareTable(Signature, 0, pBuff, needBufferSize);

		const PRawSMBIOSData pDMIData = (PRawSMBIOSData)pBuff;
		/*_tprintf(TEXT("SMBIOS version:%d.%d\n"), pDMIData->SMBIOSMajorVersion, pDMIData->SMBIOSMinorVersion);
		_tprintf(TEXT("DMI Revision:%x\n"), pDMIData->DmiRevision);
		_tprintf(TEXT("Total length: %d\n"), pDMIData->Length);
		_tprintf(TEXT("DMI at address %x\n"), (DWORD)((PBYTE)&pDMIData->SMBIOSTableData));*/

		DumpSMBIOSStruct(&(pDMIData->SMBIOSTableData), pDMIData->Length);

	}
}
void CMBCtrl::DumpSMBIOSStruct(void *Addr, UINT Len)
{
	LPBYTE p = (LPBYTE)(Addr);
	const DWORD lastAddress = ((DWORD)p) + Len;
	PSMBIOSHEADER pHeader;

	for (;;) {
		pHeader = (PSMBIOSHEADER)p;
		DispatchStructType(pHeader);
		PBYTE nt = p + pHeader->Length; // point to struct end
		while (0 != (*nt | *(nt + 1))) nt++; // skip string area
		nt += 2;
		if ((DWORD)nt >= lastAddress)
			break;
		p = nt;
	}
}
bool CMBCtrl::DispatchStructType(PSMBIOSHEADER hdr)
{
	if (2 == hdr->Type)
	{
		//_tprintf(TEXT("%s\n"), getHeaderString(cstrHEADER));
		//tpfunc[i].Proc((void*)hdr);
		ProcBoardInfo((void*)hdr);
		return true;
	}
	return false;
}
bool CMBCtrl::ProcBoardInfo(void* p)
{
	PBoardInfo pBoard = (PBoardInfo)p;
	const char *str = toPointString(p);
	m_modelname=LocateString(str, pBoard->Product);
	/*_tprintf(TEXT("%s\n"), getHeaderString(2));
	_tprintf(TEXT("Length: 0x%X\n"), pBoard->Header.Length);
	_tprintf(TEXT("Manufacturer: %s\n"), LocateString(str, pBoard->Manufacturer));
	_tprintf(TEXT("Product Name: %s\n"), LocateString(str, pBoard->Product));
	_tprintf(TEXT("Version: %s\n"), LocateString(str, pBoard->Version));
	_tprintf(TEXT("Serial Number: %s\n"), LocateString(str, pBoard->SN));
	_tprintf(TEXT("Asset Tag Number: %s\n"), LocateString(str, pBoard->AssetTag));
	if (pBoard->Header.Length > 0x08)
	{
		_tprintf(TEXT("Location in Chassis: %s\n"), LocateString(str, pBoard->LocationInChassis));
	}*/

	return true;
}
const char* CMBCtrl::toPointString(void* p)
{
	return (char*)p + ((PSMBIOSHEADER)p)->Length;
}
const char* CMBCtrl::LocateStringA(const char* str, UINT i)
{
	static const char strNull[] = "Null String";

	if (0 == i || 0 == *str) return strNull;

	while (--i)
	{
		str += strlen((char*)str) + 1;
	}
	return str;
}

const wchar_t* CMBCtrl::LocateStringW(const char* str, UINT i)
{
	static wchar_t buff[2048];
	const char *pStr = LocateStringA(str, i);
	SecureZeroMemory(buff, sizeof(buff));
	MultiByteToWideChar(CP_OEMCP, 0, pStr, strlen(pStr), buff, sizeof(buff));
	return buff;
}
void CMBCtrl::GetModuleName(CString &modename)
{
    modename=m_modelname;
}