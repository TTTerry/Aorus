#ifndef GV_GVLEDLIB_H
#define GV_GVLEDLIB_H

#ifdef GVLEDLIB_EXPORTS
#define GVLEDLIB_API __declspec(dllexport)
#else
#define GVLEDLIB_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
/// Led燈光模式，For XH300/XC300/XC700/XTC300/XM300
#define TYPE_BRIGHT		1	// 恒亮
#define TYPE_BREATH		2	// 呼吸
#define TYPE_CYCLING	3	// 多彩循环

//////////////////////////////////////////////////////////////////////////
/// Led設置參數，For XH300/XC300/XC700/XTC300
typedef struct _GVLED_XCFG
{
	int nType;				// Led 类型
	int nBright;			// 亮度 1~10
	int nSpeed;				// 速度 1~10
	unsigned long clr;		// 颜色列表

}GVLED_XCFG, *PGVLED_XCFG;
///
//////////////////////////////////////////////////////////////////////////
/// Led設置參數，For XK700
typedef struct _GVLED_KCFG
{
#define START_PRESS			0	// 按下啓動效果
#define START_AUTO			1	// 自動啓動效果

#define TYPE_CONSISTENT		1	// 恆亮
#define TYPE_PULSING		2	// 呼吸，顔色數量1~2
#define TYPE_REACTIVE		3	// 觸發
#define TYPE_RIPPLE			4	// 波紋
#define TYPE_CYCLINGS		5	// 多彩循環
#define TYPE_WAVE			6	// 波浪
#define TYPE_LOL			7	// LOL功能鍵
#define TYPE_CS				8	// CS功能鍵

	int		nType;			// Led效果
	int		nSpeed;			// 速度
	int		nBright;		// 亮度
	int		nStartWay;		// 啓動效果方式
	int		nTimes;			// 播放效果次數
	int		nWidth;			// 寬度，波紋/波浪有效
	int		nAngle;			// 角度，波浪有效
	bool	bOn;			// 開關燈效
	int		nCount;			// 顔色數量
	unsigned long clrList[10];	// 顔色列表

}GVLED_KCFG, *PGVLED_KCFG;
///
//////////////////////////////////////////////////////////////////////////
/// XM300 LED设定值
typedef struct _GVLED_MCFG
{
	bool bBackLight;	// 是否背光，true表示燈亮，false表示off
	int  nBright;		// 亮度 0~10
	int  nSpeed;		// 速度 0~5
	unsigned long clr;	// Profile顔色
	int nType;			// 燈光模式

} GVLED_MCFG, *PGVLED_MCFG;
///
//////////////////////////////////////////////////////////////////////////
/// Keyboard 按鍵索引定義
typedef enum _GVLED_VK
{
	GVK_LCTRL = 0,		//	Left CTRL
	GVK_LWIN,			//	Left WIN
	GVK_LALT,			//	Left ALT
	GVK_SPACE,			//	Space
	GVK_RALT,			//	Right ALT
	GVK_WINLOCK,		//	WinLock
	GVK_FN,				//	Fn
	GVK_RCTRL,			//	Right CTRL
	GVK_LEFT,			//	Left
	GVK_DOWN,			//	Down
	GVK_RIGHT,			//	Right
	GVK_NUM0,			//	Num 0
	GVK_NUM_PERIOD,		//	Num .
	GVK_NUM_ENTER,		//	Num Enter
	GVK_LSHIFT,			//	Left Shift
	GVK_Z,				//	Z
	GVK_X,				//	X
	GVK_C,				//	C
	GVK_V,				//	V
	GVK_B,				//	B
	GVK_N,				//	N
	GVK_M,				//	M
	GVK_COMMA,			//	,<
	GVK_PERIOD,			//	.>
	GVK_SLASH,			//	/?
	GVK_RSHIFT,			//	Right Shift
	GVK_UP,				//	Up
	GVK_NUM1,			//	Num 1
	GVK_NUM2,			//	Num 2
	GVK_NUM3,			//	Num 3
	GVK_CAPSLOCK,		//	CapsLock
	GVK_A,				//	A
	GVK_S,				//	S
	GVK_D,				//	D
	GVK_F,				//	F
	GVK_G,				//	G
	GVK_H,				//	H
	GVK_J,				//	J
	GVK_K,				//	K
	GVK_L,				//	Left 
	GVK_SEMICOLON,		//	;:
	GVK_APOSTROPHE,		//	'"
	GVK_ENTER,			//	Enter
	GVK_NUM4,			//	Num 4
	GVK_NUM5,			//	Num 5
	GVK_NUM6,			//	Num 6
	GVK_NUM_PLUS,		//	NUm +
	GVK_TAB,			//	Tab
	GVK_Q,				//	Q
	GVK_W,				//	W
	GVK_E,				//	E
	GVK_R,				//	Right 
	GVK_T,				//	T
	GVK_Y,				//	Y
	GVK_U,				//	U
	GVK_I,				//	I
	GVK_O,				//	O
	GVK_P,				//	P
	GVK_LBRACKETS,		//	[{
	GVK_RBRACKETS,		//	]}
	GVK_BACKSLASH,		//	\|
	GVK_DELETE,			//	Delete
	GVK_END,			//	End
	GVK_PAGEDOWN,		//	PageDown
	GVK_NUM7,			//	Num 7
	GVK_NUM8,			//	Num 8
	GVK_NUM9,			//	Num 9
	GVK_WAVY,			//	`~
	GVK_1,				//	1
	GVK_2,				//	2
	GVK_3,				//	3
	GVK_4,				//	4
	GVK_5,				//	5
	GVK_6,				//	6
	GVK_7,				//	7
	GVK_8,				//	8
	GVK_9,				//	9
	GVK_0,				//	0
	GVK_MINUS,			//	-_
	GVK_EQUAL,			//	=+
	GVK_BACKSPACE,		//	BackSpace
	GVK_INSERT,			//	Insert
	GVK_HOME,			//	Home
	GVK_PAGEUP,			//	Page Up
	GVK_NUM,			//	Num
	GVK_NUM_DIVIDE,		//	Num /
	GVK_NUM_MULTIPLY,	//	Num *
	GVK_NUM_SUBTRACT,	//	Num -
	GVK_ESC,			//	Esc
	GVK_F1,				//	F1
	GVK_F2,				//	F2
	GVK_F3,				//	F3
	GVK_F4,				//	F4
	GVK_F5,				//	F5
	GVK_F6,				//	F6
	GVK_F7,				//	F7
	GVK_F8,				//	F8
	GVK_F9,				//	F9
	GVK_F10,			//	F10
	GVK_F11,			//	F11
	GVK_F12,			//	F12
	GVK_PRINTSCREEN,	//	PrintScreen
	GVK_SCROLLLOCK,		//	Scroll Lock
	GVK_PAUSE,			//	Pause
	GVK_LOGO,			//	Logo

}GVLED_VK, *PVLED_VK;



#ifdef __cplusplus
extern "C" {
#endif

	/****************************************************************************************
	 * 功能描述：
	 * 初始化設備，
	 * VID：固定为 0x1044
	 * PID：XH300(0x7A24), XC300(0x7A21), XC700(0x7A22), XCT7(0x7A23), XK700(0x7A19/0x7A1A), XM300(0x7A13)
	 *
	 * 输入参数：
	 * [in]  wVID      設備VID
	 * [in]  wPID      設備PID
	 * [out] nIndex    設備索引
	 * 
	 * 返回值：
	 * true 表示初始化成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedInit(unsigned short wVID, unsigned short wPID, int& nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取設備是否連接
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * 
	 * 返回值：
	 * true 表示仍然連接；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedIsConnect(int nIndex);
	
	/****************************************************************************************
	 * 功能描述：
	 * 重置Timer
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * 
	 * 返回值：
	 * true 表示仍然連接；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedResetTimer(int nIndex);
	
	/****************************************************************************************
	 * 功能描述：
	 * 設置顔色
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * 
	 * 返回值：
	 * true 表示仍然連接；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedSetClr(unsigned long clr, int nIndex);
	
	/****************************************************************************************
	 * 功能描述：
	 * 临时设定Led参数
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * [in] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXSet(int nIndex, GVLED_XCFG config);
	
	/****************************************************************************************
	 * 功能描述：
	 * 读取Led参数
	 *
	 * 输入参数：
	 * [in]  nIndex    設備索引
	 * [out] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXGet(int nIndex, GVLED_XCFG& config);
	
	/****************************************************************************************
	 * 功能描述：
	 * 保存参数设定，若不执行这条指令，插拔后会恢复原本状态
	 *
	 * 输入参数：
	 * [in]  nIndex    設備索引
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedXSave(int nIndex);

	/****************************************************************************************
	 * 功能描述：
	 * 设定XK700 Led参数
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * [in] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedKSet(int nIndex, GVLED_KCFG config);

	/****************************************************************************************
	 * 功能描述：
	 * 设定XK700 單獨按鍵 Led参数
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * [in] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedKSetSingle(int nIndex, bool bKbStatus[107], GVLED_KCFG config);

	/****************************************************************************************
	 * 功能描述：
	 * 獲取XK700默認Led参数
	 *
	 * 输入参数：
	 * [in]  nType     Led效果類型
	 * [out] config    Led控制参数
	 * 
	 * 返回值：
	 * void
	 ****************************************************************************************/
	GVLEDLIB_API void GvLedKGetDef(int nType, GVLED_KCFG& config);

	/****************************************************************************************
	 * 功能描述：
	 * 临时设定Led参数, For XM300
	 *
	 * 输入参数：
	 * [in] nIndex    設備索引
	 * [in] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMSet(int nIndex, GVLED_MCFG config);
	
	/****************************************************************************************
	 * 功能描述：
	 * 读取Led参数, For XM300
	 *
	 * 输入参数：
	 * [in]  nIndex    設備索引
	 * [out] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMGet(int nIndex, GVLED_MCFG& config);
	
	/****************************************************************************************
	 * 功能描述：
	 * 保存参数设定，若不执行这条指令，插拔后会恢复原本状态, For XM300
	 *
	 * 输入参数：
	 * [in]  nIndex    設備索引
	 * [out] config    Led控制参数
	 * 
	 * 返回值：
	 * true 表示发送成功；
	 ****************************************************************************************/
	GVLEDLIB_API bool GvLedMSave(int nIndex, GVLED_MCFG config);


#ifdef __cplusplus
}
#endif

#endif