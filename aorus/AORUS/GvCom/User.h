#ifndef _GV_COM_DLL_DBUSER_H_
#define _GV_COM_DLL_DBUSER_H_

#include "Base.h"

namespace Gv {

//
// ������l����ԃKM_SYS_User�ˆT�Y��
//
class GVDLL User : public Base
{
public:
	struct GVDLL Employee	// ���T�ˆT
	{
		Employee();
		CString sIdDB;		// �Y�ώ�ID
		bool bLeft;			// �x��B, true��ʾ�x, false��ʾ�� 
		CString sLogin;		// ��䛎�̖ 
		CString sCName;		// �������Q
		CString sEName;		// Ӣ�����Q
		CString sDomain;	// ��������
		CString sMailAddr;	// �]���ַ
		CString sDept;		// ���ٲ��T, ������
		CString sNum;		// ���T��̖
		CString sTitle;		// ���T�Q, ������
		CString sTele;		// �֙C̖�a
		CString sExt;		// �֙C̖�a
		CString sMVPN;		// MVPN̖�a
	};

	class GVDLL EmployeeCollection
	{
	public:
		 EmployeeCollection();
		~EmployeeCollection();

		UINT Count(); 
		void Add(Employee* pNew);
		void Clear();  // clear all Employees.

		Employee& operator[](UINT nIndex);

	private:
		vector<Employee*> m_lstEmployees;
	};

public:
	User(DB db);
	User(CString sConnectionString);  // connnection string
	User(CString sServer, CString sDB, CString sLogin, CString sPassword);

	CString GetName(CString sUserId); // empty means error.
	bool QueryById(CString sIdDB, Employee& employee);	
	bool QueryByLogin(CString sLogin/*�����ˆT��̖*/, Employee& employee);
	bool QueryByMail(CString sMailAddr/*�����]���ַ*/, Employee& employee);
	bool QueryByIds(CString* idDBs, int nCount, EmployeeCollection& lstEmployees);
	bool QueryByMails(CString* mailAddrs/*�����]���ַ*/, int nCount, EmployeeCollection& lstEmployees); 
	bool QueryLike(CString sInfoLike/*�ˆT��̖or������orӢ����*/, EmployeeCollection& lstEmployees);

private:
	CString m_sConnection;
};

}

#endif