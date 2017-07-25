#pragma once

#define KEY_ROW 6
#define KEY_COL	21
#define MEM_SIZE 0x11000

#define DEF_MEM_ADDR 0x20000
#define LED_START_MEM_ADDR 0x30000
#define DEF_MEM_TYPE  1
#define LED_START_MEM_TYPE  2

#define MAX_PROFILE_COUNT		5


class CKbLedCtrl
{
public:
	CKbLedCtrl(void);
	~CKbLedCtrl(void);

	static void LoadMemory();
	static void LoadProfileClrList(int nProfile);
	static void ResetClrList(int nProfile);

	static void GetMarcoList(GVORDER_MACROS_ATTR lstmacros[], int nCount);
	static void SetMacrosKey(GVORDER_MACROS macros);
	static void GetMacrosKey(GVORDER_MACROS& macros);
	static void SetKeyFunToDefault(int nProfile);
	static void SetKeyFun(GVORDER_KEYFUN fnkey);
	static void GetKeyFun(GVORDER_KEYFUN& fnkey);

	static void ToConsistent(bool bStatus[], COLORREF clr, int nBright, int nSpeed, bool bOn, int nProfile);
	static void ToPulsing(bool bStatus[], COLORREF clr1, COLORREF clr2, int nBright, int nSpeed, bool bRandom, bool bOn, int nProfile);
	static void ToReactive(bool bStatus[],  COLORREF clr, int nSpeed, int nProfile);
	static void ToRipple(bool bStatus[], int nWidth, int nStart, int nTimes, COLORREF clrs[], int nCount, int nSpeed, int nProfile, bool bOn);
	static void ToCycling(bool bStatus[], int nBright, int nSpeed, bool bOn, int nProfile);
	static void ToWave(bool bStatus[], int nAngle, COLORREF clr[], int nCount, bool bOn, int nBright, int nSpeed, int nProfile);
	static void ToWave(bool bStatus[], int nAngle, COLORREF clr[], int nCount, bool bOn, int nBright, int nSpeed, int start, int time, int nProfile);


	static void GetSelItem(/* out */bool bSels[KEY_ROW][KEY_COL], /* in */bool bStatus[], int nCount = KEYCOUNT);
	static void Wave(int profile, int nAngle, int nClr, int nBright, int nSpeed, COLORREF clr[], int nCount);
	static void FormToColor(COLORREF from, COLORREF to, int count, BYTE* byDefault, DWORD *Index);
	static void FormToColor(COLORREF from, COLORREF to, int count, COLORREF clr[]);
	static void CKbLedCtrl::GetWaveByte(int nAngle, BYTE* byMem);
	static bool SetClr(int i, int j, int nClr);
	static bool CKbLedCtrl::SetClr(int i, int j, int nClr, int nKey[KEY_ROW][KEY_COL]);
	static bool SaveMemery(int nProfile, CString file);  //保存Memory到本地
	static bool ReadMemeryToSet(int nProfile, CString file);  //读写本地Memory，并保存
	static void DeleteDefineProfile(int nProfile);    //删除本地自定义Memory
	static void DeleteProfile(int nProfile);    //删除本地Profile Memory
	static void Default(BYTE nProfile);

	static void CKbLedCtrl::EnableKeyType(bool keyType);  //键盘类型标志位
	static CString GetCfgPath(int nProfile);


	static bool m_bIsSave;       //下一次ToByte不发送,主要用于合并多次设置操作
	static bool m_bIsKeyType;          //设置键盘类型，使用m_dwKTClrLastAddr
	static DWORD m_dwKTClrLastAddr;     
	static DWORD m_nKTClrList; //当选择键盘类型时，不递增m_nClrList列表索引
	static DWORD m_dwKTRippleLastAddr;

	static BYTE m_Memory[MEM_SIZE];
	static BYTE m_LedMemory[MEM_SIZE];
	static BYTE m_LedValueMemory[MEM_SIZE];

	//当是设置键盘类型时，用下面两个临时数组
	static BYTE m_LedMemoryKT[0x2000];   
	static BYTE m_LedValueMemoryKT[0x1000];
	static BYTE m_RippleMemoryKT[0x1000];

private:
	static void CKbLedCtrl::ToByte(int nClrCount, int nTimer, int nClrIndex, int nSpeed, int nProfile);
	static void DeleteDirectory(CString directory_path);

	static int m_nClrList[5];                 //profile 1 ~ 5
	//是否设定具体键盘类型

	static int m_nClrCount;
	static bool m_isReadLedMem;
	static bool m_isReadValueMem;
	static DWORD m_dwClrLastAddr[MAX_PROFILE_COUNT];

	static DWORD m_dwDefineRippleLastAddr;
	static DWORD m_DefineWaveIndex[5];         //profile 1 ~ 5
	static DWORD m_DefineRippleIndex[5];       //profile 1 ~ 5 rippleDefine_Flag  
};
