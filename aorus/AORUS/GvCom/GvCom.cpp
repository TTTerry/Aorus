#include "stdafx.h"
#include "GvCom.h"
using namespace Gv;

#ifndef  GVCOM_EXPORT
#ifndef  _UNICODE
#pragma comment(lib, "GvCom/GvComA.lib")
#else
#pragma comment(lib, "GvCom/GvComW.lib")
#endif
#endif

#ifndef  _SAMPLE_CODE
// Add SampleCode here

// function name rule: SampleCode__Class_***

/////////////////////////////////////////////////
// Excel class
/////////////////////////////////////////////////
//
// ���Пo���ؔ����Y�ώ������SQL�_��
//
void SampleCode_Excel_1()
{
}

/////////////////////////////////////////////////
// Sql class
/////////////////////////////////////////////////
//
// ���Пo���ؔ����Y�ώ������SQL�_��
//
void SampleCode_Sql_1()
{
	#define SERVER			_T("HZC-PC\\SQLEXPRESS")	// Local machine
	#define DATABASE		_T("TEST")
	#define USER			_T("test")
	#define PASSWORD		_T("test")	

	SqlCmd::Column cols[4] = 
	{
		SqlCmd::Column(_T("Field_1"), _T("Value_1")),
		SqlCmd::Column(_T("Field_2"), _T("Value_2")),
		SqlCmd::Column(_T("Field_3"), _T("Value_3")),
		SqlCmd::Column(_T("Field_4"), _T("Value_4")),
	};

	Sql sql(SERVER, DATABASE, USER, PASSWORD);
	CString sSqlCmd = SqlCmd::Insert(_T("TableName"), cols, 4);  // ����SqlCmd�ƴ��SQL�Z��
	bool bSuccessful = sql.ExecSqlCmdNonQuery(sSqlCmd);
	if(!bSuccessful)
	{
		CString sError = sql.GetLastError();
	}
}

//
// �����з��ؔ����Y�ώ������SQL�_��
//
void SampleCode_Sql_2()
{
	#define SERVER			_T("HZC-PC\\SQLEXPRESS")	// Local machine
	#define DATABASE		_T("TEST")
	#define USER			_T("test")
	#define PASSWORD		_T("test")	

	DataTable dt;
	Sql sql(SERVER, DATABASE, USER, PASSWORD);
	CString sSqlCmd = SqlCmd::Select(_T("TableName"), 10);  // ����SqlCmd�ƴ��SQL�Z��
	bool bSuccessful = sql.ExecSqlCmd(sSqlCmd, dt);
	if(!bSuccessful)
	{
		CString sError = sql.GetLastError();
		return;
	}

	// �xÿ��ӛ䛙�λֵ2�N��ʽ: 
	// 1) dt.Rows[i][j].GetValue(); j������̖
	// 2) dt.Rows[i]["��λ��"].GetValue();
	// ע��: �{�����������T��dt.Rows[i]["��λ��"].GetDateTimeV()�t���D�Q�������ֵ.
	// ��ҊDataColumn��^�ļ�.

	for(UINT i=0; i<dt.Rows.Count(); i++)
	{
		CString sCol_1 = dt.Rows[i]["Field_1"].GetValue(); // or: dt.Rows[i][0].GetValue()
		CString sCol_2 = dt.Rows[i]["Field_2"].GetValue(); // or: dt.Rows[i][1].GetValue()
		CString sCol_3 = dt.Rows[i]["Field_3"].GetValue(); // or: dt.Rows[i][2].GetValue()
		CString sCol_4 = dt.Rows[i]["Field_4"].GetValue(); // or: dt.Rows[i][3].GetValue()
	}
}

//
// ����EBOM
//
void SampleCode_HwTool_ParseEBOM()
{
	//HwTool hw;
	//EBOM bom;
	//CString sFile = _T("D:\\EBOM.txt");
	//if(!hw.ParseEBOM(sFile, bom))
	//{
	//	CString sErrInfo = hw.GetLastError(); // for debug.
	//}

	//for(UINT i=0; i<bom.Count(); i++)
	//{
	//	EBOM::Material* material = bom.GetMaterial(i);
	//	
	//	// basic info.
	//	// Other info, see Material class definition
	//	CString sDesc1  = material->GetDesc1();
	//	CString sDesc2  = material->GetDesc2(); 
	//	CString sPartNo = material->GetPartNo();

	//	// location
	//	for(UINT k=0; k<material->LocsCount(); k++)
	//	{
	//		CString sLocation = material->GetLocation(k);
	//	}

	//	// sub-materials
	//	for(UINT k=0; k<material->SubMCount(); k++)
	//	{
	//		CString sDesc1_s  = material->GetSubMaterial(k)->GetDesc1();
	//		CString sDesc2_s  = material->GetSubMaterial(k)->GetDesc2();
	//		CString sPartNo_s = material->GetSubMaterial(k)->GetPartNo();
	//	}
	//}
}


#endif