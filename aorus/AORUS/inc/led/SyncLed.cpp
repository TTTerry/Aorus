#include "StdAfx.h"
#include "SyncLed.h"



SYNCLED_CONFIG::_SYNCLED_CONFIG()
{
	nType = TYPE_CYCLING;
	nBright = 80;
	nSpeed = 8;
	nClrCount = 7;
	nSecond = 0;
	for (int i = 0; i < CLR_MAX_COUNT; i++)
	{
		if (i < CLR_DEFINE_COUNT)
		{
			clrArray[i] = s_clr[i];
		}
		else
		{
			clrArray[i] = RGB(0, 0, 0);
		}
	}
}

SYNCLED_CONFIG& SYNCLED_CONFIG::operator = (const SYNCLED_CONFIG& config)
{
	nType = config.nType;
	nBright = config.nBright;
	nSpeed = config.nSpeed;
	nClrCount = config.nClrCount;
	nSecond = config.nSecond;
	for (int i = 0; i < CLR_MAX_COUNT; i++)
	{
		clrArray[i] = config.clrArray[i];
	}

	return *this;
}

CString SYNCLED_CONFIG::GetClrString()
{
	CString sClr;
	for(int i = 0; i < nClrCount; i++)
	{	
		sClr += RGBToHex(clrArray[i]) + _T(",");
	}
	sClr.Mid(0, sClr.GetLength() - 1);
	return sClr;
}

void SYNCLED_CONFIG::SetClrString(CString sClr)
{
	for(int i = 0; i < nClrCount; i++)
	{	
		CString temp = _T("");
		AfxExtractSubString(temp, sClr, i);
		clrArray[i] = HexToRGB(temp);
		nClrCount = i + 1;
	}
}

SHELLEXECUTEINFO CSyncLed::m_st;

CSyncLed::CSyncLed(void)
{
	CreateDir(GetModuleDirectory() + _T("GvTemp"));
}

CSyncLed::~CSyncLed(void)
{
}

void CSyncLed::Begin()
{
	HWND hWnd = ::FindWindow(NULL, _T("GvLedService"));
	if (NULL != hWnd)
		return;

	CString sPath = GetModuleDirectory() + _T("Led\\GvLedService.exe");
	CString sNewDirectory = sPath.Left(sPath.ReverseFind(_T('\\')) + 1);
	SetCurrentDirectory(sNewDirectory);

	memset(&m_st, 0, sizeof(m_st));

	m_st.cbSize = sizeof(SHELLEXECUTEINFO);
	m_st.fMask = SEE_MASK_NOCLOSEPROCESS;
	m_st.hwnd = NULL;
	m_st.lpVerb = _T("open");
	m_st.lpFile = (LPTSTR)(LPCTSTR)sPath; 
	m_st.lpParameters = _T("/h"); 
#ifdef _DEBUG
	m_st.lpParameters = _T("/h"); 
#endif // _DEBUG
	m_st.lpDirectory = NULL;
	m_st.nShow = SW_HIDE;
	m_st.hInstApp = NULL; 
	ShellExecuteEx(&m_st);
	SetCurrentDirectory(GetModuleDirectory());

	Read(s_SyncLedConfig);
	Sleep(3000);
	Set(s_SyncLedConfig);
}

void CSyncLed::End()
{
	HWND hWnd = ::FindWindow(NULL, _T("GvLedService"));
	if (NULL != hWnd)
	{
		WinExec("taskkill /im GvLedService.exe", SW_HIDE);
		memset(&m_st, 0, sizeof(m_st));
	}
}

void CSyncLed::RefreshMemory()
{
	SYNCLED_CONFIG cfg;
	cfg.nType = TYPE_MEMORY;
	Set(cfg);
	Read(s_SyncLedConfig);
}

void CSyncLed::Set(SYNCLED_CONFIG config, bool bSave)
{
	HWND hWnd = ::FindWindow(NULL, _T("GvLedService"));

	if (NULL != hWnd)
	{
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = sizeof(SYNCLED_CONFIG);
		cpd.lpData = (void*)&config;
		::SendMessage(hWnd, WM_COPYDATA, NULL,(LPARAM)&cpd);
		if(bSave) Save(config);
	}
}

bool CSyncLed::Read(SYNCLED_CONFIG& config)
{
	CString sPath = GetModuleDirectory() + _T("GvTemp\\sync.io");
	if(!PathFileExists(sPath)) return false;
	BYTE Datas[sizeof(SYNCLED_CONFIG) + 8] = {0};
	BYTE* Mem = &Datas[8];
	memset(Datas, 0xff, sizeof(SYNCLED_CONFIG) + 8);
	CFile file;
	if(!file.Open(sPath, CFile::typeBinary | CFile::modeRead))
	{
		return false;
	}

	file.Read(Datas, sizeof(SYNCLED_CONFIG) + 8);
	file.Close();

	if(strcmp((char*)Datas, "SYNCLED") != 0) return false;

	memcpy((void*)&config, Mem, sizeof(SYNCLED_CONFIG));

	return true;
}

bool CSyncLed::Save(SYNCLED_CONFIG config)
{
	if(config.nType <= 0) return true;
	CString sPath = GetModuleDirectory() + _T("GvTemp\\sync.io");
	BYTE Datas[sizeof(SYNCLED_CONFIG) + 8] = "SYNCLED";
	BYTE* Mem = &Datas[8];
	memset(Mem, 0xff, sizeof(SYNCLED_CONFIG) - 8);

	memcpy(Mem, (void*)&config, sizeof(SYNCLED_CONFIG));

	CFile file;
	if(!file.Open(sPath, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite))
	{
		return false;
	}

	file.Write(Datas, sizeof(SYNCLED_CONFIG) + 8);
	file.Close();

	return true;
}