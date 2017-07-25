#ifndef _GV_COM_DLL_OPSYSTEM_H_
#define _GV_COM_DLL_OPSYSTEM_H_

#include "Base.h"

namespace Gv {
class GVDLL OS : public Base
{
public:
	enum OS_VER { // OS version
		Unknown = 0, 
		WinXP, 
		WinServer_2003, 
		WinServer_2003_R2,
		Vista,
		Win7,
		WinServer_2008,
		WinServer_2008_R2,
		Win8,
	}; 

	struct GVDLL MODULE_VER { // Module version
		WORD wMajor;
		WORD wMinor;
		WORD wRevision;
		WORD wBuild;  
	};

public:
	static CString GetUserName();			// 當前系統用戶名稱

	static CString GetCurDirectory();		// 當前exe路徑, 返回字符串以'\'結尾
	static CString GetTmpDirectory();		// 當前系統用戶臨時路徑, 返回字符串以'\'結尾

	static void GetCurModuleVersion(MODULE_VER& ver);	// 獲取調用本DLL的程式版本
	static void GetModuleVersion(const TCHAR* szModuleName/*調用GetModuleFileName() API獲取ModuleName*/, MODULE_VER& ver); // 獲取指定程式版本
	static CString MakeCurModuleTitle(CString sModule);	// 格式化諸如: 'Module Ver1.00 Designed by VGA Software Dept.'	字符串

	static bool IsWow64();					// 判別作業系統32/64位, true: 64位
	static OS_VER GetOSVersion();			// 判別作業系統版本

	static bool Reboot();					// 重啟系統
	static bool ShutDown();					// 關閉系統
	
};
}

#endif

