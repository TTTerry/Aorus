#ifndef _GV_COM_DLL_HWTOOL_H_
#define _GV_COM_DLL_HWTOOL_H_

#include "Base.h"
#include "DataTable.h"


namespace Gv {
	

// EBOM information

class GVDLL EBOM
{
	enum TypeM { Other = 0, SMD = 1, DIP = 2, };		// material type in EBOM
	enum Layer { Unknown = 0, Top = 1, Bottom = 2, };	// material layer

public:
	//
	// EBOM料件所使用的位置集合
	//
	class GVDLL LocationCollection
	{
	public:
		 LocationCollection();
		~LocationCollection();

		UINT Count();
		void Add(CString* pNew);
		void Clear();
		bool Contain(CString sLocation);

		CString& operator[](UINT nIndex);

	private:
		vector<CString*> m_lstLocs;	
	};

	class Material;

	//
	// EBOM料件集合
	//
	class GVDLL MaterialCollection
	{
	public:
		 MaterialCollection();
		~MaterialCollection();

		UINT Count();
		void Add(Material* pNew);
		void Clear();

		bool Contain(CString sPartNo);

		Material* FindByLocation( // return material which contains the location. return NULL if not found.
			CString sLocation); 

		Material* FindByPartNo(	// return NULL if not found.
			CString sPartNo, // Key material's Part No.
			Layer layer=EBOM::Unknown/*Ignored layer if layer = Unknown*/);	

		Material* FindBySubPartNo(	// return material which contians the sub-material. return NULL if not found.
			CString sSubPartNo, // Sub material's Part No.
			Layer layer=EBOM::Unknown/*Ignored layer if layer = Unknown*/);

		Material& operator[](UINT nIndex);

	private:
		vector<Material*> m_lstMaterials;	
	};

	//
	// EBOM中的料件信息
	//

	class GVDLL Material
	{
	public:
		 Material();
		~Material();
		friend class EBOM;

		void Clear();

		CString GetPartNo();
		CString GetVerify();
		CString GetDesc1();
		CString GetDesc2();
		CString GetVendor();
		CString GetVendorPartNo();		// Vendor PartNo. is empty in EBOM
		TypeM	GetType();
		Layer   GetLayer();

	public:
		MaterialCollection Subs;  // sub-materials
		LocationCollection Locations; // Symbol Locations
		
	protected:
		TypeM m_type;
		Layer m_layer;
		CString m_sPartNo;	// Material Part No.
		CString m_sVerify;	// Verify status.
		CString m_sDesc1;	// description 1 in BOM file
		CString m_sDesc2;	// description 2 in BOM file
		CString m_sVendor;	// Vendor	
		CString m_sVendorPartNo;
	};

public:
	 EBOM();
	~EBOM();
	friend class HwTool;

	void Clear();
	
	CString GetPCBVer();
	CString GetModelName();
	MaterialCollection Materials; // 在該列表中, 同一料號的料件可能會出現2次(用於區分正背板)

protected:
	CString Parse(CString sFile);

private:
	CString m_sModel;
	CString m_sPCBVer;
};


class GVDLL HwTool : public Base
{
public:
	static void CheckUser(CString sAppName);
	static void CheckAppVersion(CString AppName, CString AppVersion);

	bool ExecSqlCmdNonQuery(CString sSqlCmd);
	bool ExecSqlCmd(CString sSqlCmd, DataTable& dt);

	bool ParseEBOM(CString sBOMPath, EBOM& info); // full file path
};
}

#endif