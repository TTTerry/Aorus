#include "stdafx.h"
#include "IniFile.h"

#ifdef _UNICODE
#define _ttof _wtof
#else
#define _ttof  atof
#endif

//---------------------------------------------------------------------------------------
CIniFile::CIniFile()
{
	m_bInitialize = FALSE;
	ZeroMemory(m_szIniFile, sizeof(TCHAR) * MAX_LEN);
}
//---------------------------------------------------------------------------------------
CIniFile::~CIniFile()
{
}
//---------------------------------------------------------------------------------------
void CIniFile::SetIniFile(CString strIniFile)
{
	ASSERT(strIniFile != _T(""));

	m_bInitialize = TRUE;
	memcpy(m_szIniFile, strIniFile.GetBuffer(MAX_LEN), sizeof(TCHAR) * MAX_LEN);
	strIniFile.ReleaseBuffer();
}

//int
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, int& nValue, BOOL bInitIfGetFailed)
{
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);

	int nTemp = nValue;
	if(m_bInitialize)
	{
		TCHAR szValue[MAX_LEN];
		if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_LEN, m_szIniFile))
		{
			nValue = (int)_ttoi(szValue);
			return TRUE;
		}
	}

	if(bInitIfGetFailed)
	{
		nValue = nTemp;
		return SetIniInfo(pszAppName, pszKeyName, nValue);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, int nValue)
{
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);

	if(m_bInitialize)
	{
		TCHAR szValue[MAX_LEN];
		_itot_s(nValue, szValue, MAX_LEN, 10);
		return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString strAppName, CString strKeyName, int& nValue, BOOL bInitIfGetFailed)
{
	int nTemp = nValue;
	BOOL bDone = GetIniInfo(strAppName.GetBuffer(MAX_LEN), strKeyName.GetBuffer(MAX_LEN), nValue);
	strAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	if(bDone)
	{
		return TRUE;
	}

	if(bInitIfGetFailed)
	{
		nValue = nTemp;
		return SetIniInfo(strAppName, strKeyName, nValue);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString strAppName, CString strKeyName, int nValue)
{
	BOOL bDone = SetIniInfo(strAppName.GetBuffer(MAX_LEN), strKeyName.GetBuffer(MAX_LEN), nValue);
	strAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}


//WORD
//---------------------------------------------------------------------------------------

BOOL CIniFile::GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, WORD& wValue, BOOL bInitIfGetFailed)
{
	int nValue = (int)wValue;
	if(GetIniInfo(pszAppName, pszKeyName, nValue, bInitIfGetFailed))
	{
		wValue = (WORD)nValue;
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, WORD  wValue)
{
	int nValue = (int)wValue;
	return SetIniInfo(pszAppName, pszKeyName, nValue);
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString strAppName, CString strKeyName, WORD& wValue, BOOL bInitIfGetFailed)
{
	int nValue = (int)wValue;
	if(GetIniInfo(strAppName, strKeyName, nValue, bInitIfGetFailed))
	{
		wValue = (WORD)nValue;
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString strAppName, CString strKeyName, WORD  wValue)
{
	int nValue = (int)wValue;
	return SetIniInfo(strAppName, strKeyName, nValue);
}
//---------------------------------------------------------------------------------------

BOOL CIniFile::GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, bool& bValue, BOOL bInitIfGetFailed)
{
	int nValue = (int)bValue;
	if(GetIniInfo(pszAppName, pszKeyName, nValue, bInitIfGetFailed))
	{
		bValue = (0 != nValue);
		return TRUE;
	}

	return FALSE;
}

//bool
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, bool  bValue)
{
	int nValue = (int)bValue;
	return SetIniInfo(pszAppName, pszKeyName, nValue);
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString strAppName, CString strKeyName, bool& bValue, BOOL bInitIfGetFailed)
{
	int nValue = (int)bValue;
	if(GetIniInfo(strAppName, strKeyName, nValue, bInitIfGetFailed))
	{
		bValue = (0 != nValue);
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString strAppName, CString strKeyName, bool  bValue)
{
	int nValue = (int)bValue;
	return SetIniInfo(strAppName, strKeyName, nValue);
}


//DWORD
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD& dwValue, BOOL bInitIfGetFailed)
{
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);

	DWORD dwTemp = dwValue;
	if(m_bInitialize)
	{
		TCHAR szValue[MAX_LEN];
		if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_LEN, m_szIniFile))
		{
			dwValue = (DWORD)_ttol(szValue);
			return TRUE;
		}
	}

	if(bInitIfGetFailed)
	{
		dwValue = dwTemp;
		return SetIniInfo(pszAppName, pszKeyName, dwValue);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD dwValue)
{
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);

	if(m_bInitialize)
	{
		TCHAR szValue[MAX_LEN];
		_ltot_s(dwValue, szValue, MAX_LEN, 10);
		return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString strAppName, CString strKeyName, DWORD& dwValue, BOOL bInitIfGetFailed)
{
	DWORD dwTemp = dwValue;
	BOOL bDone = GetIniInfo(strAppName.GetBuffer(MAX_LEN), strKeyName.GetBuffer(MAX_LEN), dwValue);
	strAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	if(bDone)
	{
		return TRUE;
	}

	if(bInitIfGetFailed)
	{
		dwValue = dwTemp;
		return SetIniInfo(strAppName, strKeyName, dwValue);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString strAppName, CString strKeyName, DWORD dwValue)
{
	BOOL bDone = SetIniInfo(strAppName.GetBuffer(MAX_LEN), strKeyName.GetBuffer(MAX_LEN), dwValue);
	strAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}

//CString
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_LEN], BOOL bInitIfGetFailed)
{
	ASSERT(NULL != szValue);
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);
	
	TCHAR szTemp[MAX_LEN] = {0};
	if(m_bInitialize)
	{
		if(GetPrivateProfileString(pszAppName, pszKeyName, NULL, szTemp, MAX_LEN, m_szIniFile))
		{
			_tcscpy_s(szValue, MAX_LEN, szTemp);
			return TRUE;
		}
	}

	_tcscpy_s(szTemp, MAX_LEN, szValue);

	if(bInitIfGetFailed)
	{
		return SetIniInfo(pszAppName, pszKeyName, szTemp);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_LEN])
{
	ASSERT(NULL != szValue);
	ASSERT(NULL != pszAppName);
	ASSERT(NULL != pszKeyName);

	TCHAR szTemp[MAX_LEN] = {0};
	if(m_bInitialize)
	{
		_tcscpy_s(szTemp, MAX_LEN, szValue);
		return WritePrivateProfileString(pszAppName, pszKeyName, szTemp, m_szIniFile);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString strAppName, CString strKeyName, CString& strValue, BOOL bInitIfGetFailed)
{	
	ASSERT(_T("") != strAppName);
	ASSERT(_T("") != strKeyName);

	CString strTemp;
	if(m_bInitialize)
	{
		BOOL bDone = GetPrivateProfileString(strAppName.GetBuffer(), strKeyName.GetBuffer(), NULL, strTemp.GetBuffer(MAX_LEN), MAX_LEN, m_szIniFile);
		strAppName.ReleaseBuffer();
		strKeyName.ReleaseBuffer();
		strTemp.ReleaseBuffer();
		if(bDone)
		{
			strValue = strTemp;
			return TRUE;
		}
	}

	strTemp = strValue;

	if(bInitIfGetFailed)
	{
		return SetIniInfo(strAppName, strKeyName, strTemp);
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString strAppName, CString strKeyName, CString strValue)
{
	ASSERT(_T("") != strAppName);
	ASSERT(_T("") != strKeyName);

	if(m_bInitialize)
	{
		CString strTemp = strValue;
		BOOL bDone = WritePrivateProfileString(strAppName.GetBuffer(), strKeyName.GetBuffer(), strTemp.GetBuffer(), m_szIniFile);
		strAppName.ReleaseBuffer();
		strKeyName.ReleaseBuffer();
		strTemp.ReleaseBuffer();

		return bDone;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------
