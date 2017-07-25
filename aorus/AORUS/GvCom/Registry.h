#ifndef _GV_COM_DLL_REGISTER_H_
#define _GV_COM_DLL_REGISTER_H_

#include "Base.h"

namespace Gv {

class GVDLL Registry : public Base
{

public:
	//
	// �����]�Ա��е�KEY���
	//
	enum TYPE { KEY_CLASSES_ROOT = 0, KEY_CURRENT_USER = 1, KEY_LOCAL_MACHINE = 2, KEY_USERS = 3 };

public:
	Registry(TYPE type);
	Registry(HKEY hKey);	// 1) HKEY_CLASSES_ROOT; 2) HKEY_CURRENT_USER; 3) HKEY_LOCAL_MACHINE; 4) HKEY_USERS;

	//
	// ����sSubKeyָ���]�Ա�ĳ��Ŀ��µ�·��, ����HKEY_CURRENT_USER��: "software\\GIGABYTE\\verification\\skill"
	//

	bool IsExisted(CString sSubKey); // �Єeָ���]�Ա�·�����ڷ�
	bool CreateKey(CString sSubKey); // �Ӽ�����ָ���]�Ա�·��, ��: "software\\GBT\\Verify", ��GBT�cVerify��������, �tͬ�r������
	bool DeleteKey(CString sSubKey); // �h��ָ���]�Ա�·��, ��h��: "software\\GBT\\Verify", �t�HVerify���h��, �丸��GBT�����h��

	bool DeleteValue(CString sSubKey, CString sValueName); // �h���]�Ա�·�����]�Ա��ֵ

	// Read registry
	bool Read(CString sSubKey, CString sValueName, int&    nValue);
	bool Read(CString sSubKey, CString sValueName, bool&   bValue);
	bool Read(CString sSubKey, CString sValueName, UINT&   nValue);
	bool Read(CString sSubKey, CString sValueName, long&   nValue);
	bool Read(CString sSubKey, CString sValueName, DWORD&  dwValue);
	bool Read(CString sSubKey, CString sValueName, CString& sValue);
	bool Read(CString sSubKey, CString sValueName, LPVOID lpData, DWORD& dwDataSize/*size of data buffer*/);

	// Write registry, ��sSubKey�����ڕr����ͬ�r����
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
