#ifndef _GV_COM_DLL_DBUSER_H_
#define _GV_COM_DLL_DBUSER_H_

#include "Base.h"

namespace Gv {

//
// 本類根據條件查詢KM_SYS_User人員資料
//
class GVDLL User : public Base
{
public:
	struct GVDLL Employee	// 部門人員
	{
		Employee();
		CString sIdDB;		// 資料庫ID
		bool bLeft;			// 離職狀態, true表示離職, false表示在職 
		CString sLogin;		// 登錄帳號 
		CString sCName;		// 中文名稱
		CString sEName;		// 英文名稱
		CString sDomain;	// 所屬域名
		CString sMailAddr;	// 郵箱地址
		CString sDept;		// 所屬部門, 暫保留
		CString sNum;		// 部門工號
		CString sTitle;		// 部門職稱, 暫保留
		CString sTele;		// 手機號碼
		CString sExt;		// 分機號碼
		CString sMVPN;		// MVPN號碼
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
	bool QueryByLogin(CString sLogin/*完整人員帳號*/, Employee& employee);
	bool QueryByMail(CString sMailAddr/*完整郵箱地址*/, Employee& employee);
	bool QueryByIds(CString* idDBs, int nCount, EmployeeCollection& lstEmployees);
	bool QueryByMails(CString* mailAddrs/*完整郵箱地址*/, int nCount, EmployeeCollection& lstEmployees); 
	bool QueryLike(CString sInfoLike/*人員帳號or中文名or英文名*/, EmployeeCollection& lstEmployees);

private:
	CString m_sConnection;
};

}

#endif