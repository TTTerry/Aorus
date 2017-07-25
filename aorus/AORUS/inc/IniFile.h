#ifndef _CINIFILE_2568lhtor6kfgfsgjj_H
#define _CINIFILE_2568lhtor6kfgfsgjj_H


/**********************************************************************************
 *
 * 实现操作Ini文件类
 *
 *********************************************************************************/
#define MAX_LEN 1024
class CIniFile
{
public:
	 CIniFile();
	~CIniFile();

	/****************************************************************************************
	 * 功能描述：
	 * 设置Ini文件路径, 使用该类时必须先设置Ini文件路径
	 *
	 * 输入参数:
	 * strIniFile Ini文件存放路径, 该路径必须为绝对路径, 如C:\file.ini.
	 ****************************************************************************************/
	void SetIniFile(CString strIniFile);

	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在int变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * nValue      如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用nValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, int& nValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, int  nValue);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, int& nValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, int  nValue);


	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在WORD变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * wValue      如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用nValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, WORD& wValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, WORD  wValue);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, WORD& wValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, WORD  wValue);

	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在bool变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * bValue      如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用nValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, bool& bValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, bool  bValue);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, bool& bValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, bool  bValue);


	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在DWORD变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * dwValue     如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用dwValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, DWORD& dwValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, DWORD  dwValue);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, DWORD& dwValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, DWORD  dwValue);


	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在double变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * dbValue     如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用dbValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, double& dbValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, double  dbValue);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, double& dbValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, double  dbValue);



	/****************************************************************************************
	 * 功能描述：
	 * 读/写Ini文件, 读/写结果保存在CString变量中
	 *
	 * 输入参数:
	 * pszAppName  如Ini文件中的[AppName].
	 * pszKeyName  如Ini文件中KeyName=Value中的KeyName
	 * szValue     如Ini文件中KeyName=Value中的Value
	 * bInitIfGetFailed 当Get键值失败时(该键值不存在)且bInitIfGetFailed为TRUE时, 用szValue初始化该键值
	 ****************************************************************************************/
	BOOL GetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, TCHAR szValue[MAX_LEN], BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(TCHAR  *pszAppName, TCHAR*  pszKeyName, TCHAR szValue[MAX_LEN]);
	BOOL GetIniInfo(CString strAppName, CString strKeyName, CString& strValue, BOOL bInitIfGetFailed=FALSE);
	BOOL SetIniInfo(CString strAppName, CString strKeyName, CString  strValue);

private:
	BOOL  m_bInitialize;
	TCHAR m_szIniFile[MAX_LEN];
};

#endif  //_CINIFILE_2568lhtor6kfgfsgjj_H

