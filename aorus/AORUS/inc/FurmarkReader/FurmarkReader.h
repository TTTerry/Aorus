#pragma once

#define SHMEM_PATH _T("scanner\\FurMark_XTREME_Edition_x32.exe")
#define SHMEM_NAME _T("FurMark_ShMem")
#define SHMEM_HEADER_SIGNATURE "[Geeks3D_GIGABYTE]"


#define SHMEM_DATA_INDEX_IS_DEMO_RUNNING 0
#define SHMEM_DATA_INDEX_CUR_ARTIFACTS 1
#define SHMEM_DATA_INDEX_TOTAL_ARTIFACTS 2

class CFurmarkReader
{
public:
	CFurmarkReader(void);
	~CFurmarkReader(void);

	bool Launcher(CString sPath, CString sParameters);
	bool IsRunning();
	bool IsDemoRunning();
	bool GetNumArtifacts(DWORD* cur, DWORD* tot);
	bool ReadSignature();
	BOOL Destroy();

private:
	CString m_sCfgFolder;
	SHELLEXECUTEINFO m_stShExecInfo;

};
