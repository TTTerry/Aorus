#include "StdAfx.h"
#include "Cfg.h"
#include "math.h"
#include "../../AORUSDlg.h"


CCfg::CCfg()
{
	m_nNumOfCards = 1;
	ZeroMemory(m_curProfile, sizeof(m_curProfile));
	for (int i = 0; i < GVDISP_CARD_MAXNUM; i++)
	{
		m_nProfileCount[i]=0;
		m_nVgaMode[i] = 2;
	}
	m_curCarSel = 0;
	m_bOcCard = TRUE;
	m_sCardIds = _T("test_ids");
	m_csName = _T("GIGABYTE");
	m_csPassword=_T("123456");
}
CCfg::~CCfg()
{
}

const VGA_PARAM_BASESETTING CCfg::GetBaseSetting()
{
	return m_baseSetting;
}

void CCfg::GetBaseSetting(VGA_PARAM_BASESETTING& setting)
{
	setting = m_baseSetting;
}

#pragma region Encrypt/Decrypt

CString CCfg::DecryptConfig()
{
	CString sModuleFile = _T("");
	GetModuleFileName(NULL, sModuleFile.GetBuffer(MAX_PATH), MAX_PATH);
	sModuleFile.ReleaseBuffer();
	if(sModuleFile != _T(""))
	{
		sModuleFile = sModuleFile.Left(sModuleFile.ReverseFind('\\') + 1);
	}

	CString sCfgFile =sModuleFile + _T("AORUS.DAT");

	SYSTEMTIME stT;
	::GetLocalTime(&stT);
	CString sTempCfg;
	sTempCfg.Format(_T("%04d%02d%02d_%02d%02d%02d.ini"), stT.wYear, stT.wMonth, stT.wDay, stT.wHour, stT.wMinute, stT.wSecond);
	

	sTempCfg = sModuleFile + _T("GvTemp\\") + sTempCfg;
	::CreateDirectory(sModuleFile + _T("GvTemp\\"), NULL);

	if(PathFileExists(sTempCfg))
	{
		CFile::Remove(sTempCfg);
	}

	BOOL bSuccessful = FALSE;
	if(PathFileExists(sCfgFile))
	{
		USES_CONVERSION;
		CHAR szPassword[64] = "89124888";
		if(GVAPI_OK == GvDecryptFile((LPTSTR)(LPCTSTR)sCfgFile, (LPTSTR)(LPCTSTR)sTempCfg, PBYTE(szPassword)))
		{
			bSuccessful = TRUE;
		}
		else if(GVAPI_OK == GvDecryptFile((LPTSTR)(LPCTSTR)sCfgFile, (LPTSTR)(LPCTSTR)sTempCfg, PBYTE(szPassword)))
		{
			bSuccessful = TRUE;
		}

	}

	if(!bSuccessful)
	{
		CFile file;
		if(file.Open(sTempCfg, CFile::modeCreate))
		{
			file.Close();
			bSuccessful = TRUE;
		}
	}

	return bSuccessful ? sTempCfg : _T("");
}

void CCfg::EncryptConfig(CString sTempCfg)
{
	CmdLock();
	CString sModuleFile = _T("");
	GetModuleFileName(NULL, sModuleFile.GetBuffer(MAX_PATH), MAX_PATH);
	sModuleFile.ReleaseBuffer();
	if(sModuleFile != _T(""))
	{
		sModuleFile = sModuleFile.Left(sModuleFile.ReverseFind('\\') + 1);
	}

	CString sCfgFile = sModuleFile + _T("AORUS.DAT");
	if (!PathFileExists(sTempCfg))
		return; 
	if(PathFileExists(sCfgFile))
	{
		CFile::Remove(sCfgFile);
	}

	USES_CONVERSION;
	CHAR szPassword[64] = "89124888";
	GvEncryptFile((LPTSTR)(LPCTSTR)sTempCfg, (LPTSTR)(LPCTSTR)sCfgFile, PBYTE(szPassword));
	CFile::Remove(sTempCfg);
	CmdUnLock();
}

#pragma endregion

BOOL CCfg::Initialize()
{
	CmdLock();

//	CString strDevice = _T("COMMON");
	GVDISP_VGA_INFO vgaInfo  = {0};
	BOOL bIdsSuccessful = TRUE;
	CString sConfig = DecryptConfig();
	m_sCardIds=Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sVid + _T("_") + Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sDid 
		+ _T("_") + Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sSsid + _T("_") + Aorus()->GetVGA()->Ctrl()->GetCardInfo()->sSvid;
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);

		// 读取Profile资讯
		
		m_nNumOfCards=Aorus()->GetVGA()->Ctrl()->GetGpuCount();
		for (int j = 0; j < Aorus()->GetVGA()->Ctrl()->GetGpuCount(); j++)
		{
			CString sProfile;
			sProfile.Format(_T("CARD_%d_ProfileCount"), j);
			config.GetIniInfo(m_sCardIds, sProfile,	m_nProfileCount[j], TRUE);

			for (int i = 0; i < 8; i++)
			{
				CString sSession = _T("");
				int nClk = 0;
				sSession.Format(_T("PRO%d_%d_"), i, j);
				if(config.GetIniInfo(m_sCardIds, sSession + _T("GpuClk"), nClk, FALSE))
				{
					//if(i + 1 > m_nProfileCount) m_nProfileCount = i + 1;
				}
			}
		}
        config.GetIniInfo(m_sCardIds,_T("REMOTE_NAME"),m_csName,true);
		config.GetIniInfo(m_sCardIds,_T("REMOTE_PASSWORD"),m_csPassword,true);

		config.GetIniInfo(m_sCardIds, _T("BASE_SyncLed"),		m_baseSetting.bSyncLed,			TRUE);
		config.GetIniInfo(m_sCardIds, _T("BASE_SyncMutil"),		m_baseSetting.bSyncMutil,		TRUE);
		config.GetIniInfo(m_sCardIds, _T("BASE_AutoRun"),		m_baseSetting.bAutoRun,			TRUE);
		config.GetIniInfo(m_sCardIds, _T("BASE_CheckUpdate"),	m_baseSetting.bCheckUpdate,		TRUE);
		config.GetIniInfo(m_sCardIds, _T("BASE_CloseMin"),		m_baseSetting.bCloseMin,		TRUE); 
		config.GetIniInfo(m_sCardIds, _T("BASE_Minimize"),		m_baseSetting.bMinimize,		TRUE); 
		config.GetIniInfo(m_sCardIds, _T("BASE_LastCheck"),		m_baseSetting.sLastCheckUpdate,	TRUE); 
// 		config.GetIniInfo(strDevice,_T("REMOTE_NAME"),m_csName,true);
// 		config.GetIniInfo(strDevice,_T("REMOTE_PASSWORD"),m_csPassword,true);
// 
// 		config.GetIniInfo(strDevice, _T("BASE_SyncLed"),		m_baseSetting.bSyncLed,			TRUE);
// 		config.GetIniInfo(strDevice, _T("BASE_SyncMutil"),		m_baseSetting.bSyncMutil,		TRUE);
// 		config.GetIniInfo(strDevice, _T("BASE_AutoRun"),		m_baseSetting.bAutoRun,			TRUE);
// 		config.GetIniInfo(strDevice, _T("BASE_CheckUpdate"),	m_baseSetting.bCheckUpdate,		TRUE);
// 		config.GetIniInfo(strDevice, _T("BASE_CloseMin"),		m_baseSetting.bCloseMin,		TRUE); 
// 		config.GetIniInfo(strDevice, _T("BASE_Minimize"),		m_baseSetting.bMinimize,		TRUE); 
// 		config.GetIniInfo(strDevice, _T("BASE_LastCheck"),		m_baseSetting.sLastCheckUpdate,	TRUE); 

		if(bIdsSuccessful)
		{
			config.GetIniInfo(m_sCardIds, _T("MONI_GpuClk"),		m_moniSetting.bGpuClk,		TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_MemClk"),		m_moniSetting.bMemClk,		TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_GpuVol"),		m_moniSetting.bGpuVol,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_Power"),			m_moniSetting.bPower,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_MemVol"),		m_moniSetting.bMemVol,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_FanSpd"),		m_moniSetting.bFanSpd,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_FanRpm"),		m_moniSetting.bFanRpm,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_Temperature"),	m_moniSetting.bTemperature,	TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_GPUsage"),		m_moniSetting.bGPUsage,		TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_CPUsage"),		m_moniSetting.bCPUsage,		TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_CPUClock"),		m_moniSetting.bCPUClock,	TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_MemUsage"),		m_moniSetting.bMemUsage,	TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_PageUsage"),		m_moniSetting.bPageUsage,	TRUE);
			config.GetIniInfo(m_sCardIds, _T("MONI_LogFile"),		m_moniSetting.sLogFile,		TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_TimeInterval"),	m_moniSetting.nTimeInterval,TRUE); 
			config.GetIniInfo(m_sCardIds, _T("MONI_LogFlag"),	m_moniSetting.bLogRecord,TRUE); 

			for (int i = 0; i <= Aorus()->GetVGA()->Ctrl()->GetGpuCount(); i++)
			{
				CString sProfile;
				sProfile.Format(_T("CARD%d"), i);
				config.GetIniInfo(m_sCardIds, sProfile + _T("ProSel"), m_curProfile[i], TRUE);
				config.GetIniInfo(m_sCardIds, sProfile + _T("VGAMode"), m_nVgaMode[i], TRUE);
				//GetLedCfgFromIni(config, DEVICE_VGA, m_ledVGA[i], i, 0);
			}

				// Initialize the fan curve.

				for(int i=0; i<m_nNumOfCards; i++)
				{
					VGA_PARAM_RANGE fanR;
					Aorus()->GetVGA()->Ctrl()->GetPerfInfo(VGA_PERF_FANSPD,fanR);
					//GetFanSettingInfo(fanR);
					for (int j = 0; j < 100; j++)
					{
						Aorus()->GetVGA()->Ctrl()->GetFanAutoSetting(m_fanSetting[j][i]);
						/*m_fanSetting[j][i].nFanMode = VGA_FANMODE_AUTO;
						m_fanSetting[j][i].nCurveStep = 6;
						m_fanSetting[j][i].curve[0].nFanSpeed    = 40;
						m_fanSetting[j][i].curve[1].nFanSpeed    = 50;
						m_fanSetting[j][i].curve[2].nFanSpeed    = 60;
						m_fanSetting[j][i].curve[3].nFanSpeed    = 80;
						m_fanSetting[j][i].curve[4].nFanSpeed    = 90;
						m_fanSetting[j][i].curve[5].nFanSpeed    = 100;
						m_fanSetting[j][i].curve[0].nTemperature = 30;
						m_fanSetting[j][i].curve[1].nTemperature = 40;
						m_fanSetting[j][i].curve[2].nTemperature = 50;
						m_fanSetting[j][i].curve[3].nTemperature = 60;
						m_fanSetting[j][i].curve[4].nTemperature = 70;
						m_fanSetting[j][i].curve[5].nTemperature = 80;*/

					/*	if(fanR.nStep > 0)
						{
							for(int m=0; m<m_fanSetting[j][i].nCurveStep; m++)
							{
								if(m_fanSetting[j][i].curve[m].nFanSpeed < fanR.nMin) m_fanSetting[j][i].curve[m].nFanSpeed = fanR.nMin;
								if(m_fanSetting[j][i].curve[m].nFanSpeed > fanR.nMax)	m_fanSetting[j][i].curve[m].nFanSpeed = fanR.nMax;
							}
						}*/
					}
				}
			for(int i=0; i<m_nNumOfCards; i++)
			{
				for (int j = 0; j < m_nProfileCount[i]; j++)
				{
					CString sCurve = _T(""), sIndex = _T("");

					sIndex.Format(_T("_%d_%d"), j, i);
					//TCHAR szCurve[1024] = {0};

					config.GetIniInfo(m_sCardIds, _T("FAN_Percent") + sIndex,	m_fanSetting[j][i].nFanPercent, TRUE);
					config.GetIniInfo(m_sCardIds, _T("FAN_FanMode") + sIndex,	m_fanSetting[j][i].nFanMode, TRUE);
					config.GetIniInfo(m_sCardIds, _T("FAN_CurveStep") + sIndex,	m_fanSetting[j][i].nCurveStep, TRUE);
					config.GetIniInfo(m_sCardIds, _T("FAN_Stop") + sIndex,	m_fanSetting[j][i].bFanStop, TRUE);
					config.GetIniInfo(m_sCardIds, _T("FAN_FanCurve") + sIndex,	sCurve);
					//sCurve.Format(_T("%s"), szCurve);
					if(_T("") == sCurve)
					{
						for(int m=0; m<VGA_FANCURVE_STEPS; m++)
						{
							// Format as (T1,S1)(T2,S2)(T3,S3)(T4,S4).
							CString sTemp;
							sTemp.Format(_T("(%d,%d)"), m_fanSetting[j][i].curve[m].nTemperature, m_fanSetting[j][i].curve[m].nFanSpeed);	
							sCurve += sTemp;
						}
						config.SetIniInfo(m_sCardIds, _T("FAN_FanCurve") + sIndex, sCurve);
					}
					int nLB  = sCurve.Find(_T("("));
					int nRB  = sCurve.Find(_T(")"));
					int nDot = sCurve.Find(_T(","));
					int nCount = 0;
					while(nLB >= 0 && nRB > 0 && nDot > 0)
					{  
						// sCurve = (T1,S1)(T2,S2)(T3,S3)(T4,S4)
						CString sValue = sCurve.Mid(0, nRB + 1);
						sCurve = sCurve.Right(sCurve.GetLength() - nRB - 1);
						CString sTemperature = sValue.Mid(1, nDot - 1);
						CString sFanSpeed = sValue.Mid(nDot + 1, nRB - nDot - 1);

						 m_fanSetting[j][i].curve[nCount].nTemperature = _ttoi(sTemperature);
						 m_fanSetting[j][i].curve[nCount].nFanSpeed = _ttoi(sFanSpeed);

						nLB  = sCurve.Find(_T("("));
						nRB  = sCurve.Find(_T(")"));
						nDot = sCurve.Find(_T(","));

						nCount++; 
						if(nCount >= VGA_FANCURVE_STEPS)
						{
							break;
						}
					}
				}
			}
        }

		for(int i=0; i<m_nNumOfCards; i++)
		{
			for (int j = 0; j < m_nProfileCount[i]; j++)
			{
				CString sProfile, sCurve = _T("");
				sProfile.Format(_T("PRO%d_%d_"), m_nProfileCount, m_nNumOfCards);

				config.GetIniInfo(m_sCardIds,  sProfile + _T("GpuClk"),	m_performance[j][i].nGpuClk, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("MemClk"),	m_performance[j][i].nMemClk, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("GpuVol"),	m_performance[j][i].nGpuVol, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("MaxVol"),	m_performance[j][i].nMaxVol, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("MemVol"),	m_performance[j][i].nMemVol, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("FanSpd"),	m_performance[j][i].nFanSpd, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("FanMode"),m_performance[j][i].nFanMode, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("Power"),	m_performance[j][i].nPower, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("Temp"),	m_performance[j][i].nTemperature, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("TempGPU"),m_performance[j][i].bTempPowerLink, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("VolLock"),m_performance[j][i].bVolLock, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("GpuCv"),	m_performance[j][i].dwGpuClkCurve, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("NumVFPoints"),m_performance[j][i].GpuVf.nNumVFPoints, TRUE);
				config.GetIniInfo(m_sCardIds,  sProfile + _T("GpuCurve"),sCurve, TRUE);
				if(_T("") != sCurve)
				{
					int nLB  = sCurve.Find(_T("("));
					int nRB  = sCurve.Find(_T(")"));
					int nDot = sCurve.Find(_T(","));
					int nCount = 0;
					while(nLB >= 0 && nRB > 0 && nDot > 0)
					{  
						// sCurve = (T1,S1)(T2,S2)(T3,S3)(T4,S4)
						CString sValue = sCurve.Mid(0, nRB + 1);
						sCurve = sCurve.Right(sCurve.GetLength() - nRB - 1);
						CString sIndex = sValue.Mid(1, nDot - 1);
						CString sOffset = sValue.Mid(nDot + 1, nRB - nDot - 1);

						m_performance[j][i].GpuVf.offset[nCount].nIndex= _ttoi(sIndex);
						m_performance[j][i].GpuVf.offset[nCount].nOffset = _ttoi(sOffset);

						nLB  = sCurve.Find(_T("("));
						nRB  = sCurve.Find(_T(")"));
						nDot = sCurve.Find(_T(","));
						nCount++; 
						if(nCount >= VGA_FANCURVE_STEPS)
						{
							break;
						}
					}
				}

			}
		}
    }
    EncryptConfig(sConfig);
	CmdUnLock();
	if(PathFileExists(sConfig))
	{
		CFile::Remove(sConfig);
	}

	return TRUE;
}

int CCfg::GetProfileSel(int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	return m_curProfile[nCard];
}

void CCfg::SetProfileSel(int nCard,int nFieleIndex)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	CString sConfig = DecryptConfig(), sProfile;
	CIniFile config;
	config.SetIniFile(sConfig);
	if(_T("") == sConfig)
	{
		return;
	}

	m_curProfile[nCard]=nFieleIndex;
	sProfile.Format(_T("CARD%d"), nCard);
	config.SetIniInfo(m_sCardIds,sProfile+ _T("ProSel"), nFieleIndex);
	EncryptConfig(sConfig);
	return ;
}

int CCfg::GetVgaMode(int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	return m_nVgaMode[nCard];
}

int CCfg::SetVgaMode(int nVgaMode, int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	CString sConfig = DecryptConfig(), sProfile;
	CIniFile config;
	config.SetIniFile(sConfig);

	sProfile.Format(_T("CARD%d"), nCard);
	config.SetIniInfo(m_sCardIds, sProfile + _T("VGAMode"),	nVgaMode);
	EncryptConfig(sConfig);
	m_nVgaMode[nCard] = nVgaMode;
	return nVgaMode;
}

void CCfg::GetCurVGALedProfile(LED_SETTING& led, int nCard)
{
	//int nProfileCur = 0;
	//CArray<LED_SETTING> profiles;
	//GetLedProfiles(DEVICE_VGA, profiles, nProfileCur, nCard);
	//led = profiles.GetAt(nProfileCur);
}

void CCfg::GetLedProfiles(int nDevice, CArray<LED_SETTING>& profiles, int& nProfileCur, int nCard)
{
	CmdLock();
	CString sPre = _T("");
	CString strDevice = _T("COMMON");
	switch(nDevice)
	{
	case DEVICE_VGA:	sPre.Format(_T("VGA%d_"), nCard); break;
	case DEVICE_SLI:	sPre.Format(_T("SLI%d_"), nCard); break;
	case DEVICE_MB:		sPre.Format(_T("MB%d_"), nCard);  break;
	case DEVICE_ATC700: sPre.Format(_T("ATC700%d_"), nCard); break;
	case DEVICE_AC300:	sPre.Format(_T("AC300%d_"), nCard); break;
	case DEVICE_AH300:	sPre.Format(_T("AH300%d_"), nCard); break;
	case DEVICE_AM300:	sPre.Format(_T("AM300%d_"), nCard); break;
	case DEVICE_AK700:	sPre.Format(_T("AK700%d_"), nCard); break;
	case DEVICE_H5:	sPre.Format(_T("H5%d_"), nCard); break;
	default: return;
	}

	CString sConfig = DecryptConfig();
	if (_T("") == sConfig)
		return; // Decrypt error

	CIniFile ini;
	ini.SetIniFile(sConfig);

	int nProfiles = 1;
	int nCurProfile = 0;

	ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Profiles"), nProfiles, TRUE);
	ini.GetIniInfo(m_sCardIds, sPre + _T("LED_CurProfile"), nCurProfile, TRUE);

	nProfileCur = nCurProfile;
	for (int i = 0; i < 5; i++)//Terry 2017/07/18
	{
		LED_SETTING led;
		switch(nDevice)
		{
		case DEVICE_VGA:	sPre.Format(_T("VGA%d_%d_"), nCard, i); break;
		case DEVICE_SLI:	sPre.Format(_T("SLI%d_%d_"), nCard, i); break;
		case DEVICE_MB:		sPre.Format(_T("MB%d_%d_"), nCard, i);  break;
		case DEVICE_ATC700: sPre.Format(_T("ATC700%d_%d_"), nCard, i); break;
		case DEVICE_AC300:	sPre.Format(_T("AC300%d_%d_"), nCard, i); break;
		case DEVICE_AH300:	sPre.Format(_T("AH300%d_%d_"), nCard, i); break;
		case DEVICE_AM300:	sPre.Format(_T("AM300%d_%d_"), nCard, i); break;
		case DEVICE_AK700:	sPre.Format(_T("AK700%d_%d_"), nCard, i); break;
		case DEVICE_H5:	sPre.Format(_T("H5%d_%d_"), nCard, i); break;
		}
		
			CString sColor = _T("");
		if ((nDevice == DEVICE_ATC700) || (nDevice == DEVICE_AC300) || (nDevice == DEVICE_AH300) \
			|| (nDevice == DEVICE_AM300) || (nDevice == DEVICE_AK700) ||  (nDevice == DEVICE_H5))
		{
			ini.GetIniInfo(strDevice, sPre + _T("LED_ProName"),	led.sProfileName, TRUE);
			ini.GetIniInfo(strDevice, sPre + _T("LED_On"),			led.bOn, TRUE);
			ini.GetIniInfo(strDevice, sPre + _T("LED_Select"),		led.nSelectCard, TRUE);
			ini.GetIniInfo(strDevice, sPre + _T("LED_Style"),		led.dwStyle, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Variation"),	led.dwVariation, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Range"),		led.nRangeMax, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_RangeMin"),	led.nRangeMin, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Speed"),		led.nSpeed, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Type"),		led.nType, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Random"),		led.bMutilColor, TRUE); 
			ini.GetIniInfo(strDevice, sPre + _T("LED_Color"),		sColor, TRUE); 
		}
		else{
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_ProName"),	led.sProfileName, TRUE);
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_On"),			led.bOn, TRUE);
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Select"),		led.nSelectCard, TRUE);
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Style"),		led.dwStyle, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Variation"),	led.dwVariation, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Range"),		led.nRangeMax, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_RangeMin"),	led.nRangeMin, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Speed"),		led.nSpeed, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Type"),		led.nType, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Random"),		led.bMutilColor, TRUE); 
			ini.GetIniInfo(m_sCardIds, sPre + _T("LED_Color"),		sColor, TRUE); 
		}

		if (!sColor.IsEmpty())
		{
			int nR = 0, nG = 0, nB = 0;
			_stscanf(sColor, _T("#%2X%2X%2X"), &nR, &nG, &nB);
			led.clrLed = RGB(nR, nG, nB);
		}
		profiles.Add(led);
	}

	EncryptConfig(sConfig);
	CmdUnLock();
}

void CCfg::SetLedProfiles(int nDevice, CArray<LED_SETTING>& profiles, int nProfileCur, int nCard)
{
	CmdLock();
	CString sPre = _T("");
	CString strDevice = _T("COMMON");
	switch(nDevice)
	{
	case DEVICE_VGA:	sPre.Format(_T("VGA%d_"), nCard); break;
	case DEVICE_SLI:	sPre.Format(_T("SLI%d_"), nCard); break;
	case DEVICE_MB:		sPre.Format(_T("MB%d_"), nCard);  break;
	case DEVICE_ATC700: sPre.Format(_T("ATC700%d_"), nCard); break;
	case DEVICE_AC300:	sPre.Format(_T("AC300%d_"), nCard); break;
	case DEVICE_AH300:	sPre.Format(_T("AH300%d_"), nCard); break;
	case DEVICE_AM300:	sPre.Format(_T("AM300%d_"), nCard); break;
	case DEVICE_AK700:	sPre.Format(_T("AK700%d_"), nCard); break;
	case DEVICE_H5:	sPre.Format(_T("H5%d_"), nCard); break;
	default: return;
	}

	CString sConfig = DecryptConfig();
	if (_T("") == sConfig)
		return; // Decrypt error

	CIniFile ini;
	ini.SetIniFile(sConfig);

	int nProfiles = (int)profiles.GetSize();

	ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Profiles"), nProfiles);
	ini.SetIniInfo(m_sCardIds, sPre + _T("LED_CurProfile"), nProfileCur);

	Sleep(500);
	for (int i = 0; i < nProfiles; i++)
	{
		LED_SETTING led = profiles.GetAt(i);
		switch(nDevice)
		{
		case DEVICE_VGA:	sPre.Format(_T("VGA%d_%d_"), nCard, i); break;
		case DEVICE_SLI:	sPre.Format(_T("SLI%d_%d_"), nCard, i); break;
		case DEVICE_MB:		sPre.Format(_T("MB%d_%d_"), nCard, i);  break;
		case DEVICE_ATC700: sPre.Format(_T("ATC700%d_%d_"), nCard, i); break;
		case DEVICE_AC300:	sPre.Format(_T("AC300%d_%d_"), nCard, i); break;
		case DEVICE_AH300:	sPre.Format(_T("AH300%d_%d_"), nCard, i); break;
		case DEVICE_AM300:	sPre.Format(_T("AM300%d_%d_"), nCard, i); break;
		case DEVICE_AK700:	sPre.Format(_T("AK700%d_%d_"), nCard, i); break;
		case DEVICE_H5:	sPre.Format(_T("H5%d_%d_"), nCard, i); break;
		}

		if ((nDevice == DEVICE_ATC700) || (nDevice == DEVICE_AC300) || (nDevice == DEVICE_AH300) \
			|| (nDevice == DEVICE_AM300) || (nDevice == DEVICE_AK700) ||  (nDevice == DEVICE_H5))
		{
			ini.SetIniInfo(strDevice, sPre + _T("LED_ProName"),	led.sProfileName);
			ini.SetIniInfo(strDevice, sPre + _T("LED_On"),			led.bOn);
			ini.SetIniInfo(strDevice, sPre + _T("LED_Select"),		led.nSelectCard);
			ini.SetIniInfo(strDevice, sPre + _T("LED_Style"),		led.dwStyle); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Variation"),	led.dwVariation); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Range"),		led.nRangeMax); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_RangeMin"),	led.nRangeMin); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Speed"),		led.nSpeed); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Type"),		led.nType); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Random"),		led.bMutilColor); 
			ini.SetIniInfo(strDevice, sPre + _T("LED_Color"),		ColorToString(led.clrLed)); 
		}
		else{
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_ProName"),	led.sProfileName);
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_On"),			led.bOn);
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Select"),		led.nSelectCard);
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Style"),		led.dwStyle); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Variation"),	led.dwVariation); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Range"),		led.nRangeMax); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_RangeMin"),	led.nRangeMin); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Speed"),		led.nSpeed); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Type"),		led.nType); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Random"),		led.bMutilColor); 
			ini.SetIniInfo(m_sCardIds, sPre + _T("LED_Color"),		ColorToString(led.clrLed)); 
		}

	}

	EncryptConfig(sConfig);
	CmdUnLock();
}



void CCfg::SetLoadingInfo(CString csName,CString csPasswor)
{
	CString strDevice = _T("COMMON");
	m_csName=csName;
	m_csPassword=csPasswor;
	CString sConfig = DecryptConfig();
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);
// 		config.SetIniInfo(m_sCardIds,  _T("REMOTE_NAME"),	  m_csName);
// 		config.SetIniInfo(m_sCardIds,  _T("REMOTE_PASSWORD"), m_csPassword);
		config.SetIniInfo(strDevice,  _T("REMOTE_NAME"),	  m_csName);
		config.SetIniInfo(strDevice,  _T("REMOTE_PASSWORD"), m_csPassword);
		EncryptConfig(sConfig);
	}
}
void CCfg::SetProfileName(int nProfile,int nCard,CString csName)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	CString sConfig = DecryptConfig();
	if(_T("") != sConfig)
	{
		CString str;
		str.Format(L"Card %d Profile %d name",nCard,nProfile);
		CIniFile config;
		config.SetIniFile(sConfig);
		config.SetIniInfo(m_sCardIds, str, csName);
		EncryptConfig(sConfig);
	}
}
void CCfg::GetLoadingInfo(CString &csName,CString &csPasswor)
{
	csName=m_csName;
	csPasswor=m_csPassword;
}
void CCfg::GetProfileName(int nProfile,int nCard ,CString &csName)
{
	if(nCard < 0) nCard = 0;
	CIniFile config;
	CString sProfile;
	CString sConfig = DecryptConfig();
	if(_T("") != sConfig)
	{
		CString str;
		str.Format(L"Card %d Profile %d name",nCard,nProfile);
		CIniFile config;
		config.SetIniFile(sConfig);
		config.GetIniInfo(m_sCardIds,str,csName,true);
		if(PathFileExists(sConfig))
		{
			CFile::Remove(sConfig);
		}
	}
}

void CCfg::GetFanSetting(FAN_SETTING& setting, int nCard, int nProfile)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	setting = m_fanSetting[nProfile][nCard];
}
void CCfg::GetPerformances(DWORD dwPerfs, VGA_PERFORMANCE& perf, int nProfile, int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	// Get user setting value.
	perf.nFanMode = VGA_FANMODE_AUTO;

	if(dwPerfs & VGA_PERF_GPUCLK)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_GPUCLK,		perf);
	if(dwPerfs & VGA_PERF_MEMCLK)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_MEMCLK,		perf);
	if(dwPerfs & VGA_PERF_POWER)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_POWER,		perf);
	if(dwPerfs & VGA_PERF_TEMPER)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_TEMPER,		perf);
	if(dwPerfs & VGA_PERF_FANSPD)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_FANSPD,		perf);
	if(dwPerfs & VGA_PERF_OVERVOL)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_OVERVOL,		perf);
	//if(dwPerfs & VGA_PERF_OVERVOL)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_OVERVOL,		perf);
	if(dwPerfs & VGA_PERF_MEMVOL)		Aorus()->GetVGA()->Ctrl()->GetPerformancesDefault(VGA_PERF_MEMVOL,		perf);
	if(dwPerfs & VGA_PERF_GCLKCUV )
	{
		GetVfClockClock(perf.GpuVf, GVDISP_CLOCK_DOMAIN_ID_GPU, nCard);
	}
	if(dwPerfs & VGA_PERF_MCLKCUV )
	{
		GetVfClockClock(perf.MemVf, GVDISP_CLOCK_DOMAIN_ID_MEMORY, nCard);
	}

	CIniFile config;
	CString sProfile;
	CString sConfig = DecryptConfig();
	if(_T("") == sConfig)
	{
		return;
	}

	sProfile.Format(_T("PRO%d_%d_"), nProfile, nCard);
	config.SetIniFile(sConfig);

	//config.GetIniInfo(m_sCardIds, _T("CardCheck"), perf.nCardCheck,	TRUE);
	config.GetIniInfo(m_sCardIds, sProfile + _T("VolLock"),	perf.bVolLock,	TRUE);
	if(dwPerfs & VGA_PERF_GPUCLK)		config.GetIniInfo(m_sCardIds, sProfile + _T("GpuClk"),	perf.nGpuClk,		TRUE);
	if(dwPerfs & VGA_PERF_MEMCLK)		config.GetIniInfo(m_sCardIds, sProfile + _T("MemClk"),	perf.nMemClk,		TRUE);
	if(dwPerfs & VGA_PERF_OVERVOL)		config.GetIniInfo(m_sCardIds, sProfile + _T("GpuVol"),	perf.nGpuVol,		TRUE);
	//if(dwPerfs & VGA_PERF_OVERVOL)		config.GetIniInfo(m_sCardIds, sProfile + _T("MaxVol"),	perf.nMaxVol,		TRUE);
	//if(dwPerfs & VGA_PERF_OVERVOL)		config.GetIniInfo(m_sCardIds, sProfile + _T("MaxCheck"),perf.nMaxVolCheck,	TRUE);
	if(dwPerfs & VGA_PERF_MEMVOL)		config.GetIniInfo(m_sCardIds, sProfile + _T("MemVol"),	perf.nMemVol,		TRUE);
	if(dwPerfs & VGA_PERF_POWER)		config.GetIniInfo(m_sCardIds, sProfile + _T("Power"),	perf.nPower,		TRUE);
	if(dwPerfs & VGA_PERF_TEMPER)		config.GetIniInfo(m_sCardIds, sProfile + _T("Temp"),	perf.nTemperature,	TRUE);
	if(dwPerfs & VGA_PERF_TEMPER)	    config.GetIniInfo(m_sCardIds, sProfile + _T("TempGPU"), perf.bTempPowerLink,TRUE);
	if(dwPerfs & VGA_PERF_FANSPD)		config.GetIniInfo(m_sCardIds, sProfile + _T("FanSpd"),	perf.nFanSpd,		TRUE);
	if(dwPerfs & VGA_PERF_FANSPD)		config.GetIniInfo(m_sCardIds, sProfile + _T("FanMode"),	perf.nFanMode,		TRUE);
	if(dwPerfs & VGA_PERF_GCLKCUV)		config.GetIniInfo(m_sCardIds, sProfile + _T("GpuCv"),	perf.dwGpuClkCurve,	TRUE);
	if(dwPerfs & VGA_PERF_MCLKCUV)		config.GetIniInfo(m_sCardIds, sProfile + _T("MemCv"),	perf.dwMemClkCurve,	TRUE);
	if(dwPerfs & VGA_PERF_GCLKCUV)
	{
		CString sCurve;
		config.GetIniInfo(m_sCardIds, sProfile + _T("GpuCurve"),	sCurve);

		int nLB  = sCurve.Find(_T("("));
		int nRB  = sCurve.Find(_T(")"));
		int nDot = sCurve.Find(_T(","));
		int nCount = 0;
		while(nLB >= 0 && nRB > 0 && nDot > 0)
		{  
			// sCurve = (T1,S1)(T2,S2)(T3,S3)(T4,S4)
			CString sValue = sCurve.Mid(0, nRB + 1);
			sCurve = sCurve.Right(sCurve.GetLength() - nRB - 1);
			CString sIndex = sValue.Mid(1, nDot - 1);
			CString sOffset = sValue.Mid(nDot + 1, nRB - nDot - 1);

			perf.GpuVf.offset[nCount].nIndex = _ttoi(sIndex);
			perf.GpuVf.offset[nCount].nOffset = _ttoi(sOffset);

			nLB  = sCurve.Find(_T("("));
			nRB  = sCurve.Find(_T(")"));
			nDot = sCurve.Find(_T(","));

			nCount++; 
			if(nCount >= GVDISP_VFPT_MAXNUM)
			{
				break;
			}
		}
		perf.GpuVf.nNumVFPoints = nCount;
	}

	if(dwPerfs & VGA_PERF_MCLKCUV)
	{
		CString sCurve;
		config.GetIniInfo(m_sCardIds, sProfile + _T("MemCurve"),	sCurve);

		int nLB  = sCurve.Find(_T("("));
		int nRB  = sCurve.Find(_T(")"));
		int nDot = sCurve.Find(_T(","));
		int nCount = 0;
		while(nLB >= 0 && nRB > 0 && nDot > 0)
		{  
			// sCurve = (T1,S1)(T2,S2)(T3,S3)(T4,S4)
			CString sValue = sCurve.Mid(0, nRB + 1);
			sCurve = sCurve.Right(sCurve.GetLength() - nRB - 1);
			CString sIndex = sValue.Mid(1, nDot - 1);
			CString sOffset = sValue.Mid(nDot + 1, nRB - nDot - 1);

			perf.MemVf.offset[nCount].nIndex = _ttoi(sIndex);
			perf.MemVf.offset[nCount].nOffset = _ttoi(sOffset);

			nLB  = sCurve.Find(_T("("));
			nRB  = sCurve.Find(_T(")"));
			nDot = sCurve.Find(_T(","));

			nCount++; 
			if(nCount >= GVDISP_VFPT_MAXNUM)
			{
				break;
			}
		}
		perf.MemVf.nNumVFPoints = nCount;
	}

	EncryptConfig(sConfig);
}

bool CCfg::GetVfClockClock(GVDISP_CLOCK_VFSET& vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	GVDISP_CLOCK_VFSET vfpt;
	if(GVAPI_OK != GvGetVfClockOffset(nCard, id, &vfpt)) return false;
	vfset.nNumVFPoints = 2;
	vfset.offset[0] = vfpt.offset[0];
	vfset.offset[1] = vfpt.offset[vfpt.nNumVFPoints - 1];
	return true;
}

GVDISP_CLOCK_VFOFFSET CCfg::VFPtToOffset(GVDISP_CLOCK_VFPT vfpt)
{
	GVDISP_CLOCK_VFOFFSET offset;
	int nBaseClock = 0;
	for (int i = 0; i < m_GpuBaseVfs.nNumVFPoints; i++)
	{
		vfpt.nIndex = m_GpuBaseVfs.vfs[i].nIndex;
		nBaseClock = m_GpuBaseVfs.vfs[i].value.nClock;
		if(vfpt.value.nVoltage <= m_GpuBaseVfs.vfs[i].value.nVoltage) break;
	}
	offset.nIndex = vfpt.nIndex;
	offset.nOffset = (vfpt.value.nClock * 2 - nBaseClock) * 2;

	return offset;
}


void CCfg::SetProfileCount(int nProfileCount ,int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	m_nProfileCount[nCard]=nProfileCount;
	CIniFile config;
	CString sConfig = DecryptConfig();
	CString sProfile;
	sProfile.Format(_T("CARD_%d_ProfileCount"), nCard);
	if(_T("") == sConfig)
	{
		return;
	}
	config.SetIniFile(sConfig);
	config.SetIniInfo(m_sCardIds,sProfile,nProfileCount);
	EncryptConfig(sConfig);
}
void CCfg::SetBaseSetting(VGA_PARAM_BASESETTING& setting)
{
	CmdLock();
//	CString strDevice = _T("COMMON");
	CString sConfig = DecryptConfig();
	if(_T("") != sConfig)
	{
		Sleep(500);
		CIniFile config;
		config.SetIniFile(sConfig);

		m_baseSetting = setting;
		config.SetIniInfo(m_sCardIds, _T("BASE_SyncLed"),		setting.bSyncLed);
		config.SetIniInfo(m_sCardIds, _T("BASE_SyncMutil"),		setting.bSyncMutil);
		config.SetIniInfo(m_sCardIds, _T("BASE_AutoRun"),		setting.bAutoRun);
		config.SetIniInfo(m_sCardIds, _T("BASE_CheckUpdate"),	setting.bCheckUpdate);
		config.SetIniInfo(m_sCardIds, _T("BASE_CloseMin"),		setting.bCloseMin); 
		config.SetIniInfo(m_sCardIds, _T("BASE_Minimize"),		setting.bMinimize); 
		config.SetIniInfo(m_sCardIds, _T("BASE_LastCheck"),		setting.sLastCheckUpdate); 
// 		config.SetIniInfo(strDevice, _T("BASE_SyncLed"),		setting.bSyncLed);
// 		config.SetIniInfo(strDevice, _T("BASE_SyncMutil"),		setting.bSyncMutil);
// 		config.SetIniInfo(strDevice, _T("BASE_AutoRun"),		setting.bAutoRun);
// 		config.SetIniInfo(strDevice, _T("BASE_CheckUpdate"),	setting.bCheckUpdate);
// 		config.SetIniInfo(strDevice, _T("BASE_CloseMin"),		setting.bCloseMin); 
// 		config.SetIniInfo(strDevice, _T("BASE_Minimize"),		setting.bMinimize); 
// 		config.SetIniInfo(strDevice, _T("BASE_LastCheck"),		setting.sLastCheckUpdate); 


		CString sLastCheckUpdate;
		TCHAR szFolder[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, szFolder);
		CString sStartUp(szFolder);

		if(setting.bAutoRun)
		{
			DWORD cbData = MAX_PATH;
			CString sModule = GetModuleDirectory() + _T("autorun.exe");
			CreateFileShortcut(_T("autorun.exe"), sStartUp, _T("GRAPHICS ENGINE.lnk"), sModule, _T("/r"), 0, _T(""), SW_SHOWNORMAL);
			USES_CONVERSION;
			CString sCmd;
			sCmd.Format(_T("schtasks /CREATE /TN \"Launcher GIGABYTE AORUS GRAPHICS ENGINE\" /TR \"'%sAORUS.exe' /h\" /SC ONSTART /RL HIGHEST /F"), GetModuleDirectory());
			WinExec(T2A(sCmd), SW_HIDE); 
		}
		else
		{
			WinExec("schtasks /DELETE /TN \"Launcher GIGABYTE AORUS GRAPHICS ENGINE\" /F", SW_HIDE);  
			DeleteFile(sStartUp + _T("\\GRAPHICS ENGINE.lnk"));
		}

		EncryptConfig(sConfig);
		CmdUnLock();
	}
}
void CCfg::SetFanSetting(FAN_SETTING& setting, int nCard, int nProfile ,BOOL bSetCurFANstate)
{
	if(nCard < 0) nCard = 0;
	CString sConfig = DecryptConfig(), sProfile;
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);

		int c = nCard;

		// 是否同步所有卡設定
		//for(c = m_baseSetting.bSyncMutil ? 0 : nCard; c < (m_baseSetting.bSyncMutil ? nCard + 1 : GetGpuCount()); c++)
		//{
		m_fanSetting[nProfile][c] = setting;

		CString sCurve = _T(""), sIndex = _T("");
		sIndex.Format(_T("_%d_%d"), nProfile, nCard);
		for(int i=0; i<VGA_FANCURVE_STEPS; i++)
		{
			CString sTemp;
			sTemp.Format(_T("(%d,%d)"), setting.curve[i].nTemperature, setting.curve[i].nFanSpeed);	
			sCurve += sTemp;
		}

		config.SetIniInfo(m_sCardIds, _T("FAN_Percent") + sIndex, setting.nFanPercent);
		config.SetIniInfo(m_sCardIds, _T("FAN_FanMode") + sIndex, setting.nFanMode);
		config.SetIniInfo(m_sCardIds, _T("FAN_Stop") + sIndex, setting.bFanStop);
		if(VGA_FANMODE_AUTO != m_fanSetting[nProfile][nCard].nFanMode)	// ONLY save manual mode.
		{
			config.SetIniInfo(m_sCardIds, _T("FAN_CurveStep") + sIndex,	setting.nCurveStep);
			config.SetIniInfo(m_sCardIds, _T("FAN_FanCurve") + sIndex,	sCurve);
		}

		EncryptConfig(sConfig);
	}
	if(bSetCurFANstate)
		m_curfansetting[nCard]=setting;
}
void CCfg::SetPerformances(DWORD dwPerfs, VGA_PERFORMANCE& perf, int nProfile, int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	CIniFile config;
	CString sProfile;
	CString sConfig = DecryptConfig();
	if(_T("") == sConfig)
	{
		return;
	}
    
	sProfile.Format(_T("PRO%d_%d_"), nProfile, nCard);
	config.SetIniFile(sConfig);

	
	//sProfile.Format(_T("PRO%d_%d_"), nProfile, nCard);
	//config.SetIniFile(sConfig);

	//config.SetIniInfo(m_sCardIds, _T("ProSel"), nProfile);
	//m_curProfile[nCard] = nProfile;
	config.SetIniInfo(m_sCardIds,sProfile + _T("VolLock"), perf.bVolLock);
	if(dwPerfs & VGA_PERF_GPUCLK)	
	{
		m_performance[nProfile][nCard].nGpuClk=perf.nGpuClk;
		config.SetIniInfo(m_sCardIds, sProfile + _T("GpuClk"),	perf.nGpuClk);
	}
	if(dwPerfs & VGA_PERF_MEMCLK)	
	{
		m_performance[nProfile][nCard].nGpuClk=perf.nGpuClk;
		config.SetIniInfo(m_sCardIds, sProfile + _T("MemClk"),	perf.nMemClk);
	}
	if(dwPerfs & VGA_PERF_OVERVOL)	
	{
		m_performance[nProfile][nCard].nGpuClk=perf.nGpuClk;
		config.SetIniInfo(m_sCardIds, sProfile + _T("GpuVol"),	perf.nGpuVol);
	}
	/*if(dwPerfs & VGA_PERF_OVERVOL)	
	{
		m_performance[nProfile][nCard].nMaxVol=perf.nMaxVol;
		config.SetIniInfo(m_sCardIds, sProfile + _T("MaxVol"),	perf.nMaxVol);
	}*/
	//if(dwPerfs & VGA_PERF_MAXVOL)	config.SetIniInfo(m_sCardIds, sProfile + _T("MaxCheck"),perf.nMaxVolCheck);
	if(dwPerfs & VGA_PERF_MEMVOL)
	{
		m_performance[nProfile][nCard].nMemVol=perf.nMemVol;
		config.SetIniInfo(m_sCardIds, sProfile + _T("MemVol"),	perf.nMemVol);
	}
	if(dwPerfs & VGA_PERF_FANSPD)
	{
		m_performance[nProfile][nCard].nFanSpd=perf.nFanSpd;
		config.SetIniInfo(m_sCardIds, sProfile + _T("FanSpd"),	perf.nFanSpd);
	}
	if(dwPerfs & VGA_PERF_FANSPD)
	{
		m_performance[nProfile][nCard].nFanMode=perf.nFanMode;
		config.SetIniInfo(m_sCardIds, sProfile + _T("FanMode"),	perf.nFanMode);
	}
	if(dwPerfs & VGA_PERF_POWER)	
	{
		m_performance[nProfile][nCard].nPower=perf.nPower;
		config.SetIniInfo(m_sCardIds, sProfile + _T("Power"),	perf.nPower);
	}
	if(dwPerfs & VGA_PERF_TEMPER)
	{
		m_performance[nProfile][nCard].nTemperature=perf.nTemperature;
		config.SetIniInfo(m_sCardIds, sProfile + _T("Temp"),	perf.nTemperature);
	}
	if(dwPerfs & VGA_PERF_TEMPER) 
	{
		m_performance[nProfile][nCard].bTempPowerLink=perf.bTempPowerLink;
		config.SetIniInfo(m_sCardIds, sProfile + _T("TempGPU"), perf.bTempPowerLink);
	}
	if(dwPerfs & VGA_PERF_GCLKCUV)	
	{
		m_performance[nProfile][nCard].dwGpuClkCurve=perf.dwGpuClkCurve;
		config.SetIniInfo(m_sCardIds, sProfile + _T("GpuCv"),	perf.dwGpuClkCurve);
	}
	if(dwPerfs & VGA_PERF_MCLKCUV)	
	{
		m_performance[nProfile][nCard].dwMemClkCurve=perf.dwMemClkCurve;
		config.SetIniInfo(m_sCardIds, sProfile + _T("MemCv"),	perf.dwMemClkCurve);
	}
	if(dwPerfs & VGA_PERF_GCLKCUV  && perf.dwGpuClkCurve > 0)
	{
		CString sCurve = _T("");
		m_performance[nProfile][nCard].GpuVf.nNumVFPoints=perf.GpuVf.nNumVFPoints;
		for(int i=0; i < perf.GpuVf.nNumVFPoints; i++)
		{
			// Format as (T1,S1)(T2,S2)(T3,S3)(T4,S4).

			CString sTemp;
			m_performance[nProfile][nCard].GpuVf.offset[i].nOffset= perf.GpuVf.offset[i].nOffset;
			m_performance[nProfile][nCard].GpuVf.offset[i].nIndex= perf.GpuVf.offset[i].nIndex;
			sTemp.Format(_T("(%d,%d)"), perf.GpuVf.offset[i].nIndex, perf.GpuVf.offset[i].nOffset);	
			sCurve += sTemp;
		}
		config.SetIniInfo(m_sCardIds, sProfile + _T("GpuCurve"), sCurve);
		config.SetIniInfo(m_sCardIds, sProfile + _T("NumVFPoints"),	perf.GpuVf.nNumVFPoints);
	}
	if(dwPerfs & VGA_PERF_MCLKCUV  && perf.dwMemClkCurve > 0)
	{
		CString sCurve = _T("");
		for(int i=0; i < perf.MemVf.nNumVFPoints; i++)
		{
			// Format as (T1,S1)(T2,S2)(T3,S3)(T4,S4).

			CString sTemp;
			sTemp.Format(_T("(%d,%d)"), perf.MemVf.offset[i].nIndex, perf.MemVf.offset[i].nOffset);	
			sCurve += sTemp;
		}
		config.SetIniInfo(m_sCardIds, sProfile + _T("MemCurve"), sCurve);
	}

	EncryptConfig(sConfig);
}
void CCfg::GetMoniSetting(VGA_PARAM_MONISETTING& setting)
{
	setting = m_moniSetting;
}
 void CCfg::GetCurFanSetting(FAN_SETTING &fansetting,int nCard)
 {
	 if(nCard < 0) nCard = 0;
	 nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
     fansetting=m_curfansetting[nCard];
 }
void CCfg::SetMoniSetting(VGA_PARAM_MONISETTING setting)
{
	m_moniSetting=setting;
	CString sConfig = DecryptConfig();
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);

		m_moniSetting = setting;
		config.SetIniInfo(m_sCardIds, _T("MONI_GpuClk"),		setting.bGpuClk);
		config.SetIniInfo(m_sCardIds, _T("MONI_MemClk"),		setting.bMemClk);
		config.SetIniInfo(m_sCardIds, _T("MONI_GpuVol"),		setting.bGpuVol); 
		config.SetIniInfo(m_sCardIds, _T("MONI_MemVol"),		setting.bMemVol); 
		config.SetIniInfo(m_sCardIds, _T("MONI_FanSpd"),		setting.bFanSpd); 
		config.SetIniInfo(m_sCardIds, _T("MONI_FanRpm"),		setting.bFanRpm); 
		config.SetIniInfo(m_sCardIds, _T("MONI_Temperature"),	setting.bTemperature); 
		config.SetIniInfo(m_sCardIds, _T("MONI_Power"),			setting.bPower); 
		config.SetIniInfo(m_sCardIds, _T("MONI_GPUsage"),		setting.bGPUsage);
		config.SetIniInfo(m_sCardIds, _T("MONI_CPUsage"),		setting.bCPUsage);
		config.SetIniInfo(m_sCardIds, _T("MONI_CPUClock"),		setting.bCPUClock);
		config.SetIniInfo(m_sCardIds, _T("MONI_MemUsage"),		setting.bMemUsage);
		config.SetIniInfo(m_sCardIds, _T("MONI_PageUsage"),		setting.bPageUsage);
		config.SetIniInfo(m_sCardIds, _T("MONI_TimeInterval"),	setting.nTimeInterval);
		config.SetIniInfo(m_sCardIds, _T("MONI_LogFile"),		setting.sLogFile);
		config.SetIniInfo(m_sCardIds, _T("MONI_LogFlag"),		setting.bLogRecord);

		EncryptConfig(sConfig);
	}
}
void CCfg::SetCurFanSetting(FAN_SETTING fansetting,int nCard)
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	m_curfansetting[nCard]=fansetting;
}

int CCfg::GetProfileCount( int nCard )
{
	if(nCard < 0) nCard = 0;
	nCard = nCard % Aorus()->GetVGA()->Ctrl()->GetGpuCount();
	return m_nProfileCount[nCard];
}

void CCfg::GetTxtInputInfor(int nIndex, CString &str)
{
	CString sConfig = DecryptConfig();
	CString sProfile;
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);

		sProfile.Format(_T("AK700Key%d"), nIndex);

		config.GetIniInfo(sProfile, _T("TXT"),	str);

		EncryptConfig(sConfig);
	}
}

void CCfg::SetTxtInputInfor(int nIndex, CString str)
{
	CString sConfig = DecryptConfig(), sProfile;
	if(_T("") != sConfig)
	{
		CIniFile config;
		config.SetIniFile(sConfig);

		sProfile.Format(_T("AK700Key%d"), nIndex);

		config.SetIniInfo(sProfile, _T("TXT"),	str);

		EncryptConfig(sConfig);
	}
}