#ifndef _GV_COM_DLL_INIFILE_H_
#define _GV_COM_DLL_INIFILE_H_

#include "Base.h"

namespace Gv {
class GVDLL Ini : public Base
{

public:
	Ini(CString sIniFile/*full path*/);

	// read ini
	bool Read(CString sAppName,   CString sKeyName,   DWORD&   dwValue);
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, DWORD&   dwValue);
	bool Read(CString sAppName,   CString sKeyName,   int&     nValue);
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, int&     nValue);
	bool Read(CString sAppName,   CString sKeyName,   UINT&    nValue);
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, UINT&    nValue);
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, long&    nValue);
	bool Read(CString sAppName,   CString sKeyName,   long&    nValue);
	bool Read(CString sAppName,   CString sKeyName,   CString& sValue);
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, CString& sValue);
	bool Read(CString sAppName,   CString sKeyName,   bool&    bValue); // if key's value is 0, bValue = false, others, bValue = true.
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, bool&    bValue);
	
	// write ini
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, DWORD   dwValue);
	bool Write(CString sAppName,   CString sKeyName,   DWORD   dwValue);
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, int     nValue);
	bool Write(CString sAppName,   CString sKeyName,   int     nValue);
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, UINT    nValue);
	bool Write(CString sAppName,   CString sKeyName,   UINT    nValue);
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, long    nValue);
	bool Write(CString sAppName,   CString sKeyName,   long    nValue);
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, CString sValue);
	bool Write(CString sAppName,   CString sKeyName,   CString sValue);
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, bool    bValue);
	bool Write(CString sAppName,   CString sKeyName,   bool    bValue);

private:
	TCHAR m_szIni[MAX_PATH];
};
}

#endif

