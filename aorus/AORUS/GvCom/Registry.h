#ifndef _GV_COM_DLL_REGISTER_H_
#define _GV_COM_DLL_REGISTER_H_

#include "Base.h"

namespace Gv {

class GVDLL Registry : public Base
{

public:
	//
	// 對應註冊表中的KEY類型
	//
	enum TYPE { KEY_CLASSES_ROOT = 0, KEY_CURRENT_USER = 1, KEY_LOCAL_MACHINE = 2, KEY_USERS = 3 };

public:
	Registry(TYPE type);
	Registry(HKEY hKey);	// 1) HKEY_CLASSES_ROOT; 2) HKEY_CURRENT_USER; 3) HKEY_LOCAL_MACHINE; 4) HKEY_USERS;

	//
	// 以下sSubKey指定註冊表某根目錄下的路徑, 如在HKEY_CURRENT_USER下: "software\\GIGABYTE\\verification\\skill"
	//

	bool IsExisted(CString sSubKey); // 判別指定註冊表路徑存在否
	bool CreateKey(CString sSubKey); // 層級創建指定註冊表路徑, 如: "software\\GBT\\Verify", 若GBT與Verify均不存在, 則同時被創建
	bool DeleteKey(CString sSubKey); // 刪除指定註冊表路徑, 如刪除: "software\\GBT\\Verify", 則僅Verify被刪除, 其父級GBT不被刪除

	bool DeleteValue(CString sSubKey, CString sValueName); // 刪除註冊表路徑下註冊表項值

	// Read registry
	bool Read(CString sSubKey, CString sValueName, int&    nValue);
	bool Read(CString sSubKey, CString sValueName, bool&   bValue);
	bool Read(CString sSubKey, CString sValueName, UINT&   nValue);
	bool Read(CString sSubKey, CString sValueName, long&   nValue);
	bool Read(CString sSubKey, CString sValueName, DWORD&  dwValue);
	bool Read(CString sSubKey, CString sValueName, CString& sValue);
	bool Read(CString sSubKey, CString sValueName, LPVOID lpData, DWORD& dwDataSize/*size of data buffer*/);

	// Write registry, 若sSubKey不存在時會被同時創建
	bool Write(CString sSubKey, CString sValueName, int    nValue);
	bool Write(CString sSubKey, CString sValueName, bool   bValue);
	bool Write(CString sSubKey, CString sValueName, UINT   nValue);
	bool Write(CString sSubKey, CString sValueName, long   nValue);
	bool Write(CString sSubKey, CString sValueName, DWORD  dwValue);
	bool Write(CString sSubKey, CString sValueName, CString sValue);
	bool Write(CString sSubKey, CString sValueName, LPVOID lpData, DWORD dwDataSize/*size of data buffer*/, DWORD dwType/*ex: REG_SZ*/);

private:
	HKEY m_hKey;
};
}

#endif
