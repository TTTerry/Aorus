#include "StdAfx.h"
#include "KbCfg.h"

KB_CLR_CFG::_KB_CLR_CFG()
{
	nCount = 1;
	ZeroMemory(clrList, sizeof(COLORREF) * 10);
	clrList[0] = 255;
}

KB_CLR_CFG::_KB_CLR_CFG(int nType)
{
	switch(nType)
	{
	case 0:
		clrList[0] = s_clrKbLed[0];
		nCount = 1;
		break;
	case 1:
		clrList[0] = s_clrKbLed[0];
		clrList[1] = s_clrKbLed[1];
		nCount = 2;
		break;
	case 2:
		clrList[0] = s_clrKbLed[0];
		nCount = 0;
		break;
	case 3:
		clrList[0] = s_clrKbLed[0];
		clrList[1] = s_clrKbLed[1];
		clrList[2] = s_clrKbLed[2];
		clrList[3] = s_clrKbLed[3];
		clrList[4] = s_clrKbLed[4];
		clrList[5] = s_clrKbLed[5];
		clrList[6] = s_clrKbLed[6];
		nCount = 7;
		break;
	case 4:
		clrList[0] = s_clrKbLed[0];
		clrList[1] = s_clrKbLed[1];
		clrList[2] = s_clrKbLed[2];
		clrList[3] = s_clrKbLed[3];
		clrList[4] = s_clrKbLed[4];
		clrList[5] = s_clrKbLed[5];
		clrList[6] = s_clrKbLed[7];
		nCount = 7;
		break;
	case 5:
		clrList[0] = s_clrKbLed[0];
		clrList[1] = s_clrKbLed[1];
		clrList[2] = s_clrKbLed[2];
		clrList[3] = s_clrKbLed[3];
		clrList[4] = s_clrKbLed[4];
		clrList[5] = s_clrKbLed[5];
		clrList[6] = s_clrKbLed[7];
		nCount = 7;
		break;
	}
}

KB_LED_CFG::_KB_LED_CFG()
{
	nType = 1;
	nSpeed = 10;
	nBrightness = 10;
	nStartWay = START_AUTO;
	nTimes = 2;
	nWidth = 2;
	nAngle = 0;
	nClrCount = 0;
	bOn = true;
}

void KB_LED_CFG::Def(int nType)
{
	switch(nType)
	{
	case 1:
		nType = LED_CONSISTENT;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_AUTO;
		nTimes = 2;
		nWidth = 2;
		nAngle = 0;
		bOn = true;
		nClrCount = 1;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].nCount = 1;
		break;
	case 2:
		nType = LED_PULSING;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_AUTO;
		nTimes = 2;
		nWidth = 2;
		nAngle = 0;
		nClrCount = 1;
		bOn = true;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].clrList[1] = s_clrKbLed[1];
		clrCfg[0].nCount = 2;
		break;
	case 3:
		nType = LED_REACTIVE;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_AUTO;
		nTimes = 2;
		nWidth = 1;
		nAngle = 1;
		nClrCount = 1;
		bOn = true;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].nCount = 0;
		break;
	case 4:
		nType = LED_RIPPLE;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_PRESS;
		nTimes = 1;
		nWidth = 1;
		nAngle = 0;
		nClrCount = 1;
		bOn = true;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].clrList[1] = s_clrKbLed[1];
		clrCfg[0].clrList[2] = s_clrKbLed[2];
		clrCfg[0].clrList[3] = s_clrKbLed[3];
		clrCfg[0].clrList[4] = s_clrKbLed[4];
		clrCfg[0].clrList[5] = s_clrKbLed[5];
		clrCfg[0].clrList[6] = s_clrKbLed[6];
		clrCfg[0].nCount = 7;
		break;
	case 5:
		nType = LED_CYCLING;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_AUTO;
		nTimes = 0;
		nWidth = 2;
		nAngle = 0;
		nClrCount = 1;
		bOn = true;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].clrList[1] = s_clrKbLed[1];
		clrCfg[0].clrList[2] = s_clrKbLed[2];
		clrCfg[0].clrList[3] = s_clrKbLed[3];
		clrCfg[0].clrList[4] = s_clrKbLed[4];
		clrCfg[0].clrList[5] = s_clrKbLed[5];
		clrCfg[0].clrList[6] = s_clrKbLed[7];
		clrCfg[0].nCount = 7;
		break;
	case 6:
		nType = LED_WAVE;
		nSpeed = 10;
		nBrightness = 10;
		nStartWay = START_PRESS;
		nTimes = 1;
		nWidth = 2;
		nAngle = 0;
		nClrCount = 1;
		bOn = true;
		clrCfg[0].clrList[0] = s_clrKbLed[0];
		clrCfg[0].clrList[1] = s_clrKbLed[1];
		clrCfg[0].clrList[2] = s_clrKbLed[2];
		clrCfg[0].clrList[3] = s_clrKbLed[3];
		clrCfg[0].clrList[4] = s_clrKbLed[4];
		clrCfg[0].clrList[5] = s_clrKbLed[5];
		clrCfg[0].clrList[6] = s_clrKbLed[7];
		clrCfg[0].nCount = 7;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

CKbCfg::CKbCfg(void)
{
}

CKbCfg::~CKbCfg(void)
{
}

void CKbCfg::SetClrCfg(KB_CLR_CFG cfg, int nType, int nIndex)
{
	CIniFile ini;
	CString sPath = CKbLedCtrl::GetCfgPath(-1) + _T("present.ini");
	ini.SetIniFile(sPath);
	CString sSession;
	sSession.Format(_T("T%d_%d"), nType, nIndex);
	for (int m = 0; m < cfg.nCount; m++)
	{
		CString sKey;
		sKey.Format(_T("C%d"), m);
		ini.SetIniInfo(sSession, sKey, cfg.clrList[m]);
	}
	ini.SetIniInfo(sSession, _T("Count"), cfg.nCount);
}

void CKbCfg::SetClrCfgs(KB_CLR_CFG cfg[], int nType, int nCount)
{
	CIniFile ini;
	CString sPath = CKbLedCtrl::GetCfgPath(-1) + _T("present.ini");
	ini.SetIniFile(sPath);
	CString sSession;
	for (int n = 0; n < nCount; n++)
	{
		sSession.Format(_T("T%d_%d"), nType, n);
		for (int m = 0; m < cfg[n].nCount; m++)
		{
			CString sKey;
			sKey.Format(_T("C%d"), m);
			ini.SetIniInfo(sSession, sKey, cfg[n].clrList[m]);
		}
		ini.SetIniInfo(sSession, _T("Count"), cfg[n].nCount);
	}
	sSession.Format(_T("T%d"), nType);
	ini.SetIniInfo(sSession, _T("Count"), nCount);
}

void CKbCfg::GetClrCfgs(KB_CLR_CFG cfg[], int nType, int& nCount)
{
	CIniFile ini;
	CString sPath = CKbLedCtrl::GetCfgPath(-1) + _T("present.ini");

	ini.SetIniFile(sPath);
	CString sSession;
	sSession.Format(_T("T%d"), nType);
	BOOL bGet = ini.GetIniInfo(sSession, _T("Count"), nCount);

	if (!bGet)
	{
		KB_CLR_CFG cfgDefault(nType);
		cfg[0] = cfgDefault;
		nCount = 1;
		SetClrCfgs(cfg, nType, nCount);
		return;
	}

	for (int n = 0; n < nCount; n++)
	{
		sSession.Format(_T("T%d_%d"), nType, n);
		ini.GetIniInfo(sSession, _T("Count"), cfg[n].nCount);
		for (int m = 0; m < cfg[n].nCount; m++)
		{
			CString sKey;
			sKey.Format(_T("C%d"), m);
			ini.GetIniInfo(sSession, sKey, cfg[n].clrList[m]);
		}
	}
}
