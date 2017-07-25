#ifndef _GV_COM_DLL_LIVEUPDATE_H_
#define _GV_COM_DLL_LIVEUPDATE_H_

#include "Base.h"
#include "OS.h"

namespace Gv {

class GVDLL LiveUpdate : public Base
{
public:
	//
	// �@���������
	//
	enum UTILITY { ATBIOS = 0, OCGURU_II };
	//
	// BIOS Update��Ϣ
	//
	struct GVDLL BIOS
	{
		CString sBiosVer;		// ex: F1
		CString sUpdateDate;	// ex: 2010-07-28
	};
	//
	// BIOS Update����
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
	// �پW�C�N���Q
	//
	struct GVDLL MODEL
	{
		CString sName;			// ex: GV-R667D3-2GI
		CString sTipTopName;	// ex: 9VR667D32I
	};
	//
	// �پW�C�N����
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
	// �@���C�N�پWҎ��, ���֙�λ���ܿ�
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
	// �f��: ���º����е�sModelName������횞�Model�������Q, ��: GV-RX16P256D-RH
	//

	// 
	// �������������, ���F�@��BIOS�ԄӸ���
	//
	static void BiosUpdate(CString sModelName, CString sCurBiosVer/*ex: F1*/);

	// 
	// �������������, ���F�@��Driver�ԄӸ���
	//
	static void DriverUpdate(CString sModelName, CString sCurDrvVer/*ex: 8.671*/, CTime curDrvDate);

	// �������������, ���Fָ�������ԄӸ���
	//
	static void UtilityUpdate(UTILITY utility, OS::MODULE_VER curUtiVer);

	//
	// �@ȡGIGABYTE�پW�������@���C�N����
	//
	bool GetModels(ModelCollection& lstModels);

	//
	// �@ȡGIGABYTE�پWָ���C�N������BIOS����
	//
	bool GetBioses(CString sModelName, BiosCollection& lstBioses);

	//
	// �@ȡ�پW���P�ָ��Model��Ҏ���f��
	//
	bool GetModelSpec(CString sModelName, CString sRevision/*PCB�汾, ��1.1, ���S��*/, SPEC& modelSpec);

	//
	// �@ȡ�پW���P�ָ��Model�ĮaƷURL
	//
	CString GetModelUrl(CString sModelName);

	//
	// �@ȡ�پW���P�ָ��Model��FAQ URL
	//
	CString GetModelFAQUrl(CString sModelName);
};

}


#endif