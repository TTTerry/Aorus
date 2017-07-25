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
	static CString GetUserName();			// ��ǰϵ�y�Ñ����Q

	static CString GetCurDirectory();		// ��ǰexe·��, �����ַ�����'\'�Yβ
	static CString GetTmpDirectory();		// ��ǰϵ�y�Ñ��R�r·��, �����ַ�����'\'�Yβ

	static void GetCurModuleVersion(MODULE_VER& ver);	// �@ȡ�{�ñ�DLL�ĳ�ʽ�汾
	static void GetModuleVersion(const TCHAR* szModuleName/*�{��GetModuleFileName() API�@ȡModuleName*/, MODULE_VER& ver); // �@ȡָ����ʽ�汾
	static CString MakeCurModuleTitle(CString sModule);	// ��ʽ���T��: 'Module Ver1.00 Designed by VGA Software Dept.'	�ַ���

	static bool IsWow64();					// �Єe���Iϵ�y32/64λ, true: 64λ
	static OS_VER GetOSVersion();			// �Єe���Iϵ�y�汾

	static bool Reboot();					// �؆�ϵ�y
	static bool ShutDown();					// �P�]ϵ�y
	
};
}

#endif

