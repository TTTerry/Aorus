#include "StdAfx.h"
#include "AM300Cmd.h"
#include "AM300Ctrl.h"
#include "setupapi.h"
#include "CmdFormat.h"

extern "C"
{
#include "../../lib/hidsdi.h"
}

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "Setupapi.lib")
GVORDER_MEMORY_PARAM xParam;


CAM300Ctrl::CAM300Ctrl()
{
}

CAM300Ctrl::~CAM300Ctrl()
{
}


void CAM300Ctrl::LoadMemory(GVORDER_MEMORY_PARAM param)
{
	int nLength = CMD_LENGTH;
	DWORD dwReturn = GVAPI_OK;
	xParam = param;
	
	// 加载 Profile设定
	for (int i = 0; i < param.nProfileCount; i++)
	{
		DWORD dwAddr = m_AM300ProfileAddr[i];
		BYTE byMemory[MEM_MAX_SIZE * 2] = { 0 };
		nLength = MEM_MAX_SIZE;
		//ReadByte(byMemory, nLength, dwAddr, nBrd);
		CAM300Cmd::ReadMCU64Byte(dwAddr, byMemory);

		memcpy(&m_KeyProfile[i][0], byMemory, KEYMAP_PROFILE_SIZE);
	}

	// 加载Mouse Key Profile设定
	for (int i = 0; i < param.nProfileCount; i++)
	{
		DWORD dwAddr = s_AM300MsProfileAddr[i];
		BYTE byMemory[MEM_MAX_SIZE + 1] = { 0 };
		nLength = MEM_MAX_SIZE;
		//ReadByte(byMemory, nLength, dwAddr, nBrd);
		CAM300Cmd::ReadMCU64Byte(dwAddr, byMemory);

		memcpy(&m_KeyProfile[i][GVORDER_DEVICE_KEYBOARD == param.type ? KEYMAP_PROFILE_SIZE * 2 : KEYMAP_PROFILE_SIZE], byMemory, KEYMAP_PROFILE_SIZE);
	}

	// 樓婥操摩?靡備
	DWORD dwAddr = MACROS_NAME_ADDR;

	BYTE byMemory[MACROS_NAME] = { 0 };
	nLength = MACROS_NAME_LENGTH;
	CAM300Cmd::MyReadByte(dwAddr, nLength, byMemory);
	memcpy(&m_MarosPro[0][0], byMemory, MACROS_NAME);	
}

DWORD CAM300Ctrl::GetCurProfile(GVORDER_PROFILE& profile)
{
	BYTE szData[9] = {0x00, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	

	CAM300Cmd::SendCmdAndReadBack(szData);

	profile = CCmdFormat::toProfile(&szData[CMD_DATA_INDEX]);
	return 0;

}

DWORD CAM300Ctrl::SelProfile(int nProfile)
{
	BYTE szData[9] = {0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	

	szData[2] = nProfile;
	CAM300Cmd::SendCmd(szData);
	return 0;
}

DWORD CAM300Ctrl::GetProfile(GVORDER_PROFILE& profile)
{
	int nProfile = profile.nProfile;
	BYTE byData[DATA_LENGTH + MEM_MAX_SIZE * 4 + 1] = {0};
	memcpy(byData, m_KeyProfile[nProfile], MEM_MAX_SIZE);

	profile.bEnable = byData[PROFILE_STATUS];
	profile.clr = RGB(byData[PROFILE_COLORR], byData[PROFILE_COLORG], byData[PROFILE_COLORB]);
	profile.nSpeed = 5 - (byData[PROFILE_SPEED] - 5);
	profile.nBrightness = (int)(byData[PROFILE_BRIGHT] / 25.5 + 0.5);
	profile.nBeathType = (GVORDER_LED_MODE)byData[PROFILE_LEDMOD];
	profile.bBackLight = byData[PROFILE_BLIGHT] == 0xff;

	if(!profile.bBackLight) profile.nBrightness = byData[PROFILE_BLIGHT];
	if(profile.nSpeed < 0 || profile.nSpeed > 5) profile.nSpeed = 5;
	if(profile.nBrightness < 0 || profile.nBrightness > 10) profile.nBrightness = 10;
	if(0xff == profile.nBeathType) profile.bBackLight = false;
	if(0xff == profile.nBeathType) profile.nBeathType = GVORDER_LED_CONSISTENT;
	return 0;
}



DWORD CAM300Ctrl::SetProfile(GVORDER_PROFILE profile)
{
     int nProfile = profile.nProfile;
     BYTE byData[DATA_LENGTH + MEM_MAX_SIZE * 4 + 1] = { 0 };
     BYTE* byMem = &byData[DATA_LENGTH];
     memcpy(byMem, m_KeyProfile[nProfile], MEM_MAX_SIZE);

     byMem[PROFILE_STATUS] = profile.bEnable ? 0xff : 0;
     byMem[PROFILE_COLORR] = GetRValue(profile.clr);
     byMem[PROFILE_COLORG] = GetGValue(profile.clr);
     byMem[PROFILE_COLORB] = GetBValue(profile.clr);
     //byMem[PROFILE_SPEED] = (BYTE)(11 - profile.nSpeed) * 2;        // Peter Lee 2017/7/4 for M3
     if (profile.nBeathType == GVORDER_LED_SINGLETWINKLE || profile.nBeathType == GVORDER_LED_TWICETWINKLE || profile.nBeathType == 7 || profile.nBeathType == 8)
          byMem[PROFILE_SPEED]     = (BYTE)(11 - profile.nSpeed) * 20;     
     else
          byMem[PROFILE_SPEED]     = (BYTE)(11 - profile.nSpeed) * 2; 

     //byMem[PROFILE_BRIGHT] = profile.bBackLight ? profile.nBrightness * 25.5 : 0; // 若關閉背光將亮度設置成，
     byMem[PROFILE_BRIGHT] = profile.bBackLight ? profile.nBrightness : 0; // Peter Lee 2017/7/4 for M3
     byMem[PROFILE_LEDMOD] = profile.nBeathType;
     byMem[PROFILE_BLIGHT] = profile.bBackLight ? 0xff : 0xff - profile.nBrightness; // 并將背光欄位設置成亮度。

     int nCmdLength = MEM_MAX_SIZE + CMD_LENGTH;
     DWORD dwAddr = m_AM300ProfileAddr[nProfile];
     byData[0] = MEM_MAX_SIZE;
     byData[1] = ADDRH(dwAddr);    byData[2] = ADDRM(dwAddr);    byData[3] = ADDRL(dwAddr);

     memcpy(m_KeyProfile[nProfile], byMem, MEM_MAX_SIZE);

     CAM300Cmd::WriteMCU64Byte(dwAddr, byMem);

     return 0;


}

//------------------------------------DPI Control Terry 2017/07/03---------------------------------------
DWORD  CAM300Ctrl::GetDPI(GVORDER_DPI& dpi)
{
	BYTE szData[9] = {0x00, 0xc5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	CAM300Cmd::SendCmdAndReadBack(szData);
	dpi = CCmdFormat::toDPI(&szData[CMD_DATA_INDEX]);
	return 0;
}

DWORD CAM300Ctrl::GetCurDPI(GVORDER_DPI& dpi)
{
	BYTE szData[9] = {0x00, 0xB3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	CAM300Cmd::SendCmdAndReadBack(szData);
	dpi = CCmdFormat::toDPI(&szData[CMD_DATA_INDEX]);
	return 0;
}

DWORD  CAM300Ctrl::SetDPI(GVORDER_DPI dpi)
{
	int ndpiIndex = dpi.nIndex;
	int nX = 0x05 + ndpiIndex * 2;
	int nY = 0x06 + ndpiIndex * 2;
	m_KeyProfile[0][nX] = dpi.nX;
	m_KeyProfile[0][nY] = dpi.nY;


	BYTE szData[9] = {0x00, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	szData[2] = dpi.nIndex;
	szData[3] = dpi.nX;
	szData[4] = dpi.nY;
	//	CCmdFormat::toData(dpi, szData);

	CAM300Cmd::SendCmd(szData);
	return 0;
}

DWORD  CAM300Ctrl::GetReportRate(int& nReportRate)
{
	BYTE szData[9] = {0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	CAM300Cmd::SendCmdAndReadBack(szData);
	nReportRate = CCmdFormat::toReportRate(&szData[CMD_DATA_INDEX]);
	return 0;
}

DWORD  CAM300Ctrl::SetReportRate(int nReportRate)
{
	BYTE szData[9] = {0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	szData[2] = nReportRate;
	CAM300Cmd::SendCmd(szData);
	m_KeyProfile[0][PROFILE_RATE] = nReportRate;
	//CDeviceCmd::SetReportRate(nReportRate);
	return 0;
}

DWORD  CAM300Ctrl::SelDPI(int nDpiIndex)
{
	BYTE szData[9] = {0x00, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	
	szData[2] = nDpiIndex;
	CAM300Cmd::SendCmd(szData);
	return 0;
}
//---------------------------------------------------------------------------------------------


DWORD CAM300Ctrl::SetKeyMapping(GVORDER_KEYFUN fnkey)
{
	BYTE byData[DATA_LENGTH + MEM_MAX_SIZE * 4 + 1] = {0};
	//	BYTE* byMem = &byData[DATA_LENGTH];
	BYTE* byMem = &byData[0];
	if(fnkey.nIndex < 0x10)
		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE], MEM_MAX_SIZE);
	else
		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE + KEYMAP_PROFILE_SIZE], MEM_MAX_SIZE);

	BYTE byBtn[5] = {0};
	int nCmdLength = MEM_MAX_SIZE + CMD_LENGTH;
	DWORD dwAddr = m_AM300ProfileAddr[fnkey.nProfile] + KEYMAP_PROFILE_SIZE;
	if(fnkey.nIndex >= 0x10) dwAddr += KEYMAP_PROFILE_SIZE;

	CCmdFormat::toData(fnkey, byBtn);
	//  	byData[0] = MEM_MAX_SIZE;
	//  	byData[1] = ADDRH(dwAddr);	
	//  	byData[2] = ADDRM(dwAddr);	
	//  	byData[3] = ADDRL(dwAddr);

	BYTE byRevice[MEM_MAX_SIZE + 1] = { 0 };

	int nTypeAddr =  fnkey.nIndex;
	int nData1Addr = nTypeAddr + 0x10;
	int nData2Addr = nData1Addr + 0x10;
	int nData3Addr = nData2Addr + 0x10;
	byData[nTypeAddr] = byBtn[DATA_BTN_TYPE];
	byData[nData1Addr] = byBtn[DATA_BTN_OPT1];
	byData[nData2Addr] = byBtn[DATA_BTN_OPT2];
	byData[nData3Addr] = byBtn[DATA_BTN_OPT3];

	if(fnkey.nIndex < 0x10)
		memcpy(&m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE], byMem, MEM_MAX_SIZE);
	else
		memcpy(&m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE + KEYMAP_PROFILE_SIZE], byMem, MEM_MAX_SIZE);

	CAM300Cmd::WriteMCU64Byte(dwAddr, byData);

	return 0;
}

DWORD CAM300Ctrl::GetKeyMapping(GVORDER_KEYFUN& fnkey)
{
	int nProfile = fnkey.nProfile;
	BYTE szData[DATA_LENGTH + MEM_MAX_SIZE * 4 + 1] = {0};

	BYTE* byMem = &szData[DATA_LENGTH];
	if(fnkey.nIndex < 0x10)
		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE], MEM_MAX_SIZE);
	else

		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE + KEYMAP_PROFILE_SIZE], MEM_MAX_SIZE);

	BYTE byBtn[5] = {0};

	int nTypeAddr = fnkey.nIndex;
	int nData1Addr = nTypeAddr + 0x10;
	int nData2Addr = nData1Addr + 0x10;
	int nData3Addr = nData2Addr + 0x10;
	byBtn[DATA_BTN_INDEX] = fnkey.nIndex;
	byBtn[DATA_BTN_TYPE] = byMem[nTypeAddr];
	byBtn[DATA_BTN_OPT1] = byMem[nData1Addr];
	byBtn[DATA_BTN_OPT2] = byMem[nData2Addr];
	byBtn[DATA_BTN_OPT3] = byMem[nData3Addr];

	fnkey = CCmdFormat::toKeyFun(byBtn);
	fnkey.nProfile = nProfile;
	fnkey.nIndex = nTypeAddr;

	return 0;
}

DWORD  CAM300Ctrl::GetMacrosList(GVORDER_MACROS_ATTR lstmacros[], int nCount)
{
	getMacroList(lstmacros, nCount);
	return 0;
}

DWORD CAM300Ctrl::getMacroList(GVORDER_MACROS_ATTR lstmacros[], int& nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		lstmacros[i] = CCmdFormat::toMacrosattr(&m_MarosPro[i][0]);
	}
	return 0;
}

DWORD CAM300Ctrl::SetKeyMappingDefault(int nProfile, GVORDER_DEVICE_TYPE type)
{

	BYTE szData[CMD_LENGTH + MEM_MAX_SIZE] = {0};
	BYTE* byData = &szData[DATA_LENGTH];
	memset(byData, 0xff, MEM_MAX_SIZE);

	DWORD dwAddr = s_AM300MsProfileAddr[nProfile] ;
	if(GVORDER_DEVICE_KEYBOARD == type) dwAddr += KEYMAP_PROFILE_SIZE;

	//  	szData[DATA_MEM_BYTES] = MEM_MAX_SIZE;
	//  	szData[DATA_MEM_ADDRL] = ADDRL(dwAddr);
	//  	szData[DATA_MEM_ADDRM] = ADDRM(dwAddr);
	//  	szData[DATA_MEM_ADDRH] = ADDRH(dwAddr);
	int nCmdLen = CMD_LENGTH + MEM_MAX_SIZE;

	if(GVORDER_DEVICE_MOUSE == type)
		memcpy(&m_KeyProfile[nProfile][KEYMAP_PROFILE_SIZE], byData, MEM_MAX_SIZE);
	else
		memcpy(&m_KeyProfile[nProfile][KEYMAP_PROFILE_SIZE + KEYMAP_PROFILE_SIZE], byData, MEM_MAX_SIZE);

	// 	CAM300Cmd::SendCmd(byData);
	CAM300Cmd::WriteMCU64Byte(dwAddr, szData);

	return 0;
}

DWORD CAM300Ctrl::SetKeyMappingAddr(GVORDER_KEYFUN fnkey, DWORD dwAddr)
{
	BYTE byData[DATA_LENGTH + MEM_MAX_SIZE * 4 + 1] = {0};
	BYTE* byMem = &byData[DATA_LENGTH];
	if(fnkey.nIndex < 16)
		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][0], MEM_MAX_SIZE);
	else
		memcpy(byMem, &m_KeyProfile[fnkey.nProfile][KEYMAP_PROFILE_SIZE], MEM_MAX_SIZE);

	BYTE byBtn[5] = {0};
	DWORD dwWrite = dwAddr - dwAddr % 0x40;
	int nCmdLength = MEM_MAX_SIZE + CMD_LENGTH;
	CCmdFormat::toData(fnkey, byBtn);
	// 	 byData[0] = MEM_MAX_SIZE;
	// 	 byData[1] = ADDRH(dwWrite);	byData[2] = ADDRM(dwWrite);	byData[3] = ADDRL(dwWrite);
	BYTE byRevice[MEM_MAX_SIZE + 1] = { 0 };

	int nTypeAddr = dwAddr % 0x40 + DATA_LENGTH;
	int nData1Addr = nTypeAddr + 0x10;
	int nData2Addr = nData1Addr + 0x10;
	int nData3Addr = nData2Addr + 0x10;
	byData[nTypeAddr] = byBtn[DATA_BTN_TYPE];
	byData[nData1Addr] = byBtn[DATA_BTN_OPT1];
	byData[nData2Addr] = byBtn[DATA_BTN_OPT2];
	byData[nData3Addr] = byBtn[DATA_BTN_OPT3];

	CAM300Cmd::WriteMCU64Byte(dwAddr, byData);

	return 0;
}


//**************************************MACRO控制部分 add by terry 20170525******************************************/
DWORD CAM300Ctrl::SetMacrosKey(GVORDER_MACROS macros)
{
	BYTE byData[MACROS_KEYS_SIZE * 4] = {0};
	BYTE* byMem = &byData[DATA_LENGTH];
	int nLength = CMD_LENGTH;
	DWORD dwReturn = GVAPI_OK;


	int nLocation = 0;
	for (int i = 0; i < macros.nCount; i++)
	{
		BYTE byMaros[10];
		int nLen = 0;
		CCmdFormat::toData(macros.macros[i], byMaros, nLen);
		// 更新Marco Key内存?存
		memcpy(&m_MarosKey[macros.nIndex][nLocation], byMaros, nLen);
		nLocation += nLen;
	}

	memset(&m_MarosKey[macros.nIndex][nLocation], 0xff, MACROS_KEYS_SIZE - nLocation);

	DWORD dwAddr = MACROS_KEYS_ADDR + MACROS_KEYS_SIZE*macros.nIndex;
	dwAddr = dwAddr - (dwAddr % 0x1000);
	int iOff = macros.nIndex - (macros.nIndex % 4);
	CAM300Cmd::Write4KByte(&m_MarosKey[iOff][0], dwAddr);



	//保存名字/发送类型/时间模式
	USES_CONVERSION;
	memset(&m_MarosPro[macros.nIndex][0], 0xff, MACROS_NAME_SIZE);
	m_MarosPro[macros.nIndex][0] = macros.attr.nIcon;

	BYTE bMode = 0;
	if(GVORDER_MACROS_EXEC == macros.attr.RunType) //once
	{
		if(GVORDER_MACROS_AUTO == macros.attr.TimeMode)
			bMode = 0x80;
		else if(GVORDER_MACROS_FIXEDTIME == macros.attr.TimeMode)
			bMode = 0x81;
		else if(GVORDER_MACROS_NONE == macros.attr.TimeMode)
			bMode = 0x82;
	}
	else if(GVORDER_MACROS_LOOP == macros.attr.RunType)  // loop
	{
		if(GVORDER_MACROS_AUTO == macros.attr.TimeMode)
			bMode = 0x88;
		else if(GVORDER_MACROS_FIXEDTIME == macros.attr.TimeMode)
			bMode = 0x89;
		else if(GVORDER_MACROS_NONE == macros.attr.TimeMode)
			bMode = 0x8a;
	}
	else if(GVORDER_MACROS_FIRE == macros.attr.RunType) //fire key
	{
		if(GVORDER_MACROS_AUTO == macros.attr.TimeMode)
			bMode = 0x8c;
		else if(GVORDER_MACROS_FIXEDTIME == macros.attr.TimeMode)
			bMode = 0x8d;
		else if(GVORDER_MACROS_NONE == macros.attr.TimeMode)
			bMode = 0x8e;
	}

	memcpy(&m_MarosPro[macros.nIndex][1], W2A(macros.attr.szName), MACROS_NAME_SIZE-1);
	m_MarosPro[macros.nIndex][MACROS_NAME_SIZE - 1] = bMode;

	dwAddr = MACROS_NAME_ADDR;
	nLength = MACROS_NAME_SIZE + CMD_LENGTH;
	BYTE byName[MACROS_NAME_SIZE * MACRO_COUNT]= {0};
	CAM300Cmd::Write4KByte(&m_MarosPro[0][0], dwAddr);
	Sleep(50);

	for (int j = 0; j < xParam.nProfileCount; j++)
	{
		GVORDER_KEYFUN fn;
		bool bChange = false;
		for (int i = 0; i < 0x10; i++)
		{
			GVORDER_KEYFUN keyfun;
			keyfun.nIndex = i;
			keyfun.nProfile = j;
			CAM300Ctrl::GetKeyMapping(keyfun);
			if((GVORDER_FUN_MACROSONCE  == keyfun.fnType		// 巨集執行一次
				|| GVORDER_FUN_MACROSLOOP  == keyfun.fnType		// 巨集按下放開後循環執行，再按下放開後停止
				|| GVORDER_FUN_MACROCSFIRE == keyfun.fnType)		// 巨集按下後循環執行，放開即停止
				&& macros.nIndex == keyfun.value.macros.macrosIndex)
			{
				bChange = true;
				keyfun.value.macros.type = macros.attr.RunType + GVORDER_FUN_MACROSONCE;
				int nAddrIndex = KEYMAP_PROFILE_SIZE + (xParam.type == GVORDER_DEVICE_KEYBOARD ? KEYMAP_PROFILE_SIZE : 0) + keyfun.nIndex;
				m_KeyProfile[j][nAddrIndex] = macros.attr.RunType + GVORDER_FUN_MACROSONCE;
				fn = keyfun;
			}
		}
		if (bChange)
		{
			CAM300Ctrl::SetKeyMapping(fn);
			CAM300Ctrl::SelProfile(j);
		}
	}
	return 0;
}

DWORD CAM300Ctrl::GetMacrosKey(GVORDER_MACROS& macros)
{
	BYTE byData[MACROS_KEYS_SIZE * 4] = {0};
	BYTE* byMem = &byData[DATA_LENGTH];
	int nLength = CMD_LENGTH;
	DWORD dwReturn = GVAPI_OK;

	int nLen = 0;
	BYTE byMemory[MACROS_KEYS_SIZE * MACROS_KEYS_COUNT] = { 0 };
	nLength = MACROS_KEYS_SIZE * MACROS_KEYS_COUNT;

	DWORD dwAddr = MACROS_KEYS_ADDR + MACROS_KEYS_SIZE * macros.nIndex;
	//dwAddr = dwAddr - (dwAddr % 0x1000);
	CAM300Cmd::MyReadByte(dwAddr, nLength, byMemory);//C400
	memcpy(&m_MarosKey[macros.nIndex][0], byMemory, nLength);

	macros.nCount = 0;
	for (int i = 0; i < MACROS_KEYS_SIZE; i+=nLen)
	{
		BYTE byMaros[10];
		macros.macros[macros.nCount] = CCmdFormat::toMacrosunit(&m_MarosKey[macros.nIndex][i], nLen);
		if(nLen == 0) break;
		macros.nCount++;
	}

	macros.attr = CCmdFormat::toMacrosattr(&m_MarosPro[macros.nIndex][0]);

	return 0;
}
