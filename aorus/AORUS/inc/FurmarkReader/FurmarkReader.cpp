#include "StdAfx.h"
#include "FurmarkReader.h"


#pragma pack(push, 1)
struct FURMARK_SHMEM
{
	char signature[32]; // 32 bytes
	DWORD data[8]; // 32 bytes
};
#pragma pack(pop)


CFurmarkReader::CFurmarkReader(void)
{
	m_sCfgFolder = Gv::OS::GetCurDirectory();
	m_stShExecInfo.hProcess=NULL;
}

CFurmarkReader::~CFurmarkReader(void)
{
}

bool CFurmarkReader::IsRunning()
{
	bool ret = false;
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHMEM_NAME);
	if (hMapFile)
	{
		ret = true;
		CloseHandle(hMapFile);
	}
	return ret;
}

bool CFurmarkReader::IsDemoRunning()
{
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHMEM_NAME);
	if (!hMapFile)
	{
		return false;
	}

	FURMARK_SHMEM *p = (FURMARK_SHMEM*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	if (!p) 
	{
		CloseHandle(hMapFile);
		return false;
	}

	FURMARK_SHMEM shmem;
	memcpy(&shmem, p, sizeof(FURMARK_SHMEM));

	bool ret = shmem.data[SHMEM_DATA_INDEX_IS_DEMO_RUNNING] ? true: false;

	UnmapViewOfFile(p);
	CloseHandle(hMapFile);
	return ret;
}

bool CFurmarkReader::GetNumArtifacts(DWORD* cur, DWORD* tot)
{
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHMEM_NAME);
	if (!hMapFile)
	{
		return false;
	}

	FURMARK_SHMEM *p = (FURMARK_SHMEM*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	if (!p)
	{
		CloseHandle(hMapFile);
		return false;
	}

	FURMARK_SHMEM shmem;
	memcpy(&shmem, p, sizeof(FURMARK_SHMEM));
	UnmapViewOfFile(p);
	CloseHandle(hMapFile);

	*cur = shmem.data[SHMEM_DATA_INDEX_CUR_ARTIFACTS];
	*tot = shmem.data[SHMEM_DATA_INDEX_TOTAL_ARTIFACTS];

	return true;
}

bool CFurmarkReader::ReadSignature()
{
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHMEM_NAME);
	if (!hMapFile)
		return false;

	FURMARK_SHMEM *p = (FURMARK_SHMEM*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	if (!p) 
	{
		CloseHandle(hMapFile);
		return false;
	}

	FURMARK_SHMEM shmem;
	memcpy(&shmem, p, sizeof(FURMARK_SHMEM));

	UnmapViewOfFile(p);
	CloseHandle(hMapFile);

	printf("\nConnected to shared memory block: %s", shmem.signature);
	return true;
}

bool CFurmarkReader::Launcher(CString sPath, CString sParameters)
{
	//CString sPath = m_sCfgFolder + SHMEM_PATH;
	//CString sParameters = _T(" -nogui -width=1024 -height=768 -furmark -scan");
	CString sNewDirectory = sPath.Left(sPath.ReverseFind(_T('\\')) + 1);
	SetCurrentDirectory(sNewDirectory);

	m_stShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	m_stShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	m_stShExecInfo.hwnd = NULL;
	m_stShExecInfo.lpVerb = _T("");
	m_stShExecInfo.lpFile = (LPTSTR)(LPCTSTR)sPath; 
	m_stShExecInfo.lpParameters = sParameters; 
	m_stShExecInfo.lpDirectory = NULL;
	m_stShExecInfo.nShow = SW_SHOW;
	m_stShExecInfo.hInstApp = NULL; 

	ShellExecuteEx(&m_stShExecInfo);

	if(NULL == m_stShExecInfo.hProcess)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CFurmarkReader::Destroy()
{
	if(NULL != m_stShExecInfo.hProcess)
	{
		DWORD dwReturn = WaitForSingleObject(m_stShExecInfo.hProcess, 0); // test the object's state and returns immediately.
		switch(dwReturn)
		{
		case WAIT_OBJECT_0:
			CloseHandle(m_stShExecInfo.hProcess);
			m_stShExecInfo.hProcess = NULL;
			return TRUE;

		case WAIT_TIMEOUT:
			TerminateProcess(m_stShExecInfo.hProcess, 2);
			CloseHandle(m_stShExecInfo.hProcess);
			m_stShExecInfo.hProcess = NULL;
			return TRUE;

		case WAIT_FAILED: // error occur.
			CloseHandle(m_stShExecInfo.hProcess);
			m_stShExecInfo.hProcess = NULL;
			return FALSE;
		}
	}

	return TRUE;
}