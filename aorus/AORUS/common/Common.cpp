#include "stdafx.h"
#include "common.h"
#include "math.h"
#include "imagehlp.h"
#pragma comment(lib, "imagehlp.lib")


void CreateDir(CString sPath)
{
	USES_CONVERSION;
	MakeSureDirectoryPathExists(T2A(sPath));
}

DWORD GetTimeElapse(DWORD dwOldTick)
{
	return (::GetTickCount() - dwOldTick);
}

COLORREF StringToColor(CString sClr) 
{
	int nR = 0, nG = 0, nB = 0;
	_stscanf(sClr, _T("#%2X%2X%2X"), &nR, &nG, &nB);
	return RGB(nR, nG, nB);
}

CString ColorToString(COLORREF clrRGB)
{
	CString sClr;
	sClr.Format(_T("#%02X%02X%02X"), GetRValue(clrRGB), GetGValue(clrRGB), GetBValue(clrRGB));
	return sClr;
}

COLORREF HexToRGB(CString sClr) 
{
	int nR = 0, nG = 0, nB = 0;
	_stscanf(sClr, _T("%2X%2X%2X"), &nR, &nG, &nB);
	return RGB(nR, nG, nB);
}

CString RGBToHex(COLORREF clrRGB)
{
	CString sClr;
	sClr.Format(_T("%02X%02X%02X"), GetRValue(clrRGB), GetGValue(clrRGB), GetBValue(clrRGB));
	return sClr;
}

COLORREF HSBToRGB(float h, float s, float v)
{
	if(h > 360 || h < 0 || s < 0 || v < 0)
		return RGB(255, 255, 255);

	if((int)h == 360) h = 0;

	float r = 0, g = 0, b = 0;  
	int i = (int) (((int)h / 60) % 6);  
	float f = (h / 60) - i;  
	float p = v * (1 - s);  
	float q = v * (1 - f * s);  
	float t = v * (1 - (1 - f) * s);  
	switch (i) {  
	case 0:  
		r = v;  
		g = t;  
		b = p;  
		break;  
	case 1:  
		r = q;  
		g = v;  
		b = p;  
		break;  
	case 2:  
		r = p;  
		g = v;  
		b = t;  
		break;  
	case 3:  
		r = p;  
		g = q;  
		b = v;  
		break;  
	case 4:  
		r = t;  
		g = p;  
		b = v;  
		break;  
	case 5:  
		r = v;  
		g = p;  
		b = q;  
		break;  
	default:  
		break;  
	}  
	return RGB((int) (r * 255.0), (int) (g * 255.0), (int) (b * 255.0));
}

float RGBtoHSB(COLORREF clr) 
{
	int rgbR, rgbG, rgbB;

	rgbR = GetRValue(clr);
	rgbG = GetGValue(clr);
	rgbB = GetBValue(clr);

	int rgb[] = {rgbR, rgbG, rgbB};
	int max = rgbR;  
	int min = rgbR;  
	for (int i = 0; i < 3; i++)
	{
		if(max < rgb[i]) max = rgb[i];
		if(min > rgb[i]) min = rgb[i];
	}

	float hsbB = max / 255.0f;  
	float hsbS = max == 0 ? 0 : (max - min) / (float) max;  

	float hsbH = 0;  
	if (max == rgbR && rgbG >= rgbB) {  
		hsbH = (float)((rgbG - rgbB) * 60.0 / (max - min) + 0);  
	} else if (max == rgbR && rgbG < rgbB) {  
		hsbH = (float)((rgbG - rgbB) * 60.0 / (max - min) + 360);  
	} else if (max == rgbG) {  
		hsbH = (float)((rgbB - rgbR) * 60.0 / (max - min) + 120);  
	} else if (max == rgbB) {  
		hsbH = (float)((rgbR - rgbG) * 60.0 / (max - min) + 240);  
	}  

	return hsbH;  
}  
HANDLE InstallFont(DWORD dwFontID)
{
	HINSTANCE hInstRes = NULL;// or the dll/exe that contains the font resource;
	HRSRC hRsrc = FindResource(hInstRes, MAKEINTRESOURCE(dwFontID), _T("RT_FONT"));
	DWORD cbSize = SizeofResource(hInstRes, hRsrc);
	HGLOBAL hMem = LoadResource(hInstRes, hRsrc);
	LPVOID pvData = LockResource(hMem);
	DWORD nFontsInstalled = 0;
	return AddFontMemResourceEx(pvData, cbSize, NULL, &nFontsInstalled);
}

void UninstallFont(HANDLE hFont)
{
	if(NULL == hFont) return;
	RemoveFontMemResourceEx(hFont);
}
CString GetModuleDirectory()
{
	CString sModuleFile = _T("");
	GetModuleFileName(NULL, sModuleFile.GetBuffer(MAX_PATH), MAX_PATH);
	sModuleFile.ReleaseBuffer();
	if(sModuleFile != _T(""))
	{
		sModuleFile = sModuleFile.Left(sModuleFile.ReverseFind('\\') + 1);
	}

	return sModuleFile;
}
BOOL CreateFileShortcut(CString sFileName, CString sLnkFileDir, CString sLnkFileName, CString sWorkDir, CString sArguments, WORD wHotkey, CString sDescription, int iShowCmd)  
{  
	if (sLnkFileDir.IsEmpty())  
		return FALSE;  

	HRESULT hr;  
	IShellLink     *pLink;  //IShellLink对象指针  
	IPersistFile   *ppf; //IPersisFil对象指针  

	//创建IShellLink对象  
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);  
	if (FAILED(hr))  
		return FALSE;  

	//从IShellLink对象中获取IPersistFile接口  
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);  
	if (FAILED(hr))  
	{  
		pLink->Release();  
		return FALSE;  
	}  

	//目标  
	if (!sFileName.IsEmpty())  
		pLink->SetPath(_wpgmptr);  
	else  
		pLink->SetPath(sFileName);

	//工作目录  
	if (!sWorkDir.IsEmpty())  
		pLink->SetPath(sWorkDir);

	//運行參數  
	if (!sArguments.IsEmpty())  
		pLink->SetArguments(sArguments);

	//快捷键  
	if (wHotkey != 0)  
		pLink->SetHotkey(wHotkey);

	//备注  
	if (!sDescription.IsEmpty())
		pLink->SetDescription(sDescription);

	//显示方式  
	pLink->SetShowCmd(iShowCmd);


	if (sLnkFileName.IsEmpty()) //沒有指定快捷方式的名称
	{
		//没有指定名称，就从取指定文件的文件名作为快捷方式名称。  
		sLnkFileName = sFileName.Left(sFileName.ReverseFind('\\') + 1);

		int nLen = sLnkFileName.GetLength();
		sLnkFileName.SetAt(nLen - 3, 'l');
		sLnkFileName.SetAt(nLen - 2, 'n');
		sLnkFileName.SetAt(nLen - 1, 'k');
	}

	hr = ppf->Save(sLnkFileDir + _T("\\") + sLnkFileName, TRUE);

	ppf->Release();
	pLink->Release();
	return SUCCEEDED(hr);
}  

CString BrowseFolder(HWND hWnd)
{
	ASSERT(hWnd);

	CString string = _T("");

	TCHAR szBuffer[MAX_PATH];  
	ZeroMemory(szBuffer, MAX_PATH);  

	BROWSEINFO bi; 
	LPITEMIDLIST pList=NULL; 
	bi.hwndOwner      = hWnd;  
	bi.pidlRoot       = NULL;  
	bi.pszDisplayName = szBuffer;  
	bi.lpszTitle      = _T("");  
	bi.ulFlags        = BIF_EDITBOX;  
	bi.lpfn           = NULL;  
	bi.lParam         = 0;  
	bi.iImage         = 0;
	if(NULL != (pList = SHBrowseForFolder(&bi)))  
	{  
		SHGetPathFromIDList(pList, string.GetBuffer(MAX_PATH));
		string.ReleaseBuffer();
	}

	return string;
}

CString BrowseFile(LPCTSTR lpszFilter, LPCTSTR lpszDefExt, BOOL bOpen)
{
	CString sPathName = _T("");
	CFileDialog dlg(bOpen, 
		lpszDefExt,
		NULL, 
		OFN_HIDEREADONLY | OFN_EXPLORER,
		lpszFilter, 
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		sPathName = dlg.GetPathName();
	}
	return sPathName;
}

void DebugLog(const wchar_t* pszFormat, ...)
{
	ASSERT(pszFormat && *pszFormat);

	wchar_t  szMsg[1024];	
	va_list  vargs;

	va_start(vargs, pszFormat);

	_vsnwprintf_s( szMsg, sizeof(szMsg) - 1, pszFormat, vargs);

	CString sTime;
	SYSTEMTIME st;
	memset(&st, 0, sizeof(SYSTEMTIME));
	GetSystemTime(&st);
	sTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d >>> "),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	OutputDebugString(sTime + CString(szMsg) + _T("\n"));

	va_end(vargs);
}

void LogFile(const wchar_t* pszFormat, ...)
{
	CString sCmd = GetCommandLine();
	if (sCmd.Find(_T(" /l")) < 0)
	{
		return;
	}

	ASSERT(pszFormat && *pszFormat);

	wchar_t  szMsg[1024];	
	va_list  vargs;

	va_start(vargs, pszFormat);

	_vsnwprintf_s( szMsg, sizeof(szMsg) - 1, pszFormat, vargs);

	CString sTime;
	SYSTEMTIME st;
	memset(&st, 0, sizeof(SYSTEMTIME));
	GetSystemTime(&st);
	sTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d >>> "),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	CStdioFile Logfile;
	if(Logfile.Open(GetModuleDirectory() + _T("log.txt"), CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
	{
		CTime CurTime = CTime::GetCurrentTime();
		Logfile.SeekToEnd();
		Logfile.WriteString(sTime + CString(szMsg) + _T("\n"));
		Logfile.Close();
	}

	va_end(vargs);
}

void ShowLoadingWindow(LPVOID pParam, int status)
{
	CUiDlg* pMain = (CUiDlg*)pParam;
	if (status == SW_SHOW && pMain->IsWindowVisible())
	{
		WinExec("loading.exe",SW_SHOW);
		CWnd* hNotepad = pMain->FindWindow(NULL, _T("LoadingGIF"));
		if (hNotepad == NULL)
		{
			return;
		}
		CRect c;
		CRect LoadCrect;
		pMain->FindWindow(NULL, _T("LoadingGIF"))->GetClientRect(LoadCrect);
		pMain->GetClientRect(&c);
		pMain->ClientToScreen(&c);
		hNotepad->SetWindowPos(&CWnd::wndTopMost,c.Width() / 2 + c.left-LoadCrect.Width()/2, c.Height()/2+c.top-LoadCrect.Height()/2, 0, 0, SWP_NOSIZE);
	} 
	else if (status == SW_HIDE)
	{
		CWnd* hNotepad = pMain->FindWindow(NULL, _T("LoadingGIF"));
		if (hNotepad != NULL)
		{
			::PostMessage(hNotepad->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
		}
	}
}

#include "../inc/shm/ShareMemory.h"
CShareMemory s_shareMemory;
static int s_nLockTime = 0;

void InitLock()
{
	s_shareMemory.Init(_T("MUX_GIGABYTE_AORUS_SYNC_LED"), _T("SHM_GIGABYTE_AORUS_SYNC_LED"), sizeof(int));
}

void CmdLock()
{
	s_nLockTime++;
	int nLock = 1;
	s_shareMemory.Write(&nLock);
}

void CmdUnLock()
{
	s_nLockTime--;
	int nLock = 0;
	if(0 == s_nLockTime) 
		s_shareMemory.Write(&nLock);
}

bool RawInputDevices(HWND hWnd, DWORD dwType, bool bRegister)
{
	RAWINPUTDEVICE rid[3];
	memset (rid, 0, sizeof (rid));

	int n = 0;

	if (RAW_DEV_HID & dwType)
	{
		rid[n].usUsagePage = 0xFF00;
		rid[n].usUsage = 0x01;
		rid[n].dwFlags = bRegister ? RIDEV_INPUTSINK : RIDEV_REMOVE;
		rid[n].hwndTarget = bRegister ? hWnd : NULL;
		n++;
	}

	if (RAW_DEV_KB & dwType)
	{
		rid[n].usUsagePage = 0x01;
		rid[n].usUsage = 0x06;
		rid[n].dwFlags = bRegister ? RIDEV_INPUTSINK | RIDEV_NOHOTKEYS : RIDEV_REMOVE;
		rid[n].hwndTarget = bRegister ? hWnd : NULL;
		n++;
	}

	if (RAW_DEV_MS & dwType)
	{
		rid[n].usUsagePage = 0x01;
		rid[n].usUsage = 0x02;
		rid[n].dwFlags = bRegister ? RIDEV_INPUTSINK : RIDEV_REMOVE;
		rid[n].hwndTarget = bRegister ? hWnd : NULL;
		n++;
	}

	return RegisterRawInputDevices(rid, n, sizeof (RAWINPUTDEVICE)) == TRUE; // 註冊監聽hid設備
}