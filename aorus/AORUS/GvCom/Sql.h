#ifndef _GV_COM_DLL_SQL_H_
#define _GV_COM_DLL_SQL_H_

#include "SqlCmd.h"
#include "DataTable.h"

namespace Gv {

//
// 本類封裝訪問資料庫時無事務處理的操作.
//

class GVDLL Sql : public Base
{
public:
	Sql(DB db);
	Sql(CString sConnectionString);  // connnection string
	Sql(CString sServer,	// server
		CString sDB,		// DB Name
		CString sLogin,		// login name
		CString sPassword);	// password

public:
	virtual CString GetLastSqlCmd();
	COleDateTime GetServerDateTime();

	virtual bool CheckConnection(); // see we can connect to the server or not.
	virtual bool ExecSqlCmdNonQuery(CString sSqlCmd);  // Operation DON'T return any data. ex: INSERT/UPDATE ...
	virtual bool ExecSqlCmd(CString sSqlCmd, DataTable& dt); // Operation return data. ex: SELECT...

protected:
	CString m_sLastSqlCmd;
	CString m_sConnection;
};


//
// 本類封裝訪問資料庫時有事務處理的操作.
//

class GVDLL SqlTrans : public Sql
{
public:
	SqlTrans(DB db);
	SqlTrans(CString sConnectionString);  // connnection string
	SqlTrans(CString sServer,	// server
		 CString sDB,			// DB Name
		 CString sLogin,		// Login name
		 CString sPassword);	// password

public:
	virtual bool ExecSqlCmdNonQuery(CString sSqlCmd); 
	virtual bool ExecSqlCmd(CString sSqlCmd, DataTable& dt);
	bool Insert(CString sTableName, SqlCmd::Column* columns, int nCount, CString& sId);			// 插入數據並返回ID
	bool Insert(CString sTableName, CString* columns, CString* values, int nCount, CString& sId);	// 插入數據並返回ID
    void Commit();		// 執行完資料庫操作, 提交事務并關閉鏈接;
    void Rollback();	// 執行完資料庫操作, 回滾事務并關閉鏈接;

private:
	bool  m_bSuccessful;
	void* m_pRecordset;
	void* m_pConnection;
};

}

#endif
