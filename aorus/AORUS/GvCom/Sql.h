#ifndef _GV_COM_DLL_SQL_H_
#define _GV_COM_DLL_SQL_H_

#include "SqlCmd.h"
#include "DataTable.h"

namespace Gv {

//
// ����b�L���Y�ώ�r�o��̎��Ĳ���.
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
// ����b�L���Y�ώ�r����̎��Ĳ���.
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
	bool Insert(CString sTableName, SqlCmd::Column* columns, int nCount, CString& sId);			// ���딵���K����ID
	bool Insert(CString sTableName, CString* columns, CString* values, int nCount, CString& sId);	// ���딵���K����ID
    void Commit();		// �������Y�ώ����, �ύ�ղ��P�]朽�;
    void Rollback();	// �������Y�ώ����, �؝L�ղ��P�]朽�;

private:
	bool  m_bSuccessful;
	void* m_pRecordset;
	void* m_pConnection;
};

}

#endif
