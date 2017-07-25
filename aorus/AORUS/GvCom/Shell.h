#ifndef _GV_COM_DLL_SHELL_H_
#define _GV_COM_DLL_SHELL_H_

#include "Base.h"

namespace Gv {

class GVDLL Shell : public Base
{
public: 
	 Shell();
	 Shell(CString sClass/*��ʽ����������Q*/, CString sWindowName/*��ʽ�����ژ��}*/); // ��ҊMSDN FindWindowEx()�����f����Spy++.exe
	~Shell();
	//
	// ����ָ��·����ʽ
	//
	bool Execute(CString sPath,		/*����·��*/ 
		CString sParameters=_T(""),	/*�����*/
		bool bWinShow=false			/*true:���Еr�@ʾ����*/
		);

	bool IsRunning(bool& bRunning);	// �z�y��ʽ�Ƿ��\����

	//
	// ģ�M����c������������ڵ�ĳ�c����λ��
	// ʹ��ǰՈ�{��Shell(CString, CString)���캯��
	//
	bool MouseClicked(POINT ptLocRelative);  

	//
	// ģ�Mᘌ���ʽ���F���I�c��, VK��ҊMSDN�f��
	// ʹ��ǰՈ�{��Shell(CString, CString)���캯��
	// 
	bool KeyClicked(BYTE btVirtualKey, bool bShowForeground=false/*true: �c��ǰ����픴���*/);	

private:
	CWnd* ShowForeground();

private:
	HANDLE m_hProcess;
	CString m_sClass;
	CString m_sWindowName;
};

}


#endif