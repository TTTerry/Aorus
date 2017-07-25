#ifndef _GV_COM_DLL_DBMENUS_H_
#define _GV_COM_DLL_DBMENUS_H_

#include "Base.h"
#include "DataTable.h"

namespace Gv {

//
// ������l����ԃKM_SYS_Menus�ˆ��Y��
//
class GVDLL Menus : public Base
{
public:

	//
	// KMϵ�y�ˆ�
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
		bool m_bValid;		// ��Ч��
		CString m_sIdDB;	// �Y�ώ�ID
		CString m_sUrl;		// �ˆ�朽�
		CString m_sName;	// �ˆ����Q
	};

	//
	// KMϵ�y�ˆμ���
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
	// KMϵ�y���, ���������ɲˆ�
	//
	class GVDLL Page : public Menu
	{
	public:
		 Page();
		~Page();
		MenuCollection Menus;	// ���ˆμ���
	}; 

	//
	// KMϵ�y��漯��
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
	// KM��ϵ�y, ����KM��퓵���߅�ˆΙڵ�ĳ�Ŀ�µ����, ��ϵ�y�����������
	//
	class GVDLL SubSystem : public Menu
	{
	public:
		 SubSystem();
		~SubSystem();
		PageCollection Pages;	// ��ϵ�y��漯��
	};

	//
	// KM��ϵ�y����
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
	// KMϵ�y, ����KM��퓵���߅�ˆΙڵ��Ŀ, ϵ�y����������ϵ�y
	//
	class GVDLL System : public Menu
	{
	public:
		 System();
		~System();
		SubSystemCollection SubSytems; // ϵ�y�е���ϵ�y����
	};

	//
	// KMϵ�y����, ����KM�����߅�ˆΙ�, ϵ�y��������ϵ�y
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
		vector<System*> m_lstSystems; // KM��ϵ�y����	
	};

public:
	Menus(DB db);
	Menus(CString sConnectionString);  // connnection string
	Menus(CString sServer, CString sDB, CString sLogin, CString sPassword);

	// 
	// �f��: 
	// bHasPage: true��ʾ��ԃ�r�Y��������ϵ�y���
	// bHasMenu: true��ʾ��ԃ�r�Y���������ˆ��
	// 

	bool QuerySubSystemById(CString sSubSysIdDB, SubSystem& subSystem, bool bHasMenu=false);	
	bool QuerySubSystemByName(CString sSubSysName/*������ϵ�y���Q*/, SubSystem& subSystem, bool bHasMenu=false);	
	bool QueryAllSystems(SystemCollection& lstSystems, bool bHasPage=false, bool bHasMenu=false);
	bool QuerySystemById(CString sSysIdDB, System& system, bool bHasPage=false, bool bHasMenu=false);	
	bool QuerySystemByName(CString sSysName/*����ϵ�y���Q*/, System& system, bool bHasPage=false, bool bHasMenu=false);

private:
	void FillMenu(DataRow& row, Menu* pNew);

private:
	CString m_sConnection;
};

}

#endif