#pragma once

#define LED_CONSIST		1
#define LED_PULSING		2
#define LED_REACTIVE	3
#define LED_RIPPLE		4
#define LED_CYCLING		5
#define LED_WAVE		6
#define LED_DEFINED		7
#define LED_CMD_LOL		8
#define LED_CMD_CS		9

class CXK700Cmd
{
public:
	CXK700Cmd(void);
	~CXK700Cmd(void);

	/* 連接XK700 */
	static bool ConnectXK700();
	/* 讀取4k byte */
	static void MyReadByte(int Addr, int nLen, BYTE* pMemory);
	/* 寫入4k byte */
	static void Write4KByte(BYTE* pBytes, int Addr);
	/* 同步PC顔色 */
	static void SyncPCColor(BYTE R, BYTE G, BYTE B);
	/* 設置profile */
	static void SwitchProfile(BYTE Profile);
	/* 設置類型 */
	static void ChgLedType(BYTE Profile, BYTE bType);
	/* profile Led類型 速度 亮度 */
	static void GetLedSetting(BYTE Profile, BYTE* pbType, BYTE* pbSpeed, BYTE* pbBrightness, BYTE* pbDir);
	/* 獲取當前profile */
	static BYTE GetProfileIdx();
	/* Led類型 顔色index RGB 速度 亮度 */
	static void ChgLedSetting(BYTE type, BYTE colorIdx, BYTE R, BYTE G, BYTE B, BYTE bright, BYTE speed);  //qifan

	/* Led ON  OFF */
	static void SetLEDStatus(bool isOn);

	//出厂设置
	static BYTE WireDefault(BYTE nProfile);

	/* bStatus NULL = 0 , 104 = 1, 105 = 2*/
	static BYTE bStatus[10];
	static BYTE iLength;


private:
	static void StopFlase();
	static void EraseFlase4K(int Addr);
	static void MyWriteByte(BYTE* pBytes, int nLen);
	static HANDLE hXK700;

};
