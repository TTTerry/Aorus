#ifndef _GV_COM_DLL_DATATABLE_H_
#define _GV_COM_DLL_DATATABLE_H_


#include "Base.h"

namespace Gv {

/////////////////////////////////////////////////
// DataColumn class
/////////////////////////////////////////////////
class GVDLL DataColumn
{
public:
	DataColumn(CString sColName);
	
	CString GetValue();
	int GetIntV();
	long GetLongV();
	bool GetBoolV();
	float GetFloatV();
	double GetDoubleV();
	UINT GetUintV();
	DWORD GetDwordV();
	COleDateTime GetDateTimeV();	// Get value as DateTime
	
	void SetValue(CString sValue);
	CString ColumnName();
	DataColumn& operator = (const DataColumn& dc);
	 
private: 
	CString m_sValue;	// Field value of table.
	CString m_sColName;	// Field name of table in DB.
}; 
 
/////////////////////////////////////////////////
// DataColumnCollection class
/////////////////////////////////////////////////
class GVDLL DataColumnCollection
{
public:
	 DataColumnCollection();
	~DataColumnCollection();

	UINT Count(); 
	void Add(CString sColName);
	void Add(DataColumn* pNew);
	void Clear();  // clear all columns.

	DataColumn& operator[](UINT nIndex);
	DataColumn& operator[](const CStringA& sColumnName);
private:
	vector<DataColumn*> m_lstCols;
	map<CString, DataColumn*> m_lstNames;
};

/////////////////////////////////////////////////
// DataRow class
/////////////////////////////////////////////////
class GVDLL DataRow
{
public:
	DataRow();
	DataColumnCollection& Columns();
	DataColumn& operator[](UINT nIndex);
	DataColumn& operator[](const CStringA& sColName);
	
private:	
	DataColumnCollection m_cols;
};

/////////////////////////////////////////////////
// DataRowCollection class
/////////////////////////////////////////////////
class GVDLL DataRowCollection
{
public:
	 DataRowCollection();
	~DataRowCollection();
	
	UINT Count();  
	void Add(DataRow* pNew);  
	void Clear();	// clear all rows.

	DataRow& operator[](UINT nIndex); 
	
private:
	list<DataRow*> m_lstRows; 
};

/////////////////////////////////////////////////
// DataTable class
/////////////////////////////////////////////////
class GVDLL DataTable
{
public:
	 DataTable();
	~DataTable();

	void Clear(); 
	DataRow* NewRow();

public:
	DataRowCollection    Rows; 
	DataColumnCollection Cols; // every column title of table
};

}

#endif