#ifndef _GV_COM_DLL_SQLCMD_H_
#define _GV_COM_DLL_SQLCMD_H_

#include "Base.h"

namespace Gv {

class GVDLL SqlCmd
{
public:
	struct GVDLL Column {

		CString sCol; // Column name
		CString sVal; // Column value
		
		Column();
		Column(CString sColName, CString sColValue);
	};

public:
	// 產生: " WHERE 1 = 1"
	static CString Where();

	// 產生: " WHERE (SQL語句)"
	static CString Where(CString sSqlCmd);

	// 產生: " WHERE 列名 = 值", 其中"="可以為其他二元運算符, 
	// 運算符必須為"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"其中的一種
	static CString Where(CString sColumn, CString sOperator, CString sValue);
	static CString Where(CString sColumn, CString sOperator, int     nValue);
	static CString Where(CString sColumn, CString sOperator, float   fValue);
	static CString Where(CString sColumn, CString sOperator, double  fValue);

	// 產生: " AND (SQL語句)"
	static CString And(CString sSqlCmd);

	// 產生: " AND 列名 = 值", 其中"="可以為其他二元運算符, 
	// 運算符必須為"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"其中的一種
	static CString And(CString sColumn, CString sOperator, CString sValue);
	static CString And(CString sColumn, CString sOperator, int     nValue);
	static CString And(CString sColumn, CString sOperator, float   fValue);
	static CString And(CString sColumn, CString sOperator, double  fValue);

	// 產生: " OR (SQL語句)"
	static CString Or(CString sSqlCmd);

	// 產生: " OR 列名 = 值", 其中"="可以為其他二元運算符, 
	// 運算符必須為"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"其中的一種
	static CString Or(CString sColumn, CString sOperator, CString sValue);
	static CString Or(CString sColumn, CString sOperator, int     nValue);
	static CString Or(CString sColumn, CString sOperator, float   fValue);
	static CString Or(CString sColumn, CString sOperator, double  fValue);
	
	// 產生: " 列名 BETWEEN (SQL語句1) AND (SQL語句2)"
	static CString Between(CString sColumn, CString sSqlCmd1, CString sSqlCmd2);

	// 產生: " 列名 BETWEEN 最小值 AND 最大值"
	static CString Between(CString sColumn, int    nMinValue, int     nMaxValue);
	static CString Between(CString sColumn, float  fMinValue, float   fMaxValue);
	static CString Between(CString sColumn, double fMinValue, double  fMaxValue);
	static CString Between(CString sColumn, COleDateTime dtFrom, COleDateTime dtTo);

	// 產生: " 列名 NOT BETWEEN (SQL語句1) AND (SQL語句2)"
	static CString NotBetween(CString sColumn, CString sSqlCmd1, CString sSqlCmd2);

	// 產生: " 列名 NOT BETWEEN 最小值 AND 最大值"
	static CString NotBetween(CString sColumn, int    nMinValue, int    nMaxValue);
	static CString NotBetween(CString sColumn, float  fMinValue, float  fMaxValue);
	static CString NotBetween(CString sColumn, double fMinValue, double fMaxValue);
	static CString NotBetween(CString sColumn, COleDateTime dtFrom, COleDateTime dtTo);

	// 產生: " 列名 IN (其他SQL語句)"
	static CString In(CString sColumn, CString sSqlCmd);

	// 產生: " 列名 IN (值1, 值2, 值3, ...)"
	static CString In(CString sColumn, CString* values, int nCount);
	static CString In(CString sColumn, int*     values, int nCount);
	static CString In(CString sColumn, float*   values, int nCount, int nPrecision=3/*浮點數格式化字符串時小數點後精度3位*/);
	static CString In(CString sColumn, double*  values, int nCount, int nPrecision=3/*浮點數格式化字符串時小數點後精度3位*/);

	// 產生: " 列名 NOT IN (其他SQL語句)"
	static CString NotIn(CString sColumn, CString sSqlCmd);

	// 產生: " 列名 NOT IN (值1, 值2, 值3, ...)"
	static CString NotIn(CString sColumn, CString* values, int nCount);
	static CString NotIn(CString sColumn, int*     values, int nCount);
	static CString NotIn(CString sColumn, float*   values, int nCount, int nPrecision=3/*浮點數格式化字符串時小數點後精度3位*/);
	static CString NotIn(CString sColumn, double*  values, int nCount, int nPrecision=3/*浮點數格式化字符串時小數點後精度3位*/);

	// 產生: " ORDER BY 列1 ASC, 列2 ASC, ...", 其中"ASC"可為"DESC"關鍵字
	static CString OrderBy(CString sColumns, CString sOrderBy);
	static CString OrderBy(CString* columns, CString* orderBy, int nCount);

	// 產生: " 列名 IS NULL"
	static CString IsNull(CString sColumn);

	// 產生: " 列名 IS NOT NULL"
	static CString IsNotNull(CString sColumn);

	// 產生: " SELECT TOP n * FROM 表名"
	static CString Select(CString sTableName, int nTop=0/*0表示返回全部記錄*/);

	// 產生: " SELECT TOP n 列1 FROM 表名"
	static CString SelectColumn(CString sTableName, CString sColSel, int nTop=0/*0表示返回全部記錄*/);

	// 產生: " SELECT TOP n 列1, 列2, ... FROM 表名"
	static CString SelectColumns(CString sTableName, CString* colsSel, int nCols, int nTop=0/*0表示返回全部記錄*/);

	// 產生: " SELECT DISTINCT TOP n 列1, 列2, ... FROM 表名"
	static CString SelectDistinct(CString sTableName, CString* columns, int nCols, int nTop=0/*0表示返回全部記錄*/);

    // 產生: " INSERT INTO 表名 (列1, 列2,...) VALUES (值1, 值2,....);"
	static CString Insert(CString sTableName, Column* columns, int nCount, bool breturnId=false);
	static CString Insert(CString sTableName, CString* columns, CString* values, int nCount, bool breturnId=false/*true則添加" SELECT @@IDENTITY AS ID;"語句片段*/);

	// 產生: " UPDATE 表名 SET 列名 = '值'"
	static CString Update(CString sTableName, CString sColumn, CString sValue);

	// 產生: " UPDATE 表名 SET 列1 = '值1', 列2 = '值2', ..."
	static CString Update(CString sTableName, Column* columns, int nCount);
	static CString Update(CString sTableName, CString* columns, CString* values, int nCount);

	// 產生: " DELETE * FROM 表名"
	static CString Delete(CString sTableName);


	// 產生: " INNER JOIN 待聯合表 ON 聯合欄位1 = 聯合欄位2", 其中"="可以為其他二元運算符
	static CString InnerJoin(CString sJoinTable/*待聯合表*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// 產生: " LEFT JOIN 待聯合表 ON 聯合欄位1 = 聯合欄位2", 其中"="可以為其他二元運算符
	static CString LeftJoin (CString sJoinTable/*待聯合表*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// 產生: " RIGHT JOIN 待聯合表 ON 聯合欄位1 = 聯合欄位2", 其中"="可以為其他二元運算符
	static CString RightJoin(CString sJoinTable/*待聯合表*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// 產生: " FULL JOIN 待聯合表 ON 聯合欄位1 = 聯合欄位2", 其中"="可以為其他二元運算符
	static CString FullJoin (CString sJoinTable/*待聯合表*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// 產生: " GROUP BY 列名"
	static CString GroupBy(CString sColumn);

};
}

#endif