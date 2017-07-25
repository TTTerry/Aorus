#pragma once

class CKCFirmwareCmd
{
public:
	CKCFirmwareCmd(void);
	~CKCFirmwareCmd(void);

	bool ConnectXK700(WORD wVID, WORD wPID);
	void SyncPCColor(BYTE R, BYTE G, BYTE B);
	void SetColor(BYTE bColorIndex, BYTE R, BYTE G, BYTE B);
	void SaveSetting();
	void SetLedSetting(BYTE bType, BYTE bSpeed, BYTE bMinBrightness, BYTE bBrightness, BYTE bColorIndex, BYTE bCycleCount);
	
	/* Led ON  OFF */
	//static void SetLEDStatus(bool isOn);
	void GetFWVersion(BYTE *pHVer, BYTE *pLVer);
	void GetRGBColor(BYTE colorIdx, BYTE *pR, BYTE *pG, BYTE *pB);
	void GetLedSetting(BYTE* pbType, BYTE* pbSpeed, BYTE* pbMinBrightness, BYTE* pbBrightness, BYTE* pbColorIndex, BYTE* pbCycleCount);
	DWORD SendCommandByte(int nIndex, int nBrd, int nHID, BYTE* szCmd, BYTE* szReceive, int& nCmdLen);

private:
	HANDLE m_hDevice;
};