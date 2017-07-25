#ifndef _GV_COM_DLL_LIVEUPDATE_H_
#define _GV_COM_DLL_LIVEUPDATE_H_

#include "Base.h"
#include "OS.h"

namespace Gv {

class GVDLL LiveUpdate : public Base
{
public:
	//
	// 顯卡工具類型
	//
	enum UTILITY { ATBIOS = 0, OCGURU_II };
	//
	// BIOS Update信息
	//
	struct GVDLL BIOS
	{
		CString sBiosVer;		// ex: F1
		CString sUpdateDate;	// ex: 2010-07-28
	};
	//
	// BIOS Update集合
	//
	class GVDLL BiosCollection
	{
	public:
		 BiosCollection();
		~BiosCollection();

		UINT Count();
		void Add(BIOS* pNew);
		void Clear();

		BIOS& operator[](UINT nIndex);

	private:
		vector<BIOS*> m_lstBioses;	
	};
	//
	// 官網機種名稱
	//
	struct GVDLL MODEL
	{
		CString sName;			// ex: GV-R667D3-2GI
		CString sTipTopName;	// ex: 9VR667D32I
	};
	//
	// 官網機種集合
	//
	class GVDLL ModelCollection
	{
	public:
		 ModelCollection();
		~ModelCollection();

		UINT Count();
		void Add(MODEL* pNew);
		void Clear();

		MODEL& operator[](UINT nIndex);

	private:
		vector<MODEL*> m_lstModels;	
	};
	//
	// 顯卡機種官網規格, 部分欄位可能空
	//
	struct GVDLL SPEC
	{
		CString sModelName;				// ex: GV-R667D3-2GI
		CString sProductId;				// Product id in gigabyte web site. ex: 4181
		CString sRevision;				// Model revision. ex: 1.1
		CString sChipset;				// ex: Radeon HD 6670
		CString sTools;					// Software tools supported.
		CString sCoreClock;				// ex: 800 MHz
		CString sMemoryClock;			// ex: 1600 MHz
		CString sShaderClock;			// ex: 2000 MHz
		CString sProcessTech;			// Process Technology. ex: 40 nm
		CString sMemorySize;			// ex: 2 GB
		CString sMemoryBus;				// ex: 128 bit
		CString sMemoryType;			// ex: DDR3
		CString sDirectX;				// DirectX version supported. ex: 11
		CString sOpenGL;				// OpenGL version supported. ex: 4.1
		CString sPCBForm;				// ex: ATX
		CString sIOPort;				// ex: HDMI * 1;DVI-D * 1;D-sub * 1;
		CString sDigitalMaxResolution;	// ex: 2560 x 1600
		CString sAnalogMaxResolution;	// ex: 2048 x 1536
		CString sMultiView;				// ex: 2
		CString sCardBus;				// ex: PCI-E 2.1
		CString sCardSize;				// ex: H=37.7 mm, L=211.8 mm, W=136.8 mm
		CString sPowerRequirement;		// ex: 400 W
	};


public: 
	 LiveUpdate();
	~LiveUpdate();

	// 
	// 說明: 以下函數中的sModelName參數必須為Model完整名稱, 如: GV-RX16P256D-RH
	//

	// 
	// 彈出更新嚮導頁面, 實現顯卡BIOS自動更新
	//
	static void BiosUpdate(CString sModelName, CString sCurBiosVer/*ex: F1*/);

	// 
	// 彈出更新嚮導頁面, 實現顯卡Driver自動更新
	//
	static void DriverUpdate(CString sModelName, CString sCurDrvVer/*ex: 8.671*/, CTime curDrvDate);

	// 彈出更新嚮導頁面, 實現指定工具自動更新
	//
	static void UtilityUpdate(UTILITY utility, OS::MODULE_VER curUtiVer);

	//
	// 獲取GIGABYTE官網上所有顯卡機種集合
	//
	bool GetModels(ModelCollection& lstModels);

	//
	// 獲取GIGABYTE官網指定機種的所有BIOS集合
	//
	bool GetBioses(CString sModelName, BiosCollection& lstBioses);

	//
	// 獲取官網上關於指定Model的規格說明
	//
	bool GetModelSpec(CString sModelName, CString sRevision/*PCB版本, 如1.1, 允許空*/, SPEC& modelSpec);

	//
	// 獲取官網上關於指定Model的產品URL
	//
	CString GetModelUrl(CString sModelName);

	//
	// 獲取官網上關於指定Model的FAQ URL
	//
	CString GetModelFAQUrl(CString sModelName);
};

}


#endif