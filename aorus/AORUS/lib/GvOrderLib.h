#ifndef GV_ORDERLIB_H
#define GV_ORDERLIB_H


#ifdef  GV_ORDERLIB_EXPORTS
#define GV_ORDERLIB_API __declspec(dllexport)
#else
#define GV_ORDERLIB_API __declspec(dllimport)
#endif

#define GVORDER_DEVICE_MAX	20

#define GVAPI_OK					0x00000000
#define GVAPI_CMDERR_FAILED			0x20000001	// Unknown Error
#define GVAPI_CMDERR_ERR_PARAM		0x20000002	// invalid parameter
#define GVAPI_CMDERR_ERR_NOBOARD	0x20000003	// no boards found
#define GVAPI_CMDERR_NOHID			0x20000004	// no HID found
#define GVAPI_CMDERR_DEVNOFOUND		0x20000005	// device not found
#define GVAPI_CMDERR_DEVNOOPEN		0x20000006	// device not open
#define GVAPI_CMDERR_CONNECT		0x20000007	// connect device failed
#define GVAPI_CMDERR_DISCONNECT		0x20000008	// disconnect device failed
#define GVAPI_CMDERR_SENDDATA		0x20000009	// send data failed
#define GVAPI_FWERR_IMPORT			0x20000010	// Import Marco Error
#define GVAPI_FWERR_EXPORT			0x20000011	// Export Marco Error
#define GVAPI_CMDERR_RECVDATA		0x2000000A	// receive data failed
#define GVAPI_CMDERR_NOINIT			0x2000000B	// Fireware havn't Init

//////////////////////////////////////////////////////////////////////////
/// 灯号矩阵游戏类型
typedef enum _GVORDER_MATRIX_GAME
{
	GVORDER_MATRIX_NONE = -1,
	GVORDER_MATRIX_FPS = 0,
	GVORDER_MATRIX_MMO,
	GVORDER_MATRIX_MOBA,
	GVORDER_MATRIX_RTS,
	GVORDER_MATRIX_CSGO,
	GVORDER_MATRIX_DOTAII,
	GVORDER_MATRIX_LOL,
	GVORDER_MATRIX_STARCRAFTII,
	GVORDER_MATRIX_DEFINE,

}GVORDER_MATRIX_GAME, *PGVORDER_MATRIX_GAME;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 设备ID结构体
typedef struct _GVORDER_DEVICE
{
	DWORD dwVID;
	DWORD dwPID;
	DWORD dwHID;

} GVORDER_DEVICE, *PGVORDER_DEVICE;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 灯号矩阵游戏类型
typedef enum _GVORDER_LED_MODE
{
	GVORDER_LED_CONSISTENT = 1, // 恆亮
	GVORDER_LED_BREATHING,		// 呼吸
	GVORDER_LED_CYCLING,		// 顔色循環
	GVORDER_LED_SINGLETWINKLE,
	GVORDER_LED_TWICETWINKLE,
	GVORDER_LED_OFF,			// 顔色關閉

}GVORDER_LED_MODE, *PGVORDER_LED_MODE;

//////////////////////////////////////////////////////////////////////////
/// Profile设定值
typedef struct _GVORDER_STATUS
{
	int  nProfile;
	bool bBackLight;  // 是否背光，true表示燈亮，false表示off
	bool bEnable;	  // 是否啓用
	int  nBrightness; // 亮度 0~10
	int  nSpeed;	  // 速度 0~5
	COLORREF clr;	  // Profile顔色
	GVORDER_LED_MODE nBeathType; // 呼吸模式

} GVORDER_PROFILE, *PGVORDER_STATUS;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LED配置
#define GVORDER_LED_TYPE	0x00001
#define GVORDER_LED_BRIGHT	0x00002
#define GVORDER_LED_SPEED	0x00004
#define GVORDER_LED_BASE	((GVORDER_LED_TYPE)|(GVORDER_LED_BRIGHT)|(GVORDER_LED_SPEED))
#define GVORDER_LED_COLOR	0x00008
#define GVORDER_LED_ALL		0xFFFFF

#define GVORDER_CLR_MAX 10
typedef struct _GVORDER_LED_CFG
{
	GVORDER_LED_MODE type;
	int nBright;
	int nSpeed;
	int nClrCount; // 顏色數組，有可能有雙色呼吸，如果燈光模式是七色循環，則為7，恆亮為1，呼吸可能為1可能為2(雙色呼吸)
	COLORREF clrArray[GVORDER_CLR_MAX];

}GVORDER_LED_CFG, *PGVORDER_LED_CFG;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// DPI设定值
typedef struct _GVORDER_DPI
{
	int nIndex;		// Dpi Index
	int nX;
	int nY;

} GVORDER_DPI, *PGVORDER_DPI;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LED设定值 For K7
typedef struct _GVORDER_LED
{
	int nProfile;
	COLORREF clrRGB;	// 顔色
	int  nBrightLight;  // if > 128, it's breath
	GVORDER_MATRIX_GAME Matrix; // 亮度矩陣
	int nLight;

} GVORDER_LED, *PGVORDER_LED;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 左右滾輪模式
typedef enum _GVORDER_TILT_TYPE
{
	GVORDER_TILT_TYPE_HW = 1,	// 硬件模式
	GVORDER_TILT_TYPE_SW,		// 軟件模式，硬件HID消息：0xBC

}GVORDER_TILT_TYPE, *PGVORDER_TILT_TYPE;

#define GVORDER_TILT_MSG	0xBC
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 多媒體鍵
typedef enum _GVORDER_MEDIA_KEY
{
	GVORDER_MEDIA_BROWSER = 0,		// 瀏覽器
	GVORDER_MEDIA_VOLUP,			// 音量變大
	GVORDER_MEDIA_VOLDOWN,			// 音量變小
	GVORDER_MEDIA_CACULATOR,		// 計算器
	GVORDER_MEDIA_PLAY,				// 音樂播放
	GVORDER_MEDIA_STOP,				// 音樂停止
	GVORDER_MEDIA_NEXT,				// 下一首
	GVORDER_MEDIA_PREV,				// 上一首
	GVORDER_MEDIA_EMAIL,			// 郵箱
	GVORDER_MEDIA_COMPUTER,			// 我的電腦
	GVORDER_MEDIA_MEDIAPLAYER,		// MeidaPlay
	GVORDER_MEDIA_SLEEP,			// 睡眠
	GVORDER_MEDIA_MUTE,				// 靜音
	GVORDER_MEDIA_QTY,				// 多媒體鍵定義數量

}GVORDER_MEDIA_KEY, *PGVORDER_MEDIA_KEY;

//////////////////////////////////////////////////////////////////////////
/// 鼠標鍵，與Mouse Key Code對應
typedef enum _GVORDER_MOUSE_KEY
{
	GVORDER_MOUSE_LEFT = 1,		// 左
	GVORDER_MOUSE_RIGHT = 2,	// 右
	GVORDER_MOUSE_MIDDLE = 4,	// 中
	GVORDER_MOUSE_KEY4 = 8,		// 4鍵（側邊鍵）
	GVORDER_MOUSE_KEY5 = 10,	// 5鍵（側邊鍵）

}GVORDER_MOUSE_KEY, *PGVORDER_MOUSE_KEY;

//////////////////////////////////////////////////////////////////////////
/// 按鍵替換函數定義
typedef enum _GVORDER_FUNCTION_TYPE
{
	GVORDER_FUN_DEFAULT = 0,		// 默認
	GVORDER_FUN_NONE,				// 無函數
	GVORDER_FUN_MOUSE,				// 鼠標
	GVORDER_FUN_KEYBOARD,			// 鍵盤
	GVORDER_FUN_MOUSELOOP,			// 鼠標連擊
	GVORDER_FUN_KEYLOOP,			// 鍵盤連擊
	GVORDER_FUN_MACROSONCE,			// 巨集執行一次
	GVORDER_FUN_MACROSLOOP,			// 巨集按下放開後循環執行，再按下放開後停止
	GVORDER_FUN_MACROCSFIRE,		// 巨集按下後循環執行，放開即停止
	GVORDER_FUN_FIREDPI,			// 指定DPI(按下後切換DPI  放開後回復原DPI)
	GVORDER_FUN_SWITCHDPI,			// 指定DPI(按下放開後切換DPI  再按下放開回復原DPI)
	GVORDER_FUN_PLUSDPI,			// DPI+
	GVORDER_FUN_SUBDPI,				// DPI-
	GVORDER_FUN_LOOPDPI,			// DPI循環切換
	GVORDER_FUN_SWITCHPRO,			// Profile循環切換
	GVORDER_FUN_MEDIA,				// 多媒體鍵
	GVORDER_FUN_LOCKXY,				// 鎖定XY，1爲鎖定，0爲放開
	GVORDER_FUN_GHOST,				// Ghost鍵，硬件HID消息：0xBF
	GVORDER_FUN_APP,
}GVORDER_FUNCTION_TYPE, *PGVORDER_FUNCTION_TYPE;

#define GVORDER_GHOST_MSG	0xBF

//////////////////////////////////////////////////////////////////////////
/// 按鍵函數
typedef struct _GVORDER_KEYFUN
{
	int nIndex;		// 按鍵Index
	int nProfile;	// 所屬Profile
	GVORDER_FUNCTION_TYPE fnType;	// 按鍵函數類型
	union{
		struct
		{
			BYTE msbutton;	// 按鍵 對應 GVORDER_MOUSE_KEY
			BYTE wheelcount;// 鼠標剩下滾輪 0x01 向上，0xff 向下
			BYTE tiltcount; // 鼠標左右滾輪 0x01 向左，0xff 向右
		}mouse;		// 鼠標 GVORDER_FUN_MOUSE

		struct
		{
			// Ctrl - VK_LCTRL/VK_RCTRL; Alt - VK_LMENU/VK_RMENU; Shift - VK_LSHIFT/VK_RSHIFT; Win - VK_LWIN/VK_RWIN
			BYTE keyModifier;
			BYTE keyCode; // VKeyCode

		}keyboard; // 鍵盤 GVORDER_FUN_KEYBOARD

		struct
		{
			BYTE msbutton;  // 按鍵 對應 GVORDER_MOUSE_KEY
			BYTE times;		// 次數
			BYTE delay;		// delay時間
		}mouseloop; // 鼠標連擊 GVORDER_FUN_MOUSELOOP

		struct
		{
			BYTE keyCode;   // key Code
			BYTE times;		// 次數
			BYTE delay;		// delay時間
		}keyloop; // 鍵盤連擊 GVORDER_FUN_KEYLOOP

		struct
		{
			WORD macrosIndex;  // Marco Index
			BYTE type;		   // 巨集類型 GVORDER_MACROS_RUN

		}macros; // Marco key GVORDER_FUN_MACROSONCE/GVORDER_FUN_MACROSLOOP/GVORDER_FUN_MACROCSFIRE

		struct  
		{
			BYTE x; 
			BYTE y;
			BYTE ms; // only GVORDER_FUN_FIREDPI
		}dpi;	// DPI GVORDER_FUN_FIREDPI/GVORDER_FUN_SWITCHDPI

		struct
		{
			GVORDER_MEDIA_KEY key; // 媒體鍵
		}media; // 媒體鍵Function GVORDER_FUN_MEDIA

		struct
		{
			BYTE x; // 1 = lock, 0 = unlock
			BYTE y;
		}lock;	// 鎖定DPI GVORDER_FUN_LOCKXY

		struct
		{
			int nProfile;
		}profile;
	}value;

}GVORDER_KEYFUN, *PGVORDER_KEYFUN;

//////////////////////////////////////////////////////////////////////////
/// 巨集指令类型
typedef enum _GVORDER_MACROS_TYPE
{
	GVORDER_MACROS_KEYBOARDUP = 0,	// 按鍵向上
	GVORDER_MACROS_KEYBOARDOWN,		// 按鍵向下
	GVORDER_MACROS_MEDIAUP,			// 多媒體鍵向上
	GVORDER_MACROS_MEDIADOWN,		// 多媒體鍵向下
	GVORDER_MACROS_MOUSEUP,			// 鼠標向上
	GVORDER_MACROS_MOUSEDOWN,		// 鼠標向下
	GVORDER_MACROS_MOUSEX,			// 鼠標坐標X
	GVORDER_MACROS_MOUSEY,			// 鼠標坐標Y
	GVORDER_MACROS_SCROLLUP,		// 鼠標滾輪上
	GVORDER_MACROS_SCROLLDOWN,		// 鼠標滾輪下
	GVORDER_MACROS_DELAY,			// 時間Delay

} GVORDER_MACROS_TYPE, *PGVORDER_MACROS_TYPE;

//////////////////////////////////////////////////////////////////////////
/// 巨集设定單元
#define GVORDER_MACROS_MAX	192 // 最多可包含單元 = 0x0240（Marco Size） / 3 （Unit Size）
typedef struct _GVORDER_MACROS_UNIT
{
	GVORDER_MACROS_TYPE nType;
	DWORD dwValue;

} GVORDER_MACROS_UNIT, *PGVORDER_MACROS_UNIT;

//////////////////////////////////////////////////////////////////////////
/// 巨集執行模式
typedef enum _GVORDER_MACROS_RUN
{
	GVORDER_MACROS_EXEC = 0,	// 執行一次
	GVORDER_MACROS_LOOP,		// 按下放開後循環執行，再按下放開後停止
	GVORDER_MACROS_FIRE,		// 按下後循環執行，放開即停止

}GVORDER_MACROS_RUN, *PGVORDER_MACROS_RUN;

//////////////////////////////////////////////////////////////////////////
/// 巨集時間錄製模式
typedef enum _GVORDER_MACROS_TIME
{
	GVORDER_MACROS_AUTO = 0,	// 默認，與實際時間一致
	GVORDER_MACROS_FIXEDTIME,	// 固定時間
	GVORDER_MACROS_NONE,		// 不記錄時間

}GVORDER_MACROS_TIME, *PGVORDER_MACROS_TIME;

//////////////////////////////////////////////////////////////////////////
/// 巨集屬性
typedef struct _GVORDER_MACROS_ATTR
{
	int nIcon;						// 所使用的Icon Index
	GVORDER_MACROS_RUN  RunType;	// 運行模式
	GVORDER_MACROS_TIME TimeMode;	// 時間模式
	TCHAR szName[15];				// 名字

} GVORDER_MACROS_ATTR, *PGVORDER_MACROS_ATTR;

//////////////////////////////////////////////////////////////////////////
/// 巨集主體
typedef struct _GVORDER_MACROS
{
	int nIndex;										// 巨集索引
	int nCount;										// 巨集單元數量
	GVORDER_MACROS_ATTR attr;						// 巨集屬性
	GVORDER_MACROS_UNIT macros[GVORDER_MACROS_MAX]; // 巨集單元數組
	void Insert(GVORDER_MACROS_UNIT nMacro, int iIdx)
	{
		for (int i = nCount; i > iIdx; i--)
			macros[i] = macros[i - 1];
		macros[iIdx] = nMacro;
		nCount++;
	}
	void Append(GVORDER_MACROS_UNIT nMacro, int iIdx)
	{
		nCount++;
		for (int i = nCount; i >  iIdx; i--)
			macros[i + 1] = macros[i];
		macros[iIdx + 1] = nMacro;
	}
} GVORDER_MACROS, *PGVORDER_MACROS;
///
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// LoadMemory參數
typedef enum _GVORDER_DEVICE_TYPE
{
	GVORDER_DEVICE_KEYBOARD = 0,	// 鍵盤
	GVORDER_DEVICE_MOUSE,			// 鼠標
	GVORDER_DEVICE_HEADSET,			// 耳機
	GVORDER_DEVICE_POWER,			// 電源
	GVORDER_DEVICE_CHASSIS,			// 機箱

}GVORDER_DEVICE_TYPE, *PGVORDER_DEVICE_TYPE;

typedef struct _GVORDER_MEMORY_PARAM
{
	GVORDER_DEVICE_TYPE type;
	int nProfileCount;
	int nMarcoCount;

} GVORDER_MEMORY_PARAM, *PGVORDER_MEMORY_PARAM;
///
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

	/****************************************************************************************
	 * 功能描述：
	 * 初始化設備
	 *
	 * 输入参数：
	 * [in]  device      所要連接裝置的屬性
	 * [out] nIndex      返回設備Index，相同ID具備相同Index
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_FWERR_ERR_NOBOARD表示沒有找到裝置；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderInit(GVORDER_DEVICE device, int& nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 加載設備Flash部分數據到緩存區，建議寫在綫程中，加載完畢再開始軟體各方面的操作
	 *
	 * 输入参数：
	 * [in]  param       加載參數
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderLoadMemory(GVORDER_MEMORY_PARAM param, int& nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 釋放設備資源
	 *
	 * 输入参数：
	 * [in]  nIndex      設備Index
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderFree(int nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取該設備ID共有幾個裝置
	 *
	 * 输入参数：
	 * [in]  nIndex      設備Index
	 * [out] nCount      裝置數量
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceCount(int nIndex, int& nCount);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取裝置FW版本
	 *
	 * 输入参数：
	 * [out] szVersion   FW版本字符串   
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderVersionW(wchar_t* szVersion, int nIndex, int nBrd = 0);
	GV_ORDERLIB_API DWORD GvOrderVersionA(char* szVersion, int nIndex, int nBrd = 0);

#ifdef _UNICODE
#define GvOrderVersion GvOrderVersionW
#else
#define GvOrderVersion GvOrderVersionA
#endif

	/****************************************************************************************
	 * 功能描述：
	 * 切換Profile
	 *
	 * 输入参数：
	 * [in]  nProfile    Profile Index   
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSelProfile(int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取當前Profile資訊
	 *
	 * 输入参数：
	 * [out] profile     Profile資訊   
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetCurProfile(GVORDER_PROFILE& profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 切換DPI
	 *
	 * 输入参数：
	 * [in]  nDpiIndex   DPI Index   
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSelDPI(int nDpiIndex, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取當前DPI
	 *
	 * 输入参数：
	 * [out] dpi		 DPI信息
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetCurDPI(GVORDER_DPI& dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 應用設定，已棄用
	 *
	 * 输入参数：
	 * [in]  nProfile    應用Profile
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderApply(int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設置ReportRate
	 *
	 * 输入参数：
	 * [in]  nReportRate ReportRate
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetReportRate(int nReportRate, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取當前ReportRate
	 *
	 * 输入参数：
	 * [out] nReportRate ReportRate
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetReportRate(int& nReportRate, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設置Profile
	 *
	 * 输入参数：
	 * [in]  profile     Profile信息
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetProfile(GVORDER_PROFILE profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取Profile
	 *
	 * 输入参数：
	 * [in]  profile     Profile信息，需預先賦值Index
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetProfile(GVORDER_PROFILE& profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設置指定Index DPI
	 *
	 * 输入参数：
	 * [in]  dpi		 DPI
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetDPI(GVORDER_DPI dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 讀取指定Index DPI
	 *
	 * 输入参数：
	 * [out] dpi		 DPI，需預先賦值Index
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetDPI(GVORDER_DPI& dpi, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設定Led模式，For K7
	 *
	 * 输入参数：
	 * [in]  led		 LED模式
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetLed(GVORDER_LED led, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 讀取Led模式，For K7
	 *
	 * 输入参数：
	 * [out] led		 LED模式
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetLed(GVORDER_LED& led, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設置按鍵Funtion
	 *
	 * 输入参数：
	 * [in]  fnkey		 按鍵Function
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyMapping(GVORDER_KEYFUN fnkey, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設置按鍵Funtion
	 *
	 * 输入参数：
	 * [in]  fnkey		 按鍵Function
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyMappingDefault(int nProfile, GVORDER_DEVICE_TYPE type, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 讀取按鍵Funtion
	 *
	 * 输入参数：
	 * [out] fnkey		 按鍵Function
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetKeyMapping(GVORDER_KEYFUN& fnkey, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設定指定地址function，For K7
	 *
	 * 输入参数：
	 * [out] fnkey		 按鍵Function
	 * [in]  dwAddr      地址
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyToAddr(GVORDER_KEYFUN fnkey, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設定Marco Key
	 *
	 * 输入参数：
	 * [in]  macros		 巨集鍵
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetMacrosKey(GVORDER_MACROS macros, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取Marco Key
	 *
	 * 输入参数：
	 * [out] macros		 獲取巨集鍵，需預先賦值Index
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosKey(GVORDER_MACROS& macros, int nIndex, int nBrd = 0);
	GV_ORDERLIB_API DWORD GvOrderGetMacrosList(GVORDER_MACROS_ATTR lstmacros[], int nCount, int nIndex, int nBrd = 0);

	//////////////////////////////////////////////////////////////////////////
	/// 未實現
	GV_ORDERLIB_API DWORD GvOrderTranslateKey(RAWKEYBOARD keyEvent, GVORDER_MACROS_UNIT& keyValue);
	GV_ORDERLIB_API DWORD GvOrderGetMacrosKeyLength(GVORDER_MACROS& macros, int& nLength);
	///
	//////////////////////////////////////////////////////////////////////////

	/****************************************************************************************
	 * 功能描述：
	 * 寫入Byte到指定地址，最大長度爲64
	 *
	 * 输入参数：
	 * [in]  pBytes		 要寫入的Byte
	 * [in]  nLen		 要寫入的長度
	 * [in]  dwAddr		 要寫入的地址
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderWriteByte(BYTE* pBytes, int nLen, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 從指定地址讀取Byte，最大長度爲64
	 *
	 * 输入参数：
	 * [out] pBytes		 存放讀取的Byte的緩存區
	 * [in]  nLen		 要讀取的長度
	 * [in]  dwAddr		 要讀取的地址
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderReadByte(BYTE* pBytes, int& nLen, DWORD dwAddr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設定左右滾動模式
	 *
	 * 输入参数：
	 * [in]  tilt		 左右滾動模式
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetScrollType(GVORDER_TILT_TYPE tilt, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 設定Profile顔色
	 *
	 * 输入参数：
	 * [in]  clr		 要設定的顔色
	 * [in]  nProfile	 要設定的Profile
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetProfileClr(COLORREF clr, int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 同步設備顔色
	 *
	 * 输入参数：
	 * [in]  clr		 要同步的顔色
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSyncClr(COLORREF clr, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 讀取Profile顔色
	 *
	 * 输入参数：
	 * [out] clr		 讀取到的顔色
	 * [in]  nProfile	 要設定的Profile
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetProfileClr(COLORREF& clr, int nProfile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 從文件中導出Marco Key
	 *
	 * 输入参数：
	 * [in]  macros		marco key
	 * [in]  szPath		保存路徑
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderImportMarcoW(GVORDER_MACROS& macros, const wchar_t* szPath);
	GV_ORDERLIB_API DWORD GvOrderImportMarcoA(GVORDER_MACROS& macros, const char* szPath);

#ifdef _UNICODE
#define GvOrderImportMarco GvOrderImportMarcoW
#else
#define GvOrderImportMarco GvOrderImportMarcoA
#endif

	/****************************************************************************************
	 * 功能描述：
	 * 導出Marco到文件中
	 *
	 * 输入参数：
	 * [in]  macros		marco key
	 * [in]  szPath		保存路徑
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderExportMarcoW(GVORDER_MACROS macros, const wchar_t* szPath);
	GV_ORDERLIB_API DWORD GvOrderExportMarcoA(GVORDER_MACROS macros, const char* szPath);

#ifdef _UNICODE
#define GvOrderExportMarco GvOrderExportMarcoW
#else
#define GvOrderExportMarco GvOrderExportMarcoA
#endif

	/****************************************************************************************
	 * 功能描述：
	 * 鎖定FW發送指令功能，防止與FW溝通過程由於用戶觸發導致崩潰
	 *
	 * 输入参数：
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceLock(int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 解鎖FW發送指令功能
	 *
	 * 输入参数：
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderDeviceUnLock(int& nProfile, int& nDpiIndex, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 即使變更Led顯示，For XM300
	 *
	 * 输入参数：
	 * [in]  profile     Profile設定
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderChangeLed(GVORDER_PROFILE profile, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 及時變更Led顯示模式，For K85/XH300/XC700/CPU Cooler
	 *
	 * 输入参数：
	 * [in]  config      Led設定
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetLight(GVORDER_LED_CFG  config, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取Led顯示模式，For K85/XH300/XC700/CPU Cooler
	 *
	 * 输入参数：
	 * [out] config      Led設定
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetLight(GVORDER_LED_CFG& config, int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 保存Led設定，For K85/XH300/XC700/CPU Cooler
	 *
	 * 输入参数：
	 * [in]  nIndex      設備Index
	 * [in]  nBrd        裝置索引
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSaveLight(int nIndex, int nBrd = 0);

	/****************************************************************************************
	 * 功能描述：
	 * 將二進制碼轉爲Marco Key List，Fro XK700
	 *
	 * 输入参数：
	 * [in]  pAttr			數據Byte
	 * [out] lstmacros      Marco List
	 * [in]  nCount			最大數量
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosListFromByte(BYTE* pAttr, GVORDER_MACROS_ATTR lstmacros[], int nCount);

	/****************************************************************************************
	 * 功能描述：
	 * 將二進制碼轉爲Marco Key，Fro XK700
	 *
	 * 输入参数：
	 * [in]  pUnit			Marco數據Byte
	 * [in]  pAttr			Marco屬性Byte
	 * [out] macros			Macro Key
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetMacrosFromByte(BYTE* pUnit, BYTE* pAttr, GVORDER_MACROS& macros);

	/****************************************************************************************
	 * 功能描述：
	 * 將Marco Key轉爲二進制碼，Fro XK700
	 *
	 * 输入参数：
	 * [in]  pUnit			Marco數據Byte
	 * [in]  pAttr			Marco屬性Byte
	 * [in]  macros			Macro Key
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetMacrosToByte(BYTE* pUnit, BYTE* pAttr, GVORDER_MACROS macros);

	/****************************************************************************************
	 * 功能描述：
	 * 將二進制碼轉爲Key Fun， Fro XK700
	 *
	 * 输入参数：
	 * [in]  pUnit			Key Function Byte
	 * [out] keyfun			Key Function
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderGetKeyFunFromByte(BYTE* pUnit, GVORDER_KEYFUN& keyfun);

	/****************************************************************************************
	 * 功能描述：
	 * 將Key Fun轉爲二進制碼， Fro XK700
	 *
	 * 输入参数：
	 * [in]  pUnit			Key Function Byte
	 * [in]  keyfun			Key Function
	 * 
	 * 返回值：
	 * 返回GVAPI_OK表示调用成功；GVAPI_CMDERR_DEVNOFOUND表示尚未Init；
	 ****************************************************************************************/
	GV_ORDERLIB_API DWORD GvOrderSetKeyFunToByte(BYTE* pUnit, GVORDER_KEYFUN keyfun);


#ifdef __cplusplus
}
#endif

#endif
