#pragma once
#include <pdh.h>
#pragma comment(lib,"pdh.lib")

#include "TKTime.h"

typedef struct _MEMORY_ACTIVITY {

	// %
	int iMemUsage;	// percent of memory :  51%
	// KB
	int iTotalMem;	// total of physical memory : 2029968 KB
	int iFreeMem;	// free of physical memory  : 987388 KB
	int iTotalPage;	// total of paging file	: 3884620 KB
	int iFreePage;	// free of paging file : 2799776 KB
	int iTotalVMem;	// total of virtual memory : 2097024 KB
	int iFreeVMem;	// free of virtual memory : 2084876 KB
	int iFreeExMem;	// free of extended memory : 0KB

} MEMORY_ACTIVITY, *PMEMORY_ACTIVITY;


typedef BOOL ( __stdcall * pfnGetSystemTimes)( LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime );

class CCPUInfo
{
public:
    CCPUInfo( void );
    ~CCPUInfo( void );
    
    // return :
    // % of cpu usage for this process 
    // % cpu systemUsage 
    // uptime
	double GetUsage();
	int GetTemp();
	int GetBoardTemp();
	float GetCPUClock();
	int GetUsage( int* pSystemUsage, TKTime* pUpTime );
	DWORD GetMemoryUsage(PMEMORY_ACTIVITY pInfo);

private:
	void Init();
	int GetTimeElapse(DWORD dwOldTick);

	static bool s_bInit;
	static PDH_HQUERY cpuQuery;
	static PDH_HCOUNTER cpuTotal;

	static int base_out_addr;
	static int base_in_addr;

	CRITICAL_SECTION m_lock;
	static HINSTANCE s_hKernel;
    static pfnGetSystemTimes s_pfnGetSystemTimes;

    static TKDelay s_delay;

    static TKLong s_time;

    static TKLong s_idleTime;
    static TKLong s_kernelTime;
    static TKLong s_userTime;
    static int    s_lastCpu;
    static int    s_cpu[5];

    static TKLong s_kernelTimeProcess;
    static TKLong s_userTimeProcess;
    static int    s_lastCpuProcess;
    static int    s_cpuProcess[5];

    static int    s_count;
    static int    s_index;

    static TKLong s_lastUpTime;

};