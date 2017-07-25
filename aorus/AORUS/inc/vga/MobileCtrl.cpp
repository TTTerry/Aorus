#include "StdAfx.h"
#include "../../AORUS.h"
#include "MobileCtrl.h"
#include "../../AORUSDlg.h"
#include "../mainboard/MBCtrl.h"


CMobileCtrl::CMobileCtrl()
{
    m_nConenectIpCount=0;
}
CMobileCtrl::~CMobileCtrl()
{

}
void CMobileCtrl::init()
{
   AfxBeginThread(ListenThread, this);
}

UINT CMobileCtrl::ListenThread(LPVOID lpParam)
{
	CMobileCtrl* pMain = (CMobileCtrl*) lpParam;
	char szData[1024] = "";
	pMain->m_listener.Init(9999);
	while(SOCKET_OK == pMain->m_listener.Recv(szData, 1024))
	{
		if("0.0.0.0" == pMain->m_listener.GetLastRecvIP()) continue;
		pMain->GetCmd(szData, pMain->m_listener.GetLastRecvIP());
		memset(szData, 0, 1024);
	}
	pMain->m_listener.Close();
	return 0;
}
void CMobileCtrl::GetCmd(const char* szData, CString sRecvIP)
{
	CString sData(szData);
	CString sCmd = sData.Mid(0, sData.Find(':'));
	sData = sData.Mid(sData.Find(':') + 1);
	CSocketApp sock;
	if ("LIST" == sCmd)
	{
		CString sName =L"", sKey=L"",sIP = L"";
		sIP = sock.GetIP();
		Aorus()->GetCfg()->GetLoadingInfo(sName,sKey);
		sData = L"{ 'cmd' : 'list', 'data' : { 'name' : '" + sName + L"', 'ip' : '" + sIP +L"'} }";
		sData.Replace(L"'", L"\"");
	}
	else if ("VERIFY" == sCmd)
	{
		CSocketApp sock;
		CString sPasswd = L"", sName = L"", sIP = L"";
		Aorus()->GetCfg()->GetLoadingInfo(sName,sPasswd);
		sIP = sock.GetIP();
		Aorus()->GetCfg()->GetLoadingInfo(sName,sPasswd);
		if (sPasswd==sData)
		{
			if(m_nConenectIpCount<10)
			{
				csIp[m_nConenectIpCount]=sRecvIP;
				m_nConenectIpCount++;
			}
		}
		VGA_PERFORMANCE perf;
		FAN_SETTING fansetting;
		VGA_PARAM_BASESETTING basesetting;
		VGA_SPECIALPERFS spcPerf;
		VGA_CARD_INFO const *cardinfo;
		Aorus()->GetCfg()->GetBaseSetting(basesetting);
		Aorus()->GetVGA()->Ctrl()->GetSpecialPerformaces(spcPerf);
		Aorus()->GetCfg()->GetPerformances(VGA_PERF_ALL,perf,Aorus()->GetVGAProfileSel(),Aorus()->GetVGASel());
		Aorus()->GetCfg()->GetFanSetting(fansetting,Aorus()->GetVGASel(),Aorus()->GetVGAProfileSel());
		cardinfo=Aorus()->GetVGA()->Ctrl()->GetCardInfo();
		CString csInsert = sPasswd == sData ? L"true" : L"false";
		sData =L"{\"cmd\":\"verify\",\"data\":{\"result\":";
		sData=sData+csInsert+L",\"name\":\""+sName+L"\",\"ip\":\""+sIP+L"\",\"setting\":{\"mode\":";
		if (perf.nGpuClk==Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_OC)) csInsert=L"0";
		else if(perf.nGpuClk==Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_GAME)) csInsert=L"1";
		else if(perf.nGpuClk==Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_ECO)) csInsert=L"2";
		else csInsert=L"3";
		sData=sData+csInsert+L",\"gclk\":";
		csInsert.Format(L"%d",perf.nGpuClk+spcPerf.nGpuBaseClk);
		sData=sData+csInsert+L",\"mclk\":";
		csInsert.Format(L"%d",perf.nMemClk+spcPerf.nMemBaseClk);
		sData=sData+csInsert+L",\"fanstop\":";
		csInsert=fansetting.bFanStop? L"true":L"false";
		sData=+sData+csInsert+L",\"modelname\":\""+cardinfo->sModelName+L"\",\"gpuCount\":";
		csInsert.Format(L"%d",Aorus()->GetVGA()->Ctrl()->GetGpuCount());
		sData=sData+csInsert+L",\"mb\":true,\"led\":{";
		int nGpuCount=Aorus()->GetVGA()->Ctrl()->GetGpuCount(),i=0;
		while(nGpuCount!=i)
		{
			csInsert.Format(L"\"v%d\":{\"on\":",i);
			LED_SETTING ledsetting;
			Aorus()->GetCfg()->GetCurVGALedProfile(ledsetting, i);
			sData = sData + csInsert;
			csInsert=ledsetting.bOn? L"true":L"false";
			sData=sData+csInsert+L",\"random\":";
			csInsert=ledsetting.bMutilColor? L"true":L"false";
			sData=sData+csInsert+L",\"\slitype\":";
			csInsert=ledsetting.nType==SLI_TYPE_GA? L"0":L"1";
			sData=sData+csInsert+L",\"minRange\":";
			csInsert.Format(L"%d,\"maxRange\":%d,\"speed\":%d,\"style\":%d,\"variation\":%d,\"clr\":\"#%x\"},",
				ledsetting.nRangeMin,ledsetting.nRangeMax,ledsetting.nSpeed,ledsetting.dwStyle,ledsetting.dwVariation,ledsetting.clrLed);
			sData=sData+csInsert;
			i++;
		}
		LED_SETTING ledsetting;
		Aorus()->GetCfg()->GetCurVGALedProfile(ledsetting, nGpuCount);
		sData=sData+L"\"mb\":{\"on\":";
		csInsert=ledsetting.bOn? L"true":L"false";
		sData=sData+csInsert+L",\"random\":";
		csInsert=ledsetting.bMutilColor? L"true":L"false";
		sData=sData+csInsert+L",\"\slitype\":";
		csInsert=ledsetting.nType==SLI_TYPE_GA? L"0":L"1";
		sData=sData+csInsert+L",\"minRange\":";
		csInsert.Format(L"%d,\"maxRange\":%d,\"speed\":%d,\"style\":%d,\"variation\":%d,\"clr\":\"#%x\"}},\"syncled\":",
			ledsetting.nRangeMin,ledsetting.nRangeMax,ledsetting.nSpeed,ledsetting.dwStyle,ledsetting.dwVariation,ledsetting.clrLed);
		sData=sData+csInsert;
		csInsert=basesetting.bSyncLed? L"true":L"false";
		sData=sData+csInsert+L"}}}";	
	}
	else if ("MODE" == sCmd)
	{
		CString csCard=sData.Mid(1,sData.Find('|'));
		int cardsel=_wtoi(csCard);
		int pos=sData.Find('|'); 
		sData = sData.Mid(pos + 1);
		VGA_PERFORMANCE perf;
		if("0"==sData)
		{
			perf.nGpuClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_OC);
			perf.nMemClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_OC);
		}
		else if("1"==sData)
		{
			perf.nGpuClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_GAME);
			perf.nMemClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_GAME);
		}
		else if ("2"==sData)
		{
			perf.nGpuClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_GPUCLK,VGA_MODE_ECO);
			perf.nMemClk=Aorus()->GetVGA()->Ctrl()->GetOneStep(VGA_PERF_MEMCLK,VGA_MODE_ECO);
		}
		Aorus()->GetVGA()->Ctrl()->SetPerformances(VGA_PERF_GPUCLK|VGA_PERF_MEMCLK,cardsel,perf);
		Aorus()->MobileUpdateUI(0);
		sData.Format(L"{ \"cmd\" : \"mode\", \"data\" : { \"gclk\" : %d, \"mclk\" : %d } }",perf.nGpuClk,perf.nMemClk);

	}
	else if("FANSTOP"==sCmd)
	{
		CString csCard=sData.Mid(1,sData.Find('|'));
		int cardsel=_wtoi(csCard);
		int pos=sData.Find('|'); 
		sData = sData.Mid(pos + 1,pos+2);
		FAN_SETTING fansetting;
		Aorus()->GetCfg()->GetFanSetting(fansetting,cardsel,Aorus()->GetVGAProfileSel());
		fansetting.bFanStop=_wtoi(sData)==1? TRUE :FALSE;
		Aorus()->GetVGA()->Ctrl()->SetFanSetting(cardsel,fansetting);
		Aorus()->GetCfg()->SetFanSetting(fansetting,cardsel,Aorus()->GetVGAProfileSel());
		CString csBstop=fansetting.bFanStop==1? _T("true"):_T("false");
		sData.Format(L"{ \"cmd\" : \"fanStop\", \"data\" : { \"card\" : \"V%d\", \"v\" :",cardsel);
		sData=sData+csBstop+_T("}}");

	}
	else if("LED-ON"==sCmd||"LED-RAND"==sCmd||"LED-SLI"==sCmd||"LED-MINR"==sCmd||"LED-MAXR"==sCmd||"LED-SPEED"==sCmd||"LED-VAR"==sCmd||"LED-STYLE"==sCmd||"LED-CLR"==sCmd)
	{
		CString csCard=sData.Mid(1,sData.Find('|'));
		int cardsel;
		if (csCard==L"b|")
		{
			cardsel=Aorus()->GetVGA()->Ctrl()->GetGpuCount();
		}
		else{
			cardsel=_wtoi(csCard);
		}
		
		sData = sData.Mid(sData.Find('|')+1);

		LED_SETTING ledsetting;
		Aorus()->GetCfg()->GetCurVGALedProfile(ledsetting, cardsel);
		if ("LED-ON"==sCmd)    
		{
			ledsetting.bOn=_wtoi(sData)==1? TRUE :FALSE;
			CString csledon=ledsetting.bOn==true? _T("true"):_T("false");
			sData.Format(L"{ \"cmd\" : \"led-on\", \"data\" : { \"card\" : \"V%d\", \"v\" :",cardsel);
			sData=sData+csledon+_T("}}");
		}
		else if ("LED-RAND"==sCmd)  
		{
			ledsetting.bMutilColor=_wtoi(sData)==1? TRUE :FALSE;
			CString csledrand=ledsetting.bMutilColor==true? _T("true"):_T("false");
			sData.Format(L"{ \"cmd\" : \"led-on\", \"data\" : { \"card\" : \"V%d\", \"v\" :",cardsel);
			sData=sData+csledrand+_T("}}");
		}
		else if ("LED-SLI"==sCmd) 
		{
			ledsetting.nType=_wtoi(sData)==1? SLI_TYPE_GA:SLI_TYPE_NV;
			sData.Format(L"{ \"cmd\" : \"led-sli\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.nType==SLI_TYPE_GA? 1:0);
		}
		else if ("LED-MINR"==sCmd) 
		{
			ledsetting.nRangeMin=_wtoi(sData);
			sData.Format(L"{ \"cmd\" : \"led-minR\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.nRangeMin);
		}
		else if ("LED-MAXR"==sCmd)
		{
			ledsetting.nRangeMax=_wtoi(sData);
			sData.Format(L"{ \"cmd\" : \"led-maxR\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.nRangeMax);
		}
		else if("LED-SPEED"==sCmd) 
		{
			ledsetting.nSpeed=_wtoi(sData);
			sData.Format(L"{ \"cmd\" : \"led-speed\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.nSpeed);
		}
		else if("LED-STYLE"==sCmd)  
		{
			ledsetting.dwStyle=_wtoi(sData);
			sData.Format(L"{ \"cmd\" : \"led-style\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.dwStyle);
		}
		else if("LED-VAR"==sCmd)    
		{
			ledsetting.dwStyle=_wtoi(sData);
			sData.Format(L"{ \"cmd\" : \"led-var\", \"data\" : { \"card\" : \"V%d\", \"v\" : %d}}",cardsel,ledsetting.dwVariation);
		}
		else if("LED-CLR"==sCmd)  
		{
			ledsetting.clrLed=StringToColor(sData);
			sData.Format(L"{ \"cmd\" : \"led-clr\", \"data\" : { \"card\" : \"V%d\", \"v\" : \"#%x\"}}",cardsel,ledsetting.clrLed);
		}
		if (cardsel==Aorus()->GetVGA()->Ctrl()->GetGpuCount())
		{
			//g_Mbctrl.SetLedSetting(ledsetting);
		}
		else
		{
			Aorus()->GetVGA()->Ctrl()->SetLedSetting(cardsel,ledsetting);
		}
		
		CArray<LED_SETTING> profiles;
		int nProfileCur = 0;
		profiles.Add(ledsetting);
		Aorus()->GetCfg()->SetLedProfiles(DEVICE_VGA, profiles, nProfileCur, 0);

		Aorus()->MobileUpdateUI(1);
	}
	else if("LED-SYNC"==sCmd)
	{
		VGA_PARAM_BASESETTING basesetting;
		Aorus()->GetCfg()->GetBaseSetting(basesetting);
		basesetting.bSyncLed=_wtoi(sData)==1? TRUE:FALSE;
		Aorus()->GetCfg()->SetBaseSetting(basesetting);

		CString cssync=basesetting.bSyncLed==true? _T("true"):_T("false");
		sData.Format(L"{ \"cmd\" : \"led-sync\", \"data\"  :{\"v\" :");
		sData=sData+cssync+_T("}}");
	}
	char cSendData[1024];
	memset(cSendData,'\0',1024);
	WideCharToMultiByte(CP_ACP,0,sData,sData.GetLength(),cSendData,1024,NULL,NULL);
	sock.Init(6000, sRecvIP);
	sock.Send(cSendData,strlen(cSendData)+1);
	sock.Close();  

}
void CMobileCtrl::syncLedState()
{
	/*CString sRecvIP=m_listener.GetLastRecvIP();

    CSocketApp sock;
	sock.Init(6000, sRecvIP);*/
    CString sData,csInsert;
	LED_SETTING ledsetting;
	Aorus()->GetCfg()->GetCurVGALedProfile(ledsetting, Aorus()->GetVGASel());

	sData=L"\"cmd\":\"led-sync\",\"data\":{";
	csInsert.Format(L"\"card%d\":{\"on\":",Aorus()->GetVGASel());
	sData=sData+csInsert;
	csInsert=ledsetting.bOn? L"true":L"false";
	sData=sData+csInsert+L",\"random\":";
	csInsert=ledsetting.bMutilColor? L"true":L"false";
	sData=sData+csInsert+L",\"\slitype\":";
	csInsert=ledsetting.nType==SLI_TYPE_GA? L"0":L"1";
	sData=sData+csInsert+L",\"minRange\":";
	csInsert.Format(L"%d,\"maxRange\":%d,\"speed\":%d,\"style\":%d,\"variation\":%d,\"clr\":\"#%x\"},",
		ledsetting.nRangeMin,ledsetting.nRangeMax,ledsetting.nSpeed,ledsetting.dwStyle,ledsetting.dwVariation,ledsetting.clrLed);
	sData=sData+csInsert;

	char cSendData[1024];
	memset(cSendData,'\0',1024);
	WideCharToMultiByte(CP_ACP,0,sData,sData.GetLength(),cSendData,1024,NULL,NULL);
	for (int i=0;i<m_nConenectIpCount;i++)
	{
		CSocketApp sock;
		sock.Init(6000, csIp[i]);
		sock.Send(cSendData,strlen(cSendData));
		sock.Close();  
	}
}
void CMobileCtrl::monitor()
{

	//CString sRecvIP=m_listener.GetLastRecvIP();

	CString sData,csInsert;
	VGA_PERFORMANCE perf;
	Aorus()->GetVGA()->Ctrl()->GetCurrentPerformances(VGA_PERF_ALL,Aorus()->GetVGASel(), perf);

	sData.Format(L"{\"cmd\":\"monitor\",\"data\":{\
		\"gclk\":%d,\
		\"mclk\":%d,\
		\"gvol\":%d,\
		\"fanper\":%d,\
		\"fanrpm\":%d,\
		\"power\":%d,\
		\"temp\":%d,\
		\"gusage\":%d,\
		\"cusage\":%d,\
		\"musage\":%d\,\
		\"pusage\":%d\
		}}",perf.nGpuClk,perf.nMemClk,perf.nGpuVol/1000.0,perf.nFanSpd,perf.nFanSpd,perf.nPower
		,perf.nTemperature,perf.nGPUsage,20,10,20);

	char cSendData[1024];
	memset(cSendData,'\0',1024);
	WideCharToMultiByte(CP_ACP,0,sData,sData.GetLength(),cSendData,1024,NULL,NULL);
	for (int i=0;i<m_nConenectIpCount;i++)
	{
		CSocketApp sock;
		sock.Init(6000, csIp[i]);
		sock.Send(cSendData,strlen(cSendData));
		sock.Close();  
	}

	    
}