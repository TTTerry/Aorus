#ifndef _GV_COM_DLL_EXCEL_H_
#define _GV_COM_DLL_EXCEL_H_

#include "Base.h"

namespace Gv {

class GVDLL Excel : public Base
{
public:
	enum Ver {Unknown = 0, Excel_2003, Excel_2007, }; //  Excel version

	struct GVDLL Cell {
		int nStyle;		// Cell style index. default: -1 = Non-style
		CString sValue; // Cell value

		Cell(CString _sValue);
		Cell(CString _sValue, int _nStyle);
	};

	struct GVDLL Column {
		CString sName;	// column name
		int nWidth;		// column width, Uint: px
		Align align;    // column align
		bool bGroup;   

		Column(CString _sName, int _nWidth, Align _align);
		Column(CString _sName, int _nWidth, Align _align, bool _bGroup);
	};

	class GVDLL Sheet {
	public:
		Sheet(void* pExcelOp, int nSheet);

	public:
		// sheet operation 
		CString GetName();
		void SetName(CString sName);
		bool GetVisable();
		void SetVisable(bool bVisable=true);
		void FreezePanes(int row/*based on 1, 0: Ignored row freeze*/, int col/*based on 1, 0: Ignored row freeze*/, bool bFreeze);
		int  GetIndex();  // index in Excel file, based on 1

		// row operation 
		void RowSetHeight(int row/*based on 1*/, int nHeight/*px, 0: AutoFit*/, bool bWrapText/*true: auto line wrap*/);
		void RowInsert(int rowStart/*based on 1*/, int nCount);
		void RowDelete(int rowStart/*based on 1*/, int nCount);
		void RowFreeze(int row/*based on 1*/, bool bFreeze);

		// col operation 
		void ColSetWidth(int col/*based on 1*/, int nWidth/*px, 0: AutoFit*/);
		void ColInsert(int colStart/*based on 1*/, int nCount);
		void ColDelete(int colStart/*based on 1*/, int nCount);
		void ColFreeze(int col/*based on 1*/, bool bFreeze);
		void ColAlign(int col/*based on 1*/, Align horAlign, AlignV verAlign);

		// cell operation 
		CString CellGetText(int row/*based on 1*/, int col/*based on 1*/);
		void CellSetText(int row/*based on 1*/, int col/*based on 1*/, CString sValue);

	private:
		int m_nSheet;		// Sheet index, based on 1
		void* m_pExcelOp;	// Class ExcelOp pointer
	};

	// sheets collection
	class GVDLL SheetCollection
	{
	public:
		 SheetCollection();
		~SheetCollection();
		friend class Excel;

		Sheet& operator[](UINT nIndex/* based on 1*/);
		
		UINT Count(); 
		void Add(); // insert one as the last sheet.
		void Add(CString sSheetName);	// insert one as the last sheet.
		void Add(int nBefore/* based on 1*/, bool bBefore/* true: before; false: after*/);
		void Add(CString sSheetName, int nBefore/* based on 1*/, bool bBefore/* true: before; false: after*/);
		void Remove(int nIndex/* based on 1*/);

	protected:
		void SetExcelOp(Excel* pExcel, void* pExcelOp);

	private:
		void* m_pExcelOp;
		Excel* m_pExcel;
		Sheet* m_pCurSheet;
	};

public:
	 Excel();	// new excel file
	 Excel(CString sFileName);	// open excel file
	~Excel();

public: 
	SheetCollection Sheets;	// sheets list.

	void Save();  // Save and dispose excel resource.
	void SaveAs(CString sFileName);	// Save and dispose excel resource.
	Excel::Ver GetVersion();

private:
	void Dispose();

private:
	void* m_pExcelOp;
	Sheet* m_pCurSheet;
	SheetCollection* m_pSheets;
};

}

#endif

