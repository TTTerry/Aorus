#ifndef _GV_COM_DLL_DBMENUS_H_
#define _GV_COM_DLL_DBMENUS_H_

#include "Base.h"
#include "DataTable.h"

namespace Gv {

//
// 本類根據條件查詢KM_SYS_Menus菜單資料
//
class GVDLL Menus : public Base
{
public:

	//
	// KM系統菜單
	//
	class GVDLL Menu
	{
	friend class Menus;

	public:
		Menu();
	public:
		bool IsValid();		
		CString GetIdDB();	
		CString GetUrl();
		CString GetName();

	protected:
		bool m_bValid;		// 有效否
		CString m_sIdDB;	// 資料庫ID
		CString m_sUrl;		// 菜單鏈接
		CString m_sName;	// 菜單名稱
	};

	//
	// KM系統菜單集合
	//
	class GVDLL MenuCollection
	{
	public:
		 MenuCollection();
		~MenuCollection();

		UINT Count();
		void Add(Menu* pNew);
		void Clear();

		Menu& operator[](UINT nIndex);

	private:
		vector<Menu*> m_lstMenus;	
	};

	//
	// KM系統頁面, 頁面包含若干菜單
	//
	class GVDLL Page : public Menu
	{
	public:
		 Page();
		~Page();
		MenuCollection Menus;	// 頁面菜單集合
	}; 

	//
	// KM系統頁面集合
	//
	class GVDLL PageCollection
	{
	public:
		 PageCollection();
		~PageCollection();

		UINT Count();
		void Add(Page* pNew);
		void Clear();

		Page& operator[](UINT nIndex);

	private:
		vector<Page*> m_lstPages;	
	};

	//
	// KM子系統, 對應KM主頁的左邊菜單欄的某項目下的子項, 子系統包含若干頁面
	//
	class GVDLL SubSystem : public Menu
	{
	public:
		 SubSystem();
		~SubSystem();
		PageCollection Pages;	// 子系統頁面集合
	};

	//
	// KM子系統集合
	//
	class GVDLL SubSystemCollection
	{
	public:
		 SubSystemCollection();
		~SubSystemCollection();

		UINT Count();
		void Add(SubSystem* pNew);
		void Clear();

		SubSystem& operator[](UINT nIndex);

	private:
		vector<SubSystem*> m_lstSubSystems;	
	};

	//
	// KM系統, 對應KM主頁的左邊菜單欄的項目, 系統包含若干子系統
	//
	class GVDLL System : public Menu
	{
	public:
		 System();
		~System();
		SubSystemCollection SubSytems; // 系統中的子系統集合
	};

	//
	// KM系統集合, 對應KM主頁左邊菜單欄, 系統包含若干系統
	//
	class GVDLL SystemCollection
	{
	public:
		 SystemCollection();
		~SystemCollection();

		UINT Count(); 
		void Add(System* pNew);
		void Clear(); 

		System& operator[](UINT nIndex);

	private:
		vector<System*> m_lstSystems; // KM各系統集合	
	};

public:
	Menus(DB db);
	Menus(CString sConnectionString);  // connnection string
	Menus(CString sServer, CString sDB, CString sLogin, CString sPassword);

	// 
	// 說明: 
	// bHasPage: true表示查詢時結果包含子系統頁面
	// bHasMenu: true表示查詢時結果包含頁面菜單項
	// 

	bool QuerySubSystemById(CString sSubSysIdDB, SubSystem& subSystem, bool bHasMenu=false);	
	bool QuerySubSystemByName(CString sSubSysName/*完整子系統名稱*/, SubSystem& subSystem, bool bHasMenu=false);	
	bool QueryAllSystems(SystemCollection& lstSystems, bool bHasPage=false, bool bHasMenu=false);
	bool QuerySystemById(CString sSysIdDB, System& system, bool bHasPage=false, bool bHasMenu=false);	
	bool QuerySystemByName(CString sSysName/*完整系統名稱*/, System& system, bool bHasPage=false, bool bHasMenu=false);

private:
	void FillMenu(DataRow& row, Menu* pNew);

private:
	CString m_sConnection;
};

}

#endif