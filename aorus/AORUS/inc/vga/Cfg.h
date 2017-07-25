#pragma once
#ifndef _VGASETTING_H_
#define _VGASETTING_H_

#define LED_PROFILE_CONT	5

class CCfg
{
public:
	 CCfg();
	~CCfg();


	CString DecryptConfig();
	void EncryptConfig(CString sTempCfg);
	BOOL Initialize();
	int GetProfileSel(int nCard);
	void SetProfileSel(int nCard,int nFieleIndex);
	int GetVgaMode(int nCard);
	int SetVgaMode(int nVgaMode, int nCard);

	bool GetVfClockClock(GVDISP_CLOCK_VFSET& vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard);
	GVDISP_CLOCK_VFOFFSET VFPtToOffset(GVDISP_CLOCK_VFPT vfpt);


	void GetBaseSetting(VGA_PARAM_BASESETTING& setting);

	void GetCurVGALedProfile(LED_SETTING& led, int nCard);
	void GetLedProfiles(int nDevice, CArray<LED_SETTING>& profiles, int& nProfileCur, int nCard);
	void SetLedProfiles(int nDevice, CArray<LED_SETTING>& profiles, int  nProfileCur, int nCard);

	void GetFanSetting(FAN_SETTING& setting, int nCard, int nProfile);
	void GetPerformances(DWORD dwPerfs, VGA_PERFORMANCE& perf, int nProfile, int nCard);
	void GetLoadingInfo(CString &csName,CString &csPasswor);
	void GetProfileName(int nProfile,int nCard,CString &csName);
	void GetMoniSetting(VGA_PARAM_MONISETTING& setting);
    void GetCurFanSetting(FAN_SETTING &fansetting,int nCard);

	void SetBaseSetting(VGA_PARAM_BASESETTING& setting);

	void SetFanSetting(FAN_SETTING& setting, int nCard, int nProfile, BOOL bSetCurFANstate=true);
	void SetPerformances(DWORD dwPerfs, VGA_PERFORMANCE& perf, int nProfile, int nCard);
    void SetLoadingInfo(CString csName,CString csPasswor) ;
	void SetProfileName(int nProfile,int nCard,CString csName);
	void SetMoniSetting(VGA_PARAM_MONISETTING setting);
	void SetCurFanSetting(FAN_SETTING fansetting,int nCard);
	int GetProfileCount(int nCard);

	const VGA_PARAM_BASESETTING GetBaseSetting();
	void SetProfileCount(int nProfileCount ,int nCard);

	void GetTxtInputInfor(int nIndex, CString &str);//Terry 2017/6/26
	void SetTxtInputInfor(int nIndex, CString sPath);
private:
	VGA_PARAM_BASESETTING		m_baseSetting;
	FAN_SETTING		m_fanSetting[100][GVDISP_CARD_MAXNUM];
	FAN_SETTING        m_curfansetting[GVDISP_CARD_MAXNUM];
	// led cfg 
	LED_SETTING	m_ledMB;
	LED_SETTING	m_ledIXEB;
	LED_SETTING m_ledATC700;
	LED_SETTING m_ledAC300;
	LED_SETTING m_ledAH300;
	LED_SETTING m_ledAM300[LED_PROFILE_CONT];
	LED_SETTING m_ledAK700[LED_PROFILE_CONT];

	LED_SETTING	m_ledVGA[GVDISP_CARD_MAXNUM];

	VGA_PERFORMANCE             m_performance[100][GVDISP_CARD_MAXNUM];
    VGA_PARAM_MONISETTING		m_moniSetting;
	VGA_CARD_INFO	m_cardInfo;
	int  m_nProfileCount[GVDISP_CARD_MAXNUM];
	int  m_curProfile[GVDISP_CARD_MAXNUM];
	int  m_nVgaMode[GVDISP_CARD_MAXNUM];
	int m_curCarSel;
	int  m_nNumOfCards;
	
	BOOL m_bOcCard;
	BOOL m_bLightCard;
    BOOL m_bColorful;
	CString m_sCardIds;
	CString m_csName;
	CString m_csPassword;

	GVDISP_CLOCK_VFPTS			m_GpuBaseVfs;

	
};
#endif