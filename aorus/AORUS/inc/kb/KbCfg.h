#pragma once

typedef struct _KB_CLR_CFG
{
	int nCount;
	COLORREF clrList[10];
	_KB_CLR_CFG();
	_KB_CLR_CFG(int nType);

}KB_CLR_CFG, *PKB_CLR_CFG;

typedef struct _KB_LED_CFG
{
#define START_PRESS 0
#define START_AUTO  1

#define LED_CONSISTENT	1
#define LED_PULSING		2
#define LED_REACTIVE	3
#define LED_RIPPLE		4
#define LED_CYCLING		5
#define LED_WAVE		6
#define LED_LOL			7
#define LED_CS			8

	int		nType;
	int		nSpeed;
	int		nBrightness;
	int		nStartWay;
	int		nTimes;
	int		nWidth;
	int		nAngle;
	int		nClrCount;
	bool	bOn;
	KB_CLR_CFG clrCfg[10];

	void Def(int nType);

	_KB_LED_CFG();

}KB_LED_CFG, *PKB_LED_CFG;

class CKbCfg
{
public:
	CKbCfg(void);
	~CKbCfg(void);

	static void SetClrCfg(KB_CLR_CFG cfg, int nType, int nIndex);
	static void SetClrCfgs(KB_CLR_CFG cfg[], int nType, int nCount);
	static void GetClrCfgs(KB_CLR_CFG cfg[], int nType, int& nCount);
};
