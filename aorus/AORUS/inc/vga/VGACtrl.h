#pragma once

class CVGACtrl
{
public:
	CVGACtrl(void);
	~CVGACtrl(void);

	bool Initialize(const HWND& hWnd);
	bool IsVgaCard();
	bool IsLedCard();
	bool IsNvCard();
	bool IsIXEBCard() { return m_bIXEB; } // Is external VGA card
	bool IsSwUpdate();
	bool IsNvSli();
	bool IsAorus();
	const VGA_CARD_INFO* GetCardInfo();
	int	 GetGpuCount();
	void GetPerfInfo(int nFlag, VGA_PARAM_RANGE& range);
	void GetCurrentPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perfs);
	void GetCurrentMBInfo(DWORD dwPerfs, VGA_MB_INFO& perfs);
	void GetPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perfs);
	void SetPerformances(DWORD dwPerfs, int nCard, VGA_PERFORMANCE& perfs);

	void GetPerformancesDefault(DWORD dwPerfs, VGA_PERFORMANCE& perfs);
	bool GetSpecialPerformaces(VGA_SPECIALPERFS& perf);

	void SetFanSetting(int nCard, FAN_SETTING  setting);
	void SetFanSettingDefault(int nCard);

	/****************************************************************************************
	 * 功能描述：
	 * ?時監控風扇設定，并根據設定改?轉速
	 *
	 * 输入参数：
	 * [in]  settings 所有顯卡的風扇設定
	 * 
	 * 返回值：
	 * void
	 ****************************************************************************************/
	void FanSpeedMintoring(FAN_SETTING settings[], int nCurTemperature[]);
	void GetFanAutoSetting(FAN_SETTING& setting);
	void GetFanSilentSetting(FAN_SETTING& silent);
	void SetLedSetting(int nCard, LED_SETTING  setting, bool bSave = false);
	void LedMintoring(int nCard, LED_SETTING setting);
	void LedMintoringSync(LED_SETTING setting);
	// 設置所有顯卡Led設定
	void SetAllLedSetting(LED_SETTING setting, bool bSave = false);
	CString LogOutToTxt(VGA_PERFORMANCE perf, VGA_MB_INFO MbInfo, DWORD dwPerfs, CString sSavePath);
	// 獲取一鍵超頻頻率
	int  GetOneStep(DWORD dwPerf = VGA_PERF_GPUCLK, DWORD dwType = VGA_MODE_GAME);
	void ContactUs();
	void ConnectToUrl();
	void ConnectToFAQ();
	void BiosUpdate();
	bool IsOneStepCard();
	void DriverUpdate();
	void SoftwareUpdate();
	void GetGpuBaseVfs(GVDISP_CLOCK_VFPTS &GpuBaseVfs);
	void GetGpuBaseSet(GVDISP_CLOCK_VFSET &GpuBaseOffset);
	int  OffsetIndexToClk(const int nIndex);
	int  OffsetIndexToVol(const int nIndex);
	int  OffsetToVFPtClk(GVDISP_CLOCK_VFOFFSET offset);
	GVDISP_CLOCK_VFOFFSET VFPtToOffset(GVDISP_CLOCK_VFPT vfpt);
	GVDISP_CLOCK_VFPT OffsetToVFPt(GVDISP_CLOCK_VFOFFSET vfpt);
	void GetCurClockCurve(PGVDISP_CLOCK_VFPTS pVF);
	bool IsSupportFanStop();	// Peter Lee 2017/4/18
	bool IsBoost3();
private:
	void TranlateClockOffset(PGVDISP_CLOCK_VFSET pVfset, int nMin, int nMax);
	void TranlateClockVF(GVDISP_CLOCK_VFSET Vfset, int& nMin, int& nMax);
	//int  OffsetToVFPtClk(GVDISP_CLOCK_VFOFFSET offset);
	//int  OffsetIndexToClk(const int nIndex);
	//int  OffsetIndexToVol(const int nIndex);
	//GVDISP_CLOCK_VFOFFSET VFPtToOffset(GVDISP_CLOCK_VFPT vfpt);
	//GVDISP_CLOCK_VFPT OffsetToVFPt(GVDISP_CLOCK_VFOFFSET vfpt);
	BOOL GetCurrentPerformance(int nPerf, int* pValue, int nCard);
	BOOL GetPerformance(int nPerf, int* pValue, int nCard);			// Get current setting value.
	BOOL SetPerformance(int nPerf, int nCard, int* pValue, int* pValue2 = NULL);			
	BOOL GetPerformanceDefault(int nPerf, int* pValue);		// Get setting value's default value.
	BOOL SetPerformanceDefault(int nPerf, int nCard = 0);
	bool GetVfClockClock(GVDISP_CLOCK_VFSET& vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard);
	bool SetVfClockClock(GVDISP_CLOCK_VFSET vfset, GVDISP_CLOCK_DOMAIN_ID id, int nCard);

	int  GetOneStepOc(DWORD dwPerf = VGA_PERF_GPUCLK);
	int  GetOneStepDefault(DWORD dwPerf = VGA_PERF_GPUCLK);
	int  GetOneStepOcBoost();
	int  GetOneStepEcoBoost();
	int  GetOneStepEOc(DWORD dwPerf = VGA_PERF_GPUCLK);

	CString LogHeader(DWORD dwPerfs, CString sSavePath);
	void StopLogOut ();

	GVDISP_CLOCK_VFPTS	m_GpuBaseVfs;
	GVDISP_CLOCK_VFSET  m_BaseOffsets;
	VGA_CARD_INFO		m_cardInfo;
	CStdioFile*			m_pLogFile;
	CString				m_sCardIds;
	CString				m_sLogPath;
	int					m_nNumOfCards;
	int					m_nNumPerfLs;
	bool				m_bLightCard;
	int					m_nOneStepIndex;
	HWND				m_hWnd;
	bool				m_bIXEB; //  External VGA or not
};
