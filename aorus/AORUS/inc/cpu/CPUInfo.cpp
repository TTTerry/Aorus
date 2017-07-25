#include "StdAfx.h"
#include "CPUInfo.h"
#include "SmartLock.h"
#include "TVicLib.h"
#pragma comment(lib, "inc/cpu/TVicLib.lib")

TKLong  CCPUInfo::s_time;
TKDelay CCPUInfo::s_delay;

int    CCPUInfo::s_count = 0;
int    CCPUInfo::s_index = 0;

TKLong CCPUInfo::s_idleTime;
TKLong CCPUInfo::s_kernelTime;
TKLong CCPUInfo::s_userTime;
int    CCPUInfo::s_lastCpu = 0;
int    CCPUInfo::s_cpu[];

TKLong CCPUInfo::s_kernelTimeProcess;
TKLong CCPUInfo::s_userTimeProcess;
int    CCPUInfo::s_lastCpuProcess;
int    CCPUInfo::s_cpuProcess[];

TKLong CCPUInfo::s_lastUpTime = 0;

bool CCPUInfo::s_bInit = false;
PDH_HQUERY CCPUInfo::cpuQuery;
PDH_HCOUNTER CCPUInfo::cpuTotal;

int CCPUInfo::base_out_addr;
int CCPUInfo::base_in_addr;

typedef LPSTR ( *PGBCPUFUNC ) (DWORD, DWORD, LPSTR, LPVOID);

HINSTANCE CCPUInfo::s_hKernel = NULL;

pfnGetSystemTimes CCPUInfo::s_pfnGetSystemTimes = NULL;

CCPUInfo::CCPUInfo()
{
	::InitializeCriticalSection( &m_lock );
	if( s_hKernel == NULL )
	{   
		s_hKernel = LoadLibrary( _T("Kernel32.dll") );
		if( s_hKernel != NULL )
		{
			s_pfnGetSystemTimes = (pfnGetSystemTimes)GetProcAddress( s_hKernel, "GetSystemTimes" );
			if( s_pfnGetSystemTimes == NULL )
			{
				FreeLibrary( s_hKernel ); s_hKernel = NULL;
			}
		}
	}
	s_delay.Mark();

	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, _T("\\Processor(_Total)\\% Processor Time"), NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);


	s_bInit = true;

}

CCPUInfo::~CCPUInfo()
{
    if( s_hKernel == NULL )
    {
        FreeLibrary( s_hKernel ); s_hKernel = NULL;
    }

    ::DeleteCriticalSection( &m_lock );
	//CloseTVicHW();
}

DWORD CCPUInfo::GetMemoryUsage(PMEMORY_ACTIVITY pInfo)
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof (statex);

	if(!GlobalMemoryStatusEx (&statex))
		return 1;

	pInfo->iMemUsage  = (int)statex.dwMemoryLoad;
	pInfo->iTotalMem  = (int)statex.ullTotalPhys / 1024;
	pInfo->iFreeMem   = (int)statex.ullAvailPhys / 1024;
	pInfo->iTotalPage = (int)statex.ullTotalPageFile / 1024;
	pInfo->iFreePage  = (int)statex.ullAvailPageFile / 1024;
	pInfo->iTotalVMem = (int)statex.ullTotalVirtual / 1024;
	pInfo->iFreeVMem  = (int)statex.ullAvailVirtual / 1024;
	pInfo->iFreeExMem = (int)statex.ullAvailExtendedVirtual / 1024;

	return 0;

}

int CCPUInfo::GetTemp()
{
	return 0;
}

int CCPUInfo::GetBoardTemp()
{
	return 0;
}

float CCPUInfo::GetCPUClock()
{
	float fClock;
	char *pInfo;
	HINSTANCE hDLL;
	hDLL = LoadLibrary(_T("MFCCPU"));
	fClock = 0;

	if(hDLL == NULL)
	{
		//::MessageBox(NULL,"Load ycc fail!!", "GetCPUInfo", MB_OK | MB_ICONSTOP);
		return 1;
	}

	PGBCPUFUNC pGBCPUFunc = (PGBCPUFUNC)GetProcAddress(hDLL, "GBFunc");

	if(pGBCPUFunc == NULL)
	{
		//::MessageBox(NULL,"Get funtion fail !!","GetCPUInfo",MB_OK | MB_ICONSTOP);
		FreeLibrary(hDLL);
		return 1;
	}

	int len=0;
	float freq=0;
	char temp[10];
	char csb[255];
	char* cpustr = NULL;

	if(!cpustr)
	{
		strcpy(csb, (LPSTR)pGBCPUFunc(0xFFFFFFFF, 0, "0", 0));
		cpustr = (char *)malloc(strlen(csb));
		strcpy(cpustr,csb);
	}
	pInfo = (LPSTR)pGBCPUFunc(0,0,cpustr,0);            //Initial

	pInfo = (LPSTR)pGBCPUFunc(25,0,cpustr,0);          //CPU
	len = strlen(pInfo);
	memcpy(temp,pInfo,len);
	freq = (float)atof(temp);
	fClock = freq;

	FreeLibrary(hDLL);

	return fClock;
}

int CCPUInfo::GetUsage( int* pSystemUsage, TKTime* pUpTime )
{
    TKLong sTime;
    int sLastCpu;
    int sLastCpuProcess;
    TKTime sLastUpTime;

    // lock
    { 
        SmartLock lock( &m_lock );

        sTime           = s_time;
        sLastCpu        = s_lastCpu;
        sLastCpuProcess = s_lastCpuProcess;
        sLastUpTime     = s_lastUpTime;
    }

    if( s_delay.MSec() <= 200 )
    {
        if( pSystemUsage != NULL )
            *pSystemUsage = sLastCpu;

        if( pUpTime != NULL )
            *pUpTime = sLastUpTime;

        return sLastCpuProcess;
    }

    TKLong time;
    
    TKLong idleTime;
    TKLong kernelTime;
    TKLong userTime;
    TKLong kernelTimeProcess;
    TKLong userTimeProcess;

    GetSystemTimeAsFileTime( (LPFILETIME)&time );

    if( sTime == 0 )
    {
        // for the system
        if( s_pfnGetSystemTimes != NULL )
        {
            /*BOOL res = */s_pfnGetSystemTimes( (LPFILETIME)&idleTime, (LPFILETIME)&kernelTime, (LPFILETIME)&userTime );
        }
        else
        {
            idleTime    = 0;
            kernelTime  = 0;
            userTime    = 0;
        }

        // for this process
        {
            FILETIME createTime;
            FILETIME exitTime;
            GetProcessTimes( GetCurrentProcess(), &createTime, &exitTime, 
                             (LPFILETIME)&kernelTimeProcess, 
                             (LPFILETIME)&userTimeProcess );
        }

        // LOCK
        {
            SmartLock lock( &m_lock );

            s_time              = time;
            
            s_idleTime          = idleTime;
            s_kernelTime        = kernelTime;
            s_userTime          = userTime;

            s_kernelTimeProcess = kernelTimeProcess;
            s_userTimeProcess   = userTimeProcess;

            s_lastCpu           = 0;
            s_lastCpuProcess    = 0;

            s_lastUpTime        = kernelTime + userTime;

            sLastCpu        = s_lastCpu;
            sLastCpuProcess = s_lastCpuProcess;
            sLastUpTime     = s_lastUpTime;
        }

        if( pSystemUsage != NULL )
            *pSystemUsage = sLastCpu;

        if( pUpTime != NULL )
            *pUpTime = sLastUpTime;

        s_delay.Mark();
        return sLastCpuProcess;
    }
    /////////////////////////////////////////////////////
    // sTime != 0

    TKLong div = ( time - sTime );
        
    // for the system
    if( s_pfnGetSystemTimes != NULL )
    {
        /*BOOL res = */s_pfnGetSystemTimes( (LPFILETIME)&idleTime, (LPFILETIME)&kernelTime, (LPFILETIME)&userTime );
    }
    else
    {
        idleTime    = 0;
        kernelTime  = 0;
        userTime    = 0;
    }

    // for this process
    {
        FILETIME createTime;
        FILETIME exitTime;
        GetProcessTimes( GetCurrentProcess(), &createTime, &exitTime, 
                         (LPFILETIME)&kernelTimeProcess, 
                         (LPFILETIME)&userTimeProcess );
    }

    int cpu;
    int cpuProcess;
    // LOCK
    {
        SmartLock lock( &m_lock );

        TKLong usr = userTime   - s_userTime;
        TKLong ker = kernelTime - s_kernelTime;
        TKLong idl = idleTime   - s_idleTime;

        TKLong sys = (usr + ker);

        if( sys == 0 )
            cpu = 0;
        else
            cpu = int( (sys - idl) *100 / sys ); // System Idle take 100 % of cpu :-((
        
        cpuProcess = int( ( ( ( userTimeProcess - s_userTimeProcess ) + ( kernelTimeProcess - s_kernelTimeProcess ) ) *100 ) / div );
        
        s_time              = time;

        s_idleTime          = idleTime;
        s_kernelTime        = kernelTime;
        s_userTime          = userTime;

        s_kernelTimeProcess = kernelTimeProcess;
        s_userTimeProcess   = userTimeProcess;
        
        s_cpu[(s_index++) %5] = cpu;
        s_cpuProcess[(s_index++) %5] = cpuProcess;
        s_count ++;
        if( s_count > 5 ) 
            s_count = 5;
        
        int i;
        cpu = 0;
        for( i = 0; i < s_count; i++ )
            cpu += s_cpu[i];
        
        cpuProcess = 0;
        for( i = 0; i < s_count; i++ )
            cpuProcess += s_cpuProcess[i];

        cpu         /= s_count;
        cpuProcess  /= s_count;
        
        s_lastCpu        = cpu;
        s_lastCpuProcess = cpuProcess;

        s_lastUpTime     = kernelTime + userTime;

        sLastCpu        = s_lastCpu;
        sLastCpuProcess = s_lastCpuProcess;
        sLastUpTime     = s_lastUpTime;
    }

    if( pSystemUsage != NULL )
        *pSystemUsage = sLastCpu;

    if( pUpTime != NULL )
        *pUpTime = sLastUpTime;

    s_delay.Mark();
    return sLastCpuProcess;
}

double CCPUInfo::GetUsage()
{
	static double fUsage = 0;
	static DWORD dwOldTick = ::GetTickCount();

	if(GetTimeElapse(dwOldTick) < 2000) return fUsage;
	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	fUsage = counterVal.doubleValue;
	dwOldTick = ::GetTickCount();
	return fUsage;
}

int CCPUInfo::GetTimeElapse(DWORD dwOldTick)
{
	return (::GetTickCount() - dwOldTick);
}
