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
	// �a��: " WHERE 1 = 1"
	static CString Where();

	// �a��: " WHERE (SQL�Z��)"
	static CString Where(CString sSqlCmd);

	// �a��: " WHERE ���� = ֵ", ����"="���Ԟ�������Ԫ�\���, 
	// �\�����횞�"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"���е�һ�N
	static CString Where(CString sColumn, CString sOperator, CString sValue);
	static CString Where(CString sColumn, CString sOperator, int     nValue);
	static CString Where(CString sColumn, CString sOperator, float   fValue);
	static CString Where(CString sColumn, CString sOperator, double  fValue);

	// �a��: " AND (SQL�Z��)"
	static CString And(CString sSqlCmd);

	// �a��: " AND ���� = ֵ", ����"="���Ԟ�������Ԫ�\���, 
	// �\�����횞�"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"���е�һ�N
	static CString And(CString sColumn, CString sOperator, CString sValue);
	static CString And(CString sColumn, CString sOperator, int     nValue);
	static CString And(CString sColumn, CString sOperator, float   fValue);
	static CString And(CString sColumn, CString sOperator, double  fValue);

	// �a��: " OR (SQL�Z��)"
	static CString Or(CString sSqlCmd);

	// �a��: " OR ���� = ֵ", ����"="���Ԟ�������Ԫ�\���, 
	// �\�����횞�"=", "<>", "<", "<=", ">", ">=", "LIKE", "NOT LIKE"���е�һ�N
	static CString Or(CString sColumn, CString sOperator, CString sValue);
	static CString Or(CString sColumn, CString sOperator, int     nValue);
	static CString Or(CString sColumn, CString sOperator, float   fValue);
	static CString Or(CString sColumn, CString sOperator, double  fValue);
	
	// �a��: " ���� BETWEEN (SQL�Z��1) AND (SQL�Z��2)"
	static CString Between(CString sColumn, CString sSqlCmd1, CString sSqlCmd2);

	// �a��: " ���� BETWEEN ��Сֵ AND ���ֵ"
	static CString Between(CString sColumn, int    nMinValue, int     nMaxValue);
	static CString Between(CString sColumn, float  fMinValue, float   fMaxValue);
	static CString Between(CString sColumn, double fMinValue, double  fMaxValue);
	static CString Between(CString sColumn, COleDateTime dtFrom, COleDateTime dtTo);

	// �a��: " ���� NOT BETWEEN (SQL�Z��1) AND (SQL�Z��2)"
	static CString NotBetween(CString sColumn, CString sSqlCmd1, CString sSqlCmd2);

	// �a��: " ���� NOT BETWEEN ��Сֵ AND ���ֵ"
	static CString NotBetween(CString sColumn, int    nMinValue, int    nMaxValue);
	static CString NotBetween(CString sColumn, float  fMinValue, float  fMaxValue);
	static CString NotBetween(CString sColumn, double fMinValue, double fMaxValue);
	static CString NotBetween(CString sColumn, COleDateTime dtFrom, COleDateTime dtTo);

	// �a��: " ���� IN (����SQL�Z��)"
	static CString In(CString sColumn, CString sSqlCmd);

	// �a��: " ���� IN (ֵ1, ֵ2, ֵ3, ...)"
	static CString In(CString sColumn, CString* values, int nCount);
	static CString In(CString sColumn, int*     values, int nCount);
	static CString In(CString sColumn, float*   values, int nCount, int nPrecision=3/*���c����ʽ���ַ����rС���c�ᾫ��3λ*/);
	static CString In(CString sColumn, double*  values, int nCount, int nPrecision=3/*���c����ʽ���ַ����rС���c�ᾫ��3λ*/);

	// �a��: " ���� NOT IN (����SQL�Z��)"
	static CString NotIn(CString sColumn, CString sSqlCmd);

	// �a��: " ���� NOT IN (ֵ1, ֵ2, ֵ3, ...)"
	static CString NotIn(CString sColumn, CString* values, int nCount);
	static CString NotIn(CString sColumn, int*     values, int nCount);
	static CString NotIn(CString sColumn, float*   values, int nCount, int nPrecision=3/*���c����ʽ���ַ����rС���c�ᾫ��3λ*/);
	static CString NotIn(CString sColumn, double*  values, int nCount, int nPrecision=3/*���c����ʽ���ַ����rС���c�ᾫ��3λ*/);

	// �a��: " ORDER BY ��1 ASC, ��2 ASC, ...", ����"ASC"�ɞ�"DESC"�P�I��
	static CString OrderBy(CString sColumns, CString sOrderBy);
	static CString OrderBy(CString* columns, CString* orderBy, int nCount);

	// �a��: " ���� IS NULL"
	static CString IsNull(CString sColumn);

	// �a��: " ���� IS NOT NULL"
	static CString IsNotNull(CString sColumn);

	// �a��: " SELECT TOP n * FROM ����"
	static CString Select(CString sTableName, int nTop=0/*0��ʾ����ȫ��ӛ�*/);

	// �a��: " SELECT TOP n ��1 FROM ����"
	static CString SelectColumn(CString sTableName, CString sColSel, int nTop=0/*0��ʾ����ȫ��ӛ�*/);

	// �a��: " SELECT TOP n ��1, ��2, ... FROM ����"
	static CString SelectColumns(CString sTableName, CString* colsSel, int nCols, int nTop=0/*0��ʾ����ȫ��ӛ�*/);

	// �a��: " SELECT DISTINCT TOP n ��1, ��2, ... FROM ����"
	static CString SelectDistinct(CString sTableName, CString* columns, int nCols, int nTop=0/*0��ʾ����ȫ��ӛ�*/);

    // �a��: " INSERT INTO ���� (��1, ��2,...) VALUES (ֵ1, ֵ2,....);"
	static CString Insert(CString sTableName, Column* columns, int nCount, bool breturnId=false);
	static CString Insert(CString sTableName, CString* columns, CString* values, int nCount, bool breturnId=false/*true�t���" SELECT @@IDENTITY AS ID;"�Z��Ƭ��*/);

	// �a��: " UPDATE ���� SET ���� = 'ֵ'"
	static CString Update(CString sTableName, CString sColumn, CString sValue);

	// �a��: " UPDATE ���� SET ��1 = 'ֵ1', ��2 = 'ֵ2', ..."
	static CString Update(CString sTableName, Column* columns, int nCount);
	static CString Update(CString sTableName, CString* columns, CString* values, int nCount);

	// �a��: " DELETE * FROM ����"
	static CString Delete(CString sTableName);


	// �a��: " INNER JOIN ���ϱ� ON �ϙ�λ1 = �ϙ�λ2", ����"="���Ԟ�������Ԫ�\���
	static CString InnerJoin(CString sJoinTable/*���ϱ�*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// �a��: " LEFT JOIN ���ϱ� ON �ϙ�λ1 = �ϙ�λ2", ����"="���Ԟ�������Ԫ�\���
	static CString LeftJoin (CString sJoinTable/*���ϱ�*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// �a��: " RIGHT JOIN ���ϱ� ON �ϙ�λ1 = �ϙ�λ2", ����"="���Ԟ�������Ԫ�\���
	static CString RightJoin(CString sJoinTable/*���ϱ�*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// �a��: " FULL JOIN ���ϱ� ON �ϙ�λ1 = �ϙ�λ2", ����"="���Ԟ�������Ԫ�\���
	static CString FullJoin (CString sJoinTable/*���ϱ�*/, CString sJoinField1, CString sOperator, CString sJoinField2);

	// �a��: " GROUP BY ����"
	static CString GroupBy(CString sColumn);

};
}

#endif