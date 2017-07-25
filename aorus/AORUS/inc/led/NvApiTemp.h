#pragma once
#include "math.h"
#define LED_MIN_LIGHT 7

#define LED_CLR_R					0x000001
#define LED_CLR_G					0x000002
#define LED_CLR_B					0x000004
#define LED_CLR_U					0x010000

#define LED_MODE_AUTO				0x000008
#define LED_MODE_ON					0x000010
#define LED_MODE_OFF				0x000020

#define LED_TYPE_NONE				0x001000
#define LED_TYPE_BREATHING			0x002000
#define LED_TYPE_FLASHING			0x004000
#define LED_TYPE_DUAL_FLASHING		0x008000
#define LED_TYPE_VARIABLE_FLASHING	0x010000
#define LED_TYPE_RANDOM				0x020000
#define LED_TYPE_AUDIO_FLASHING		0x040000

#define POWER_ONE_LOW		0x01
#define POWER_ONE_HIGH		0x02
#define POWER_ONE_OK		0x04
#define POWER_TWO_LOW		0x10
#define POWER_TWO_HIGH		0x20
#define POWER_TWO_OK		0x40

#define SLI_TYPE_GA			0x01
#define SLI_TYPE_NV			0x02

#define CTRL_MODE_CARD		0x01
#define CTRL_MODE_SLI		0x02
#define CTRL_MODE_SYNC		0x03

static const DWORD s_ClrCmd[] = {
	LED_CLR_R, 
	LED_CLR_G, 
	LED_CLR_B, 
	LED_CLR_R | LED_CLR_G, 
	LED_CLR_R | LED_CLR_B, 
	LED_CLR_B | LED_CLR_G, 
	LED_CLR_R | LED_CLR_G | LED_CLR_B, 

};

class CVGALed
{
public:
	CVGALed(void);
	~CVGALed(void);

	static int m_nLight;

	static bool IsFanStop(int nIndex);
	static CString TranslateStatus(DWORD dwStatus);
	static DWORD GetPowerStatus(int nIndex);
	static bool SwitchMode(int nIndex, DWORD dwMode);
	static void SetLed(int nIndex, DWORD dwMode, DWORD dwLED);
	static void SetLedLight(int nIndex, DWORD dwMode, int nSpeed, int nRange, int nMinRange = 0);
	static void SetLed(int nIndex, DWORD dwMode);
	static void SetColor(int nIndex, int nR, int nG, int nB);
	static void SetLight(LED_SETTING setting, int nCount);
	static void SetLight(DWORD dwMode, int nSpeed, int nRange, int nCount);
	static void SetLight(int nValue, int nType, int nCount);
	static void SetLightBeach(int nCount, int nSpeed, int nRange);
	static void SetLightFlash(int nCount, int nSpeed, int nRange);
	static void SetLightDoubleFlash(int nCount, int nSpeed, int nRange);
	static void Save(int nIndex);
	static void SetSliType(int nType, int nIndex);
	static float GetVersion(int nGpuIndex = 0);
	static DWORD WriteI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr);
	static DWORD ReadI2C(int nGpuIndex, PGVDISP_I2C_REGADDR pRegAddr, unsigned char*  data);
	static void ChangeClr(int nIndex);

	static int m_nColorIndex;
	static bool m_bRandClr;
	static DWORD m_dwMode;
	static DWORD m_dwI2CAddr;
	static int m_nCount;
};
