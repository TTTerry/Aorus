#include "StdAfx.h"
#include "LangX.h"


int CLangX::m_nLangCur = LANG_EN_US;

CLangX::CLangX(void)
{
	// check language type

	LCID  lcid;
	lcid = ::GetSystemDefaultLCID();
	#ifdef _DEBUG
	lcid = 2052;
	#endif // _DEBUG
	#ifdef _UI_Test
	lcid = -1;
	#endif // _DEBUG
	switch (lcid)
	{
	case 2052: // Chinese
	case 4100:	m_nLangCur = LANG_ZH_CN; break;
	case 1028: // Traditional Chinese
	case 3076:
	case 5124:	m_nLangCur = LANG_ZH_TW; break;
	default:	m_nLangCur = LANG_EN_US; break;
	}
	// Peter Lee 2017/6/18 testt english
	m_nLangCur = LANG_EN_US;
}

CLangX::~CLangX(void)
{
}

CString CLangX::Get(CArray<LANG_WORD> arrWordsUserDefined, int nKey)
{
	int nSize = (int)arrWordsUserDefined.GetSize();
	for (int mm = 0; mm < nSize; mm++)
	{
		if (arrWordsUserDefined.GetAt(mm).nKey != nKey)
			continue;
		switch(m_nLangCur)
		{
		case LANG_ZH_CN: return arrWordsUserDefined.GetAt(mm).sCn;
		case LANG_ZH_TW: return arrWordsUserDefined.GetAt(mm).sTw;
		case LANG_EN_US: return arrWordsUserDefined.GetAt(mm).sEn;
		}
	}

	ASSERT(FALSE); 
	return _T("");
}

CString CLangX::Get(LANG_WORD arrWordsUserDefined[], int nWordsCnt, int nKey)
{
	for (int mm = 0; mm < nWordsCnt; mm++)
	{
		if (arrWordsUserDefined[mm].nKey != nKey)
			continue;
		switch(m_nLangCur)
		{
		case LANG_ZH_CN: return arrWordsUserDefined[mm].sCn;
		case LANG_ZH_TW: return arrWordsUserDefined[mm].sTw;
		case LANG_EN_US: return arrWordsUserDefined[mm].sEn;
		}
	}

	ASSERT(FALSE); 
	return _T("");
}

CString CLangX::Get(int nKey)
{
	#pragma region words define

	static LANG_WORD s_Words[] = {
		// home
		LANG_WORD(LANG_AORUS_VGA, _T("显示适配器"), _T("顯示卡"), _T("VGA")),
		LANG_WORD(LANG_AORUS_IXEB, _T("电竞外接盒"), _T("電競外接盒"), _T("GAMING BOX")),
		LANG_WORD(LANG_AORUS_MOUSE, _T("鼠标"), _T("滑鼠"), _T("MOUSE")),
		LANG_WORD(LANG_AORUS_KB, _T("键盘"), _T("鍵盤"), _T("KEYBOARD")),
		LANG_WORD(LANG_AORUS_HEADSET, _T("耳机"), _T("耳機"), _T("HEADSET")),
		LANG_WORD(LANG_AORUS_CASE, _T("机壳"), _T("機殼"), _T("CASE")),
		LANG_WORD(LANG_AORUS_MOTHERBOARD, _T("主板"), _T("主機板"), _T("MOTHERBOARD")),
		LANG_WORD(LANG_AORUS_CPU_COOLER, _T("CPU散热器"), _T("CPU散熱器"), _T("CPU COOLER")),
		LANG_WORD(LANG_AORUS_MOTHRBOARD, _T("主板"), _T("主機板"), _T("MOTHERBOARD")),
		LANG_WORD(LANG_AORUS_SLI, _T("桥接器"), _T("橋接器"), _T("SLI")),
		LANG_WORD(LANG_AORUS_HOMETIP, _T("简易模式"), _T("簡易模式"), _T("HOME")),
		LANG_WORD(LANG_AORUS_MONITIP, _T("监控"), _T("監控"), _T("MONITORING")),
		LANG_WORD(LANG_AORUS_FANSTOPTIP, _T("启动/关闭风扇停转功能"), _T("啟動/關閉風扇停轉功能"), _T("FAN STOP/ACTIVE")),
		LANG_WORD(LANG_AORUS_LEDTIP, _T("LED控制"), _T("LED控制"), _T("LED CONTROL")),
		LANG_WORD(LANG_AORUS_KEYASSIGNTIP, _T("KEY ASSIGN"), _T("KEY ASSIGN"), _T("KEY ASSIGN")),
		LANG_WORD(LANG_AORUS_PROFTIP, _T("专家模式"), _T("專家模式"), _T("PROFESSIONAL MODE")),
		LANG_WORD(LANG_AORUS_ALLCARD, _T("所有显示适配器"), _T("所有顯示卡"), _T("ALL GRAPHICS CARDS")),
		LANG_WORD(LANG_AORUS_MACRO, _T("聚 集"), _T("聚 集"), _T("MACRO")),
		LANG_WORD(LANG_AORUS_POINTER, _T("POINTER"), _T("POINTER"), _T("POINTER")),
		LANG_WORD(LANG_AORUS_BUTTONS, _T("BUTTONS"), _T("BUTTONS"), _T("BUTTONS")),
		// OC
		LANG_WORD(LANG_VGAOC_GPUCLK, _T("GPU BOOST频率 \\"), _T("GPU BOOST頻率 \\"), _T("GPU BOOST CLOCK \\")),
		LANG_WORD(LANG_VGAOC_MEMCLK, _T("显存频率             \\"), _T("記憶體頻率         \\"), _T("MEMORY CLOCK     \\")),
		LANG_WORD(LANG_VGAOC_AMDCLK, _T("GPU 频率	\\"), _T("GPU 頻率	\\"), _T("GPU CLOCK		\\")),
		//VGA LED
		LANG_WORD(LANG_VGALED_LEDCAPTION, _T("LED控制"), _T("LED控制"), _T("LED CONTROL")),
		LANG_WORD(LANG_VGALED_LEDEFFECTS, _T("	效果"), _T("	效果"), _T("LED EFFECTS")),
		LANG_WORD(LANG_VGALED_STYLE, _T("	风格"), _T("	風格"), _T("STYLE")),
		LANG_WORD(LANG_VGALED_SPEED, _T("	速度"), _T("	速度"), _T("SPEED")),
		LANG_WORD(LANG_VGALED_VARIATION, _T("	监控"), _T("	監控"), _T("MONITORING")),
		LANG_WORD(LANG_VGALED_BRIGHTNESS, _T("	亮度"), _T("	亮度"), _T("BRIGHTNESS")),
		LANG_WORD(LANG_VGALED_SYNCLEDDEV, _T("同步灯光效果至其他技嘉装置"), _T("同步燈光效果至其他技嘉裝置"), _T("SYNC WITH OTHER GIGABYTE DEVICES")),
		LANG_WORD(LANG_VGALED_DEFAULT, _T("默认值"), _T("預設值"), _T("DEFAULT")),
		LANG_WORD(LANG_VGALED_APPLY, _T("套用"), _T("套用"), _T("APPLY")),
		LANG_WORD(LANG_VGALED_VGASTYLE_CONSI, _T("单色显示"), _T("單色顯示"), _T("CONSISTENT")),
		LANG_WORD(LANG_VGALED_VGASTYLE_BREATH, _T("呼吸"), _T("呼吸"), _T("BREATHING")),
		LANG_WORD(LANG_VGALED_VGASTYLE_FLASH, _T("闪烁"), _T("閃爍"), _T("FLASHING")),
		LANG_WORD(LANG_VGALED_VGASTYLE_DUALFLASH, _T("双重闪烁"), _T("雙重閃爍"), _T("DUAL FLASHING")),
		LANG_WORD(LANG_VGALED_VGASTYLE_VARIA, _T("监控"), _T("監控"), _T("MONITORING")),
		LANG_WORD(LANG_VGALED_VGASTYLE_AUDIOFLASH, _T("音讯闪烁"), _T("音訊閃爍"), _T("AUDIO FLASHING")),
		LANG_WORD(LANG_VGALED_VGASTYLE_RANDOM, _T("多色循环"), _T("多色循環"), _T("CIRCLING")),

		LANG_WORD(LANG_VGALED_VGAVARIA_STYLEBASE, _T("基础风格"), _T("基礎風格"), _T("STYLE BASE")),
		LANG_WORD(LANG_VGALED_VGAVARIA_GPUTEMP, _T("GPU 温度"), _T("GPU 溫度"), _T("GPU TEMPERATURE")),
		LANG_WORD(LANG_VGALED_VGAVARIA_GPUUTI, _T("GPU 利用率"), _T("GPU 利用率"), _T("GPU UTILIZATION")),
		LANG_WORD(LANG_VGALED_VGAVARIA_GPUCLK, _T("GPU 频率"), _T("GPU 頻率"), _T("GPU CLOCK")),
		LANG_WORD(LANG_VGALED_VGAVARIA_GPUVOL, _T("GPU 电压"), _T("GPU 電壓"), _T("GPU VOLTAGE")),
		LANG_WORD(LANG_VGALED_VGAVARIA_GPUFANSPD, _T("GPU 风扇速度"), _T("GPU 風扇轉速"), _T("GPU FANSPEED")),

		LANG_WORD(LANG_VGALED_MBSTYLE_CONS, _T("单色显示"), _T("單色顯示"), _T("CONSISTENT")),
		LANG_WORD(LANG_VGALED_MBSTYLE_BREATHING, _T("呼吸"), _T("呼吸"), _T("BREATHING")),
		LANG_WORD(LANG_VGALED_MBSTYLE_FLASHING, _T("闪烁"), _T("閃爍"), _T("FLASHING")),
		LANG_WORD(LANG_VGALED_MBSTYLE_VARIATION, _T("监控"), _T("監控"), _T("MONITORING")),
		LANG_WORD(LANG_VGALED_MBSTYLE_AUDIOFLASHING, _T("音讯闪烁"), _T("音訊閃爍"), _T("AUDIO FLASHING")),
		LANG_WORD(LANG_VGALED_MBSTYLE_WAVE, _T("波浪"), _T("波浪"), _T("WAVE")),
		LANG_WORD(LANG_VGALED_MBSTYLE_RANDOM, _T("多色循环"), _T("多色循環"), _T("CIRCLING")),

		LANG_WORD(LANG_VGALED_MBVARIA_CPUUTI, _T("CPU 利用率"), _T("CPU 利用率"), _T("CPU UTILIZATION")),
		LANG_WORD(LANG_VGALED_MVSTYLE_CPUTEMP, _T("CPU 温度"), _T("CPU 溫度"), _T("CPU TEMPERATURE")),
		LANG_WORD(LANG_VGALED_MVSTYLE_SYSTEMP, _T("SYS 温度"), _T("SYS 溫度"), _T("SYS TEMPERATURE")),
		LANG_WORD(LANG_VGALED_MVSTYLE_CPUFANSPD, _T("CPU 风扇转速"), _T("CPU 風扇轉速"), _T("CPU FANSPEED")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_CONS, _T("单色显示"), _T("單色顯示"), _T("CONSISTENT")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_BREATHING, _T("呼吸"), _T("呼吸"), _T("BREATHING")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_RANDOM, _T("多色循环"), _T("多色循環"), _T("CIRCLING")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_AUDIOFLASHING, _T("音讯闪烁"), _T("音訊閃爍"), _T("AUDIO FLASHING")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_FLASHING, _T("闪烁"), _T("閃爍"), _T("FLASHING")),
		LANG_WORD(LANG_VGALED_SYCSTYLE_GPUCPUUSG, _T("GPU/CPU 利用率"), _T("GPU/CPU 利用率"), _T("GPU/CPU UTILIZATION")),
		// vga pro
		LANG_WORD(LANG_VGAPRO_PROFILE, _T("资料文件"), _T("資料檔"), _T("PROFILES")),
		LANG_WORD(LANG_VGAPRO_APPLY, _T("套用"), _T("套用"), _T("APPLY")),
		LANG_WORD(LANG_VGAPRO_RESET, _T("重置"), _T("重置"), _T("RESET")),
		LANG_WORD(LANG_VGAPRO_DEFAULT, _T("默认值"), _T("預設值"), _T("DEFAULT")),
		LANG_WORD(LANG_VGAPRO_GPUBOOSTCLK, _T("GPU BOOST频率"), _T("GPU BOOST頻率"), _T("GPU BOOST CLOCK")),
		LANG_WORD(LANG_VGAPRO_GPUAMDCLK, _T("GPU 频率"), _T("GPU 頻率"), _T("GPU CLOCK")),
		LANG_WORD(LANG_VGAPRO_MEMCLK, _T("显存频率"), _T("記憶體頻率"), _T("MEMORY CLOCK")),
		LANG_WORD(LANG_VGAPRO_GPUVOL, _T("GPU电压"), _T("GPU電壓"), _T("GPU VOLTAGE")),
		LANG_WORD(LANG_VGAPRO_FANSPD, _T("风扇转速"), _T("風扇轉速"), _T("FAN SPEED")),
		LANG_WORD(LANG_VGAPRO_PWRTAR, _T("目标功耗"), _T("目標功耗"), _T("POWER TARGET")),
		LANG_WORD(LANG_VGAPRO_TARTEMP, _T("目标温度"), _T("目標溫度"), _T("TARGET TEMPERATURE")),
		LANG_WORD(LANG_VGAPRO_GPUCUSTOM, _T("自定义"), _T("自訂"), _T("CUSTOMIZED")),
		LANG_WORD(LANG_VGAPRO_FANAUTO, _T("自动"), _T("自動"), _T("AUTO")),
		LANG_WORD(LANG_VGAPRO_FANMANUAL, _T("手动"), _T("手動"), _T("MANUAL")),
		LANG_WORD(LANG_VGAPRO_FANCUSTOM, _T("自定义"), _T("自訂"), _T("CUSTOMIZED")),
		// CUSTOMIZED
		LANG_WORD(LANG_VGACUST_CAP, _T("自定义    "), _T("自訂"), _T("CUSTOMIZED")),
		LANG_WORD(LANG_VGACUST_CLK, _T("频率[MHz]"), _T("頻率[MHz]"), _T("CLOCK[MHz]")),
		LANG_WORD(LANG_VGACUST_VOL, _T("电压[V]"), _T("電壓[V]"), _T("VOLTAGE[V]")),
		LANG_WORD(LANG_VGACUST_FANSPD, _T("风扇转速[%]"), _T("風扇轉速[%]"), _T("FAN SPEED[%]")),
		LANG_WORD(LANG_VGACUST_FANTEMP, _T("温度[℃]"), _T("温度[℃]"), _T("TEMPERATURE[℃]")),
		LANG_WORD(LANG_VGACUST_ACTOCSCANER, _T("启动OC SCANNER"), _T("啟動OC SCANNER"), _T("ACTIVATE OC SCANNER")),
		LANG_WORD(LANG_VGACUST_STOPOCSCANER, _T("结束OC SCANNER"), _T("結束OC SCANNER"), _T("STOP OC SCANNER")),
		// MONI
		LANG_WORD(LANG_MONI_EDIT, _T("设定"), _T("設定"), _T("EDIT")),
		LANG_WORD(LANG_MONI_GPUCLK, _T("GPU 频率"), _T("GPU 頻率"), _T("GPU CLOCK")),
		LANG_WORD(LANG_MONI_MEMCLK, _T("MEM 频率"), _T("記憶體頻率"), _T("MEM CLOCK")),
		LANG_WORD(LANG_MONI_GPUVOL, _T("GPU 电压"), _T("GPU 電壓"), _T("GPU VOL")),
		LANG_WORD(LANG_MONI_MEMVOL, _T("显存电压"), _T("記憶體電壓"), _T("MEM VOL")),
		LANG_WORD(LANG_MONI_FANSPD, _T("风扇速度"), _T("風扇轉速"), _T("FAN SPEED")),
		LANG_WORD(LANG_MONI_GPUTEMP, _T("GPU 温度"), _T("GPU 温度"), _T("GPU TEMPE")),
		LANG_WORD(LANG_MONI_PWRCONS, _T("显卡用电量"), _T("顯卡用電量"), _T("PWR CONSL")),
		LANG_WORD(LANG_MONI_GPUUSG, _T("GPU 使用率"), _T("GPU 使用率"), _T("GPU USAGE")),
		LANG_WORD(LANG_MONI_CPUUSG, _T("CPU 使用率"), _T("CPU 使用率"), _T("CPU USAGE")),
		LANG_WORD(LANG_MONI_CPUCLK, _T("CPU 频率"), _T("CPU 頻率"), _T("CPU CLOCK")),
		LANG_WORD(LANG_MONI_MEMUSG, _T("内存使用率"), _T("記憶體使用率"), _T("MEM USAGE")),
		LANG_WORD(LANG_MONI_PGFILEUSG, _T("页面文件用量"), _T("頁面文件使用率"), _T("PGFILE USG")),
		//MONI EDIT
		LANG_WORD(LANG_MONIEDIT_CAPTION, _T("监控设定"), _T("監控設定"), _T("MONITORING")),
		LANG_WORD(LANG_MONIEDT_ALL, _T("全选"), _T("全選"), _T("ALL")),
		LANG_WORD(LANG_MONIEDT_PWERTAR, _T("显卡用电量"), _T("顯卡用電量"), _T("POWER TARGET")),
		LANG_WORD(LANG_MONIEDT_CPUUSG, _T("CPU 使用率"), _T("CPU 使用率"), _T("CPU USAGE")),
		LANG_WORD(LANG_MONIEDT_GPUCLK, _T("GPU 频率"), _T("GPU 頻率"), _T("GPU CLOCK")),
		LANG_WORD(LANG_MONIEDT_GPUVOL, _T("GPU 电压"), _T("GPU 電壓"), _T("GPU VOLTAGE")),
		LANG_WORD(LANG_MONIEDT_GPUUSG, _T("GPU 使用率"), _T("GPU 使用率"), _T("GPU USAGE")),
		LANG_WORD(LANG_MONIEDT_GPUTEMP, _T("GPU 温度"), _T("GPU 温度"), _T("GPU TEMPERATURE")),
		LANG_WORD(LANG_MONIEDT_GPUFANSPD_PERCENT, _T("GPU 风扇转速(%)"), _T("GPU 風扇轉速(%)"), _T("GPU FAN SPEED(%)")),
		LANG_WORD(LANG_MONIEDT_GPUFANSPD_RPM, _T("GPU 风扇转速(RPM)"), _T("GPU 風扇轉速(RPM)"), _T("GPU FAN SPEED(RPM)")),
		LANG_WORD(LANG_MONIEDT_VRAMCLK, _T("MEM 频率"), _T("記憶體頻率"), _T("MEM CLOCK")),
		LANG_WORD(LANG_MONIEDT_VRAMUSG, _T("内存使用率"), _T("記憶體使用率"), _T("MEM USAGE")),
		//MONI EDT
		LANG_WORD(LANG_MONIEDT_HAR_POLL_PER, _T("硬件存取间隔\r\n(毫秒)"), _T("硬體存取間隔\r\n(毫秒)"), _T("HARDWARE POLLING PERIOD\r\n(IN MILLISECOND)")),
		LANG_WORD(LANG_MONIEDT_INMILLISECOND, _T("(毫秒)"), _T("毫秒"), _T("(IN MILLISECOND)")),
		LANG_WORD(LANG_MONIEDT_LOGHISTORY_TO_FILE, _T("储存Log档"), _T("儲存Log檔"), _T("LOG HISTORY TO FILE")),
		LANG_WORD(LANG_MONIEDT_APPLY, _T("套用"), _T("套用"), _T("APPLY")),
		//SETTING
		LANG_WORD(LANG_SET_CAPTION, _T("设定"), _T("設定"), _T("SETTING")),
		LANG_WORD(LANG_SET_GENERAL, _T("一般设定"), _T("一般設定"), _T("GENERAL")),
		LANG_WORD(LANG_SET_VGA, _T("显卡"), _T("顯示卡"), _T("VGA")),
		LANG_WORD(LANG_SET_START_WITH_WINDOW, _T("随Windows启动"), _T("隨Windows啟動"), _T("START WITH WINDOWS")),
		LANG_WORD(LANG_SET_START_MIN, _T("启动时最小化"), _T("啟動時最小化"), _T("START MINIMIZED")),
		LANG_WORD(LANG_SET_CLOSEBTN_TO_TRAY, _T("关闭时最小化到系统列"), _T("關閉時最小化到系統列"), _T("CLOSE BUTTON MINIMIZED TO TRAY")),
		LANG_WORD(LANG_SET_AUTOCHECK_FOR_UPDATE, _T("自动检查是否有最新版本"), _T("自動檢查是否有最新版本"), _T("AUTOMATICALLY CHECK FOR UPDATES")),
		LANG_WORD(LANG_SET_CHECK_FOR_UPDATE, _T("立即检查更新"), _T("立即檢查更新"), _T("CHECK FOR UPDATE")),
		LANG_WORD(LANG_SET_LAST_CHECK_ON, _T("上次检查日期"), _T("上次檢查日期"), _T("LAST CHECKED ON")),
		LANG_WORD(LANG_SET_OK, _T("确定"), _T("確定"), _T("OK")),
		LANG_WORD(LANG_SET_CANCEL, _T("取消"), _T("取消"), _T("CANCEL")),
		//LANG_WORD(LANG_SET_BIOS_VER, _T("BIOS版本"), _T("BIOS版本"), _T("BIOS VERSION")),
		//LANG_WORD(LANG_SET_DRI_VER, _T("驱动版本"), _T("驅動版本"), _T("DRIVER VERSION")),
		LANG_WORD(LANG_SET_BIOS_VER, _T("BIOS版本"), _T("BIOS版本"), _T("BIOS VER")),	// Peter Lee 2017/5/4 short length
		LANG_WORD(LANG_SET_DRI_VER, _T("驱动版本"), _T("驅動版本"), _T("DRIVER VER")),	// Peter Lee 2017/5/4 short length
		//REMOTE CTRL SETTING
		LANG_WORD(LANG_REMOTE_CAPTION, _T("远程控制设定"), _T("遠程控制設定"), _T("REMOTE CONTROL SETTING")),
		LANG_WORD(LANG_REMOTE_NAME, _T("NAME"), _T("NAME"), _T("NAME")),
		LANG_WORD(LANG_REMOTE_PASSWORD, _T("PASSWORD"), _T("PASSWORD"), _T("PASSWORD")),
		LANG_WORD(LANG_REMOTE_APPLY, _T("套用"), _T("套用"), _T("APPLY")),
		LANG_WORD(LANG_REMOTE_CANCEL, _T("取消"), _T("取消"), _T("CANCEL")),
		LANG_WORD(LANG_FONT, _T("Aldrich"), _T("Aldrich"), _T("Aldrich")),
		LANG_WORD(LANG_CONTACT, _T("联系我们"), _T("聯係我們"), _T("Contact us")),
	};

	#pragma endregion

	try {
		ASSERT(s_Words[nKey].nKey == nKey);  // double check 
		switch(m_nLangCur)
		{
		case LANG_ZH_CN: return s_Words[nKey].sCn;
		case LANG_ZH_TW: return s_Words[nKey].sTw;
		case LANG_EN_US: return s_Words[nKey].sEn;
		}
	}
	catch (...)
	{
	}
	return _T("");
}