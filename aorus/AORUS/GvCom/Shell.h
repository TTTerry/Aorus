#ifndef _GV_COM_DLL_SHELL_H_
#define _GV_COM_DLL_SHELL_H_

#include "Base.h"

namespace Gv {

class GVDLL Shell : public Base
{
public: 
	 Shell();
	 Shell(CString sClass/*程式主窗口類名稱*/, CString sWindowName/*程式主窗口標題*/); // 參見MSDN FindWindowEx()參數說明及Spy++.exe
	~Shell();
	//
	// 啟動指定路徑程式
	//
	bool Execute(CString sPath,		/*完整路徑*/ 
		CString sParameters=_T(""),	/*命令參數*/
		bool bWinShow=false			/*true:執行時顯示窗口*/
		);

	bool IsRunning(bool& bRunning);	// 檢測程式是否運行中

	//
	// 模擬鼠標點擊相對於主窗口的某點座標位置
	// 使用前請調用Shell(CString, CString)構造函數
	//
	bool MouseClicked(POINT ptLocRelative);  

	//
	// 模擬針對程式實現熱鍵點擊, VK參見MSDN說明
	// 使用前請調用Shell(CString, CString)構造函數
	// 
	bool KeyClicked(BYTE btVirtualKey, bool bShowForeground=false/*true: 點擊前先置頂窗口*/);	

private:
	CWnd* ShowForeground();

private:
	HANDLE m_hProcess;
	CString m_sClass;
	CString m_sWindowName;
};

}


#endif